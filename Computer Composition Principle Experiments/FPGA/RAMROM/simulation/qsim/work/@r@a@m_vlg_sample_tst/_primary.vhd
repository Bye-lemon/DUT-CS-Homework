library verilog;
use verilog.vl_types.all;
entity RAM_vlg_sample_tst is
    port(
        ADR             : in     vl_logic_vector(7 downto 0);
        CLK             : in     vl_logic;
        DATA            : in     vl_logic_vector(7 downto 0);
        WREN            : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end RAM_vlg_sample_tst;
