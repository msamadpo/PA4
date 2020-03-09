
#include "Map.hpp"
#include <algorithm>
#include <queue>
#include <set>
#include <stack>

struct compare {
    bool operator()(Vertex* v1, Vertex* v2) {
        // Returns the biggest frequency
        if (v1->distance != v2->distance) {
            return v1->distance > v2->distance;
        }
        // Returns the smallest word
        return v1->name > v2->name;
    }
};

struct edgeCompare {
    bool operator()(Edge* e1, Edge* e2) {
        // Returns the biggest frequency
        if (e1->weight != e2->weight) {
            return e1->weight > e2->weight;
        }
        // Returns the smallest word
        return e1->target->name > e2->target->name;
    }
};

typedef std::priority_queue<Vertex*, std::vector<Vertex*>, compare>
    edge_min_heap;

typedef std::priority_queue<Edge*, std::vector<Edge*>, edgeCompare>
    edges_min_heap;

/* TODO */
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

/* TODO */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
    if (from.size() == 0 || to.size() == 0) {
        return;
    }
    if (this->vertexId.find(from) == this->vertexId.end() ||
        this->vertexId.find(to) == this->vertexId.end()) {
        return;
    }
    auto ofSource = vertices.at(this->vertexId.find(from)->second);
    ofSource->distance = 0;
    auto ofDest = vertices.at(this->vertexId.find(to)->second);
    auto priorityQueue = new edge_min_heap();
    set<Vertex*>* ofVisited = new set<Vertex*>();
    vector<Vertex*>* ofEdited = new vector<Vertex*>();
    priorityQueue->push(ofSource);
    ofSource->ofPrev = nullptr;
    while (!priorityQueue->empty()) {
        auto currentVertex = priorityQueue->top();
        priorityQueue->pop();
        ofEdited->push_back(currentVertex);
        if (currentVertex == ofDest) {
            while (currentVertex != NULL) {
                shortestPath.push_back(currentVertex);
                currentVertex = currentVertex->ofPrev;
            }
            std::reverse(shortestPath.begin(), shortestPath.end());
            break;
        }
        if (ofVisited->find(currentVertex) == ofVisited->end()) {
            ofVisited->insert(currentVertex);
            vector<Edge*>* ofEdges = &currentVertex->outEdges;
            for (int i = 0; i < ofEdges->size(); i++) {
                auto currentEdge = ofEdges->at(i);
                int newDist = currentVertex->distance + currentEdge->weight;
                if (currentEdge->target->distance < 0 ||
                    newDist < currentEdge->target->distance) {
                    currentEdge->target->distance = newDist;
                    currentEdge->target->ofPrev = currentVertex;
                    priorityQueue->push(currentEdge->target);
                }
            }
        }
    }
    for (int i = 0; i < ofEdited->size(); i++) {
        ofEdited->at(i)->distance = -1;
    }
    delete ofVisited;
    delete ofEdited;
    delete priorityQueue;
}

/* TODO */
void Map::findMST(vector<Edge*>& MST) {
    auto queueOfEdges = new edges_min_heap();
    unordered_map<Vertex*, Vertex*>* upTree =
        new unordered_map<Vertex*, Vertex*>();
    Vertex* ofM = nullptr;
    for (int i = 0; i < this->undirectedEdges.size(); i++) {
        if (ofM == NULL) {
            if (this->undirectedEdges.at(i)->source->name == "Marshall") {
                this->undirectedEdges.at(i)->source;
            }
            if (this->undirectedEdges.at(i)->target->name == "Marshall") {
                ofM = this->undirectedEdges.at(i)->target;
            }
        }
        queueOfEdges->push(this->undirectedEdges.at(i));
        pair<Vertex*, Vertex*> ofNodeOne(this->undirectedEdges.at(i)->source,
                                         nullptr);
        upTree->insert(ofNodeOne);
        pair<Vertex*, Vertex*> ofNodeTwo(this->undirectedEdges.at(i)->target,
                                         nullptr);
        upTree->insert(ofNodeTwo);
    }
    while (!queueOfEdges->empty()) {
        auto currentEdge = queueOfEdges->top();
        queueOfEdges->pop();
        auto vertexOne = currentEdge->source;
        auto vertexTwo = currentEdge->target;
        auto vertexOneSent = upTree->find(vertexOne)->second;
        auto vertexTwoSent = upTree->find(vertexTwo)->second;
        vector<Vertex*> ofFirstSet;
        if (vertexOneSent == nullptr && vertexTwoSent == nullptr) {
            upTree->find(vertexTwo)->second = vertexOne;
            MST.push_back(currentEdge);
        } else {
            if (vertexOneSent != nullptr) {
                while (vertexOneSent != nullptr) {
                    ofFirstSet.push_back(vertexOne);
                    vertexOne = vertexOneSent;
                    vertexOneSent = upTree->find(vertexOne)->second;
                }
                for (int i = 0; i < ofFirstSet.size(); i++) {
                    if (upTree->find(ofFirstSet.at(i))->second != vertexOne) {
                        upTree->find(ofFirstSet.at(i))->second = vertexOne;
                    }
                }
            }
            vector<Vertex*> ofSecondSet;
            if (vertexTwoSent != nullptr) {
                while (vertexTwoSent != nullptr) {
                    ofSecondSet.push_back(vertexTwo);
                    vertexTwo = vertexTwoSent;
                    vertexTwoSent = upTree->find(vertexTwo)->second;
                }
                for (int i = 0; i < ofSecondSet.size(); i++) {
                    if (upTree->find(ofSecondSet.at(i))->second != vertexTwo) {
                        upTree->find(ofSecondSet.at(i))->second = vertexTwo;
                    }
                }
            }
            if (vertexOne != vertexTwo) {
                MST.push_back(currentEdge);
                if (ofFirstSet.size() > ofSecondSet.size()) {
                    upTree->find(vertexTwo)->second = vertexOne;
                } else {
                    upTree->find(vertexOne)->second = vertexTwo;
                }
            }
        }
    }
}

/* TODO */
void Map::crucialRoads(vector<Edge*>& roads) {
    for (int i = 0; i < this->undirectedEdges.size(); i++) {
        auto currentEdge = this->undirectedEdges.at(i);
        bool criticalEdge =
            this->DFS(currentEdge->source, currentEdge->target, currentEdge);
        if (criticalEdge) {
            roads.push_back(currentEdge);
        }
    }
}

bool Map::DFS(Vertex* from, Vertex* to, Edge* toAvoid) {
    stack<Vertex*>* ofVetrecies = new stack<Vertex*>();
    set<Vertex*>* ofVisited = new set<Vertex*>();
    ofVetrecies->push(from);
    while (!ofVetrecies->empty()) {
        auto ofCurrent = ofVetrecies->top();
        ofVetrecies->pop();
        if (ofCurrent == to) {
            return false;
        }
        if (ofVisited->find(ofCurrent) == ofVisited->end()) {
            ofVisited->insert(ofCurrent);
            for (int i = 0; i < ofCurrent->outEdges.size(); i++) {
                auto currentEdge = ofCurrent->outEdges.at(i);
                if (currentEdge->source == from) {
                    if (currentEdge->target != to) {
                        ofVetrecies->push(currentEdge->target);
                    }
                } else {
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
    for (Vertex* v : vertices) {
        for (Edge* e : v->outEdges) {
            delete e;
        }
        delete v;
    }
    for (Edge* e : undirectedEdges) {
        delete e;
    }
}
