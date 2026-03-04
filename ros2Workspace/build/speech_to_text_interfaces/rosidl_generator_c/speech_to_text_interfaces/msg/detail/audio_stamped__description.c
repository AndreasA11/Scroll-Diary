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
      0xbb, 0x02, 0x05, 0x1e, 0xb6, 0x64, 0x32, 0x82,
      0xfc, 0x0a, 0x8c, 0x7a, 0x29, 0x94, 0xeb, 0x49,
      0x55, 0x28, 0x85, 0x42, 0x4b, 0xb7, 0x12, 0x2b,
      0x4d, 0x97, 0x58, 0x30, 0xfa, 0xd0, 0x8c, 0x11,
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
      {speech_to_text_interfaces__msg__AudioStamped__FIELDS, 3, 3},
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
speech_to_text_interfaces__msg__AudioStamped__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {speech_to_text_interfaces__msg__AudioStamped__TYPE_NAME, 42, 42},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 48, 48},
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
