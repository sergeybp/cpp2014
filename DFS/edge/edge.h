#ifndef EDGE_H
#define EDGE_H


#include <vector>
#include <fstream>
#include <string>

#define NodePayLoad npl;
#define EdgePayLoad epl;
using namespace std;


template<typename npl, typename epl>
class Graph;

template<typename npl, typename epl>
class Node;

template<typename npl, typename epl>
class Edge {
    friend class Graph<npl, epl>;

private:
    Node<npl, epl>* previous;
    Node<npl, epl>* next;
    epl weight;
public:

    //Constructor
    Edge(Node<npl, epl>*, Node<npl, epl>*, epl);

    //Get previous node(this edge starts there)
    Node<npl, epl>* getPrevious() const {
        return previous;
    }

    //Get next node(this edge finishes there)
    Node<npl, epl>* getNext() const {
        return next;
    }

    //Get edge's weight
    epl getWeight() const {
        return weight;
    }

    //Check if 2 nodes are connected by this edge
    bool connects(Node<npl, epl>* node1, Node<npl, epl>* node2) const {
        return ((node1 == this->previous && node2 == this->next) || (node1 == this->next && node2 == this->previous));
    }
};

#endif // EDGE_H
