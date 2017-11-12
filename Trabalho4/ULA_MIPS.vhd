library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ULA_MIPS is
	generic(WSIZE : natural := 32);
	port (
		opcode : in std_logic_vector(3 downto 0);
		A, B: in std_logic_vector(WSIZE-1 downto 0);
		Z: out std_logic_vector(WSIZE-1 downto 0);
		zero, ovfl: out std_logic);
end ULA_MIPS;


architecture ULA of ULA_MIPS is
	signal tmp : std_logic_vector(WSIZE-1 downto 0);
	signal a32 : std_logic_vector(WSIZE-1 downto 0);

	begin
		tmp <= std_logic_vector(signed(A) - signed(B));
		Z <= a32;
		
		proc_ula: process(A,B,a32,tmp,opcode)
		variable OVFLADD : std_logic_vector(WSIZE-1 downto 0);
		variable OVFLSUB : std_logic_vector(WSIZE-1 downto 0);
		begin
			OVFLADD := std_logic_vector(signed(A) + signed(B));
			OVFLSUB := std_logic_vector(signed(A) - signed(B));
			if ((A(31) = B(31)) and (A(31) /= OVFLADD(31)) and opcode = "0010")
				then ovfl <= '1';
			elsif ((A(31) /= B(31)) and (B(31) = OVFLSUB(31)) and opcode = "0100")
				then ovfl <= '1';
				else ovfl <= '0';
			end if;
			
			if(a32 = X"00000000")
				then zero <= '1';
				else zero <= '0';
			end if;
			
			case opcode is
				when "0000" => a32 <= A and B ; -- and
				when "0001" => a32 <= A or B; -- or
				when "0010" => a32 <= std_logic_vector(signed(A) + signed(B)); -- add
				when "0011" => a32 <= std_logic_vector(unsigned(A) + unsigned(B)); -- addu
				when "0100" => a32 <= std_logic_vector(signed(A) - signed(B)); -- sub
				when "0101" => a32 <= std_logic_vector(unsigned(A) - unsigned(B)); -- subu
				when "0110" => a32 <= (0 => tmp(WSIZE-1), others => '0'); -- slt
				when "0111" => a32 <= A nand B; -- nand
				when "1000" => a32 <= A nor B; -- nor
				when "1001" => a32 <= A xor B; -- xor
				when "1010" => a32 <= std_logic_vector(SHIFT_LEFT(unsigned(B),to_integer(unsigned(A)))); -- sll
				when "1011" => a32 <= std_logic_vector(SHIFT_RIGHT(unsigned(B),to_integer(unsigned(A)))); -- srl
				when "1100" => a32 <= std_logic_vector(SHIFT_RIGHT(signed(B),to_integer(unsigned(A)))); -- sra
				when others => a32 <= (others => '0');
			end case;
		end process;
end architecture ULA;