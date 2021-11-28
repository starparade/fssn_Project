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

#include "clientstreaming.grpc.pb.h"
#include "clientstreaming.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using clientstreaming::Message;
using clientstreaming::Number;
using clientstreaming::ClientStreaming;

class MyServiceServicer final : public ClientStreaming::Service {
    public:
        Status GetServerResponse(ServerContext* context, ServerReader< Message>* reader, Number* response) override {
            Message msg;
            int msg_count = 0;
            Message previous;

            cout << "Server processing gRPC client-streaming." << endl;
            while (reader->Read(&msg)) {
                msg_count++;
                previous = msg;
            }

            response->set_value(msg_count);

            return Status::OK;
        }
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