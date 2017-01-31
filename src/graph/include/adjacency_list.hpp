#ifndef GRAPH_ADJACENCY_LIST_HPP
#define GRAPH_ADJACENCY_LIST_HPP

#include "tags.hpp"
#include "properties.hpp"
#include "traits.hpp"

#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <cassert>
#include <list>
#include <vector>
#include <iostream>

namespace graph {

template<typename DirectedTag, typename VertexProp = NoProp, typename EdgeProp = NoProp>
struct AdjacencyList {
private:
	struct OutEdge {
	}; //OutEdge END

	using OutEdgeList = std::vector<OutEdge>;

	struct StoredVertexSimple {
		StoredVertexSimple() {}

		StoredVertexSimple(VertexProp vp) : vp(vp) {}

		VertexProp vp;
		OutEdgeList eOut;
	}; //StoredVertexSimple END

	using StoredVertex = StoredVertexSimple;

	struct StoredEdge {
		StoredEdge(std::size_t src, std::size_t tar) : src(src), tar(tar) { }

		StoredEdge(std::size_t src, std::size_t tar, EdgeProp ep) : src(src), tar(tar), ep(ep) { } 
	public:
		std::size_t src, tar;
		EdgeProp ep;
	}; //StoredEdge END

	using VList = std::vector<StoredVertex>;
	using EList = std::vector<StoredEdge>;
public: // Graph
	using VertexDescriptor = std::size_t;

	struct EdgeDescriptor {
		std::size_t src, tar;
		EdgeProp ep;
	}; // EdgeDescriptor END

	using DirectedCategory = DirectedTag;
public: // VertexList
	struct VertexRange {
		// the iterator is simply a counter that returns its value when dereferenced
		using iterator = boost::counting_iterator<VertexDescriptor>;
	public:
		VertexRange(std::size_t n) : n(n) { }

		iterator begin() const {
			return iterator(0);
		}

		iterator end() const {
			return iterator(n);
		}
	private:
		std::size_t n;
	}; // VertexRange END

public: // EdgeList
	struct EdgeRange {
		// We want to adapt the edge list, so it dereferences to EdgeDescriptor instead of StoredEdge
		using EListIterator = typename EList::const_iterator;

		struct iterator : boost::iterator_adaptor<
				iterator, // because we use CRTP
				EListIterator, // the iterator we adapt
				EdgeDescriptor, // we want to convert the StoredEdge into an EdgeDescriptor
				boost::use_default, // let the Boost library figure out the traversal category
				EdgeDescriptor // when we dereference we return by value, not by reference
			> {
			using Base = boost::iterator_adaptor<
				iterator, EListIterator, EdgeDescriptor,
				boost::use_default, EdgeDescriptor>;
		public:
			iterator(EListIterator i) : Base(i) { }
		private:
			friend class boost::iterator_core_access; // let the Boost machinery use our methods

			EdgeDescriptor dereference() const {
				// get our current position stored in the boost::iterator_adaptor base class
				const EListIterator &i = this->base_reference();
				return EdgeDescriptor{i->src, i->tar};
			}
		}; // iterator END

	public:
		EdgeRange(const AdjacencyList &g) : g(&g) { }

		iterator begin() const {
			return iterator(g->eList.begin());
		}

		iterator end() const {
			return iterator(g->eList.end());
		}
	private:
		const AdjacencyList *g;
	}; //EdgeList END

public: // Incidence
	struct OutEdgeRange {
		// we can reuse the EdgeRange::iterator as the out-edges are simply a sub-range of the edges
		using iterator = typename EdgeRange::iterator;
	public:
		OutEdgeRange(VertexDescriptor v, const AdjacencyList &g) : src(v), g(&g) { }

		iterator begin() const {
			std::vector<StoredEdge> oe;

			for (auto it = g->eList.begin(); it != g->eList.end(); ++it)
			{	
				if(it->src == src) 
				{
					oe.push_back(*it);
				}
			}
			return iterator(
				typename EdgeRange::iterator(oe.begin()));
		}	
		
		iterator end() const {
			std::vector<StoredEdge> oe;
			for (auto it = g->eList.begin(); it != g->eList.end(); ++it)
			{	
				if(it->src == src) 
				{
					oe.push_back(*it);
				}
			}		
			return iterator(
				typename EdgeRange::iterator(oe.end())
			);
		}
	private:
		std::size_t src;
		const AdjacencyList *g;
	};	//OutEdgeRange END

public: // Bidirectional 1d
	struct InEdgeRange {
		// we can reuse the EdgeRange::iterator as the in-edges are simply a sub-range of the edges
		using iterator = typename EdgeRange::iterator;
	public:
		InEdgeRange(VertexDescriptor v, const AdjacencyList &g) : src(v), g(&g) { }

