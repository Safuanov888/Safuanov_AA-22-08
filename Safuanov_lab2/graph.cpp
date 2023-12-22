#include "pipe.h"
#include "KS.h"
#include "graph.h"
#include <math.h>
#include "queue"

void GraphStructure::add(int entrance, int exit, double weight, double capacity) {
	graph_list[entrance][exit] = make_pair(weight, capacity);
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
			double weight;
			double capacity;
			if (pair.second.maintenance == 0) {
				weight = pair.second.length;
				capacity = 10000 * sqrt(pow((double)pair.second.diameter / 1000, 5) / pair.second.length);
			}
			else {
				weight = INFINITY;
				capacity = 0;
			}
			if (pair.second.take_id_of_entrance() != 0 && pair.second.take_id_of_exit() != 0) {
				graph.add(pair.second.take_id_of_entrance(), pair.second.take_id_of_exit(), weight, capacity);
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

	for (const auto& [neighbor, param] : graph.graph_list[node]) {
		if (!visited[neighbor]) {
			DFS(graph, visited, neighbor, sorted);
		}
	}
	sorted.push_back(node);
}

bool BFS(GraphStructure& graph, int entrance, int exit, vector<int>& parent) {
	std::queue<int> q;
	std::unordered_set<int> visited;
	q.push(entrance);
	visited.insert(entrance);
	bool foundPath = false;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (const auto& [v, edge] : graph.graph_list[u]) {
			double capacity = edge.second;
			if (!visited.count(v) && capacity > 0) {
				q.push(v);
				parent[v-1] = u;
				visited.insert(v);
				if (v == exit) {
					foundPath = true;
					break;
				}
			}
		}
	}

	return foundPath;
}

double FordFulkerson(GraphStructure& graph, int entrance, int exit) {
	vector<int> parent(graph.graph_list.size() + 1, -1);
	double max_flow = 0.0;

	while (BFS(graph, entrance, exit, parent)) {
		double path_flow = INFINITY;

		// Нахождение минимального потока в пути
		for (int id = exit; id != entrance; id = parent[id-1]) {
			int entrance = parent[id-1];
			path_flow = min(path_flow, graph.graph_list[entrance][id].second);
		}
		// Обновление потоков в сети
		for (int id = exit; id != entrance; id = parent[id-1]) {
			int entrance = parent[id-1];
			graph.graph_list[entrance][id].second -= path_flow;
			graph.graph_list[id][entrance].second += path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;

}

vector<int> ShortestWay(GraphStructure& graph, int entrance, int exit) {

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