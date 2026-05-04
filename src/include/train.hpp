#pragma once
#include <string>
#include <vector>
#include "car.hpp"
#include "track.hpp"

class Train {
public:
    Train(const std::string& name, std::vector<std::string> stops, std::vector<car> cars, TrackSet trackSet)
        : name(name), stops(stops), cars(cars), trackSet(trackSet) {}


    // getters
    std::string getName() const { return name; }
    std::vector<std::string> getStops() const { return stops; }
    const TrackSet& getTrackSet() const { return trackSet; }
    
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

    // setters

    void setName(const std::string& newName) { name = newName; }
    void setStops(const std::vector<std::string>& newStops) { stops = newStops; }
    void setCars(const std::vector<car>& newCars) { cars = newCars; }
    void setTrackSet(const TrackSet& newTrackSet) { trackSet = newTrackSet; }
    void addCar(const car& newCar) { cars.push_back(newCar); }
    void rmCar(const std::string& make, const std::string& model) {
        cars.erase(std::remove_if(cars.begin(), cars.end(),
            [&](const car& c) { return c.getMake() == make && c.getModel() == model; }),
            cars.end());
    }
    void addStop(const std::string& newStop) { stops.push_back(newStop); }
    void rmStop(const std::string& stop) {
        stops.erase(std::remove(stops.begin(), stops.end(), stop), stops.end());
    }
    void clearStops() { stops.clear(); }
    void setStop(size_t index, const std::string& newStop) {
        if (index < stops.size()) {
            stops[index] = newStop;
        }
    }
    void setCar(size_t index, const car& newCar) {
        if (index < cars.size()) {
            cars[index] = newCar;
        }
    }
    void setCarMake(size_t index, const std::string& newMake) {
        if (index < cars.size()) {
            cars[index].setMake(newMake);
        }
    }
    void setCarModel(size_t index, const std::string& newModel) {
        if (index < cars.size()) {
            cars[index].setModel(newModel);
        }
    }
    void setCarYear(size_t index, int newYear) {
        if (index < cars.size()) {
            cars[index].setYear(newYear);
        }
    }
    void setCarOrientations(size_t index, const std::vector<std::string>& newOrientations) {
        if (index < cars.size()) {
            cars[index].setOrientations(newOrientations);
        }
    }
    void setCarPositions(size_t index, const std::vector<float>& newPositions) {
        if (index < cars.size()) {
            cars[index].setPositions(newPositions);
        }
    }
    void setCarTextures(size_t index, const std::vector<SDL_Texture*>& newTextures) {
        if (index < cars.size()) {  
            cars[index].setTextures(newTextures);
        }
    }
    void setCarTextureRects(size_t index, const std::vector<SDL_Rect>& newTextureRects) {
        if (index < cars.size()) {
            cars[index].setTextureRects(newTextureRects);
        }
    }
    void setCarCollisionRects(size_t index, const std::vector<SDL_Rect>& newCollisionRects) {
        if (index < cars.size()) {
            cars[index].setCollisionRects(newCollisionRects);
        }
    }   

private:
    std::string name;
    std::vector<std::string> stops;
    std::vector<car> cars;
    TrackSet trackSet;
};