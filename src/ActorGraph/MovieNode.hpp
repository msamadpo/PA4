/**
 * Authors: Matthew Lund and Mohammad Javid
 * Contact info: mtlund@ucsd.edu (Matthew),
 *               Msamadpo@ucsd.edu (Mohammad)
 *
 * Sources used:
 *  1) Stepik: Introduction to Data Structures (Fall 2016)
 *     by Moshiri and Izhikevich (available at stepik.org)
 *
 * Implementation idea:
 *  1) CSE 100 - Week 8 - 9 Discussion slides
 *
 * Description of File:
 *  This file defines the neccessary methods to create a
 *  node representing an movie edge. It is used to make a
 *  connected graph
 */

#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP

#include <string>
#include <vector>

using namespace std;

class ActorNode;

/**
 * The MovieNode class allows the user to create a
 * a node which represents an movie. It contains
 * the movie's name, and a vector of actor nodes
 * which are connected by this movie edge.
 *
 * Instance variables:
 *  1) movieName - The name of the movie
 *
 *  2) ofActors - The actors which are
 *                linked by this edge.
 */
class MovieNode {
  protected:
    string movieName;
    vector<ActorNode*>* ofActors;

  public:
    /*
     * This is the contructor method for the node.
     * Its purpose is to initialize the necessary
     * instance variables to make a movie node.
     *
     * Parameters:
     *  1) movieName - The name of the movie.
     *
     */
    MovieNode(string movieName);

    /*
     * The purpose of this method is to return
     * the name of the movie node.
     *
     * Parameters:
     *  NONE
     *
     */
    string getMovieName();

    /*
     * The purpose of this method is to add
     * a actor node to the vector of actors
     * which this movie node links.
     *
     * Parameters:
     *  1) ofActor - A pointer to the actor node.
     *
     */
    void addActor(ActorNode* ofActor);

    /*
     * The purpose of this method is to
     * return a vecor which contains
     * all of the actor nodes that
     * are linked by this vector.
     *
     * Parameters:
     *  NONE
     *
     */
    vector<ActorNode*>* actorsInMovie();

    /*
     * The purpose of this method is to free up
     * all of the memory used by the movie node
     * in the graph.
     *
     * Parameters:
     *  NONE
     *
     */
    ~MovieNode();
};

#endif  // MOVIENODE_HPP