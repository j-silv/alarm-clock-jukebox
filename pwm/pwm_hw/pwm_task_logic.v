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
/* File: pwm_task_logic.v                                                  */
/* Description: This module contains the core of the pwm functionality.    */
/*    The clock_divide and duty_cycle inputs are used in conjunction with  */
/*    a counter to determine how long the pwm output stays high and low.   */
/*    The output is 1 bit.                                                 */
/***************************************************************************/

module pwm_task_logic
(
	clk,
	pwm_enable,
	resetn, 
	clock_divide,
	duty_cycle,
	pwm_out
);

//Inputs
input clk;				//Input Clock to be divided
input [31:0] clock_divide;	//Clock Divide value
input [31:0] duty_cycle;	//Duty Cycle vale
input pwm_enable;			//Enable signal
input resetn;			//Reset

//Outputs
output pwm_out;			//PWM output

//Signal Declarations	
reg [31:0] counter;		//PWM Internal Counter
reg pwm_out;			//PWM output
	
//Start Main Code	
always @(posedge clk or negedge resetn)         //PWM Counter Process
begin
	if (~resetn)begin
		counter <= 0;
	end
	else if(pwm_enable)begin
		if (counter >= clock_divide)begin
			counter <= 0;
		end
		else begin	
			counter <= counter + 1;
		end
	end
	else begin
		counter <= counter;			
	end
end

always @(posedge clk or negedge resetn)      //PWM Comparitor
begin
	if (~resetn)begin
		pwm_out <= 0;
	end
	else if(pwm_enable)begin
		if (counter >= duty_cycle)begin
			pwm_out <= 1'b1;
		end
		else begin
			if (counter == 0)
				pwm_out <= 0;
			else
				pwm_out <= pwm_out;
			end
		end
	else begin
		pwm_out <= 1'b0;
	end
end

	
endmodule
