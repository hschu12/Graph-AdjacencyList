#ifndef GRAPH_TOPOLOGICAL_SORT_HPP
#define GRAPH_TOPOLOGICAL_SORT_HPP

#include "depth_first_search.hpp"

namespace graph {
namespace detail {

template<typename OutputIterator>
struct TopoVisitor : DFSNullVisitor {
	TopoVisitor(OutputIterator iter) : iter(iter) { }

	// TODO
private:
	OutputItererator iter;
};

} // namespace detail

template<typename Graph, typename OutputIterator>
void topoSort(const Graph &g, OutputIterator oIter) {
	// TODO
}

} // namespace graph

#endif // GRAPH_TOPOLOGICAL_SORT_HPP
