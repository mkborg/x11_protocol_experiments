#include "connection.h"

#include "logger/debug_level.h"

int main()
{
  ++debug_level;
  x11::client2server::Connection connection;

  return 0;
}
