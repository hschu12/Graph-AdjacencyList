#ifndef GRAPH_IO_HPP
#define GRAPH_IO_HPP

#include "traits.hpp"

#include <iostream>

namespace graph {

template<typename Graph>
Graph loadDimacs(std::istream &s) {
	auto error = [](auto &&msg) {
		throw std::runtime_error(std::string("Parsing error: ") + msg);
	};
	char cmd;
	if(!(s >> cmd) || cmd != 'p') error("Expected 'p'.");
	std::string edgeKeyword;
	if(!(s >> edgeKeyword) || edgeKeyword != "edge") error("Expected 'edge'.");
	std::size_t n;
	if(!(s >> n)) error("Expected number of vertices.");
	std::size_t m;
	if(!(s >> m)) error("Expected number of edges.");

	Graph g(n);
	using Vertex = typename graph::Traits<Graph>::VertexDescriptor;
	using Edge = typename graph::Traits<Graph>::EdgeDescriptor;

	for(std::size_t i = 1; i <= m; ++i) {
		if(!(s >> cmd) || cmd != 'e') error("Expected 'e' for edge " + std::to_string(i) + ".");
		std::size_t src, tar;
		if(!(s >> src >> tar)) error("Expected source and target for edge " + std::to_string(i) + ".");
		if(src == 0 || src > n) error("Source " + std::to_string(src) + " for edge " + std::to_string(i) + " is out of bounds.");
		if(tar == 0 || tar > n) error("Target " + std::to_string(tar) + " for edge " + std::to_string(i) + " is out of bounds.");
		addEdge(src - 1, tar - 1, g);
	}
	return g;
}

template<typename Graph, typename VertexPrinter, typename EdgePrinter>
std::ostream &printDot(std::ostream &s, const Graph &g, VertexPrinter vPrinter, EdgePrinter ePrinter) {
	s << "digraph g {\n";
	for(auto v : vertices(g)) {
		s << getIndex(v, g) << " [";
		vPrinter(s, v, g);
		s << "];\n";
	}
	for(auto e : edges(g)) {
		s << getIndex(source(e, g), g) << " -> " << getIndex(target(e, g), g);
		s << " [";
		ePrinter(s, e, g);
		s << "];\n";
	}
	s << "}\n";
	return s;
}

template<typename Graph>
std::ostream &printDot(std::ostream &s, const Graph &g) {
	return printDot(s, g, [](auto&&...) {}, [](auto&&...) {});
}

} // namespace graph

#endif // GRAPH_IO_HPP
