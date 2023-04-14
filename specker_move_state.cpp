#include <iostream>
using namespace std;

class Move
{
public:
    // Take sc coins from heap sh and put tc coins to heap th.
    Move(int sh, int sc, int th, int tc): sh(sh),sc(sc),th(th),tc(tc){}

    int getSource() const{
        return sh;
    }
    int getSourceCoins() const{
        return sc;
    }
    int getTarget() const{
        return th;
    }
    int getTargetCoins() const{
        return tc;
    }

    friend ostream &operator<<(ostream &out, const Move &move){
        if (move.getTargetCoins() !=0){
        out << "takes " << move.sc << " coins from heap " << move.sh << " and puts " << move.tc << " coins to heap " << move.th;
        }
        else  out << "takes " << move.sc << " coins from heap " << move.sh << " and puts nothing";
        return out;
    }

private:
    int sh, sc,th,tc;
};

// class State
// {
// public:
//     // State with h heaps, where the i-th heap starts with c[i] coins.
//     // A total of n players are in the game, numbered from 0 to n-1,
//     // and player 0 is the first to play.
//     State(int h, const int c[], int n);
//     ~State();

//     void next(const Move &move) throw(logic_error);
//     bool winning() const;

//     int getHeaps() const;   
//     int getCoins(int h) const throw(logic_error);

//     int getPlayers() const;
//     int getPlaying() const;

//     friend ostream &operator<<(ostream &out, const State &state);
// };

int main(){
    Move move1 = Move(10,3,5,0);
    cout << move1;
}