library verilog;
use verilog.vl_types.all;
entity FIFO is
    port(
        Q               : out    vl_logic_vector(7 downto 0);
        WREN            : in     vl_logic;
        CLK             : in     vl_logic;
        CLR             : in     vl_logic;
        D               : in     vl_logic_vector(7 downto 0);
        U               : out    vl_logic_vector(7 downto 0)
    );
end FIFO;
