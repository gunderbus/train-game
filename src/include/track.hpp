#pragma once
#include <vector>
#include <memory>
#include "stop.hpp"

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