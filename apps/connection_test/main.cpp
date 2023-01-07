#include "connection.h"

#include "logger/debug_level.h"

int main()
{
  ++debug_level;
  x11::Connection connection;

  return 0;
}
