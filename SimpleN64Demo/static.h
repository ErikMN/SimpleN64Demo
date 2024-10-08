#define STATIC_SEGMENT 1
#define CFB_SEGMENT 2

#define SCREEN_HT 240
#define SCREEN_WD 320

/* this stack size is in bytes, and is a lot larger
 * than this program needs.
 */
#define STACKSIZE 0x2000

#define GLIST_LEN 2048
/*
 * ifdef needed because this file is included by "spec"
 */
#ifdef _LANGUAGE_C

/*
 * Layout of dynamic data.
 *
 * This structure holds the things which change per frame. It is advantageous
 * to keep dynamic data together so that we may selectively write back dirty
 * data cache lines to DRAM prior to processing by the RCP.
 *
 */
typedef struct {
  Mtx projection;
  Mtx modeling;
  Mtx rotate;
  Gfx glist[GLIST_LEN];
} Dynamic;

extern Dynamic dynamic;

/* these are the static display lists */
extern Gfx rspinit_dl[];
extern Gfx rdpinit_dl[];
extern Gfx clearcfb_dl[];
extern Gfx clearzbuffer_dl[];
extern Gfx shade_cube_dl[];
extern Gfx shadetri_simple_dl[];
extern Gfx textri_dl[];

/* RSP task data that is modified by the RSP and read the the CPU */
extern u16 zbuffer[];    /* RAM address */
extern u64 dram_stack[]; /* used for matrix stack */
extern u64 rdp_output[]; /* RSP writes back RDP data */
#define RDP_OUTPUT_LEN (4096 * 16)

/* CPU addresses for the color frame buffer */
extern u16 cfb[][SCREEN_WD * SCREEN_HT];

/* RSP address for the color frame buffer */
extern u16 rsp_cfb[];

#endif /* _LANGUAGE_C */
