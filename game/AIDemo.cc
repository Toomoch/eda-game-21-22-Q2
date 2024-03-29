#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Demo


// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.


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

  map<int, int> kind; // For wizards: 0 -> random, 1 -> cyclic.

  void move_dwarves() {
    VI D = dwarves(me());
    int n = D.size();
    VI perm = random_permutation(n);
      // id is an own dwarf. For some reason (or not) we treat our dwarves in random order.
    for (int i = 0; i < n; ++i) {
      int id = D[perm[i]];
      if (random(0, 2) == 0) command(id, Dir(random(0, 7))); // With probability 1/3, we move at random.
      else { // Otherwise, ...
        bool enemy = false;
        for (int k = 0; not enemy and k < 8; ++k) {
          Pos p = unit(id).pos;
          if (pos_ok(p)) {
            int id2 = cell(p).id;
            if (id2 != -1 and unit(id2).player != me()) { // if we are next to an enemy, we attack.
              enemy = true;
              command(id, Dir(k));
            }
          }
        }
        // Finally, the following code does several things, most of them stupid.
        // It's just to show that there are many possibilities.
        if (not enemy) {
          if (round() < 40) command(id, Left);
          else if (round() > 180) command(id, None);
          else if (random(0, 1)) {
            set<Pos> S;
            while ((int)S.size() < 4) S.insert(Pos(random(0, 59), random(0, 59)));
            vector<Pos> V(S.begin(), S.end());
            if (V[random(0, 3)].i >= 30 ) command(id, Bottom);
            else command(id, RT);
          }
          else if (status(0) > 0.8) command(id, Left);
          else if (unit(id).health < 20) command(id, Dir(2*random(0, 3)));
          else if (cell(10, 20).owner == 2) command(id, TL);
          else if (nb_cells(3) > 50) command(id, LB);
          else if (nb_treasures(me()) < 4) command(id, BR);
          else if (cell(Pos(20, 30)).type == Cave) command(id, Bottom);
          else if (cell(Pos(2, 2)).treasure) command(id, Top);
          else cerr << unit(id).pos << endl; // You can print to cerr to debug.
        }
      }
    }
  }

  void move_wizards() {
    vector<int> W = wizards(me());
    for (int id : W) {
      if (kind.find(id) == kind.end()) kind[id] = random(0, 1);
      if (kind[id] == 0) command(id, Dir(2*random(0, 3)));
      else command(id, Dir(2*(round()%4)));
   }
  }


  /**
   * Play method, invoked once per each round.
   */
  void play () {
    move_dwarves();
    move_wizards();
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