		iterator begin() const {
			std::vector<StoredEdge> ie;

			for (auto it = g->eList.begin(); it != g->eList.end(); ++it)
			{	
				if(it->tar == src) 
				{
					ie.push_back(*it);
				}
			}
			return iterator(
				typename EdgeRange::iterator(ie.begin()));
		}	
		
		iterator end() const {
			std::vector<StoredEdge> ie;
			for (auto it = g->eList.begin(); it != g->eList.end(); ++it)
			{	
				if(it->tar == src) 
				{
					ie.push_back(*it);
				}
			}		
			return iterator(
				typename EdgeRange::iterator(ie.end())
			);
		}
	private:
		std::size_t src;
		const AdjacencyList *g;
	}; //InEdgeRange END
public:
	AdjacencyList(std::size_t n) : vList(n) { }
private:
	VList vList;
	EList eList;
	int index = 0;

public:

	template <typename U = EdgeProp, typename std::enable_if<std::is_same<U, edgeProp::Cost>::value>::type* =nullptr>
	int operator[](const EdgeDescriptor e) {
		for (auto iter = eList.begin(); iter != eList.end(); ++iter)
		{
			if(iter->src == e.src && iter->tar == e.tar)
			{
				return iter->ep.data;
			}
		}
		return 0;
	}

	template <typename U = EdgeProp, typename std::enable_if<std::is_same<U, NoProp>::value>::type* =nullptr>
	int operator[](const EdgeDescriptor e) {
		return 0;
	}

	template <typename U = VertexProp, typename std::enable_if<std::is_same<U, vertexProp::Capacity>::value>::type* =nullptr>
	int operator[](const VertexDescriptor v) {
		return vList[v].vp.data;
	}

	template <typename U = VertexProp, typename std::enable_if<std::is_same<U, NoProp>::value>::type* =nullptr>
	int operator[](const VertexDescriptor v) {
		return 0;
	}

public: // VertexList
	friend std::size_t numVertices(const AdjacencyList &g) {
		return g.index;
	}

	friend VertexRange vertices(const AdjacencyList &g) {
		return VertexRange(numVertices(g));
	}
public: // EdgeList
	friend std::size_t numEdges(const AdjacencyList &g) {
		return g.eList.size();
	}

	friend EdgeRange edges(const AdjacencyList &g) {
		return EdgeRange(g);
	}

public: // Incidence
	friend VertexDescriptor source(const EdgeDescriptor &e, const AdjacencyList &g) {
		return e.src+1;
	}

	friend VertexDescriptor target(const EdgeDescriptor &e, const AdjacencyList &g) {
		return e.tar+1;
	}

	friend std::size_t outDegree(VertexDescriptor v, const AdjacencyList &g) {
		auto oe = outEdges(v,g);
		return std::distance(oe.begin(), oe.end());
	}

	friend OutEdgeRange outEdges(VertexDescriptor v, const AdjacencyList &g) {
		return OutEdgeRange(v, g);
	}

	friend std::size_t inDegree(VertexDescriptor v, const AdjacencyList &g) {
		auto ie = inEdges(v,g);
		return std::distance(ie.begin(), ie.end());
	}

	friend InEdgeRange inEdges(VertexDescriptor v, const AdjacencyList &g) {
		return InEdgeRange(v, g);
	}

	friend std::size_t degree(VertexDescriptor v, const AdjacencyList &g) {
		return inDegree(v, g) + outDegree(v,g);
	} 

public: // Other
	friend std::size_t getIndex(VertexDescriptor v, const AdjacencyList &g) {
		return v;
	}

	//addEdge NoProp
	template <typename U = DirectedTag, typename std::enable_if<std::is_same<U, tags::Bidirectional>::value>::type* =nullptr>
	friend EdgeDescriptor addEdge(VertexDescriptor src, VertexDescriptor tar, AdjacencyList &g) {
		if (src > g.vList.size() || tar > g.vList.size()) //Is Both vertices existing
		{
			std::cout << "Max vertex is: " << g.vList.size() << ". Either target(" << tar+1 << ") or source(" << src+1 << ") node not existing!" << std::endl;
			assert(false); 
		} 
		if (src == tar)  // is the source and target vertex the same?
		{
			std::cout << "Source (" << src+1 << ") and target (" << tar+1 << ") vertex is the same. Not allowed!" << std::endl;
			assert(false);
		}
		//already exists?
		for (auto it = g.eList.begin(); it != g.eList.end(); ++it)
		{
			if(it->src == src && it->tar == tar) 
			{
				std::cout << "Edge: (" << src+1 << "," << tar+1 << ") already exists!" << std::endl;
				assert(false);
			}
			if(it->src == tar && it->tar == src)
			{
				std::cout << "Edge: (" << src+1 << "," << tar+1 << ") already exists!" << std::endl;
				assert(false);
			}
		}
		StoredEdge *se1 = new StoredEdge(tar, src);
		StoredEdge *se2 = new StoredEdge(src, tar);
		g.eList.push_back(*se1);
		g.eList.push_back(*se2);
		return EdgeDescriptor{src, tar};
	}

