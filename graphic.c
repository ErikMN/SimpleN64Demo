/* General routine for graphics */
#include <nusys.h>
#include "graphic.h"

Gfx gfx_glist[2][GFX_GLIST_LEN];
Dynamic gfx_dynamic[2];
Gfx *glistp = NULL;
u32 gfx_gtask_no = 0;
u16 *perspNorm;

/*
  The viewport structure
  The conversion from (-1,-1,-1)-(1,1,1).  The decimal part of 2-bit.
 */
static Vp vp = {
  SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* The scale factor  */
  SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* Move  */
};

/*
  The initialization of RDP
*/
Gfx setup_rdpstate[] = {
  gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
  gsDPSetColorDither(G_CD_BAYER),
  gsSPEndDisplayList(),
};

/*
  The initialization of RSP
*/
Gfx setup_rspstate[] = {
  gsSPViewport(&vp),
  gsSPClearGeometryMode(0xFFFFFFFF),
  // gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK),
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsSPEndDisplayList(),
};

/**
 * The initialization of RSP/RDP
 */
void
gfxRCPInit(void)
{
  /* Setting the RSP segment register  */
  gSPSegment(glistp++, 0, 0x0); /* For the CPU virtual address  */

  /* Setting RSP  */
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rspstate));

  /* Setting RDP  */
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(setup_rdpstate));
}

/**
 * Address setting and clearing the frame buffer/Z-buffer
 * Using nuGfxZBuffer (the address of the Z-buffer) and nuGfxCfb_ptr
 * (the address of the frame buffer) which are global variables of NuSYSTEM.
 */
void
gfxClearCfb(void)
{
  /* Clear the Z-buffer  */
  gDPSetDepthImage(glistp++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetCycleType(glistp++, G_CYC_FILL);
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  // Clearing the Z buffer with the maximum value:
  gDPSetFillColor(glistp++, (GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)));
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  gDPPipeSync(glistp++);

  /* Clear the frame buffer  */
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, osVirtualToPhysical(nuGfxCfb_ptr));
  // Fill the color frame buffer with grey:
  gDPSetFillColor(glistp++, (GPACK_RGBA5551(64, 64, 64, 1) << 16 | GPACK_RGBA5551(64, 64, 64, 1)));

  // Gfx *gdl, s32 ulx, s32 uly, s32 lrx, s32 lry
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
  // As a general rule, the gDPPipeSync command must be inserted after a series of primitives.
  gDPPipeSync(glistp++);
}
