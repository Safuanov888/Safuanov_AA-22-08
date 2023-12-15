#include "pipe.h"
#include "KS.h"
#include "graph.h"

void GraphStructure::add(int entrance, int exit) {
	graph_list[entrance].insert(exit);
}

vector<int> get_ids_of_ks(unordered_map<int, KS> data_KS) {
	vector<int> ids;
	for (auto pair : data_KS) {
		ids.push_back(pair.first);
	}
	return ids;
}

GraphStructure CreateGraph(unordered_map<int, Pipe> data_P, unordered_map<int, KS> data_KS) {
	GraphStructure graph;
	if (data_KS.size() != 0) {
		// добавляем вершины графа
		for (auto pair : data_P) {
			if (pair.second.take_id_of_entrance() != 0 && pair.second.take_id_of_exit() != 0) {
				graph.add(pair.second.take_id_of_entrance(), pair.second.take_id_of_exit());
			}
		}
	}
	else {
		cout << "Нет КС для создания графа" << '\n';
	}
	return graph;
}

void DFS(GraphStructure& graph, unordered_map<int, bool>& visited, int node, vector<int>& sorted) {
	visited[node] = true;

	for (int neighbor : graph.graph_list[node]) {
		if (!visited[neighbor]) {
			DFS(graph, visited, neighbor, sorted);
		}
	}
	sorted.push_back(node);
}

vector<int> TopologicalSorting(GraphStructure& graph) {
	unordered_map<int, bool> visited;
	vector<int> sorted;
	// Инициализация всех вершин как не посещенных
	for (auto& pair : graph.graph_list) {
		visited[pair.first] = false;
	}

	// Обход графа в глубину для каждой вершины
	for (auto& pair : graph.graph_list) {
		if (!visited[pair.first]) {
			DFS(graph, visited, pair.first, sorted);
		}
	}

	// Формирование результата - упорядоченного списка вершин
	vector<int> result;
	for (int i = sorted.size() - 1; i >= 0; i--) {
		result.push_back(sorted[i]);
	}
	return result;
}

void ViewGraph(unordered_map<int, Pipe> data_P, unordered_map<int, KS> data_KS) {
	for (auto pair : data_P) {
		cout << pair.second.name << '\n';
		cout << "id входа " << pair.second.take_id_of_entrance() << '\n';
		cout << "id выхода " << pair.second.take_id_of_exit() << '\n';
	}
	for (auto pair : data_KS) {
		cout << pair.second.name << '\n';
		cout << "вершина с id " << pair.first << '\n';
	}
}

bool CheckCicle(unordered_map<int, Pipe> data_P, unordered_map<int, KS> data_KS) 
{
	for (int i = data_KS.size(); i > 0; i--) {
		vector<int> ids_of_ks = get_ids_of_ks(data_KS);
		for (int id : ids_of_ks) {
			int outcome = 0;
			for (auto& [id_p, pipe] : data_P) {
				if (pipe.take_id_of_entrance() == id) {
					outcome += 1;
				}
			}
			if (outcome == 0) {
				data_KS.erase(id);
				for (auto& [id_p, pipe] : data_P) {
					if (pipe.take_id_of_entrance() == id || pipe.take_id_of_exit() == id) {
						pipe.connection(0, 0);
					}
				}
				break;
			}
		}
	}
	return (data_KS.size() == 0); 
}