#include <ultra64.h>
#include "static.h"

/*
 * Remember, viewport structures have 2 bits of fraction in them.
 */
static Vp vp = {
  SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* scale */
  SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* translate */
};

/* initialize the RSP state: */
Gfx rspinit_dl[] = {
  gsSPViewport(&vp),
  gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                        G_TEXTURE_GEN_LINEAR | G_LOD),
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
  gsSPEndDisplayList(),
};

/*
 * clear the z (depth) frame buffer
 */
Gfx clearzbuffer_dl[] = {
  gsDPSetDepthImage(OS_K0_TO_PHYSICAL(zbuffer)),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, OS_K0_TO_PHYSICAL(zbuffer)),
  gsDPSetFillColor(GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)),
  gsDPFillRectangle(0, 0, SCREEN_WD - 1, SCREEN_HT - 1),
  gsSPEndDisplayList(),
};

/* initialize the RDP state: */
Gfx rdpinit_dl[] = {
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPPipelineMode(G_PM_1PRIMITIVE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
  gsDPSetTextureLOD(G_TL_TILE),
  gsDPSetTextureLUT(G_TT_NONE),
  gsDPSetTextureDetail(G_TD_CLAMP),
  gsDPSetTexturePersp(G_TP_PERSP),
  gsDPSetTextureFilter(G_TF_BILERP),
  gsDPSetTextureConvert(G_TC_FILT),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetCombineKey(G_CK_NONE),
  gsDPSetAlphaCompare(G_AC_NONE),
  gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
  gsDPSetColorDither(G_CD_DISABLE),
  gsDPPipeSync(),
  gsSPEndDisplayList(),
};

// clear the color frame buffer:
Gfx clearcfb_dl[] = {
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, rsp_cfb),

  gsDPSetFillColor(GPACK_RGBA5551(64, 64, 64, 1) << 16 | GPACK_RGBA5551(64, 64, 64, 1)),
  gsDPFillRectangle(0, 0, SCREEN_WD - 1, SCREEN_HT - 1),
  gsDPPipeSync(),

  // background color:
  gsDPSetFillColor(GPACK_RGBA5551(64, 64, 64, 1) << 16 | GPACK_RGBA5551(64, 64, 64, 1)), // grey

  // gsDPFillRectangle(20, 20, SCREEN_WD-20, SCREEN_HT-20),
  gsDPFillRectangle(0, 0, SCREEN_WD, SCREEN_HT),

  gsSPEndDisplayList(),
};

/******************************************************************************/

/*
 * This group of vertices, and accompanying display list, demonstrate
 * simple Gouraud triangles:
 */
// clang-format off
static Vtx shade_tri_vtx[] = {
  { -64,  64, -5, 0, 0, 0, 0x00, 0xff, 0x00, 0xff },
  {  64,  64, -5, 0, 0, 0, 0x00, 0x00, 0x00, 0xff },
  {  64, -64, -5, 0, 0, 0, 0x00, 0x00, 0xff, 0xff },
  { -64, -64, -5, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
};
// clang-format on

Gfx shadetri_simple_dl[] = {
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.projection)), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.modeling)), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.rotate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH),
  /*
   * Setup display modes antialiased in 1 cycle
   */
  gsDPPipeSync(),
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
  gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
  gsSPVertex(&(shade_tri_vtx[0]), 4, 0),
  gsSP1Triangle(0, 1, 2, 0),
  gsSP1Triangle(0, 2, 3, 0),
  gsSPEndDisplayList(),
};

/******************************************************************************/

// The Vtx structure is as follows:

// typedef struct {
//   short ob[3]; /* x, y, z (signed 16-bit integer) */
//   unsigned short flag; /* Currently has no meaning */
//   short tc[2]; /* Texture coordinates (s10.5) */
//   unsigned char	cn[4]; /* Color & alpha (0~255, unsigned 8-bit) */
// } Vtx_t;

