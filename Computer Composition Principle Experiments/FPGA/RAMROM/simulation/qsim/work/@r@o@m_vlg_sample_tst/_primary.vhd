library verilog;
use verilog.vl_types.all;
entity ROM_vlg_sample_tst is
    port(
        ADD             : in     vl_logic_vector(7 downto 0);
        CLK             : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end ROM_vlg_sample_tst;
