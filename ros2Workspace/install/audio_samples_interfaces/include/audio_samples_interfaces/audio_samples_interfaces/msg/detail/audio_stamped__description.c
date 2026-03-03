// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from audio_samples_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice

#include "audio_samples_interfaces/msg/detail/audio_stamped__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_audio_samples_interfaces
const rosidl_type_hash_t *
audio_samples_interfaces__msg__AudioStamped__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xc3, 0x94, 0x77, 0xd7, 0x7a, 0x13, 0x0d, 0xe2,
      0xd9, 0x84, 0x8b, 0x82, 0xfb, 0xd8, 0xc8, 0x65,
      0x61, 0x87, 0xc0, 0x80, 0x20, 0xc5, 0xf7, 0xc2,
      0x0d, 0x18, 0xf9, 0x14, 0xf5, 0x46, 0x5a, 0x03,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char audio_samples_interfaces__msg__AudioStamped__TYPE_NAME[] = "audio_samples_interfaces/msg/AudioStamped";

// Define type names, field names, and default values
static char audio_samples_interfaces__msg__AudioStamped__FIELD_NAME__data[] = "data";
static char audio_samples_interfaces__msg__AudioStamped__FIELD_NAME__sample_rate[] = "sample_rate";
static char audio_samples_interfaces__msg__AudioStamped__FIELD_NAME__channels[] = "channels";

static rosidl_runtime_c__type_description__Field audio_samples_interfaces__msg__AudioStamped__FIELDS[] = {
  {
    {audio_samples_interfaces__msg__AudioStamped__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {audio_samples_interfaces__msg__AudioStamped__FIELD_NAME__sample_rate, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {audio_samples_interfaces__msg__AudioStamped__FIELD_NAME__channels, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
audio_samples_interfaces__msg__AudioStamped__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {audio_samples_interfaces__msg__AudioStamped__TYPE_NAME, 41, 41},
      {audio_samples_interfaces__msg__AudioStamped__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32[] data\n"
  "uint32 sample_rate\n"
  "uint8 channels";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
audio_samples_interfaces__msg__AudioStamped__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {audio_samples_interfaces__msg__AudioStamped__TYPE_NAME, 41, 41},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 48, 48},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
audio_samples_interfaces__msg__AudioStamped__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *audio_samples_interfaces__msg__AudioStamped__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
