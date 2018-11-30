library verilog;
use verilog.vl_types.all;
entity RAM is
    port(
        altera_reserved_tms: in     vl_logic;
        altera_reserved_tck: in     vl_logic;
        altera_reserved_tdi: in     vl_logic;
        altera_reserved_tdo: out    vl_logic;
        Q               : out    vl_logic_vector(7 downto 0);
        WREN            : in     vl_logic;
        CLK             : in     vl_logic;
        ADR             : in     vl_logic_vector(7 downto 0);
        DATA            : in     vl_logic_vector(7 downto 0)
    );
end RAM;
