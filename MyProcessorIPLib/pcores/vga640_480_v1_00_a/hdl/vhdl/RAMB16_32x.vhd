library IEEE;
use IEEE.STD_LOGIC_1164.all;

package MEM is

component RAMB16_8x
	Generic
	(
		count : integer
   );
	Port
	(
		we1    : in  STD_LOGIC;
		clk1   : in  STD_LOGIC;
		addr1  : in  STD_LOGIC_VECTOR(13 downto 0);
		di1    : in  STD_LOGIC_VECTOR(7 downto 0);
		do1    : out STD_LOGIC_VECTOR(7 downto 0);
		we2    : in  STD_LOGIC;
		clk2   : in  STD_LOGIC;
		addr2  : in  STD_LOGIC_VECTOR(13 downto 0);
		di2    : in  STD_LOGIC_VECTOR(7 downto 0);
		do2    : out STD_LOGIC_VECTOR(7 downto 0)
	);
end component;

end MEM;

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.std_logic_unsigned.all;

library work;
use work.USEFUL.ALL;
use work.CONVERT.ALL;

entity RAMB16_8x is
	Generic
	(
		count : integer
        );
	Port
	(
		we1    : in  STD_LOGIC;
		clk1   : in  STD_LOGIC;
		addr1  : in  STD_LOGIC_VECTOR(13 downto 0);
		di1    : in  STD_LOGIC_VECTOR(7 downto 0);
		do1    : out STD_LOGIC_VECTOR(7 downto 0);
		we2    : in  STD_LOGIC;
		clk2   : in  STD_LOGIC;
		addr2  : in  STD_LOGIC_VECTOR(13 downto 0);
		di2    : in  STD_LOGIC_VECTOR(7 downto 0);
		do2    : out STD_LOGIC_VECTOR(7 downto 0)
	);
end RAMB16_8x;

architecture Behavioral1 of RAMB16_8x is

component RAMB16_S9_S9
        port (
          DIA   : in  std_logic_vector (7 downto 0);
          DIB   : in  std_logic_vector (7 downto 0);
          DIPA  : in  std_logic_vector (0 downto 0);
          DIPB  : in  std_logic_vector (0 downto 0);
          ENA   : in  std_logic;
          ENB   : in  std_logic;
          WEA   : in  std_logic;
          WEB   : in  std_logic;
          SSRA  : in  std_logic := '0';
          SSRB  : in  std_logic := '0';
          CLKA  : in  std_logic;
          CLKB  : in  std_logic;
          ADDRA : in  std_logic_vector (10 downto 0);
          ADDRB : in  std_logic_vector (10 downto 0);
          DOA   : out std_logic_vector (7 downto 0);
          DOB   : out std_logic_vector (7 downto 0);
          DOPA  : out std_logic_vector (0 downto 0);
          DOPB  : out std_logic_vector (0 downto 0) ); 
      end component;

      type MEMS is array (0 to count-1) of std_logic_vector(7 downto 0);
      signal OA : MEMS;
      signal OB : MEMS;
begin
	BYTE_BRAM_GEN : for n in 0 to count-1 generate
		signal wea : STD_LOGIC;
		signal web : STD_LOGIC;
	begin
		wea <= active_high( (we1 = '1') and (n = goNatural( addr1(13 downto 11)) ) );
		web <= active_high( (we2 = '1') and (n = goNatural( addr2(13 downto 11)) ) );

		mem1 : RAMB16_S9_S9 port map (
		  WEA => wea, ENA => '1', CLKA => clk1,
                    ADDRA => addr1(10 downto 0), DIA => di1, DOA => OA(n), DIPA => "0", DOPA => open,
		  WEB => web, ENB => '1', CLKB => clk2,
                    ADDRB => addr2(10 downto 0), DIB => di2, DOB => OB(n), DIPB => "0", DOPB => open
		);
	end generate BYTE_BRAM_GEN;

	do1 <= OA( goNatural( addr1(13 downto 11) ) );
	do2 <= OB( goNatural( addr2(13 downto 11) ) );
		
end Behavioral1;
