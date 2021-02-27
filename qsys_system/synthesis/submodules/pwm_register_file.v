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
/* File: pwm_register_file                                                 */
/* Description: Register interface for PWM.  Contains logic for reading    */
/*    and writing to PWM registers.                                        */
/***************************************************************************/

module pwm_register_file
(	//Avalon Signals
	clk,
	resetn, 
	chip_select,
	address,
	write,
	write_data,
	read,
	read_data,

	//PWM Output Signals
	pwm_clock_divide,
	pwm_duty_cycle,
	pwm_enable
);

//Parameters
parameter clock_divide_reg_init = 32'h0000_0000;
parameter duty_cycle_reg_init   = 32'h0000_0000;

//Inputs

input clk;			      //System Clock
input resetn;			//System Reset
input chip_select;		//Avalon Chip select signal
input [1:0] address;	      //Avalon Address bus 
input write;			//Avalon Write signal
input [31:0] write_data;	//Avalon Write data bus
input read;			      //Avalon read signal
	
//Outputs
output [31:0] read_data;	  //Avalon read data bus
output [31:0] pwm_clock_divide; //PWM clock divide drive signals
output [31:0] pwm_duty_cycle;   //PWM duty cycle drive signals
output        pwm_enable;       //PWM enable drive signals

//Signal Declarations	
		
reg [31:0] clock_divide_register;	//Clock divider register
reg [31:0] duty_cycle_register;  	//Duty Cycle Register
reg        enable_register;	 	//Enable Bit	
reg [31:0] read_data;			//Read_data bus
	
//Nodes used for address decoding
wire clock_divide_reg_selected, duty_cycle_reg_selected, enable_reg_selected;
//Nodes for determining if a valid write occurred to a specific address
wire write_to_clock_divide, write_to_duty_cycle, write_to_enable;
//Nodes for determining if a valid read occurred to a specific address
wire read_to_clock_divide, read_to_duty_cycle, read_to_enable;
//Nodes used to determine if a valid access has occurred
wire valid_write, valid_read;

//Start Main Code	

//address decode
assign clock_divide_reg_selected = !address[1] & !address[0];  //address 00
assign duty_cycle_reg_selected   = !address[1] &  address[0];  //address 01
assign enable_reg_selected       =  address[1] & !address[0];  //address 10

//determine if a vaild transaction was initiated 
assign valid_write = chip_select & write;		
assign valid_read  = chip_select & read;

//determine if a write occurred to a specific address
assign write_to_clock_divide = valid_write & clock_divide_reg_selected;
assign write_to_duty_cycle   = valid_write & duty_cycle_reg_selected;
assign write_to_enable       = valid_write & enable_reg_selected;

//determine if a read occurred to a specific address
assign read_to_clock_divide = valid_read & clock_divide_reg_selected;
assign read_to_duty_cycle   = valid_read & duty_cycle_reg_selected;
assign read_to_enable       = valid_read & enable_reg_selected;

//Write to clock_divide Register
always@(posedge clk or negedge resetn)
begin
	if(~resetn)begin //Async Reset
		clock_divide_register <= clock_divide_reg_init; //32'h0000_0000;
	end
	else begin	
		if(write_to_clock_divide) begin
			clock_divide_register <= write_data; 	 
		end
		else begin
			clock_divide_register <= clock_divide_register;  
		end
		
	end
end	

//Write to duty_cycle Register
always@(posedge clk or negedge resetn)
begin
	if(~resetn)begin //Async Reset
		duty_cycle_register <= duty_cycle_reg_init; //32'h0000_0000;
	end
	else begin	
		if(write_to_duty_cycle) begin
			duty_cycle_register <= write_data; 	 
		end
		else begin
			duty_cycle_register <= duty_cycle_register;  
		end
	end
end	

//Write to enable register
always@(posedge clk or negedge resetn)
begin
	if(~resetn)begin //Async Reset
		enable_register <= 1'b0;
	end
	else begin
		if(write_to_enable)begin
			enable_register <= write_data[0];
		end
		else begin
			enable_register <= enable_register;
		end
	end
end

//Read Data Bus Mux
always@(read_to_clock_divide or read_to_duty_cycle or read_to_enable or clock_divide_register or duty_cycle_register or enable_register)
begin
	if(read_to_clock_divide) begin
		read_data = clock_divide_register;
	end
	else if(read_to_duty_cycle) begin
		read_data = duty_cycle_register;
	end
	else if(read_to_enable) begin
		read_data = {31'd0,enable_register};
	end
	else begin
		read_data = 32'h0000_0000;
	end
end

//assign register values to register file outputs to the PWM
assign pwm_clock_divide = clock_divide_register;
assign pwm_duty_cycle = duty_cycle_register;
assign pwm_enable = enable_register;

endmodule
