#include <iostream>
#include <fstream>

using namespace std;

class Pipe
{
	int id;
	static int Nextid;
public:
	inline int getid() const { return id; };
	string name;
	int length;
	int diameter;
	bool maintenance;
	Pipe();
	void add();
	void view();
	void change();
	void download();
	void save(ofstream& out, int id);
}; 
