//
// Created by victor_moraes on 22/10/24.
//

#include "Game.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {
        throw std::runtime_error("A instância de Game já existe!");
    }

    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        throw std::runtime_error(std::string("Erro ao inicializar SDL: ") + SDL_GetError());
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        throw std::runtime_error(std::string("Erro ao inicializar SDL_Image: ") + IMG_GetError());
    }

    if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == 0) {
        throw std::runtime_error(std::string("Erro ao inicializar SDL_Mixer: ") + Mix_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        throw std::runtime_error(std::string("Erro ao abrir o áudio: ") + Mix_GetError());
    }

    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        throw std::runtime_error(std::string("Erro ao criar a janela: ") + SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        throw std::runtime_error(std::string("Erro ao criar o renderizador: ") + SDL_GetError());
    }

    state = new State();
}

Game::~Game() {
    delete state;

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}

void Game::Run() {
    state->LoadAssets();

    while (!state->QuitRequested()) {
        state->Update(1);

        SDL_RenderClear(renderer);

        state->Render();

        SDL_RenderPresent(renderer);
        SDL_Delay(17);
    }
}

Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game(
                GAME_TITLE,
                WINDOW_WIDTH, WINDOW_HEIGHT
        );
    }
    return *instance;}