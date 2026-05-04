#pragma once
#include <string>
#include <vector>

class car {
public:
    car(const std::string& make, const std::string& model, int year)
        : make(make), model(model), year(year) {}

    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }

    // orientation stuff
    std::vector<std::string> getOrientations() const;
    std::vector<float> getPositions();

    // image stuff
    std::vector<SDL_Texture*> getTextures() const;
    std::vector<SDL_Rect> getTextureRects() const;
    std::vector<SDL_Rect> getCollisionRects() const;

private:
    std::string make;
    std::string model;
    int year;

    // orientation data
    std::vector<std::string> orientations;
    std::vector<float> positions;
    
    // image data
    std::vector<SDL_Texture*> textures;
    std::vector<SDL_Rect> textureRects;
    std::vector<SDL_Rect> collisionRects;

};