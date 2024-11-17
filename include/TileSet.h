//
// Created by victor_moraes on 17/11/24.
//

#ifndef GAME_TILESET_H
#define GAME_TILESET_H

#pragma once

#include <Sprite.h>
#include <iostream>

class TileSet {
private:
    Sprite tileSet;

    int tileWidth;
    int tileHeight;
public:
    TileSet(int tileWidth, int tileHeight, const std::string& file);
    [[nodiscard]] int GetTileWidth() const;
    [[nodiscard]] int GetTileHeight() const;
    void RenderTile(unsigned index, float x, float y);

};

#endif // GAME_TILESET_H
