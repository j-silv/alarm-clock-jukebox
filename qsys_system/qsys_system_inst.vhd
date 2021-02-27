	component qsys_system is
		port (
			buttons_external_connection_export    : in  std_logic_vector(1 downto 0) := (others => 'X'); -- export
			clk_clk                               : in  std_logic                    := 'X';             -- clk
			hour0_external_connection_export      : out std_logic_vector(7 downto 0);                    -- export
			hour1_external_connection_export      : out std_logic_vector(7 downto 0);                    -- export
			led_alarm_external_connection_export  : out std_logic;                                       -- export
			led_piano_external_connection_export  : out std_logic_vector(6 downto 0);                    -- export
			led_status_external_connection_export : out std_logic_vector(1 downto 0);                    -- export
			minute0_external_connection_export    : out std_logic_vector(7 downto 0);                    -- export
			minute1_external_connection_export    : out std_logic_vector(7 downto 0);                    -- export
			pwm_external_connection_export        : out std_logic;                                       -- export
			reset_reset_n                         : in  std_logic                    := 'X';             -- reset_n
			second0_external_connection_export    : out std_logic_vector(7 downto 0);                    -- export
			second1_external_connection_export    : out std_logic_vector(7 downto 0);                    -- export
			switches_external_connection_export   : in  std_logic_vector(9 downto 0) := (others => 'X')  -- export
		);
	end component qsys_system;

	u0 : component qsys_system
		port map (
			buttons_external_connection_export    => CONNECTED_TO_buttons_external_connection_export,    --    buttons_external_connection.export
			clk_clk                               => CONNECTED_TO_clk_clk,                               --                            clk.clk
			hour0_external_connection_export      => CONNECTED_TO_hour0_external_connection_export,      --      hour0_external_connection.export
			hour1_external_connection_export      => CONNECTED_TO_hour1_external_connection_export,      --      hour1_external_connection.export
			led_alarm_external_connection_export  => CONNECTED_TO_led_alarm_external_connection_export,  --  led_alarm_external_connection.export
			led_piano_external_connection_export  => CONNECTED_TO_led_piano_external_connection_export,  --  led_piano_external_connection.export
			led_status_external_connection_export => CONNECTED_TO_led_status_external_connection_export, -- led_status_external_connection.export
			minute0_external_connection_export    => CONNECTED_TO_minute0_external_connection_export,    --    minute0_external_connection.export
			minute1_external_connection_export    => CONNECTED_TO_minute1_external_connection_export,    --    minute1_external_connection.export
			pwm_external_connection_export        => CONNECTED_TO_pwm_external_connection_export,        --        pwm_external_connection.export
			reset_reset_n                         => CONNECTED_TO_reset_reset_n,                         --                          reset.reset_n
			second0_external_connection_export    => CONNECTED_TO_second0_external_connection_export,    --    second0_external_connection.export
			second1_external_connection_export    => CONNECTED_TO_second1_external_connection_export,    --    second1_external_connection.export
			switches_external_connection_export   => CONNECTED_TO_switches_external_connection_export    --   switches_external_connection.export
		);

