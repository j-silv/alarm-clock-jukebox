# TCL File Generated by Component Editor 18.1
# Sat Feb 27 20:53:35 CET 2021
# DO NOT MODIFY


# 
# pwm "pwm" v1.0
#  2021.02.27.20:53:35
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module pwm
# 
set_module_property DESCRIPTION ""
set_module_property NAME pwm
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME pwm
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL pwm_avalon_interface
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file pwm_avalon_interface.v VERILOG PATH pwm/pwm_hw/pwm_avalon_interface.v TOP_LEVEL_FILE
add_fileset_file pwm_register_file.v VERILOG PATH pwm/pwm_hw/pwm_register_file.v
add_fileset_file pwm_task_logic.v VERILOG PATH pwm/pwm_hw/pwm_task_logic.v
add_fileset_file altera_avalon_pwm_regs.h OTHER PATH pwm/pwm_sw/inc/altera_avalon_pwm_regs.h
add_fileset_file altera_avalon_pwm_routines.h OTHER PATH pwm/pwm_sw/HAL/inc/altera_avalon_pwm_routines.h
add_fileset_file altera_avalon_pwm_routines.c OTHER PATH pwm/pwm_sw/HAL/src/altera_avalon_pwm_routines.c


# 
# parameters
# 
add_parameter clock_divide_reg_init STD_LOGIC_VECTOR 0
set_parameter_property clock_divide_reg_init DEFAULT_VALUE 0
set_parameter_property clock_divide_reg_init DISPLAY_NAME clock_divide_reg_init
set_parameter_property clock_divide_reg_init WIDTH 34
set_parameter_property clock_divide_reg_init TYPE STD_LOGIC_VECTOR
set_parameter_property clock_divide_reg_init UNITS None
set_parameter_property clock_divide_reg_init ALLOWED_RANGES 0:17179869183
set_parameter_property clock_divide_reg_init HDL_PARAMETER true
add_parameter duty_cycle_reg_init STD_LOGIC_VECTOR 0
set_parameter_property duty_cycle_reg_init DEFAULT_VALUE 0
set_parameter_property duty_cycle_reg_init DISPLAY_NAME duty_cycle_reg_init
set_parameter_property duty_cycle_reg_init WIDTH 34
set_parameter_property duty_cycle_reg_init TYPE STD_LOGIC_VECTOR
set_parameter_property duty_cycle_reg_init UNITS None
set_parameter_property duty_cycle_reg_init ALLOWED_RANGES 0:17179869183
set_parameter_property duty_cycle_reg_init HDL_PARAMETER true


# 
# display items
# 


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock CMSIS_SVD_VARIABLES ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clk clk Input 1


# 
# connection point pwm_out
# 
add_interface pwm_out conduit end
set_interface_property pwm_out associatedClock clock
set_interface_property pwm_out associatedReset ""
set_interface_property pwm_out ENABLED true
set_interface_property pwm_out EXPORT_OF ""
set_interface_property pwm_out PORT_NAME_MAP ""
set_interface_property pwm_out CMSIS_SVD_VARIABLES ""
set_interface_property pwm_out SVD_ADDRESS_GROUP ""

add_interface_port pwm_out pwm_out export Output 1


# 
# connection point resetn
# 
add_interface resetn reset end
set_interface_property resetn associatedClock clock
set_interface_property resetn synchronousEdges DEASSERT
set_interface_property resetn ENABLED true
set_interface_property resetn EXPORT_OF ""
set_interface_property resetn PORT_NAME_MAP ""
set_interface_property resetn CMSIS_SVD_VARIABLES ""
set_interface_property resetn SVD_ADDRESS_GROUP ""

add_interface_port resetn resetn reset_n Input 1


# 
# connection point control_slave
# 
add_interface control_slave avalon end
set_interface_property control_slave addressUnits WORDS
set_interface_property control_slave associatedClock clock
set_interface_property control_slave associatedReset resetn
set_interface_property control_slave bitsPerSymbol 8
set_interface_property control_slave burstOnBurstBoundariesOnly false
set_interface_property control_slave burstcountUnits WORDS
set_interface_property control_slave explicitAddressSpan 0
set_interface_property control_slave holdTime 0
set_interface_property control_slave linewrapBursts false
set_interface_property control_slave maximumPendingReadTransactions 0
set_interface_property control_slave maximumPendingWriteTransactions 0
set_interface_property control_slave readLatency 0
set_interface_property control_slave readWaitStates 0
set_interface_property control_slave readWaitTime 0
set_interface_property control_slave setupTime 0
set_interface_property control_slave timingUnits Cycles
set_interface_property control_slave writeWaitTime 0
set_interface_property control_slave ENABLED true
set_interface_property control_slave EXPORT_OF ""
set_interface_property control_slave PORT_NAME_MAP ""
set_interface_property control_slave CMSIS_SVD_VARIABLES ""
set_interface_property control_slave SVD_ADDRESS_GROUP ""

add_interface_port control_slave avalon_chip_select chipselect Input 1
add_interface_port control_slave address address Input 2
add_interface_port control_slave write write Input 1
add_interface_port control_slave write_data writedata Input 32
add_interface_port control_slave read read Input 1
add_interface_port control_slave read_data readdata Output 32
set_interface_assignment control_slave embeddedsw.configuration.isFlash 0
set_interface_assignment control_slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment control_slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment control_slave embeddedsw.configuration.isPrintableDevice 0
