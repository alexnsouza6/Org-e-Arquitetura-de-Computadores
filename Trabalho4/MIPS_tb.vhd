-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- ***************************************************************************
-- This file contains a Vhdl test bench template that is freely editable to   
-- suit user's needs .Comments are provided in each section to help the user  
-- fill out necessary details.                                                
-- ***************************************************************************
-- Generated on "10/26/2017 14:03:42"
                                                            
-- Vhdl Test Bench template for design  :  ULA_MIPS
-- 
-- Simulation tool : ModelSim-Altera (VHDL)
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;     
use ieee.numeric_std.all;                           

ENTITY MIPS_tb IS
END MIPS_tb;
ARCHITECTURE ULA_MIPS_arch OF MIPS_tb IS
-- constants                                                 
-- signals                                                   
SIGNAL A : STD_LOGIC_VECTOR(31 DOWNTO 0);
SIGNAL B : STD_LOGIC_VECTOR(31 DOWNTO 0);
SIGNAL opcode : STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL ovfl : STD_LOGIC;
SIGNAL Z : STD_LOGIC_VECTOR(31 DOWNTO 0);
SIGNAL zero : STD_LOGIC;
COMPONENT ULA_MIPS
	PORT (
	A : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	B : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	opcode : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
	ovfl : OUT STD_LOGIC;
	Z : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
	zero : OUT STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : ULA_MIPS
	PORT MAP (
-- list connections between master ports and signals
	A => A,
	B => B,
	opcode => opcode,
	ovfl => ovfl,
	Z => Z,
	zero => zero
	);
init : PROCESS                                               
-- variable declarations                                     
BEGIN                                                        
        -- code that executes only once
	-- testing and func
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(0,32));
	opcode <= "0000";
	wait for 10 ps;

	-- testing or func
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(0,32));
	opcode <= "0001";
	wait for 10 ps;
	
	-- testing add func for zero
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(-1,32));
	opcode <= "0010";
	wait for 10 ps;
	
	-- testing add func for negative
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(-2,32));
	opcode <= "0010";
	wait for 10 ps;
	
	-- testing add func for positive
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(0,32));
	opcode <= "0010";
	wait for 10 ps;
	
	-- testing add func for overflow
	-- generates overflow
	A <= "01111111111111111111111111111111";
	B <= "01111111111111111111111111111111";
	opcode <= "0010";
	wait for 10 ps;
	
	
	-- testing addu func for positive
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(1,32));
	opcode <= "0011";
	wait for 10 ps;

	-- testing sub func for negative
	A <= std_logic_vector(to_signed(6,32));
	B <= std_logic_vector(to_signed(8,32));
	opcode <= "0100";
	wait for 10 ps;
	
	-- testing sub func for positive
	A <= std_logic_vector(to_signed(6,32));
	B <= std_logic_vector(to_signed(4,32));
	opcode <= "0100";
	wait for 10 ps;
	
	-- testing sub func for overflow
	-- generates overflow
	A <= "01100000000000000000000000000000";
	B <= "10000000000000000000000000000000";
	opcode <= "0100";
	wait for 10 ps;
		  
	-- testing subu func for negative
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(2,32));
	opcode <= "0101";
	wait for 10 ps;
	
	-- testing subu func for positive
	A <= std_logic_vector(to_signed(2,32));
	B <= std_logic_vector(to_signed(1,32));
	opcode <= "0101";
	wait for 10 ps;
                              
										
	-- testing slt func
	A <= std_logic_vector(to_signed(4,32));
	B <= std_logic_vector(to_signed(6,32));
	opcode <= "0110";
	wait for 10 ps;
	
	-- testing nand func
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(0,32));
	opcode <= "0111";
	wait for 10 ps;
	
	-- testing nor func
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(0,32));
	opcode <= "1000";
	wait for 10 ps;
	
	-- testing xor func
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(0,32));
	opcode <= "1001";
	wait for 10 ps;
	
	-- testing sll func
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(4,32));
	opcode <= "1010";
	wait for 10 ps;
	
	-- testing srl func
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(4,32));
	opcode <= "1011";
	wait for 10 ps;
	
	-- testing sra func
	A <= std_logic_vector(to_signed(1,32));
	B <= std_logic_vector(to_signed(-3,32));
	opcode <= "1100";
	wait for 10 ps;
	
END PROCESS init;                                           
                                       
END ULA_MIPS_arch;
