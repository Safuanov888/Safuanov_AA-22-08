#include <iostream>
#include <fstream> // для работы с файлами
#include <sstream> // для считывания строки с консоли 
#include <string> // для проверки типа данных
#include <unordered_map> // наша главная структура данных
#include "pipe.h"
#include "get.h"

using namespace std;

/*struct comp_station {
	string name;
	int num_department;
	int work_department;
	double efficiency;
};*/

void menu() {
	cout << "					    Введите необходимую вам цифру                                               " << endl;
	cout << "1. Добавить трубу" << endl;
	cout << "2. Добавить КС" << endl;
	cout << "3. Просмотр объектов" << endl;
	cout << "4. Редактировать трубу" << endl;
	cout << "5. Редактировать КС" << endl;
	cout << "6. Сохранить" << endl;
	cout << "7. Загрузить" << endl;
	cout << "0. Выход" << endl << endl;
}



/*void add_comp_station(comp_station& obj_comp_station) {
	cout << "Введите название станции: ";
	obj_comp_station.name = get_str();
	cout << "Введите количество цехов: ";
	cin >> obj_comp_station.num_department;
	while (cin.fail() || cin.peek() != '\n' || obj_comp_station.num_department < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> obj_comp_station.num_department;
	}
	cout << "Введите количество работающих цехов: ";
	cin >> obj_comp_station.work_department;
	while (cin.fail() || cin.peek() != '\n' || 
		obj_comp_station.work_department < 0 || obj_comp_station.work_department > obj_comp_station.num_department) { // проверка рабочих станций,
		cin.clear();																								  // должно быть меньше
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> obj_comp_station.work_department;
	}
	cout << "Введите его эффективность: ";
	cin >> obj_comp_station.efficiency;
	while (cin.fail() || cin.peek() != '\n' || obj_comp_station.efficiency < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> obj_comp_station.efficiency;
	}
}

void view_comp_station(comp_station & obj_comp_station) {
	if (!obj_comp_station.name.empty()) {
		cout << "					    Станция                                                                 " << '\n';
		cout << "Название станции - " << obj_comp_station.name << '\n';
		cout << "Количество цехов - " << obj_comp_station.num_department << '\n';
		cout << "Количество работающих цехов - " << obj_comp_station.work_department << '\n';
		cout << "Эффективность станции - " << obj_comp_station.efficiency << '\n';
	}
	else {
		cout << "						КС отсутствует\n";
	}
}

void view(pipe& obj_pipe, comp_station& obj_comp_station) {
	cout << "Что вы хотите посмотреть? (0 - трубу, 1 - КС, что-то другое - всё)\n";
	string choice;
	cin >> choice;
	if (choice == "0") {
		view_pipe(obj_pipe);
	}
	else if (choice == "1") {
		view_comp_station(obj_comp_station);
	}
	else {
		view_pipe(obj_pipe);
		view_comp_station(obj_comp_station);
	}
}

void change_comp_station(comp_station& obj_comp_station) {
	if (obj_comp_station.name.empty()) {	// проверка на наличие КС
		cout << "Вы не ввели КС\n";
	}
	else {
		cout << "Сколько цехов задействовано в работе: ";
		cin >> obj_comp_station.efficiency;
		while (cin.fail() || cin.peek() != '\n' || obj_comp_station.efficiency < 0 || obj_comp_station.work_department > obj_comp_station.num_department) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Данные введены неверно, попробуйте ещё раз: ";
			cin >> obj_comp_station.efficiency;
		}
	}
}

void save_comp_station(comp_station& obj_comp_station, ofstream& out) {
	if (out.is_open()) {
		out << obj_comp_station.name << endl;
		out << obj_comp_station.num_department << endl;
		out << obj_comp_station.work_department << endl;
		out << obj_comp_station.efficiency << endl;
		cout << "Данные КС загружены в файл." << endl;
	}
	else {
		cout << "Ошибка!";
	}
}

void download_comp_station(comp_station& obj_comp_station, ifstream& read) {
	if (read.is_open()) {
		read >> obj_comp_station.name;
		read >> obj_comp_station.num_department;
		read >> obj_comp_station.work_department;
		read >> obj_comp_station.efficiency;
		cout << "Данные КС выгружены из файла." << endl;
	}
	else {
		cout << "Ошибка!";
	}
}*/

int main() {
	setlocale(LC_ALL, "Rus"); // Перевод всех символов на русский язык
	cout << "	Добро пожаловать в консольное приложение, описывающее базовые сущности трубопроводного транспорта газа!!!" << '\n';
	unordered_map<int, Pipe> data; 
	while (true) {
		int choice;
		menu();  // вызываем меню
		cin.clear();
		cin >> choice;
		while (cin.fail() || cin.peek() != '\n' || choice < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Данные введены неверно, попробуйте ещё раз: ";
			cin >> choice;
		}
		switch (choice) {
			case 1:
			{
				Pipe obj_pipe;

				obj_pipe.add();

				data.insert({ obj_pipe.getid(), obj_pipe });
				break;
			}
			/*case 2:
			{
				add_comp_station(obj_comp_station);
				break;
			}*/
			case 3:
			{
				for (auto const& p : data) {
					{
						Pipe l;
						l = p.second;
						l.view();
					}
				}
				break;
			}
			/*case 4:
			{
				change_pipe(obj_pipe);
				break;
			}
			case 5:
			{
				change_comp_station(obj_comp_station);
				break;
			}*/
			/*case 6:
			{
				ofstream out;
				out.open("file.txt");
				if (!obj_pipe.name.empty()) {
					out << "pipe\n";
					save_pipe(obj_pipe, out);
				}
				if (!obj_comp_station.name.empty()) {
					out << "comp_station\n";
					save_comp_station(obj_comp_station, out);
				}
				break;
			}
			case 7:
			{
				read.open("file.txt");
				if (read.peek() == std::ifstream::traits_type::eof()) {  // условие пустоты файла
					cout << "Файл пуст!\n";
				}
				else {
					string line;
					while (getline(read, line)) {
						if (line.find("pipe") != string::npos) {
							download_pipe(obj_pipe, read);
						}
						if (line.find("comp_station") != string::npos) {
							download_comp_station(obj_comp_station, read);
						}
					}
				}
				break;
			}*/
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