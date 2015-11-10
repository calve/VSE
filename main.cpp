/*
 * main.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: rkouere
 */

#include "systemc.h"
#include "ram.h"
#include "ram2.h"
int sc_main(int argc, char* argv[])
{
Memory mem("main_memory");
sc_start();
return 0;
}
//int sc_main(int argc, char * argv[]) {
//	sc_signal<bool> clock;
//	sc_signal<sc_int<8> > addr;
//	sc_signal<bool> enable;
//	sc_signal<bool> writte;
//	sc_signal<sc_int<16> > data_in;
//	sc_signal<sc_int<16> > data_out;
//
//	sc_trace_file *my_trace_file;
//	my_trace_file =
//			sc_create_vcd_trace_file("ram_trace");
//	sc_trace(my_trace_file, data_in, "data_in");
//	sc_trace(my_trace_file, data_out, "data_out");
//	sc_trace(my_trace_file, addr, "addr");
//	ram ram("ram");
//	ram.addr_in(addr);
//	ram.enable(enable);
//	ram.writte(writte);
//	ram.data_in(data_in);
//	ram.data_out(data_out);
//
//	cout << "init ram" << endl;
//	/* test writting 2 to the ram @1 */
//	addr = 1;
//	writte = true;
//	data_in = 20;
//	enable = true;
//	sc_start();
//
//	cout << "test 1" << endl;
//	addr = 2;
//	writte = true;
//	data_in = 5;
//	enable = true;
//	sc_start();
//
//
//	/* test writting 1 to the ram @1 */
//	cout << "test 2" << endl;
//	addr = 1;
//	writte = false;
//	sc_start();
//
//	cout << "test 3" << endl;
//	/* test reading the ram @10 */
//	addr = 10;
//	enable = true;
//	writte = false;
//	sc_start();
//
//	cout << "test 4" << endl;
//	/* test reading the ram @10 */
//	addr = 2;
//	enable = true;
//	writte = false;
//	sc_start();
//
//	return EXIT_SUCCESS;
//}

