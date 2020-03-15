/**
 * Authors: Matthew Lund and Mohammad Javid
 * Contact info: mtlund@ucsd.edu (Matthew),
 *               Msamadpo@ucsd.edu (Mohammad)
 *
 * Sources used:
 *  1) Stepik: Introduction to Data Structures (Fall 2016)
 *     by Moshiri and Izhikevich (available at stepik.org)
 *
 * Description of File:
 *  This file defines the neccessary methods to create a
 *  graph of nodes and their respective edges. It also
 *  features implementations of various traversals to
 *  move around and find properties of the graph.
 */

#include "Map.hpp"
#include <algorithm>
#include <queue>
#include <set>
#include <stack>

struct compare {
    bool operator()(Vertex* v1, Vertex* v2) {
        // Returns the smalles distance
        if (v1->distance != v2->distance) {
            return v1->distance > v2->distance;
        }
        // Returns the string in alphabetical order.
        return v1->name > v2->name;
    }
};

struct edgeCompare {
    bool operator()(Edge* e1, Edge* e2) {
        // Returns the smallest weight
        if (e1->weight != e2->weight) {
            return e1->weight > e2->weight;
        }
        // Returns the string in alphabetical order
        return e1->target->name > e2->target->name;
    }
};

typedef std::priority_queue<Vertex*, std::vector<Vertex*>, compare>
    edge_min_heap;

typedef std::priority_queue<Edge*, std::vector<Edge*>, edgeCompare>
    edges_min_heap;

/*
 * This is the contructor method for the graph.
 * Its purpose is to initialize the necessary
 * instance variables to make a graph.
 *
 * Parameters:
 *  NONE
 *
 */
Map::Map() {}

/* Build the map graph from vertex and edge files */
bool Map::buildMapFromFile(const string& vertexFileName,
                           const string& edgeFileName) {
    // add vertices first
    ifstream vertexFile(vertexFileName);
    while (vertexFile) {
        string s;
        if (!getline(vertexFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 3) continue;

        // add vertex defined in this line to the graph
        string name(data[0]);
        float x = stoi(data[1]);
        float y = stoi(data[2]);

        addVertex(name, x, y);
    }

    // then add edges
    ifstream edgeFile(edgeFileName);
    while (edgeFile) {
        string s;
        if (!getline(edgeFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 2) continue;

        // add edge defined in this line to the graph
        string name1(data[0]);
        string name2(data[1]);

        addEdge(name1, name2);
    }

    return true;
}

/*
 * Add a vertex with name and x, y coordinates to the map graph. Returns
 * false if the name already existed in the map graph, and true otherwise
 */
bool Map::addVertex(const string& name, float x, float y) {
    if (vertexId.count(name) > 0) return false;
    vertexId[name] = vertices.size();
    vertices.push_back(new Vertex(name, x, y));
    return true;
}

/*
 * Add an undirected edge between vertices with names "name1" and "name2".
 * Returns false if either name is not in the map graph.
 */
bool Map::addEdge(const string& name1, const string& name2) {
    if (vertexId.count(name1) == 0 || vertexId.count(name2) == 0) {
        return false;
    }
    unsigned int id1 = vertexId[name1];
    unsigned int id2 = vertexId[name2];
    Vertex* v1 = vertices[id1];
    Vertex* v2 = vertices[id2];
    float weight = sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2));
    v1->outEdges.push_back(new Edge(v1, v2, weight));
    v2->outEdges.push_back(new Edge(v2, v1, weight));

    undirectedEdges.push_back(new Edge(v1, v2, weight));
    return true;
}

