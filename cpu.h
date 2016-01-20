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
    while (true) {
      wait();
      int f = (rand() % 10) < 5 ? WRITE : READ;
      int addr = (rand() % MEM_SIZE);
      MAddr.write(addr);
      MAddr.write(f);
      if (f == WRITE) {
        int data = rand();
        cout << " Writing " << data << " at " << addr << endl;
        MData.write(data);
      }
      else {
        int data = MData.read().to_int();
        cout << " Reading " << data << " at " << addr << endl;
      }
      wait();
    }
  }
};
#endif /* CPU_H_ */
