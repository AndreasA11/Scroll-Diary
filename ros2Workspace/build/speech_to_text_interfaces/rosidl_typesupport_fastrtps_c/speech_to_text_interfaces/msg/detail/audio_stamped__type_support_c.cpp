// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from speech_to_text_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice
#include "speech_to_text_interfaces/msg/detail/audio_stamped__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "speech_to_text_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "speech_to_text_interfaces/msg/detail/audio_stamped__struct.h"
#include "speech_to_text_interfaces/msg/detail/audio_stamped__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // data
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // data

// forward declare type support functions


using _AudioStamped__ros_msg_type = speech_to_text_interfaces__msg__AudioStamped;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_speech_to_text_interfaces
bool cdr_serialize_speech_to_text_interfaces__msg__AudioStamped(
  const speech_to_text_interfaces__msg__AudioStamped * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: data
  {
    size_t size = ros_message->data.size;
    auto array_ptr = ros_message->data.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: sample_rate
  {
    cdr << ros_message->sample_rate;
  }

  // Field name: channels
  {
    cdr << ros_message->channels;
  }

  // Field name: has_speech
  {
    cdr << (ros_message->has_speech ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_speech_to_text_interfaces
bool cdr_deserialize_speech_to_text_interfaces__msg__AudioStamped(
  eprosima::fastcdr::Cdr & cdr,
  speech_to_text_interfaces__msg__AudioStamped * ros_message)
{
  // Field name: data
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.get_state();
    bool correct_size = cdr.jump(size);
    cdr.set_state(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->data.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->data);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->data, size)) {
      fprintf(stderr, "failed to create array for field 'data'");
      return false;
    }
    auto array_ptr = ros_message->data.data;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: sample_rate
  {
    cdr >> ros_message->sample_rate;
  }

  // Field name: channels
  {
    cdr >> ros_message->channels;
  }

  // Field name: has_speech
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->has_speech = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_speech_to_text_interfaces
size_t get_serialized_size_speech_to_text_interfaces__msg__AudioStamped(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AudioStamped__ros_msg_type * ros_message = static_cast<const _AudioStamped__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: data
  {
    size_t array_size = ros_message->data.size;
    auto array_ptr = ros_message->data.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: sample_rate
  {
    size_t item_size = sizeof(ros_message->sample_rate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: channels
  {
    size_t item_size = sizeof(ros_message->channels);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: has_speech
  {
    size_t item_size = sizeof(ros_message->has_speech);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_speech_to_text_interfaces
size_t max_serialized_size_speech_to_text_interfaces__msg__AudioStamped(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: data
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: sample_rate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: channels
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: has_speech
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = speech_to_text_interfaces__msg__AudioStamped;
    is_plain =
      (
      offsetof(DataType, has_speech) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_speech_to_text_interfaces
bool cdr_serialize_key_speech_to_text_interfaces__msg__AudioStamped(
  const speech_to_text_interfaces__msg__AudioStamped * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: data
  {
    size_t size = ros_message->data.size;
    auto array_ptr = ros_message->data.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: sample_rate
  {
    cdr << ros_message->sample_rate;
  }

  // Field name: channels
  {
    cdr << ros_message->channels;
  }

  // Field name: has_speech
  {
    cdr << (ros_message->has_speech ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_speech_to_text_interfaces
size_t get_serialized_size_key_speech_to_text_interfaces__msg__AudioStamped(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AudioStamped__ros_msg_type * ros_message = static_cast<const _AudioStamped__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: data
  {
    size_t array_size = ros_message->data.size;
    auto array_ptr = ros_message->data.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: sample_rate
  {
    size_t item_size = sizeof(ros_message->sample_rate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: channels
  {
    size_t item_size = sizeof(ros_message->channels);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: has_speech
  {
    size_t item_size = sizeof(ros_message->has_speech);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_speech_to_text_interfaces
size_t max_serialized_size_key_speech_to_text_interfaces__msg__AudioStamped(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: data
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: sample_rate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: channels
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: has_speech
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = speech_to_text_interfaces__msg__AudioStamped;
    is_plain =
      (
      offsetof(DataType, has_speech) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _AudioStamped__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const speech_to_text_interfaces__msg__AudioStamped * ros_message = static_cast<const speech_to_text_interfaces__msg__AudioStamped *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_speech_to_text_interfaces__msg__AudioStamped(ros_message, cdr);
}

static bool _AudioStamped__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  speech_to_text_interfaces__msg__AudioStamped * ros_message = static_cast<speech_to_text_interfaces__msg__AudioStamped *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_speech_to_text_interfaces__msg__AudioStamped(cdr, ros_message);
}

static uint32_t _AudioStamped__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_speech_to_text_interfaces__msg__AudioStamped(
      untyped_ros_message, 0));
}

static size_t _AudioStamped__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_speech_to_text_interfaces__msg__AudioStamped(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_AudioStamped = {
  "speech_to_text_interfaces::msg",
  "AudioStamped",
  _AudioStamped__cdr_serialize,
  _AudioStamped__cdr_deserialize,
  _AudioStamped__get_serialized_size,
  _AudioStamped__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _AudioStamped__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_AudioStamped,
  get_message_typesupport_handle_function,
  &speech_to_text_interfaces__msg__AudioStamped__get_type_hash,
  &speech_to_text_interfaces__msg__AudioStamped__get_type_description,
  &speech_to_text_interfaces__msg__AudioStamped__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, speech_to_text_interfaces, msg, AudioStamped)() {
  return &_AudioStamped__type_support;
}

#if defined(__cplusplus)
}
#endif
