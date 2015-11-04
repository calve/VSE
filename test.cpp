/*
 * test.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: rkouere
 */


/*#.......................................#
  # Developer : Franklin                  #
  # Last run date : 21 - Apr - 2014       #
  # Dependencies : None                   #
  # Known issues : None                   #
  # Files/Database: None                  #
  # Revision     : V1D0                   #
  #.......................................# */

#include "systemc.h"
  SC_MODULE (compteur) {
    sc_in<bool> clock;
    sc_in<bool> reset;
    sc_in<bool> load;
    sc_in<sc_uint<8>> in;

    sc_out<sc_uint<8>> out;

    unsigned char value;

    void compte() {
    	if (load == true) {
    		value = in;
    	}
    	else if (reset == false) {
    		value = 0;
    	} else {
    		value++;
    	}
    	out = value;

    }
    SC_CTOR (compteur) {
    	SC_METHOD(compteur)
    	sensitive << clock.pos();
    }
  };

