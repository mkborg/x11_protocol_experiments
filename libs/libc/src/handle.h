#pragma once

//#include "template/deleter.h"
#include "template/handle.h"
#include "libc/close.h"

namespace libc {

inline
void close(int h) { ::libc::raw::close(h); }

using Handle = ::Template::Handle<int, -1, close>;
//using Fd = Handle;

/*
class Fd
  : private Handle
{
public:
};
*/

} // namespace libc
