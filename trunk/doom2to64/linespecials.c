/*
type (upper bits):
0x200 - req red key
0x400 - req blue key
0x800 - req yellow key
0x1000 - walk trigger
0x2000 - shoot trigger
0x4000 - use trigger
0x8000 - retriggerable
*/

#define LDF_REDKEY 0x200
#define LDF_BLUEKEY 0x400
#define LDF_YELLOWKEY 0x800
#define LDF_WALK 0x1000
#define LDF_SHOOT 0x2000
#define LDF_USE 0x4000
#define LDF_RETRIG 0x8000

/*
type (bottom 8 bits):
1 Vertical Door Manual
2 Open Door Line Tag
3 Close Door Line Tag
4 Raise Door Line Tag
5 Raise Floor Line Tag
6 Ceiling Crush & Raise Line Tag
8 Build Stairs Line Tag
10 Platform Down Wait Up Line Tag
16 Door Close Wait 30 Seconds Open Line Tag
17 Spawn Light Strobe Line Tag
19 Lower Floor Line Tag
22 Plat Raise and Change Line Tag
25 Ceiling Crush and Raise Line Tag
30 Raise Floor To Nearest Line Tag
31 Vertical Door Open Once Manual
36 Lower Floor Fast Line Tag
37 Lower Floor and Change Line Tag
38 Lower Floor to Lowest Line Tag
39 Teleport to Dest Thing TID
43 Ceiling Lower to Floor Line Tag
44 Ceiling Crush and Raise Line Tag
52 Exit Level Manual
53 Perpetual Platform Raise Line Tag
54 Platform Stop Line Tag
56 Raise Floor Crush Line Tag
57 Ceiling Crush Stop Line Tag
58 Raise Floor 24 Units Line Tag
59 Raise Floor 24 Units and Change Line Tag
66 Platform Down Up Raise 24 Units Line Tag
67 Platform Down Up Raise 32 Units Line Tag
90 Artifact Switch 1 Matching Line Tag + 1
91 Artifact Switch 2 Matching Line Tag + 1
92 Artifact Switch 3 Matching Line Tag + 1
93 Modify Thing Flags Thing TID
94 Alert Thing Thing TID
100 Build Stairs Fast 16 Units Line Tag
108 Door Raise Fast Once Line Tag
109 Door Open/Close Fast Line Tag
110 Door Close Fast Line Tag
117 Vertical Door Fast Manual
118 Vertical Door Open Fast Manual
119 Raise Floor to Nearest Line Tag
121 Platform Down Wait Up Stay Fast Line Tag
122 Platform Up Wait Down Stay
123 Platform Up Wait Down Stay Fast Line Tag
124 Secret Exit Tag = Level/Map ##
125 Monster Teleport to Dest Thing TID
141 Silent Crusher Line Tag
200 Clear Camera View Manual
201 Set Camera Thing TID
202 Invoke Dart Thing TID
203 Delay Timer Tag = Delay Amount
204 Set Macro Integer Tag = Set Integer
205 Modify Sector Color 1 Line Tag, Integer = Light ID
206 Modify Sector Color 2 Line Tag, Integer = Light ID
207 Modify Sector Color 3 Line Tag, Integer = Light ID
208 Modify Sector Color 4 Line Tag, Integer = Light ID
209 Modify Sector Color 5 Line Tag, Integer = Light ID
210 Custom Ceiling Line Tag, Integer = Move Amount
212 Custom Floor Line Tag, Integer = Move Amount
214 Move Elevator Sector Line Tag, Integer = Move Amount
218 Change Line Flags Tag = Dest Line Tag, Integer = Source Line Tag
219 Modify Line Texture Tag = Dest Line Tag, Integer = Source Line Tag
220 Modify Sector Flags Tag = Dest Sector Tag, Integer = Source Sector Tag
221 Modify Sector Specials Tag = Dest Sector Tag, Integer = Source Sector Tag
222 Modify Sector Lights Tag = Dest Sector Tag, Integer = Source Sector Tag
223 Modify Sector Flats Tag = Dest Sector Tag, Integer = Source Sector Tag
224 Spawn Thing Thing TID
225 Quake Tag = Duration
226 Custom Ceiling Fast Line Tag, Integer = Move Amount
233 Freeze Player Tag = Duration
234 Change Light by Light Tag Tag = Dest Light ID, Integer = Source Light ID
235 Modify Light Data Tag = Dest Sector Tag, Integer = Source Sector Tag
236 Custom Down/Up Platform Line Tag, Integer = Move Amount
237 Custom Down/Up Platform Fast Line Tag, Integer = Move Amount
238 Custom Up/Down Platform Line Tag, Integer = Move Amount
239 Custom Up/Down Platform Fast Line Tag, Integer = Move Amount
240 Trigger Random Lines Tag = Triggered Lines With Matching Tag
241 Split Open Sector Line Tag, Integer = Move Amount
242 Fade Out Thing Thing TID
243 Move and Aim Camera Tag = Thing TID, Integer = Next Camera Spot
244 Set Floor Height Line Tag, Integer = Height
245 Set Ceiling Height Line Tag, Integer = Height
246 Restart Macro at Script Line Tag = Repeat count, Integer = Script Line ##
247 Move Floor by Height Line Tag, Integer = Z Height
248 Suspend Macro Script Tag = Macro Line Type (256 - 511)
249 Telefrag to Dest Thing TID
250 Toggle Macros On Tag = Macro Line Type (256 - 511)
251 Toggle Macros Off Tag = Macro Line Type (256 - 511)
252 Move Ceiling by Height Line Tag, Integer = Z Height
253 Unlock Cheat Menu Manual
254 Morph Logo on F_SKYG Sky Manual
	*/

