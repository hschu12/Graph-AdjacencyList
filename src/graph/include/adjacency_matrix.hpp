#ifndef GRAPH_ADJACENCY_MATRIX_HPP
#define GRAPH_ADJACENCY_MATRIX_HPP

#include "properties.hpp"
#include "tags.hpp"
#include "traits.hpp"

#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <cassert>
#include <vector>

namespace graph {

template<typename VertexData = NoProp, typename EdgeProp = NoProp>
struct AdjacencyMatrix {
private:
	struct StoredEdge {
		bool exists = false;
	};
	using Matrix = std::vector<StoredEdge>;
	using MatrixIterator = typename Matrix::const_iterator;
public: // Graph
	using VertexDescriptor = std::size_t;

	struct EdgeDescriptor {
		std::size_t src, tar;
		bool exist; // so we can represent both edges and non-edges
	};

	using DirectedCategory = tags::Directed;
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
	};
public: // EdgeList
	struct EdgeRange {
		// In the iterator, we want first adapt the MatrixIterator
		// (which iterates through StoredEdges) to give EdgeDescirptors,
		// and then skip those that don't exist in the graph.
		// First: adapt the iterator for the matrix (which is a vector::iterator).
		struct MatrixAdaptorIterator : boost::iterator_adaptor<
				MatrixAdaptorIterator, // because we use CRTP
				MatrixIterator, // the iterator we adapt
				EdgeDescriptor, // we want to convert the StoredEdge into an EdgeDescriptor
				boost::use_default, // let the Boost library figure out the traversal category
				EdgeDescriptor // when we dereference we return by value, not by reference
			> {
			using Base = boost::iterator_adaptor<
				MatrixAdaptorIterator, MatrixIterator, EdgeDescriptor,
				boost::use_default, EdgeDescriptor>;
		public:
			MatrixAdaptorIterator(const MatrixIterator &i, const MatrixIterator &first, std::size_t n)
			: Base(i), first(first), n(n) { }
		private:
			friend class boost::iterator_core_access; // let the Boost machinery use our methods

			EdgeDescriptor dereference() const {
				// get our current position stored in the boost::iterator_adaptor base class
				const MatrixIterator &i = this->base_reference();
				auto idx = i - first;
				auto src = idx / n;
				auto tar = idx % n;
				return EdgeDescriptor{src, tar, i->exists};
			}
		public:
			MatrixIterator first;
			std::size_t n;
		};

		// Now wrap the tracking iterator such that entries without an edge are skipped.
		struct EdgeExistPred {
			bool operator()(const EdgeDescriptor &e) const {
				return e.exist;
			}
		};
		using iterator = boost::filter_iterator<EdgeExistPred, MatrixAdaptorIterator>;
	public:
		EdgeRange(const AdjacencyMatrix *g) : g(g) { }

		iterator begin() const {
			return iterator(
				MatrixAdaptorIterator(g->matrix.begin(), g->matrix.begin(), g->n),
				MatrixAdaptorIterator(g->matrix.end(), g->matrix.begin(), g->n)
			);
		}

		iterator end() const {
			return iterator(
				MatrixAdaptorIterator(g->matrix.end(), g->matrix.begin(), g->n),
				MatrixAdaptorIterator(g->matrix.end(), g->matrix.begin(), g->n)
			);
		}
	private:
		const AdjacencyMatrix *g;
	};
public: // Incidence
	struct OutEdgeRange {
		// we can reuse the EdgeRange::iterator as the out-edges are simply a sub-range of the edges
		using iterator = typename EdgeRange::iterator;
	public:
		OutEdgeRange(VertexDescriptor v, const AdjacencyMatrix &g) : src(v), g(&g) { }

		iterator begin() const {
			auto first = g->matrix.begin() + src * g->n;
			return iterator(
				typename EdgeRange::MatrixAdaptorIterator(first, g->matrix.begin(), g->n),
				typename EdgeRange::MatrixAdaptorIterator(g->matrix.end(), g->matrix.end(), g->n)
			);
		}	
		
		iterator end() const {
			auto last = g->matrix.begin() + (src + 1) * g->n;
			return iterator(
				typename EdgeRange::MatrixAdaptorIterator(last, g->matrix.begin(), g->n),
				typename EdgeRange::MatrixAdaptorIterator(g->matrix.end(), g->matrix.end(), g->n)
			);
		}
	private:
		std::size_t src;
		const AdjacencyMatrix *g;
	};	
public:
	AdjacencyMatrix(std::size_t n)
	: n(n), matrix(n*n) { }
private:
	std::size_t n, m;
	Matrix matrix;
public: // VertexList
	friend std::size_t numVertices(const AdjacencyMatrix &g) {
		return g.n;
	}

	friend VertexRange vertices(const AdjacencyMatrix &g) {
		return VertexRange(g.n);
	}
public: // EdgeList
	friend std::size_t numEdges(const AdjacencyMatrix &g) {
		return g.m;
	}

	friend EdgeRange edges(const AdjacencyMatrix &g) {
		return EdgeRange(&g);
	}
public: // Incidence
	friend VertexDescriptor source(const EdgeDescriptor &e, const AdjacencyMatrix &g) {
		return e.src;
	}

	friend VertexDescriptor target(const EdgeDescriptor &e, const AdjacencyMatrix &g) {
		return e.tar;
	}

	friend std::size_t outDegree(VertexDescriptor v, const AdjacencyMatrix &g) {
		auto oe = outEdges(v, g);
		return std::distance(oe.begin(), oe.end());
	}

	friend OutEdgeRange outEdges(VertexDescriptor v, const AdjacencyMatrix &g) {
		return OutEdgeRange(v, g);
	}
public: // Other
	friend std::size_t getIndex(VertexDescriptor v, const AdjacencyMatrix &g) {
		return v;
	}

	friend EdgeDescriptor addEdge(VertexDescriptor src, VertexDescriptor tar, AdjacencyMatrix &g) {
		if(g.matrix[src * g.n + tar].exists) assert(false);
		++g.m;
		g.matrix[src * g.n + tar].exists = true;
		return EdgeDescriptor{src, tar, true};
	}
};

} // namespace graph

#endif // GRAPH_ADJACENCY_MATRIX_HPP
