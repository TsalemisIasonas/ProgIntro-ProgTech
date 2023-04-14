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

int Move::getSource() const {
    return sh;
}

int Move::getSourceCoins() const {
    return sc;
}

int Move::getTarget() const {
    return th;
}

int Move::getTargetCoins() const {
    return tc;
}

ostream &operator<<(ostream &out, const Move &move) {
    out << "Move(" << move.getSourceCoins() << " coins from heap " << move.getSource()
            << " to heap " << move.getTarget() << " with " << move.getTargetCoins() << " coins)";
    return out;
}

State::State(int h, const int c[], int n) : h(h), c(new int[h]), n(n) {
    for (int i = 0; i < h; i++) {
        this->c[i] = c[i];
    }
}

State::~State() {
    delete[] c;
}

void State::next(const Move &move) throw(logic_error) {
    // TODO: implement this function
}

bool State::winning() const {
    // TODO: implement this function
}

int State::getHeaps() const {
    return h;
}

int State::getCoins(int h) const throw(logic_error) {
    if (h < 0 || h >= this->h) {
        throw logic_error("Heap index out of bounds");
    }
    return c[h];
}

int State::getPlayers() const {
    return n;
}

int State::getPlaying() const {
    return player;
}

ostream &operator<<(ostream &out, const State &state) {
    out << "State(" << state.getHeaps() << " heaps,";
    for (int i = 0; i < state.getHeaps(); i++) {
        out << " heap " << i << ": " << state.getCoins(i) << " coins,";
    }
    out << " player " << state.getPlaying() << " playing)";
    return out;
}

bool State::winning() const {
    int total_coins = 0;
    for(int i=0; i<h; i++){
      total_coins += c[i];
    }
    return total_coins == 0;  // If the total number of coins in all heaps is 0, then the current player has won.
}
void State::next(const Move &move) throw(logic_error) {
    // Ensure that source heap and target heap are within bounds
    if (move.getSource() < 0 || move.getSource() >= h || move.getTarget() < 0 || move.getTarget() >= h) {
        throw logic_error("Heap index out of bounds");
    }

    // Ensure that the move is valid
    if (move.getSourceCoins() <= 0 || move.getTargetCoins() <= 0 || move.getSourceCoins() > c[move.getSource()] ||
        move.getTargetCoins() > c[move.getTarget()]) {
        throw logic_error("Invalid move");
    }
    
    // Update the state of the game
    c[move.getSource()] -= move.getSourceCoins();
    c[move.getTarget()] -= move.getTargetCoins();
    player = (player + 1) % n; // switch to next player
}
