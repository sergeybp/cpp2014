#ifndef GRAPH_H
#define GRAPH_H


#include<node/node.h>
#include<edge/edge.h>

#include <vector>
#include <fstream>
#include <string>


#define NodePayLoad npl;
#define EdgePayLoad epl;
using namespace std;

template<typename npl, typename epl>
class Edge;


template<typename npl, typename epl>
class Graph;

template<typename npl, typename epl>
class Node;


template<typename npl, typename epl>
class Graph {
    friend class Node<npl, epl>;

    friend class Edge<npl, epl>;

public:
    typedef Node<npl, epl>* NodeHandle;
    typedef Edge<npl, epl>* EdgeHandle;
    typedef function<void(NodeHandle const &)> NodeVisitor;
    typedef function<void(EdgeHandle const &)> EdgeVisitor;
private:
    vector<NodeHandle> vertex;
    vector<EdgeHandle> edges;
public:
    Graph() {
    }
    void load(string const &filename);
    NodeHandle getNodeHandleById(size_t point) const {
        return vertex[point];
    }
    void save(string const &filename);
    NodeHandle addNode(npl const &);
    NodeHandle move(NodeHandle const &origin, EdgeHandle const &edge);
    npl &operator[](NodeHandle const &node);
    void dfs(NodeVisitor const &startNode, NodeVisitor const &endNode, NodeVisitor const &discoverNode);
    void addEdge(NodeHandle const &a, NodeHandle const &b, epl const &);
    void forEachNode(function<void(NodeHandle const &)> const &visitor) const;
    size_t getNodesCount() const;
    void forEachEdge(NodeHandle const &source, EdgeVisitor const &visitor);
};

#endif // GRAPH_H
