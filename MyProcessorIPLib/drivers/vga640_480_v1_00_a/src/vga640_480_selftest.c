//////////////////////////////////////////////////////////////////////////////
// Filename:          /home2/thomas.suckow/CST455/edk_user_repository/MyProcessorIPLib/drivers/vga640_480_v1_00_a/src/vga640_480_selftest.c
// Version:           1.00.a
// Description:       Contains a diagnostic self-test function for the vga640_480 driver
// Date:              Wed Nov  2 10:03:47 2011 (by Create and Import Peripheral Wizard)
//////////////////////////////////////////////////////////////////////////////


/***************************** Include Files *******************************/

#include "vga640_480.h"

/************************** Constant Definitions ***************************/


/************************** Variable Definitions ****************************/

extern Xuint32 LocalBRAM; /* User logic local memory (BRAM) base address */

/************************** Function Definitions ***************************/

/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the VGA640_480 instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus VGA640_480_SelfTest(void * baseaddr_p)
{
  int     Index;
  Xuint32 baseaddr;
  Xuint8  Reg8Value;
  Xuint16 Reg16Value;
  Xuint32 Reg32Value;
  Xuint32 Mem32Value;

  /*
   * Check and get the device address
   */
  XASSERT_NONVOID(baseaddr_p != XNULL);
  baseaddr = (Xuint32) baseaddr_p;

  xil_printf("******************************\n\r");
  xil_printf("* User Peripheral Self Test\n\r");
  xil_printf("******************************\n\n\r");

  /*
   * Write data to user logic BRAMs and read back
   */
  xil_printf("User logic BRAM test...\n\r");
  xil_printf("   - local BRAM address is 0x%08x\n\r", LocalBRAM);
  xil_printf("   - write pattern to local BRAM and read back\n\r");
  for ( Index = 0; Index < 256; Index++ )
  {
    VGA640_480_mWriteMemory(LocalBRAM+4*Index, 0xDEADBEEF);
    Mem32Value = VGA640_480_mReadMemory(LocalBRAM+4*Index);
    if ( Mem32Value != 0xDEADBEEF )
    {
      xil_printf("   - write/read BRAM failed on address 0x%08x\n\r", LocalBRAM+4*Index);
      return XST_FAILURE;
    }
  }
  xil_printf("   - write/read BRAM passed\n\n\r");

  /*
   * Enable all possible interrupts and clear interrupt status register(s)
   */
  xil_printf("Interrupt controller test...\n\r");
  Reg32Value = VGA640_480_mReadReg(baseaddr, VGA640_480_INTR_IPISR_OFFSET);
  xil_printf("   - IP (user logic) interrupt status : 0x%08x\n\r", Reg32Value);
  xil_printf("   - clear IP (user logic) interrupt status register\n\r");
  VGA640_480_mWriteReg(baseaddr, VGA640_480_INTR_IPISR_OFFSET, Reg32Value);
  Reg32Value = VGA640_480_mReadReg(baseaddr, VGA640_480_INTR_DISR_OFFSET);
  xil_printf("   - Device (peripheral) interrupt status : 0x%08x\n\r", Reg32Value);
  xil_printf("   - clear Device (peripheral) interrupt status register\n\r");
  VGA640_480_mWriteReg(baseaddr, VGA640_480_INTR_DISR_OFFSET, Reg32Value);
  xil_printf("   - enable all possible interrupt(s)\n\r");
  VGA640_480_EnableInterrupt(baseaddr_p);
  xil_printf("   - write/read interrupt register passed\n\n\r");

  return XST_SUCCESS;
}
