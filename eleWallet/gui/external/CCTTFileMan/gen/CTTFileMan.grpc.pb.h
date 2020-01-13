// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: CTTFileMan.proto
// Original file comments:
// Copyright 2018 gctt authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_CTTFileMan_2eproto__INCLUDED
#define GRPC_CTTFileMan_2eproto__INCLUDED

#include "CTTFileMan.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace eleWallet {

// The greeting service definition.
class Operation final {
 public:
  static constexpr char const* service_full_name() {
    return "eleWallet.Operation";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Sends a operation to wallet backend
    virtual ::grpc::Status DoRPCOperation(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::eleWallet::OpReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>> AsyncDoRPCOperation(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>>(AsyncDoRPCOperationRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>> PrepareAsyncDoRPCOperation(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>>(PrepareAsyncDoRPCOperationRaw(context, request, cq));
    }
    virtual ::grpc::Status SendRate(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::eleWallet::OpReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>> AsyncSendRate(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>>(AsyncSendRateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>> PrepareAsyncSendRate(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>>(PrepareAsyncSendRateRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      // Sends a operation to wallet backend
      virtual void DoRPCOperation(::grpc::ClientContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void DoRPCOperation(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::eleWallet::OpReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SendRate(::grpc::ClientContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SendRate(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::eleWallet::OpReply* response, std::function<void(::grpc::Status)>) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>* AsyncDoRPCOperationRaw(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>* PrepareAsyncDoRPCOperationRaw(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>* AsyncSendRateRaw(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::eleWallet::OpReply>* PrepareAsyncSendRateRaw(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status DoRPCOperation(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::eleWallet::OpReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>> AsyncDoRPCOperation(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>>(AsyncDoRPCOperationRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>> PrepareAsyncDoRPCOperation(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>>(PrepareAsyncDoRPCOperationRaw(context, request, cq));
    }
    ::grpc::Status SendRate(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::eleWallet::OpReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>> AsyncSendRate(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>>(AsyncSendRateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>> PrepareAsyncSendRate(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>>(PrepareAsyncSendRateRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void DoRPCOperation(::grpc::ClientContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response, std::function<void(::grpc::Status)>) override;
      void DoRPCOperation(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::eleWallet::OpReply* response, std::function<void(::grpc::Status)>) override;
      void SendRate(::grpc::ClientContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response, std::function<void(::grpc::Status)>) override;
      void SendRate(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::eleWallet::OpReply* response, std::function<void(::grpc::Status)>) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>* AsyncDoRPCOperationRaw(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>* PrepareAsyncDoRPCOperationRaw(::grpc::ClientContext* context, const ::eleWallet::OpRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>* AsyncSendRateRaw(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::eleWallet::OpReply>* PrepareAsyncSendRateRaw(::grpc::ClientContext* context, const ::eleWallet::OpRate& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_DoRPCOperation_;
    const ::grpc::internal::RpcMethod rpcmethod_SendRate_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Sends a operation to wallet backend
    virtual ::grpc::Status DoRPCOperation(::grpc::ServerContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response);
    virtual ::grpc::Status SendRate(::grpc::ServerContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_DoRPCOperation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_DoRPCOperation() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_DoRPCOperation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoRPCOperation(::grpc::ServerContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDoRPCOperation(::grpc::ServerContext* context, ::eleWallet::OpRequest* request, ::grpc::ServerAsyncResponseWriter< ::eleWallet::OpReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SendRate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_SendRate() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_SendRate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendRate(::grpc::ServerContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendRate(::grpc::ServerContext* context, ::eleWallet::OpRate* request, ::grpc::ServerAsyncResponseWriter< ::eleWallet::OpReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_DoRPCOperation<WithAsyncMethod_SendRate<Service > > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_DoRPCOperation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_DoRPCOperation() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::eleWallet::OpRequest, ::eleWallet::OpReply>(
          [this](::grpc::ServerContext* context,
                 const ::eleWallet::OpRequest* request,
                 ::eleWallet::OpReply* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->DoRPCOperation(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithCallbackMethod_DoRPCOperation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoRPCOperation(::grpc::ServerContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void DoRPCOperation(::grpc::ServerContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_SendRate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_SendRate() {
      ::grpc::Service::experimental().MarkMethodCallback(1,
        new ::grpc::internal::CallbackUnaryHandler< ::eleWallet::OpRate, ::eleWallet::OpReply>(
          [this](::grpc::ServerContext* context,
                 const ::eleWallet::OpRate* request,
                 ::eleWallet::OpReply* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->SendRate(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithCallbackMethod_SendRate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendRate(::grpc::ServerContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void SendRate(::grpc::ServerContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  typedef ExperimentalWithCallbackMethod_DoRPCOperation<ExperimentalWithCallbackMethod_SendRate<Service > > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_DoRPCOperation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_DoRPCOperation() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_DoRPCOperation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoRPCOperation(::grpc::ServerContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SendRate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_SendRate() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_SendRate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendRate(::grpc::ServerContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_DoRPCOperation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_DoRPCOperation() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_DoRPCOperation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoRPCOperation(::grpc::ServerContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDoRPCOperation(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_SendRate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_SendRate() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_SendRate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendRate(::grpc::ServerContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendRate(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_DoRPCOperation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_DoRPCOperation() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->DoRPCOperation(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_DoRPCOperation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DoRPCOperation(::grpc::ServerContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void DoRPCOperation(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_SendRate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_SendRate() {
      ::grpc::Service::experimental().MarkMethodRawCallback(1,
        new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->SendRate(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_SendRate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendRate(::grpc::ServerContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void SendRate(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_DoRPCOperation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_DoRPCOperation() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::eleWallet::OpRequest, ::eleWallet::OpReply>(std::bind(&WithStreamedUnaryMethod_DoRPCOperation<BaseClass>::StreamedDoRPCOperation, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_DoRPCOperation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status DoRPCOperation(::grpc::ServerContext* context, const ::eleWallet::OpRequest* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedDoRPCOperation(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::eleWallet::OpRequest,::eleWallet::OpReply>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SendRate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_SendRate() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< ::eleWallet::OpRate, ::eleWallet::OpReply>(std::bind(&WithStreamedUnaryMethod_SendRate<BaseClass>::StreamedSendRate, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_SendRate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SendRate(::grpc::ServerContext* context, const ::eleWallet::OpRate* request, ::eleWallet::OpReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSendRate(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::eleWallet::OpRate,::eleWallet::OpReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_DoRPCOperation<WithStreamedUnaryMethod_SendRate<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_DoRPCOperation<WithStreamedUnaryMethod_SendRate<Service > > StreamedService;
};

}  // namespace eleWallet


#endif  // GRPC_CTTFileMan_2eproto__INCLUDED
