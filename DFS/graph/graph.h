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

    //Constructor
    Graph() {
    }

    //Loading from file(FILEFORMAT see at the end of public)
    void load(string const &filename);
    NodeHandle getNodeHandleById(size_t point) const {
        return vertex[point];
    }

    //Saving to file(FILEFORMAT see at the end of public)
    void save(string const &filename);

    //Add new node
    NodeHandle addNode(npl const &);

    //Get the end of edge, starting in this node
    NodeHandle move(NodeHandle const &origin, EdgeHandle const &edge);

    //Get node content
    npl &operator[](NodeHandle const &node);

    //DFS
    void dfs(NodeVisitor const &startNode, NodeVisitor const &endNode, NodeVisitor const &discoverNode);

    //Add new edge
    void addEdge(NodeHandle const &a, NodeHandle const &b, epl const &);

    //Visiting all nodes in graph
    void forEachNode(function<void(NodeHandle const &)> const &visitor) const;

    //Get nodes count
    size_t getNodesCount() const;

    //Visiting all edges in graph that contains source
    void forEachEdge(NodeHandle const &source, EdgeVisitor const &visitor);

    /* FILEFORMAT
     *nodeCount edgeCount
     *1.nodeContent 2.nodeContent ... nodeCount.nodeContent
     *1.nodeIndex 2.nodeIndex edgeWeight
     *  ..
     *  ..
     * (edgeCount)
     *  ..
     *1.nodeIndex 2.nodeIndex edgeWeight
     */
};

#endif // GRAPH_H