	//addEdge EdgeProp
	template <typename U = DirectedTag, typename std::enable_if<std::is_same<U, tags::Bidirectional>::value>::type* =nullptr>
	friend EdgeDescriptor addEdge(VertexDescriptor src, VertexDescriptor tar, EdgeProp ep, AdjacencyList &g) {
		if (src > g.vList.size() || tar > g.vList.size()) //Is Both vertices existing
		{
			std::cout << "Max vertex is: " << g.vList.size() << ". Either target(" << tar+1 << ") or source(" << src+1 << ") node not existing!" << std::endl;
			assert(false); 
		} 
		if (src == tar)  // is the source and target vertex the same?
		{
			std::cout << "Source (" << src+1 << ") and target (" << tar+1 << ") vertex is the same. Not allowed!" << std::endl;
			assert(false);
		}
		//already exists?
		for (auto it = g.eList.begin(); it != g.eList.end(); ++it)
		{
			if(it->src == src && it->tar == tar) 
			{
				std::cout << "Edge: (" << src+1 << "," << tar+1 << ") already exists!" << std::endl;
				assert(false);
			}
			if(it->src == tar && it->tar == src)
			{
				std::cout << "Edge: (" << src+1 << "," << tar+1 << ") already exists!" << std::endl;
				assert(false);
			}
		}
		StoredEdge *se1 = new StoredEdge(tar, src, ep);
		StoredEdge *se2 = new StoredEdge(src, tar, ep);
		g.eList.push_back(*se1);
		g.eList.push_back(*se2);
		return EdgeDescriptor{src, tar, ep};
	}
  
  	//NoProp
	template <typename U = DirectedTag, typename std::enable_if<std::is_same<U, tags::Directed>::value>::type* = nullptr>
	friend EdgeDescriptor addEdge(VertexDescriptor src, VertexDescriptor tar, AdjacencyList &g) {
		if (src > g.vList.size() || tar > g.vList.size()) //Is Both vertices existing
		{
			std::cout << "Max vertex is: " << g.vList.size() << ". Either target(" << tar+1 << ") or source(" << src+1 << ") node not existing!" << std::endl;
			assert(false); 
		} 
		if (src == tar)  // is the source and target vertex the same?
		{
			std::cout << "Source (" << src+1 << ") and target (" << tar+1 << ") vertex is the same. Not allowed!" << std::endl;
			assert(false);
		}
		//already exists?
		for (auto it = g.eList.begin(); it != g.eList.end(); ++it)
		{
			if(it->src == src && it->tar == tar) 
			{
				std::cout << "Edge: (" << src+1 << "," << tar+1 << ") already exists!" << std::endl;
				assert(false);
			}
		}
		StoredEdge *se = new StoredEdge(src, tar);
		g.eList.push_back(*se);
		return EdgeDescriptor{src, tar};
	}

	//EdgeProp
	template <typename U = DirectedTag, typename std::enable_if<std::is_same<U, tags::Directed>::value>::type* =nullptr>
	friend EdgeDescriptor addEdge(VertexDescriptor src, VertexDescriptor tar, EdgeProp ep, AdjacencyList &g) {
		if (src > g.vList.size() || tar > g.vList.size()) //Is Both vertices existing
		{
			std::cout << "Max vertex is: " << g.vList.size() << ". Either target(" << tar+1 << ") or source(" << src+1 << ") node not existing!" << std::endl;
			assert(false); 
		} 
		if (src == tar)  // is the source and target vertex the same?
		{
			std::cout << "Source (" << src+1 << ") and target (" << tar+1 << ") vertex is the same. Not allowed!" << std::endl;
			assert(false);
		}
		//already exists?
		for (auto it = g.eList.begin(); it != g.eList.end(); ++it)
		{
			if(it->src == src && it->tar == tar) 
			{
				std::cout << "Edge: (" << src+1 << "," << tar+1 << ") already exists!" << std::endl;
				assert(false);
			}
		}
		StoredEdge *se = new StoredEdge(src, tar, ep);
		g.eList.push_back(*se);
		return EdgeDescriptor{src, tar, ep};
	}
	
	friend VertexDescriptor addVertex(AdjacencyList &g) {
		if (g.index >= g.vList.size()) {
			std::cout << "Cant add more than " << g.vList.size() << " vertices!" << std::endl;
			assert(false);
		}
		VertexDescriptor v = g.index;
		g.index++;
		return v;
	}

	friend VertexDescriptor addVertex(VertexProp vp, AdjacencyList &g) {
		if (g.index >= g.vList.size()) {
			std::cout << "Cant add more than " << g.vList.size() << " vertices!" << std::endl;
			assert(false);
		}
		VertexDescriptor v = g.index;
		g.vList[v].vp = vp;
		g.index++;
		return v;
	}
};

} // namespace graph

#endif // GRAPH_ADJACENCY_LIST_HPP
