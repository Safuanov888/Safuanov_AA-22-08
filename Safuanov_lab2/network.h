#pragma once
#include <iostream>
#include "pipe.h"
#include <unordered_map>
#include "KS.h"

class Network {
private:
	unordered_map<int, Pipe> data_P;
	unordered_map<int, KS> data_KS;
public:
	inline unordered_map<int, Pipe> TakePipe() { return data_P; };
	inline unordered_map<int, KS> TakeKS() { return data_KS; };

	void ConnectionPipes();
	void AddPipe(Pipe p);
	void AddKS(KS ks);
	void ViewData();
	void change_and_delete_pipe();
	void change_and_delete_ks();
	void save();
	void download();
};