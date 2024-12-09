#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <thread>
#include <chrono>
#include "batsman.h"
#include "match.h"

using namespace std;

int playerAno, playerBno, teamAwkts, teamBwkts;
int teamAballs, teamBballs;

int noOfovers = 3;

Match match1;
Batsman batmanA[11];
Batsman batmanB[11];

void firstbatting();
void maingame();
void createplayers();
void swapplayers(int &a, int &b);
void scorecard();
void scorecardB();
void finalScore();
void calover(int balls);

int randomgen();
int selectbowlerA(int current);
int selectbowlerB(int current);
int newplayer(int batman1, int batman2);

float calculateSR(int x, int y);
float calculateEcon(int x, int y);

int main(){
    srand(time(0));
    firstbatting();
    this_thread::sleep_for(chrono::seconds(1));
    createplayers();
    system("CLS");
    maingame();
    // finalScore();

    return 0;
};

void firstbatting(){
    int tossresult = randomgen();
    if(tossresult<51){
        int captaindecision = randomgen();
        if(captaindecision <51){
            match1.tossA(1);
            match1.tossB(0);
            cout<<"Team A won the toss and decided to bat first."<<endl;
        }else{
            match1.tossA(0);
            match1.tossB(1);
            cout<<"Team A won the toss and decided to bowl first."<<endl;
        }
    }else{
        int captaindecision = randomgen();
        if(captaindecision <51){
            match1.tossA(0);
            match1.tossB(1);
            cout<<"Team B won the toss and decided to bat first."<<endl;
        }else{
            match1.tossA(1);
            match1.tossB(0);
            cout<<"Team B won the toss and decided to bowl first."<<endl;
        }
    }
};

