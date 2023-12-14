#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class GraphStructure {
public:
	unordered_map<int, unordered_set<int>> graph_list;
	void add(int entrance, int exit);
};
GraphStructure CreateGraph(unordered_map<int, Pipe> data_P, unordered_map<int, KS> data_KS);
vector<int> TopologicalSorting(GraphStructure& graph);