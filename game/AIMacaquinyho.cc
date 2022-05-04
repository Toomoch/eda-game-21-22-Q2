#include "Player.hh"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Macaquinyho


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  typedef vector<int> VI;
  map<int, int> kind;
  /**
   * Play method, invoked once per each round.
   */
  #define TAULER_SIZE 60
  int INF = numeric_limits<int>::max();

  bool pos_legal (Pos pos) {
    return pos.i >= 0 and pos.j >= 0 and pos.i < TAULER_SIZE and pos.j < TAULER_SIZE 
    and cell(pos).type == Granite;
  }

  bool target (Pos pos)
  {
    return cell(pos).type == Cave and cell(pos).treasure;
  }

  bool pos_stop_early (Pos pos)
  {

  }

  int bfs (Pos orig) {
    vector<vector<int> > dist(TAULER_SIZE,vector<int>(TAULER_SIZE, INF));
    if (pos_stop_early) return 0;

    queue<Pos> Q;
    Q.push(orig);
    dist[orig.i][orig.j] = 0;
    
    while (not Q.empty()) {
      Pos p = Q.front(); Q.pop();
      for (int k = 0; k < 8; ++k){
        Pos nova = p + Dir(k);
        if (pos_legal(nova) and dist[nova.i][nova.j] == INF) 
        {
          dist[nova.i][nova.j] = dist[p.i][p.j] + 1;
          if (target(nova)) return dist[nova.i][nova.j];
          Q.push(nova);
        }
      }
    }
    return -1;
    
  }
  void nans ()
  {
    VI D = dwarves(me());
    int n = D.size();
    for (int i = 0; i < n; ++i) 
    {
      int id = D[i];
    }
  }

  virtual void play () 
  {
    nans();
    
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
