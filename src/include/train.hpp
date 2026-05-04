#pragma once
#include <string>
#include <vector>
#include "car.hpp"

class Train {
public:
    Train(const std::string& name, std::vector<std::string> stops, std::vector<car> cars)
        : name(name), stops(stops), cars(cars) {}

    std::string getName() const { return name; }
    std::vector<std::string> getStops() const { return stops; }
    
    std::vector<std::string> getOrientations() const {
        std::vector<std::string> allOrientations;
        for (const auto& c : cars) {
            auto orientations = c.getOrientations();
            allOrientations.insert(allOrientations.end(), orientations.begin(), orientations.end());
        }
        return allOrientations;
    }
    
    std::vector<float> getPositions() const {
        std::vector<float> allPositions;
        for (const auto& c : cars) {
            auto positions = c.getPositions();
            allPositions.insert(allPositions.end(), positions.begin(), positions.end());
        }
        return allPositions;    
    }   
    
    std::vector<SDL_Texture*> getTextures() const {
        std::vector<SDL_Texture*> allTextures;
        for (const auto& c : cars) {
            auto textures = c.getTextures();
            allTextures.insert(allTextures.end(), textures.begin(), textures.end());
        }
        return allTextures;
    }
    
    std::vector<SDL_Rect> getTextureRects() const {
        std::vector<SDL_Rect> allTextureRects;
        for (const auto& c : cars) {
            auto textureRects = c.getTextureRects();
            allTextureRects.insert(allTextureRects.end(), textureRects.begin(), textureRects.end());
        }
        return allTextureRects;
    }
    
    std::vector<SDL_Rect> getCollisionRects() const {
        std::vector<SDL_Rect> allCollisionRects;
        for (const auto& c : cars) {
            auto collisionRects = c.getCollisionRects();
            allCollisionRects.insert(allCollisionRects.end(), collisionRects.begin(), collisionRects.end());
        }
        return allCollisionRects;
    }

private:
    std::string name;
    std::vector<std::string> stops;
    std::vector<car> cars;
};