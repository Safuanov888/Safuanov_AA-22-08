#include <iostream>
#include <fstream> // для работы с файлами
#include <sstream> // для считывания строки с консоли 
#include <string> // для проверки типа данных
#include <format> 
#include <chrono> // для замера времени и вывода в нужном формате

#include <unordered_map>  // структуры данных
#include <unordered_set>

#include "samples.h"
#include "pipe.h"
#include "KS.h"
#include "logging.h"


using namespace std;
using namespace chrono;

void menu() {
	cout << "					    Введите необходимую вам цифру                                               " << '\n';
	cout << "1. Добавить трубу" << '\n';
	cout << "2. Добавить КС" << '\n';
	cout << "3. Просмотр объектов" << '\n';
	cout << "4. Редактировать трубу" << '\n';
	cout << "5. Редактировать КС" << '\n';
	cout << "6. Сохранить" << '\n';
	cout << "7. Загрузить" << '\n';
	cout << "0. Выход" << '\n' << '\n';
}

bool filter_by_status(const Pipe& dict, bool status) {
	return dict.maintenance == status;
}

bool filter_by_non_working(const KS& dict, int non_working) {
	return dict.num_department - dict.work_department == dict.num_department * non_working / 100;
}

int main() {
	setlocale(LC_ALL, "Rus"); // Перевод всех символов на русский язык
	cout << "	Добро пожаловать в консольное приложение, описывающее базовые сущности трубопроводного транспорта газа!!!" << '\n';
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d-%m-%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log" + time + ".txt");
	if (logfile) {
		cerr_out.redirect(logfile);
	}
	unordered_map<int, Pipe> data_P;
	unordered_map<int, KS> data_KS;
	while (true) {
		menu();  // вызываем меню
		cout << "Кнопка: ";
		cin.clear();
		int choice = get_correct_value(0, 7);
		switch (choice) {
		case 1:
		{
			add_to_dict(data_P);
			break;
		}
		case 2:
		{
			add_to_dict(data_KS);
			break;
		}
		case 3:
		{
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
			break;
		}
		case 4:
		{
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
							}
						}
						else {
							for (int id : set) {
								data_P.erase(id);
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
							}
						}
						else {
							cout << "Работает труба или нет(0 - не работает, 1 - работает): ";
							for (int id : set) {
								data_P[id].change();
							}
						}
					}
				}
			}
			else {
				cout << "Нет труб для изменений" << '\n';
			}
			break;
		}
		case 5:
		{
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
					for (int id : set) {
						if (choice) {
							data_KS.erase(id);
						}
						else {
							data_KS[id].change();
						}
					}
				}
			}
			else {
				cout << "Нет КС для изменений" << '\n';
			}
			break;
		}
		case 6:
		{
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
			break;
		}
		case 7:
		{
			cout << "Введите название файла для загрузки: ";
			string read_file = get_str();
			ifstream read(read_file);
			if (read.peek() == std::ifstream::traits_type::eof()) {  // условие пустоты файла
				cout << "Файла не существует!\n";
			}
			else {
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
			break;
		}
		case 0:
		{
			cout << "Выход из программы";
			exit(0);
		}
		default:
		{
			cout << "Введите числа от 0 до 7\n";
			break;
		}
		}
	}
	return 0;
}