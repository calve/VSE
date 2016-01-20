#ifndef RAM_H_
#define RAM_H_
#include "systemc.h"
#include "common.h"

static const int MEM_SIZE = 512;
SC_MODULE(Memory) {
public:
        enum Function {
                FUNC_READ, FUNC_WRITE
        };
        enum RetCode {
                RET_READ_DONE, RET_WRITE_DONE,
        };
        sc_in<bool> Clk;
        sc_inout_rv<3> MCmd;
        sc_in<int> Port_Addr;
        sc_out<RetCode> Port_Done;
        sc_inout_rv<32> Port_Data;

        SC_CTOR(Memory) {
                SC_THREAD(execute);
                sensitive << Clk.pos();
                dont_initialize();
                m_data = new int[MEM_SIZE];
        }
        ~Memory() {
                delete[] m_data;
        }

private:
        int * m_data;
        void execute() {
                while (true) {
                        wait(MCmd.value_changed_event());
                        int cmd = MCmd.read().to_int();
                        int addr = Port_Addr.read();
                        int data = 0;
                        if (cmd == WRITE) {
                                data = Port_Data.read().to_int();
                        }
                        // Simulate Memory read / write delay
                        wait(100);
                        if (cmd == READ) {
                                Port_Data.write((addr < MEM_SIZE) ? m_data[addr] : 0);
                                Port_Done.write(RET_READ_DONE);
                                wait();
                                Port_Data.write("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
                        } else {
                                if (addr < MEM_SIZE) {
                                        m_data[addr] = data;
                                }
                                Port_Done.write(RET_WRITE_DONE);
                        }
                }
        }
};

#endif /* RAM_H_ */
