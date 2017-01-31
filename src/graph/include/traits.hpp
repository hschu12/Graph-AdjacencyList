#ifndef GRAPH_TRAITS_HPP
#define GRAPH_TRAITS_HPP

#include <type_traits>

// This file is based on boost::graph_traits

namespace graph {
namespace detail {

template<typename T>
struct Voider {
	using type = void;
};

template<typename T>
using Void = void; //typename Voider<T>::type;


#define GRAPH_TRAITS_DEF_MEMBER_OR_VOID(Name) \
	template<typename, typename = void> \
	struct TraitsGetMember_ ## Name { \
		using type = void; \
	}; \
	\
	template<typename T> \
	struct TraitsGetMember_ ## Name <T, detail::Void<typename T::Name> > { \
		using type = typename T::Name; \
	}; \
	\
	template<typename G> \
	struct TraitsMember_ ## Name { \
		using type = typename detail::TraitsGetMember_ ## Name <G>::type; \
	}
GRAPH_TRAITS_DEF_MEMBER_OR_VOID(VertexRange);
GRAPH_TRAITS_DEF_MEMBER_OR_VOID(EdgeRange);
GRAPH_TRAITS_DEF_MEMBER_OR_VOID(OutEdgeRange);
GRAPH_TRAITS_DEF_MEMBER_OR_VOID(InEdgeRange);

#define GRAPH_TRAITS_GET_MEMBER_OR_VOID(Name) \
	using Name = typename detail::TraitsMember_ ## Name <G>::type

#define GRAPH_TRAITS_RANGE(Name) \
	GRAPH_TRAITS_GET_MEMBER_OR_VOID(Name ## Range); \
	using Name ## Iterator = typename detail::TraitsIteratorOrVoid<Name ## Range>::type
	

template<typename T, typename = void>
struct TraitsIteratorOrVoid {
	using type = void;
};

template<typename T>
struct TraitsIteratorOrVoid<T, detail::Void<typename T::iterator> > {
	using type = typename T::iterator;
};

} // namespace detail

template<typename G>
struct Traits {
public: // Graph
	using VertexDescriptor = typename G::VertexDescriptor;
	using EdgeDescriptor = typename G::EdgeDescriptor;
	using DirectedCategory = typename G::DirectedCategory;
public: // VertexListGraph
	GRAPH_TRAITS_RANGE(Vertex);
	GRAPH_TRAITS_RANGE(Edge);
public: // IncidenceGraph
	GRAPH_TRAITS_RANGE(OutEdge);
public: // BidirectionalGraph
	GRAPH_TRAITS_RANGE(InEdge);
};

} // namespace graph

#endif // GRAPH_TRAITS_HPP
