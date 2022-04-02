/* Main routine/Structure of game processing */
#include <nusys.h>
#include "main.h"

/* Declaration of the prototype  */
void retraceCallbackFunction(int);

/* Declaration of the external function  */
void initGame(void);
void makeDL(void);
void updateGame(void);

/* The global variable  */
NUContData contdata[1]; /* Read data of 1 controller  */
u8 contPattern;         /* The pattern connected to the controller  */

/* Main */
void
mainproc(void)
{
  /* The initialization of graphic */
  nuGfxInit();

  /* The initialization of the controller manager  */
  contPattern = nuContInit();

  /* The initialization for the "game" */
  initGame();

  /* Register call-back  */
  nuGfxFuncSet((NUGfxFunc)retraceCallbackFunction);

  /* The screen display is ON */
  nuGfxDisplayOn();

  /* Run loop */
  // while (1);
}

/**
 * The callback function pendingGfx which is passed from Nusystem as the
 * argument of the callback function is the total of RCP tasks that are
 * currently processing and waiting for the process.
 */
void
retraceCallbackFunction(int pendingGfx)
{
  /* Provide the display process if 2 or less RCP tasks are processing or
   * waiting for the process.
   */
  if (pendingGfx < 3) {
    makeDL();
  }

  /* The process of game progress */
  updateGame();
}
