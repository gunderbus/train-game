#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Track;  // Forward declaration

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

class Train {
public:
    Train(const std::string& name, std::vector<std::string> stops, std::vector<car> cars, TrackSet trackSet)
        : name(name), stops(stops), cars(cars), trackSet(trackSet) {}


    // getters
    std::string getName() const { return name; }
    std::vector<std::string> getStops() const { return stops; }
    const TrackSet& getTrackSet() const { return trackSet; }
    const std::vector<car>& getCars() const { return cars; }
    
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

class Track : public std::enable_shared_from_this<Track> {
public:
    Track(std::shared_ptr<Stop> start, std::shared_ptr<Stop> end)
        : start(start), end(end) {}

    std::shared_ptr<Stop> getStart() const { return start; }
    std::shared_ptr<Stop> getEnd() const { return end; }

    const std::vector<std::shared_ptr<Track>>& getConnectedTracks() const { return connectedTracks; }

    void addConnection(std::shared_ptr<Track> track) {
        if (track != nullptr && track != shared_from_this()) {
            connectedTracks.push_back(track);
        }
    }

private:
    std::shared_ptr<Stop> start;
    std::shared_ptr<Stop> end;
    std::vector<std::shared_ptr<Track>> connectedTracks;
};

class TrackSet {
public:
    void addTrack(std::shared_ptr<Track> track) {
        tracks.push_back(track);
    }

    void connectTracks() {
        for (size_t i = 0; i < tracks.size(); ++i) {
            for (size_t j = i + 1; j < tracks.size(); ++j) {
                // Connect if they share a stop
                auto track1 = tracks[i];
                auto track2 = tracks[j];
                if (sharesStop(track1, track2)) {
                    track1->addConnection(track2);
                    track2->addConnection(track1);
                }
            }
        }
    }

    const std::vector<std::shared_ptr<Track>>& getTracks() const { return tracks; }

private:
    std::vector<std::shared_ptr<Track>> tracks;

    bool sharesStop(std::shared_ptr<Track> t1, std::shared_ptr<Track> t2) {
        return (t1->getStart() == t2->getStart() || t1->getStart() == t2->getEnd() ||
                t1->getEnd() == t2->getStart() || t1->getEnd() == t2->getEnd());
    }
};

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Train Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set render draw color (white background)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Example usage of classes
    auto stop1 = std::make_shared<Stop>("Station A", 100.0f, 200.0f);
    auto stop2 = std::make_shared<Stop>("Station B", 300.0f, 400.0f);
    auto track = std::make_shared<Track>(stop1, stop2);

    TrackSet trackSet;
    trackSet.addTrack(track);
    trackSet.connectTracks();  // Connect tracks that share stops

    std::vector<car> cars;
    cars.emplace_back("Toyota", "Model X", 2020);
    cars[0].setCurrentTrack(track);

    Train train("Express Train", {"Station A", "Station B"}, cars, trackSet);

    // Simple text rendering simulation (since SDL_ttf not included, just print to console)
    std::cout << "Train Name: " << train.getName() << std::endl;
    std::cout << "Stops: ";
    for (const auto& stop : train.getStops()) {
        std::cout << stop << " ";
    }
    std::cout << std::endl;
    std::cout << "Number of Cars: " << train.getCars().size() << std::endl;
    std::cout << "Number of Tracks: " << train.getTrackSet().getTracks().size() << std::endl;

    // Main loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render something simple, e.g., a rectangle representing the train
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Blue
        SDL_Rect trainRect = {100, 250, 200, 100};  // x, y, w, h
        SDL_RenderFillRect(renderer, &trainRect);

        // Update screen
        SDL_RenderPresent(renderer);

        // Cap frame rate
        SDL_Delay(16);  // ~60 FPS
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}