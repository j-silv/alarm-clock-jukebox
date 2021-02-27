
module qsys_system (
	buttons_external_connection_export,
	clk_clk,
	hour0_external_connection_export,
	hour1_external_connection_export,
	led_alarm_external_connection_export,
	led_status_external_connection_export,
	minute0_external_connection_export,
	minute1_external_connection_export,
	reset_reset_n,
	second0_external_connection_export,
	second1_external_connection_export,
	speaker_external_connection_export,
	switches_external_connection_export,
	led_piano_external_connection_export,
	pwm_external_connection_export);	

	input	[1:0]	buttons_external_connection_export;
	input		clk_clk;
	output	[7:0]	hour0_external_connection_export;
	output	[7:0]	hour1_external_connection_export;
	output		led_alarm_external_connection_export;
	output	[1:0]	led_status_external_connection_export;
	output	[7:0]	minute0_external_connection_export;
	output	[7:0]	minute1_external_connection_export;
	input		reset_reset_n;
	output	[7:0]	second0_external_connection_export;
	output	[7:0]	second1_external_connection_export;
	output		speaker_external_connection_export;
	input	[9:0]	switches_external_connection_export;
	output	[6:0]	led_piano_external_connection_export;
	output		pwm_external_connection_export;
endmodule
