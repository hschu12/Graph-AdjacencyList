#ifndef GRAPH_DEPTH_FIRST_SEARCH_HPP
#define GRAPH_DEPTH_FIRST_SEARCH_HPP

#include "traits.hpp"

#include <iostream>

namespace graph {

struct DFSNullVisitor {
	template<typename G, typename V>
	void initVertex(const V&, const G&) { }	

	template<typename G, typename V>
	void startVertex(const V&, const G&) { }	

	template<typename G, typename V>
	void discoverVertex(const V&, const G&) { }	

	template<typename G, typename V>
	void finishVertex(const V& v, const G& g) { 
	}	

	template<typename G, typename E>
	void examineEdge(const E&, const G&) { }	

	template<typename G, typename E>
	void treeEdge(const E&, const G&) { }	

	template<typename G, typename E>
	void backEdge(const E&, const G&) { }	

	template<typename G, typename E>
	void forwardOrCrossEdge(const E&, const G&) { }	

	template<typename G, typename E>
	void finishEdge(const E&, const G&) { }	
};

namespace detail {

enum struct DFSColour {
	White, Grey, Black
};

template<typename Graph, typename Visitor>
void dfsVisit(const Graph &g, Visitor visitor, typename Traits<Graph>::VertexDescriptor u,
		std::vector<DFSColour> &colour) {
    visitor->discoverVertex(u, g);

	colour[u] = DFSColour::Grey;
	auto adjacent = outEdges(u, g);
	for( auto edge = adjacent.begin(); edge != adjacent.end(); ++edge) 
	{

		auto tar = (*edge).tar;

		if (colour[tar] == DFSColour::White) 
		{
			visitor->treeEdge(*edge, g);
			dfsVisit(g, visitor, tar , colour);
		}
		else if (colour[tar] == DFSColour::Grey)
		{
			visitor->backEdge(*edge, g);
		}
		else if (colour[tar] == DFSColour::Black)
		{
			visitor->forwardOrCrossEdge(*edge, g);
		}
	}
	colour[u] = DFSColour::Black;
	visitor->finishVertex(u, g);
}

} // namespace detail

template<typename Graph, typename Visitor>
void dfs(const Graph &g, Visitor visitor) {
	std::vector<detail::DFSColour> colour;
	for( auto vertex = 0; vertex != numVertices(g); ++vertex)
	{
		colour.push_back(detail::DFSColour::White);
		visitor->initVertex(vertex, g);
	}
	for( auto vertex = 0; vertex != numVertices(g); ++vertex)
	{
		if (colour[vertex] == detail::DFSColour::White) 
		{
			visitor->startVertex(vertex, g);
			dfsVisit(g, visitor, vertex, colour);
		}
	}
}

} // namespace graph

#endif // GRAPH_DEPTH_FIRST_SEARCH_HPP
