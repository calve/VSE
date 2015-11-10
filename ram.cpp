/*
 * ram.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: rkouere
 */

#include "ram.h"

void ram::read_data() {
	if (enable && !writte) {
		data_out = ram_data[addr_in.read()];
	} else {
		data_out = -1;
	}
	cout << "data_out = " << data_in << endl;
}

void ram::write_data() {
	if (enable && writte) {
		ram_data[addr_in.read()] = data_in;
		cout << "data_in = " << ram_data[addr_in.read()] << endl;
	}
}
