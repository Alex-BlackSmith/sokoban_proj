#include <libtcod.hpp>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

template <typename T>
class TwoDimArray {
public:
    TwoDimArray() = default;
    TwoDimArray(T argValue, unsigned argLen, unsigned argWth) : length(argLen), width(argWth)
    {
        value = new T *[length];
        for (auto row : value)
        {
            row = new T[argWth];
        }
    }

    void setArray(const unsigned len, const unsigned wth, char *Array) {
        length = len;
        width = wth;

    }
    TwoDimArray getArray () {
        return this;
    };
private:
    unsigned length;
    unsigned width;
    T **value;
};

int main() {
    TCODConsole::initRoot(80,60,"AlexSmith's Sokoban", false, TCOD_RENDERER_GLSL);




    return 0;
}

