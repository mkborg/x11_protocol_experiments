#include "cxx_template/deleter.h"
#include "cxx_template/handle.h"

void bar(const void * p);

//void.
//void *
void
//int
x_close(void * h)
{
  bar(h);
  return nullptr;
}

using Deleter = ::Template::Deleter<int, void, x_close>;
//using Handle = ::Template::Handle<int, -1, x_close>;
using Handle = ::Template::Handle<int, -1, Deleter>;


void foo()
{
  Handle handle;
  bar( static_cast<const void *>(&handle);
}
