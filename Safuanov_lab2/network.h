#pragma once
#include <iostream>
#include "pipe.h"
#include "KS.h"

class Network {
public:
	void ConnectionPipes(unordered_map<int, Pipe>& data_P, unordered_map<int, KS>& data_KS);
};