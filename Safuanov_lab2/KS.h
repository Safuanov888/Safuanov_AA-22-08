#pragma once
#include <fstream>

using namespace std;

class KS
{
private:
	int id;
	static int Nextid;
public:
	inline int getid() const { return id; };
	static void reset_next_id() { Nextid=0; };
	string name;
	int num_department;
	int work_department;
	double efficiency;
	KS();
	void add();
	void view();
	void change();
	void download(ifstream& read);
	void save(ofstream& out);
};