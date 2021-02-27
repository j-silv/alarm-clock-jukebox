/***************************************************************************/
/*	Copyright © 2004 Altera Corporation. All rights reserved.            */
/* Altera products are protected under numerous U.S. and foreign patents,  */
/* maskwork rights, copyrights and other intellectual property laws.  This */
/* reference design file, and your use thereof, *is subject to and         */
/* governed by the terms and conditions of the applicable Altera Reference */
/* Design License Agreement (either as signed by you or found at           */
/* www.altera.com).  By using this reference design file, you indicate     */
/* your acceptance of such terms and conditions between you and Altera     */
/* Corporation.  In the event that you do not agree with such terms and    */
/* conditions, you may not use the reference design file and please        */
/* promptly destroy any copies you have made. This reference design file   */
/* is being provided on an “as-is” basis and as an accommodation and       */
/* therefore all warranties, representations or guarantees of any kind     */
/* (whether express, implied or statutory) including, without limitation,  */
/* warranties of merchantability, non-infringement, or fitness for a       */
/* particular purpose, are specifically disclaimed.  By making this        */
/* reference design file available, Altera expressly does not recommend,   */
/* suggest or require that this reference design file be used in           */
/* combination with any other product not provided by Altera.              */
/***************************************************************************/

/***************************************************************************/
/* File: pwm_avalon_interface.v                                            */
/* Description: Top level module.  Instantiates pwm_task_logic and         */
/*    pwm_register_file modules and adds Avalon slave interface.           */
/***************************************************************************/ 

module pwm_avalon_interface
(	clk,
	resetn,
	avalon_chip_select,
	address,
	write,
	write_data,
	read,
	read_data,
	pwm_out
 );

//Parameter values to pass to pwm_register_file instance
parameter clock_divide_reg_init = 32'h0000_0000;
parameter duty_cycle_reg_init = 32'h0000_0000;

//Avalon_Slave_PWM Avalon I/O
input clk;		 	      //System clock - tied to all blocks
input resetn;		 	//System reset - tied to all blocks
input avalon_chip_select;	//Avalon Chip select
input [1:0]address;	      //Avalon Address bus 
input write;			//Avalon Write signal
input [31:0]write_data;		//Avalon Write data bus
input read;		            //Avalon Read signal
	
output [31:0]read_data;		//Avalon Read data bus

//Avalon_Slave_PWM Exported I/O
output pwm_out;		      //PWM output signal
	
//Avalon_Slave_PWM Interal Nodes
wire [31:0] pwm_clock_divide;  //Clock divide wire from register file to pwm task logic
wire [31:0] pwm_duty_cycle;    //Duty cycle value from register file to pwm task logic
wire 	      pwm_enable;        //PWM enable signal from register file to pwm task logic
	

//PWM Instance
pwm_task_logic task_logic
(
    .clk     	    (clk ),
    .pwm_enable       (pwm_enable),
    .resetn           (resetn),
    .clock_divide     (pwm_clock_divide),
    .duty_cycle       (pwm_duty_cycle),
    .pwm_out	    (pwm_out)
);

//Register File instance
pwm_register_file #(clock_divide_reg_init, duty_cycle_reg_init) memory_element
(	
	.clk	             (clk),
	.resetn            (resetn),
	.chip_select       (avalon_chip_select),
	.address           (address),
	.write             (write),
	.write_data        (write_data),
	.read              (read),
	.read_data         (read_data),
	.pwm_clock_divide  (pwm_clock_divide),
	.pwm_duty_cycle	 (pwm_duty_cycle),
	.pwm_enable	       (pwm_enable)
);

endmodule







