// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CTTFileMan.proto

#ifndef PROTOBUF_INCLUDED_CTTFileMan_2eproto
#define PROTOBUF_INCLUDED_CTTFileMan_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_CTTFileMan_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_CTTFileMan_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_CTTFileMan_2eproto();
namespace eleWallet {
class OpRate;
class OpRateDefaultTypeInternal;
extern OpRateDefaultTypeInternal _OpRate_default_instance_;
class OpReply;
class OpReplyDefaultTypeInternal;
extern OpReplyDefaultTypeInternal _OpReply_default_instance_;
class OpRequest;
class OpRequestDefaultTypeInternal;
extern OpRequestDefaultTypeInternal _OpRequest_default_instance_;
}  // namespace eleWallet
namespace google {
namespace protobuf {
template<> ::eleWallet::OpRate* Arena::CreateMaybeMessage<::eleWallet::OpRate>(Arena*);
template<> ::eleWallet::OpReply* Arena::CreateMaybeMessage<::eleWallet::OpReply>(Arena*);
template<> ::eleWallet::OpRequest* Arena::CreateMaybeMessage<::eleWallet::OpRequest>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace eleWallet {

// ===================================================================

class OpRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:eleWallet.OpRequest) */ {
 public:
  OpRequest();
  virtual ~OpRequest();

  OpRequest(const OpRequest& from);

