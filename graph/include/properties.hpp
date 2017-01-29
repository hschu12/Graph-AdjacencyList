#ifndef GRAPH_PROPERTIES_HPP
#define GRAPH_PROPERTIES_HPP

#include <iostream>

namespace graph {

struct NoProp { };

	namespace edgeProp {
		struct Cost { 
			Cost(std::size_t cost) : data(cost) { }
		public:
			std::size_t data;
		};
	} //namespace edgeProp

	namespace vertexProp {

		struct Capacity { 
			Capacity(int cap) : data(cap) { }
		public:
			int data;
		};
	
	} // namespace edgeProp

} // namespace graph

#endif // GRAPH_PROPERTIES_HPP
