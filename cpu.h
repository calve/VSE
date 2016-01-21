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
  sc_out<int> SResp;
  sc_in<int> SCmdAccept;

  SC_CTOR(CPU) {
    SC_THREAD(execute);
    sensitive << Clk.pos();
    dont_initialize();
  }
 private:
  void execute() {
    int addr = 0;
    while (true) {
      wait(Clk.value_changed_event());
      int f = (rand() % 2 ? WR : RD);
      addr += 1;
      addr %= 10;
      int data = -1;
      SResp.write(0);
      MAddr.write(addr);
      MCmd.write(f);
      if (f == WR) {
        data = rand() % 16;
        MData.write(data);
        cout << "CPU: Writing request at " << addr << " : " << data << endl;
        wait(SCmdAccept.value_changed_event());
      }
      else if (f == RD) {
        cout << "CPU: Reading request at " << addr << endl;
        wait(SCmdAccept.value_changed_event());
        cout << "CPU: Accepted by RAM" << endl;
        SResp.write(1);
        data = SData.read();
        cout << " : " << data << endl;
      }
    }
  }
};
#endif /* CPU_H_ */
