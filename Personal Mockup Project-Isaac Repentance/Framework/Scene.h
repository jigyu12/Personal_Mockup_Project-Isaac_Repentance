#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene() = default;

	virtual void Init();

	virtual void Update(float deltaTime);

	virtual void Draw(sf::RenderWindow& window);

	virtual void Release();



protected:

};