  inline OpRequest& operator=(const OpRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  OpRequest(OpRequest&& from) noexcept
    : OpRequest() {
    *this = ::std::move(from);
  }

  inline OpRequest& operator=(OpRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const OpRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const OpRequest* internal_default_instance() {
    return reinterpret_cast<const OpRequest*>(
               &_OpRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(OpRequest* other);
  friend void swap(OpRequest& a, OpRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline OpRequest* New() const final {
    return CreateMaybeMessage<OpRequest>(nullptr);
  }

  OpRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<OpRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const OpRequest& from);
  void MergeFrom(const OpRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(OpRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated string opParams = 2;
  int opparams_size() const;
  void clear_opparams();
  static const int kOpParamsFieldNumber = 2;
  const ::std::string& opparams(int index) const;
  ::std::string* mutable_opparams(int index);
  void set_opparams(int index, const ::std::string& value);
  #if LANG_CXX11
  void set_opparams(int index, ::std::string&& value);
  #endif
  void set_opparams(int index, const char* value);
  void set_opparams(int index, const char* value, size_t size);
  ::std::string* add_opparams();
  void add_opparams(const ::std::string& value);
  #if LANG_CXX11
  void add_opparams(::std::string&& value);
  #endif
  void add_opparams(const char* value);
  void add_opparams(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField<::std::string>& opparams() const;
  ::google::protobuf::RepeatedPtrField<::std::string>* mutable_opparams();

  // string opCmd = 1;
  void clear_opcmd();
  static const int kOpCmdFieldNumber = 1;
  const ::std::string& opcmd() const;
  void set_opcmd(const ::std::string& value);
  #if LANG_CXX11
  void set_opcmd(::std::string&& value);
  #endif
  void set_opcmd(const char* value);
  void set_opcmd(const char* value, size_t size);
  ::std::string* mutable_opcmd();
  ::std::string* release_opcmd();
  void set_allocated_opcmd(::std::string* opcmd);

  // @@protoc_insertion_point(class_scope:eleWallet.OpRequest)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField<::std::string> opparams_;
  ::google::protobuf::internal::ArenaStringPtr opcmd_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_CTTFileMan_2eproto;
};
// -------------------------------------------------------------------

class OpRate final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:eleWallet.OpRate) */ {
 public:
  OpRate();
  virtual ~OpRate();

  OpRate(const OpRate& from);

  inline OpRate& operator=(const OpRate& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  OpRate(OpRate&& from) noexcept
    : OpRate() {
    *this = ::std::move(from);
  }

  inline OpRate& operator=(OpRate&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const OpRate& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const OpRate* internal_default_instance() {
    return reinterpret_cast<const OpRate*>(
               &_OpRate_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(OpRate* other);
  friend void swap(OpRate& a, OpRate& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline OpRate* New() const final {
    return CreateMaybeMessage<OpRate>(nullptr);
  }

  OpRate* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<OpRate>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const OpRate& from);
  void MergeFrom(const OpRate& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(OpRate* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 rate = 1;
  void clear_rate();
  static const int kRateFieldNumber = 1;
  ::google::protobuf::int32 rate() const;
  void set_rate(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:eleWallet.OpRate)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 rate_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_CTTFileMan_2eproto;
};
// -------------------------------------------------------------------

class OpReply final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:eleWallet.OpReply) */ {
 public:
  OpReply();
  virtual ~OpReply();

  OpReply(const OpReply& from);

  inline OpReply& operator=(const OpReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  OpReply(OpReply&& from) noexcept
    : OpReply() {
    *this = ::std::move(from);
  }

  inline OpReply& operator=(OpReply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const OpReply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const OpReply* internal_default_instance() {
    return reinterpret_cast<const OpReply*>(
               &_OpReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(OpReply* other);
  friend void swap(OpReply& a, OpReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline OpReply* New() const final {
    return CreateMaybeMessage<OpReply>(nullptr);
  }

  OpReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<OpReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const OpReply& from);
  void MergeFrom(const OpReply& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(OpReply* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string message = 1;
  void clear_message();
  static const int kMessageFieldNumber = 1;
  const ::std::string& message() const;
  void set_message(const ::std::string& value);
  #if LANG_CXX11
  void set_message(::std::string&& value);
  #endif
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  ::std::string* mutable_message();
  ::std::string* release_message();
  void set_allocated_message(::std::string* message);

  // @@protoc_insertion_point(class_scope:eleWallet.OpReply)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr message_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_CTTFileMan_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// OpRequest

// string opCmd = 1;
inline void OpRequest::clear_opcmd() {
  opcmd_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& OpRequest::opcmd() const {
  // @@protoc_insertion_point(field_get:eleWallet.OpRequest.opCmd)
  return opcmd_.GetNoArena();
}
inline void OpRequest::set_opcmd(const ::std::string& value) {
  
  opcmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:eleWallet.OpRequest.opCmd)
}
#if LANG_CXX11
inline void OpRequest::set_opcmd(::std::string&& value) {
  
  opcmd_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:eleWallet.OpRequest.opCmd)
}
#endif
inline void OpRequest::set_opcmd(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  opcmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:eleWallet.OpRequest.opCmd)
}
inline void OpRequest::set_opcmd(const char* value, size_t size) {
  
  opcmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:eleWallet.OpRequest.opCmd)
}
inline ::std::string* OpRequest::mutable_opcmd() {
  
  // @@protoc_insertion_point(field_mutable:eleWallet.OpRequest.opCmd)
  return opcmd_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* OpRequest::release_opcmd() {
  // @@protoc_insertion_point(field_release:eleWallet.OpRequest.opCmd)
  
  return opcmd_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void OpRequest::set_allocated_opcmd(::std::string* opcmd) {
  if (opcmd != nullptr) {
    
  } else {
    
  }
  opcmd_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), opcmd);
  // @@protoc_insertion_point(field_set_allocated:eleWallet.OpRequest.opCmd)
}

// repeated string opParams = 2;
inline int OpRequest::opparams_size() const {
  return opparams_.size();
}
inline void OpRequest::clear_opparams() {
  opparams_.Clear();
}
inline const ::std::string& OpRequest::opparams(int index) const {
  // @@protoc_insertion_point(field_get:eleWallet.OpRequest.opParams)
  return opparams_.Get(index);
}
inline ::std::string* OpRequest::mutable_opparams(int index) {
  // @@protoc_insertion_point(field_mutable:eleWallet.OpRequest.opParams)
  return opparams_.Mutable(index);
}
inline void OpRequest::set_opparams(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:eleWallet.OpRequest.opParams)
  opparams_.Mutable(index)->assign(value);
}
#if LANG_CXX11
inline void OpRequest::set_opparams(int index, ::std::string&& value) {
  // @@protoc_insertion_point(field_set:eleWallet.OpRequest.opParams)
  opparams_.Mutable(index)->assign(std::move(value));
}
#endif
inline void OpRequest::set_opparams(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  opparams_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:eleWallet.OpRequest.opParams)
}
inline void OpRequest::set_opparams(int index, const char* value, size_t size) {
  opparams_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:eleWallet.OpRequest.opParams)
}
inline ::std::string* OpRequest::add_opparams() {
  // @@protoc_insertion_point(field_add_mutable:eleWallet.OpRequest.opParams)
  return opparams_.Add();
}
inline void OpRequest::add_opparams(const ::std::string& value) {
  opparams_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:eleWallet.OpRequest.opParams)
}
#if LANG_CXX11
inline void OpRequest::add_opparams(::std::string&& value) {
  opparams_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:eleWallet.OpRequest.opParams)
}
#endif
inline void OpRequest::add_opparams(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  opparams_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:eleWallet.OpRequest.opParams)
}
inline void OpRequest::add_opparams(const char* value, size_t size) {
  opparams_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:eleWallet.OpRequest.opParams)
}
inline const ::google::protobuf::RepeatedPtrField<::std::string>&
OpRequest::opparams() const {
  // @@protoc_insertion_point(field_list:eleWallet.OpRequest.opParams)
  return opparams_;
}
inline ::google::protobuf::RepeatedPtrField<::std::string>*
OpRequest::mutable_opparams() {
  // @@protoc_insertion_point(field_mutable_list:eleWallet.OpRequest.opParams)
  return &opparams_;
}

// -------------------------------------------------------------------

// OpRate

// int32 rate = 1;
inline void OpRate::clear_rate() {
  rate_ = 0;
}
inline ::google::protobuf::int32 OpRate::rate() const {
  // @@protoc_insertion_point(field_get:eleWallet.OpRate.rate)
  return rate_;
}
inline void OpRate::set_rate(::google::protobuf::int32 value) {
  
  rate_ = value;
  // @@protoc_insertion_point(field_set:eleWallet.OpRate.rate)
}

// -------------------------------------------------------------------

// OpReply

// string message = 1;
inline void OpReply::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& OpReply::message() const {
  // @@protoc_insertion_point(field_get:eleWallet.OpReply.message)
  return message_.GetNoArena();
}
inline void OpReply::set_message(const ::std::string& value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:eleWallet.OpReply.message)
}
#if LANG_CXX11
inline void OpReply::set_message(::std::string&& value) {
  
  message_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:eleWallet.OpReply.message)
}
#endif
inline void OpReply::set_message(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:eleWallet.OpReply.message)
}
inline void OpReply::set_message(const char* value, size_t size) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:eleWallet.OpReply.message)
}
inline ::std::string* OpReply::mutable_message() {
  
  // @@protoc_insertion_point(field_mutable:eleWallet.OpReply.message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* OpReply::release_message() {
  // @@protoc_insertion_point(field_release:eleWallet.OpReply.message)
  
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void OpReply::set_allocated_message(::std::string* message) {
  if (message != nullptr) {
    
  } else {
    
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:eleWallet.OpReply.message)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace eleWallet

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_CTTFileMan_2eproto
