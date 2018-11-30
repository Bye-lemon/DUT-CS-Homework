library verilog;
use verilog.vl_types.all;
entity CNT10_vlg_check_tst is
    port(
        Q               : in     vl_logic_vector(23 downto 0);
        sampler_rx      : in     vl_logic
    );
end CNT10_vlg_check_tst;
