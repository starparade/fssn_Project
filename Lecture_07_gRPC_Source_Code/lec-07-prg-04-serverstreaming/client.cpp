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

#include "serverstreaming.grpc.pb.h"
#include "serverstreaming.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using serverstreaming::Message;
using serverstreaming::Number;
using serverstreaming::ServerStreaming;

class MyServiceClient {
    public:
        MyServiceClient(shared_ptr<Channel> channel)
            : stub_(ServerStreaming::NewStub(channel)) {}

        void generate_send_messages() {
            Message msg;
            Number request;
            request.set_value(5);
            ClientContext context;

            std::unique_ptr<ClientReader<Message>> reader(stub_->GetServerResponse(&context, request));
            while (reader->Read(&msg)) {
                cout << "[server to client] " << msg.message() << endl;
            }
            Status status = reader->Finish();
            if (!status.ok()) {
                std::cout << "serverstreaming rpc failed." << std::endl;
            }
        }

    private:
        unique_ptr<ServerStreaming::Stub> stub_;
};

int main(int argc, char** argv)
{
    MyServiceClient channel(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    channel.generate_send_messages();

    return 0;
}