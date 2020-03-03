/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

/* TODO */
ActorGraph::ActorGraph() {
    this->ofActors = new unordered_map<string, ActorNode*>();
}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraphFromFile(const char* filename) {
    ifstream infile(filename);
    bool readHeader = false;

    // Start of Addition
    unordered_map<string, MovieNode*>* movieList =
        new unordered_map<string, MovieNode*>();

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

        // TODO: we have an actor/movie relationship to build the graph

        title = title + "#@" + to_string(year);
        if (this->ofActors->find(actor) == this->ofActors->end() &&
            movieList->find(title) == movieList->end()) {
            auto ofCurrentActor = new ActorNode(actor);
            auto ofCurrentMovie = new MovieNode(title);
            ofCurrentActor->addMovie(ofCurrentMovie);
            ofCurrentMovie->addActor(ofCurrentActor);
            std::pair<string, ActorNode*> actorPair(actor, ofCurrentActor);
            std::pair<string, MovieNode*> moviePair(title, ofCurrentMovie);
            this->ofActors->insert(actorPair);
            movieList->insert(moviePair);
        } else if (this->ofActors->find(actor) == this->ofActors->end() ||
                   movieList->find(title) == movieList->end()) {
            if (this->ofActors->find(actor) == this->ofActors->end()) {
                auto ofCurrentMovie = movieList->find(title)->second;
                auto ofCurrentActor = new ActorNode(actor);
                ofCurrentActor->addMovie(ofCurrentMovie);
                ofCurrentMovie->addActor(ofCurrentActor);
                std::pair<string, ActorNode*> actorPair(actor, ofCurrentActor);
                this->ofActors->insert(actorPair);
            } else {
                auto ofCurrentMovie = new MovieNode(title);
                auto ofCurrentActor = this->ofActors->find(actor)->second;
                ofCurrentActor->addMovie(ofCurrentMovie);
                ofCurrentMovie->addActor(ofCurrentActor);
                std::pair<string, MovieNode*> moviePair(title, ofCurrentMovie);
                movieList->insert(moviePair);
            }
        } else {
            auto ofCurrentMovie = movieList->find(title)->second;
            auto ofCurrentActor = this->ofActors->find(actor)->second;
            ofCurrentActor->addMovie(ofCurrentMovie);
            ofCurrentMovie->addActor(ofCurrentActor);
        }
    }

    // Addition
    delete movieList;

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();

    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    if (this->ofActors->find(fromActor) == this->ofActors->end() ||
        this->ofActors->find(toActor) == this->ofActors->end()) {
        return;
    }
    queue<ActorNode*>* ofNodes = new queue<ActorNode*>();
    auto endNode = this->ofActors->find(toActor)->second;
    unordered_set<string>* ofVisitedActors = new unordered_set<string>();
    unordered_set<string>* ofVisitedMovies = new unordered_set<string>();
    ofNodes->push(this->ofActors->find(fromActor)->second);
    ActorNode* ofCurrentNode = nullptr;
    auto startNode = this->ofActors->find(fromActor)->second;
    while (ofNodes->size() > 0) {
        ofCurrentNode = ofNodes->front();
        ofNodes->pop();
        if (ofCurrentNode->getActorName() == toActor) {
            auto ofCurrPrev = ofCurrentNode->getPrevious();
            shortestPath = "(" + ofCurrentNode->getActorName() + ")";
            while (ofCurrentNode != startNode) {
                string ofActor = "(" + ofCurrPrev.first->getActorName() + ")";
                ofActor = ofActor + "--";
                string ofMovie = "[" + ofCurrPrev.second->getMovieName() + "]";
                ofActor = ofActor + ofMovie + "-->";
                ofActor = ofActor + shortestPath;
                shortestPath = ofActor;
                ofCurrentNode = ofCurrentNode->getPrevious().first;
                ofCurrPrev = ofCurrentNode->getPrevious();
            }
            break;
        }
        ofVisitedActors->insert(ofCurrentNode->getActorName());
        vector<MovieNode*> ofEdges = vector<MovieNode*>();
        auto ofMovies = ofCurrentNode->inMovies();
        for (int i = 0; i < ofMovies->size(); i++) {
            auto currentMovie = ofMovies->at(i);
            if (ofVisitedMovies->find(currentMovie->getMovieName()) ==
                ofVisitedMovies->end()) {
                ofVisitedMovies->insert(currentMovie->getMovieName());
                auto actorVector = currentMovie->actorsInMovie();
                for (int j = 0; j < actorVector->size(); j++) {
                    auto currActorEdge = actorVector->at(j);
                    if (ofVisitedActors->find(currActorEdge->getActorName()) ==
                        ofVisitedActors->end()) {
                        pair<ActorNode*, MovieNode*> ofPrevious(ofCurrentNode,
                                                                currentMovie);
                        currActorEdge->setPrevious(ofPrevious);
                        ofVisitedActors->insert(currActorEdge->getActorName());
                        ofNodes->push(currActorEdge);
                    }
                }
            }
        }
    }
    delete ofNodes;
    delete ofVisitedActors;
    delete ofVisitedMovies;
    return;
}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {
    return;
}

/* TODO */
ActorGraph::~ActorGraph() {}
