//
// Created by victor_moraes on 17/11/24.
//

#include <TileMap.h>
#include <GameObject.h>

TileMap::TileMap(GameObject& associated, const std::string& file, std::unique_ptr<TileSet> tileSet)
        : Component(associated), tileSet(std::move(tileSet)) {
    Load(file);
}

void TileMap::SetTileSet(std::unique_ptr<TileSet> newTileSet) {
    tileSet = std::move(newTileSet);
}

void TileMap::Load(const std::string& file) {
    std::ifstream tileMapFile(file);
    if (!tileMapFile.is_open()) {
        std::cerr << "Error: could not open file " << file << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(tileMapFile, line);
    std::stringstream ss(line);

    char comma;
    ss >> mapWidth >> comma >> mapHeight >> comma >> mapDepth;


    int tile;
    while (std::getline(tileMapFile, line)) {
        std::stringstream tileStream(line);

        while (tileStream >> tile) {
            tileMatrix.push_back(tile);

            if (tileStream.peek() == ',') {
                tileStream.ignore();
            }
        }
    }

    tileMapFile.close();
    std::cout << "Loaded " << tileMatrix.size() << " tiles." << std::endl;
}

void TileMap::RenderLayer(int layer) {
    if (layer < 0 || layer >= mapDepth) {
        std::cout << "Error: invalid layer " << layer << std::endl;
        exit(1);
    }

    float parallaxOffsetX = 0;
    float parallaxOffsetY = 0;

    if (layer == 0) {
        parallaxOffsetX = Camera::pos.x * 0.1f;
        parallaxOffsetY = Camera::pos.y * 0.1f;
    }

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            tileSet->RenderTile(
                    At(x, y, layer),
                    x * tileSet->GetTileWidth() + associated.box.x - parallaxOffsetX,
                    y * tileSet->GetTileHeight() + associated.box.y - parallaxOffsetY
            );
        }
    }
}


void TileMap::Render() {
    for (int z = 0; z < mapDepth; z++) {
        RenderLayer(z);
    }
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix.at(
            x +
            y * mapWidth +
            z * mapWidth * mapHeight
    );
}

void TileMap::Update(float dt) {}

bool TileMap::Is(const std::string& type) const {
    return type == "TileMap";
}

int TileMap::GetWidth() const {
    return mapWidth;
}

int TileMap::GetHeight() const {
    return mapHeight;
}

int TileMap::GetDepth() const {
    return mapDepth;
}

