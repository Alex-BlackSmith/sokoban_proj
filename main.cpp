#include <libtcod.hpp>
#include "TwoDimArray.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <map>


using std::string;
using std::map;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::vector;
using std::ostream;
using std::fstream;
using std::getline;






//overload << operator
ostream& operator<<(ostream& stream, TwoDimArray<char>& TwoDArray) {
    for (auto i = 0; i < TwoDArray.length; i++){
        for (auto j = 0; j < TwoDArray.width; j++){
            stream << TwoDArray.getObjPos(i,j);
        }
        cout << endl;
    }
    return stream;
}

//overload >> operator
ifstream& operator>> (ifstream &file, TwoDimArray<char> &TwoDArray) {
    unsigned len, wth;
    file >> len >> wth;
    TwoDimArray<char> mapLocal(len, wth);
    TwoDArray = mapLocal;
    string buf;
    getline(file,buf);
    for (auto i = 0; i < len ; i++){
        for (auto j = 0; j <= wth; j++){
            TwoDArray.setObjPos(i,j,file.get());
        }
    }
}

void updateWinPositions(map<vector<int>,char>& mapOfWinPositions, const vector<TCODColor>& colVec);

void chkKeyPressAndMovePlayer(vector<int>& tmpPlrPos, const vector<TCODColor>& colourVec);

bool ifWin(map<vector<int>,char>& mapOfWinPositions);

void firstPaintOfScreen(TwoDimArray<char>& TwoDArray, const vector<TCODColor>& colourVec, vector<int>& tmpPlrPos, map<vector<int>,char>& mapCharWin);

int main() {
    ifstream in("TestMap.txt"); //read txt file
    TwoDimArray<char> Test; //create instance of 2DArray class
    in >> Test; //load map from txt into 2DArray
    const TCODColor player {0,255,0};
    const TCODColor wall{255,0,0};
    const TCODColor box{255,255,0};
    const TCODColor winCross{255,255,255};
    const vector<TCODColor> colourVec = {player, wall, box, winCross}; //0 - player, 1 - wall, 2 - box, 3 - winCross
    vector<int> tempPlrPos; //temporary player position vector (x,y)
    map<vector<int>,char> mapCharWin; // vector of win positions "(x,y) - character"



    firstPaintOfScreen(Test, colourVec, tempPlrPos, mapCharWin);

    while (!ifWin(mapCharWin)) {
        updateWinPositions(mapCharWin, colourVec);
        chkKeyPressAndMovePlayer(tempPlrPos, colourVec);
    }

    TCODConsole::initRoot(Test.getDimX(),Test.getDimY(),"Winner", false, TCOD_RENDERER_GLSL);
    while (1) {}
    return 0;
}

void updateWinPositions(map<vector<int>,char>& mapOfWinPositions, const vector<TCODColor>& colVec) {
    for (auto &cross : mapOfWinPositions) {
        if (TCODConsole::root->getChar(cross.first[0], cross.first[1]) == 'X') {
            TCODConsole::root->setCharBackground(cross.first[0], cross.first[1], colVec[3]);
            cross.second = 'X';
        } else if (TCODConsole::root->getChar(cross.first[0], cross.first[1]) == 'B') {
            TCODConsole::root->setCharBackground(cross.first[0], cross.first[1], colVec[2]);
            cross.second = 'B';
        } else if (TCODConsole::root->getChar(cross.first[0], cross.first[1]) == 'P') {
            TCODConsole::root->setCharBackground(cross.first[0], cross.first[1], colVec[0]);
            cross.second = 'P';
        } else if (TCODConsole::root->getChar(cross.first[0], cross.first[1]) == ' ') {
            TCODConsole::root->setChar(cross.first[0], cross.first[1], 'X');
            TCODConsole::root->setCharBackground(cross.first[0], cross.first[1], colVec[3]);
        }
    }
}

