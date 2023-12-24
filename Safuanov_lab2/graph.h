#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class GraphStructure {
public:
	unordered_map<int, unordered_map<int, pair<int, double>>> graph_list;
	void add(int entrance, int exit, double weight, double capacity);
};
GraphStructure CreateGraph(unordered_map<int, Pipe> data_P, unordered_map<int, KS> data_KS);
vector<int> TopologicalSorting(GraphStructure& graph);
void ViewGraph(unordered_map<int, Pipe> data_P, unordered_map<int, KS> data_KS);
bool CheckCicle(unordered_map<int, Pipe> data_P, unordered_map<int, KS> data_KS);
double FordFulkerson(GraphStructure& graph, int entrance, int exit);
vector<int> ShortestWay(GraphStructure& graph, int start, int end);