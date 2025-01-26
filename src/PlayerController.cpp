//
// Created by victor_moraes on 25/01/25.
//

#include "PlayerController.h"

#include "iostream"
using namespace std;
PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

void PlayerController::Start() {
    // Initialization code if necessary
}

void PlayerController::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    if (auto character = associated.GetComponent<Character>()) {
        Vec2 direction(0, 0);
        // Handle movement
        if (input.IsKeyDown(W_KEY)) {
            direction.y -= 1;
        }
        if (input.IsKeyDown(S_KEY)) {
            direction.y += 1;
        }
        if (input.IsKeyDown(A_KEY)) {
            direction.x -= 1;
        }
        if (input.IsKeyDown(D_KEY)) {
            direction.x += 1;
        }
        if (direction.Magnitude() > 0) {
            direction = direction.Normalize();
            character->Issue(Command(Command::MOVE, associated.box.Center().x + direction.x, associated.box.Center().y + direction.y));
        }

        // Continuously send mouse position to the character's gun
        Vec2 mousePos(input.GetMouseX(), input.GetMouseY());
        if (auto gunPtr = character->GetGun().lock()) {
            auto gunComp = gunPtr->GetComponent<Gun>();
            if (gunComp) {
                gunComp->SetTarget(mousePos);
            }
        }

        // Issue SHOOT command if left mouse button is pressed
        if (input.MousePress(LEFT_MOUSE_BUTTON)) {
            if (auto gunPtr = character->GetGun().lock()) {
                auto gunComp = gunPtr->GetComponent<Gun>();
                if (gunComp) {
                    gunComp->Shoot(mousePos);
                }
            }
        }
    }
}

void PlayerController::Render() {
    // Rendering code if necessary
}

bool PlayerController::Is(const std::string& type) const {
    return type == "PlayerController";
}

