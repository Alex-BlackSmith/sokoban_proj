#include <libtcod.hpp>
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



//implementation of the template class of 2DArray
template <typename T> class TwoDimArray {
public:
    TwoDimArray() = default;

    TwoDimArray(const unsigned argLen,const unsigned argWth) : length(argLen), width(argWth)
    {
        value = new T *[length];
        for (auto i = 0; i < length; i++){
            value[i] = new T[width] {};
        }
    }

    ~TwoDimArray() {}


    void setObjPos(const unsigned posX, const unsigned posY, T obj) {
        value[posX][posY] = obj;
    }
    char getObjPos (const unsigned posX, const unsigned posY) const{
        return value[posX][posY];
    }

    unsigned  getDimX() const {
        return width;
    }

    unsigned  getDimY() const {
        return length;
    }

    friend ostream& operator<< (ostream& stream, TwoDimArray<char>& TwoDArray);
    friend ifstream& operator>> (ifstream &file, TwoDimArray<char>& TwoDArray);

private:
    unsigned length;
    unsigned width;
    T **value;
};

//overload >> operator

ostream& operator<<(ostream& stream, TwoDimArray<char>& TwoDArray) {
    for (auto i = 0; i < TwoDArray.length; i++){
        for (auto j = 0; j < TwoDArray.width; j++){
            stream << TwoDArray.getObjPos(i,j);
        }
        cout << endl;
    }
    return stream;
}

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



