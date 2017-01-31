#include "include/adjacency_list.hpp"
#include "include/properties.hpp"
#include "include/tags.hpp"
#include "include/depth_first_search.hpp"
#include "include/topological_sort.hpp"
#include <iostream>

int main()
{
	using edgedirection = graph::tags::Directed;
		
	graph::AdjacencyList<edgedirection> graf = graph::AdjacencyList<edgedirection>(7);

	auto v1 = addVertex(graf);
	auto v2 = addVertex(graf);
	auto v3 = addVertex(graf);
	auto v4 = addVertex(graf);
	auto v5 = addVertex(graf);
	auto v6 = addVertex(graf);
	auto v7 = addVertex(graf);
	
	
	auto e1 = addEdge(v1, v2, graf);
	auto e2 = addEdge(v1, v4, graf);
	auto e3 = addEdge(v2, v3, graf);
	auto e4 = addEdge(v2, v5, graf);
	auto e5 = addEdge(v6, v7, graf);

	//Testing  
 	std::vector<std::size_t> vs;	
	vs.reserve(numVertices(graf));
	graph::topoSort(graf, std::back_inserter<>(vs));
	std::reverse(vs.begin(), vs.end());
	for (auto iter = vs.begin(); iter != vs.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}
	return 0;
}