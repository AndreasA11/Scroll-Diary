// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from speech_to_text_interfaces:msg/AudioStamped.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "speech_to_text_interfaces/msg/audio_stamped.hpp"


#ifndef SPEECH_TO_TEXT_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__STRUCT_HPP_
#define SPEECH_TO_TEXT_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__speech_to_text_interfaces__msg__AudioStamped __attribute__((deprecated))
#else
# define DEPRECATED__speech_to_text_interfaces__msg__AudioStamped __declspec(deprecated)
#endif

namespace speech_to_text_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AudioStamped_
{
  using Type = AudioStamped_<ContainerAllocator>;

  explicit AudioStamped_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sample_rate = 0ul;
      this->channels = 0;
      this->has_speech = false;
    }
  }

  explicit AudioStamped_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sample_rate = 0ul;
      this->channels = 0;
      this->has_speech = false;
    }
  }

  // field types and members
  using _data_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _data_type data;
  using _sample_rate_type =
    uint32_t;
  _sample_rate_type sample_rate;
  using _channels_type =
    uint8_t;
  _channels_type channels;
  using _has_speech_type =
    bool;
  _has_speech_type has_speech;

  // setters for named parameter idiom
  Type & set__data(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->data = _arg;
    return *this;
  }
  Type & set__sample_rate(
    const uint32_t & _arg)
  {
    this->sample_rate = _arg;
    return *this;
  }
  Type & set__channels(
    const uint8_t & _arg)
  {
    this->channels = _arg;
    return *this;
  }
  Type & set__has_speech(
    const bool & _arg)
  {
    this->has_speech = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator> *;
  using ConstRawPtr =
    const speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__speech_to_text_interfaces__msg__AudioStamped
    std::shared_ptr<speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__speech_to_text_interfaces__msg__AudioStamped
    std::shared_ptr<speech_to_text_interfaces::msg::AudioStamped_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AudioStamped_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    if (this->sample_rate != other.sample_rate) {
      return false;
    }
    if (this->channels != other.channels) {
      return false;
    }
    if (this->has_speech != other.has_speech) {
      return false;
    }
    return true;
  }
  bool operator!=(const AudioStamped_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AudioStamped_

// alias to use template instance with default allocator
using AudioStamped =
  speech_to_text_interfaces::msg::AudioStamped_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace speech_to_text_interfaces

#endif  // SPEECH_TO_TEXT_INTERFACES__MSG__DETAIL__AUDIO_STAMPED__STRUCT_HPP_
