// Reference: https://github.com/grpc/grpc/blob/v1.41.0/examples/cpp/route_guide/route_guide_server.cc

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

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "serverstreaming.grpc.pb.h"
#include "serverstreaming.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using serverstreaming::Message;
using serverstreaming::Number;
using serverstreaming::ServerStreaming;

class MyServiceServicer final : public ServerStreaming::Service {
    public:
        Status GetServerResponse(ServerContext* context, const Number* request, ServerWriter<Message>* writer) override {
            const int msg_num = request->value();
            for (int i = 1; i <= msg_num; i++) {
                Message msg;
                msg.set_message("message #" + to_string(i));
                message_list_.push_back(msg);
            }

            cout << "Server processing gRPC server-streaming " << msg_num << endl;
            for (const Message& m : message_list_) {
                writer->Write(m);
            }
            return Status::OK;
        }
    private:
        std::vector<Message> message_list_;
};

void serve() {
    string server_address("0.0.0.0:50051");
    MyServiceServicer service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Starting server. Listening on port 50051." << endl;
    server->Wait();
}

int main(int argc, char** argv)
{
    serve();

    return 0;
}