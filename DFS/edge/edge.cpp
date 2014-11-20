#include <edge/edge.h>

template<typename npl, typename epl>
Edge<npl, epl>::Edge(Node<npl, epl>* previous, Node<npl, epl>* next, epl weight) {
    this->previous = previous;
    this->next = next;
    this->weight = weight;
}
