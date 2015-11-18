/*
 * main.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: rkouere
 */

#include "systemc.h"
//#include "ram.h"
//#include "ram2.h"

#include "ram.h"
#include "cpu.h"

int sc_main(int argc, char * argv[]) {
	try {
		//Instantiate Modules
		Memory mem("main_memory");
		CPU cpu("cpu");
		//Signals
		sc_buffer<Memory::Function> sigMemFunc;
		sc_buffer<Memory::RetCode> sigMemDone;
		sc_signal<int> sigMemAddr;
		sc_signal_rv<32> sigMemData;
		// The clock that will drive the CPU and Memory
		sc_clock clk;
		// Connecting module ports with signals
		mem.Port_Func(sigMemFunc);
		mem.Port_Addr(sigMemAddr);
		mem.Port_Data(sigMemData);
		mem.Port_Done(sigMemDone);
		cpu.Port_MemFunc(sigMemFunc);
		cpu.Port_MemAddr(sigMemAddr);
		cpu.Port_MemData(sigMemData);
		cpu.Port_MemDone(sigMemDone);
		mem.Port_CLK(clk);
		cpu.Port_CLK(clk);

		cout << "Installing trace signals. Output in ram_trace.vcd " << endl;
		sc_trace_file *wf = sc_create_vcd_trace_file("ram_trace");
		sc_trace(wf, clk, "clock");
		sc_trace(wf, sigMemFunc, "function");
		sc_trace(wf, sigMemAddr, "sigMemAddr");
		sc_trace(wf, sigMemData, "sigMemData");

 		cout << " Running (press CTRL + C to exit)... " << endl;
		// Start Simulation
		sc_start();
	} catch (const std::exception & e) {
		cerr << e.what() << endl;
	}
	return 0;
}


