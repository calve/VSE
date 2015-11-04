/*
 * ram.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: rkouere
 */

#include "ram.h"

void ram::read_data() {
	if (enable && !writte) {
		data = ram_data[addr.read()];
	} else {
		data = "ZZZZZZZZZZZZZZZZ";
	}
}
void ram::write_data() {
	if (enable && writte) {
		ram_data[addr.read()] = data;
	}
}

