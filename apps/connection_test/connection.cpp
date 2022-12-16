#include "connection.h"

#include <libc/getenv.h>

#include "logger/debug.h"

/*
    https://datacadamia.com/ssh/x11/display

    hostname:D.S

    where:

    hostname is the name of the computer where the X server runs. An omitted hostname means the localhost.
    D is a sequence number (usually 0). It can be varied if there are multiple displays connected to one computer.
    S is the screen number. A display can actually have multiple screens. Usually there's only one screen though where 0 is the default.

    Examples:

    localhost:4
    example.com:0
    :0.0

    hostname:D.S means screen S on display D of host hostname; the X server for this display is listening at TCP port 6000+D.
    host/unix:D.S means screen S on display D of host host; the X server for this display is listening at UNIX domain socket /tmp/.X11-unix/XD (so it's only reachable from host).
    :D.S is equivalent to host/unix:D.S, where host is the local hostname.
*/
/*
    https://docs.oracle.com/cd/E88353_01/html/E37853/x11-7.html

    From  the  user's perspective, every X server has a display name of the
       form:

              hostname:displaynumber.screennumber
       or
              protocol/hostname:displaynumber.screennumber

       This information is used by the application to determine how it  should
       connect  to  the  server  and which screen it should use by default (on
       displays with multiple monitors):

       protocol
               The protocol specifies the protocol to use  for  communication.
               Exactly  which  protocols  are supported is platform dependent,
               but most commonly supported ones are:

               tcp     TCP over IPv4 or IPv6
               inet    TCP over IPv4 only
               inet6   TCP over IPv6 only
               unix    UNIX Domain Sockets (same host only)
               local   Platform preferred local connection method
               If the  protocol  is  not  specified,  Xlib  uses  whatever  it
               believes is the most efficient transport.

       hostname
               The  hostname  specifies  the  name of the machine to which the
               display is physically connected.  If the hostname is not given,
               a connection to a server on the same machine will be used.

       displaynumber
               The  phrase  "display" is usually used to refer to a collection
               of monitors that share a common set of input devices (keyboard,
               mouse,  tablet, etc.).  Most workstations tend to only have one
               display.  Larger, multi-user systems, however, frequently  have
               several  displays  so  that  more  than one person can be doing
               graphics work at once.  To avoid confusion, each display  on  a
               machine  is assigned a display number (beginning at 0) when the
               X server for that display is started.  The display number  must
               always be given in a display name.

       screennumber
               Some displays share their input devices among two or more moni-
               tors.  These may be configured  as  a  single  logical  screen,
               which  allows  windows to move across screens, or as individual
               screens, each with their own set  of  windows.   If  configured
               such  that each monitor has its own set of windows, each screen
               is assigned a screen number (beginning at 0) when the X  server
               for  that  display  is  started.   If  the screen number is not
               given, screen 0 will be used.
*/
/*
    mk:
        AF_UNIX, SOCK_STREAM, 0
        AF_INET, SOCK_STREAM, 0

    hostname:displaynumber.screennumber
*/

namespace x11 {
namespace client2server {

Connection::Connection()
  : Connection(libc::cxx::getenv("DISPLAY"))
{
}

Connection::Connection(const std::string& display)
{
  DPRINTF("display='%s'", display.c_str());
}

} // namespace client2server
} // namespace x11
