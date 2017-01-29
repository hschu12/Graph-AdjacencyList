#ifndef GRAPH_TAGS_HPP
#define GRAPH_TAGS_HPP

namespace graph {
namespace tags {

struct Undirected { };
struct Directed { };
struct Bidirectional : Directed { };

} // namespace tags
} // namespace graphs

#endif // GRAPH_TAGS_HPP
