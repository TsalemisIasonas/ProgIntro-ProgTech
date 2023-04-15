#include <iostream>
#include "specker1n.cpp"
using namespace std;

class Player
{
public:
    Player(const string &n);
    virtual ~Player();

    virtual const string &getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream &operator<<(ostream &out, const Player &player);

private:
    string name;
};

Player::Player(const string &n) : name(n) {}

ostream &operator<<(ostream &out, const Player &player)
{
    out << player.getType() << "player" << player.name;
    return out;
}

class GreedyPlayer : public Player
{
public:
    GreedyPlayer(const string &n) : Player(n), type("Greedy") {}
    const string &getType() const override
    {
        return type;
    }
    Move play(const State &s) override
    {
        int heap = 0;
        int coins = 0;
        for (int i = 0; i < s.getHeaps(); i++)
            if (s.getCoins(i) > coins)
            {
                heap = i;
                coins = s.getCoins(i);
            }
        Move GreedyMove(heap, coins, 0, 0);
        return GreedyMove;
    }

private:
    string type;
};

class SpartanPlayer : public Player
{
public:
    SpartanPlayer(const string &n) : Player(n), type("Spartan") {}
    const string &getType() const override
    {
        return type;
    }
    Move play(const State &s) override
    {
        int heap = 0;
        int coins = 0;
        for (int i = 0; i < s.getHeaps(); i++)
            if (s.getCoins(i) > coins)
            {
                heap = i;
                coins = s.getCoins(i);
            }
        Move SpartanMove(heap, 1, 0, 0);
        return SpartanMove;
    }

private:
    string type;
};

class SneakyPlayer : public Player
{
public:
    SneakyPlayer(const string &n) : Player(n), type("Sneaky") {}
    const string &getType() const override
    {
        return type;
    }
    Move play(const State &s) override
    {
        int heap = 0;
        int coins = s.getCoins(0);
        for (int i = 1; i < s.getHeaps(); i++)
            if (s.getCoins(i) < coins)
            {
                heap = i;
                coins = s.getCoins(i);
            }
        Move SneakyMove(heap, coins, 0, 0);
        return SneakyMove;
    }

private:
    string type;
};


class RighteousPlayer : public Player
{
public:
    RighteousPlayer(const string &n) : Player(n), type("Righteous") {}
    const string &getType() const override
    {
        return type;
    }
    Move play(const State &s) override
    {
        int heap = 0;
        int coins = 0;
        int targetHeap = 0;
        int targetHeapCoins = s.getCoins(0);
        for (int i = 0; i < s.getHeaps(); i++)
            if (s.getCoins(i) > coins)
            {
                heap = i;
                coins = s.getCoins(i);
            }

        for (int i = 1; i < s.getHeaps(); i++)
            if (s.getCoins(i) < targetHeapCoins)
            {
                targetHeap = i;
                targetHeapCoins = s.getCoins(i);
            }

        Move RighteousMove(heap, coins/2, 0, (coins/2)-1);
        return RighteousMove;
    }

private:
    string type;
};