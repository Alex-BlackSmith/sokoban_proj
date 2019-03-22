#include <libtcod.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ostream;
using std::fstream;
using std::getline;

ifstream in("TestMap.txt");

//implementation of the template class of 2DArray
template <typename T>
class TwoDimArray {
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
        /*for(auto i = 0; i < length; i++){
            delete value[i];
        }
        delete[] value;*/

    void setPos(const unsigned posx, const unsigned posy, T obj) {
        value[posx][posy] = obj;
    };
    char getPos (const unsigned posx, const unsigned posy) {
        return value[posx][posy];
    };

    friend ostream& operator<<(ostream& stream, TwoDimArray<char>& TwoDArray);
private:
    unsigned length;
    unsigned width;
    T **value;
};

//overload >> operator
    ostream& operator<<(ostream& stream, TwoDimArray<char>& TwoDArray) {
        for (auto i = 0; i < TwoDArray.length; i++){
            for (auto j = 0; j < TwoDArray.width; j++){
                stream << TwoDArray.getPos(i,j);
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
    for (auto i = 0; i < len ; i++)
        for (auto j = 0; j <= wth; j++){
                TwoDArray.setPos(i,j,file.get());
        }
    }

int main() {
    TCODConsole::initRoot(80,60,"AlexSmith's Sokoban", false, TCOD_RENDERER_GLSL);
    TwoDimArray<char> Test;
    in >> Test;
    cout << Test;
    return 0;
}

//legacy

//that function reads txt file and load dimensions of map
//and store them into len and wth
// although store strings in map into 1-dim array of chars
void readMap(const string& filename) {
    unsigned len, wth, dim, i = 0;
    char ch;
    fstream mapFile;
    mapFile.open(filename);
    if (mapFile) {
        mapFile >> len >> wth;
    }
    dim = wth*len;
    const char *strArr[dim];
    //mapFile.get(ch);
    while(i < dim){

        mapFile.get(ch);
        *(strArr + i++) = &ch;



    }

    for (auto c : strArr)
        cout << c << " ";
    return;
}