int linedef_type_conv[] = {
/* ldt   0 x "-- Normal"        "--  Normal" */
0,
/* ldt   1 d "DR Open door"     "DR  Open  door" */
LDF_USE | LDF_RETRIG | 1,
/* ldt   2 d "W1 Open door (O)" "W1  Open  door (stays open)" */
LDF_WALK | 2,
/* ldt   3 d "W1 Close door"    "W1  Close door" */
LDF_WALK | 3,
/* ldt   4 d "W1 Open door"     "W1  Open  door" */
LDF_WALK | 4,
/* ldt   5 F "W1 Floor up LIC"  "W1  Raise floor to LIC" */
LDF_WALK | 5,
/* ldt   6 C "W1 Crush FF"      "W1  Start fast crushing, fast hurt" */
LDF_WALK | 6,
/* ldt   7 s "S1 Raise stairs"  "S1  Raise stairs (several sectors 0/999)" */
LDF_USE | 7,
/* ldt   8 s "W1 Raise stairs"  "W1  Raise stairs (several sectors 0/999)" */
LDF_WALK | 8,
/* ldt   9 x "S1 Donut"         "S1  Lower floor, raise Ne. floor (NXP) 'Donut'" */
0,   /* not supported in 64! */
/* ldt  10 l "W1 Lower lift"    "W1  Lower lift" */
0,   /* not supported in 64! */
/* ldt  11 e "S- End level"     "S-  End level, go to next level" */
LDF_USE | 52,
/* ldt  12 L "W1 Light to HE"   "W1  Light level goes to HE" */
0,   /* not supported in 64! */
/* ldt  13 L "W1 Light to 255"  "W1  Light level goes to 255" */
0,   /* not supported in 64! */
/* ldt  14 F "S1& F. up 32 TX"  "S1& Raise floor by 32 (TX)" */
0, // not yet
/* ldt  15 F "S1& F. up 24 TX"  "S1& Raise floor by 24 (TX)" */
0, // not yet
/* ldt  16 d "W1 Close for 30s" "W1  Close door for 30 seconds" */
0, // not yet
/* ldt  17 L "W1 Start blink"   "W1  Start blinking lights" */
0, // not yet
/* ldt  18 F "S1 Floor up nhEF" "S1  Raise floor to nhEF" */
0, // not yet
/* ldt  19 f "W1 Floor dn HEF"  "W1  Lower floor to HEF" */
0, // not yet
/* ldt  20 F "S1& F up nhEF TX" "S1& Raise floor to nhEF (TX)" */
0, // not yet
/* ldt  21 l "S1 Lower lift"    "S1  Lower lift" */
0, // not yet
/* ldt  22 F "W1& F up nhEF TX" "W1& Raise floor to nhEF (TX)" */
0, // not yet
/* ldt  23 f "S1 Floor dn LEF"  "S1  Lower floor to LEF" */
0, // not yet
/* ldt  24 F "G1 Floor up LIC"  "G1  Raise floor to LIC" */
0, // not yet
/* ldt  25 C "W1 Crush FS"      "W1  Start fast crushing, slow hurt" */
0, // not yet
/* ldt  26 b "DR Open blue dr"  "DR  Open  door, blue key" */
LDF_USE | LDF_BLUEKEY | LDF_RETRIG | 2,
/* ldt  27 y "DR Open yel dr"   "DR  Open  door, yellow key" */
LDF_USE | LDF_YELLOWKEY | LDF_RETRIG | 2,
/* ldt  28 r "DR Open red dr"   "DR  Open  door, red key" */
LDF_USE | LDF_REDKEY | LDF_RETRIG | 2,
/* ldt  29 d "S1 Open door"     "S1  Open  door" */
LDF_USE | 1,
/* ldt  30 F "W1 Floor up SLT"  "W1  Raise floor by ShortestLowerTexture" */
0, // not yet
/* ldt  31 d "D1 Open door (O)" "D1  Open  door (stays open)" */
LDF_USE | 2,
/* ldt  32 b "D1 Open blu (O)"  "D1  Open  door (stays open), blue key" */
LDF_USE | LDF_BLUEKEY | 2,
/* ldt  33 r "D1 Open red (O)"  "D1  Open  door (stays open), red key" */
LDF_USE | LDF_REDKEY | 2,
/* ldt  34 y "D1 Open yel (O)"  "D1  Open  door (stays open), yellow key" */
LDF_USE | LDF_YELLOWKEY | 2,
/* ldt  35 L "W1 Light to 35"   "W1  Light level goes to 35" */
0, // not yet
/* ldt  36 f "W1 F. DN HEF+8"   "W1  Lower turbo floor to HEF + 8" */
0, // not yet
/* ldt  37 f "W1 F. dn LEF NXP" "W1  Lower floor to LEF (NXP)" */
0, // not yet
/* ldt  38 f "W1 Floor dn LEF"  "W1  Lower floor to LEF" */
0, // not yet
/* ldt  39 t "W1 Teleport"      "W1  Teleport to another sector" */
0, // not yet
/* ldt  40 c "W1 Ceil up HEC"   "W1  Raise ceiling to HEC" */
0, // not yet
/* ldt  41 c "S1 Ceil dn floor" "S1  Lower ceiling to floor" */
0, // not yet
/* ldt  42 d "SR Close door"    "SR  Close door" */
0, // not yet
/* ldt  43 c "SR Ceil dn floor" "SR  Lower ceiling to floor" */
0, // not yet
/* ldt  44 c "W1 Ceil dn flr+8" "W1  Lower ceiling to floor + 8" */
0, // not yet
/* ldt  45 f "SR Floor dn HEF"  "SR  Lower floor to HEF" */
0, // not yet
/* ldt  46 d "GR Open door (O)" "GR  Open  door (stays open)" */
0, // not yet
/* ldt  47 F "G1 F. up nhEF TX" "G1  Raise floor to nhEF (TX)" */
0, // not yet
/* ldt  48 A "-- Scroll left"   "--  Scrolling wall, left" */
0, // not yet
/* ldt  49 c "S1 Ceil dn flr+8" "S1  Lower ceiling to floor + 8" */
0, // not yet
/* ldt  50 d "S1 Close door"    "S1  Close door" */
0, // not yet
/* ldt  51 e "S- Secret level"  "S-  End level, go to secret level" */
0, // not yet
/* ldt  52 e "W- End level"     "W-  End level, go to next level" */
0, // not yet
/* ldt  53 m "W1 Start moving"  "W1  Start moving floor" */
0, // not yet
/* ldt  54 m "W1 Stop moving f" "W1  Stop  moving floor" */
0, // not yet
/* ldt  55 F "S1 F. up LIC-8"   "S1  Raise floor to LIC - 8, crush" */
0, // not yet
/* ldt  56 F "W1& F. up LIC-8"  "W1& Raise floor to LIC - 8, crush" */
0, // not yet
/* ldt  57 C "W1& Stop crush"   "W1& Stop  crushing" */
0, // not yet
/* ldt  58 F "W1 Floor up 24"   "W1  Raise floor by 24" */
0, // not yet
/* ldt  59 F "W1 F. up 24 TXP"  "W1  Raise floor by 24 (TXP)" */
0, // not yet
/* ldt  60 f "SR Floor dn LEF"  "SR  Lower floor to LEF" */
0, // not yet
/* ldt  61 d "SR Open door (O)" "SR  Open  door (stays open)" */
0, // not yet
/* ldt  62 l "SR Lower lift"    "SR  Lower lift" */
0, // not yet
/* ldt  63 d "SR Open door"     "SR  Open  door" */
0, // not yet
/* ldt  64 F "SR Floor up LIC"  "SR  Raise floor to LIC" */
0, // not yet
/* ldt  65 F "SR F. up LIC-8"   "SR  Raise floor to LIC - 8, crush" */
0, // not yet
/* ldt  66 F "SR& F. up 24 TX"  "SR& Raise floor by 24 (TX)" */
0, // not yet
/* ldt  67 F "SR& F. up 32 TX"  "SR& Raise floor by 32 (TX)" */
0, // not yet
/* ldt  68 f "SR& F up nhEF TX" "SR& Raise floor to nhEF (TX)" */
0, // not yet
/* ldt  69 F "SR F. up nhEF"    "SR  Raise floor to nhEF" */
0, // not yet
/* ldt  70 f "SR F. DN HEF+8"   "SR  Lower turbo floor to HEF + 8" */
0, // not yet
/* ldt  71 f "S1 F. DN HEF+8"   "S1  Lower turbo floor to HEF + 8" */
0, // not yet
/* ldt  72 c "WR Ceil dn flr+8" "WR  Lower ceiling to floor + 8" */
0, // not yet
/* ldt  73 C "WR& Crush SS"     "WR& Start slow crushing, slow hurt" */
0, // not yet
/* ldt  74 C "WR& Stop crush"   "WR& Stop  crushing" */
0, // not yet
/* ldt  75 d "WR Close door"    "WR  Close door" */
0, // not yet
/* ldt  76 d "WR Close for 30s" "WR  Close door for 30 seconds" */
0, // not yet
/* ldt  77 C "WR& Crush FF"     "WR& Start fast crushing, fast hurt" */
0, // not yet
/* ldt  78 x "SR Floor -- NXP"  "SR  Floor transfer (NXP) [Boom]" */
0, // not yet
/* ldt  79 L "WR Light to 35"   "WR  Light level goes to 35" */
0, // not yet
/* ldt  80 L "WR Light to HE"   "WR  Light level goes to HE" */
0, // not yet
/* ldt  81 L "WR Light to 255"  "WR  Light level goes to 255" */
0, // not yet
/* ldt  82 f "WR Floor dn LEF"  "WR  Lower floor to LEF" */
0, // not yet
/* ldt  83 f "WR Floor dn HEF"  "WR  Lower floor to HEF" */
0, // not yet
/* ldt  84 f "WR F. dn LEF NXP" "WR  Lower floor to LEF (NXP)" */
0, // not yet
/* ldt  85 A "-- Scroll right"  "--  Scrolling wall, right [Boom]" */
0, // not yet
/* ldt  86 d "WR Open door (O)" "WR  Open  door (stays open)" */
LDF_WALK | LDF_RETRIG | 2,
/* ldt  87 m "WR& Start moving" "WR& Start moving floor" */
0, // not yet
/* ldt  88 l "WR Lower lift"    "WR  Lower lift" */
0, // not yet
/* ldt  89 m "WR& Stop moving"  "WR& Stop  moving floor" */
0, // not yet
/* ldt  90 d "WR Open door"     "WR  Open  door" */
0, // not yet
/* ldt  91 F "WR Floor up LIC"  "WR  Raise floor to LIC" */
0, // not yet
/* ldt  92 F "WR Floor up 24"   "WR  Raise floor by 24" */
0, // not yet
/* ldt  93 F "WR F. up 24 TXP"  "WR  Raise floor by 24 (TXP)" */
0, // not yet
/* ldt  94 F "WR F. up LIC-8"   "WR  Raise floor to LIC - 8, crush" */
0, // not yet
/* ldt  95 F "WR F. up nhEF TX" "WR  Raise floor to nhEF (TX)" */
0, // not yet
/* ldt  96 F "WR Floor up SLT"  "WR  Raise floor by ShortestLowerTexture" */
0, // not yet
/* ldt  97 t "WR Teleport"      "WR  Teleport to another sector" */
0, // not yet
/* ldt  98 f "WR F. DN HEF+8"   "WR  Lower turbo floor to HEF + 8" */
0, // not yet
/* ldt  99 b "SR OPEN blu door" "SR  Open  turbo door, blue key [v1.6]" */
LDF_USE | LDF_BLUEKEY | LDF_RETRIG | 1,
/* ldt 100 s "W1 RaiseStairs16" "W1  Raise stairs (step=16), crush [v1.6]" */
0, // not yet
/* ldt 101 F "S1 Floor up LIC"  "S1  Raise floor to LIC" */
0, // not yet
/* ldt 102 f "S1 Floor dn HEF"  "S1  Lower floor to HEF" */
0, // not yet
/* ldt 103 d "S1 Open door (O)" "S1  Open  door (stays open)" */
LDF_USE | 2,
/* ldt 104 L "W1 Light to LE"   "W1  Light level goes to LE" */
0, // not yet
/* ldt 105 D "WR OPEN door"     "WR  Open  turbo door [v1.6]" */
0, // not yet
/* ldt 106 D "WR OPEN door (O)" "WR  Open  turbo door (stays open) [v1.6]" */
0, // not yet
/* ldt 107 D "WR CLOSE door"    "WR  Close turbo door [v1.6]" */
0, // not yet
/* ldt 108 D "W1 OPEN door"     "W1  Open  turbo door [v1.6]" */
0, // not yet
/* ldt 109 D "W1 OPEN door (O)" "W1  Open  turbo door (stays open) [v1.6]" */
0, // not yet
/* ldt 110 D "W1 CLOSE door"    "W1  Close turbo door [v1.6]" */
0, // not yet
/* ldt 111 D "S1 OPEN door"     "S1  Open  turbo door [v1.6]" */
0, // not yet
/* ldt 112 D "S1 OPEN door (O)" "S1  Open  turbo door (stays open) [v1.6]" */
0, // not yet
/* ldt 113 D "S1 CLOSE door"    "S1  Close turbo door [v1.6]" */
0, // not yet
/* ldt 114 D "SR OPEN door"     "SR  Open  turbo door [v1.6]" */
0, // not yet
/* ldt 115 D "SR OPEN door (O)" "SR  Open  turbo door (stays open) [v1.6]" */
0, // not yet
/* ldt 116 D "SR CLOSE door"    "SR  Close turbo door [v1.6]" */
0, // not yet
/* ldt 117 D "DR OPEN door"     "DR  Open  turbo door [v1.6]" */
0, // not yet
/* ldt 118 D "D1 OPEN door (O)" "D1  Open  turbo door (stays open) [v1.6]" */
0, // not yet
/* ldt 119 F "W1 Floor up nhEF" "W1  Raise floor to nhEF [v1.6]" */
0, // not yet
/* ldt 120 l "WR LOWER lift"    "WR  Lower turbo lift [v1.6]" */
0, // not yet
/* ldt 121 l "W1 LOWER lift"    "W1  Lower turbo lift [v1.6]" */
0, // not yet
/* ldt 122 l "S1 LOWER lift"    "S1  Lower turbo lift [v1.6]" */
0, // not yet
/* ldt 123 l "SR LOWER lift"    "SR  Lower turbo lift [v1.6]" */
0, // not yet
/* ldt 124 e "W- Secret level"  "W-  End level, go to secret level [v1.6]" */
0, // not yet
/* ldt 125 t "W1 Teleport mons" "W1  Teleport monsters only [v1.6]" */
0, // not yet
/* ldt 126 t "WR Teleport mons" "WR  Teleport monsters only [v1.6]" */
0, // not yet
/* ldt 127 s "S1 RaiseStairs16" "S1  Raise stairs (step=16), crush [v1.6]" */
0, // not yet
/* ldt 128 F "WR Floor up nhEF" "WR  Raise floor to nhEF [v1.6]" */
0, // not yet
/* ldt 129 F "WR Floor UP nhEF" "WR  Raise turbo floor to nhEF [v1.6]" */
0, // not yet
/* ldt 130 F "W1 Floor UP nhEF" "W1  Raise turbo floor to nhEF [v1.6]" */
0, // not yet
/* ldt 131 F "S1 Floor UP nhEF" "S1  Raise turbo floor to nhEF [v1.6]" */
0, // not yet
/* ldt 132 F "SR Floor UP nhEF" "SR  Raise turbo floor to nhEF [v1.6]" */
0, // not yet
/* ldt 133 b "S1 OPEN blu door" "S1  Open  turbo door, blue key [v1.6]" */
0, // not yet
/* ldt 134 r "SR OPEN red door" "SR  Open  turbo door, red key [v1.6]" */
0, // not yet
/* ldt 135 r "S1 OPEN red door" "S1  Open  turbo door, red key [v1.6]" */
0, // not yet
/* ldt 136 y "SR OPEN yel door" "SR  Open  turbo door, yellow key [v1.6]" */
0, // not yet
/* ldt 137 y "S1 OPEN yel door" "S1  Open  turbo door, yellow key [v1.6]" */
0, // not yet
/* ldt 138 L "SR Light to 255"  "SR  Light level goes to 255 [v1.6]" */
0, // not yet
/* ldt 139 L "SR Light to 0"    "SR  Light level goes to 0 [v1.6]" */
0, // not yet
/* ldt 140 F "S1 Floor up 512"  "S1  Raise floor by 512, medium speed [v1.6]" */
0, // not yet
/* ldt 141 C "W1& Crush SS sil" "W1& Start slow crushing, slow hurt, silent [v1.6]" */
0, // not yet
};

