// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from audio_samples_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "audio_samples_interfaces/msg/detail/audio_stamped__rosidl_typesupport_introspection_c.h"
#include "audio_samples_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "audio_samples_interfaces/msg/detail/audio_stamped__functions.h"
#include "audio_samples_interfaces/msg/detail/audio_stamped__struct.h"


// Include directives for member types
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  audio_samples_interfaces__msg__AudioStamped__init(message_memory);
}

void audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_fini_function(void * message_memory)
{
  audio_samples_interfaces__msg__AudioStamped__fini(message_memory);
}

size_t audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__size_function__AudioStamped__data(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__get_const_function__AudioStamped__data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__get_function__AudioStamped__data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__fetch_function__AudioStamped__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__get_const_function__AudioStamped__data(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__assign_function__AudioStamped__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__get_function__AudioStamped__data(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__resize_function__AudioStamped__data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_message_member_array[3] = {
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(audio_samples_interfaces__msg__AudioStamped, data),  // bytes offset in struct
    NULL,  // default value
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__size_function__AudioStamped__data,  // size() function pointer
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__get_const_function__AudioStamped__data,  // get_const(index) function pointer
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__get_function__AudioStamped__data,  // get(index) function pointer
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__fetch_function__AudioStamped__data,  // fetch(index, &value) function pointer
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__assign_function__AudioStamped__data,  // assign(index, value) function pointer
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__resize_function__AudioStamped__data  // resize(index) function pointer
  },
  {
    "sample_rate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(audio_samples_interfaces__msg__AudioStamped, sample_rate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "channels",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(audio_samples_interfaces__msg__AudioStamped, channels),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_message_members = {
  "audio_samples_interfaces__msg",  // message namespace
  "AudioStamped",  // message name
  3,  // number of fields
  sizeof(audio_samples_interfaces__msg__AudioStamped),
  false,  // has_any_key_member_
  audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_message_member_array,  // message members
  audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_init_function,  // function to initialize message memory (memory has to be allocated)
  audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_message_type_support_handle = {
  0,
  &audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_message_members,
  get_message_typesupport_handle_function,
  &audio_samples_interfaces__msg__AudioStamped__get_type_hash,
  &audio_samples_interfaces__msg__AudioStamped__get_type_description,
  &audio_samples_interfaces__msg__AudioStamped__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_audio_samples_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, audio_samples_interfaces, msg, AudioStamped)() {
  if (!audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_message_type_support_handle.typesupport_identifier) {
    audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &audio_samples_interfaces__msg__AudioStamped__rosidl_typesupport_introspection_c__AudioStamped_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
