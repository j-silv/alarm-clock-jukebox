
module qsys_system (
	clk_clk,
	ledr_external_connection_export,
	reset_reset_n,
	hour0_external_connection_export,
	hour1_external_connection_export,
	min0_external_connection_export,
	min1_external_connection_export,
	sec0_external_connection_export,
	sec1_external_connection_export,
	speaker_external_connection_export,
	switches_external_connection_export,
	buttons_external_connection_export);	

	input		clk_clk;
	output	[9:0]	ledr_external_connection_export;
	input		reset_reset_n;
	output	[6:0]	hour0_external_connection_export;
	output	[6:0]	hour1_external_connection_export;
	output	[6:0]	min0_external_connection_export;
	output	[6:0]	min1_external_connection_export;
	output	[6:0]	sec0_external_connection_export;
	output	[6:0]	sec1_external_connection_export;
	output		speaker_external_connection_export;
	input	[9:0]	switches_external_connection_export;
	input	[1:0]	buttons_external_connection_export;
endmodule
