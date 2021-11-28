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
#include <cstdlib>

#include <zmq.hpp>
#include <zhelpers.hpp>


//  .split worker task
//  Each worker task works on one request at a time and sends a random number
//  of replies back, with random delays between replies:

class server_worker {
public:
    server_worker(zmq::context_t& ctx, int sock_type, int id)
        : ctx_(ctx),
        worker_(ctx_, sock_type),
        id(id)
    {}

    void work() {
        worker_.connect("inproc://backend");
        std::cout << "Worker#" << id << " started" << std::endl;

        try {
            while (true) {
                zmq::message_t identity;
                zmq::message_t msg;
                zmq::message_t copied_id;
                zmq::message_t copied_msg;
                worker_.recv(identity, zmq::recv_flags::none);
                worker_.recv(msg, zmq::recv_flags::none);
                std::cout << "Worker#" << id << " received " << msg.to_string() 
                    << " from "  << identity.to_string() << std::endl;
                copied_id.copy(identity);
                copied_msg.copy(msg);
                worker_.send(copied_id, zmq::send_flags::sndmore);
                worker_.send(copied_msg, zmq::send_flags::none);
            }
        }
        catch (std::exception& e) {}
    }

private:
    zmq::context_t& ctx_;
    zmq::socket_t worker_;
    int id;
};


//  .split server task
//  This is our server task.
//  It uses the multithreaded server model to deal requests out to a pool
//  of workers and route replies back to clients. One worker can handle
//  one request at a time but one client can talk to multiple workers at
//  once.

class server_task {
public:
    server_task(int num_server)
        : ctx_(1),
        frontend_(ctx_, ZMQ_ROUTER),
        backend_(ctx_, ZMQ_DEALER),
        num_server(num_server)
    {}

    void run() {
        frontend_.bind("tcp://*:5570");
        backend_.bind("inproc://backend");

        std::vector<server_worker*> worker;
        std::vector<std::thread*> worker_thread;
        for (int i = 0; i < num_server; ++i) {
            worker.push_back(new server_worker(ctx_, ZMQ_DEALER, i));

            worker_thread.push_back(new std::thread(std::bind(&server_worker::work, worker[i])));
            worker_thread[i]->detach();
        }


        try {
            zmq::proxy(frontend_, backend_);
        }
        catch (std::exception& e) {}

        for (int i = 0; i < num_server; ++i) {
            delete worker[i];
            delete worker_thread[i];
        }
    }

private:
    zmq::context_t ctx_;
    zmq::socket_t frontend_;
    zmq::socket_t backend_;
    int num_server;
};

int main(int argc, char* argv[])
{
    int num_server = atoi(argv[1]);
    server_task st(num_server);

    std::thread t4(std::bind(&server_task::run, &st));

    t4.detach();

    getchar();
    return 0;
}