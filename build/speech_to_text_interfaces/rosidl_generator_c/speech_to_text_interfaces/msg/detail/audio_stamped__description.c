// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from speech_to_text_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice

#include "speech_to_text_interfaces/msg/detail/audio_stamped__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_speech_to_text_interfaces
const rosidl_type_hash_t *
speech_to_text_interfaces__msg__AudioStamped__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x53, 0xf3, 0x4c, 0x60, 0x3e, 0xe5, 0xeb, 0x88,
      0x6e, 0xb1, 0x0e, 0xd3, 0xf5, 0xd7, 0x10, 0x0c,
      0x96, 0x3e, 0x28, 0x61, 0x95, 0x35, 0x3c, 0x84,
      0x3d, 0x6d, 0xf3, 0x42, 0x9b, 0x55, 0x55, 0x0f,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char speech_to_text_interfaces__msg__AudioStamped__TYPE_NAME[] = "speech_to_text_interfaces/msg/AudioStamped";

// Define type names, field names, and default values
static char speech_to_text_interfaces__msg__AudioStamped__FIELD_NAME__data[] = "data";
static char speech_to_text_interfaces__msg__AudioStamped__FIELD_NAME__sample_rate[] = "sample_rate";
static char speech_to_text_interfaces__msg__AudioStamped__FIELD_NAME__channels[] = "channels";
static char speech_to_text_interfaces__msg__AudioStamped__FIELD_NAME__has_speech[] = "has_speech";

static rosidl_runtime_c__type_description__Field speech_to_text_interfaces__msg__AudioStamped__FIELDS[] = {
  {
    {speech_to_text_interfaces__msg__AudioStamped__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {speech_to_text_interfaces__msg__AudioStamped__FIELD_NAME__sample_rate, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {speech_to_text_interfaces__msg__AudioStamped__FIELD_NAME__channels, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {speech_to_text_interfaces__msg__AudioStamped__FIELD_NAME__has_speech, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
speech_to_text_interfaces__msg__AudioStamped__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {speech_to_text_interfaces__msg__AudioStamped__TYPE_NAME, 42, 42},
      {speech_to_text_interfaces__msg__AudioStamped__FIELDS, 4, 4},
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
  "uint8 channels\n"
  "bool has_speech";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
speech_to_text_interfaces__msg__AudioStamped__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {speech_to_text_interfaces__msg__AudioStamped__TYPE_NAME, 42, 42},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 64, 64},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
speech_to_text_interfaces__msg__AudioStamped__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *speech_to_text_interfaces__msg__AudioStamped__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
