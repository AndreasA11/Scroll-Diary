// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from audio_samples_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice
#ifndef AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "audio_samples_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "audio_samples_interfaces/msg/detail/audio_stamped__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_audio_samples_interfaces
bool cdr_serialize_audio_samples_interfaces__msg__AudioStamped(
  const audio_samples_interfaces__msg__AudioStamped * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_audio_samples_interfaces
bool cdr_deserialize_audio_samples_interfaces__msg__AudioStamped(
  eprosima::fastcdr::Cdr &,
  audio_samples_interfaces__msg__AudioStamped * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_audio_samples_interfaces
size_t get_serialized_size_audio_samples_interfaces__msg__AudioStamped(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_audio_samples_interfaces
size_t max_serialized_size_audio_samples_interfaces__msg__AudioStamped(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_audio_samples_interfaces
bool cdr_serialize_key_audio_samples_interfaces__msg__AudioStamped(
  const audio_samples_interfaces__msg__AudioStamped * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_audio_samples_interfaces
size_t get_serialized_size_key_audio_samples_interfaces__msg__AudioStamped(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_audio_samples_interfaces
size_t max_serialized_size_key_audio_samples_interfaces__msg__AudioStamped(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_audio_samples_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, audio_samples_interfaces, msg, AudioStamped)();

#ifdef __cplusplus
}
#endif

#endif  // AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
