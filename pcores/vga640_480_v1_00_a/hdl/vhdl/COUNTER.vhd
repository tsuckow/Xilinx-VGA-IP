-------------------------------------------------------------------------------
--
-- Package: Counters
--
-------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

package COUNTER is
	--
	-- n-bit Counter
	--
	component n_bit_counter
		generic
		(
			n: INTEGER
		);
		port
		(
			clk       : in std_logic;
			reset     : in std_logic := '0';
			enable    : in std_logic := '1';
			count_out : out std_logic_vector(n-1 downto 0)
		);
	end component;
end COUNTER;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
 
entity n_bit_counter is
	generic
	(
		n: INTEGER := 3
	); 
	port
	(
		clk       : in     std_logic := '0';
		reset     : in     std_logic := '0';
		enable    : in     std_logic := '1';
		count_out : out    std_logic_vector(n-1 downto 0) := (n-1 downto 0 => '0')
	 
	);
end n_bit_counter;
 
architecture behv of n_bit_counter is
signal count_buf : std_logic_vector(n-1 downto 0) := (n-1 downto 0 => '0');
begin
 
	process(clk, enable, reset)
	begin
		if reset = '1' then
		    count_buf <= (count_buf'range => '0');
		elsif rising_edge(clk) then
			if enable = '1' then
				count_buf <= count_buf + 1;
			end if;
		end if;
	end process;
	
	count_out <= count_buf;
 
end behv;