#include <iostream>
#include <fstream>

using namespace std;

struct pipe {
	string name;
	int length;
	int diameter;
	string maintenance;

};

struct KS {
	string name;
	int num_department;
	int work_department;
	int efficiency;
};

int menu() {
	cout << "	Добро пожаловать в консольное приложение, описывающее базовые сущности трубопроводного транспорта газа!!!" << '\n';
	cout << "                                          В вашем распоряжении есть меню                                           " << '\n';
	while (true) {
		cout << "1. Добавить трубу" << '\n';
		cout << "2. Добавить КС" << '\n';
		cout << "3. Просмотр всех объектов" << '\n';
		cout << "4. Редактировать трубу" << '\n';
		cout << "5. Редактировать КС" << '\n';
		cout << "6. Сохранить" << '\n';
		cout << "7. Загрузить" << '\n';
		cout << "0. Выход" << '\n';
	}
	return 0;
}



int main() {
	setlocale(LC_ALL, "Rus"); // Перевод всех символов на русский язык














	return 0;
}