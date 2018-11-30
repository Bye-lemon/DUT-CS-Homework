library verilog;
use verilog.vl_types.all;
entity FIFO_vlg_sample_tst is
    port(
        CLK             : in     vl_logic;
        CLR             : in     vl_logic;
        D               : in     vl_logic_vector(7 downto 0);
        WREN            : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end FIFO_vlg_sample_tst;
