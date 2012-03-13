Status of doom64ex support. Right now, not much, and probably broken.

lswad, spitwad - can view contents of doom64.wad
wadext - can extract raw lumps from doom64.wad
wadconvgfx-doom64ex - works, should be merged back into wadconvgfx
wadldc64, wadlc64 - work in progress
doom2to64 - semi-functional

wadpat and wadflat are meaningless for doom64: there are no patches in
64, just textures (stored in doom64.wad as PNGs). wadtex could use an
option to make it extract the PNG lumps between T_START and T_END.
wadtxls and lswad could use a similar option.

would be nice to have deutex support. Probably better off writing a
deutex clone from scratch than trying to add it to the existing code.
Call it tex64.

Music format is non-standard, but should map to MIDI and back OK.
