// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hello_grpc.proto

#include "hello_grpc.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace hello_grpc {
constexpr MyNumber::MyNumber(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : value_(0){}
struct MyNumberDefaultTypeInternal {
  constexpr MyNumberDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~MyNumberDefaultTypeInternal() {}
  union {
    MyNumber _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT MyNumberDefaultTypeInternal _MyNumber_default_instance_;
}  // namespace hello_grpc
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_hello_5fgrpc_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_hello_5fgrpc_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_hello_5fgrpc_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_hello_5fgrpc_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::hello_grpc::MyNumber, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::hello_grpc::MyNumber, value_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::hello_grpc::MyNumber)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::hello_grpc::_MyNumber_default_instance_),
};

const char descriptor_table_protodef_hello_5fgrpc_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020hello_grpc.proto\022\nhello_grpc\"\031\n\010MyNumb"
  "er\022\r\n\005value\030\001 \001(\0052G\n\tMyService\022:\n\nMyFunc"
  "tion\022\024.hello_grpc.MyNumber\032\024.hello_grpc."
  "MyNumber\"\000b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_hello_5fgrpc_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_hello_5fgrpc_2eproto = {
  false, false, 138, descriptor_table_protodef_hello_5fgrpc_2eproto, "hello_grpc.proto", 
  &descriptor_table_hello_5fgrpc_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_hello_5fgrpc_2eproto::offsets,
  file_level_metadata_hello_5fgrpc_2eproto, file_level_enum_descriptors_hello_5fgrpc_2eproto, file_level_service_descriptors_hello_5fgrpc_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_hello_5fgrpc_2eproto_getter() {
  return &descriptor_table_hello_5fgrpc_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_hello_5fgrpc_2eproto(&descriptor_table_hello_5fgrpc_2eproto);
namespace hello_grpc {

// ===================================================================

class MyNumber::_Internal {
 public:
};

MyNumber::MyNumber(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:hello_grpc.MyNumber)
}
MyNumber::MyNumber(const MyNumber& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  value_ = from.value_;
  // @@protoc_insertion_point(copy_constructor:hello_grpc.MyNumber)
}

inline void MyNumber::SharedCtor() {
value_ = 0;
}

MyNumber::~MyNumber() {
  // @@protoc_insertion_point(destructor:hello_grpc.MyNumber)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void MyNumber::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void MyNumber::ArenaDtor(void* object) {
  MyNumber* _this = reinterpret_cast< MyNumber* >(object);
  (void)_this;
}
void MyNumber::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MyNumber::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void MyNumber::Clear() {
// @@protoc_insertion_point(message_clear_start:hello_grpc.MyNumber)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  value_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MyNumber::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 value = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          value_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* MyNumber::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:hello_grpc.MyNumber)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 value = 1;
  if (this->_internal_value() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_value(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:hello_grpc.MyNumber)
  return target;
}

size_t MyNumber::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hello_grpc.MyNumber)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 value = 1;
  if (this->_internal_value() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_value());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MyNumber::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    MyNumber::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MyNumber::GetClassData() const { return &_class_data_; }

void MyNumber::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<MyNumber *>(to)->MergeFrom(
      static_cast<const MyNumber &>(from));
}


void MyNumber::MergeFrom(const MyNumber& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hello_grpc.MyNumber)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_value() != 0) {
    _internal_set_value(from._internal_value());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MyNumber::CopyFrom(const MyNumber& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hello_grpc.MyNumber)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MyNumber::IsInitialized() const {
  return true;
}

void MyNumber::InternalSwap(MyNumber* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(value_, other->value_);
}

::PROTOBUF_NAMESPACE_ID::Metadata MyNumber::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_hello_5fgrpc_2eproto_getter, &descriptor_table_hello_5fgrpc_2eproto_once,
      file_level_metadata_hello_5fgrpc_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace hello_grpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::hello_grpc::MyNumber* Arena::CreateMaybeMessage< ::hello_grpc::MyNumber >(Arena* arena) {
  return Arena::CreateMessageInternal< ::hello_grpc::MyNumber >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
