#include <node/node.h>

template<typename npl, typename epl>
Node<npl, epl>::Node(size_t point, npl inf) {
    this->point = point;
    this->inf = inf;
    gTable = new vector<Edge<npl, epl>*>();
}
