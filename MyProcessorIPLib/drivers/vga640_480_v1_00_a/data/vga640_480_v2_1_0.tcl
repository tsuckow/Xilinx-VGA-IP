##############################################################################
## Filename:          /home2/thomas.suckow/CST455/edk_user_repository/MyProcessorIPLib/drivers/vga640_480_v1_00_a/data/vga640_480_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Wed Nov  2 10:03:47 2011 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "vga640_480" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "C_MEM0_BASEADDR" "C_MEM0_HIGHADDR" 
}
