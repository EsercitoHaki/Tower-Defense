#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include <string>

enum TileType {
    TILE_PATH = 0,
    TILE_BUILDABLE = 1,
    TILE_BLOCK = 2
};

class Map {
public:
    Map(int w, int h, int t);
    Map(const std::string& mapFile, int t);

    void renderMap(SDL_Renderer* renderer);
    bool isBuildable(int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getTileSize() const { return tileSize; }

    friend class MapLoader;
private:
    std::vector<std::vector<TileType>> tiles;
    int width, height, tileSize;
};