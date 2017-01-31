#include "include/adjacency_list.hpp"
#include "include/properties.hpp"
#include "include/tags.hpp"
#include "include/depth_first_search.hpp"
#include "include/topological_sort.hpp"
#include <iostream>

int main()
{
	using edgedirection = graph::tags::Bidirectional;
	using vertexProp = graph::vertexProp::Capacity;
	using edgeProp = graph::edgeProp::Cost;

	graph::AdjacencyList<edgedirection, vertexProp, edgeProp> graf = graph::AdjacencyList<edgedirection, vertexProp, edgeProp>(4);

	auto v1 = addVertex(graph::vertexProp::Capacity(10), graf);
	auto v2 = addVertex(graph::vertexProp::Capacity(15), graf);
	auto v3 = addVertex(graph::vertexProp::Capacity(20), graf);
	auto v4 = addVertex(graph::vertexProp::Capacity(25), graf);
	auto v5 = addVertex(graph::vertexProp::Capacity(30), graf);

	auto e1 = addEdge(v1, v2, graf);
	auto e2 = addEdge(v1, v3, graf);
	auto e3 = addEdge(v2, v3, graf);
	auto e4 = addEdge(v2, v4, graf);
	auto e5 = addEdge(v3, v4, graf);

	return 0;
}