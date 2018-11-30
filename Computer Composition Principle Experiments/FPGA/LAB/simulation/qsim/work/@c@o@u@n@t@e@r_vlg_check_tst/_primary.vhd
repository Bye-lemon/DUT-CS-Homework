library verilog;
use verilog.vl_types.all;
entity COUNTER_vlg_check_tst is
    port(
        CF_HIGH         : in     vl_logic;
        CF_LOW          : in     vl_logic;
        Q               : in     vl_logic_vector(7 downto 0);
        sampler_rx      : in     vl_logic
    );
end COUNTER_vlg_check_tst;
