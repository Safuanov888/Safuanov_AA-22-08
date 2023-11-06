#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>

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
	void change(int id);
	void download(ifstream& read);
	void save(ofstream& out, int id);
}; 
