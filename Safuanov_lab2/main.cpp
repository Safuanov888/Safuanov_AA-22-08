#include <iostream>
#include <fstream> // для работы с файлами
#include <format> 
#include <chrono> // для замера времени и вывода в нужном формате

#include <unordered_map>  // структуры данных
#include <unordered_set>

#include "utils_and_samples.h"
#include "network.h"
#include "graph.h"
#include "pipe.h"
#include "KS.h"
#include "logging.h"
#include "menu.h"

using namespace std;
using namespace chrono;

int main() {
	setlocale(LC_ALL, "Rus"); // Перевод всех символов на русский язык
	cout << "	Добро пожаловать в консольное приложение, описывающее базовые сущности трубопроводного транспорта газа!!!" << '\n';
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d-%m-%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log" + time + ".txt");
	if (logfile) {
		cerr_out.redirect(logfile);
	}
	Network network;
	while (true) {
		PrintMenu();  // вызываем меню
		cout << "Кнопка: ";
		cin.clear();
		int choice = get_correct_value(0, 9);
		switch (choice) 
		{
		case 1:
		{
			Pipe pipe;
			network.AddPipe(pipe);
			break;
		}
		case 2:
		{
			KS ks;
			network.AddKS(ks);
			break;
		}
		case 3:
		{
			network.ViewData();
			break;
		}
		case 4:
		{
			network.change_and_delete_pipe();
			break;
		}
		case 5:
		{
			network.change_and_delete_ks();
			break;
		}
		case 6:
		{
			network.save();
			break;
		}
		case 7:
		{
			network.download();
			break;
		}
		case 8:
		{
			network.ConnectionPipes();
			break;
		}
		case 9:
		{
			GraphStructure gas_network = CreateGraph(network.TakePipe(), network.TakeKS());
			vector<int> sorting_nodes = TopologicalSorting(gas_network);
			if (sorting_nodes.size() != 0) {
				cout << "Топологическая сортировка выполнена: ";
				for (int node : sorting_nodes) {
					cout << node << " ";
				} 
				cout << '\n';
			}
			else {
				cout << "Невозможно выполнить топологическую сортировку" << '\n';
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