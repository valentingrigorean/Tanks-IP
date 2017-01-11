#pragma once

#include <anax/System.hpp>
#include "../Input.h"
#include "../components/TankComponent.h"

struct InputComponent;
struct BodyComponent;

class InputSystem :public anax::System<anax::Requires<InputComponent, BodyComponent>>
{
public:
	InputSystem();
	void Update();
	Input* GetInput() const;
	void SetInput(Input* input);	
private:	
	void SetData(anax::Entity& e, DIRECTION dir,bool idle = false);
private:
	Input* _input;
};