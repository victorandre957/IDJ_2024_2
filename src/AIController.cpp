#include <AIController.h>

AIController::AIController(GameObject& associated) :
  Component(associated),
  npcCounter(0),
  state(RESTING),
  restTimer(),
  destination(),
  cooldownRest(1000) {
}

void AIController::Start() {}

void AIController::Update(float dt) {
  if (Character::player == nullptr) {
    return;
  }
  restTimer.Update(dt);

  Component* character_comp = associated.GetComponent<Character>();
  if (character_comp == nullptr) {
    std::cout << "Error: No character component found in AIController\n";
    exit(1);
  }
  Character* character = static_cast<Character*>(character_comp);

  switch (state) {
  case RESTING:
    if (restTimer.Get() > cooldownRest) {
      state = MOVING;
      restTimer.Restart();
      destination = Rect(Camera::pos.x, Camera::pos.y, 1200, 900).Center();
    }
    break;
  case MOVING:
    if (associated.box.Center().Distance(destination) <= 350) {
      state = RESTING;
      Vec2 playerCenterPos = Rect(Camera::pos.x, Camera::pos.y, 1200, 900).Center();
        Vec2 move_dir = (destination - associated.box.Center()).Normalize();

      character->Issue(Command(Command::SHOOT, playerCenterPos.x, playerCenterPos.y));
      restTimer.Restart();
    } else {
      Vec2 move_dir = (destination - associated.box.Center()).Normalize();
      character->Issue(Command(Command::MOVE, move_dir.x, move_dir.y));
    }
    break;
  default:
    std::cout << "Error: AIController state not found (how?)\n";
    break;
  }
}

void AIController::Render() {}

bool AIController::Is(std::string type) {
  return type == "AIController";
}
