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
    sc_signal<int> MAddr;
    sc_signal<int> MData;
    sc_signal<int> SData;
    sc_signal<bool> SResp;
    sc_signal<bool> SCmdAccept;
    // The clock that will drive the CPU and Memory
    sc_clock clk;
    // Connecting module ports with signals
    mem.MCmd(MCmd);
    mem.MAddr(MAddr);
    mem.MData(MData);
    mem.SData(SData);
    mem.SResp(SResp);
    mem.SCmdAccept(SCmdAccept);
    cpu.MCmd(MCmd);
    cpu.MAddr(MAddr);
    cpu.MData(MData);
    cpu.SData(SData);
    cpu.SResp(SResp);
    cpu.SCmdAccept(SCmdAccept);
    mem.Clk(clk);
    cpu.Clk(clk);

    cout << "Installing trace signals. Output in ram_trace.vcd " << endl;
    sc_trace_file *wf = sc_create_vcd_trace_file("ram_trace");
    sc_trace(wf, clk, "clock");
    sc_trace(wf, MCmd, "MCmd");
    sc_trace(wf, MAddr, "MAddr");
    sc_trace(wf, MData, "MData");
    sc_trace(wf, SData, "SData");
    sc_trace(wf, SCmdAccept, "SCmdAccept");
    sc_trace(wf, SResp, "SResp");

    cout << " Running (press CTRL + C to exit)... " << endl;
    // Start Simulation
    sc_start();
  } catch (const std::exception & e) {
    cerr << e.what() << endl;
  }
  return 0;
}


