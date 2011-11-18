--- http://www.velocityreviews.com/forums/t22799-log2-n.html

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.std_logic_unsigned.all;

package useful is
--- find minimum number of bits required to
--- represent N as an unsigned binary number
---
function log2_ceil(N: natural) return positive;
function subarray(AryIn: std_logic_vector; size: natural; num: natural) return std_logic_vector;
function patternmask(size: natural; num: natural) return std_logic_vector;

--http://www.vhdl.org/comp.lang.vhdl/FAQ1.html#reduction
function reduction_or(VecIn: std_logic_vector) return std_logic;
function reduction_and(VecIn: std_logic_vector) return std_logic;

function active_high( bool : boolean ) return std_logic;
end;

package body useful is
--- find minimum number of bits required to
--- represent N as an unsigned binary number
---
function log2_ceil(N: natural) return positive is
begin
if N < 2 then
return 1;
else
return 1 + log2_ceil(N/2);
end if;
end;

function subarray(AryIn: std_logic_vector; size: natural; num: natural) return std_logic_vector is
begin
	if ( size*(num+1)-1 > AryIn'high ) then
		ASSERT FALSE
		REPORT "SubArray: Index is higher than input vector"
		SEVERITY FAILURE;
	end if;
	
	if ( size*num < AryIn'low ) then
		ASSERT FALSE
		REPORT "SubArray: Index is lower than input vector"
		SEVERITY FAILURE;
	end if;
	
	return AryIn( size*(num+1)-1 downto size*num);
end;

function patternmask(size: natural; num: natural) return std_logic_vector is
variable mask : std_logic_vector( size-1 downto 0 );
begin
	for i in mask'range loop
		if i mod (2**num) >= (2**num)/2 then
			mask(i) := '1';
		else
			mask(i) := '0';
		end if;
	end loop;
	
	return mask;
end;

function reduction_or(VecIn: std_logic_vector) return std_logic is
begin
	if VecIn = (VecIn'range => '0') then
		return '0';
	else
		return '1';
	end if;
end;

function reduction_and(VecIn: std_logic_vector) return std_logic is
begin
	if VecIn = (VecIn'range => '1') then
		return '1';
	else
		return '0';
	end if;
end;

function active_high( bool : boolean ) return std_logic is
begin
	if bool then
		return '1';
	else
		return '0';
	end if;
end;

end;