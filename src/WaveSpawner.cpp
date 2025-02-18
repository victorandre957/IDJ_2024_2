#include <WaveSpawner.h>

WaveSpawner::WaveSpawner(GameObject& associated) :
  Component(associated),
  zombieCounter(0),
  waves(),
  zombieCooldownTimer(),
  currentWave(0) {
  Wave firstWave(5, 2000);
  waves.push_back(firstWave);

  Wave secondWave(10, 1000);
  waves.push_back(secondWave);

  Wave finalWave(20, 500);
  waves.push_back(finalWave);
}

WaveSpawner::WaveSpawner(GameObject& associated, std::vector<Wave> waves) :
  Component(associated),
  zombieCounter(0),
  waves(waves),
  zombieCooldownTimer(),
  currentWave(0) {}

WaveSpawner::~WaveSpawner() {}

void WaveSpawner::Start() {}

void WaveSpawner::Update(float dt) {
  zombieCooldownTimer.Update(dt);

  if (
    zombieCounter < waves[currentWave].zombies &&
    zombieCooldownTimer.Get() > waves[currentWave].cooldown
  ) {
    GameObject* zombieGO = new GameObject();
    Zombie* zombie = new Zombie(*zombieGO);
    zombieGO->AddComponent(std::make_shared<Zombie>(*zombieGO));


    Vec2 cameraCenter = Rect(
      Camera::pos.x,
      Camera::pos.y,
      1200,
      900
    ).Center();

    int angleDegRand = rand() % 360;
    float angleRand = angleDegRand * M_PI / 180;

    // minimum distance from camera center
    float Rm = (Camera::pos).Distance(cameraCenter);

    // radius of zombie box
    float Rz = zombieGO->box.GetDiagonal() / 2;

    Vec2 spawnPoint = cameraCenter + Vec2(1, 0).Rotate(angleRand) * (Rm + Rz + (rand() % 100));
    zombieGO->box.Center(spawnPoint);
    State::GetInstance().AddObject(zombieGO);

    zombieCounter++;
    zombieCooldownTimer.Restart();
  }

  if (zombieCounter >= waves[currentWave].zombies && Zombie::zombieCount == 0) {
    currentWave++;
    if (currentWave == waves.size()) {
      associated.RequestDelete();
      currentWave = 0;
    }
    zombieCounter = 0;
    zombieCooldownTimer.Restart();
  }
}

void WaveSpawner::Render() {}

bool WaveSpawner::Is(const std::string& type) const {
    return type == "WaveSpawner";
}