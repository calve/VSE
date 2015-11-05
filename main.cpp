/*
 * main.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: rkouere
 */

#include "systemc.h"
#include "ram.h"

int sc_main(int argc, char * argv[]) {
	sc_signal<bool> clock;
	sc_signal<sc_int<8> > addr;
	sc_signal<bool> enable;
	sc_signal<bool> writte;
	sc_signal_rv<16> data;

	sc_trace_file *my_trace_file;
	my_trace_file =
			sc_create_vcd_trace_file("ram_trace");
	sc_trace(my_trace_file, data, "data");
	sc_trace(my_trace_file, addr, "addr");
	ram ram("ram");
	ram.addr(addr);
	ram.enable(enable);
	ram.writte(writte);
	ram.data(data);

	/* test writting 2 to the ram @1 */
	addr = 1;
	writte = true;
	data = 20;
	enable = true;
	sc_start();


	addr = 2;
	writte = true;
	data = 5;
	enable = true;
	sc_start();


	/* test writting 1 to the ram @1 */
	addr = 1;
	writte = false;
	sc_start();

	/* test reading the ram @10 */
	addr = 10;
	enable = true;
	writte = false;
	sc_start();

	/* test reading the ram @10 */
	addr = 2;
	enable = true;
	writte = false;
	sc_start();

	return EXIT_SUCCESS;
}

