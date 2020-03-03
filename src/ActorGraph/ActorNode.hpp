/**
 * TODO: add file header
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <string>
#include <vector>

using namespace std;

class MovieNode;

/**
 * TODO: add class header
 */
class ActorNode {
  protected:
    string actorName;
    vector<MovieNode*>* ofMovies;
    pair<ActorNode*, MovieNode*> ofPrevious;

  public:
    ActorNode(string actorName);

    string getActorName();

    void addMovie(MovieNode* ofMovie);

    vector<MovieNode*>* inMovies();

    void setPrevious(pair<ActorNode*, MovieNode*> ofPrevious);

    pair<ActorNode*, MovieNode*> getPrevious();

    ~ActorNode();
};

#endif  // ACTORNODE_HPP