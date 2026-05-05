#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "include/train.hpp"
#include "include/car.hpp"
#include "include/stop.hpp"
#include "include/track.hpp"

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