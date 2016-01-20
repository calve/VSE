/*
 * rampolska.h
 *
 *  Created on: Nov 11, 2015
 *      Author: rkouere
 */

#ifndef CPU_H_
#define CPU_H_
#include "systemc.h"

SC_MODULE(CPU) {
 public:
  sc_in<bool> Clk;
  sc_out_rv<3> MCmd;
  sc_out<int> MAddr;
  sc_inout_rv<32> MData;

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
      int f = (rand() % 10) < 5 ? WRITE : READ;
      addr += 1;
      addr %= 10;
      int data = -1;
      MAddr.write(addr);
      if (f == WRITE) {
        data = rand();
        cout << " Writing " << data << " at " << addr << endl;
        MData.write(data);
        MAddr.write(f);
      }
      else {
        MAddr.write(f);
        data = MData.read().to_int();
        cout << " Reading " << data << " at " << addr << endl;
      }
      wait();
    }
  }
};
#endif /* CPU_H_ */
