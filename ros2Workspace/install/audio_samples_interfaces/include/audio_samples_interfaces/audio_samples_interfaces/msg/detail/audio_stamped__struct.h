// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from audio_samples_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "audio_samples_interfaces/msg/audio_stamped.h"


#ifndef AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__STRUCT_H_
#define AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/AudioStamped in the package audio_samples_interfaces.
typedef struct audio_samples_interfaces__msg__AudioStamped
{
  rosidl_runtime_c__float__Sequence data;
  uint32_t sample_rate;
  uint8_t channels;
} audio_samples_interfaces__msg__AudioStamped;

// Struct for a sequence of audio_samples_interfaces__msg__AudioStamped.
typedef struct audio_samples_interfaces__msg__AudioStamped__Sequence
{
  audio_samples_interfaces__msg__AudioStamped * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} audio_samples_interfaces__msg__AudioStamped__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__STRUCT_H_
