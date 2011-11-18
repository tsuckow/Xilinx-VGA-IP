//////////////////////////////////////////////////////////////////////////////
// Filename:          /home2/thomas.suckow/CST455/edk_user_repository/MyProcessorIPLib/drivers/vga640_480_v1_00_a/src/vga640_480.c
// Version:           1.00.a
// Description:       vga640_480 Driver Source File
// Date:              Wed Nov  2 10:03:47 2011 (by Create and Import Peripheral Wizard)
//////////////////////////////////////////////////////////////////////////////


/***************************** Include Files *******************************/

#include "vga640_480.h"

/************************** Function Definitions ***************************/

/**
 *
 * Enable all possible interrupts from VGA640_480 device.
 *
 * @param   baseaddr_p is the base address of the VGA640_480 device.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void VGA640_480_EnableInterrupt(void * baseaddr_p)
{
  Xuint32 baseaddr;
  baseaddr = (Xuint32) baseaddr_p;

  /*
   * Enable all interrupt source from user logic.
   */
  VGA640_480_mWriteReg(baseaddr, VGA640_480_INTR_IPIER_OFFSET, 0x00000001);

  /*
   * Enable all possible interrupt sources from device.
   */
  VGA640_480_mWriteReg(baseaddr, VGA640_480_INTR_DIER_OFFSET,
    INTR_TERR_MASK
    | INTR_DPTO_MASK
    | INTR_IPIR_MASK
    );

  /*
   * Set global interrupt enable.
   */
  VGA640_480_mWriteReg(baseaddr, VGA640_480_INTR_DGIER_OFFSET, INTR_GIE_MASK);
}

/**
 *
 * Example interrupt controller handler for VGA640_480 device.
 * This is to show example of how to toggle write back ISR to clear interrupts.
 *
 * @param   baseaddr_p is the base address of the VGA640_480 device.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void VGA640_480_Intr_DefaultHandler(void * baseaddr_p)
{
  Xuint32 baseaddr;
  Xuint32 IntrStatus;
Xuint32 IpStatus;
  baseaddr = (Xuint32) baseaddr_p;

  /*
   * Get status from Device Interrupt Status Register.
   */
  IntrStatus = VGA640_480_mReadReg(baseaddr, VGA640_480_INTR_DISR_OFFSET);

  xil_printf("Device Interrupt! DISR value : 0x%08x \n\r", IntrStatus);

  /*
   * Verify the source of the interrupt is the user logic and clear the interrupt
   * source by toggle write baca to the IP ISR register.
   */
  if ( (IntrStatus & INTR_IPIR_MASK) == INTR_IPIR_MASK )
  {
    xil_printf("User logic interrupt! \n\r");
    IpStatus = VGA640_480_mReadReg(baseaddr, VGA640_480_INTR_IPISR_OFFSET);
    VGA640_480_mWriteReg(baseaddr, VGA640_480_INTR_IPISR_OFFSET, IpStatus);
  }

}

