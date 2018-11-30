library verilog;
use verilog.vl_types.all;
entity CNT10 is
    port(
        Q               : out    vl_logic_vector(23 downto 0);
        LOCK            : in     vl_logic;
        ENB             : in     vl_logic;
        F_IN            : in     vl_logic;
        RST             : in     vl_logic
    );
end CNT10;
