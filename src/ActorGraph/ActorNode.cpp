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

#include "ActorNode.hpp"
#include "MovieNode.hpp"

using namespace std;

/*
 * This is the contructor method for the node.
 * Its purpose is to initialize the necessary
 * instance variables to make a actor node.
 *
 * Parameters:
 *  1) actorName - The name of the actor
 *
 */
ActorNode::ActorNode(string actorName) {
    this->actorName = actorName;
    this->ofMovies = new vector<MovieNode*>();
}

/*
 * The purpose of this method is to return
 * the name of the actor.
 *
 * Parameters:
 *  NONE
 *
 */
string ActorNode::getActorName() { return this->actorName; }

/*
 * The purpose of this method is to add an edge
 * to the actor node.
 *
 * Parameters:
 *  1) ofMovie - The node representing the edge
 *
 */
void ActorNode::addMovie(MovieNode* ofMovie) {
    // Add movie to list of edges
    this->ofMovies->push_back(ofMovie);
}

/*
 * The purpose of this method is to return a
 * vector which contains all of the edges
 * of the actor node.
 *
 * Parameters:
 *  NONE
 *
 */
vector<MovieNode*>* ActorNode::inMovies() { return this->ofMovies; }

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
void ActorNode::setPrevious(pair<ActorNode*, MovieNode*> ofPrevious) {
    this->ofPrevious = ofPrevious;
}

/*
 * The purpose of this method is to return a
 * pair which represents the previous node
 * of the current actor node
 *
 * Parameters:
 *  NONE
 *
 */
pair<ActorNode*, MovieNode*> ActorNode::getPrevious() {
    return this->ofPrevious;
}

/*
 * The purpose of this method is to free up
 * all of the memory used by the actor node
 * in the graph.
 *
 * Parameters:
 *  NONE
 *
 */
ActorNode::~ActorNode() {
    // Clear vector of all pointers
    this->ofMovies->clear();
    // Delete vector
    delete this->ofMovies;
}