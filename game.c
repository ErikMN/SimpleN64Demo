/* Create DL/Display processing and game processing */
// https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/n64man.htm
#include <assert.h>
#include <stdbool.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"

static float theta;    /* The rotational angle of the model */
static float triPos_x; /* The display position-X */
static float triPos_y; /* The display position-Y */
static float triPos_z; /* The display position-Z */
static float roll;     /* Angle of rotation of roll (in degrees, x-axis) */
static float pitch;    /* Angle of rotation of pitch (in degrees, y-axis) */
static int model;      /* Select the model to be rendered */

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
  triPos_z = -300.0;
  theta = 0.0;
  roll = 0.0;
  pitch = 0.0;
  model = 1;
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

  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gu/guPerspective.htm
  guPerspective(&dynamicp->projection, // Pointer to the resulting 4x4 projection matrix
                perspNorm,             // Pointer to the resulting numerical value
                60.0F,                 // The angle of view in the vertical (y) direction (0 ~ 180 degrees)
                (f32)SCREEN_WD /
                    (f32)SCREEN_HT, // The aspect ratio (width/height) setting the view in the horizontal (x) direction
                10.0F,              // Distance from viewpoint to near clipping plane
                999.0F,             // Distance from viewpoint to far clipping plane
                1.0F);              // Scale for matrix elements

  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gu/guRotate.htm
  guRotate(&dynamicp->rotate, theta, 0.0F, 0.0F, 1.0F);

  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gu/guTranslate.htm
  guTranslate(&dynamicp->translate, triPos_x, triPos_y, 0.0F);

  // https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gu/guPosition.htm
  // (m, roll, pitch, yaw, scale, x-trans, y-trans, z-trans)
  guPosition(&dynamicp->position, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, triPos_z);
  guPosition(&dynamicp->roll, roll, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F);
  guPosition(&dynamicp->pitch, 0.0F, pitch, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F);

  switch (model) {
  case 1:
    /* Draw a cube */
    shadecube(dynamicp);
    break;
  case 2:
    /* Draw a square */
    shadetri(dynamicp);
  default:
    break;
  }

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

    nuDebConTextPos(0, 12, 26);
    sprintf(conbuf, "Roll=%5.1f", roll);
    nuDebConCPuts(0, conbuf);

    nuDebConTextPos(0, 12, 27);
    sprintf(conbuf, "Pitch=%5.1f", pitch);
    nuDebConCPuts(0, conbuf);

    nuDebConTextPos(0, 12, 28);
    sprintf(conbuf, "Angle=%5.1f", theta);
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
  if (contdata[0].trigger & START_BUTTON) {
    vel = -vel;
    nuDebConTextPos(0, 12, 1);
    sprintf(conbuf, "START button Push");
    nuDebConCPuts(0, conbuf);
    nuDebConDisp(NU_SC_SWAPBUFFER);
  }
  nuDebConClear(0);

  // http://ultra64.ca/files/documentation/online-manuals/functions_reference_manual_2.0i/nusys/nuDebConDisp.html
  nuDebConDisp(NU_SC_SWAPBUFFER);

  if (theta > 360.0) {
    theta -= 360.0;
  } else if (theta < 0.0) {
    theta += 360.0;
  }

  if (roll > 360.0) {
    roll -= 360.0;
  } else if (roll < 0.0) {
    roll += 360.0;
  }

  if (pitch > 360.0) {
    pitch -= 360.0;
  } else if (pitch < 0.0) {
    pitch += 360.0;
  }

  if (contdata[0].button & A_BUTTON) {
    nuDebConTextPos(0, 12, 2);
    sprintf(conbuf, "A button hold");
    nuDebConCPuts(0, conbuf);
    roll += vel;
  }

  if (contdata[0].button & B_BUTTON) {
    nuDebConTextPos(0, 12, 2);
    sprintf(conbuf, "B button hold");
    nuDebConCPuts(0, conbuf);
    pitch += vel;
  }

  if (contdata[0].button & L_TRIG) {
    nuDebConTextPos(0, 12, 2);
    sprintf(conbuf, "L button hold");
    nuDebConCPuts(0, conbuf);
    triPos_z += vel;
  }

  if (contdata[0].button & R_TRIG) {
    nuDebConTextPos(0, 12, 2);
    sprintf(conbuf, "R button hold");
    nuDebConCPuts(0, conbuf);
    triPos_z -= vel;
  }

  if (contdata[0].button & Z_TRIG) {
    nuDebConTextPos(0, 12, 2);
    sprintf(conbuf, "Z button hold");
    nuDebConCPuts(0, conbuf);
    theta -= vel;
  }

  /* Reset the postition */
  if (contdata[0].button & U_CBUTTONS) {
    nuDebConTextPos(0, 12, 1);
    sprintf(conbuf, "GAME RESET!");
    nuDebConCPuts(0, conbuf);
    initGame();
  }

  /* Switch the model */
  if (contdata[0].trigger & D_CBUTTONS) {
    if (model == 1) {
      model = 2;
    } else if (model == 2) {
      model = 1;
    }

    nuDebConTextPos(0, 12, 1);
    if (model == 1) {
      sprintf(conbuf, "CUBE");
    } else if (model == 2) {
      sprintf(conbuf, "SQUARE");
    }
    nuDebConCPuts(0, conbuf);
  }

  if (contdata[0].button & L_CBUTTONS) {
    nuDebConTextPos(0, 12, 1);
    sprintf(conbuf, "FASTER");
    nuDebConCPuts(0, conbuf);
    vel = 5;
  }

  if (contdata[0].button & R_CBUTTONS) {
    nuDebConTextPos(0, 12, 1);
    sprintf(conbuf, "SLOWER");
    nuDebConCPuts(0, conbuf);
    vel = 1;
  }
}

/* The vertex coordinate */
// clang-format off
static Vtx shade_vtx[] =  {
  { -64,  64, -5, 0, 0, 0, 0x00, 0xff, 0x00, 0xff },
  {  64,  64, -5, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
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
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->rotate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->position)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->roll)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->pitch)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

  gSPVertex(glistp++, shade_vtx, ARRAY_SIZE(shade_vtx), 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_1CYCLE);
  gSPPerspNormalize(glistp++, &perspNorm);
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
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->rotate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->position)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->roll)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->pitch)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

  // Loads into the RSP vertex buffer the vertices that will be used by the gSPXTriangle commands that generates
  // polygons. https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/gsp/gSPVertex.htm
  gSPVertex(glistp++, shade_cube_vtx, ARRAY_SIZE(shade_cube_vtx), 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_1CYCLE);

  /* Scaling of same dimension coordinates */
  gSPPerspNormalize(glistp++, &perspNorm);

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
