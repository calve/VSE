/*
 * ram.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: rkouere
 */

#include "ram.h"

void ram::read_data() {
	if (enable && !readwr) {
		data = ram_data[addr.read()];
	} else {
		data = "ZZZZZZZZZZZZZZZZ";
	}
}
void ram::write_data() {
	if (enable && readwr) {
		ram_data[addr.read()] = data;
	}
}

