#include "map.h"
#include "map_loader.h"

Map::Map(int w, int h, int t) : width(w), height(h), tileSize(t) {
    tiles.resize(height);
    for (int i = 0; i < height; i++) {
        tiles[i].resize(width, TILE_BUILDABLE);
    }
}

Map::Map(const std::string& mapFile, int t) : tileSize(t) {
    if (!MapLoader::loadTiledMap(mapFile, this)) {
        // Fallback to default map if loading fails
        width = 18;
        height = 18;
        tiles.resize(height);
        for (int i = 0; i < height; i++) {
            tiles[i].resize(width, TILE_BUILDABLE);
        }
    }
}

void Map::renderMap(SDL_Renderer* renderer) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            SDL_FRect tileRect = { 
                (float)x * tileSize, 
                (float)y * tileSize, 
                (float)tileSize, 
                (float)tileSize 
            };
             if (tiles[y][x] == TILE_PATH) {
                SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Nâu cho đường path
            } else if (tiles[y][x] == TILE_BUILDABLE) {
                SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Xanh lá cho vùng có thể xây
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Đỏ cho vùng bị chặn
            }
            
            SDL_RenderFillRect(renderer, &tileRect);
            
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Xám cho viền
            SDL_RenderRect(renderer, &tileRect);
        }
    }
}

bool Map::isBuildable(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return tiles[y][x] == TILE_BUILDABLE;
}