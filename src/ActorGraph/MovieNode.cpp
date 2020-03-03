/**
 * TODO: add file header
 */

#include "MovieNode.hpp"
#include "ActorNode.hpp"

using namespace std;

MovieNode::MovieNode(string movieName) {
    this->movieName = movieName;
    this->ofActors = new vector<ActorNode*>();
}

string MovieNode::getMovieName() { return this->movieName; }

void MovieNode::addActor(ActorNode* ofActor) {
    this->ofActors->push_back(ofActor);
}

vector<ActorNode*>* MovieNode::actorsInMovie() { return this->ofActors; }

MovieNode::~MovieNode() {
    this->ofActors->clear();
    delete this->ofActors;
}