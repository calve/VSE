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
  sc_in<int> SResp;
  sc_out<int> SCmdAccept;

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
        cout << "RAM: Write at " << addr << " : " << data;
        m_data[addr] = data;
        cout << " ... " << m_data[addr] << endl;
        SCmdAccept.write(1);
      }
      else if (cmd == RD) {
        SCmdAccept.write(1);
        data = m_data[addr];
        cout << "RAM: Read at " << addr << " : " << data << endl;
        SData.write(data);
        SCmdAccept.write(0);
        wait(SResp.value_changed_event());
      }
      else {
        cout << "RAM: Did nothing " << endl;
      }
    }
  }
};

#endif /* RAM_H_ */
