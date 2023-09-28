#include <iostream>
#include <fstream> // для работы с файлами
#include <sstream> // для считывания строки с консоли 
#include <string> // для проверки типа данных

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

bool is_string(string check_type) {
	for (char c : check_type) {
		if (isdigit(c)) {
			return false; // Если есть цифра, то это не строка
		}
	}
	return true; // Если не содержит цифры, то это строка
}

bool find_space(string row) {
	for (char c : row) {
		if (c == ' ') {
			return true;
		}
	}
	return false;
}

void add_pipe(pipe& obj_pipe) {
	cout << "Введите название трубы: ";
	while (true) {

		cin >> obj_pipe.name;
		if (is_string(obj_pipe.name)) {
			break;
		}
		cout << "Данные введены неверно, попробуйте ещё раз: ";
	}
	cout << "Введите длину трубы: ";
	while (true) {
		string input1, copy1;
		cin >> input1;
		copy1 = input1;
		getline(cin, copy1);
		if (find_space(copy1)) {
			cout << "Данные введены неверно, попробуйте ещё раз: ";
		}
		else {
			try {
				obj_pipe.length = stod(input1);
				break;
			}
			catch (invalid_argument& myException) {
				cout << "Данные введены неверно, попробуйте ещё раз: ";
			}
		}
	}
	cout << "Введите диаметр трубы: ";
	while (true) {
		string input2, copy2; // добавляется копия строки, чтобы не затрагивать саму строку
		cin >> input2;
		copy2 = input2;
		getline(cin, copy2);
		if (find_space(copy2)) {
			cout << "Данные введены неверно, попробуйте ещё раз: ";
		}
		else {
			try {
				obj_pipe.diameter = stod(input2);
				break;
			}
			catch (invalid_argument& myException) {
				cout << "Данные введены неверно, попробуйте ещё раз: ";
			}
		}
	}
	cout << "Подлежит ли она ремонту?: ";
	while (true) {
		cin >> obj_pipe.maintenance;
		if (is_string(obj_pipe.name)) {
			if (obj_pipe.maintenance == "Yes" || obj_pipe.maintenance == "YES") {
				break;
			}
			else if (obj_pipe.maintenance == "No" || obj_pipe.maintenance == "NO") {
				break;
			}
			else {
				cout << "Данные введены неверно, попробуйте ещё раз: ";
			}
		}
		else {
			cout << "Данные введены неверно, попробуйте ещё раз: ";
		}
	}
}

void add_comp_station(comp_station& obj_comp_station) {
	cout << "Введите название станции: ";
	cin.ignore(1000, '\n');
	getline(cin, obj_comp_station.name);
	cout << "Введите количество цехов: ";
	cin >> obj_comp_station.num_department;
	cout << "Введите количество работающих цехов: ";
	cin >> obj_comp_station.work_department;
	cout << "Введите его эффективность: ";
	cin >> obj_comp_station.efficiency;
}

void rewiew(pipe& obj_pipe, comp_station& obj_comp_station) {
	cout << "					    Труба                                                                 " << '\n';
	cout << "Название трубы - " << obj_pipe.name << '\n';
	cout << "Длина трубы - " << obj_pipe.length << '\n';
	cout << "Диаметр трубы - " << obj_pipe.diameter << '\n';
	cout << "Ремонт трубы - " << obj_pipe.maintenance << '\n';
	cout << "					    Станция                                                                 " << '\n';
	cout << "Название станции - " << obj_comp_station.name << '\n';
	cout << "Количество цехов - " << obj_comp_station.num_department << '\n';
	cout << "Количество работающих цехов - " << obj_comp_station.work_department << '\n';
	cout << "Эффективность станции - " << obj_comp_station.efficiency << '\n';
}

void change_pipe(pipe& obj_pipe) {
	cout << "Введите название трубы: ";
	cin.ignore(1000, '\n');
	getline(cin, obj_pipe.name);
	cout << "Введите длину трубы: ";
	cin >> obj_pipe.length;
	cout << "Введите диаметр трубы: ";
	cin >> obj_pipe.diameter;
	cout << "Подлежит ли она ремонту?: ";
	cin >> obj_pipe.maintenance;
}

void change_comp_station(comp_station& obj_comp_station) {
	cout << "Введите название станции: ";
	cin.ignore(1000, '\n');
	getline(cin, obj_comp_station.name);
	cout << "Введите количество цехов: ";
	cin >> obj_comp_station.num_department;
	cout << "Введите количество работающих цехов: ";
	cin >> obj_comp_station.work_department;
	cout << "Введите его эффективность: ";
	cin >> obj_comp_station.efficiency;
}

void save_info(pipe& obj_pipe, comp_station& obj_comp_station) {
	ofstream inputFile("file.txt");
	if (inputFile.is_open()) {      // если файл открывается
		inputFile << obj_pipe.name << endl;
		inputFile << obj_pipe.length << endl;
		inputFile << obj_pipe.diameter << endl;
		inputFile << obj_pipe.maintenance << endl;
		inputFile << obj_comp_station.name << endl;
		inputFile << obj_comp_station.num_department << endl;
		inputFile << obj_comp_station.work_department << endl;
		inputFile << obj_comp_station.efficiency << endl;
	}
	else {
		cout << "Ошибка!";
	}
	inputFile.close();
	cout << "Данные успешно записаны в файл." << endl;
}

void download_info(pipe& obj_pipe, comp_station& obj_comp_station) {
	ifstream outputFile("file.txt");
	if (outputFile.is_open()) {
		outputFile >> obj_pipe.name;
		outputFile >> obj_pipe.length;
		outputFile >> obj_pipe.diameter;
		outputFile >> obj_pipe.maintenance;
		outputFile >> obj_comp_station.num_department;
		outputFile >> obj_comp_station.name;
		outputFile >> obj_comp_station.work_department;
		outputFile >> obj_comp_station.efficiency;
	}
	else {
		cout << "Ошибка!";
	}
	outputFile.close();
	cout << "Данные успешно выгружены из файла." << endl;
}

int main() {
	setlocale(LC_ALL, "Rus"); // Перевод всех символов на русский язык
	cout << "	Добро пожаловать в консольное приложение, описывающее базовые сущности трубопроводного транспорта газа!!!" << '\n';
	pipe obj_pipe;
	comp_station obj_comp_station;
	while (true) {
		int choice;
		cout << "					    Введите необходимую вам цифру                                               " << '\n';
		cout << "1. Добавить трубу" << '\n';
		cout << "2. Добавить КС" << '\n';
		cout << "3. Просмотр всех объектов" << '\n';
		cout << "4. Редактировать трубу" << '\n';
		cout << "5. Редактировать КС" << '\n';
		cout << "6. Сохранить" << '\n';
		cout << "7. Загрузить" << '\n';
		cout << "0. Выход" << '\n' << '\n';
		cin >> choice;
		switch (choice) {
		case 1:
			add_pipe(obj_pipe);
			break;
		case 2:
			add_comp_station(obj_comp_station);
			break;
		case 3:
			rewiew(obj_pipe, obj_comp_station);
			break;
		case 4:
			change_pipe(obj_pipe);
			break;
		case 5:
			change_comp_station(obj_comp_station);
			break;
		case 6:
			save_info(obj_pipe, obj_comp_station);
			break;
		case 7:
			download_info(obj_pipe, obj_comp_station);
			break;
		case 0:
			cout << "Выход из программы";
			exit(0);
		}
	}
	return 0;
}