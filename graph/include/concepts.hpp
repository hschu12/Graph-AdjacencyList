#ifndef GRAPH_CONCEPTS_HPP
#define GRAPH_CONCEPTS_HPP

#include "tags.hpp"
#include "traits.hpp"

namespace graph {

template<typename R>
concept bool Range = requires(R r) {
	{ r.begin() } -> typename R::iterator;
	{ r.end() } -> typename R::iterator;
};

template<typename G>
concept bool Graph = requires {
	typename Traits<G>::VertexDescriptor;
	typename Traits<G>::EdgeDescriptor;
	typename Traits<G>::DirectedCategory;
} && (
	std::is_convertible<typename Traits<G>::DirectedCategory, tags::Directed>::value
 || std::is_convertible<typename Traits<G>::DirectedCategory, tags::Undirected>::value
);

template<typename G>
concept bool VertexListGraph = Graph<G>
	&& requires(const G &g) {
		typename Traits<G>::VertexRange;
		typename Traits<G>::VertexIterator;
		
	}
	&& std::is_same<
		typename Traits<G>::VertexRange::iterator,
		typename Traits<G>::VertexIterator
	>::value
;

template<typename G>
concept bool EdgeListGraph = Graph<G>
	&& requires(const G &g) {
		typename Traits<G>::EdgeRange;
		typename Traits<G>::EdgeIterator;
		
	}
	&& std::is_same<
		typename Traits<G>::EdgeRange::iterator,
		typename Traits<G>::EdgeIterator
	>::value
;

} // namespace graph

#endif // GRAPH_CONCEPTS_HPP
