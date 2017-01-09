#pragma once

#include <anax/System.hpp>
#include "../Input.h"

struct InputComponent;
struct VelocityComponent;

class InputSystem :public anax::System<anax::Requires<InputComponent, VelocityComponent>>
{
public:
	InputSystem();
	void Update();
	Input* GetInput() const;
	void SetInput(Input* input);
private:
	Input* _input;
};