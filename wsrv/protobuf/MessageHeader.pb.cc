// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageHeader.proto

#include "MessageHeader.pb.h"

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

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace GaoProtobuf {
PROTOBUF_CONSTEXPR MessageHeader::MessageHeader(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.fromid_)*/int64_t{0}
  , /*decltype(_impl_.toid_)*/int64_t{0}
  , /*decltype(_impl_.groupid_)*/int64_t{0}
  , /*decltype(_impl_.typeid__)*/0
  , /*decltype(_impl_.namespaceid_)*/0
  , /*decltype(_impl_.classid_)*/0
  , /*decltype(_impl_.methodid_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct MessageHeaderDefaultTypeInternal {
  PROTOBUF_CONSTEXPR MessageHeaderDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~MessageHeaderDefaultTypeInternal() {}
  union {
    MessageHeader _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 MessageHeaderDefaultTypeInternal _MessageHeader_default_instance_;
}  // namespace GaoProtobuf
static ::_pb::Metadata file_level_metadata_MessageHeader_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_MessageHeader_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_MessageHeader_2eproto = nullptr;

const uint32_t TableStruct_MessageHeader_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::GaoProtobuf::MessageHeader, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::GaoProtobuf::MessageHeader, _impl_.fromid_),
  PROTOBUF_FIELD_OFFSET(::GaoProtobuf::MessageHeader, _impl_.toid_),
  PROTOBUF_FIELD_OFFSET(::GaoProtobuf::MessageHeader, _impl_.groupid_),
  PROTOBUF_FIELD_OFFSET(::GaoProtobuf::MessageHeader, _impl_.typeid__),
  PROTOBUF_FIELD_OFFSET(::GaoProtobuf::MessageHeader, _impl_.namespaceid_),
  PROTOBUF_FIELD_OFFSET(::GaoProtobuf::MessageHeader, _impl_.classid_),
  PROTOBUF_FIELD_OFFSET(::GaoProtobuf::MessageHeader, _impl_.methodid_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::GaoProtobuf::MessageHeader)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::GaoProtobuf::_MessageHeader_default_instance_._instance,
};

const char descriptor_table_protodef_MessageHeader_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\023MessageHeader.proto\022\013GaoProtobuf\"\206\001\n\rM"
  "essageHeader\022\016\n\006fromId\030\001 \001(\003\022\014\n\004toId\030\002 \001"
  "(\003\022\017\n\007groupId\030\003 \001(\003\022\016\n\006typeId\030\004 \001(\005\022\023\n\013n"
  "amespaceId\030\005 \001(\005\022\017\n\007classId\030\006 \001(\005\022\020\n\010met"
  "hodId\030\007 \001(\005B\016\252\002\013GaoProtobufb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_MessageHeader_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_MessageHeader_2eproto = {
    false, false, 195, descriptor_table_protodef_MessageHeader_2eproto,
    "MessageHeader.proto",
    &descriptor_table_MessageHeader_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_MessageHeader_2eproto::offsets,
    file_level_metadata_MessageHeader_2eproto, file_level_enum_descriptors_MessageHeader_2eproto,
    file_level_service_descriptors_MessageHeader_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_MessageHeader_2eproto_getter() {
  return &descriptor_table_MessageHeader_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_MessageHeader_2eproto(&descriptor_table_MessageHeader_2eproto);
namespace GaoProtobuf {

// ===================================================================

class MessageHeader::_Internal {
 public:
};

MessageHeader::MessageHeader(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:GaoProtobuf.MessageHeader)
}
MessageHeader::MessageHeader(const MessageHeader& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  MessageHeader* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.fromid_){}
    , decltype(_impl_.toid_){}
    , decltype(_impl_.groupid_){}
    , decltype(_impl_.typeid__){}
    , decltype(_impl_.namespaceid_){}
    , decltype(_impl_.classid_){}
    , decltype(_impl_.methodid_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.fromid_, &from._impl_.fromid_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.methodid_) -
    reinterpret_cast<char*>(&_impl_.fromid_)) + sizeof(_impl_.methodid_));
  // @@protoc_insertion_point(copy_constructor:GaoProtobuf.MessageHeader)
}

inline void MessageHeader::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.fromid_){int64_t{0}}
    , decltype(_impl_.toid_){int64_t{0}}
    , decltype(_impl_.groupid_){int64_t{0}}
    , decltype(_impl_.typeid__){0}
    , decltype(_impl_.namespaceid_){0}
    , decltype(_impl_.classid_){0}
    , decltype(_impl_.methodid_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

MessageHeader::~MessageHeader() {
  // @@protoc_insertion_point(destructor:GaoProtobuf.MessageHeader)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void MessageHeader::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void MessageHeader::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void MessageHeader::Clear() {
// @@protoc_insertion_point(message_clear_start:GaoProtobuf.MessageHeader)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.fromid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.methodid_) -
      reinterpret_cast<char*>(&_impl_.fromid_)) + sizeof(_impl_.methodid_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MessageHeader::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int64 fromId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.fromid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int64 toId = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.toid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int64 groupId = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.groupid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 typeId = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.typeid__ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 namespaceId = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _impl_.namespaceid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 classId = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          _impl_.classid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 methodId = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 56)) {
          _impl_.methodid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* MessageHeader::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:GaoProtobuf.MessageHeader)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 fromId = 1;
  if (this->_internal_fromid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(1, this->_internal_fromid(), target);
  }

  // int64 toId = 2;
  if (this->_internal_toid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(2, this->_internal_toid(), target);
  }

  // int64 groupId = 3;
  if (this->_internal_groupid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(3, this->_internal_groupid(), target);
  }

  // int32 typeId = 4;
  if (this->_internal_typeid_() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_typeid_(), target);
  }

  // int32 namespaceId = 5;
  if (this->_internal_namespaceid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(5, this->_internal_namespaceid(), target);
  }

  // int32 classId = 6;
  if (this->_internal_classid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(6, this->_internal_classid(), target);
  }

  // int32 methodId = 7;
  if (this->_internal_methodid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(7, this->_internal_methodid(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:GaoProtobuf.MessageHeader)
  return target;
}

size_t MessageHeader::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:GaoProtobuf.MessageHeader)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int64 fromId = 1;
  if (this->_internal_fromid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_fromid());
  }

  // int64 toId = 2;
  if (this->_internal_toid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_toid());
  }

  // int64 groupId = 3;
  if (this->_internal_groupid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_groupid());
  }

  // int32 typeId = 4;
  if (this->_internal_typeid_() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_typeid_());
  }

  // int32 namespaceId = 5;
  if (this->_internal_namespaceid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_namespaceid());
  }

  // int32 classId = 6;
  if (this->_internal_classid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_classid());
  }

  // int32 methodId = 7;
  if (this->_internal_methodid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_methodid());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MessageHeader::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    MessageHeader::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MessageHeader::GetClassData() const { return &_class_data_; }


void MessageHeader::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<MessageHeader*>(&to_msg);
  auto& from = static_cast<const MessageHeader&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:GaoProtobuf.MessageHeader)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_fromid() != 0) {
    _this->_internal_set_fromid(from._internal_fromid());
  }
  if (from._internal_toid() != 0) {
    _this->_internal_set_toid(from._internal_toid());
  }
  if (from._internal_groupid() != 0) {
    _this->_internal_set_groupid(from._internal_groupid());
  }
  if (from._internal_typeid_() != 0) {
    _this->_internal_set_typeid_(from._internal_typeid_());
  }
  if (from._internal_namespaceid() != 0) {
    _this->_internal_set_namespaceid(from._internal_namespaceid());
  }
  if (from._internal_classid() != 0) {
    _this->_internal_set_classid(from._internal_classid());
  }
  if (from._internal_methodid() != 0) {
    _this->_internal_set_methodid(from._internal_methodid());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MessageHeader::CopyFrom(const MessageHeader& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:GaoProtobuf.MessageHeader)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageHeader::IsInitialized() const {
  return true;
}

void MessageHeader::InternalSwap(MessageHeader* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MessageHeader, _impl_.methodid_)
      + sizeof(MessageHeader::_impl_.methodid_)
      - PROTOBUF_FIELD_OFFSET(MessageHeader, _impl_.fromid_)>(
          reinterpret_cast<char*>(&_impl_.fromid_),
          reinterpret_cast<char*>(&other->_impl_.fromid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MessageHeader::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_MessageHeader_2eproto_getter, &descriptor_table_MessageHeader_2eproto_once,
      file_level_metadata_MessageHeader_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace GaoProtobuf
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::GaoProtobuf::MessageHeader*
Arena::CreateMaybeMessage< ::GaoProtobuf::MessageHeader >(Arena* arena) {
  return Arena::CreateMessageInternal< ::GaoProtobuf::MessageHeader >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>