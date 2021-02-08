	component qsys_system is
		port (
			clk_clk                             : in  std_logic                    := 'X';             -- clk
			ledr_external_connection_export     : out std_logic_vector(9 downto 0);                    -- export
			reset_reset_n                       : in  std_logic                    := 'X';             -- reset_n
			hour0_external_connection_export    : out std_logic_vector(6 downto 0);                    -- export
			hour1_external_connection_export    : out std_logic_vector(6 downto 0);                    -- export
			min0_external_connection_export     : out std_logic_vector(6 downto 0);                    -- export
			min1_external_connection_export     : out std_logic_vector(6 downto 0);                    -- export
			sec0_external_connection_export     : out std_logic_vector(6 downto 0);                    -- export
			sec1_external_connection_export     : out std_logic_vector(6 downto 0);                    -- export
			speaker_external_connection_export  : out std_logic;                                       -- export
			switches_external_connection_export : in  std_logic_vector(9 downto 0) := (others => 'X'); -- export
			buttons_external_connection_export  : in  std_logic_vector(1 downto 0) := (others => 'X')  -- export
		);
	end component qsys_system;

	u0 : component qsys_system
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                          clk.clk
			ledr_external_connection_export     => CONNECTED_TO_ledr_external_connection_export,     --     ledr_external_connection.export
			reset_reset_n                       => CONNECTED_TO_reset_reset_n,                       --                        reset.reset_n
			hour0_external_connection_export    => CONNECTED_TO_hour0_external_connection_export,    --    hour0_external_connection.export
			hour1_external_connection_export    => CONNECTED_TO_hour1_external_connection_export,    --    hour1_external_connection.export
			min0_external_connection_export     => CONNECTED_TO_min0_external_connection_export,     --     min0_external_connection.export
			min1_external_connection_export     => CONNECTED_TO_min1_external_connection_export,     --     min1_external_connection.export
			sec0_external_connection_export     => CONNECTED_TO_sec0_external_connection_export,     --     sec0_external_connection.export
			sec1_external_connection_export     => CONNECTED_TO_sec1_external_connection_export,     --     sec1_external_connection.export
			speaker_external_connection_export  => CONNECTED_TO_speaker_external_connection_export,  --  speaker_external_connection.export
			switches_external_connection_export => CONNECTED_TO_switches_external_connection_export, -- switches_external_connection.export
			buttons_external_connection_export  => CONNECTED_TO_buttons_external_connection_export   --  buttons_external_connection.export
		);

