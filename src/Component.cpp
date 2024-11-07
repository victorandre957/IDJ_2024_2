//
// Created by victor_moraes on 03/11/24.
//

#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject& associated) : associated(associated) {}

Component::~Component() = default;
