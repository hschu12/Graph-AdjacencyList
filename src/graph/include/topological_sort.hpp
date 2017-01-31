#ifndef GRAPH_TOPOLOGICAL_SORT_HPP
#define GRAPH_TOPOLOGICAL_SORT_HPP

#include "depth_first_search.hpp"
#include <iostream>

namespace graph {
namespace detail {

template<typename OutputIterator>
struct TopoVisitor : DFSNullVisitor {
	TopoVisitor(OutputIterator iter) : iter(iter) { }

	template<typename G, typename V>
	void finishVertex(const V& v, const G& g) { 
		auto vertex = v+1;
		iter = vertex;
	}	

private:
	OutputIterator iter;
};

} // namespace detail

template<typename Graph, typename OutputIterator>
void topoSort(const Graph &g, OutputIterator oIter) {
	detail::TopoVisitor<OutputIterator> *vis = new detail::TopoVisitor<OutputIterator>(oIter);
	dfs(g,vis);
}

} // namespace graph

#endif // GRAPH_TOPOLOGICAL_SORT_HPP
