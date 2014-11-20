#include "gtest/gtest.h"

#include "graph/graph.cpp"
#include "node/node.cpp"
#include "edge/edge.cpp"

using namespace std;


namespace {
    int n = 1000;
    int n_max = 1000000000;
    vector<int> num;
    int thisPoint;
    vector<int> points;
    bool flag;
    Graph<int, int>::NodeHandle currentNode;
    Graph<int, int> graph,graph1;
    Graph<float,float> fGraph;



    void edgeV(Graph<int, int>::EdgeHandle const &edge) {
        num.push_back(graph[edge->getPrevious() == currentNode ? edge->getNext() : edge->getPrevious()]);
    }


    void myV(Graph<int, int>::NodeHandle const &source) {
        num.clear();
        currentNode = source;
        graph.forEachEdge(source, edgeV);
    }

    void edgeV1(Graph<int, int>::EdgeHandle const &edge) {
            EXPECT_EQ(edge->getPrevious(), graph.move(edge->getNext(), edge));
            EXPECT_EQ(edge->getNext(), graph.move(edge->getPrevious(), edge));
        }

        void nodeVisitor(Graph<int, int>::NodeHandle const &source) {
            graph.forEachEdge(source, edgeV1);
        }

        void startNode(Graph<int, int>::NodeHandle const &source) {
            points[source->getPoint()] == n_max ? (points[source->getPoint()] = thisPoint) : (thisPoint = points[source->getPoint()]);
        }

        void discoverNode(Graph<int, int>::NodeHandle const &source) {
            if (points[source->getPoint()] == n_max) {
                points[source->getPoint()] = (thisPoint + 1) % 2;
            }
            else if (points[source->getPoint()] == thisPoint) {
                flag = false;
            }
        }

        void endNode(Graph<int, int>::NodeHandle const &source) {
            thisPoint = n_max;
        }

        bool myCheck() {
            thisPoint = 0;
            for (size_t i = 0; i < graph.getNodesCount(); i++) {
                points.push_back(n_max);
            }
            flag = true;
            graph.dfs(startNode, endNode, discoverNode);
            return flag;
        }
}

TEST(myGraphCheck, addingNodes) {
    int check = 999;
    fGraph = Graph<float, float>();
    for (int i = 0; i < check; i++)
        graph.addNode((i+2)*673/111);
    EXPECT_EQ(check, (int) graph.getNodesCount());
}

TEST(myGraphCheck, makingFullGraph) {
    graph = Graph<int, int>();
    int time = clock();
    for (int i = 0; i < n; i++) {
        graph.addNode(i);
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            graph.addEdge(graph.getNodeHandleById(i), graph.getNodeHandleById(j), 0);
        }
    }
    cout << clock() - time << endl;
    EXPECT_EQ(n, (int) graph.getNodesCount());
    graph.forEachNode(myV);
}

TEST(myGraphCheck, dfsTesting) {
    graph = Graph<int, int>();
    Graph<int, int>::NodeHandle current;
    Graph<int, int>::NodeHandle prev;
    prev = graph.addNode(0);
    n = 50;
    for (int i = 0; i < n - 1; i++) {
        current = graph.addNode(0);
        graph.addEdge(current, prev, 0);
        prev = current;
    }
    EXPECT_EQ(true, myCheck());
}

TEST(myGraphCheck, inOutFileTest) {
    graph = Graph<int, int>();
    //50 - to test faster
    n = 50;
    for (int i = 0; i < n; i++) {
        graph.addNode(i);
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            graph.addEdge(graph.getNodeHandleById(i), graph.getNodeHandleById(j), 0);
        }
    }
    graph.save("out.txt");
    graph1 = Graph<int,int>();
    graph1.load("out.txt");
    EXPECT_EQ(n, (int) graph1.getNodesCount());
    graph.forEachNode(myV);
}






