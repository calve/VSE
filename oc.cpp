/*
 * master.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: rkouere
 */

#include "master.h"
#include "systemc.h"
  SC_MODULE (master) {
	  /* Basic OCP signals */
	  sc_in<bool> Clk;
	  sc_in<sc_uint<2>> MCmd;
	  sc_in<sc_uint<8>> MAddr;
	  sc_in<sc_uint<15>> MData;
	  sc_in<bool> MDataValid;
	  sc_in<bool> MRespAccept;
	  sc_in<bool> SCmdAccept;
	  sc_in<sc_uint<15>> SData;
	  sc_in<bool> SDataAccept;
	  sc_in<bool> SResp;
	  /* Control signals */
	  sc_in<sc_uint<3>> Control;
	  sc_in<bool> MReset_n;
    SC_CTOR (master) {
     }
     void say_hello() {
     cout << "Welcome to Frank's world\n";
    }
  };





  /*
  -- Basic OCP signals
  Clk:in std_logic;
  MCmd: out std_logic_vector(2 downto 0);
  MAddr: out std_logic_vector(3 downto 0);
  MData: out std_logic_vector(15 downto 0);
  MDataValid: out std_logic;
  MRespAccept: out std_logic;
  SCmdAccept: in std_logic;
  SData: in std_logic_vector(15 downto 0);
  SDataAccept: in std_logic;
  SResp: in std_logic;
  --Control signals
  Control: out std_logic_vector(3 downto 0);
  MReset_n: out std_logic
  */
