#include <string>
#include <iostream>

#include <zmq.hpp>

int main()
{
    zmq::context_t ctx(1);
    zmq::socket_t publisher(ctx, zmq::socket_type::pub);
    publisher.bind("tcp://*:5557");
    zmq::socket_t collector(ctx, zmq::socket_type::pull);
    collector.bind("tcp://*:5558");

    while (1) {

        zmq::message_t message;

        collector.recv(message, zmq::recv_flags::none);
        std::cout << "I: publishing update " << message.to_string() << std::endl;

        publisher.send(message, zmq::send_flags::none);

    }

    return 0;
}