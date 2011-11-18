-------------------------------------------------------------------------------
--
-- Package: Convert
--
-- Includes:
-- * String Conversions
-- * Type Conversions
--
-------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

package CONVERT is

--
-- String
--
function goString( input : integer ) return string;
function goString( input : std_logic_vector ) return string;
function goHexString( input : std_logic_vector ) return string;
function goString( input : std_logic ) return string;

--
-- Natural
--
function goNatural( input : std_logic_vector ) return natural;

--
-- STD_LOGIC_VECTOR
--
function goLogicVector( arg: integer ) return std_logic_vector;
function goLogicVector( arg: integer; size: integer ) return std_logic_vector;

end CONVERT;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package body CONVERT is

--
-- String
--
function goString( input : integer ) return string is
begin
	return integer'image( input );
end;

function goString( input : std_logic_vector ) return string is

variable str : string(input'length downto 1);

begin
	for i in input'length downto 1 loop
	 case input(i-1) is
	   when '0' => str(i) := '0';
	   when '1' => str(i) := '1';
	   when 'Z' => str(i) := 'z';
	   when 'U' => str(i) := 'u';
	   when 'X' => str(i) := 'x';
	   when others => str(i) := '?';
	 end case;
	end loop;
	
	return str;
end;

function goHexString( input : std_logic_vector ) return string is

variable tmp : std_logic_vector( input'length + (input'length mod 4) downto 1 ) := input;
variable str : string(tmp'length / 4 downto 1);
constant hex : string(1 to 16) := "0123456789ABCDEF";

begin
	report goString( tmp'length ) severity failure;
	for i in tmp'length / 4 downto 1 loop
		str(i) := hex( goNatural( tmp(i*4 downto (i*4) - 3) ) + 1 );
	end loop;
	
	return str;
end;

function goString( input : std_logic ) return string is

variable vec : std_logic_vector(0 to 0);

begin
  
  vec(0) := input;
  return goString( vec );

end;

--
-- Natural
--
function goNatural( input : std_logic_vector ) return natural is
begin
	return conv_integer( input );
end;

function goLogicVector( arg: integer ) return std_logic_vector is
begin
  report "goLogicVector: Must specify bit size of result." severity Failure;
  return "";
end;

function goLogicVector( arg: integer; size: integer ) return std_logic_vector is
begin
  assert size > 0 report "goLogicVector: Must specify size greater than zero." severity Failure;
  return conv_std_logic_vector(arg,size);
end;

end;