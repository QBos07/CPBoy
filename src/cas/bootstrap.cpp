#include "bootstrap.h"

#include <stdint.h>
#include <string.h>
#include <sdk/os/mcs.h>
#include "cpu/cpg.h"
#include "cpu/cmt.h"
#include "cpu/dmac.h"
#include "cpu/oc_mem.h"
#include "cpu/power.h"
#include "../core/error.h"
#include "../helpers/fileio.h"

uint8_t setup_cas()
{
  // Enable DMA Controller
  POWER_MSTPCR0->DMAC = 0;
  DMAC_DMAOR->raw = 0;
  DMAC_DMAOR->DME = 1;

  // Enable Timers
  POWER_MSTPCR0->TMU = 0;
  POWER_MSTPCR0->CMT = 0;

  // Create main folder for mcs vars
  MCS_CreateFolder("CPBoy", nullptr); 

  return 0;
}

void restore_cas() 
{
  // Disable DMA Controller
  DMAC_DMAOR->DME = 0;
  POWER_MSTPCR0->DMAC = 1;

  // Disable Timers
  cmt_stop();

  POWER_MSTPCR0->CMT = 1;
  POWER_MSTPCR0->TMU = 1;
  
  // Restore clock speed
  cpg_set_pll_mul(CPG_PLL_MUL_DEFAULT);
}
