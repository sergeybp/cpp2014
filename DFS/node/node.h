#ifndef NODE_H
#define NODE_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <stack>
#include <string>

#define NodePayLoad npl;
#define EdgePayLoad epl;
using namespace std;


template<typename npl, typename epl>
class Edge;


template<typename npl, typename epl>
class Graph;

template<typename npl, typename epl>
class Node {
    friend class Edge<npl, epl>;

    friend class Graph<npl, epl>;

private:
    size_t point;
    vector<Edge<npl, epl>*>* gTable;
    npl inf;
public:

    //Constructor
    Node(size_t, npl);

    //Get node indentificator
    size_t getPoint() const {
        return point;
    }


    //Get all edges, starting in this node
    vector<Edge<npl, epl>*>* getGTable() const {
        return gTable;
    }


    //Get node content
    npl &getInf() {
        return inf;
    }

};


#endif // NODE_H
