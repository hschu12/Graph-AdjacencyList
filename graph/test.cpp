#include "include/adjacency_list.hpp"
#include "include/adjacency_matrix.hpp"
#include "include/properties.hpp"
#include "include/tags.hpp"
#include "include/depth_first_search.hpp"
#include "include/topological_sort.hpp"
#include <iostream>
int main()
{
	using edgedirections = graph::tags::Directed;
	//using edgedirections = graph::tags::Bidirectional;
	//using edgeProp = graph::NoProp;
	using vertexProp = graph::vertexProp::Capacity;
	using edgeProp = graph::edgeProp::Cost;

	/*graph::AdjacencyMatrix<vertexProp, edgeProp> matrixgraf = graph::AdjacencyMatrix<vertexProp, edgeProp>(4);
	addEdge(1, 2, matrixgraf);
	addEdge(1, 3, matrixgraf);
	addEdge(2, 4, matrixgraf);
	addEdge(2, 3, matrixgraf);
	addEdge(3, 4, matrixgraf);

	std::cout << "Number of vertices (Matrix): " << numVertices(matrixgraf) << std::endl;
	std::cout << "Number of edges (Matix): " << numEdges(matrixgraf) << std::endl;
	std::cout << "Number of outdegree (1: Matrix): " << outDegree(1, matrixgraf) << std::endl;

	std::cout << "" << std::endl;*/

	graph::AdjacencyList<edgedirections> listgrafNoProp = graph::AdjacencyList<edgedirections>(4);
	std::cout << "Number of edges before inserts (list): " << numEdges(listgrafNoProp) << std::endl;
	std::cout << "Number of vertices before inserts (list): " << numVertices(listgrafNoProp) << std::endl;

	auto v1no = addVertex(listgrafNoProp);
	auto v2no = addVertex(listgrafNoProp);
	auto v3no = addVertex(listgrafNoProp);
	auto v4no = addVertex(listgrafNoProp);

	auto e1no = addEdge(v1no, v2no, listgrafNoProp);
	addEdge(v1no, v3no, listgrafNoProp);
	addEdge(v2no, v4no, listgrafNoProp);
	addEdge(v2no, v3no, listgrafNoProp);
	addEdge(v3no, v4no, listgrafNoProp);

	std::cout << "vertex Noprop " << listgrafNoProp[v1no] << std::endl;
	std::cout << "edge Noprop " << listgrafNoProp[e1no] << std::endl;

	
	graph::AdjacencyList<edgedirections, vertexProp, edgeProp> listgraf = graph::AdjacencyList<edgedirections, vertexProp, edgeProp>(4);
	std::cout << "Number of edges (list): " << numEdges(listgraf) << std::endl;
	auto v1 = addVertex(graph::vertexProp::Capacity(4), listgraf);
	auto v2 = addVertex(graph::vertexProp::Capacity(8), listgraf);
	auto v3 = addVertex(graph::vertexProp::Capacity(12), listgraf);
	auto v4 = addVertex(graph::vertexProp::Capacity(16), listgraf);
	std::cout << "Number of vertices (list): " << numVertices(listgraf) << std::endl;

	auto e1 = addEdge(v1, v2, graph::edgeProp::Cost(10), listgraf);
	auto e2 = addEdge(v1, v3, graph::edgeProp::Cost(20), listgraf);
	auto e3 = addEdge(v2, v3, graph::edgeProp::Cost(30), listgraf);
	auto e4 = addEdge(v2, v4, graph::edgeProp::Cost(40), listgraf);
	auto e5 = addEdge(v3, v4, graph::edgeProp::Cost(50), listgraf);

	std::cout << "vertz" << listgraf[v1] << std::endl;
	std::cout << "vertz" << listgraf[v2] << std::endl;
	std::cout << "vertz" << listgraf[v3] << std::endl;
	std::cout << "vertz" << listgraf[v4] << std::endl;

	std::cout << "edge" << listgraf[e1] << std::endl;

/*
	std::cout << "vertz" << listgraf[v1] << std::endl;

	std::cout << "Number of vertices (list): " << numVertices(listgraf) << std::endl;

	std::cout << "Number of edges (list): " << numEdges(listgraf) << std::endl;

	std::cout << "Number of outdegree (1: list): " << outDegree(v1, listgraf) << std::endl;

	std::cout << "Number of indegree (4: list): " << inDegree(v4, listgraf) << std::endl;

	std::cout << "Number of degree (3: list): " << degree(v3, listgraf) << std::endl;

*/
/*	std::vector<std::size_t> vs;	
	vs.reserve(numVertices(listgraf));
	graph::topoSort(listgraf, std::back_inserter(vs));
	std::reverse(vs.begin(), vs.end());
	std::cout << std::distance(vs.begin(), vs.end()) << std::endl;
	for (auto iter = vs.begin(); iter != vs.end(); ++iter)
	{
		std::cout << typeid(iter).name() << std::endl;
	}
*/

	return 0;
}
