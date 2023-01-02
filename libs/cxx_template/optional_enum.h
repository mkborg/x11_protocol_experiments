#pragma once

namespace Template {

template <typename T, T invalid_value>
class OptionalEnum
{
private:
  T value_;

public:
  inline bool has_value() const { return isOK(value_); }
  inline operator bool() const { return has_value(); }
  inline T value() const { return value_; }
  inline T operator*() const { return value(); }
  inline T value_or(const T& default_value) const
  {
    return has_value() ? value() : default_value;
  }

  //~OptionalEnum = default;

  explicit
  OptionalEnum()
    : value_(invalid_value)
  {
  }

  explicit
  OptionalEnum(const T& value)
    : value_(value)
  {
  }
};

} // namespace Template
