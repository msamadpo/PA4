/**
 * TODO: add file header
 */

#include "ActorNode.hpp"
#include "MovieNode.hpp"

using namespace std;

ActorNode::ActorNode(string actorName) {
    this->actorName = actorName;
    this->ofMovies = new vector<MovieNode*>();
}

string ActorNode::getActorName() { return this->actorName; }

void ActorNode::addMovie(MovieNode* ofMovie) {
    this->ofMovies->push_back(ofMovie);
}

vector<MovieNode*>* ActorNode::inMovies() { return this->ofMovies; }

void ActorNode::setPrevious(pair<ActorNode*, MovieNode*> ofPrevious) {
    this->ofPrevious = ofPrevious;
}

pair<ActorNode*, MovieNode*> ActorNode::getPrevious() {
    return this->ofPrevious;
}

ActorNode::~ActorNode() {
    this->ofMovies->clear();
    delete this->ofMovies;
}