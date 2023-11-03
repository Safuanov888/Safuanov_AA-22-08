#include <iostream>
#include <fstream> // ��� ������ � �������
#include <sstream> // ��� ���������� ������ � ������� 
#include <string> // ��� �������� ���� ������
#include <unordered_map> // ���� ������� ��������� ������
#include <unordered_set>
#include "pipe.h"
#include "KS.h"
#include "get.h"


using namespace std;

void menu() {
	cout << "					    ������� ����������� ��� �����                                               " << endl;
	cout << "1. �������� �����" << endl;
	cout << "2. �������� ��" << endl;
	cout << "3. �������� ��������" << endl;
	cout << "4. ������������� �����" << endl;
	cout << "5. ������������� ��" << endl;
	cout << "6. ���������" << endl;
	cout << "7. ���������" << endl;
	cout << "0. �����" << endl << endl;
}

template <typename I>
vector<int> get_ids(const unordered_map<int, I>& mas) 
{
	unordered_set<int> ids;
	cout << "������� id; ���� ���������, �� -1" << endl;
	while (1) {
		int id = get_int();
		if (id == -1) {
			break;
		}
		else if (mas.contains(id)) {
			ids.insert(id);
		}
		else {
			cout << "��� ������� � ���� id";
		}
		if (ids.size() == mas.size()) {
			break;
		}
	}
	return vector<int>(ids.begin(), ids.end());
}

template<typename T1, typename T2>
using filter = bool(*)(const T1& mas, T2 param);

template<typename T>
bool check_by_name(const T& mas, string name) {
	return mas.name.find(name) != string::npos;
}

bool check_by_status(const Pipe& mas, bool status) {
	return mas.maintenance == status;
}

bool check_by_non_working(const KS& mas, double non_working) {
	return 100 * ((double)(mas.num_department - mas.work_department) / (double)mas.num_department) == non_working;
}

template <typename T1, typename T2>
vector<int> find_by_filter(const unordered_map<int, T1>& mas, filter<T1, T2> f, T2 par) {
	unordered_set<int> ids;
	for (auto& pair : mas) {
		if (f(pair.second, par)) {
			ids.insert(pair.first);
		}
	}
	return ids;
}
/*vector<int> filter_str(const unordered_map<int, T>& mas, string value) {
	vector<int> g;
	for (auto const& f : mas) {
		T obj;
		int id;
		obj = f.second;
		id = f.first;
		if (obj.name == value) {
			g.push_back(id);
		}
	}
	return g;
}

vector<int> filter_bool(const unordered_map<int, Pipe>& mas, bool value) {
	vector<int> g;
	for (auto const& f : mas) {
		Pipe obj;
		int id;
		obj = f.second;
		id = f.first;
		if (obj.maintenance == value) {
			g.push_back(id);
		}
	}
	return g;
}

vector<int> filter_double(const unordered_map<int, KS>& mas, double value) {
	vector<int> g;
	for (auto const& f : mas) {
		KS obj;
		int id;
		double percent;
		obj = f.second;
		id = f.first;
		percent = 100 * ((double)(obj.num_department - obj.work_department) / (double)obj.num_department);
		if (percent == value) {
			g.push_back(id);
		}
	}
	return g;
}
*/
template <typename M>
void view_data(unordered_map<int, M>& mas) {
	for (auto const& pair : mas) {
		M value;
		value = pair.second;
		value.view();
	}
}

template <typename F>
void view_id(unordered_map<int, F>& mas, int id) {
	for (auto const& pair : mas) {
		if (id == pair.first) {
			F value;
			value = pair.second;
			value.view();
		}
	}
}

