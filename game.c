/* Create DL/Display processing and game processing */
// https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/n64man.htm
#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"

static float theta;    /* The rotational angle of the square */
static float triPos_x; /* The display position-X */
static float triPos_y; /* The display position-Y */
static float triPos_z; /* The display position-Z */

void shadetri(Dynamic *dynamicp);
void shadecube(Dynamic *dynamicp);

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(0 [x]))
#endif

/* The initialization of the "game" */
void
initGame(void)
{
  triPos_x = 0.0;
  triPos_y = 0.0;
  triPos_z = 0.0;
  theta = 0.0;
}

/* Make the display list and activate the task */
void
makeDL(void)
{
  Dynamic *dynamicp = NULL;
  char conbuf[20] = { 0 };

  /* Specify the display list buffer */
  dynamicp = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  gfxRCPInit();

  /* Clear the frame and Z-buffer */
  gfxClearCfb();

  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gu/gu_INDEX.htm

  /* projection, modeling matrix set */
  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gu/guOrtho.htm

  guOrtho(&dynamicp->projection,    // Pointer to 4x4 projection matrix resulting from calculation
          -(float)SCREEN_WD / 2.0F, // Near plane's lower-left x coordinate
          (float)SCREEN_WD / 2.0F,  // Near plane's upper-right x coordinate
          -(float)SCREEN_HT / 2.0F, // Near plane's lower-left y coordinate
          (float)SCREEN_HT / 2.0F,  // Near plane's upper-right y coordinate
          -999.0F,                  // z-coordinate of near clipping plane
          999.0F,                   // z-coordinate of far clipping plane
          1.0F);                    // Scale for matrix elements

  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gu/guRotate.htm
  guRotate(&dynamicp->modeling, theta, 1.0F, 1.0F, 1.0F);

  // guRotate(&dynamicp->modeling, triPos_x, 1.0F, 0.0F, 0.0F);
  // guRotate(&dynamicp->modeling, triPos_y, 0.0F, 1.0F, 0.0F);

  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gu/guTranslate.htm
  guTranslate(&dynamicp->translate, triPos_x, triPos_y, triPos_z);

  /* Draw a square */
  // shadetri(dynamicp);

  /* Draw a cube */
  shadecube(dynamicp);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  /* Activate the task and switch display buffers */
  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
                 (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof(Gfx),
                 NU_GFX_UCODE_F3DEX,
                 NU_SC_NOSWAPBUFFER);

  if (contPattern & 0x1) {
    /* Change character representation positions */
    nuDebConTextPos(0, 12, 23);
    sprintf(conbuf, "triPos_x=%5.1f", triPos_x);
    nuDebConCPuts(0, conbuf);

    nuDebConTextPos(0, 12, 24);
    sprintf(conbuf, "triPos_y=%5.1f", triPos_y);
    nuDebConCPuts(0, conbuf);

    nuDebConTextPos(0, 12, 25);
    sprintf(conbuf, "triPos_z=%5.1f", triPos_z);
    nuDebConCPuts(0, conbuf);
  } else {
    nuDebConTextPos(0, 9, 24);
    nuDebConCPuts(0, "Controller1 not connected");
  }

  /* Display characters on the frame buffer */
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Switch display list buffers */
  gfx_gtask_no ^= 1;
}

/* The game progressing process */
void
updateGame(void)
{
  static float vel = 1.0;
  char conbuf[20];

  /* Data reading of controller 1 */
  nuContDataGetEx(contdata, 0);

  /* Change the display position by stick data */
  triPos_x = contdata->stick_x;
  triPos_y = contdata->stick_y;

  /* The reverse rotation by the A button */
  if (contdata[0].trigger & A_BUTTON) {
    vel = -vel;
    // NOTE: osSyncPrintf doesn't work with emulators?
    // osSyncPrintf("A button Push\n");

    // triPos_z -= 100;

    nuDebConTextPos(0, 12, 1);
    sprintf(conbuf, "A button Push");
    nuDebConCPuts(0, conbuf);
    nuDebConDisp(NU_SC_SWAPBUFFER);
  }
  nuDebConClear(0);
  // http://ultra64.ca/files/documentation/online-manuals/functions_reference_manual_2.0i/nusys/nuDebConDisp.html
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Rotate fast while pushing the B button */
  if (contdata[0].button & B_BUTTON) {
    theta += vel * 5.0;
    nuDebConTextPos(0, 12, 2);
    sprintf(conbuf, "B button hold");
    nuDebConCPuts(0, conbuf);
  } else {
    theta += vel;
  }

  if (theta > 360.0) {
    theta -= 360.0;
  } else if (theta < 0.0) {
    theta += 360.0;
  }
}

