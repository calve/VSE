#ifndef CPU_H_
#define CPU_H_
#include "systemc.h"

SC_MODULE(CPU) {
 public:
  sc_in<bool> Clk;
  sc_out_rv<3> MCmd;
  sc_out<int> MAddr;
  sc_out<int> MData;
  sc_in<int> SData;
  sc_out<bool> SResp;
  sc_in<bool> SCmdAccept;

  SC_CTOR(CPU) {
    SC_THREAD(execute);
    sensitive << Clk.pos();
    dont_initialize();
  }
 private:

  void write(int addr, int data){
    MAddr.write(addr);
    MData.write(data);
    MCmd.write(WR);
    while(!SCmdAccept.posedge()){
      wait(SCmdAccept.value_changed_event());
    }
    while(!SCmdAccept.negedge()){
      wait(SCmdAccept.value_changed_event());
    }
    MCmd.write(IDLE);
  }

  int read(int addr){
    int data;
    MAddr.write(addr);
    MCmd.write(RD);
    while(!SCmdAccept.posedge()){
      wait(SCmdAccept.value_changed_event());
    }
    while(!SCmdAccept.negedge()){
      wait(SCmdAccept.value_changed_event());
    }
    MCmd.write(IDLE);
    SResp.write(1);
    data = SData.read();
    wait(200, SC_PS); /* Read takes 0.2 ns */
    SResp.write(0);
    return data;
  }

  void execute() {
    wait(Clk.value_changed_event());
    write(42, 0xdeadbeef);
    wait(Clk.value_changed_event());
    write(30, 0xbadbad02);
    wait(Clk.value_changed_event());
    read(42);
    wait(Clk.value_changed_event());
    read(30);
  }
};
#endif /* CPU_H_ */
