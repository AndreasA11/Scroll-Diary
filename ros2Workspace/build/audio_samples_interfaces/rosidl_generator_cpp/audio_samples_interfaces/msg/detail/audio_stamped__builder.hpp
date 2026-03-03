// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from audio_samples_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "audio_samples_interfaces/msg/audio_stamped.hpp"


#ifndef AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__BUILDER_HPP_
#define AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "audio_samples_interfaces/msg/detail/audio_stamped__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace audio_samples_interfaces
{

namespace msg
{

namespace builder
{

class Init_AudioStamped_channels
{
public:
  explicit Init_AudioStamped_channels(::audio_samples_interfaces::msg::AudioStamped & msg)
  : msg_(msg)
  {}
  ::audio_samples_interfaces::msg::AudioStamped channels(::audio_samples_interfaces::msg::AudioStamped::_channels_type arg)
  {
    msg_.channels = std::move(arg);
    return std::move(msg_);
  }

private:
  ::audio_samples_interfaces::msg::AudioStamped msg_;
};

class Init_AudioStamped_sample_rate
{
public:
  explicit Init_AudioStamped_sample_rate(::audio_samples_interfaces::msg::AudioStamped & msg)
  : msg_(msg)
  {}
  Init_AudioStamped_channels sample_rate(::audio_samples_interfaces::msg::AudioStamped::_sample_rate_type arg)
  {
    msg_.sample_rate = std::move(arg);
    return Init_AudioStamped_channels(msg_);
  }

private:
  ::audio_samples_interfaces::msg::AudioStamped msg_;
};

class Init_AudioStamped_data
{
public:
  Init_AudioStamped_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AudioStamped_sample_rate data(::audio_samples_interfaces::msg::AudioStamped::_data_type arg)
  {
    msg_.data = std::move(arg);
    return Init_AudioStamped_sample_rate(msg_);
  }

private:
  ::audio_samples_interfaces::msg::AudioStamped msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::audio_samples_interfaces::msg::AudioStamped>()
{
  return audio_samples_interfaces::msg::builder::Init_AudioStamped_data();
}

}  // namespace audio_samples_interfaces

#endif  // AUDIO_SAMPLES_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__BUILDER_HPP_
