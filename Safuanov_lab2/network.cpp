#include <iostream>
#include <unordered_map>
#include "network.h"
#include "utils_and_samples.h"

using namespace std;

bool filter_by_status(const Pipe& dict, bool status) {
	return dict.maintenance == status;
}

bool filter_by_non_working(const KS& dict, int non_working) {
	return dict.num_department - dict.work_department == dict.num_department * non_working / 100;
}

void Network::ConnectionPipes() {
	if (data_P.size() != 0 && data_KS.size() != 0) {
		int entrance_id, exit_id, diameter;
		cout << "Введите желаемый id для входа: ";
		entrance_id = get_correct_value<int>(1, INT_MAX);
		cout << "Введите желаемый id для выхода: ";
		exit_id = get_correct_value<int>(1, INT_MAX);
		diameter = get_diameter();

		while (true) {
			if (FindConnection(data_P, diameter)) {
				for (auto& pair : data_P) {
					if (pair.second.diameter == diameter && pair.second.take_id_of_entrance() == 0 && pair.second.take_id_of_exit() == 0) {
						pair.second.connection(entrance_id, exit_id);
						break;
					}
				}
				break;
			}
			cout << "Труба с таким диаметром не найдена, создайте новую" << '\n';
			Pipe p;
			p.add();
			data_P.insert({ p.getid(), p });
		}
		cout << "Труба с диаметром " << diameter << " успешно соединена с КС" << '\n';
	}
	else {
		cout << "Невозможно связать трубы с КС" << '\n';
	}
}

void Network::AddPipe(Pipe p) {
	p.add();
	data_P.insert({p.getid(), p});
}

void Network::AddKS(KS ks) {
	ks.add();
	data_KS.insert({ ks.getid(), ks });
}

void Network::ViewData() {
	cout << "1 - посмотреть все объекты, 0 - отфильтровать информацию: ";
	if (bool choice1 = get_correct_value(0, 1)) {
		view_data(data_P);
		view_data(data_KS);
	}
	else {
		cout << "1 - Трубу, 0 - КС: ";
		if (bool choice2 = get_correct_value(0, 1)) {
			cout << "1 - по названию, 0 - по ремонту: ";
			if (bool choice3 = get_correct_value(0, 1)) {
				cout << "Введите название: ";
				string name = get_str();
				for (int i : find_by_filter(data_P, filter_by_name, name)) {
					view_id(data_P, i);
				}
			}
			else {
				cout << "Введите статус: ";
				bool maintenance = get_correct_value(0, 1);
				for (int i : find_by_filter(data_P, filter_by_status, maintenance)) {
					view_id(data_P, i);
				}
			}
		}
		else {
			cout << "1 - по названию, 0 - по проценту незадействованных цехов: ";
			if (bool choice4 = get_correct_value(0, 1)) {
				cout << "Введите название: ";
				string name = get_str();
				for (int i : find_by_filter(data_KS, filter_by_name, name)) {
					view_id(data_KS, i);
				}
			}
			else {
				cout << "Введите процент: ";
				int non_working = get_correct_value(0, 100);
				for (int i : find_by_filter(data_KS, filter_by_non_working, non_working)) {
					view_id(data_KS, i);
				}
			}
		}
	}
}

void Network::change_and_delete_pipe() {
	if (!data_P.empty()) {
		cout << "1 - удаление, 0 - изменение труб: ";
		bool choice1 = get_correct_value(0, 1);
		vector<int> ids;
		cout << "Введите название трубы: ";
		string name = get_str();
		unordered_set<int> set = find_by_filter(data_P, filter_by_name, name);
		if (set.size() == 0) {
			cout << "Такого имени нет";
		}
		else {
			if (choice1) {
				cout << "1 - удалить все трубы, 0 - на ваш выбор: ";
				bool choice2 = get_correct_value(0, 1);
				if (!choice2) {
					cout << "Можете выбирать из данного набора id" << '\n';
					for (const auto& id : set) {
						cout << id << '\n';
					}
					ids = get_ids(data_P);
					for (int id : ids) {
						data_P.erase(id);
						cout << "Труба с id " << id << " удалена";
					}
				}
				else {
					for (int id : set) {
						data_P.erase(id);
						cout << "Труба с id " << id << " удалена";
					}
				}
			}
			else {
				cout << "1 - поменять все трубы, 0 - на ваш выбор: ";
				bool choice3 = get_correct_value(0, 1);
				if (!choice3) {
					cout << "Можете выбирать из данного набора id" << '\n';
					for (const auto& id : set) {
						cout << id << '\n';
					}
					ids = get_ids(data_P);
					for (int id : ids) {
						data_P[id].change();
						cout << "Труба с id " << id << " поменялась";
					}
				}
				else {
					cout << "Работает труба или нет(0 - не работает, 1 - работает): ";
					for (int id : set) {
						data_P[id].change();
						cout << "Труба с id " << id << " поменялась";
					}
				}
			}
		}
	}
	else {
		cout << "Нет труб для изменений" << '\n';
	}
}

void Network::change_and_delete_ks() {
	if (!data_KS.empty()) {
		cout << "1 - удаление, 0 - изменение КС: ";
		bool choice = get_correct_value(0, 1);
		cout << "Введите название КС: ";
		string name = get_str();
		unordered_set<int> set = find_by_filter(data_KS, filter_by_name, name);
		if (set.size() == 0) {
			cout << "Такого имени нет";
		}
		else {
			for (int id_ks : set) {
				if (choice) {
					data_KS.erase(id_ks);
					cout << "KC с id " << id_ks << " удалена";
					for (auto& [id_p, pipe] : data_P) {
						if (pipe.take_id_of_entrance() == id_ks || pipe.take_id_of_exit() == id_ks) {
							pipe.connection(0, 0);
						}
					}
				}
				else {
					data_KS[id_ks].change();
					cout << "Труба с id " << id_ks << " поменялась";
				}
			}
		}
	}
	else {
		cout << "Нет КС для изменений" << '\n';
	}
}

void Network::save() {
	cout << "Введите название файла для записи: ";
	string in_file = get_str();
	ofstream out(in_file);
	if (data_P.empty()) {
		cout << "Нет труб" << '\n';
	}
	if (data_KS.empty()) {
		cout << "Нет КС" << '\n';
	}
	for (auto const& p : data_P) {
		if (!p.second.name.empty()) {
			data_P[p.first].save(out);
		}
	}
	for (auto const& k : data_KS) {
		if (!k.second.name.empty()) {
			data_KS[k.first].save(out);
		}
	}
}

void Network::download() {
	cout << "Введите название файла для загрузки: ";
	string read_file = get_str();
	ifstream read(read_file);
	if (read.peek() == std::ifstream::traits_type::eof()) {  // условие пустоты файла
		cout << "Файла не существует!\n";
	}
	else {
		data_P.clear();
		Pipe::reset_next_id();
		data_KS.clear();
		KS::reset_next_id();
		string Name;
		while (getline(read, Name)) {
			if (Name == "pipe") {
				Pipe read_pipe;
				read_pipe.download(read);
				data_P.insert({ read_pipe.getid(), read_pipe });
				cout << "Данные трубы " << read_pipe.getid() << " выгружены из файла." << '\n';
			}
			if (Name == "comp") {
				KS read_ks;
				read_ks.download(read);
				data_KS.insert({ read_ks.getid(), read_ks });
				cout << "Данные КС " << read_ks.getid() << " выгружены из файла." << '\n';
			}
		}
	}
}