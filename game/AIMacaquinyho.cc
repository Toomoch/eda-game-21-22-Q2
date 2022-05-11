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
  int INF = numeric_limits<int>::max();
  int bal = balrog_id();

  bool avoid (Pos &pos) 
  {
    //bool test = cell(pos).id != -1;
    return cell(pos).type != Granite and cell(pos).type != Abyss;
    //return ((cell(pos).type == Cave) or (cell(pos).type == Rock));
  }

  bool target (Pos &pos)
  {
    return cell(pos).treasure;
  }

  bool stop_early (Pos &pos)
  {
    return cell(pos).treasure;
  }

  Dir bfs (Pos &orig) {
    vector<vector<int> > dist(rows(),vector<int>(cols(), INF));
    if (stop_early(orig)) return None;
    //Pos temp = Pos(-1,-1);
    vector<vector<int> > parent(rows(),vector<int>(cols(),8));
    queue<Pos> Q;
    Q.push(orig);
    dist[orig.i][orig.j] = 0;
    
    for (int i = 0; i < 8; i++)
    {
      Pos temp = orig + Dir(i);
      if (pos_ok(temp)) parent[temp.i][temp.j] = i;
    }

    while (not Q.empty()) 
    {
      Pos p = Q.front(); 
      Q.pop();
      for (int k = 0; k < 8; ++k)
      {
        Pos nova = p + Dir(k);
        
        if (pos_ok(nova) and avoid(nova) and dist[nova.i][nova.j] == INF) 
        {
          dist[nova.i][nova.j] = dist[p.i][p.j] + 1;
          if (nova != orig + Dir(k)) parent[nova.i][nova.j] = parent[p.i][p.j];
          if (target(nova))
          { 
            return Dir(parent[nova.i][nova.j]);
          }
          Q.push(nova);
        }
      }
    }
    return None;
    
  }

  bool attack(Unit &nan)
  {
    
    for (int j = 0; j < 8; j++)
    {
      Dir newdir = Dir(j);
      Pos newpos = nan.pos + newdir;
      if (pos_ok(newpos)) 
      {
        int id2 = cell(newpos).id;
        if (id2 != -1 and unit(id2).player != me()) 
        { 
          command(nan.id, Dir(j));
          return true;
        }
      }
    }
    return false;

  }

  void nans ()
  {
    VI D = dwarves(me());
    int n = D.size();
    for (int i = 0; i < n; ++i) 
    {
      int id = D[i];
      Unit nan = unit(id);
      
      Dir movedir = bfs(nan.pos);
      int distmin = INF;

      if (not attack(nan)) 
      {
        command(id, bfs(nan.pos)); 
      }
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
