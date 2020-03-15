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

#include "MovieNode.hpp"
#include "ActorNode.hpp"

using namespace std;

/*
 * This is the contructor method for the node.
 * Its purpose is to initialize the necessary
 * instance variables to make a movie node.
 *
 * Parameters:
 *  1) movieName - The name of the movie.
 *
 */
MovieNode::MovieNode(string movieName) {
    this->movieName = movieName;
    this->ofActors = new vector<ActorNode*>();
}

/*
 * The purpose of this method is to return
 * the name of the movie node.
 *
 * Parameters:
 *  NONE
 *
 */
string MovieNode::getMovieName() { return this->movieName; }

/*
 * The purpose of this method is to add
 * a actor node to the vector of actors
 * which this movie node links.
 *
 * Parameters:
 *  1) ofActor - A pointer to the actor node.
 *
 */
void MovieNode::addActor(ActorNode* ofActor) {
    this->ofActors->push_back(ofActor);
}

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
vector<ActorNode*>* MovieNode::actorsInMovie() { return this->ofActors; }

/*
 * The purpose of this method is to free up
 * all of the memory used by the movie node
 * in the graph.
 *
 * Parameters:
 *  NONE
 *
 */
MovieNode::~MovieNode() {
    this->ofActors->clear();
    delete this->ofActors;
}