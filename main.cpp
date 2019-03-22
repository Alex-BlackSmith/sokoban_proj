#include <libtcod.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::fstream;
using std::getline;

//that function reads txt file and load dimensions of map
//and store them into len and wth
// although store strings in map into 1-dim array of chars
void readMap(const string& filename) {
    unsigned len, wth;
    fstream mapFile;
    mapFile.open(filename);
    if (mapFile) {
        mapFile >> len >> wth;
    }
    const char *strArr[wth*len];
    cout << len << " " << wth;
    return;
}

//implementation of the template class of 2DArray
template <typename T>
class TwoDimArray {
public:
    TwoDimArray() = default;
    TwoDimArray(const unsigned argLen,const unsigned argWth) : length(argLen), width(argWth)
    {
        value = new T *[length];
        for (auto row : value)
        {
            row = new T[width];
        }
    }

    void setArray(const unsigned len, const unsigned wth, char *Array) {
        length = len;
        width = wth;

    }
    TwoDimArray getArray () {
        return this;
    };
    ~TwoDimArray() {}
private:
    unsigned length;
    unsigned width;
    T **value;
};

int main() {
    //TCODConsole::initRoot(80,60,"AlexSmith's Sokoban", false, TCOD_RENDERER_GLSL);
    readMap("TestMap.txt");



    return 0;
}