/*
 * This method reads in the name of two actors
 * and tries to find a valid path between them.
 * If multiple paths exist, it chooses the
 * one with the smalles cost or total weight.
 *
 * Parameters:
 *  1) fromActor - The vertex from which to start
 *  2) toActor - The vertex we want to end at
 *  3) shortestPath - The vector containing the
 *                    nodes that make up the path.
 *
 * Sources used:
 *  1) CSE 100 Lecture slides
 *
 *  2) Stepik: Introduction to Data Structures (Fall 2016)
 *     by Moshiri and Izhikevich (available at stepik.org)
 *     Section: 4.5 - Step 4
 *
 * Edge Cases:
 *  1) The actors do not exists - return
 *  2) The input is empty - return
 *
 */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
    // If string of input are empty.
    if (from.size() == 0 || to.size() == 0) {
        return;
    }
    // If one of the vertecies does not exist.
    if (this->vertexId.find(from) == this->vertexId.end() ||
        this->vertexId.find(to) == this->vertexId.end()) {
        return;
    }
    // Find source vertex
    auto ofSource = vertices.at(this->vertexId.find(from)->second);
    ofSource->distance = 0;
    // Find destination vertex
    auto ofDest = vertices.at(this->vertexId.find(to)->second);
    // Make a priority queue
    auto priorityQueue = new edge_min_heap();
    // Keep a list of visited and edited (distance) vertecies
    set<Vertex*>* ofVisited = new set<Vertex*>();
    vector<Vertex*>* ofEdited = new vector<Vertex*>();
    // Push starting node to queue.
    priorityQueue->push(ofSource);
    ofSource->ofPrev = nullptr;
    // While the queue is not empty.
    while (!priorityQueue->empty()) {
        // Get vertex with smalled weight, and pop it.
        auto currentVertex = priorityQueue->top();
        priorityQueue->pop();
        // Add vertex to list of edites
        ofEdited->push_back(currentVertex);
        // If the current vertex is the one we want
        if (currentVertex == ofDest) {
            // Iterate through the path
            while (currentVertex != NULL) {
                shortestPath.push_back(currentVertex);
                currentVertex = currentVertex->ofPrev;
            }
            // Reverse vector to show verticies in order
            std::reverse(shortestPath.begin(), shortestPath.end());
            break;
        }
        // If the vertex has not been visited already.
        if (ofVisited->find(currentVertex) == ofVisited->end()) {
            // Mark current vertex as visited
            ofVisited->insert(currentVertex);
            // Keep vector of all edges
            vector<Edge*>* ofEdges = &currentVertex->outEdges;
            // Iterate through each edge
            for (int i = 0; i < ofEdges->size(); i++) {
                // For the current edge, calculate the new distance
                auto currentEdge = ofEdges->at(i);
                int newDist = currentVertex->distance + currentEdge->weight;
                // If the node's distance is infinity or
                // less than the new distance.
                if (currentEdge->target->distance < 0 ||
                    newDist < currentEdge->target->distance) {
                    // Update the distance of the vertex
                    currentEdge->target->distance = newDist;
                    // Update the previous node of the vertex
                    currentEdge->target->ofPrev = currentVertex;
                    // Add vertex to queue.
                    priorityQueue->push(currentEdge->target);
                }
            }
        }
    }
    // For each vertex that has a new distance
    for (int i = 0; i < ofEdited->size(); i++) {
        // Set distance to infinity
        ofEdited->at(i)->distance = -1;
    }
    delete ofVisited;
    delete ofEdited;
    delete priorityQueue;
}

/*
 * This method tries to find a path that
 * links all of the verticies in the graph
 * together. It does so by finding the
 * smallest weighted edges such that
 * there is no cycle in the graph.
 *
 * Parameters:
 *  1) MST - The vector containing the edges
 *           that make up a path.
 *
 * Sources used:
 *  1) CSE 100 Week 9 disucssion slides
 *
 */
void Map::findMST(vector<Edge*>& MST) {
    // Make a queue of all edges
    auto queueOfEdges = new edges_min_heap();
    // Make a hashtable representing an uptree
    unordered_map<Vertex*, Vertex*>* upTree =
        new unordered_map<Vertex*, Vertex*>();
    // For each edge
    for (int i = 0; i < this->undirectedEdges.size(); i++) {
        // Add edge to queue
        queueOfEdges->push(this->undirectedEdges.at(i));
        // Make a pair of vertex and sentinel
        pair<Vertex*, Vertex*> ofNodeOne(this->undirectedEdges.at(i)->source,
                                         nullptr);
        // Add pair of vertex and sentinel
        upTree->insert(ofNodeOne);
        // Make a pair of vertex and sentinel
        pair<Vertex*, Vertex*> ofNodeTwo(this->undirectedEdges.at(i)->target,
                                         nullptr);
        // Add pair of vertex and sentinel
        upTree->insert(ofNodeTwo);
    }
    // While the queue of edges is not empty
    while (!queueOfEdges->empty()) {
        // Get the first vertex in queue
        auto currentEdge = queueOfEdges->top();
        queueOfEdges->pop();
        // Get the source and destination of the edge
        auto vertexOne = currentEdge->source;
        auto vertexTwo = currentEdge->target;
        // Get the sentinel of both the destiantion and source
        // of edge.
        auto vertexOneSent = upTree->find(vertexOne)->second;
        auto vertexTwoSent = upTree->find(vertexTwo)->second;
        // Keep track of current set of uptree
        vector<Vertex*> ofFirstSet;
        // If the two nodes are their own set
        if (vertexOneSent == nullptr && vertexTwoSent == nullptr) {
            // Set one as sentinel of the other
            upTree->find(vertexTwo)->second = vertexOne;
            MST.push_back(currentEdge);
        } else {
            // If the source vertex is part of a set
            if (vertexOneSent != nullptr) {
                // Find the sentinel of the source node
                while (vertexOneSent != nullptr) {
                    // Keep track of all the verticies in path
                    ofFirstSet.push_back(vertexOne);
                    vertexOne = vertexOneSent;
                    // Find sentinel of parent vertex
                    vertexOneSent = upTree->find(vertexOne)->second;
                }
                // Update the sentinel of traversed path in up tree
                for (int i = 0; i < ofFirstSet.size(); i++) {
                    // Make every node in uptree point to sentinel in path.
                    if (upTree->find(ofFirstSet.at(i))->second != vertexOne) {
                        upTree->find(ofFirstSet.at(i))->second = vertexOne;
                    }
                }
            }
            // Keep track of the set that the dest vertex belongs to.
            vector<Vertex*> ofSecondSet;
            // If the dest vertex is part of an uptree
            if (vertexTwoSent != nullptr) {
                // Find sentinel of vertex
                while (vertexTwoSent != nullptr) {
                    ofSecondSet.push_back(vertexTwo);
                    vertexTwo = vertexTwoSent;
                    vertexTwoSent = upTree->find(vertexTwo)->second;
                }
                // Update all of the verticies in the path
                // to the sentinel
                for (int i = 0; i < ofSecondSet.size(); i++) {
                    if (upTree->find(ofSecondSet.at(i))->second != vertexTwo) {
                        upTree->find(ofSecondSet.at(i))->second = vertexTwo;
                    }
                }
            }
            // If The two verticies have diff. sentinels.
            if (vertexOne != vertexTwo) {
                // Add the edge
                MST.push_back(currentEdge);
                // Link uptree
                if (ofFirstSet.size() > ofSecondSet.size()) {
                    upTree->find(vertexTwo)->second = vertexOne;
                } else {
                    upTree->find(vertexOne)->second = vertexTwo;
                }
            }
        }
    }
    delete queueOfEdges;
    delete upTree;
}

