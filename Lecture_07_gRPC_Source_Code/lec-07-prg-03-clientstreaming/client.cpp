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

#include "clientstreaming.grpc.pb.h"
#include "clientstreaming.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using clientstreaming::Message;
using clientstreaming::Number;
using clientstreaming::ClientStreaming;

Message make_message(const string& message)
{
    Message msg;
    msg.set_message(message);
    return msg;
}

class MyServiceClient {
    public:
        MyServiceClient(shared_ptr<Channel> channel)
            : stub_(ClientStreaming::NewStub(channel)) {}

        void generate_send_messages() {
            Message msg;
            Number response;
            ClientContext context;
            const int msg_num = 5;
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();

            default_random_engine generator(seed);
            uniform_int_distribution<int> delay_distribution(500, 1500);

            unique_ptr<ClientWriter<Message> > writer(stub_->GetServerResponse(&context, &response));
            for (int i = 1; i <= msg_num; i++) {
                const Message& m = make_message("message #" + to_string(i));
                message_list_.push_back(m);
                cout << "[client to server] " << m.message() << endl;
                if (!writer->Write(m)) {
                    // Broken stream.
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(delay_distribution(generator)));
            }
            writer->WritesDone();
            Status status = writer->Finish();
            if (status.ok()) {
                cout << "[server to client] " << response.value() << endl;
            } else {
                cout << "clientstreaming rpc failed." << endl;
            }
        }

    private:
        unique_ptr<ClientStreaming::Stub> stub_;
        vector<Message> message_list_;
};

int main(int argc, char** argv)
{
    MyServiceClient channel(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    channel.generate_send_messages();

    return 0;
}