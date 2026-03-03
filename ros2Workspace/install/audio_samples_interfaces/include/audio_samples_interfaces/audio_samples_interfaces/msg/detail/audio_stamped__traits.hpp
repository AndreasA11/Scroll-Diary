// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from audio_samples_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "audio_samples_interfaces/msg/audio_stamped.hpp"


#ifndef AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__TRAITS_HPP_
#define AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "audio_samples_interfaces/msg/detail/audio_stamped__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace audio_samples_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const AudioStamped & msg,
  std::ostream & out)
{
  out << "{";
  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: sample_rate
  {
    out << "sample_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_rate, out);
    out << ", ";
  }

  // member: channels
  {
    out << "channels: ";
    rosidl_generator_traits::value_to_yaml(msg.channels, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AudioStamped & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: sample_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sample_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_rate, out);
    out << "\n";
  }

  // member: channels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "channels: ";
    rosidl_generator_traits::value_to_yaml(msg.channels, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AudioStamped & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace audio_samples_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use audio_samples_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const audio_samples_interfaces::msg::AudioStamped & msg,
  std::ostream & out, size_t indentation = 0)
{
  audio_samples_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use audio_samples_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const audio_samples_interfaces::msg::AudioStamped & msg)
{
  return audio_samples_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<audio_samples_interfaces::msg::AudioStamped>()
{
  return "audio_samples_interfaces::msg::AudioStamped";
}

template<>
inline const char * name<audio_samples_interfaces::msg::AudioStamped>()
{
  return "audio_samples_interfaces/msg/AudioStamped";
}

template<>
struct has_fixed_size<audio_samples_interfaces::msg::AudioStamped>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<audio_samples_interfaces::msg::AudioStamped>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<audio_samples_interfaces::msg::AudioStamped>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__TRAITS_HPP_
