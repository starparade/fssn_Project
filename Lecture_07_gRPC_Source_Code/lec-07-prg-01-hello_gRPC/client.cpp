// Reference: https://github.com/grpc/grpc/blob/v1.41.0/examples/cpp/helloworld/greeter_client.cc

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
using namespace std;

#include <grpcpp/grpcpp.h>

#include "hello_grpc.grpc.pb.h"
#include "hello_grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using hello_grpc::MyService;
using hello_grpc::MyNumber;

class MyServiceClient {
    public:
        MyServiceClient(shared_ptr<Channel> channel)
            : stub_(MyService::NewStub(channel)) {}

        int MyFunction(int num) {
            MyNumber request;
            request.set_value(num);

            MyNumber response;

            ClientContext context;

            Status status = stub_->MyFunction(&context, request, &response);

            if (status.ok()) {
                return response.value();
            } else {
                cout << status.error_code() << ": " << status.error_message() << endl;
                return -1;
            }
        }

    private:
        unique_ptr<MyService::Stub> stub_;
};

int main(int argc, char** argv)
{
    MyServiceClient channel(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    int number = 4;
    int response = channel.MyFunction(number);

    cout << "gRPC result:" << response << endl;
}