#include "pipe.h"
#include "KS.h"
#include "graph.h"

void GraphStructure::add(int entrance, int exit) {
	graph_list[entrance].insert(exit);
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