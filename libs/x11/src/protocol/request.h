#pragma once

#include "cxx/raw/data.h"

#include <stdint.h>     // [u]int(8|16|32|64)_t

/*

    Every request contains an 8-bit major opcode and a 16-bit length
    field expressed in units of four bytes.

    Every request consists of four bytes of a header (containing the
    major opcode, the length field, and a data byte) followed by zero or
    more additional bytes of data.

    The length field defines the total length of the request, including
    the header. The length field in a request must equal the minimum
    length required to contain the request. If the specified length is
    smaller or larger than the required length, an error is generated.

    Unused bytes in a request are not required to be zero.

    Major opcodes 128 through 255 are reserved for extensions. Extensions
    are intended to contain multiple requests, so extension requests
    typically have an additional minor opcode encoded in the second data
    byte in the request header. However, the placement and interpretation
    of this minor opcode and of all other fields in extension requests
    are not defined by the core protocol.

    Every request on a given connection is implicitly assigned a sequence
    number, starting with one, that is used in replies, errors, and
    events.

*/
namespace x11 {
namespace protocol {
namespace request {

enum class Id
{
  CreateWindow			= 1,
  ChangeWindowAttributes	= 2,
  GetWindowAttributes		= 3,
  DestroyWindow			= 4,
  DestroySubWindows		= 5,
  ChangeSaveSet			= 6,
  ReparentWindow		= 7,
  MapWindow			= 8,
  MapSubWindows			= 9,
  UnmapWindow			= 10,
  UnmapSubWindows		= 11,
  ConfigureWindow		= 12,
  CirculateWindow		= 13,
  GetGeometry			= 14,
  QueryTree			= 15,
  InternAtom			= 16,
  GetAtomName			= 17,
  ChangeProperty		= 18,
  DeleteProperty		= 19,
  GetProperty			= 20,
  ListProperties		= 21,
  SetSelectionOwner		= 22,
  GetSelectionOwner		= 23,
  ConverSelection		= 24,
  SendEvent			= 25,
  GrabPointer			= 26,
  UngrabPointer			= 27,
  GrabButton			= 28,
  UngrabButton			= 29,
  ChangeActivePointerGrab	= 30,
  GrabKeyboard			= 31,
  UngrabKeyboard		= 32,
  GrabKey			= 33,
  UngrabKey			= 34,
  AllowEvents			= 35,
  GrabServer			= 36,
  UngrabServer			= 37,
  QueryPointer			= 38,
  GetMotionEvents		= 39,
  TranslateCoordinates		= 40,
  WarpPointer			= 41,
  SetInputFocus			= 42,
  GetInputFocus			= 43,
  QueryKeymap			= 44,
  OpenFont			= 45,
  CloseFont			= 46,
  QueryFont			= 47,
  QueryTextExtents		= 48,
  ListFonts			= 49,
  ListFontsWithInfo		= 50,
  SetFontPath			= 51,
  GetFontPath			= 52,
  CreatePixmap			= 53,
  FreePixmap			= 54,
  CreateGC			= 55,
  ChangeGC			= 56,
  CopyGC			= 57,
  SetDashes			= 58,
  SetClipRectangles		= 59,
  FreeGC			= 60,
  ClearArea			= 61,
  CopyArea			= 62,
  CopyPlane			= 63,
  PolyPoint			= 64,
  PolyLine			= 65,
  PolySegment			= 66,
  PolyRectangle			= 67,
  PolyArc			= 68,
  FillPoly			= 69,
  PolyFillRectangle		= 70,
  PolyFillArc			= 71,
  PutImage			= 72,
  GetImage			= 73,
  PolyText8			= 74,
  PolyText16			= 75,
  ImageText8			= 76,
  ImageText16			= 77,
  CreateColorMap		= 78,
  FreeColorMap			= 79,
  CopyColormapAndFree		= 80,
  InstallColormap		= 81,
  UninstallColormap		= 82,
  ListInstalledColormaps	= 83,
  AllocColor			= 84,
  AllocNamedColor		= 85,
  AllocColorCells		= 86,
  AllocColorPlanes		= 87,
  FreeColors			= 88,
  StoreColors			= 89,
  StoreNamedColor		= 90,
  QueryColors			= 91,
  LookupColor			= 92,
  CreateCursor			= 93,
  CreateGlyphCursor		= 94,
  FreeCursor			= 95,
  RecolorCursor			= 96,
  QueryBestSize			= 97,
  QueryExtension		= 98,
  ListExtensions		= 99,
  ChangeKeyboardMapping		= 100,
  GetKeyboardMapping		= 101,
  ChangeKeyboardControl		= 102,
  GetKeyboardControl		= 103,
  Bell				= 104,
  ChangePointerControl		= 105,
  GetPointerControl		= 106,
  SetScreenSaver		= 107,
  GetScreenSaver		= 108,
  ChangeHosts			= 109,
  ListHosts			= 110,
  SetAccessControl		= 111,
  SetCloseDownMode		= 112,
  KillClient			= 113,
  RotateProperties		= 114,
  ForceScreenSaver		= 115,
  SetPointerMapping		= 116,
  GetPointerMapping		= 117,
  SetModifierMapping		= 118,
  GetModifierMapping		= 119,

  NoOperation			= 127,
};

template<typename T>
inline uint16_t scaleSize(T size)
{
  return (size + 3) / 4;
}

struct Header
{
  uint8_t opcode;	// major opcode
  uint8_t unused_1;
  uint16_t size;	// request length, expressed in units of four bytes
  // uint32_t data[size - 1]
};

class GetAtomName
{
private:
  uint32_t atom_;
public:
  inline GetAtomName(uint32_t atom)
    : atom_(atom)
  {
  }
  operator cxx::raw::Data() const;
};

class NoOperation
{
public:
  NoOperation() = default;
  operator cxx::raw::Data() const;
};

} // namespace request
} // namespace protocol
} // namespace x11
