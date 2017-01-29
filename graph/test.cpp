#include "include/adjacency_list.hpp"
#include "include/adjacency_matrix.hpp"
#include "include/properties.hpp"
#include "include/tags.hpp"
#include "include/depth_first_search.hpp"
#include <iostream>
int main()
{
	using edgedirections = graph::tags::Directed;
	//using edgedirections = graph::tags::Bidirectional;
	//using edgeProp = graph::NoProp;
	using vertexProp = graph::vertexProp::Capacity;
	using edgeProp = graph::edgeProp::Cost;

	graph::AdjacencyMatrix<vertexProp, edgeProp> matrixgraf = graph::AdjacencyMatrix<vertexProp, edgeProp>(4);
	addEdge(1, 2, matrixgraf);
	addEdge(1, 3, matrixgraf);
	addEdge(2, 4, matrixgraf);
	addEdge(2, 3, matrixgraf);
	addEdge(3, 4, matrixgraf);

	std::cout << "Number of vertices (Matrix): " << numVertices(matrixgraf) << std::endl;
	std::cout << "Number of edges (Matix): " << numEdges(matrixgraf) << std::endl;
	std::cout << "Number of outdegree (1: Matrix): " << outDegree(1, matrixgraf) << std::endl;

	std::cout << "" << std::endl;

	graph::AdjacencyList<edgedirections> listgraf = graph::AdjacencyList<edgedirections>(4);
	std::cout << "Number of edges before inserts (list): " << numEdges(listgraf) << std::endl;
	std::cout << "Number of vertices before inserts (list): " << numVertices(listgraf) << std::endl;

	auto v1 = addVertex(listgraf);
	auto v2 = addVertex(listgraf);
	auto v3 = addVertex(listgraf);
	auto v4 = addVertex(listgraf);

	addEdge(v1, v2, listgraf);
	addEdge(v1, v3, listgraf);
	addEdge(v2, v4, listgraf);
	addEdge(v2, v3, listgraf);
	addEdge(v3, v4, listgraf);

	/*
	graph::AdjacencyList<edgedirections, vertexProp, edgeProp> listgraf = graph::AdjacencyList<edgedirections, vertexProp, edgeProp>(4);
	std::cout << "Number of edges (list): " << numEdges(listgraf) << std::endl;
	auto e = addEdge(1, 2,  graph::edgeProp::Cost(2), listgraf);
	std::cout << listgraf[e] << std::endl;
	auto v1 = addVertex(graph::vertexProp::Capacity(4), listgraf);
	auto v2 = addVertex(graph::vertexProp::Capacity(8), listgraf);
	std::cout << "Number of vertices (list): " << numVertices(listgraf) << std::endl;

	auto e2 = addEdge(v1, v2, graph::edgeProp::Cost(22), listgraf);
	auto v3 = addVertex(graph::vertexProp::Capacity(12), listgraf);
	auto v4 = addVertex(graph::vertexProp::Capacity(16), listgraf);*/

	/*std::cout << "vertz" << listgraf[v1] << std::endl;
	std::cout << "vertz" << listgraf[v2] << std::endl;
	std::cout << "vertz" << listgraf[v3] << std::endl;
	std::cout << "vertz" << listgraf[v4] << std::endl;

	std::cout << "vertz" << listgraf[v1] << std::endl;*/

	std::cout << "Number of vertices (list): " << numVertices(listgraf) << std::endl;

	std::cout << "Number of edges (list): " << numEdges(listgraf) << std::endl;

	std::cout << "Number of outdegree (1: list): " << outDegree(v1, listgraf) << std::endl;

	std::cout << "Number of indegree (4: list): " << inDegree(v4, listgraf) << std::endl;

	std::cout << "Number of degree (3: list): " << degree(v3, listgraf) << std::endl;

	graph::DFSNullVisitor *visitor = new graph::DFSNullVisitor();



	//dfs(listgraf, visitor);

	return 0;
}
