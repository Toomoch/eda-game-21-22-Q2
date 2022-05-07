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
    return cell(pos).type != Granite and cell(pos).type != Abyss /*and cell(pos).id != -1 and unit(cell(pos).id).type != Orc*/;
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

  int bfs (Pos &orig) {
    vector<vector<int> > dist(rows(),vector<int>(cols(), INF));
    if (stop_early(orig)) return 0;

    queue<Pos> Q;
    Q.push(orig);
    dist[orig.i][orig.j] = 0;
    
  int dist_min= INF;
  bool fin=true;

    while (not Q.empty()) 
    {
      Pos p = Q.front(); 
      Q.pop();
      fin=true;
      for (int k = 0; k < 8; ++k)
      {
        Pos nova = p + Dir(k);
        
        if (pos_ok(nova) and avoid(nova) and dist[nova.i][nova.j] == INF) 
        {
          if(cell(nova).type == Rock){
            dist[nova.i][nova.j] = dist[p.i][p.j] + cell(nova).turns;
          }
          else{
            dist[nova.i][nova.j] = dist[p.i][p.j] + 1;
          }
          if (target(nova) and dist_min>=dist[nova.i][nova.j]){
            dist_min=dist[nova.i][nova.j];
            //return dist[nova.i][nova.j];
          }
          if (dist_min>dist[nova.i][nova.j]){
            fin=false;
          }
          Q.push(nova);
        }
      }
      if(fin and dist_min!=INF){
        return dist_min;
      }
    }
    return dist_min;
    //return INF;
    
  }

  bool attack(Unit &nan)
  {
    
    for (int j = 0; j < 8; j++)
    {
      Dir newdir = Dir(j);
      Pos newpos = nan.pos + newdir;
      if (pos_ok(newpos)) 
      {
        int idattacked = cell(newpos).id;
        if (idattacked != -1 and unit(idattacked).player != me()) 
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
    vector<vector <bool> > Targeted (rows(), vector<bool> (cols(),true ));
    VI D = dwarves(me());
    int n = D.size();
    for (int i = 0; i < n; ++i) 
    {
      int id = D[i];
      Unit nan = unit(id);
      
      Dir movedir = None;
      int distmin = INF;
      if (not attack(nan))
      {
        for (int k = 0; k < 8; k++)
        {
          
          Dir newdir = Dir(k);
          Pos newpos = nan.pos + newdir;
          
          if (pos_ok(newpos) and avoid(newpos))
          {
            int dist = bfs(newpos);
            if (dist < distmin and Targeted[newpos.i][newpos.j]) 
            {
              movedir = newdir; 
              distmin = dist;
            }
          }
        }

        if (distmin != INF)
        {
          Pos newpos = nan.pos + movedir;
          Targeted[newpos.i][newpos.j]=false;
          command(id, movedir);
        } 
        
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
