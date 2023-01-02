#pragma once

/// @brief    template for 'optional' value

namespace Template {

template <typename T>
class Optional
{
public:
  struct EMPTY {};
  //const static struct EMPTY EMPTY_v;

private:
  bool has_value_ = false;
  union {
    struct EMPTY EMPTY_;
    T value_;
  } u_;

public:
  inline bool has_value() const { return has_value_; }

  inline operator bool() const { return has_value(); }

  inline T value() const { return u_.value_; }

  inline T operator*() const { return value(); }

  inline T value_or(const T& default_value) const
  {
    return has_value() ? value() : default_value;
  }

  ~Optional()
  {
    if (has_value_) {
      u_.value_.~T();
    }
  }

  // by default 'Optional' is 'empty'
  //inline
  explicit
  Optional()
    : has_value_(false)
    , u_{.EMPTY_{}}
  {
  }

  // To explictly demonstrate intention:
  // using OptionalType = Optional<Type>;
  // OptionalType::Optional(EMPTY{})
  //inline
  Optional(EMPTY)
    : has_value_(false)
    , u_{.EMPTY_{}}
  {
  }

  // To explictly demonstrate intention:
  // using OptionalType = Optional<Type>;
  // OptionalType::makeEmpty()
  //inline
  static Optional makeEmpty()
  {
    return Optional(EMPTY{});
  }

  // copy constructor
  // using OptionalType = Optional<Type>;
  // Type value;
  // OptionalType(value);
  //inline
  explicit
  Optional(const T& value)
    : has_value_(true)
    , u_{.value_{value}}
  {
  }

#if 0
  // move constructor
  // using OptionalType = Optional<Type>;
  // Type value;
  // OptionalType(value);
  //inline
  explicit
  Optional(T&& value)
    : has_value_(true)
    , u_{.value_{value}}
  {
  }

  //inline
  Optional(const Optional& other)
    : Optional(
        (other.has_value_)
          ? Optional(other.value_)
          : Optional()
    )
  {
  }
#endif

#if 0
  // FIXME: Make sure 'other' correctly becomes 'empty'
  //inline
  Optional(Optional&& other)
    : Optional(
        (other.has_value_)
          ? Optional(other.value_)
          : Optional()
    )
  {
  }
#endif

#if 0
  //inline
  Optional& operator =(const T& value)
  {
    if (has_value_) {
      u_.value_.~T();
    }
    has_value_ = true;
    u_.value_ = value;
    return *this;
  }

  inline Optional& operator =(const Optional& other)
  {
    if (this == &other) { return *this; }
    if (has_value_) {
      u_.value_.~T();
    }
    has_value_ = other.has_value_;
    if (has_value_) {
      u_.value_ = other.value_;
    }
    return *this;
  }
#endif
};

} // namespace Template
