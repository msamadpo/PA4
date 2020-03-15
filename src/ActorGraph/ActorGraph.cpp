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

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

/*
 * This is the contructor method for the graph.
 * Its purpose is to initialize the necessary
 * instance variables to make a graph.
 *
 * Parameters:
 *  NONE
 *
 */
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

    // Store a list of exiting movie edges in the graph
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

        // Add year to existing title
        title = title + "#@" + to_string(year);

        // Check if the actor and movie have not been added before
        if (this->ofActors->find(actor) == this->ofActors->end() &&
            movieList->find(title) == movieList->end()) {
            // Makes a node for the actor and edge
            auto ofCurrentActor = new ActorNode(actor);
            auto ofCurrentMovie = new MovieNode(title);
            // Links the movie and actor node.
            ofCurrentActor->addMovie(ofCurrentMovie);
            ofCurrentMovie->addActor(ofCurrentActor);
            // Makes a pair to insert into hashtable
            std::pair<string, ActorNode*> actorPair(actor, ofCurrentActor);
            std::pair<string, MovieNode*> moviePair(title, ofCurrentMovie);
            // Insert movie and actor to existing list of movies and actors
            this->ofActors->insert(actorPair);
            movieList->insert(moviePair);
        }
        // If the actor or the movie has not been created before
        else if (this->ofActors->find(actor) == this->ofActors->end() ||
                 movieList->find(title) == movieList->end()) {
            // If the actor has not been created before
            if (this->ofActors->find(actor) == this->ofActors->end()) {
                // Create an actor node, get existing movie node
                auto ofCurrentMovie = movieList->find(title)->second;
                auto ofCurrentActor = new ActorNode(actor);
                // Links said movie and actor
                ofCurrentActor->addMovie(ofCurrentMovie);
                ofCurrentMovie->addActor(ofCurrentActor);
                // Adds actor to existing list of actors
                std::pair<string, ActorNode*> actorPair(actor, ofCurrentActor);
                this->ofActors->insert(actorPair);
            }
            // If the actor exists but the movie does not
            else {
                // Make a node for the movie edge, get existing actor
                auto ofCurrentMovie = new MovieNode(title);
                auto ofCurrentActor = this->ofActors->find(actor)->second;
                // Link actor and movie node.
                ofCurrentActor->addMovie(ofCurrentMovie);
                ofCurrentMovie->addActor(ofCurrentActor);
                // Add new movie node to list of existing movies
                std::pair<string, MovieNode*> moviePair(title, ofCurrentMovie);
                movieList->insert(moviePair);
            }
        }
        // If both the movie and actor already have nodes
        else {
            // Get movie and actor nodes.
            auto ofCurrentMovie = movieList->find(title)->second;
            auto ofCurrentActor = this->ofActors->find(actor)->second;
            // Link said nodes
            ofCurrentActor->addMovie(ofCurrentMovie);
            ofCurrentMovie->addActor(ofCurrentActor);
        }
    }

    delete movieList;

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();

    return true;
}

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
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    // Edge case: string inputted are empty
    if (fromActor.size() == 0 || toActor.size() == 0) {
        return;
    }
    // Edge case: One of the actors or both are not in the graph
    if (this->ofActors->find(fromActor) == this->ofActors->end() ||
        this->ofActors->find(toActor) == this->ofActors->end()) {
        return;
    }
    queue<ActorNode*>* ofNodes = new queue<ActorNode*>();
    // End node
    auto endNode = this->ofActors->find(toActor)->second;
    // List of visited actors and movies
    unordered_set<string>* ofVisitedActors = new unordered_set<string>();
    unordered_set<string>* ofVisitedMovies = new unordered_set<string>();
    // Push the starting vertex
    ofNodes->push(this->ofActors->find(fromActor)->second);
    ActorNode* ofCurrentNode = nullptr;
    auto startNode = this->ofActors->find(fromActor)->second;
    // While the queue is not empty
    while (ofNodes->size() > 0) {
        // Get the first element in queue and remove it
        ofCurrentNode = ofNodes->front();
        ofNodes->pop();
        // If the current vertex is the destination we want
        if (ofCurrentNode->getActorName() == toActor) {
            // Gets the previous node of path
            auto ofCurrPrev = ofCurrentNode->getPrevious();
            // Creates a string representing current path
            shortestPath = "(" + ofCurrentNode->getActorName() + ")";
            // Loop through the whole path taken
            while (ofCurrentNode != startNode) {
                // Use a series of string concatenations in order to output path
                string ofActor = "(" + ofCurrPrev.first->getActorName() + ")";
                ofActor = ofActor + "--";
                string ofMovie = "[" + ofCurrPrev.second->getMovieName() + "]";
                ofActor = ofActor + ofMovie + "-->";
                ofActor = ofActor + shortestPath;
                shortestPath = ofActor;
                // Move back in the path once at a time
                ofCurrentNode = ofCurrentNode->getPrevious().first;
                ofCurrPrev = ofCurrentNode->getPrevious();
            }
            // Finish, we found the node we wanted
            break;
        }
        // Mark vertex as visited
        ofVisitedActors->insert(ofCurrentNode->getActorName());
        // Make a vector of all the possible edges
        vector<MovieNode*> ofEdges = vector<MovieNode*>();
        // Get all the edges of current vertex.
        auto ofMovies = ofCurrentNode->inMovies();
        for (int i = 0; i < ofMovies->size(); i++) {
            // Get the current edge
            auto currentMovie = ofMovies->at(i);
            // If the edge has not been visited
            if (ofVisitedMovies->find(currentMovie->getMovieName()) ==
                ofVisitedMovies->end()) {
                // Mark movie node as visited
                ofVisitedMovies->insert(currentMovie->getMovieName());
                // Get all the actors linked to that edge vertex
                auto actorVector = currentMovie->actorsInMovie();
                for (int j = 0; j < actorVector->size(); j++) {
                    // Get current actor vertex
                    auto currActorEdge = actorVector->at(j);
                    // If the actor vertex has not been visited
                    if (ofVisitedActors->find(currActorEdge->getActorName()) ==
                        ofVisitedActors->end()) {
                        // Mark vertex as visited
                        pair<ActorNode*, MovieNode*> ofPrevious(ofCurrentNode,
                                                                currentMovie);
                        currActorEdge->setPrevious(ofPrevious);
                        ofVisitedActors->insert(currActorEdge->getActorName());
                        // Add actor vertex to exiting queue.
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

/*
 * This method tries to predict a link between actors.
 * Not implemented.
 */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {
    return;
}

/*
 * This is the destructor method. It makes sure
 * to free up any memory used to create the
 * graph. It does so by removing all the
 * nodes of actors and movies while also
 * freeing the space used by the hashtable.
 *
 */
ActorGraph::~ActorGraph() {
    // Use iterators to iterate through hast table.
    auto startOfActorTable = this->ofActors->begin();
    auto endOfActorTable = this->ofActors->end();
    // Keep a list of all the movie edges
    unordered_set<MovieNode*>* ofAllMovies = new unordered_set<MovieNode*>();
    // Loop through actor hash table
    while (startOfActorTable != endOfActorTable) {
        // Get actor vertex
        auto currentActor = startOfActorTable->second;
        // Get list of edges
        auto actorMovies = currentActor->inMovies();
        // Add movie edge to hashtbale
        for (unsigned int i = 0; i < actorMovies->size(); i++) {
            ofAllMovies->insert(actorMovies->at(i));
        }
        // Delete current actor vertex, move onto next element
        delete currentActor;
        startOfActorTable++;
    }
    // Iterators to iterate through movie hash table
    auto startOfMovieTable = ofAllMovies->begin();
    auto endOfMovieTable = ofAllMovies->end();
    // While there are still elements in the hash table
    while (startOfMovieTable != endOfMovieTable) {
        // Delete each element in the hash table
        delete (*startOfMovieTable);
        startOfMovieTable++;
    }
    // Delete movie and actor hashtables
    delete ofAllMovies;
    delete this->ofActors;
}
