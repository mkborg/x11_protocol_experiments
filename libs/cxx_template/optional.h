#pragma once

/// @brief    template for 'optional' value

namespace Template {

template <typename T>
class Optional
{
private:
  bool has_value_ = false;
  T value_;

public:
  inline bool has_value() const { return has_value_; }

  inline operator bool() const { return has_value(); }

  inline T value() const { return value_; }

  inline T operator*() const { return value(); }

  inline T value_or(const T& default_value) const
  {
    return has_value() ? value() : default_value;
  }

  inline Optional(bool has_value, const T& value)
    : has_value_(has_value)
    , value_(value)
  {
  }

  inline explicit Optional(const T& value)
    : Optional(true, value)
  {
  }

  inline explicit Optional()
    : Optional(false, T())
  {
  }

  inline Optional(const Optional& other)
    : Optional(other.has_value_, other.value_)
  {
  }

  inline Optional& operator =(const T& value)
  {
    has_value_ = true;
    value_ = value;
    return *this;
  }

  inline Optional& operator =(const Optional& other)
  {
    has_value_ = other.has_value_;
    value_ = other.value_;
    return *this;
  }
};

} // namespace Template
