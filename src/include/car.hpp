#pragma once
#include <string>
#include <vector>
#include <memory>
#include "track.hpp"

class car {
public:
    car(const std::string& make, const std::string& model, int year)
        : make(make), model(model), year(year) {}

    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }

    // getters for orientation and image data
    std::vector<std::string> getOrientations() const { return orientations; }
    std::vector<float> getPositions() const { return positions; }
    std::vector<SDL_Texture*> getTextures() const { return textures; }
    std::vector<SDL_Rect> getTextureRects() const { return textureRects; }
    std::vector<SDL_Rect> getCollisionRects() const { return collisionRects; }

    // setters for orientation and image data
    void setOrientations(const std::vector<std::string>& newOrientations) { orientations = newOrientations; }
    void setPositions(const std::vector<float>& newPositions) { positions = newPositions; }
    void setTextures(const std::vector<SDL_Texture*>& newTextures) { textures = newTextures; }
    void setTextureRects(const std::vector<SDL_Rect>& newTextureRects) { textureRects = newTextureRects; }
    void setCollisionRects(const std::vector<SDL_Rect>& newCollisionRects) { collisionRects = newCollisionRects; }

    // setters for make, model, and year
    void setMake(const std::string& newMake) { make = newMake; }
    void setModel(const std::string& newModel) { model = newModel; }
    void setYear(int newYear) { year = newYear; }

    // getter and setter for current track
    std::shared_ptr<Track> getCurrentTrack() const { return currentTrack; }
    void setCurrentTrack(std::shared_ptr<Track> track) { currentTrack = track; }


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

    // current track
    std::shared_ptr<Track> currentTrack;

};