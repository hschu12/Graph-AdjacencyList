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

	//Testing Insert of Edges and Vertices
	std::cout << "Number of edges before inserts: " << numEdges(graf) << std::endl;
	std::cout << "Number of vertices before inserts: " << numVertices(graf) << std::endl;

	auto v1 = addVertex(graph::vertexProp::Capacity(4), graf);
	auto v2 = addVertex(graph::vertexProp::Capacity(8), graf);
	auto v3 = addVertex(graph::vertexProp::Capacity(12), graf);
	auto v4 = addVertex(graph::vertexProp::Capacity(16), graf);

	auto e1 = addEdge(v1, v2, graph::edgeProp::Cost(10), graf);
	auto e2 = addEdge(v1, v3, graph::edgeProp::Cost(20), graf);
	auto e3 = addEdge(v2, v3, graph::edgeProp::Cost(30), graf);
	auto e4 = addEdge(v2, v4, graph::edgeProp::Cost(40), graf);
	auto e5 = addEdge(v3, v4, graph::edgeProp::Cost(50), graf);

	std::cout << "Number of edges after inserts: " << numEdges(graf) << std::endl;
	std::cout << "Number of vertices after inserts: " << numVertices(graf) << std::endl;

	//Testing outDegree
	std::cout << "Outdegree of v1: " << outDegree(v1,graf) << std::endl;
	std::cout << "Outdegree of v2: " << outDegree(v2,graf) << std::endl;
	std::cout << "Outdegree of v3: " << outDegree(v3,graf) << std::endl;
	std::cout << "Outdegree of v4: " << outDegree(v4,graf) << std::endl;

	//Testing inDegree
	std::cout << "Indegree of v1: " << inDegree(v1,graf) << std::endl;
	std::cout << "Indegree of v2: " << inDegree(v2,graf) << std::endl;
	std::cout << "Indegree of v3: " << inDegree(v3,graf) << std::endl;
	std::cout << "Indegree of v4: " << inDegree(v4,graf) << std::endl;

	//Testing degree
	std::cout << "Degree of v1: " << degree(v1,graf) << std::endl;
	std::cout << "Degree of v2: " << degree(v2,graf) << std::endl;
	std::cout << "Degree of v3: " << degree(v3,graf) << std::endl;
	std::cout << "Degree of v4: " << degree(v4,graf) << std::endl;

	//Testing source and target
	std::cout << "Source of edge (e1): " << source(e1, graf) << std::endl;
	std::cout << "Target of edge (e1): " << target(e1, graf) << std::endl;

	//Testing getIndex
	std::cout << "Index of v1: " << getIndex(v1, graf) << std::endl;

	//Testing []overload
	std::cout << "vertexProp of v1: " << graf[v1] << std::endl;
	std::cout << "vertexProp of v2: " << graf[v2] << std::endl;
	std::cout << "vertexProp of v3: " << graf[v3] << std::endl;
	std::cout << "vertexProp of v4: " << graf[v4] << std::endl;

	std::cout << "edgeProp of e1: " << graf[e1] << std::endl;
	std::cout << "edgeProp of e2: " << graf[e2] << std::endl;
	std::cout << "edgeProp of e3: " << graf[e3] << std::endl;
	std::cout << "edgeProp of e4: " << graf[e4] << std::endl;
	std::cout << "edgeProp of e5: " << graf[e5] << std::endl;

	return 0;
}