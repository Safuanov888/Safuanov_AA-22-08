#pragma once
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
	void change(int id, int num_department);
	void download(ifstream& read);
	void save(ofstream& out, int id);
};