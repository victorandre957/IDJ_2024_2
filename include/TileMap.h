//
// Created by victor_moraes on 17/11/24.
//

#ifndef GAME_TILEMAP_H
#define GAME_TILEMAP_H

#pragma once

#include <Component.h>
#include <GameObject.h>
#include <TileSet.h>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>

class TileMap : public Component {
private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;

    int mapWidth;
    int mapHeight;
    int mapDepth;

public:
    TileMap(GameObject& associated, const std::string& file, std::unique_ptr<TileSet> tileSet);

    void Load(const std::string& file);
    void SetTileSet(std::unique_ptr<TileSet> newTileSet);
    int& At(int x, int y, int z = 0);
    void RenderLayer(int layer);
    void Render() override;
    void Update(float dt) override;
    [[nodiscard]] bool Is(const std::string& type) const override;

    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] int GetDepth() const;
};

#endif // GAME_TILEMAP_H

