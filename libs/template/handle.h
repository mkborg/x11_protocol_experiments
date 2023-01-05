#pragma once

/// @brief    'handle' template

namespace Template {

template<typename T, T CLOSED, void(*deleter)(T)>
class Handle
{
private:
  T handle_ = CLOSED;

public:
  inline T get() const { return handle_; }
  inline bool isClosed() const { return CLOSED == handle_; }
  inline operator bool() const { return !isClosed(); }

  void close()
  {
    if (!isClosed()) {
      deleter(handle_);
      handle_ = CLOSED;
    }
  }

  T release()
  {
    auto handle = handle_;
    handle_ = CLOSED;
    return handle;
  }

  void reset(T handle)
  {
    close();
    handle_ = handle;
  }

  ~Handle()
  {
    close();
  }

  inline explicit Handle()
    : handle_(CLOSED)
  {
  }

  inline explicit Handle(T handle)
    : handle_(handle)
  {
  }

  explicit Handle(const Handle& other) = delete;
  explicit Handle(Handle&& other)
    : handle_(other.handle_)
  {
    other.handle_ = CLOSED;
  }

  Handle& operator =(const Handle& other) = delete;
  Handle& operator =(Handle&& other)
  {
    if (this != &other) {
      reset(other.handle_);
      other.handle_ = CLOSED;
    }
    return *this;
  }
};

} // namespace Template
