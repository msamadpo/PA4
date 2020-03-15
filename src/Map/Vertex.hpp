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
 *  vertex in a graph with all of its outgoing edges.
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

using namespace std;

class Edge;

/* This class defines a vertex in map graph. Each vertex has a name and x, y
 * coordinates in the map */
class Vertex {
  public:
    const string name;
    float x;
    float y;
    vector<Edge*> outEdges;  // the adjacency list of this vertex that contains
                             // all outgoing edges
    Vertex* ofPrev;          // The previous node in current path
    int distance;            // Distance in current path

    /* The constructor that creates a new vertex */
    Vertex(const string& name, float x, float y)
        : name(name), x(x), y(y), ofPrev(nullptr), distance(-1) {}
};

#endif  // VERTEX_HPP