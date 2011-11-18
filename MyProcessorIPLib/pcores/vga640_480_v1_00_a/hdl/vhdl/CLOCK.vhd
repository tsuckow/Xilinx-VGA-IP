--	codingwellLib Package

library IEEE;
use IEEE.STD_LOGIC_1164.all;

--library essentialLib;
--use essentialLib.scaleable.all;

--library work;
--USE work.USEFUL.ALL;
--USE work.COUNTER.ALL;

package CLOCK is

component CLK_DIV
	Generic
	(
		counts    : integer
   );
	Port
	(
		clk_in    : in  STD_LOGIC;
		clk_out   : out STD_LOGIC
	);
end component;

function clockCalc( input: integer; output: integer ) return integer;

end CLOCK;

package body CLOCK is
	function clockCalc( input: integer; output: integer ) return integer is
	begin
		return input / output / 2;
	end function clockCalc;
end CLOCK;

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.std_logic_unsigned.all;

library work;
use work.USEFUL.ALL;
use work.COUNTER.ALL;

entity CLK_DIV is
	Generic
	(
		counts    : integer := 5
	);
	Port
	(
		clk_in    : in  STD_LOGIC := '0';
		clk_out   : out STD_LOGIC := '0'
	);
end CLK_DIV;

architecture Behavioral1 of CLK_DIV is
	signal cnt     : STD_LOGIC_VECTOR( log2_ceil(counts) downto 0 );
	signal rst     : STD_LOGIC := '0';
	signal clk_buf : std_logic := '0';
begin
	--counter: scaleUpCnt port map ( clk => clk_in, reset => rst, cnt => cnt );
		counter : n_bit_counter generic map ( n => cnt'length ) port map ( clk => clk_in, reset => rst, enable => '1', count_out => cnt );
	
		rst <= '1' WHEN (cnt = counts) ELSE '0';
		
		process begin
			wait until rising_edge(rst);
				clk_buf <= not clk_buf;
		end process;
		
		clk_out <= clk_buf;
		
end Behavioral1;
