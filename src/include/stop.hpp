#pragma once
#include <string>
#include <vector>

class Stop {
public:
    Stop(const std::string& name, float x, float y)
        : name(name), x(x), y(y) {}

    std::string getName() const { return name; }
    float getX() const { return x; }
    float getY() const { return y; }

    void setName(const std::string& newName) { name = newName; }
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }

private:
    std::string name;
    float x, y;
};