int main() {
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	unordered_map<int, Pipe> data_P; 
	unordered_map<int, KS> data_KS;
	while (true) {
		menu();  // �������� ����
		cin.clear();
		int choice = get_int();
		switch (choice) {
			case 1:
			{
				Pipe obj_pipe;

				obj_pipe.add();

				data_P.insert({ obj_pipe.getid(), obj_pipe });
				break;
			}
			case 2:
			{
				KS obj_comp_station;

				obj_comp_station.add();

				data_KS.insert({ obj_comp_station.getid(), obj_comp_station });
				break;
			}
			case 3:
			{
				cout << "1 - ���������� ��� �������, 0 - ������������� ����������: ";
				string choice1 = get_str();
				if (choice1 == "1") {
					view_data(data_P);
					view_data(data_KS);
				}
				else {
					vector<int> arr;
					cout << "1 - �����, 0 - ��: ";
					string choice2 = get_str();
					if (choice2 == "1") {
						cout << "1 - �� ��������, 0 - �� �������: ";
						string choice3 = get_str();
						if (choice3 == "1") {
							cout << "������� ��������: ";
							string name = get_str();
							arr = filter_str(data_P, name);
						}
						else {
							bool maintenance;
							cout << "1 - � �������, 0 - ���";
							cin >> maintenance;
							arr = filter_bool(data_P, maintenance);
						}
					}
					else {
						cout << "1 - �� ��������, 0 - �� �������� ����������������� �����: ";
						string choice4 = get_str();
						if (choice4 == "1") {
							cout << "������� ��������: ";
							string name = get_str();
							arr = filter_str(data_KS, name);
						}
						else {
							double non_working;
							cout << "������� �������: ";
							cin >> non_working;
							arr = filter_double(data_KS, non_working);
						}
					}
					for (int id : arr) {
						if (arr[0] % 2 == 1) {
							view_id(data_P, id);
						}
						else {
							view_id(data_KS, id);
						}
					}
				}
				break;
			}
			case 4:
			{
				if (!data_P.empty()) {
					cout << "1 - ��������, 0 - ��������� �����: ";
					string choice = get_str();
					vector<int> ids;
					while (1) {
						if (choice == "1") {
							ids = get_ids(data_P);
							if (!ids.empty()) {
								for (int id : ids) {
									data_P.erase(id);
								}
							}
							else {
								cout << "�� �� ������� id" << endl;
							}
							break;
						}
						else {

						}
					} 
				}
			}
			/*case 5:
			{
				change_comp_station(obj_comp_station);
				break;
			}*/
			case 6:
			{
				ofstream out("file.txt");
				for (auto const& p : data_P) {
					{
						int pipe_id;
						Pipe pipe_value;
						pipe_value = p.second;
						pipe_id = p.first;
						if (!pipe_value.name.empty()) {
							pipe_value.save(out, pipe_id);
						}
					}
				}
				for (auto const& k : data_KS) {
					{
						int ks_id;
						KS ks_value;
						ks_value = k.second;
						ks_id = k.first;
						if (!ks_value.name.empty()) {
							ks_value.save(out, ks_id);
						}
					}
				}
				break;
			}
			case 7:
			{
				ifstream read("file.txt");
				if (read.peek() == std::ifstream::traits_type::eof()) {  // ������� ������� �����
					cout << "���� ����!\n";
				}
				else {
					string Name;
					while (getline(read, Name)) {
						//string Name;
						if (Name == "pipe") {
							Pipe read_pipe;
							read_pipe.download(read, data_P);
							data_P.insert({ read_pipe.getid(), read_pipe});
							cout << "������ ����� " << read_pipe.getid() << " ��������� �� �����." << endl;
						}
						/*if (Name == "comp") {
							KS read_ks;
							read_ks.download(read, data_KS);
							data_KS.insert({ id, read_ks});
							cout << "������ �� " << id << " ��������� �� �����." << endl;
						}*/
					}
				}
				break;
			}
			case 0:
			{
				cout << "����� �� ���������";
				exit(0);
			}
			default:
			{
				cout << "������� ����� �� 0 �� 7\n";
				break;
			}
		}
	}
	return 0;
}