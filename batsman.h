#include <iostream>
#include "player.h"
using namespace std;

class Batsman: public player{
    public:
        // Batsman();
        int calculateruns(int y, int number){
            //assume maximum strike rate is 200.
            if(y<25+number){
                return 1;
            }else if(y<45+number){
                return 2;
            }else if(y<55+number){
                return 3;
            }else if(y<67-number){
                return 4;
            }else if(y<82-number*2){
                return 6;
            }else if(y<90){
                return 7;
            }else{
                return 8;
            }
        }
};