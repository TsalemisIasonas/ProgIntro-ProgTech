#include <iostream>
#include <stdexcept>
#include "specker2n.cpp"
using namespace std;

class Game {
public:
    Game(int heaps, int players);
    ~Game();

    void addHeap(int coins);
    void addPlayer(Player* player);
    void play(std::ostream& out);

    int getPlayers() const;
    const Player* getPlayer(int p) const;

private:
    int heaps;
    int players;
    int heapCounter= 0;
    int playerCounter= 0;
    int* totalHeaps;
    Player** totalPlayers;
};

Game::Game(int heaps, int players): heaps(heaps),players(players),totalHeaps(new int[heaps]),totalPlayers(new Player*[players]){}

Game::~Game()
{
    delete[] totalHeaps;
    delete[] totalPlayers;
}

int Game::getPlayers() const
{
    return players;
}

void Game::addHeap(int coins)
{
    if (coins < 0) {
        throw logic_error("invalid coins");
    }
    else if (heapCounter>= heaps) {
        throw logic_error("invalid heaps index");
    }
    else {
        totalHeaps[heapCounter] = coins;
        heapCounter++;
    }
}

void Game::addPlayer(Player* player)
{
    if (player == nullptr) {
        throw logic_error("invalid player");
    }
    else if (playerCounter >= players) {
        throw logic_error("invalid players index");
    }
    else {
        totalPlayers[playerCounter] = player;
        playerCounter++;
    }
}

const Player* Game::getPlayer(int p) const
{
    if (p < 0 || p >= players) {
        throw logic_error("invalid player index");
    }
    else {
        return totalPlayers[p];
    }
}

void Game::play(std::ostream& out)
{
    if (playerCounter!= players || heapCounter != heaps) {
        throw logic_error("Index Error");
    }
    else {
        State s(heaps, totalHeaps, players);
        while (true) {
            if (s.winning()) {
                int index = (s.getPlaying() == 0) ? players - 1 : s.getPlaying() - 1;
                out << "State: " << s << endl;
                out << *totalPlayers[index] << " wins" << endl;
                break;
            }
            else {
                out << "State: " << s << endl;
                out << *getPlayer(s.getPlaying()) << ' ' << totalPlayers[s.getPlaying()]->play(s) << endl;
                s.next(totalPlayers[s.getPlaying()]->play(s));
            }
        }
    }
}


