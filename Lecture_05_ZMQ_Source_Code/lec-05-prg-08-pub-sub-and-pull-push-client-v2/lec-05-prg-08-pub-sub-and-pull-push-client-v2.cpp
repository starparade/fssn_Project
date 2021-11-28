#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

#include <zmq.hpp>

int main(int argc, char* argv[])
{
    zmq::context_t ctx(1);
    zmq::socket_t subscriber(ctx, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5557");
    subscriber.set(zmq::sockopt::subscribe, "");
    zmq::socket_t publisher(ctx, zmq::socket_type::push);
    publisher.connect("tcp://localhost:5558");

    char* clientID = argv[1];
    srand((unsigned)time(NULL));
    while (1) {

        zmq_pollitem_t items[1];
        items[0].socket = subscriber;
        items[0].events = ZMQ_POLLIN;
        int rc = zmq_poll(items, 1, 100);
        if (rc > 0) {
            zmq::message_t message;
            subscriber.recv(message, zmq::recv_flags::none);
            std::cout << clientID << ": receive status => " << message.to_string() << std::endl;
        }
        else {
            int ranNum = (rand() % 100) + 1;
            zmq::message_t msg(15);
            if (ranNum < 10) {
                Sleep(1000);
                snprintf((char*)msg.data(), 14, "(%s:ON)", clientID);
                publisher.send(msg, zmq::send_flags::none);
                std::cout << clientID << ": send status - activated" << std::endl;
            }
            else if (ranNum > 90) {
                Sleep(1000);
                snprintf((char*)msg.data(), 15, "(%s:OFF)", clientID);
                publisher.send(msg, zmq::send_flags::none);
                std::cout << clientID << ": send status - activated" << std::endl;
            }
        }

    }

    return 0;
}