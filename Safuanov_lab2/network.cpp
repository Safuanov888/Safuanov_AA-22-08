#include <iostream>
#include <unordered_map>
#include "utils_and_samples.h"
#include "network.h"

using namespace std;

void Network::ConnectionPipes(unordered_map<int, Pipe>& data_P, unordered_map<int, KS>& data_KS) {
	if (data_P.size() != 0 && data_KS.size() != 0) {
		int entrance_id, exit_id, diameter;
		cout << "Введите желаемый id для входа: ";
		entrance_id = get_correct_value<int>(1, INT_MAX);
		cout << "Введите желаемый id для выхода: ";
		exit_id = get_correct_value<int>(1, INT_MAX);
		diameter = get_diameter();

		while (true) {
			if (FindConnection(data_P, diameter)) {
				for (auto pair : data_P) {
					if (pair.second.diameter == diameter && pair.second.take_id_of_entrance() == 0 && pair.second.take_id_of_exit() == 0) {
						pair.second.connection(entrance_id, exit_id);
						break;
					}
				}
				break;
			}
			cout << "Труба с таким диаметром не найдена, создайте новую" << '\n';
			add_to_dict(data_P);
		}
		cout << "Труба с диаметром " << diameter << " успешно соединена с КС" << '\n';
	}
	else {
		cout << "Невозможно связать трубы с КС" << '\n';
	}
}