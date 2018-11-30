library verilog;
use verilog.vl_types.all;
entity COUNTER is
    port(
        CF_LOW          : out    vl_logic;
        Q               : out    vl_logic_vector(7 downto 0);
        CLR             : in     vl_logic;
        ENA             : in     vl_logic;
        CLK             : in     vl_logic;
        CF_HIGH         : out    vl_logic
    );
end COUNTER;
