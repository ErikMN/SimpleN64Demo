#include <ultra64.h>
#include "static.h"

/*
 * The "dram_stack" field of the RCP task structure is set to this address.
 * It is placed in its own .c, and thus its own .o, since the linker aligns
 * individual relocatables to data cache line size (16 byte) boundaries.
 *
 * This avoids the problem where the dram_stack data is accidentally
 * scribbled over during a writeback for data sharing the same line.
 */

#if __GNUC__ /* { */

/* for GNU compiler */
u64 dram_stack[SP_DRAM_STACK_SIZE64] __attribute__((aligned(16))); /* used for matrix stack */

#else /* }{ */

/* for SGI compiler */
u64 dram_stack[SP_DRAM_STACK_SIZE64]; /* used for matrix stack */

#endif /* } */
