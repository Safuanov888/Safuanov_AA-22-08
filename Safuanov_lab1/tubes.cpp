#include <iostream>
#include <fstream> // для работы с файлами
#include <sstream> // для считывания строки с консоли 
#include <string> // для проверки типа данных

using namespace std;

struct pipe {
	string name;
	int length;
	int diameter;
	bool maintenance;
};

struct comp_station {
	string name;
	int num_department;
	int work_department;
	double efficiency;
};

string get_str() {
	string str;
	cin >> ws;
	getline(std::cin, str);
	return str;
}

void add_pipe(pipe& obj_pipe) {
	cout << "Введите название трубы: ";
	obj_pipe.name = get_str();
	cout << "Введите длину трубы: ";
	cin >> obj_pipe.length;
	while (cin.fail() || cin.peek() != '\n' || obj_pipe.length < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> obj_pipe.length;
	}
	cout << "Введите диаметр трубы: ";
	cin >> obj_pipe.diameter;
	while (cin.fail() || cin.peek() != '\n' || obj_pipe.diameter < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> obj_pipe.diameter;
	}
	cout << "Подлежит ли она ремонту?: ";
	cin >> obj_pipe.maintenance;
	while (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> obj_pipe.maintenance;
	}
}

void add_comp_station(comp_station& obj_comp_station) {
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
		obj_comp_station.work_department < 0 || obj_comp_station.work_department > obj_comp_station.num_department) { // проверка рабочих станций 
		cin.clear();																								// должно быть меньше
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

void rewiew(pipe& obj_pipe, comp_station& obj_comp_station) {
	if (!obj_pipe.name.empty()) {
		cout << "					    Труба                                                                 " << '\n';
		cout << "Название трубы - " << obj_pipe.name << '\n';
		cout << "Длина трубы - " << obj_pipe.length << '\n';
		cout << "Диаметр трубы - " << obj_pipe.diameter << '\n';
		if (obj_pipe.maintenance == 1) {
			cout << "Ремонт?: Yes\n";
		}
		else {
			cout << "Ремонт?: No\n";
		}
	}
	else {
		cout << "						Труба отсутствует\n";
	}
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

void change_pipe(pipe& obj_pipe) {
	if (obj_pipe.name.empty()) {        // проверка на наличие трубы
		cout << "Вы не ввели трубу\n";
	}
	else {
		cout << "Работает труба или нет(0 - не работает, 1 - работает): ";
		cin >> obj_pipe.maintenance;
		while (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Данные введены неверно, попробуйте ещё раз: ";
			cin >> obj_pipe.maintenance;
		}
	}
}

void change_comp_station(comp_station& obj_comp_station) {
	if (obj_comp_station.name.empty()) {	// проверка на наличие КС
		cout << "Вы не ввели КС\n";
	}
	else {
		cout << "Сколько цехов задействовано в работе: ";
		cin >> obj_comp_station.efficiency;
		while (cin.fail() || cin.peek() != '\n' || obj_comp_station.efficiency < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Данные введены неверно, попробуйте ещё раз: ";
			cin >> obj_comp_station.efficiency;
		}
	}
}

void save_pipe(pipe& obj_pipe, ofstream& out) {
	if (out.is_open()) {
		out << obj_pipe.name;
		out << obj_pipe.length;
		out << obj_pipe.diameter;
		out << obj_pipe.maintenance;
	}
	else {
		cout << "Ошибка!";
	}
	cout << "Данные успешно загружены в файл." << endl;
}

void save_comp_station(comp_station& obj_comp_station, ofstream& out) {
	if (out.is_open()) {
		out << obj_comp_station.name;
		out << obj_comp_station.num_department;
		out << obj_comp_station.work_department;
		out << obj_comp_station.efficiency;
	}
	else {
		cout << "Ошибка!";
	}
	cout << "Данные успешно загружены в файл." << endl;
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
		cin.clear();
		cin >> choice;
		while (cin.fail() || cin.peek() != '\n' || choice < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Данные введены неверно, попробуйте ещё раз: ";
			cin >> choice;
		}
		ofstream out;
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
			out.open("file.txt");
			out.close();
			if (!obj_pipe.name.empty()) {
				out.open("file.txt", ios_base::app);
				out << "p\n";
				save_pipe(obj_pipe, out);
				out.close();
			}
			if (!obj_comp_station.name.empty()) {
				out.open("file.txt", ios_base::app);
				out << "c\n";
				save_comp_station(obj_comp_station, out);
				out.close();
			}
			break;
		case 7:
			download_info(obj_pipe, obj_comp_station);
			break;
		case 0:
			cout << "Выход из программы";
			exit(0);
		default:
			cout << "Введите числа от 0 до 7\n";
			break;
		}
	}
	return 0;
}