#include "graph.h"

template<typename npl, typename epl>
void Graph<npl, epl>::load(string const &filename) {
    ifstream fin(filename);
    size_t n = 0, m = 0;
    fin >> n >> m;
    npl inf;

    for (size_t i = 0; i < n; i++) {
        fin >> inf;
        this->addNode(inf);
    }
    int x = 0, y = 0;
    epl weight;
    for (size_t i = 0; i < m; i++) {
        fin >> x >> y >> weight;
        this->addEdge(vertex[x - 1], vertex[y - 1], weight);
    }
    fin.close();
}

template<typename npl, typename epl>
void Graph<npl, epl>::save(string const &filename) {
    ofstream fout(filename);
    fout << vertex.size() << " " << edges.size() << endl;
    for (auto &node : vertex) {
        fout << node->getInf() << " ";
    }
    fout << endl;
    for (auto &edge : edges) {
        fout << edge->previous->getPoint() + 1 << " " << edge->next->getPoint() + 1 << " " << edge->getWeight() << endl;
    }
    fout.close();
}

template<typename npl, typename epl>
typename Graph<npl, epl>::NodeHandle Graph<npl, epl>::addNode(npl const &inf) {
    vertex.push_back(new Node<npl, epl>(vertex.size(), inf));
    return vertex[vertex.size() - 1];
}

template<typename npl, typename epl>
void Graph<npl, epl>::addEdge(NodeHandle const &a, NodeHandle const &b, epl const &weight) {
    if (a == b)
        return;

    Edge<npl, epl>* edge1 = new Edge<npl, epl>(a, b, weight);
    Edge<npl, epl>* edge2 = new Edge<npl, epl>(b, a, weight);
    edges.push_back(edge1);
    a->gTable->push_back(edge1);
    b->gTable->push_back(edge2);
}

template<typename npl, typename epl>
size_t Graph<npl, epl>::getNodesCount() const {
    return vertex.size();
}

template<typename npl, typename epl>
npl &Graph<npl, epl>::operator[](NodeHandle const &node) {
    return node->getInf();
}

template<typename npl, typename epl>
void Graph<npl, epl>::forEachNode(function<void(NodeHandle const &)> const &visitor) const {
    for (auto &node : vertex) {
        visitor(node);
    }
}

template<typename npl, typename epl>
void Graph<npl, epl>::forEachEdge(NodeHandle const &source, EdgeVisitor const &visitor) {
    for (auto &edge : (*source->gTable)) {
        visitor(edge);
    }
}

template<typename npl, typename epl>
typename Graph<npl, epl>::NodeHandle Graph<npl, epl>::move(NodeHandle const &origin, EdgeHandle const &edge) {
    return edge->previous == origin ? edge->next : edge->previous;
}

template<typename npl, typename epl>
void Graph<npl, epl>::dfs(NodeVisitor const &startNode, NodeVisitor const &endNode, NodeVisitor const &discoverNode) {
    vector<bool> used(vertex.size());
    for (int i = 0; i < (int) vertex.size(); i++)
        used.push_back(false);
    NodeHandle currentNode;
    for (auto &node : vertex) {
        if (!used[node->getPoint()]) {
            stack<NodeHandle> stack;
            stack.push(node);
            while (!stack.empty()) {
                currentNode = stack.top();
                stack.pop();
                startNode(currentNode);
                for (auto i = vertex[currentNode->getPoint()]->gTable->begin(); i != vertex[currentNode->getPoint()]->gTable->end(); i++) {
                    discoverNode((*i)->next);
                    if (!used[(*i)->next->getPoint()]) {
                        used[(*i)->next->getPoint()] = true;
                        stack.push((*i)->next);
                    }
                }
                endNode(currentNode);
            }
        }
    }

}
