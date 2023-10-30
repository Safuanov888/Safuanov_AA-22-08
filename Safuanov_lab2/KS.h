#pragma once
#include <iostream>
#include <fstream>

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
	void download();
	void save(ofstream& out, int id);
};