// Reference: https://zguide.zeromq.org/docs/chapter3/#The-Asynchronous-Client-Server-Pattern

//  Asynchronous client-to-server (DEALER to ROUTER)
//
//  While this example runs in a single process, that is to make
//  it easier to start and stop the example. Each task has its own
//  context and conceptually acts as a separate process.

#include <vector>
#include <thread>
#include <memory>
#include <functional>
#include <chrono>
#include <Windows.h>
#include <string>

#include <zmq.hpp>
#include <zhelpers.hpp>


//  This is our client task class.
//  It connects to the server, and then sends a request once per second
//  It collects responses as they arrive, and it prints them out. We will
//  run several client tasks in parallel, each with a different random ID.
//  Attention! -- this random work well only on linux.

class client_task {
public:
    client_task(char* id)
        : ctx_(1),
        client_socket_(ctx_, ZMQ_DEALER),
        id(id)
    {}
    
    void recvHandler(zmq::pollitem_t items[]) {
        while (true) {
            zmq::poll(items, 1, std::chrono::milliseconds(1000));
            if (items[0].revents & ZMQ_POLLIN) {
                zmq::message_t msg;
                client_socket_.recv(msg, zmq::recv_flags::none);
                std::cout << id << " received: " << msg.to_string() << std::endl;
            }
        }
    }
    
    void start() {
        client_socket_.set(zmq::sockopt::routing_id, id);
        client_socket_.connect("tcp://localhost:5570");
        std::cout << "Client " << id << " started" << std::endl;

        zmq::pollitem_t items[] = {
            { client_socket_, 0, ZMQ_POLLIN, 0 } };
        int request_nbr = 0;

        std::thread client_thread(std::bind(&client_task::recvHandler, this, std::ref(items)));
        client_thread.detach();

        try {
            while (true) {

                int strSize = 11;
                int req_nbr_c = request_nbr + 1;
                while ((req_nbr_c / 10) > 0) {
                    req_nbr_c = (int)(req_nbr_c / 10);
                    strSize++;
                }
                zmq::message_t request_string(strSize);
                snprintf((char*)request_string.data(), strSize, "request #%d", ++request_nbr);
                client_socket_.send(request_string, zmq::send_flags::none);
                std::cout << "Req #" << request_nbr << " sent..." << request_string.to_string() << std::endl;
                Sleep(1000);

            }
        }
        catch (std::exception& e) {}
    }

private:
    zmq::context_t ctx_;
    zmq::socket_t client_socket_;
    char* id;
};


//  The main thread simply starts several clients and a server, and then
//  waits for the server to finish.

int main(int argc, char* argv[])
{
    client_task ct1(argv[1]);

    std::thread t1(std::bind(&client_task::start, &ct1));

    t1.detach();

    getchar();
    return 0;
}