/*
 * The "output_buff" field of the RCP task structure is set to this address.
 * It is placed in its own .c, and thus its own .o, since the linker aligns
 * individual relocatables to data cache line size (16 byte) boundaries.
 *
 * This avoids the problem where the output buffer data is accidentally
 * scribbled over during a writeback for data sharing the same line.
 */

#include <ultra64.h>
#include "static.h"

/*
 * buffers for RSP tasks:
 */

/*
 * buffers used by fifo microcode only
 */

#if __GNUC__ /* { */

/* for GNU compiler */
u64 rdp_output[RDP_OUTPUT_LEN] __attribute__((aligned(16))); /* buffer for RDP DL */

#else /* }{ */

/* for SGI compiler */
u64 rdp_output[RDP_OUTPUT_LEN]; /* buffer for RDP DL */

#endif /* } */