/*
# rest of these are Boom, XDoom, EDGE, MBF, etc.
# May or may not support at some point.
## ldt 142 F "W1 Floor up 512"  "W1  Raise floor by 512 [Boom]"
## ldt 143 l "W1& F. up 24 TX"  "W1& Raise floor by 24 (TX) [Boom]"
## ldt 144 l "W1& F. up 32 TX"  "W1& Raise floor by 32 (TX) [Boom]"
## ldt 145 c "W1 Ceil dn floor" "W1  Lower ceiling to floor [Boom]"
## ldt 146 x "W1 Donut"         "W1  Lower floor, raise NE floor (NXP) [Boom]"
## ldt 147 F "WR Floor up 512"  "WR  Raise floor by 512 [Boom]"
## ldt 148 l "WR& F. up 24 TX"  "WR& Raise floor by 24 (TX) [Boom]"
## ldt 149 l "WR& F. up 32 TX"  "WR& Raise floor by 32 (TX) [Boom]"
## ldt 150 C "WR& Crush SS sil" "WR& Start slow crushing, silent [Boom]"
## ldt 151 c "WR Ceil up HEC"   "WR  Raise ceiling to HEC [Boom]"
## ldt 152 c "WR Ceil dn floor" "WR  Lower ceiling to floor [Boom]"
## ldt 153 x "W1 Floor -- TXP"  "W1  Floor transfer (TXP) [Boom]"
## ldt 154 x "WR Floor -- TXP"  "WR  Floor transfer (TXP) [Boom]"
## ldt 155 x "WR Donut"         "WR  Lower floor, raise NE floor (NXP) [Boom]"
## ldt 156 L "WR Start blink"   "WR  Start blinking lights [Boom]"
## ldt 157 L "WR Light to LE"   "WR  Light level goes to LE [Boom]"
## ldt 158 F "S1 Floor up SLT"  "S1  Raise floor by ShortestLowerTex [Boom]"
## ldt 159 f "S1 F. dn LEF NX"  "S1  Lower floor to LEF (NXP) [Boom]"
## ldt 160 F "S1 F. up 24 TXP"  "S1  Raise floor by 24 (TXP) [Boom]"
## ldt 161 F "S1 Floor up 24"   "S1  Raise floor by 24 [Boom]"
## ldt 162 m "S1 Start moving"  "S1  Start moving floor [Boom]"
## ldt 163 m "S1 Stop moving f" "S1  Stop  moving floor [Boom]"
## ldt 164 C "S1 Crush FF"      "S1  Start fast crushing [Boom]"
## ldt 165 C "S1& Crush SS sil" "S1& Start slow crushing, silent [Boom]"
## ldt 166 c "S1 Ceil up HEC"   "S1  Raise ceiling to HEC [Boom]"
## ldt 167 c "S1 Ceil dn flr+8" "S1  Lower ceiling to floor + 8 [Boom]"
## ldt 168 C "S1& Stop crush"   "S1& Stop  crushing [Boom]"
## ldt 169 L "S1 Light to HE"   "S1  Light level goes to HE [Boom]"
## ldt 170 L "S1 Light to 0"    "S1  Light level goes to 0 [Boom]"
## ldt 171 L "S1 Light to 255"  "S1  Light level goes to 255 [Boom]"
## ldt 172 L "S1 Start blink"   "S1  Start blinking lights [Boom]"
## ldt 173 L "S1 Light to LE"   "S1  Light level goes to LE [Boom]"
## ldt 174 t "S1 Teleport"      "S1  Teleport to another sector [Boom]"
## ldt 175 d "S1 Close for 30s" "S1  Close door for 30 seconds [Boom]"
## ldt 176 F "SR Floor up SLT"  "SR  Raise floor by ShortestLowerTex [Boom]"
## ldt 177 f "SR F. dn LEF NX"  "SR  Lower floor to LEF (NXP) [Boom]"
## ldt 178 F "SR Floor up 512"  "SR  Raise floor by 512 [Boom]"
## ldt 179 F "SR F. up 24 TXP"  "SR  Raise floor by 24 (TXP) [Boom]"
## ldt 180 F "SR Floor up 24"   "SR  Raise floor by 24 [Boom]"
## ldt 181 m "SR Start moving"  "SR  Start moving floor [Boom]"
## ldt 182 m "SR Stop moving f" "SR  Stop  moving floor [Boom]"
## ldt 183 C "SR Crush FF"      "SR  Start fast crushing [Boom]"
## ldt 184 C "SR& Crush SS"     "SR& Start slow crushing [Boom]"
## ldt 185 C "SR& Crush SS sil" "SR& Start slow crushing, silent [Boom]"
## ldt 186 c "SR Ceil up HEC"   "SR  Raise ceiling to HEC [Boom]"
## ldt 187 c "SR Ceil dn flr+8" "SR  Lower ceiling to floor + 8 [Boom]"
## ldt 188 C "SR& Stop crush"   "SR& Stop  crushing [Boom]"
## ldt 189 x "S1 Floor -- TXP"  "S1  Floor transfer (TXP) [Boom]"
## ldt 190 x "SR Floor -- TXP"  "SR  Floor transfer (TXP) [Boom]"
## ldt 191 x "SR Donut"         "SR  Lower floor, raise NE floor (NXP) [Boom]"
## ldt 192 L "SR Light to HE"   "SR  Light level goes to HE [Boom]"
## ldt 193 L "SR Start blink"   "SR  Start blinking lights [Boom]"
## ldt 194 L "SR Light to LE"   "SR  Light level goes to LE [Boom]"
## ldt 195 t "SR Teleport"      "SR  Teleport to another sector [Boom]"
## ldt 196 d "SR Close for 30s" "SR  Close door for 30 seconds [Boom]"
## ldt 197 e "G- End level"     "G-  End level, go to next level [Boom]"
## ldt 198 e "G- End level"     "G-  End level, go to secret level [Boom]"
## ldt 199 c "W1 Ceil dn LEC"   "W1  Lower ceiling to LEC [Boom]"
## ldt 200 c "W1 Ceil dn HEF"   "W1  Lower ceiling to HEF [Boom]"
## ldt 201 c "WR Ceil dn LEC"   "WR  Lower ceiling to LEC [Boom]"
## ldt 202 c "WR Ceil dn HEF"   "WR  Lower ceiling to HEF [Boom]"
## ldt 203 c "S1 Ceil dn LEC"   "S1  Lower ceiling to LEC [Boom]"
## ldt 204 c "S1 Ceil dn HEF"   "S1  Lower ceiling to HEF [Boom]"
## ldt 205 c "SR Ceil dn LEC"   "SR  Lower ceiling to LEC [Boom]"
## ldt 206 c "SR Ceil dn HEF"   "SR  Lower ceiling to HEF [Boom]"
## ldt 207 t "W1 Teleport pres" "W1  Teleport preserving dir [Boom]"
## ldt 208 t "WR Teleport pres" "WR  Teleport preserving dir [Boom]"
## ldt 209 t "S1 Teleport pres" "S1  Teleport preserving dir [Boom]"
## ldt 210 t "SR Teleport pres" "SR  Teleport preserving dir [Boom]"
## ldt 211 m "SR Floor toggle"  "SR  Floor toggle to ceil [Boom]"
## ldt 212 m "WR Floor toggle"  "WR  Floor toggle to ceil [Boom]"
## ldt 213 L "-- Xfer F. light" "--  Transfer floor lighting [Boom]"
## ldt 214 A "-- Scrl C. accel" "--  Scroll ceiling with accel [Boom]"
## ldt 215 A "-- Scrl F. accel" "--  Scroll floor with accel [Boom]"
## ldt 216 A "-- Push F. accel" "--  Push objects with accel [Boom]"
## ldt 217 A "-- Sc/Pu F. accl" "--  Scroll & push with accel [Boom]"
## ldt 218 A "-- Scrl wall acc" "--  Scroll wall with accel [Boom]"
## ldt 219 f "W1 F. dn nlEF"    "W1  Lower floor to nlEF [Boom]"
## ldt 220 f "WR F. dn nlEF"    "WR  Lower floor to nlEF [Boom]"
## ldt 221 f "S1 F. dn nlEF"    "S1  Lower floor to nlEF [Boom]"
## ldt 222 f "SR F. dn nlEF"    "SR  Lower floor to nlEF [Boom]"
## ldt 223 x "-- Friction"      "--  Set friction in tagged sectors [Boom]"
## ldt 224 x "-- Wind force"    "--  Set wind in tagged sectors [Boom]"
## ldt 225 x "-- Current force" "--  Set current in tagged sectors [Boom]"
## ldt 226 x "-- Point force"   "--  Set point force in sectors [Boom]"
## ldt 227 v "W1 Elevator nhEF" "W1  Raise elevator to nhEF [Boom]"
## ldt 228 v "WR Elevator nhEF" "WR  Raise elevator to nhEF [Boom]"
## ldt 229 v "S1 Elevator nhEF" "S1  Raise elevator to nhEF [Boom]"
## ldt 230 v "SR Elevator nhEF" "SR  Raise elevator to nhEF [Boom]"
## ldt 231 v "W1 Elevator nlEF" "W1  Lower elevator to nlEF [Boom]"
## ldt 232 v "WR Elevator nlEF" "WR  Lower elevator to nlEF [Boom]"
## ldt 233 v "S1 Elevator nlEF" "S1  Lower elevator to nlEF [Boom]"
## ldt 234 v "SR Elevator nlEF" "SR  Lower elevator to nlEF [Boom]"
## ldt 235 v "W1 Elevator curr" "W1  Move elevator to Current [Boom]"
## ldt 236 v "WR Elevator curr" "WR  Move elevator to Current [Boom]"
## ldt 237 v "S1 Elevator curr" "S1  Move elevator to Current [Boom]"
## ldt 238 v "SR Elevator curr" "SR  Move elevator to Current [Boom]"
## ldt 239 x "W1 Floor -- NXP"  "W1  Floor transfer (NXP) [Boom]"
## ldt 240 x "WR Floor -- NXP"  "WR  Floor transfer (NXP) [Boom]"
## ldt 241 x "S1 Floor -- NXP"  "S1  Floor transfer (NXP) [Boom]"
## ldt 242 x "-- Deep water"    "--  Deep water effect [Boom]"
## ldt 243 t "W1 Telept line"   "W1  Teleport to tagged line [Boom]"
## ldt 244 t "WR Telept line"   "WR  Teleport to tagged line [Boom]"
## ldt 245 A "-- Scrl C. disp"  "--  Scroll ceiling by displacement [Boom]"
## ldt 246 A "-- Scrl F. disp"  "--  Scroll floor by displacement [Boom]"
## ldt 247 A "-- Push F. disp"  "--  Push objects by displacement [Boom]"
## ldt 248 A "-- Sc/Pu F. disp" "--  Scroll & push by displacement [Boom]"
## ldt 249 A "-- Scrl wall dis" "--  Scroll wall by displacement [Boom]"
## ldt 250 A "-- Scroll ceil"   "--  Scroll tagged ceiling [Boom]"
## ldt 251 A "-- Scroll floor"  "--  Scroll tagged floor [Boom]"
## ldt 252 A "-- Push on floor" "--  Push objects on tagged floor [Boom]"
## ldt 253 A "-- Scroll,push f" "--  Scroll & push tagged floor [Boom]"
## ldt 254 A "-- Scrl wal with" "--  Scroll tagged wall with F/C [Boom]"
## ldt 255 A "-- Scrl wal side" "--  Scroll wall using sidedef [Boom]"
## ldt 256 s "WR Raise stairs"  "WR  Raise stairs (several sectors) [Boom]"
## ldt 257 s "WR RaiseStairs16" "WR  Raise stairs (step=16), crush [Boom]"
## ldt 258 s "SR Raise stairs"  "SR  Raise stairs (several sectors) [Boom]"
## ldt 259 s "SR RaiseStairs16" "SR  Raise stairs (step=16), crush [Boom]"
## ldt 260 A "-- Translucency"  "--  Make tagged lines translucent [Boom]"
## ldt 261 L "-- Xfer C. light" "--  Transfer ceiling lighting [Boom]"
## ldt 262 t "W1 Telept line R" "W1  Teleport to line, reverse [Boom]"
## ldt 263 t "WR Telept line R" "WR  Teleport to line, reverse [Boom]"
## ldt 264 t "W1 Tpt line mons" "W1  Teleport monsters to line [Boom]"
## ldt 265 t "WR Tpt line mons" "WR  Teleport monsters to line [Boom]"
## ldt 266 t "W1 Tpt L. mons R" "W1  Teleport monsters to line, rev [Boom]"
## ldt 267 t "WR Tpt L. mons R" "WR  Teleport monsters to line, rev [Boom]"
## ldt 268 t "W1 Teleport mons" "W1  Teleport monsters only [Boom]"
## ldt 269 t "WR Teleport mons" "WR  Teleport monsters only [Boom]"
## ldt 271 x "-- Xfer sky"      "--  Xfer straight upper to sky tex. [MBF]"
## ldt 272 x "-- Xfer mir. sky" "--  Xfer mirrored upper to sky tex. [MBF]"
## ldt 300 x "SR Sliding door"  "SR  Sliding door [XDoom]"
## ldt 320 x "-- Laser barrier" "--  Laser barrier [XDoom]"
## ldt 321 x "SR Laser off mom" "SR  Switch laser barrier off momentarily [XDoom]"
## ldt 322 x "G1 Laser off per" "G1  Switch laser barrier off permanently [XDoom]"
## ldt 330 x "WR Trigger messg" "WR  Trigger communication device message [XDoom]"
## ldt 331 x "W1 Trigger messg" "W1  Trigger communication device message [XDoom]"
## ldt 332 x "S1 Activate tele" "S1  Activate teleporter with message [XDoom]"
## ldt 333 x "S1 Deact. laser"  "S1  Deactivate laser with message [XDoom]"
## ldt 334 x "M1 Trigger messg" "M1  Trigger communication device message [XDoom]"
## ldt 350 d "W1 Silent door O" "W1  Open silent door by player (stays open) [XDoom]"
## ldt 351 d "S1 Silent door O" "S1  Open silent door by player (stays open) [XDoom]"
## ldt 352 d "M1 Silent door O" "M1  Open silent door by monster (stays open) [XDoom]"
## ldt 400 E "-- Thick EF"      "--  Thick extrafloor [EDGE]"
## ldt 401 E "-- Thick EF upr"  "--  Thick extrafloor, side upper [EDGE]"
## ldt 402 E "-- Thick EF lwr"  "--  Thick extrafloor, side lower [EDGE]"
## ldt 403 E "-- Liq EF opaque" "--  Liquid extrafloor, opaque [EDGE]"
## ldt 404 E "-- Liquid EF 20%" "--  Liquid extrafloor, 20% translucent [EDGE]"
## ldt 405 E "-- Liquid EF 40%" "--  Liquid extrafloor, 40% translucent [EDGE]"
## ldt 406 E "-- Liquid EF 60%" "--  Liquid extrafloor, 60% translucent [EDGE]"
## ldt 407 E "-- Liquid EF 80%" "--  Liquid extrafloor, 80% translucent [EDGE]"
## ldt 408 E "-- Liq EF invis"  "--  Liquid extrafloor, invisible [EDGE]"
## ldt 9000 A "-- Scroll right" "--  Scrolling wall, right [EDGE]"
## ldt 9001 A "-- Scroll up"    "--  Scrolling wall, up [EDGE]"
## ldt 9002 A "-- Scroll down"  "--  Scrolling wall, down [EDGE]"
## ldt 9003 A "-- Scroll L+U"   "--  Scrolling wall, left and up [EDGE]"
## ldt 9004 A "-- Scroll L+D"   "--  Scrolling wall, left and down [EDGE]"
## ldt 9005 A "-- Scroll R+U"   "--  Scrolling wall, right and up [EDGE]"
## ldt 9006 A "-- Scroll R+D"   "--  Scrolling wall, right and down [EDGE]"
## ldt 9097 t "WR Teleport prv" "WR  Teleport, preserving direction [EDGE]"
*/
