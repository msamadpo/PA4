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
 *  graph of actors and movies that they played in.
 *  It also contains the neccessary methods to preform
 *  searches throughout the graph.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "ActorNode.hpp"
#include "MovieNode.hpp"

using namespace std;

/**
 * The ActorGraph class allows the user to create a
 * a graph which is made up of actor nodes and
 * movie nodes. The graph implements BFS in order
 * to find a link between two actors.
 * It asumes the user has a file with all of the
 * actors and their movies.
 *
 * Instance variables:
 *  1) ofActors - A hashtable of Actor nodes ordered
 *                by their name
 */
class ActorGraph {
  protected:
    unordered_map<string, ActorNode*>* ofActors;

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
    ActorGraph();

    /*
     * This method reads in data from a file
     * and makes a graph based on its contents.
     * It assumes that each line of the file has
     * an actor, the movies they played in, and
     * the year the movie was released.
     *
     * Parameters:
     *  1) filename - The name of the file
     *
     */
    bool buildGraphFromFile(const char* filename);

    /*
     * This method reads in the name of two actors
     * and tries to find a valid path between them.
     * It does so using a BFS algo. If a path does
     * not exist it returns an empty string.
     *
     * Parameters:
     *  1) fromActor - The vertex from which to start
     *  2) toActor - The vertex we want to end at
     *
     * Sources used:
     *  1) CSE 100 Lecture slides
     *
     *  2) Stepik: Introduction to Data Structures (Fall 2016)
     *     by Moshiri and Izhikevich (available at stepik.org)
     *     Section: 4.3 - Step 8
     *
     * Edge Cases:
     *  1) The actors do not exists - return
     *  2) The input is empty - return
     *
     */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /*
     * This method tries to predict a link between actors.
     * Not implemented.
     */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /*
     * This is the destructor method. It makes sure
     * to free up any memory used to create the
     * graph. It does so by removing all the
     * nodes of actors and movies while also
     * freeing the space used by the hashtable.
     *
     */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
