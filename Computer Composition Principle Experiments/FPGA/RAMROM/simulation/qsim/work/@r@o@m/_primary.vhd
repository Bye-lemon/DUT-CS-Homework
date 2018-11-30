library verilog;
use verilog.vl_types.all;
entity ROM is
    port(
        altera_reserved_tms: in     vl_logic;
        altera_reserved_tck: in     vl_logic;
        altera_reserved_tdi: in     vl_logic;
        altera_reserved_tdo: out    vl_logic;
        Q               : out    vl_logic_vector(23 downto 0);
        CLK             : in     vl_logic;
        ADD             : in     vl_logic_vector(7 downto 0)
    );
end ROM;
