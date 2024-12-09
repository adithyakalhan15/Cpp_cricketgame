#ifndef player_H
#define player_H
#include <iostream>
#include "team.h"
using namespace std;

class player {
private:
    string playername;
    int playerruns = 0;
    int wkts = 0;
    int bowledruns = 0;
    int balls = 0;
    int fours = 0;
    int sixes = 0;
    int bowledballs = 0;
    int strikerate = 0;

public:
    // player();
    void setname(string name) { this->playername = name; };
    void updateplayerruns(int x) { this->playerruns = this->playerruns + x; };
    void updateballs() { balls++; };
    void updatewkts() { wkts++; };
    void updatebowlruns(int x) { this->bowledruns = this->bowledruns + x; };
    void updatefours() { fours++; };
    void updatesixes() { sixes++; };
    void updatebowledballs() { bowledballs++; };
    void setstrike(int strike){this->strikerate = strike;};
    int getplayerruns() { return playerruns; };
    int getwkts() { return wkts; };
    int getbowledruns() { return bowledruns; };
    int getbowledballs() { return bowledballs; };
    int getballs() { return balls; };
    int getfours() { return fours; };
    int getsixes() { return sixes; };
    int getstrike(){return strikerate;};
    string getname() { return playername; };
};

#endif