/**
 * TODO: add file header
 */

#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP

#include <string>
#include <vector>

using namespace std;

class ActorNode;

/**
 * TODO: add class header
 */
class MovieNode {
  protected:
    string movieName;
    vector<ActorNode*>* ofActors;

  public:
    MovieNode(string movieName);

    string getMovieName();

    void addActor(ActorNode* ofActor);

    vector<ActorNode*>* actorsInMovie();

    ~MovieNode();
};

#endif  // MOVIENODE_HPP