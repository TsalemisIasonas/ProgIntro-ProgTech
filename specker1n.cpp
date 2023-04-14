#include <iostream>
using namespace std;

class Move
{
public:
    // Take sc coins from heap sh and put tc coins to heap th.
    Move(int sh, int sc, int th, int tc);

    int getSource() const;
    int getSourceCoins() const;
    int getTarget() const;
    int getTargetCoins() const;

    friend ostream &operator<<(ostream &out, const Move &move);

private:
    int sh, sc, th, tc;
};

class State
{
public:
    // State with h heaps, where the i-th heap starts with c[i] coins.
    // A total of n players are in the game, numbered from 0 to n-1,
    // and player 0 is the first to play.
    State(int h, const int c[], int n);
    ~State();

    void next(const Move &move) throw(logic_error);
    bool winning() const;

    int getHeaps() const;
    int getCoins(int h) const throw(logic_error);

    int getPlayers() const;
    int getPlaying() const;

    friend ostream &operator<<(ostream &out, const State &state);

private:
    int h;
    int *c;
    int n;
    int player = 0;
};

Move::Move(int sh, int sc, int th, int tc) : sh(sh), sc(sc), th(th), tc(tc) {}
int Move::getSource() const { return sh; }
int Move ::getSourceCoins() const { return sc; }
int Move ::getTarget() const { return th; }
int Move ::getTargetCoins() const { return tc; }

ostream &operator<<(ostream &out, const Move &move)
{
    if (move.getTargetCoins() != 0)
    {
        out << "takes " << move.sc << " coins from heap " << move.sh << " and puts " << move.tc << " coins to heap " << move.th;
    }
    else
    {
        out << "takes " << move.sc << " coins from heap " << move.sh << " and puts nothing";
    }
    return out;
}

State::State(int h, const int c[], int n) : h(h), c(new int[h]), n(n) {
    for (int i = 0; i<h; i++){
        this->c[i] = c[i];
    }
}
State::~State() {delete[] c;}

void State::next(const Move &move) throw(logic_error){
    if (move.getSource()<0 || move.getSource()>=h || move.getTarget()<0 || move.getTarget()>=h){
        throw logic_error("invalid heap");
    }
    else if (move.getSourceCoins()<=0 || move.getTargetCoins()<0 || move.getTargetCoins()>=move.getSourceCoins() || c[move.getSource()]<move.getSourceCoins()){
        throw logic_error("invalid coins");
    }

    else {
        c[move.getSource()]-=move.getSourceCoins();
        c[move.getTarget()]+=move.getTargetCoins();

        if (player + 1 == n) player = 0;
        else player ++;
    }
}

bool State::winning() const {
    for (int i=0; i<h; i++){
        if (c[i] != 0) return false;
    }
    return true;
}
int State::getHeaps() const { return h; }
int State::getCoins(int h) const throw(logic_error)
{
    if (h < 0 || h >= this->h)
        throw logic_error("invalid heap");
    else return c[h];
}
int State::getPlayers() const { return n; }
int State::getPlaying() const { return player;}

ostream &operator<<(ostream &out, const State &state){
    out << state.c[0];
    for (int i=1; i<state.h; i++){
        out  << ", " << state.c[i];
    }
    out << " with " << state.getPlaying() << '/' << state.getPlayers() << " playing next";
    return out;
}