int main() {
    ifstream in("TestMap.txt");

    TwoDimArray<char> Test;
    in >> Test;
    vector<int> tmpPlrPos;
    vector<int> WinPos;
    std::map<vector<int>,char> mapCharWin;


    TCODConsole::initRoot(Test.getDimX(),Test.getDimY(),"AlexSmith's Sokoban", false, TCOD_RENDERER_GLSL);
    TCODConsole::root->setDefaultBackground({0,0,0});

    for (auto i = 0; i < Test.getDimY(); i++){
        for (auto j = 0; j < Test.getDimX(); j++){
            TCODConsole::root -> setChar(j, i, Test.getObjPos(i,j));
        }
    }

    for (auto i = 0; i < Test.getDimY(); i++){
        for (auto j = 0; j < Test.getDimX(); j++){

           if (TCODConsole::root -> getChar(j, i) == 'P'){
               TCODConsole::root->setCharBackground(j,i,{0,255,0});
               tmpPlrPos = {j,i};
           }
           else if (TCODConsole::root -> getChar(j, i) == '#'){
               TCODConsole::root->setCharBackground(j,i,{255,0,0});
           }
           else if (TCODConsole::root -> getChar(j, i) == 'B'){
                TCODConsole::root->setCharBackground(j,i,{250,250,0});

           }
           else if (TCODConsole::root -> getChar(j, i) == 'X'){
               TCODConsole::root->setCharBackground(j,i,{255,255,255});
               mapCharWin[{j,i}] = 'X';
           }
        }
    }
    TCODConsole::root->flush();
        while (4) {
            for (auto& cross : mapCharWin){
                if (TCODConsole::root -> getChar(cross.first[0],cross.first[1]) == 'X') {
                    TCODConsole::root->setCharBackground(cross.first[0],cross.first[1],{255,255,255});
                    cross.second = 'X';
                }
                else if(TCODConsole::root -> getChar(cross.first[0],cross.first[1]) ==  'B') {
                    TCODConsole::root->setCharBackground(cross.first[0],cross.first[1],{255,255,0});
                    cross.second = 'B';
                }
                else if(TCODConsole::root -> getChar(cross.first[0],cross.first[1]) ==  'P') {
                    TCODConsole::root->setCharBackground(cross.first[0],cross.first[1],{0,255,0});
                    cross.second = 'P';
                }
                else if(TCODConsole::root -> getChar(cross.first[0],cross.first[1]) ==  ' ') {
                    TCODConsole::root -> setChar(cross.first[0],cross.first[1], 'X');
                    TCODConsole::root->setCharBackground(cross.first[0],cross.first[1],{255,255,255});
                }
            }

            TCOD_key_t key = TCODConsole::checkForKeypress();

            TCODConsole::root->flush();
            if ( key.c == 'w' || key.c == 'W' ) {
                if (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 1) != '#'){
                    if (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 1) != 'B'){
                        TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] - 1, 'P');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] - 1,{0,255,0});
                        TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                        tmpPlrPos = {tmpPlrPos[0], tmpPlrPos[1] - 1};
                    }
                    else if ((TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 1) == 'B')
                    && (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 2) != '#')
                    && (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] - 2) != 'B')){
                        TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] - 1, 'P');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] - 1,{0,255,0});
                        TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});

                        TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] - 2, 'B');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] - 2,{255,255,0});

                        tmpPlrPos = {tmpPlrPos[0], tmpPlrPos[1] - 1};
                    }
                }
                TCODConsole::root->flush();
            }
            else if ( key.c == 'a' || key.c == 'A' ) {
                if (TCODConsole::root -> getChar(tmpPlrPos[0] - 1, tmpPlrPos[1]) != '#'){
                    if (TCODConsole::root -> getChar(tmpPlrPos[0] - 1, tmpPlrPos[1]) != 'B'){
                        TCODConsole::root -> setChar(tmpPlrPos[0] - 1, tmpPlrPos[1], 'P');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0] - 1, tmpPlrPos[1],{0,255,0});
                        TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                        tmpPlrPos = {tmpPlrPos[0] - 1, tmpPlrPos[1]};
                }

                else if ((TCODConsole::root -> getChar(tmpPlrPos[0] - 1, tmpPlrPos[1]) == 'B')
                && (TCODConsole::root -> getChar(tmpPlrPos[0] - 2, tmpPlrPos[1]) != '#')
                && (TCODConsole::root -> getChar(tmpPlrPos[0] - 2, tmpPlrPos[1]) != 'B')){
                        TCODConsole::root -> setChar(tmpPlrPos[0] - 1, tmpPlrPos[1], 'P');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0] - 1, tmpPlrPos[1],{0,255,0});
                        TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});

                        TCODConsole::root -> setChar(tmpPlrPos[0] - 2, tmpPlrPos[1], 'B');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0] - 2, tmpPlrPos[1],{255,255,0});

                        tmpPlrPos = {tmpPlrPos[0] - 1, tmpPlrPos[1]};
                    }
                }
                TCODConsole::root->flush();
            }
            else if ( key.c == 's' || key.c == 'S' ) {
                if (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 1) != '#'){
                    if (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 1) != 'B'){
                        TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] + 1, 'P');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] + 1,{0,255,0});
                        TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                        tmpPlrPos = {tmpPlrPos[0], tmpPlrPos[1] + 1};
                    }
                    else if ((TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 1) == 'B')
                    && (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 2) != '#')
                    && (TCODConsole::root -> getChar(tmpPlrPos[0], tmpPlrPos[1] + 2) != 'B')){
                        TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] + 1, 'P');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] + 1,{0,255,0});
                        TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});

                        TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1] + 2, 'B');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1] + 2,{255,255,0});

                        tmpPlrPos = {tmpPlrPos[0], tmpPlrPos[1] + 1};
                    }
                }
                TCODConsole::root->flush();
            }
            else if ( key.c == 'd' || key.c == 'D' ) {
                if (TCODConsole::root -> getChar(tmpPlrPos[0] + 1, tmpPlrPos[1]) != '#'){
                    if (TCODConsole::root -> getChar(tmpPlrPos[0] + 1, tmpPlrPos[1]) != 'B'){
                        TCODConsole::root -> setChar(tmpPlrPos[0] + 1, tmpPlrPos[1], 'P');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0] + 1, tmpPlrPos[1],{0,255,0});
                        TCODConsole::root -> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});
                        tmpPlrPos = {tmpPlrPos[0] + 1, tmpPlrPos[1]};
                    }

                    else if ((TCODConsole::root -> getChar(tmpPlrPos[0] + 1, tmpPlrPos[1]) == 'B')
                    && (TCODConsole::root -> getChar(tmpPlrPos[0] + 2, tmpPlrPos[1]) != '#')
                    && (TCODConsole::root -> getChar(tmpPlrPos[0] + 2, tmpPlrPos[1]) != 'B')){
                        TCODConsole::root -> setChar(tmpPlrPos[0] + 1, tmpPlrPos[1], 'P');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0] + 1, tmpPlrPos[1],{0,255,0});
                        TCODConsole::root-> setChar(tmpPlrPos[0], tmpPlrPos[1], ' ');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0], tmpPlrPos[1],{0,0,0});

                        TCODConsole::root -> setChar(tmpPlrPos[0] + 2, tmpPlrPos[1], 'B');
                        TCODConsole::root->setCharBackground(tmpPlrPos[0] + 2, tmpPlrPos[1],{255,255,0});

                        tmpPlrPos = {tmpPlrPos[0] + 1, tmpPlrPos[1]};
                    }
                }
                TCODConsole::root->flush();
            }
            decltype(mapCharWin.size()) winCnt = 0;
            for (auto cross : mapCharWin){
                if (cross.second == 'B'){
                    winCnt++;
                }
            }
            if (winCnt == mapCharWin.size()) {
                break;
            }

        }

    return 0;
}

