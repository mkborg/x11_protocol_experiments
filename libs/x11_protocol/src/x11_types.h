
/*
    https://www.x.org/releases/current/doc/xproto/x11protocol.html#Protocol_Formats

    Name	Value
    LISTofFOO	A type name of the form LISTofFOO means a counted list of elements of type FOO. The size of the length field may vary (it is not necessarily the same size as a FOO), and in some cases, it may be implicit. It is fully specified in Appendix B. Except where explicitly noted, zero-length lists are legal.

    BITMASK
    LISTofVALUE	The types BITMASK and LISTofVALUE are somewhat special. Various requests contain arguments of the form:

		value-mask: BITMASK
		value-list: LISTofVALUE

		These are used to allow the client to specify a subset of a heterogeneous collection of optional arguments. The value-mask specifies which arguments are to be provided; each such argument is assigned a unique bit position. The representation of the BITMASK will typically contain more bits than there are defined arguments. The unused bits in the value-mask must be zero (or the server generates a Value error). The value-list contains one value for each bit set to 1 in the mask, from least significant to most significant bit in the mask. Each value is represented with four bytes, but the actual value occupies only the least significant bytes as required. The values of the unused bytes do not matter.

    OR		A type of the form "T1 or ... or Tn" means the union of the indicated types. A single-element type is given as the element without enclosing braces.
    WINDOW	32-bit value (top three bits guaranteed to be zero)
    PIXMAP	32-bit value (top three bits guaranteed to be zero)
    CURSOR	32-bit value (top three bits guaranteed to be zero)
    FONT	32-bit value (top three bits guaranteed to be zero)
    GCONTEXT	32-bit value (top three bits guaranteed to be zero)
    COLORMAP	32-bit value (top three bits guaranteed to be zero)
    DRAWABLE	WINDOW or PIXMAP
    FONTABLE	FONT or GCONTEXT
    ATOM	32-bit value (top three bits guaranteed to be zero)
    VISUALID	32-bit value (top three bits guaranteed to be zero)
    VALUE	32-bit quantity (used only in LISTofVALUE)
    BYTE	8-bit value
    INT8	8-bit signed integer
    INT16	16-bit signed integer
    INT32	32-bit signed integer
    CARD8	8-bit unsigned integer
    CARD16	16-bit unsigned integer
    CARD32	32-bit unsigned integer
    TIMESTAMP	CARD32
    BITGRAVITY	{ Forget, Static, NorthWest, North, NorthEast, West, Center, East, SouthWest, South, SouthEast }
    WINGRAVITY	{ Unmap, Static, NorthWest, North, NorthEast, West, Center, East, SouthWest, South, SouthEast }
    BOOL	{ True, False }
    EVENT	{ KeyPress, KeyRelease, OwnerGrabButton, ButtonPress, ButtonRelease, EnterWindow, LeaveWindow, PointerMotion, PointerMotionHint, Button1Motion, Button2Motion, Button3Motion, Button4Motion, Button5Motion, ButtonMotion, Exposure, VisibilityChange, StructureNotify, ResizeRedirect, SubstructureNotify, SubstructureRedirect, FocusChange, PropertyChange, ColormapChange, KeymapState }
    POINTEREVENT	{ ButtonPress, ButtonRelease, EnterWindow, LeaveWindow, PointerMotion, PointerMotionHint, Button1Motion, Button2Motion, Button3Motion, Button4Motion, Button5Motion, ButtonMotion, KeymapState }
    DEVICEEVENT	{ KeyPress, KeyRelease, ButtonPress, ButtonRelease, PointerMotion, Button1Motion, Button2Motion, Button3Motion, Button4Motion, Button5Motion, ButtonMotion }
    KEYSYM	32-bit value (top three bits guaranteed to be zero)
    KEYCODE	CARD8
    BUTTON	CARD8
    KEYMASK	{ Shift, Lock, Control, Mod1, Mod2, Mod3, Mod4, Mod5 }
    BUTMASK	{ Button1, Button2, Button3, Button4, Button5 }
    KEYBUTMASK	KEYMASK or BUTMASK
    STRING8	LISTofCARD8
    STRING16	LISTofCHAR2B
    CHAR2B	[byte1, byte2: CARD8]
    POINT	[x, y: INT16]
    RECTANGLE	[x, y: INT16,
		width, height: CARD16]
    ARC		[x, y: INT16,
		width, height: CARD16,
		angle1, angle2: INT16]
    HOST	[family: { Internet, InternetV6, ServerInterpreted, DECnet, Chaos }
		address: LISTofBYTE]
*/
