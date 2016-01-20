#include "systemc.h"
#include "common.h"
#include "ram.h"
#include "cpu.h"


int sc_main(int argc, char * argv[]) {
        try {
                //Instantiate Modules
                Memory mem("main_memory");
                CPU cpu("cpu");
                //Signals
                sc_signal_rv<3> MCmd;
                sc_buffer<Memory::RetCode> sigMemDone;
                sc_signal<int> sigMemAddr;
                sc_signal_rv<32> sigMemData;
                // The clock that will drive the CPU and Memory
                sc_clock clk;
                // Connecting module ports with signals
                mem.MCmd(MCmd);
                mem.Port_Addr(sigMemAddr);
                mem.Port_Data(sigMemData);
                mem.Port_Done(sigMemDone);
                cpu.MCmd(MCmd);
                cpu.MAddr(sigMemAddr);
                cpu.MData(sigMemData);
                mem.Clk(clk);
                cpu.Clk(clk);

                cout << "Installing trace signals. Output in ram_trace.vcd " << endl;
                sc_trace_file *wf = sc_create_vcd_trace_file("ram_trace");
                sc_trace(wf, clk, "clock");
                sc_trace(wf, MCmd, "function");
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


