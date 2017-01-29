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
	void finishVertex(const V&, const G&) { }	

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
	// TODO
	colour[u] = DFSColour::Grey;
	auto adjacent = outEdges(u, g);
	for( auto vertex = adjacent.begin(); vertex != adjacent.end(); ++vertex) 
	{
		if (colour[u] == DFSColour::White) 
		{
			visitor->treeEdge(g, visitor);
			//dfsVisit(g, visitor, vertex, colour);
		}
		else if (colour[u] == DFSColour::Grey)
		{
			visitor->backEdge(g, visitor);
			continue;
		}
		else if (colour[u] == DFSColour::Black)
		{
			visitor->forwardOrCrossEdge(g, visitor);
			continue;
		}
	}
	colour[u] = DFSColour::Black;
	visitor->finishVertex(g, visitor);
}

} // namespace detail

template<typename Graph, typename Visitor>
void dfs(const Graph &g, Visitor visitor) {
	// TODO
	std::vector<detail::DFSColour> colour;
	for( auto vertex = 1; vertex != numVertices(g); ++vertex)
	{
		colour.push_back(detail::DFSColour::White);
	}
	for( auto vertex = 1; vertex != numVertices(g); ++vertex)
	{
		if (colour[vertex] == detail::DFSColour::White) 
		{
			dfsVisit(g, visitor, vertex, colour);
		}
	}
}

} // namespace graph

#endif // GRAPH_DEPTH_FIRST_SEARCH_HPP
