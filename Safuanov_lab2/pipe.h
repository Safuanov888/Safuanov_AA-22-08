#pragma once
#include <fstream>

using namespace std;

class Pipe
{
private:
	int id;
	static int Nextid;
	int id_of_entrance;
	int id_of_exit;
public:
	inline int getid() const { return id; };
	static void reset_next_id() {  Nextid=0; };
	inline int take_id_of_entrance() const { return id_of_entrance; };
	inline int take_id_of_exit() const { return id_of_exit; };
	string name;
	int length;
	int diameter;
	bool maintenance;
	Pipe();
	void add();
	void view();
	void change();
	void download(ifstream& read);
	void save(ofstream& out);
	void connection(int entrance, int exit);
}; 