/* Cube dimensions */
const short x = 50;
const short y = 50;
const short z1 = 0;
const short z2 = 100;
const unsigned short f = 0;
const unsigned short tcx = 0;
const unsigned short tcy = 0;
const unsigned char alpha1 = 0xff;

// The triangle surface flags
const s32 f0 = 0;
const s32 f1 = 0;

/*
 *  A(-x,y)        B(x,y)
 *  |--------------|
 *  |              |
 *  |              |
 *  |              |
 *  |              |
 *  |--------------|
 *  D(-x,-y)       C(x,-y)
 */

// x,y,z, flag, tc,tc, r,g,b, alpha
// clang-format off
static Vtx shade_cube_vtx[] = {
  // Front face:
  { -x,  y, z1, f, tcx, tcy, 0x00, 0xff, 0x00, alpha1 }, // 0 A1 (-x,  y,  z1)
  {  x,  y, z1, f, tcx, tcy, 0xff, 0x00, 0x00, alpha1 }, // 1 B1 ( x,  y,  z1)
  {  x, -y, z1, f, tcx, tcy, 0x00, 0x00, 0xff, alpha1 }, // 2 C1 ( x, -y,  z1)
  { -x, -y, z1, f, tcx, tcy, 0xff, 0x00, 0x00, alpha1 }, // 3 D1 (-x, -y,  z1)
  // Back face:
  { -x,  y, z2, f, tcx, tcy, 0x00, 0xff, 0x00, alpha1 }, // 4 A2 (-x,  y,  z2)
  {  x,  y, z2, f, tcx, tcy, 0xff, 0x00, 0x00, alpha1 }, // 5 B2 ( x,  y,  z2)
  {  x, -y, z2, f, tcx, tcy, 0x00, 0x00, 0xff, alpha1 }, // 6 C2 ( x, -y,  z2)
  { -x, -y, z2, f, tcx, tcy, 0xff, 0x00, 0x00, alpha1 }, // 7 D2 (-x, -y,  z2)
};
// clang-format on

// shaded triangle display list
Gfx shade_cube_dl[] = {
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.projection)), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.modeling)), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.rotate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH),

  // Setup display modes antialiased in 1 cycle
  gsDPPipeSync(),
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
  gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),

  gsSPVertex(shade_cube_vtx, 8, 0),

  // Front
  gsSP2Triangles(0, 1, 2, f0, 0, 3, 2, f1), // A1, B1, C1 + A1, D1, C1
  // Back
  gsSP2Triangles(4, 5, 6, f0, 4, 7, 6, f1), // A2, B2, C2 + A2, D2, C2

  // Side1 (left)
  gsSP2Triangles(0, 4, 7, f0, 0, 3, 7, f1), // A1, A2, D2 + A1, D1, D2
  // Side2 (right)
  gsSP2Triangles(1, 5, 6, f0, 1, 2, 6, f1), // B1, B2, C2 + B1, C1, C2

  // Top
  gsSP2Triangles(4, 5, 1, f0, 4, 0, 1, f1), // A2, B2, B1 + A2, A1, B1
  // Bottom
  gsSP2Triangles(7, 6, 2, f0, 7, 3, 2, f1), // D2, C2, C1 + D2, D1, C1

  gsSPEndDisplayList(),
};

/******************************************************************************/

/*
 * This group of vertices, and accompanying display list, demonstrate
 * simple textured triangles.
 *
 * The texture coordinates are texel-space coordinates that
 * are shifted up 6 bits; 5 bits because the texture coordinates
 * are S10.5 format, and 1 more bit so we can use a texture scaling
 * of 0.5, and get exact coordinates.
 *
 * The coordinates larger than the texture resolution, along with the
 * proper mode settings, cause the texture to repeat on itself.
 */
