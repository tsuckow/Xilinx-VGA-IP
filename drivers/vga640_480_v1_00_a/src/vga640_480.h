//////////////////////////////////////////////////////////////////////////////
// Filename:          /home2/thomas.suckow/CST455/edk_user_repository/MyProcessorIPLib/drivers/vga640_480_v1_00_a/src/vga640_480.h
// Version:           1.00.a
// Description:       vga640_480 Driver Header File
// Date:              Wed Nov  2 10:03:47 2011 (by Create and Import Peripheral Wizard)
//////////////////////////////////////////////////////////////////////////////

#ifndef VGA640_480_H
#define VGA640_480_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xio.h"

/************************** Constant Definitions ***************************/


/**
 * Interrupt Controller Space Offsets
 * -- INTR_DISR  : device (peripheral) interrupt status register
 * -- INTR_DIPR  : device (peripheral) interrupt pending register
 * -- INTR_DIER  : device (peripheral) interrupt enable register
 * -- INTR_DIIR  : device (peripheral) interrupt id (priority encoder) register
 * -- INTR_DGIER : device (peripheral) global interrupt enable register
 * -- INTR_ISR   : ip (user logic) interrupt status register
 * -- INTR_IER   : ip (user logic) interrupt enable register
 */
#define VGA640_480_INTR_CNTRL_SPACE_OFFSET (0x00000000)
#define VGA640_480_INTR_DISR_OFFSET (VGA640_480_INTR_CNTRL_SPACE_OFFSET + 0x00000000)
#define VGA640_480_INTR_DIPR_OFFSET (VGA640_480_INTR_CNTRL_SPACE_OFFSET + 0x00000004)
#define VGA640_480_INTR_DIER_OFFSET (VGA640_480_INTR_CNTRL_SPACE_OFFSET + 0x00000008)
#define VGA640_480_INTR_DIIR_OFFSET (VGA640_480_INTR_CNTRL_SPACE_OFFSET + 0x00000018)
#define VGA640_480_INTR_DGIER_OFFSET (VGA640_480_INTR_CNTRL_SPACE_OFFSET + 0x0000001C)
#define VGA640_480_INTR_IPISR_OFFSET (VGA640_480_INTR_CNTRL_SPACE_OFFSET + 0x00000020)
#define VGA640_480_INTR_IPIER_OFFSET (VGA640_480_INTR_CNTRL_SPACE_OFFSET + 0x00000028)

/**
 * Interrupt Controller Masks
 * -- INTR_TERR_MASK : transaction error
 * -- INTR_DPTO_MASK : data phase time-out
 * -- INTR_IPIR_MASK : ip interrupt requeset
 * -- INTR_RFDL_MASK : read packet fifo deadlock interrupt request
 * -- INTR_WFDL_MASK : write packet fifo deadlock interrupt request
 * -- INTR_IID_MASK  : interrupt id
 * -- INTR_GIE_MASK  : global interrupt enable
 * -- INTR_NOPEND    : the DIPR has no pending interrupts
 */
#define INTR_TERR_MASK (0x00000001UL)
#define INTR_DPTO_MASK (0x00000002UL)
#define INTR_IPIR_MASK (0x00000004UL)
#define INTR_RFDL_MASK (0x00000020UL)
#define INTR_WFDL_MASK (0x00000040UL)
#define INTR_IID_MASK (0x000000FFUL)
#define INTR_GIE_MASK (0x80000000UL)
#define INTR_NOPEND (0x80)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a VGA640_480 register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the VGA640_480 device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void VGA640_480_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define VGA640_480_mWriteReg(BaseAddress, RegOffset, Data) \
 	XIo_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a VGA640_480 register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the VGA640_480 device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 VGA640_480_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define VGA640_480_mReadReg(BaseAddress, RegOffset) \
 	XIo_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from VGA640_480 user logic memory (BRAM).
 *
 * @param   Address is the memory address of the VGA640_480 device.
 * @param   Data is the value written to user logic memory.
 *
 * @return  The data from the user logic memory.
 *
 * @note
 * C-style signature:
 * 	void VGA640_480_mWriteMemory(Xuint32 Address, Xuint32 Data)
 * 	Xuint32 VGA640_480_mReadMemory(Xuint32 Address)
 *
 */
#define VGA640_480_mWriteMemory(Address, Data) \
 	XIo_Out32(Address, (Xuint32)(Data))
#define VGA640_480_mReadMemory(Address) \
 	XIo_In32(Address)

/************************** Function Prototypes ****************************/


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
void VGA640_480_EnableInterrupt(void * baseaddr_p);

/**
 *
 * Example interrupt controller handler.
 *
 * @param   baseaddr_p is the base address of the VGA640_480 device.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void VGA640_480_Intr_DefaultHandler(void * baseaddr_p);

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
XStatus VGA640_480_SelfTest(void * baseaddr_p);

#endif // VGA640_480_H
