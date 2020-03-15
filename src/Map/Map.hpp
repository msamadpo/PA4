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

#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Edge.hpp"

using namespace std;

/**
 * The Map class allows the user to create a
 * a graph which is made up of Verticies and
 * edges. The graph implements various traversals
 * such as DFS, MST, crucial roads to traverse
 * the graph.
 *
 * Instance variables:
 *  1) vertices - The list of verticies in the graph.
 *
 *  2) vertexId - The hash table of the index of verticies.
 *
 *  3) undirectedEdges - The vector containig all of the und.
 *                       edges in the graph.
 */
class Map {
  private:
    // vector storing vertices in the map: id of each vertex = index in vector
    vector<Vertex*> vertices;

    // Map: name of vertex -> id of vertex = index storing vertex ptr
    unordered_map<string, unsigned int> vertexId;

    // Directed edge in vector represents an undirected edge used in MST
    vector<Edge*> undirectedEdges;

    /*
     * Add a vertex with name and x, y coordinates to the map graph. Returns
     * false if the name already existed in the map graph, and true otherwise
     */
    bool addVertex(const string& name, float x, float y);

    /*
     * Add an undirected edge between vertices with names "name1" and "name2".
     * Returns false if either name is not in the map graph.
     */
    bool addEdge(const string& name1, const string& name2);

  public:
    /*
     * This is the contructor method for the graph.
     * Its purpose is to initialize the necessary
     * instance variables to make a graph.
     *
     * Parameters:
     *  NONE
     *
     */
    Map();

    /* Build the map graph from vertex and edge files */
    bool buildMapFromFile(const string& vertexFileName,
                          const string& edgeFileName);

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
    void Dijkstra(const string& from, const string& to,
                  vector<Vertex*>& shortestPath);

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
    void findMST(vector<Edge*>& MST);

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
    void crucialRoads(vector<Edge*>& roads);

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
     *  2) Stepik: Introduction to Data Structures (Fall 2016)
     *     by Moshiri and Izhikevich (available at stepik.org)
     *     Section: 4.4 - Step: 6
     *
     */
    bool DFS(Vertex* from, Vertex* to, Edge* toAvoid);

    /* Destructor of Map graph */
    ~Map();
};

#endif  // Map_HPP