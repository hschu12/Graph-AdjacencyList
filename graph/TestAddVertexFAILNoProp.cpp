#include "include/adjacency_list.hpp"
#include "include/properties.hpp"
#include "include/tags.hpp"
#include "include/depth_first_search.hpp"
#include "include/topological_sort.hpp"
#include <iostream>

int main()
{
	using edgedirection = graph::tags::Bidirectional;
		
	graph::AdjacencyList<edgedirection> graf = graph::AdjacencyList<edgedirection>(4);

	auto v1 = addVertex(graf);
	auto v2 = addVertex(graf);
	auto v3 = addVertex(graf);
	auto v4 = addVertex(graf);
	auto v5 = addVertex(graf);

	auto e1 = addEdge(v1, v2, graf);
	auto e2 = addEdge(v1, v3, graf);
	auto e3 = addEdge(v2, v3, graf);
	auto e4 = addEdge(v2, v4, graf);
	auto e5 = addEdge(v3, v4, graf);

	return 0;
}