/*
 * This method finds all of the edges
 * which link the subsets of nodes
 * that make up a graph.
 *
 * Parameters:
 *  1) roads - A vector containing
 *             all of the crucial
 *             edges.
 *
 * Sources used:
 *  1) CSE 100 Week 9 disucssion slides
 *
 */
void Map::crucialRoads(vector<Edge*>& roads) {
    // For each possible edge in the graph
    for (int i = 0; i < this->undirectedEdges.size(); i++) {
        // Get edge at index
        auto currentEdge = this->undirectedEdges.at(i);
        // Use dfs to check if its a critical edge
        bool criticalEdge =
            this->DFS(currentEdge->source, currentEdge->target, currentEdge);
        // Add edge to vector if its critical
        if (criticalEdge) {
            roads.push_back(currentEdge);
        }
    }
}

/*
 * This method uses a modefied version
 * of DFS to find an alternate path
 * between two nodes.
 *
 * Parameters:
 *  1) from - The vertex we are starting at
 *  2) to - The vertex we are ending at
 *  3) toAvoid - The edge we want to avoid
 *
 * Sources used:
 *  1) CSE 100 Week 9 disucssion slides
 *
 */
bool Map::DFS(Vertex* from, Vertex* to, Edge* toAvoid) {
    // Make a stack of verticies
    stack<Vertex*>* ofVetrecies = new stack<Vertex*>();
    // List of visited edges
    set<Vertex*>* ofVisited = new set<Vertex*>();
    // Add starting vertex
    ofVetrecies->push(from);
    // Bool if we hit the edge we want to avoid.
    bool hitAvoid = false;
    // While the stack is not empty
    while (!ofVetrecies->empty()) {
        // Get vertex at the top of stack and pop it
        auto ofCurrent = ofVetrecies->top();
        ofVetrecies->pop();
        // If the current vertex is equal to destination
        if (ofCurrent == to) {
            return false;
        }
        // If the current vertex has not been visited
        if (ofVisited->find(ofCurrent) == ofVisited->end()) {
            // Mark vertex as visited
            ofVisited->insert(ofCurrent);
            // Loop through all of the edges of current vertex
            for (int i = 0; i < ofCurrent->outEdges.size(); i++) {
                // Edge at index i
                auto currentEdge = ofCurrent->outEdges.at(i);
                // If the current edge is equal to the start
                if (currentEdge->source == from) {
                    // If the edge does not end at destination
                    if (currentEdge->target != to) {
                        ofVetrecies->push(currentEdge->target);
                    }
                    // We hit an edge that we want to avoid
                    else {
                        // If there are multiple edges to dest.
                        if (hitAvoid) {
                            return false;
                        }
                        // Mark edge to avoid as hit
                        else {
                            hitAvoid = true;
                        }
                    }
                }
                // We are not at the starting vertex.
                else {
                    ofVetrecies->push(currentEdge->target);
                }
            }
        }
    }
    return true;
    delete ofVetrecies;
    delete ofVisited;
}

/* Destructor of Map graph */
Map::~Map() {
    // delete each vertex
    for (Vertex* v : vertices) {
        // delete each edge
        for (Edge* e : v->outEdges) {
            delete e;
        }
        delete v;
    }
    // delete undirected edges
    for (Edge* e : undirectedEdges) {
        delete e;
    }
}