// clang-format off
static Vtx tex_vtx[] = {
  { -64,  64, -5, 0, (0 << 6),   (0 << 6),   0xff, 0xff, 0xff, 0xff },
  {  64,  64, -5, 0, (127 << 6), (0 << 6),   0xff, 0xff, 0xff, 0xff },
  {  64, -64, -5, 0, (127 << 6), (127 << 6), 0xff, 0xff, 0xff, 0xff },
  { -64, -64, -5, 0, (0 << 6),   (127 << 6), 0xff, 0xff, 0xff, 0xff },
};
/*
static Vtx tex_vtx[] = {
  // Front:
  { -64,  64, z1, x, (  0 << 6), (  0 << 6), 0xff, 0xff, 0xff, alpha1 }, // 0 A1
  {  64,  64, z1, x, (127 << 6), (  0 << 6), 0xff, 0xff, 0xff, alpha1 }, // 1 B1
  {  64, -64, z1, x, (127 << 6), (127 << 6), 0xff, 0xff, 0xff, alpha1 }, // 2 C1
  { -64, -64, z1, x, (  0 << 6), (127 << 6), 0xff, 0xff, 0xff, alpha1 }, // 3 D1
  // Back:
  { -64,  64, z2, x, (  0 << 6), (  0 << 6), 0xff, 0xff, 0xff, alpha1 }, // 4 A2
  {  64,  64, z2, x, (127 << 6), (  0 << 6), 0xff, 0xff, 0xff, alpha1 }, // 5 B2
  {  64, -64, z2, x, (127 << 6), (127 << 6), 0xff, 0xff, 0xff, alpha1 }, // 6 C2
  { -64, -64, z2, x, (  0 << 6), (127 << 6), 0xff, 0xff, 0xff, alpha1 }, // 7 D2
};
*/
// clang-format on

#include "brick.h" // a 32x32 RGBA16 texture

// textured triangle display list
Gfx textri_dl[] = {
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.projection)), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.modeling)), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
  gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.rotate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH),
  gsDPPipeSync(),
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
  gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH),
  /*
   * The texture scaling parameters are .16 format. In order to
   * get an exact texture scale of 1.0, we scale above by 2.0, and
   * scale down here by 0.5
   */
  gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
  gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
  gsDPSetTextureFilter(G_TF_BILERP),
  gsDPLoadTextureBlock(brick,
                       G_IM_FMT_RGBA,
                       G_IM_SIZ_16b,
                       32,
                       32,
                       0,
                       G_TX_WRAP | G_TX_MIRROR,
                       G_TX_WRAP | G_TX_MIRROR,
                       5,
                       5,
                       G_TX_NOLOD,
                       G_TX_NOLOD),

  gsSPVertex(&(tex_vtx[0]), 4, 0),
  // gsSPVertex(&(tex_vtx[0]), 8, 0),
  gsSP1Triangle(0, 1, 2, 0),
  gsSP1Triangle(0, 2, 3, 0),

  /*
   // Front
   gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0), // A1, B1, C1, A1 + A1, C1, D1, A1
   // Back
   gsSP2Triangles(4, 5, 6, 4, 4, 6, 7, 4), // A2, B2, C2, A2 + A2, C2, D2, A2
   // Side1 (left)
   gsSP2Triangles(0, 4, 7, 0, 0, 3, 7, 0), // A1, A2, D2, A1 + A1, D1, D2, A1
   // Side2 (right)
   gsSP2Triangles(1, 5, 6, 1, 1, 2, 6, 1), // B1, B2, C2, B1 + B1, C1, C2, B1
   // Top
   gsSP2Triangles(0, 1, 5, 0, 0, 4, 5, 0), // A1, B1, B2, A1 + A1, A2, B2, A1
   // Bottom
   gsSP2Triangles(3, 2, 6, 3, 3, 7, 6, 3), // D1, C1, C2, D1 + D1, D2, C2, D1
 */

  gsSPTexture(0, 0, 0, 0, G_OFF), /* done; turn texture off */
  gsSPEndDisplayList(),
};
