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
    SResp.write(0);
    MAddr.write(addr);
    MData.write(data);
    MCmd.write(WR);
    cout << "CPU: Writing request at " << addr << " : " << data << endl;
    wait(SCmdAccept.value_changed_event());
    cout << "CPU: Write Done " << endl;
  }

  int read(int addr){
    int data;
    MAddr.write(addr);
    MCmd.write(RD);
    cout << "CPU: Reading request at " << addr << endl;
    wait(SCmdAccept.value_changed_event());
    cout << "CPU: Accepted by RAM" << endl;
    SResp.write(1);
    data = SData.read();
    cout << " : " << data << endl;
    return data;
  }

  void execute() {
    int addr = 0;
    while (true) {
      wait(Clk.value_changed_event());
      int f = (rand() % 2 ? WR : RD);
      addr += 1;
      addr %= 10;
      int data = -1;
      if (f == WR) {
        data = rand() % 16;
        write(addr, data);
      }
      else if (f == RD) {
        data = read(addr);
      }
    }
  }
};
#endif /* CPU_H_ */
