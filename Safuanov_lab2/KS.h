#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

class KS
{
	int id;
	static int Nextid;
public:
	inline int getid() const { return id; };
	string name;
	int num_department;
	int work_department;
	double efficiency;
	KS();
	void add();
	void view();
	void change();
	void download(ifstream& read, unordered_map<int, KS>& data_KS);
	void save(ofstream& out, int id);
};