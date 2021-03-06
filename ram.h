#ifndef RAM_H_
#define RAM_H_
#include "systemc.h"
#include "common.h"

static const int MEM_SIZE = 512;
SC_MODULE(Memory) {
 public:
  sc_in<bool> Clk;
  sc_inout_rv<3> MCmd;
  sc_in<int> MAddr;
  sc_in<int> MData;
  sc_out<int> SData;
  sc_in<bool> SResp;
  sc_out<bool> SCmdAccept;

  SC_CTOR(Memory) {
    SC_THREAD(execute);
    sensitive << Clk.pos();
    dont_initialize();
    m_data = new int[MEM_SIZE];
  }
  Memory() {
    delete[] m_data;
  }

 private:
  int * m_data;
  void execute() {
    while (true) {
      int cmd;
      int addr;
      int data = 0;
      wait(Clk.value_changed_event());
      addr = MAddr.read();
      cmd = MCmd.read().to_int();
      if (cmd == WR) {
        data = MData.read();
        SCmdAccept.write(1);
        m_data[addr] = data;
        wait(300, SC_PS); /* Write takes 0.3 ns */
        SCmdAccept.write(0);
      }
      else if (cmd == RD) {
        SCmdAccept.write(1);
        data = m_data[addr];
        wait(200, SC_PS); /* Read takes 0.2 ns */
        SCmdAccept.write(0);
        SData.write(data);
        while(!SResp.posedge()){
          wait(SResp.value_changed_event());
        }
        while(!SResp.negedge()){
          wait(SResp.value_changed_event());
        }
        SData.write(0);
      }
    }
  }
};

#endif /* RAM_H_ */
