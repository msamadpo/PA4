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
 *  node representing an actor. It is used to make a
 *  connected graph
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <string>
#include <vector>

using namespace std;

class MovieNode;

/**
 * The ActorNode class allows the user to create a
 * a node which represents an actor. It contains
 * the actor's name, a pointer to a previous
 * actor node, and a vector of edges made up
 * of movies.
 *
 * Instance variables:
 *  1) actorName - The name of the actor
 *
 *  2) ofMovies - The vector containing all of
 *                the edges.
 *
 *  3) ofPrevious - The previous actor node
 */
class ActorNode {
  protected:
    string actorName;
    vector<MovieNode*>* ofMovies;
    pair<ActorNode*, MovieNode*> ofPrevious;

  public:
    /*
     * This is the contructor method for the node.
     * Its purpose is to initialize the necessary
     * instance variables to make a actor node.
     *
     * Parameters:
     *  1) actorName - The name of the actor
     *
     */
    ActorNode(string actorName);

    /*
     * The purpose of this method is to return
     * the name of the actor.
     *
     * Parameters:
     *  NONE
     *
     */
    string getActorName();

    /*
     * The purpose of this method is to add an edge
     * to the actor node.
     *
     * Parameters:
     *  1) ofMovie - The node representing the edge
     *
     */
    void addMovie(MovieNode* ofMovie);

    /*
     * The purpose of this method is to return a
     * vector which contains all of the edges
     * of the actor node.
     *
     * Parameters:
     *  NONE
     *
     */
    vector<MovieNode*>* inMovies();

    /*
     * The purpose of this method is to set the
     * previous node of a actor node. Its used
     * to link paths together.
     *
     * Parameters:
     *  1) ofPrevious - The actor node and the edge
     *                  that connects both verticies.
     *
     */
    void setPrevious(pair<ActorNode*, MovieNode*> ofPrevious);

    /*
     * The purpose of this method is to return a
     * pair which represents the previous node
     * of the current actor node
     *
     * Parameters:
     *  NONE
     *
     */
    pair<ActorNode*, MovieNode*> getPrevious();

    /*
     * The purpose of this method is to free up
     * all of the memory used by the actor node
     * in the graph.
     *
     * Parameters:
     *  NONE
     *
     */
    ~ActorNode();
};

#endif  // ACTORNODE_HPP