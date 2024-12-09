#ifndef team_H
#define team_H
#include <iostream>
using namespace std;

class team{
    private:
        string teamname;
        int runs = 0;
        int wickets = 0;
        int balls = 0;
        bool tossstatus;
    public:
        // team();
        void setteamname(string name){this->teamname = name;};
        void settoss(bool d){this->tossstatus = d;};
        void updateballs(){balls++;};
        bool gettoss(){return tossstatus;};
        void updateruns(int x){this->runs = this->runs+x;};
        int getruns(){return runs;};
        void updatewhickets(){wickets++;};
        int getwickets(){return wickets;};
        int getballs(){return balls;};
};

#endif