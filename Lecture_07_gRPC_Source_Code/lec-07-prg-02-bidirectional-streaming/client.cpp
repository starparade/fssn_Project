// Reference: https://github.com/grpc/grpc/blob/v1.41.0/examples/cpp/route_guide/route_guide_client.cc

/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
using namespace std;

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "Bidirectional.grpc.pb.h"
#include "Bidirectional.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using bidirectional::Message;
using bidirectional::Bidirectional;

Message make_message(const string& message)
{
    Message m;
    m.set_message(message);
    return m;
}

class MyServiceClient {
    public:
        MyServiceClient(shared_ptr<Channel> channel)
            : stub_(Bidirectional::NewStub(channel)) {}

        void generate_send_messages() {
            ClientContext context;

            shared_ptr<ClientReaderWriter<Message, Message> > stream(stub_->GetServerResponse(&context));

            thread writer([stream]() {
                vector<Message> messages {
                    make_message("message #1"),
                    make_message("message #2"),
                    make_message("message #3"),
                    make_message("message #4"),
                    make_message("message #5")
                };
                for (const Message& msg : messages) {
                    cout << "[client to server] " << msg.message() << endl;
                    stream->Write(msg);
                }
                stream->WritesDone();
            });

            Message server_message;
            while (stream->Read(&server_message)) {
                cout << "[server to client] " << server_message.message() << endl;
            }

            writer.join();
            Status status = stream->Finish();
            if (!status.ok()) {
                std::cout << "Bidirectional rpc failed." << std::endl;
            }
        }

    private:
        unique_ptr<Bidirectional::Stub> stub_;
};

int main(int argc, char** argv)
{
    MyServiceClient channel(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    channel.generate_send_messages();

    return 0;
}