#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <zmq.hpp>

int main()
{
    zmq::context_t ctx(1);
    zmq::socket_t subscriber(ctx, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5557");
    subscriber.set(zmq::sockopt::subscribe, "");
    zmq::socket_t publisher(ctx, zmq::socket_type::push);
    publisher.connect("tcp://localhost:5558");

    srand((unsigned)time(NULL));
    while (1) {

        zmq_pollitem_t items[1];
        items[0].socket = subscriber;
        items[0].events = ZMQ_POLLIN;
        int rc = zmq_poll(items, 1, 100);
        if (rc > 0) {
            zmq::message_t message;
            subscriber.recv(message, zmq::recv_flags::none);
            std::cout << "I: received message " << message.to_string() << std::endl;
        }
        else {
            int ranNum = (rand() % 100) + 1;
            if (ranNum < 10) {
                zmq::message_t ranMsg(1);
                snprintf((char*)ranMsg.data(), 4, "%d", ranNum);
                publisher.send(ranMsg, zmq::send_flags::none);
                std::cout << "I: sending message " << ranNum << std::endl;
            }
        }
        
    }

    return 0;
}