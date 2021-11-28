// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: Bidirectional.proto

#include "Bidirectional.pb.h"
#include "Bidirectional.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace bidirectional {

static const char* Bidirectional_method_names[] = {
  "/bidirectional.Bidirectional/GetServerResponse",
};

std::unique_ptr< Bidirectional::Stub> Bidirectional::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Bidirectional::Stub> stub(new Bidirectional::Stub(channel, options));
  return stub;
}

Bidirectional::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_GetServerResponse_(Bidirectional_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::bidirectional::Message, ::bidirectional::Message>* Bidirectional::Stub::GetServerResponseRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::bidirectional::Message, ::bidirectional::Message>::Create(channel_.get(), rpcmethod_GetServerResponse_, context);
}

void Bidirectional::Stub::async::GetServerResponse(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::bidirectional::Message,::bidirectional::Message>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::bidirectional::Message,::bidirectional::Message>::Create(stub_->channel_.get(), stub_->rpcmethod_GetServerResponse_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::bidirectional::Message, ::bidirectional::Message>* Bidirectional::Stub::AsyncGetServerResponseRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::bidirectional::Message, ::bidirectional::Message>::Create(channel_.get(), cq, rpcmethod_GetServerResponse_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::bidirectional::Message, ::bidirectional::Message>* Bidirectional::Stub::PrepareAsyncGetServerResponseRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::bidirectional::Message, ::bidirectional::Message>::Create(channel_.get(), cq, rpcmethod_GetServerResponse_, context, false, nullptr);
}

Bidirectional::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Bidirectional_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< Bidirectional::Service, ::bidirectional::Message, ::bidirectional::Message>(
          [](Bidirectional::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::bidirectional::Message,
             ::bidirectional::Message>* stream) {
               return service->GetServerResponse(ctx, stream);
             }, this)));
}

Bidirectional::Service::~Service() {
}

::grpc::Status Bidirectional::Service::GetServerResponse(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::bidirectional::Message, ::bidirectional::Message>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace bidirectional

