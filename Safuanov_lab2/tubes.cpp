#include <iostream>
#include <fstream> // для работы с файлами
#include <sstream> // для считывания строки с консоли 
#include <string> // для проверки типа данных
#include <unordered_map> // наша главная структура данных
#include "pipe.h"
#include "KS.h"
#include "get.h"


using namespace std;

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

void unordered_map_view(const unordered_map<int, Pipe>& pipe, const unordered_map<int, KS>& ks) {
	for (auto const& p : pipe) {
		{
			Pipe value;
			value = p.second;
			value.view();
		}
	}
	for (auto const& k : ks) {
		{
			KS value;
			value = k.second;
			value.view();
		}
	}
}

/*void view(pipe& obj_pipe, comp_station& obj_comp_station) {
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
}*/

int main() {
	setlocale(LC_ALL, "Rus"); // Перевод всех символов на русский язык
	cout << "	Добро пожаловать в консольное приложение, описывающее базовые сущности трубопроводного транспорта газа!!!" << '\n';
	unordered_map<int, Pipe> data_P; 
	unordered_map<int, KS> data_KS;
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
				for (auto const& p : data_P) {
					{
						Pipe value;
						value = p.second;
						value.view();
					}
				}
				for (auto const& k : data_KS) {
					{
						KS value;
						value = k.second;
						value.view();
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
				if (read.peek() == std::ifstream::traits_type::eof()) {  // условие пустоты файла
					cout << "Файл пуст!\n";
				}
				else {
					string line;
					while (getline(read, line)) {
						istringstream iss(line);
						string Name;

						int id;
						iss >> Name >> id;
						if (Name == "pipe") {
							Pipe read_pipe;
							read_pipe.download(read, data_P);
							data_P.insert({ id, read_pipe});
							cout << "Данные трубы " << id << " выгружены из файла." << endl;
						}
						if (Name == "comp") {
							KS read_ks;
							read_ks.download(read, data_KS);
							data_KS.insert({ id, read_ks});
							cout << "Данные КС " << id << " выгружены из файла." << endl;
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