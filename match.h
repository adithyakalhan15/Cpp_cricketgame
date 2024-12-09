#include <iostream>
#include <fstream>
#include <string>
#include "team.h"

using namespace std;

class Match{
    private:
        string venue;
    public:
        team TeamA;
        team TeamB;
        Match(){
            ifstream readfile("data/venue.txt");
            getline(readfile,venue);
    
            cout<<"Today match is from "<<venue<<endl;

            string teamAname;
            ifstream readAfile("data/teamA.txt");
            getline(readAfile, teamAname);
            TeamA.setteamname(teamAname);

            string teamBname;
            ifstream readBfile("data/teamB.txt");
            getline(readBfile, teamBname);
            TeamA.setteamname(teamBname);
        }; // create venue with this.
        // ~Match();
        void tossA(int x){TeamA.settoss(x);};
        void tossB(int x){TeamB.settoss(x);};
        bool gettossA(){return TeamA.gettoss();};
        bool gettossB();
        void updateAruns(int x){TeamA.updateruns(x);};
        void updateBruns(int x){TeamB.updateruns(x);};
        void updateAwkt(){TeamA.updatewhickets();};
        void updateBwkt(){TeamB.updatewhickets();};
};