void maingame(){
    srand(time(0));

    if(match1.gettossA() == 1){
    int ply1 = 0; //batman 1
    int ply2 = 1; //batman 2
    int bwl = 0; //bowler
    int runs;
        
    while(match1.TeamA.getwickets()<10 && match1.TeamA.getballs()<noOfovers*6){ //first inning team A.
    
    bwl = selectbowlerB(bwl);
    for(int j=0; j<6;j++){
        runs = batmanA[ply1].calculateruns(randomgen(),ply1);
        if(match1.TeamA.getwickets()<10){
        // overs = (teamAballs/6)+(teamAballs%6)/10;
        if(runs == 1 || runs == 3){
            batmanA[ply1].updateplayerruns(runs);
            batmanA[ply1].updateballs();
            match1.TeamA.updateruns(runs);
            match1.TeamA.updateballs();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatebowlruns(runs);
            calover(match1.TeamA.getballs());
            cout<<" : "<<runs<<" for "<<batmanA[ply1].getname()<<endl;
            swapplayers(ply1,ply2);
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 7){   //out
            calover(match1.TeamA.getballs());
            cout<<" : "<<"OUT !, "<<batmanA[ply1].getname()<<endl;
            batmanA[ply1].updateballs();
            ply1 = newplayer(ply1, ply2);
            match1.TeamA.updatewhickets();
            match1.TeamA.updateballs();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatewkts();
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 8){ //wide ball
            j=j-1;
            match1.TeamA.updateruns(1);
            calover(match1.TeamA.getballs());
            cout<<" : "<<"wide ball."<<endl;
            batmanB[bwl].updatebowlruns(1);
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 4){
            batmanA[ply1].updateplayerruns(runs);
            batmanA[ply1].updateballs();
            match1.TeamA.updateruns(runs);
            match1.TeamA.updateballs();
            batmanA[ply1].updatefours();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatebowlruns(runs);
            calover(match1.TeamA.getballs());
            cout<<" : "<<runs<<" for "<<batmanA[ply1].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 6){
            batmanA[ply1].updateplayerruns(runs);
            batmanA[ply1].updateballs();
            match1.TeamA.updateruns(runs);
            match1.TeamA.updateballs();
            batmanA[ply1].updatesixes();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatebowlruns(runs);
            calover(match1.TeamA.getballs());
            cout<<" : "<<runs<<" for "<<batmanA[ply1].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }else{
            batmanA[ply1].updateplayerruns(runs);
            batmanA[ply1].updateballs();
            match1.TeamA.updateruns(runs);
            match1.TeamA.updateballs();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatebowlruns(runs);
            calover(match1.TeamA.getballs());
            cout<<" : "<<runs<<" for "<<batmanA[ply1].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        system("CLS");
        scorecard();
        this_thread::sleep_for(chrono::seconds(2));
        }else{
            break;
        }
    }
    swapplayers(ply1,ply2);
    system("CLS");
    cout<<"Marks for the team A after overs : "<<match1.TeamA.getruns()<<", wickets : "<<match1.TeamA.getwickets()<<endl;
    this_thread::sleep_for(chrono::seconds(2));
}

        cout<<"1st Inning ended. Let's goto the second Inning."<<endl;
        scorecard();
        system("CLS");
        cout<<"Team B Start to bat."<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        
        int ply3 = 0;
        int ply4 = 1;
        int bwl2;

        while(match1.TeamB.getwickets()<10 && match1.TeamB.getballs()<noOfovers*6 && match1.TeamB.getruns()<match1.TeamA.getruns()){ //2nd inning team B
        bwl2 = selectbowlerA(bwl2);
    for(int j=0; j<6;j++){
        runs = batmanB[ply3].calculateruns(randomgen(),ply3);
        if(match1.TeamB.getwickets()<10 && match1.TeamB.getruns()<match1.TeamA.getruns()){
        // overs = (teamAballs/6)+(teamAballs%6)/10;
        if(runs == 1 || runs == 3){
            batmanB[ply3].updateplayerruns(runs);
            batmanB[ply3].updateballs();
            match1.TeamB.updateruns(runs);
            match1.TeamB.updateballs();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatebowlruns(runs);
            calover(match1.TeamB.getballs());
            cout<<" : "<<runs<<" for "<<batmanB[ply3].getname()<<endl;
            swapplayers(ply3,ply4);
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 7){   //out
            calover(match1.TeamB.getballs());
            cout<<" : "<<"OUT !, "<<batmanB[ply3].getname()<<endl;
            batmanB[ply3].updateballs();
            ply3= newplayer(ply3, ply4);
            match1.TeamB.updatewhickets();
            match1.TeamB.updateballs();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatewkts();
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 8){ //wide ball
            j=j-1;
            match1.TeamB.updateruns(1);
            calover(match1.TeamB.getballs());
            cout<<" : "<<"wide ball."<<endl;
            batmanA[bwl2].updatebowlruns(1);
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 4){
            batmanB[ply3].updateplayerruns(runs);
            batmanB[ply3].updateballs();
            match1.TeamB.updateruns(runs);
            match1.TeamB.updateballs();
            batmanB[ply3].updatefours();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatebowlruns(runs);
            calover(match1.TeamB.getballs());
            cout<<" : "<<runs<<" for "<<batmanB[ply3].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 6){
            batmanB[ply3].updateplayerruns(runs);
            batmanB[ply3].updateballs();
            match1.TeamB.updateruns(runs);
            match1.TeamB.updateballs();
            batmanB[ply3].updatesixes();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatebowlruns(runs);
            calover(match1.TeamB.getballs());
            cout<<" : "<<runs<<" for "<<batmanB[ply3].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }else{
            batmanB[ply3].updateplayerruns(runs);
            batmanB[ply3].updateballs();
            match1.TeamB.updateruns(runs);
            match1.TeamB.updateballs();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatebowlruns(runs);
            calover(match1.TeamB.getballs());
            cout<<" : "<<runs<<" for "<<batmanB[ply3].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        system("CLS");
        scorecardB();
        this_thread::sleep_for(chrono::seconds(2));

        }else{
            break;
        }
    }
    swapplayers(ply3,ply4);
    system("CLS");
    cout<<"Marks for the team A after overs : "<<match1.TeamB.getruns()<<", wickets : "<<match1.TeamB.getwickets()<<endl;
    this_thread::sleep_for(chrono::seconds(2));
        }

        scorecardB();
        system("CLS");

        if(match1.TeamA.getruns()>match1.TeamB.getruns()){
            finalScore();
            cout<<"Team A win."<<endl;
        }else if(match1.TeamA.getruns()<match1.TeamB.getruns()){
            finalScore();
            cout<<"Team B wins"<<endl;
        }else{
            finalScore();
            cout<<"Match Drwan.";
        }


    }else{
        int ply3 = 0; //batman 1
        int ply4 = 1; //batman 2
        int bwl2 = 0; //bowler
        int runs;

        while(match1.TeamB.getwickets()<10 && match1.TeamB.getballs()<noOfovers*6){ //first inning team B
            bwl2 = selectbowlerA(bwl2);
    for(int j=0; j<6;j++){
        if(match1.TeamB.getwickets()<10){
        runs = batmanB[ply3].calculateruns(randomgen(),ply3);
        // overs = (teamAballs/6)+(teamAballs%6)/10;
        if(runs == 1 || runs == 3){
            batmanB[ply3].updateplayerruns(runs);
            batmanB[ply3].updateballs();
            match1.TeamB.updateruns(runs);
            match1.TeamB.updateballs();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatebowlruns(runs);
            calover(match1.TeamB.getballs());
            cout<<" : "<<runs<<" for "<<batmanB[ply3].getname()<<endl;
            swapplayers(ply3,ply4);
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 7){   //out
            calover(match1.TeamB.getballs());
            cout<<" : "<<"OUT !, "<<batmanB[ply3].getname()<<endl;
            batmanB[ply3].updateballs();
            ply3= newplayer(ply3, ply4);
            match1.TeamB.updatewhickets();
            match1.TeamB.updateballs();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatewkts();
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 8){ //wide ball
            j=j-1;
            match1.TeamB.updateruns(1);
            calover(match1.TeamB.getballs());
            cout<<" : "<<"wide ball."<<endl;
            batmanA[bwl2].updatebowlruns(1);
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 4){
            batmanB[ply3].updateplayerruns(runs);
            batmanB[ply3].updateballs();
            match1.TeamB.updateruns(runs);
            match1.TeamB.updateballs();
            batmanB[ply3].updatefours();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatebowlruns(runs);
            calover(match1.TeamB.getballs());
            cout<<" : "<<runs<<" for "<<batmanB[ply3].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 6){
            batmanB[ply3].updateplayerruns(runs);
            batmanB[ply3].updateballs();
            match1.TeamB.updateruns(runs);
            match1.TeamB.updateballs();
            batmanB[ply3].updatesixes();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatebowlruns(runs);
            calover(match1.TeamB.getballs());
            cout<<" : "<<runs<<" for "<<batmanB[ply3].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }else{
            batmanB[ply3].updateplayerruns(runs);
            batmanB[ply3].updateballs();
            match1.TeamB.updateruns(runs);
            match1.TeamB.updateballs();
            batmanA[bwl2].updatebowledballs();
            batmanA[bwl2].updatebowlruns(runs);
            calover(match1.TeamB.getballs());
            cout<<" : "<<runs<<" for "<<batmanB[ply3].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        system("CLS");
        scorecardB();
        this_thread::sleep_for(chrono::seconds(2));
        }else{
            break;
        }
    }
    swapplayers(ply3,ply4);
    system("CLS");
    cout<<"Marks for the team B after overs : "<<match1.TeamB.getruns()<<", wickets : "<<match1.TeamB.getwickets()<<endl;
    this_thread::sleep_for(chrono::seconds(2));
        }
    
    cout<<"1st Inning ended. Let's goto the second Inning."<<endl;
    scorecardB();
    system("CLS");
    cout<<"Team A Start to bat."<<endl;
    this_thread::sleep_for(chrono::seconds(2));

    int ply1 = 0; //batman 1
    int ply2 = 1; //batman 2
    int bwl = 0; //bowler

    while(match1.TeamA.getwickets()<10 && match1.TeamA.getballs()<noOfovers*6 && match1.TeamA.getruns()<match1.TeamB.getruns()){ //team A 2nd inning.
        bwl = selectbowlerB(bwl); 
    for(int j=0; j<6;j++){
        runs = batmanA[ply1].calculateruns(randomgen(),ply1);
        if(match1.TeamA.getwickets()<10 && match1.TeamA.getruns()<match1.TeamB.getruns()){
        // overs = (teamAballs/6)+(teamAballs%6)/10;
        if(runs == 1 || runs == 3){
            batmanA[ply1].updateplayerruns(runs);
            batmanA[ply1].updateballs();
            match1.TeamA.updateruns(runs);
            match1.TeamA.updateballs();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatebowlruns(runs);
            calover(match1.TeamA.getballs());
            cout<<" : "<<runs<<" for "<<batmanA[ply1].getname()<<endl;
            swapplayers(ply1,ply2);
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 7){   //out
            calover(match1.TeamA.getballs());
            cout<<" : "<<"OUT !, "<<batmanA[ply1].getname()<<endl;
            batmanA[ply1].updateballs();
            ply1 = newplayer(ply1, ply2);
            match1.TeamA.updatewhickets();
            match1.TeamA.updateballs();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatewkts();
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 8){ //wide ball
            j=j-1;
            match1.TeamA.updateruns(1);
            calover(match1.TeamA.getballs());
            cout<<" : "<<"wide ball."<<endl;
            batmanB[bwl].updatebowlruns(1);
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 4){
            batmanA[ply1].updateplayerruns(runs);
            batmanA[ply1].updateballs();
            match1.TeamA.updateruns(runs);
            match1.TeamA.updateballs();
            batmanA[ply1].updatefours();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatebowlruns(runs);
            calover(match1.TeamA.getballs());
            cout<<" : "<<runs<<" for "<<batmanA[ply1].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }else if(runs == 6){
            batmanA[ply1].updateplayerruns(runs);
            batmanA[ply1].updateballs();
            match1.TeamA.updateruns(runs);
            match1.TeamA.updateballs();
            batmanA[ply1].updatesixes();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatebowlruns(runs);
            calover(match1.TeamA.getballs());
            cout<<" : "<<runs<<" for "<<batmanA[ply1].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }else{
            batmanA[ply1].updateplayerruns(runs);
            batmanA[ply1].updateballs();
            match1.TeamA.updateruns(runs);
            match1.TeamA.updateballs();
            batmanB[bwl].updatebowledballs();
            batmanB[bwl].updatebowlruns(runs);
            calover(match1.TeamA.getballs());
            cout<<" : "<<runs<<" for "<<batmanA[ply1].getname()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        system("CLS");
        scorecard();
        this_thread::sleep_for(chrono::seconds(2));
        }else{
            break;
        }
    }
    swapplayers(ply1,ply2);
    system("CLS");
    cout<<"Marks for the team A after overs : "<<match1.TeamA.getruns()<<", wickets : "<<match1.TeamA.getwickets()<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    }

    scorecard();
    system("CLS");

    if(match1.TeamA.getruns()>match1.TeamB.getruns()){
        finalScore();
        cout<<"Team A win."<<endl;
    }else if(match1.TeamA.getruns()<match1.TeamB.getruns()){
        finalScore();
        cout<<"Team B wins"<<endl;
    }else{
        finalScore();
        cout<<"Match Drwan.";
    }
    
    }
}

void createplayers(){
    ifstream readfileA("data/playersA.txt");
    playerAno = 0;
    string name;
    while(!readfileA.eof()){
        getline(readfileA, name);
        batmanA[playerAno].setname(name);
        playerAno++;
    }
    
    readfileA.close();

    playerBno = 0;
    ifstream readfileB("data/playersB.txt");
    while(!readfileB.eof()){
        getline(readfileB, name);
        batmanB[playerBno].setname(name);
        playerBno++;
    };

    readfileB.close();

    cout<<"\v\tTeam A playing IX"<<"\t\t\tTeam B playing IX.\v"<<endl;
    for(int i=0;i<11;i++){
        cout<<"\t"<<batmanA[i].getname()<<"\t"<<"\t\t\t"<<batmanB[i].getname()<<endl;
    }
};

int selectbowlerA(int current){
    // srand(time(0));
    int b = rand()%5;
    int newball = 10 -b;
    if(current == newball || batmanA[newball].getbowledballs() == 24){
        return selectbowlerA(current);
    }else{
        return newball;
    }
};

int selectbowlerB(int current){
    int b = rand()%5;
    int newball = 10 -b;
    if(current == newball || batmanB[newball].getbowledballs() == 24){
        return selectbowlerB(current);
    }else{
        return newball;
    }
}

void scorecard(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Setting the text color to blue
    SetConsoleTextAttribute(hConsole, 3);
    // for(int i = 0; i<20; i++){
    //     SetConsoleTextAttribute(hConsole, i);
    //     std::cout << "This text is blue!" << std::endl;
    // }

    cout<<"\t\t\t\tTeam A Batting"<<endl;
    cout<<"_________________________________________________________________________________"<<endl;
    SetConsoleTextAttribute(hConsole, 4);
    cout<<"\vPlayer"<<"\t\t\tRuns"<<"\tBalls"<<"\t4s"<<"\t6s"<<"\tStrike Rate"<<endl;
    SetConsoleTextAttribute(hConsole, 6);
    for(int i=0;i<11;i++){
        cout<<"\v"<<batmanA[i].getname()<<"\t\t"<<batmanA[i].getplayerruns()<<"\t"<<batmanA[i].getballs()<<"\t"<<batmanA[i].getfours()<<"\t"<<batmanA[i].getsixes()<<"\t"<<calculateSR(batmanA[i].getplayerruns(), batmanA[i].getballs());
    };
    cout<<endl;
    
    SetConsoleTextAttribute(hConsole, 3);
    cout<<"\v\v\t\t\t\tTeam B Bowling"<<endl;
    cout<<"_________________________________________________________________________________"<<endl;
    SetConsoleTextAttribute(hConsole, 4);
    cout<<"\vPlayer"<<"\t\t\t\tWickets"<<"\tOvers"<<"\tRuns"<<"\tEconomy"<<endl;
    SetConsoleTextAttribute(hConsole, 6);
    for(int i=0;i<5;i++){
        cout<<"\v"<<batmanB[10-i].getname()<<"\t\t\t"<<batmanB[10-i].getwkts()<<"\t"<<batmanB[10-i].getbowledballs()<<"\t"<<batmanB[10-i].getbowledruns()<<"\t"<<calculateEcon(batmanB[10-i].getbowledruns(), batmanB[10-i].getbowledballs());
    };
    cout<<endl;

}

void scorecardB(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Setting the text color to blue
    SetConsoleTextAttribute(hConsole, 3);
    // for(int i = 0; i<20; i++){
    //     SetConsoleTextAttribute(hConsole, i);
    //     std::cout << "This text is blue!" << std::endl;
    // }

    cout<<"\t\t\t\tTeam B Batting"<<endl;
    cout<<"_________________________________________________________________________________"<<endl;
    SetConsoleTextAttribute(hConsole, 4);
    cout<<"\vPlayer"<<"\t\t\tRuns"<<"\tBalls"<<"\t4s"<<"\t6s"<<"\tStrike Rate"<<endl;
    SetConsoleTextAttribute(hConsole, 6);
    for(int i=0;i<11;i++){
        cout<<"\v"<<batmanB[i].getname()<<"\t\t"<<batmanB[i].getplayerruns()<<"\t"<<batmanB[i].getballs()<<"\t"<<batmanB[i].getfours()<<"\t"<<batmanB[i].getsixes()<<"\t"<<calculateSR(batmanB[i].getplayerruns(), batmanB[i].getballs());
    };
    cout<<endl;
    
    SetConsoleTextAttribute(hConsole, 3);
    cout<<"\v\v\t\t\t\tTeam A Bowling"<<endl;
    cout<<"_________________________________________________________________________________"<<endl;
    SetConsoleTextAttribute(hConsole, 4);
    cout<<"\vPlayer"<<"\t\t\t\tWickets"<<"\tOvers"<<"\tRuns"<<"\tEconomy"<<endl;
    SetConsoleTextAttribute(hConsole, 6);
    for(int i=0;i<5;i++){
        cout<<"\v"<<batmanA[10-i].getname()<<"\t\t\t"<<batmanA[10-i].getwkts()<<"\t"<<batmanA[10-i].getbowledballs()<<"\t"<<batmanA[10-i].getbowledruns()<<"\t"<<calculateEcon(batmanA[10-i].getbowledruns(), batmanA[10-i].getbowledballs());
    };
    cout<<endl;
}

int newplayer(int batman1, int batman2){
    int new_batman;
    if(batman1 > batman2){
        new_batman = batman1+1;
    }else{
        new_batman = batman1+2;
    }
    return new_batman;
}

void swapplayers(int &a, int &b){
    int temp = b;
    b=a;
    a= temp;
}

int randomgen(){
    return rand()%100;
}

void finalScore(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 3);
    cout<<"Team A "<<"\t\t\t"<<match1.TeamA.getruns()<<"/"<<match1.TeamA.getwickets()<<endl;
    calover(match1.TeamA.getballs());
    cout<<"\v"<<endl;
    SetConsoleTextAttribute(hConsole, 6);
    for(int k=0; k<11; k++){
        cout<<batmanA[k].getname()<<"\t\t"<<batmanA[k].getplayerruns()<<endl;
    }

    cout<<"\v"<<endl;
    SetConsoleTextAttribute(hConsole, 3);
    cout<<"Team B "<<"\t\t\t"<<match1.TeamB.getruns()<<"/"<<match1.TeamB.getwickets()<<endl;
    calover(match1.TeamB.getballs());
    cout<<"\v"<<endl;
    SetConsoleTextAttribute(hConsole, 6);
    for(int k=0; k<11; k++){
        cout<<batmanB[k].getname()<<"\t\t"<<batmanB[k].getplayerruns()<<endl;
    }
}

void calover(int balls){
    int overs = balls/6;
    int remain = balls%6;

    cout<<overs<<"."<<remain;
}

float calculateSR(int x, int y){
    if(x>0 && y>0){
        return (x*1.0/y*1.0)*100;
    }else{
        return 0;
    }
}

float calculateEcon(int x, int y){
    if(x>0 && y>0){
        return (x/(y/6.0));
    }else{
        return 0;
    }
}