// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from audio_samples_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "audio_samples_interfaces/msg/detail/audio_stamped__functions.h"
#include "audio_samples_interfaces/msg/detail/audio_stamped__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace audio_samples_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void AudioStamped_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) audio_samples_interfaces::msg::AudioStamped(_init);
}

void AudioStamped_fini_function(void * message_memory)
{
  auto typed_message = static_cast<audio_samples_interfaces::msg::AudioStamped *>(message_memory);
  typed_message->~AudioStamped();
}

size_t size_function__AudioStamped__data(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__AudioStamped__data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__AudioStamped__data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__AudioStamped__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__AudioStamped__data(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__AudioStamped__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__AudioStamped__data(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__AudioStamped__data(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AudioStamped_message_member_array[3] = {
  {
    "data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(audio_samples_interfaces::msg::AudioStamped, data),  // bytes offset in struct
    nullptr,  // default value
    size_function__AudioStamped__data,  // size() function pointer
    get_const_function__AudioStamped__data,  // get_const(index) function pointer
    get_function__AudioStamped__data,  // get(index) function pointer
    fetch_function__AudioStamped__data,  // fetch(index, &value) function pointer
    assign_function__AudioStamped__data,  // assign(index, value) function pointer
    resize_function__AudioStamped__data  // resize(index) function pointer
  },
  {
    "sample_rate",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(audio_samples_interfaces::msg::AudioStamped, sample_rate),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "channels",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(audio_samples_interfaces::msg::AudioStamped, channels),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AudioStamped_message_members = {
  "audio_samples_interfaces::msg",  // message namespace
  "AudioStamped",  // message name
  3,  // number of fields
  sizeof(audio_samples_interfaces::msg::AudioStamped),
  false,  // has_any_key_member_
  AudioStamped_message_member_array,  // message members
  AudioStamped_init_function,  // function to initialize message memory (memory has to be allocated)
  AudioStamped_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AudioStamped_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AudioStamped_message_members,
  get_message_typesupport_handle_function,
  &audio_samples_interfaces__msg__AudioStamped__get_type_hash,
  &audio_samples_interfaces__msg__AudioStamped__get_type_description,
  &audio_samples_interfaces__msg__AudioStamped__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace audio_samples_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<audio_samples_interfaces::msg::AudioStamped>()
{
  return &::audio_samples_interfaces::msg::rosidl_typesupport_introspection_cpp::AudioStamped_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, audio_samples_interfaces, msg, AudioStamped)() {
  return &::audio_samples_interfaces::msg::rosidl_typesupport_introspection_cpp::AudioStamped_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
