library verilog;
use verilog.vl_types.all;
entity CNT10_vlg_sample_tst is
    port(
        ENB             : in     vl_logic;
        F_IN            : in     vl_logic;
        LOCK            : in     vl_logic;
        RST             : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end CNT10_vlg_sample_tst;
