/*
 * ram.h
 *
 *  Created on: Nov 4, 2015
 *      Author: rkouere
 */

#ifndef RAM_H_
#define RAM_H_

// ram.h
#include "systemc.h"
SC_MODULE(ram) {
	sc_in<sc_int<8> > addr;
	sc_in<bool> enable;
	sc_in<bool> writte;
	sc_inout_rv<16> data;
	void read_data();
	void write_data();
	sc_lv<16> ram_data[256];
	SC_CTOR(ram) {
		SC_METHOD(read_data);
		sensitive << addr << enable << writte;
		SC_METHOD(write_data);
		sensitive << addr << enable << writte << data;
	}
};
#endif /* RAM_H_ */
