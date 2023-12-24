#include <iostream>
#include <fstream> // ��� ������ � �������
#include <format> 
#include <chrono> // ��� ������ ������� � ������ � ������ �������

#include <unordered_map>  // ��������� ������
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
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d-%m-%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log" + time + ".txt");
	if (logfile) {
		cerr_out.redirect(logfile);
	}
	Network network;
	while (true) {
		PrintMenu();  // �������� ����
		cout << "������: ";
		cin.clear();
		int choice = get_correct_value(0, 12);
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
			if (!CheckCicle(network.TakePipe(), network.TakeKS())) {
				cout << "� ����� ����������� ����, ���������� ����������" << '\n';
			}
			else {
				vector<int> sorting_nodes = TopologicalSorting(gas_network);
				if (sorting_nodes.size() != 0) {
					cout << "�������������� ���������� ���������: ";
					for (int node : sorting_nodes) {
						cout << node << " ";
					}
					cout << '\n';
				}
				else {
					cout << "���������� ��������� �������������� ����������" << '\n';
				}
			}
			break;
		}
		case 10:
		{
			if (network.TakePipe().size() != 0 && network.TakeKS().size() != 0) {
				ViewGraph(network.TakePipe(), network.TakeKS());
			}
			else {
				cout << "��� ���������� ��� ���������";
			}
			break;
		}
		case 11:
		{
			GraphStructure gas_network = CreateGraph(network.TakePipe(), network.TakeKS());
			cout << "������� id �������� �������: ";
			int source = get_correct_value<int>(1, INT_MAX);
			cout << "������� id �������� �������: ";
			int exit = get_correct_value<int>(1, INT_MAX);
			double max_flow = FordFulkerson(gas_network, source, exit);
			cout << "������������ ����� � ����: " << max_flow << '\n';
			break;
		}
		case 12:
		{
			GraphStructure gas_network = CreateGraph(network.TakePipe(), network.TakeKS());
			cout << "������� id �������� �������: ";
			int start = get_correct_value<int>(1, INT_MAX);
			cout << "������� id �������� �������: ";
			int end = get_correct_value<int>(1, INT_MAX);
			vector<int> min_path = ShortestWay(gas_network, start, end);
			if (!min_path.empty()) {
				cout << "���������� ����: ";
				for (int value = 0; value < min_path.size(); value++) {
					cout << min_path[value] << " ";
				}
				cout << '\n';
			}
			else {
				cout << "���������� ���� �� ������" << '\n';
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