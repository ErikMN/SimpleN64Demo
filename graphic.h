/* A definition of outside reference for graphics etc. */
#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

/* The screen size  */
#define SCREEN_HT 240
#define SCREEN_WD 320

/* The maximum length of the display list of one task  */
#define GFX_GLIST_LEN 2048

/* The structure of the projection-matrix  */
typedef struct {
  Mtx projection;
  Mtx translate;
  Mtx rotate;
  Mtx position;
  Mtx roll;
  Mtx pitch;
} Dynamic;

/* Parameters */
extern Dynamic gfx_dynamic[];
extern Gfx *glistp;
extern Gfx gfx_glist[][GFX_GLIST_LEN];
extern u32 gfx_gtask_no;
extern u16 *perspNorm;

/* Graphics functions */
extern void gfxRCPInit(void);
extern void gfxClearCfb(void);

/* HW init functions */
extern Gfx setup_rdpstate[];
extern Gfx setup_rspstate[];

#endif /* _GRAPHIC_H_ */