/* The vertex coordinate */
// clang-format off
static Vtx shade_vtx[] =  {
  { -64,  64, -5, 0, 0, 0, 0x00, 0xff, 0x00, 0xff },
  {  64,  64, -5, 0, 0, 0, 0x00, 0x00, 0x00, 0xff },
  {  64, -64, -5, 0, 0, 0, 0x00, 0x00, 0xff, 0xff },
  { -64, -64, -5, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
};
// clang-format on

/* Draw a square */
void
shadetri(Dynamic *dynamicp)
{
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->projection)), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->translate)), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->modeling)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

  gSPVertex(glistp++, shade_vtx, ARRAY_SIZE(shade_vtx), 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_1CYCLE);
  gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
  gSPSetGeometryMode(glistp++, G_SHADE | G_SHADING_SMOOTH);

  // The triangle surface flags
  s32 f0 = 0;
  s32 f1 = 0;

  gSP2Triangles(glistp++, 0, 1, 2, f0, 0, 2, 3, f1);
}

/* Cube dimensions */
const short x = 50;
const short y = 50;
const short z1 = 0;
const short z2 = 100;
const unsigned short f = 0;
const unsigned short tcx = 0;
const unsigned short tcy = 0;
const unsigned char alpha1 = 0xff;

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

/* The vertex coordinate */
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

/* Draw a cube */
void
shadecube(Dynamic *dynamicp)
{
  // Inserts matrix operations in the display list
  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gsp/gSPMatrix.htm
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->projection)), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->translate)), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->modeling)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

  // Loads into the RSP vertex buffer the vertices that will be used by the gSPXTriangle commands that generates
  // polygons. https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gsp/gSPVertex.htm
  gSPVertex(glistp++, shade_cube_vtx, ARRAY_SIZE(shade_cube_vtx), 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_1CYCLE);
  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gdp/gDPSetRenderMode.htm
  // (AA_: Antialiasing, RA_: Simple antialiasing (not as pretty as AA, but somewhat faster), ZB_: Z-buffering)
  gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
  gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gsp/gSPSetGeometryMode.htm
  gSPSetGeometryMode(glistp++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);

  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gsp/gSP2Triangles.htm
  // gfx *gdl, v00, v01, v02, flag0, v10, v11, v12, flag1

  // The triangle surface flags
  s32 f0 = 0;
  s32 f1 = 0;

  // Front                A1, B1, C1 + A1, D1, C1
  gSP2Triangles(glistp++, 0, 1, 2, f0, 0, 3, 2, f1);
  // Back                 A2, B2, C2 + A2, D2, C2
  gSP2Triangles(glistp++, 4, 5, 6, f0, 4, 7, 6, f1);

  // Side1 (left)         A1, A2, D2 + A1, D1, D2
  gSP2Triangles(glistp++, 0, 4, 7, f0, 0, 3, 7, f1);
  // Side2 (right)        B1, B2, C2 + B1, C1, C2
  gSP2Triangles(glistp++, 1, 5, 6, f0, 1, 2, 6, f1);

  // Top                  A2, B2, B1 + A2, A1, B1
  gSP2Triangles(glistp++, 4, 5, 1, f0, 4, 0, 1, f1);
  // Bottom               D2, C2, C1 + D2, D1, C1
  gSP2Triangles(glistp++, 7, 6, 2, f0, 7, 3, 2, f1);
}