void chkKeyPressAndMovePlayer(vector<int>& tmpPlrPos, const vector<TCODColor>& colVec){
    TCOD_key_t key = TCODConsole::checkForKeypress();
    TCODConsole::root->flush();
    if ( key.c == 'w' || key.c == 'W' ) {
        if (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 1) != '#'){
            if (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 1) != 'B'){
                TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] - 1, 'P');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] - 1,colVec[0]);
                TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                tmpPlrPos = {tmpPlrPos[0], tmpPlrPos[1] - 1};
            }
            else if ((TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 1) == 'B')
                     && (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 2) != '#')
                     && (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 2) != 'B')){
                TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] - 1, 'P');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] - 1,colVec[0]);
                TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] - 2, 'B');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] - 2,colVec[2]);
                TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                tmpPlrPos = {tmpPlrPos[0], tmpPlrPos[1] - 1};
            }
        }
        TCODConsole::root->flush();
    }
    else if ( key.c == 'a' || key.c == 'A' ) {
        if (TCODConsole::root -> getChar(tmpPlrPos[0] - 1, tmpPlrPos[1]) != '#'){
            if (TCODConsole::root -> getChar(tmpPlrPos[0] - 1, tmpPlrPos[1]) != 'B'){
                TCODConsole::root -> setChar(tmpPlrPos[0] - 1, tmpPlrPos[1], 'P');
                TCODConsole::root->setCharBackground(tmpPlrPos[0] - 1, tmpPlrPos[1],colVec[0]);
                TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                tmpPlrPos = {tmpPlrPos[0] - 1, tmpPlrPos[1]};
            }

            else if ((TCODConsole::root -> getChar(tmpPlrPos[0] - 1, tmpPlrPos[1]) == 'B')
                     && (TCODConsole::root -> getChar(tmpPlrPos[0] - 2, tmpPlrPos[1]) != '#')
                     && (TCODConsole::root -> getChar(tmpPlrPos[0] - 2, tmpPlrPos[1]) != 'B')){
                TCODConsole::root -> setChar(tmpPlrPos[0] - 1, tmpPlrPos[1], 'P');
                TCODConsole::root->setCharBackground(tmpPlrPos[0] - 1, tmpPlrPos[1],colVec[0]);
                TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                TCODConsole::root -> setChar(tmpPlrPos[0] - 2, tmpPlrPos[1], 'B');
                TCODConsole::root->setCharBackground(tmpPlrPos[0] - 2, tmpPlrPos[1],colVec[2]);
                tmpPlrPos = {tmpPlrPos[0] - 1, tmpPlrPos[1]};
            }
        }
        TCODConsole::root->flush();
    }
    else if ( key.c == 's' || key.c == 'S' ) {
        if (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 1) != '#'){
            if (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 1) != 'B'){
                TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] + 1, 'P');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] + 1,colVec[0]);
                TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                tmpPlrPos = {tmpPlrPos[0], tmpPlrPos[1] + 1};
            }
            else if ((TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 1) == 'B')
                     && (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 2) != '#')
                     && (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 2) != 'B')){
                TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] + 1, 'P');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] + 1,colVec[0]);
                TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] + 2, 'B');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] + 2,colVec[2]);
                tmpPlrPos = {tmpPlrPos[0], tmpPlrPos[1] + 1};
            }
        }
        TCODConsole::root->flush();
    }
    else if ( key.c == 'd' || key.c == 'D' ) {
        if (TCODConsole::root -> getChar(tmpPlrPos[0] + 1, tmpPlrPos[1]) != '#'){
            if (TCODConsole::root -> getChar(tmpPlrPos[0] + 1, tmpPlrPos[1]) != 'B'){
                TCODConsole::root -> setChar(tmpPlrPos[0] + 1, tmpPlrPos[1], 'P');
                TCODConsole::root->setCharBackground(tmpPlrPos[0] + 1, tmpPlrPos[1],colVec[0]);
                TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                tmpPlrPos = {tmpPlrPos[0] + 1, tmpPlrPos[1]};
            }

            else if ((TCODConsole::root -> getChar(tmpPlrPos[0] + 1, tmpPlrPos[1]) == 'B')
                     && (TCODConsole::root -> getChar(tmpPlrPos[0] + 2, tmpPlrPos[1]) != '#')
                     && (TCODConsole::root -> getChar(tmpPlrPos[0] + 2, tmpPlrPos[1]) != 'B')){
                TCODConsole::root -> setChar(tmpPlrPos[0] + 1, tmpPlrPos[1], 'P');
                TCODConsole::root->setCharBackground(tmpPlrPos[0] + 1, tmpPlrPos[1],colVec[0]);
                TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                TCODConsole::root -> setChar(tmpPlrPos[0] + 2, tmpPlrPos[1], 'B');
                TCODConsole::root->setCharBackground(tmpPlrPos[0] + 2, tmpPlrPos[1],colVec[2]);

                tmpPlrPos = {tmpPlrPos[0] + 1, tmpPlrPos[1]};
            }
        }
        TCODConsole::root->flush();
    }
}

bool ifWin(map<vector<int>,char>& mapOfWinPositions){
    decltype(mapOfWinPositions.size()) winCnt = 0;
    for (auto cross : mapOfWinPositions){
        if (cross.second == 'B'){
            winCnt++;
        }
    }
    if (winCnt == mapOfWinPositions.size()) {
        return true;
    }
    else{
        return false;
    }
}

void firstPaintOfScreen(TwoDimArray<char>& TwoDArray, const vector<TCODColor>& colVec, vector<int>& tmpPlrPos, map<vector<int>,char>& mapOfWinPositions){
    TCODConsole::initRoot(TwoDArray.getDimX(),TwoDArray.getDimY(),"AlexSmith's Sokoban", false, TCOD_RENDERER_GLSL);
    TCODConsole::root->setDefaultBackground({0,0,0});

    for (auto i = 0; i < TwoDArray.getDimY(); i++){
        for (auto j = 0; j < TwoDArray.getDimX(); j++){
            TCODConsole::root -> setChar(j, i, TwoDArray.getObjPos(i,j));
        }
    }

    for (auto i = 0; i < TwoDArray.getDimY(); i++){
        for (auto j = 0; j < TwoDArray.getDimX(); j++){

            if (TCODConsole::root -> getChar(j, i) == 'P'){
                TCODConsole::root->setCharBackground(j,i,colVec[0]);
                tmpPlrPos = {j,i};
            }
            else if (TCODConsole::root -> getChar(j, i) == '#'){
                TCODConsole::root->setCharBackground(j,i,colVec[1]);
            }
            else if (TCODConsole::root -> getChar(j, i) == 'B'){
                TCODConsole::root->setCharBackground(j,i,colVec[2]);

            }
            else if (TCODConsole::root -> getChar(j, i) == 'X'){
                TCODConsole::root->setCharBackground(j,i,colVec[3]);
                mapOfWinPositions[{j,i}] = 'X';
            }
        }
    }
    TCODConsole::root->flush();
}
