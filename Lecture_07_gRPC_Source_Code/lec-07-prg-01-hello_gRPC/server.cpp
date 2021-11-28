// Reference: https://github.com/grpc/grpc/blob/v1.41.0/examples/cpp/helloworld/greeter_server.cc

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

#include <iostream>
#include <memory>
#include <string>
#include <csignal>
using namespace std;

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "hello_grpc.grpc.pb.h"
#include "hello_grpc.pb.h"

#include "hello_grpc.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using hello_grpc::MyService;
using hello_grpc::MyNumber;

void
SigIntHandler(int signo)
{
	exit(0);
}

class MyServiceServicer final : public MyService::Service {
    Status MyFunction(ServerContext* context, const MyNumber* request, MyNumber* response) override {
        response->set_value(my_func(request->value()));
        return Status::OK;
    }
};

void RunServer() {
    string server_address("0.0.0.0:50051");
    MyServiceServicer service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    builder.RegisterService(&service);

    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Starting server. Listening on port 50051." << endl;

    server->Wait();

    signal(SIGINT, SigIntHandler);
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}