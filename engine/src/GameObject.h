#pragma once
#include <vector>

class IComponent;

class GameObject
{
public:
	
	virtual ~GameObject();

	bool isAlive() const;

	IComponent* getComponent(int id);

	void addComponent(IComponent *comp);
	void removeComponent(IComponent *comp);

private:
	std::vector<IComponent*> _components;
};

