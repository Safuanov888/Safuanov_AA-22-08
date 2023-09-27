#include <iostream>
#include <fstream>

using namespace std;

struct pipe {
	string name;
	double length;
	double diameter;
	string maintenance;
};

struct comp_station {
	string name;
	int num_department;
	int work_department;
	double efficiency;
};

void add_pipe(pipe& obj_pipe) {
	cout << "Введите название трубы: ";
	cin >> obj_pipe.name;
	cout << "Введите длину трубы: ";
	cin >> obj_pipe.length;
	cin.ignore(1000, '\n');
	cout << "Введите диаметр трубы: ";
	cin >> obj_pipe.diameter;
	cin.ignore(1000, '\n');
	cout << "Подлежит ли она ремонту?: ";
	cin >> obj_pipe.maintenance;
}

void add_comp_station(comp_station& obj_comp_station) {
	cout << "Введите название станции: ";
	cin >> obj_comp_station.name;
	cout << "Введите количество цехов: ";
	cin >> obj_comp_station.num_department;
	cin.ignore(1000, '\n');
	cout << "Введите количество работающих цехов: ";
	cin >> obj_comp_station.work_department;
	cin.ignore(1000, '\n');
	cout << "Введите его эффективность: ";
	cin >> obj_comp_station.efficiency;
	cin.ignore(1000, '\n');
}



int main() {
	setlocale(LC_ALL, "Rus"); // Перевод всех символов на русский язык
	cout << "	Добро пожаловать в консольное приложение, описывающее базовые сущности трубопроводного транспорта газа!!!" << '\n';
	cout << "                                          В вашем распоряжении есть меню                                           " << '\n';
	pipe obj_pipe;
	comp_station obj_comp_station;
	while (true) {
		int choice;
		cout << "1. Добавить трубу" << '\n';
		cout << "2. Добавить КС" << '\n';
		cout << "3. Просмотр всех объектов" << '\n';
		cout << "4. Редактировать трубу" << '\n';
		cout << "5. Редактировать КС" << '\n';
		cout << "6. Сохранить" << '\n';
		cout << "7. Загрузить" << '\n';
		cout << "0. Выход" << '\n';
		cout << "					   Введите необходимую вам цифру                                               " << '\n';
		cin >> choice;
		switch (choice) {
		case 1:
			add_pipe(obj_pipe);
			break;
		case 2:
			add_comp_station(obj_comp_station);
			break;
		}
		return 0;
	}
}