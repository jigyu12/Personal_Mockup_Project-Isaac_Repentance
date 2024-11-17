#include "pch.h"

void InputManager::Init()
{
	downKeys.clear();
	holdKeys.clear();
	upKeys.clear();

	downMouseButtons.clear();
	holdMouseButtons.clear();
	upMouseButtons.clear();

	axisInfoMap.clear();


	std::shared_ptr<json> loadAxisInfosPtr = FILE_MGR.LoadByJson(axisFilePath);
	if (loadAxisInfosPtr)
	{
		try
		{
			std::vector<AxisInfo> loadAxisInfos = loadAxisInfosPtr->get<std::vector<AxisInfo>>();
			for (const auto& axisInfo : loadAxisInfos)
			{
				axisInfoMap.insert({ axisInfo.axis, axisInfo });
			}
		}
		catch (const std::exception& ex)
		{
			std::wcerr << L"Invaild loadAxisInfo data: "<< ex.what() << std::endl;

			return;
		}
	}
	else
	{
		std::wcerr << L"loadAxisInfosPtr was nullptr" << std::endl;
	}
}

void InputManager::Update(float deltaTime)
{
	// GetAxis에 사용할 value를 계산
	for (auto& pair : axisInfoMap)
	{
		auto& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis);
		float dir = raw;
		if (dir == 0.f && axisInfo.value != 0.f)
		{
			dir = axisInfo.value > 0.f ? -1.f : 1.f;
		}

		axisInfo.value += dir * axisInfo.sensitivity * deltaTime;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

		float stopThreshold = std::abs(dir * axisInfo.sensitivity * deltaTime);
		if (raw == 0.f && std::abs(axisInfo.value) < stopThreshold)
		{
			axisInfo.value = 0.f;
		}
	}
}

void InputManager::UpdateEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
	{
		if (std::find(holdKeys.begin(), holdKeys.end(), ev.key.code) == holdKeys.end())
		{
			downKeys.push_back(ev.key.code);
			holdKeys.push_back(ev.key.code);
		}
	}
		break;
	case sf::Event::KeyReleased:
	{
		holdKeys.remove(ev.key.code);
		upKeys.push_back(ev.key.code);
	}
		break;
	case sf::Event::MouseButtonPressed:
	{
		if (std::find(holdMouseButtons.begin(), holdMouseButtons.end(), ev.mouseButton.button) == holdMouseButtons.end())
		{
			downMouseButtons.push_back(ev.mouseButton.button);
			holdMouseButtons.push_back(ev.mouseButton.button);
		}
	}
		break;
	case sf::Event::MouseButtonReleased:
	{
		holdMouseButtons.remove(ev.mouseButton.button);
		upMouseButtons.push_back(ev.mouseButton.button);
	}
		break;
	}
}

bool InputManager::GetKeyDown(const sf::Keyboard::Key key)
{
	return std::find(downKeys.begin(), downKeys.end(), key) != downKeys.end();
}

bool InputManager::GetKeyHold(const sf::Keyboard::Key key)
{
	return std::find(holdKeys.begin(), holdKeys.end(), key) != holdKeys.end();
}

bool InputManager::GetKeyUp(const sf::Keyboard::Key key)
{
	return std::find(upKeys.begin(), upKeys.end(), key) != upKeys.end();
}

bool InputManager::GetMouseDown(const sf::Mouse::Button mouseButton)
{
	return std::find(downMouseButtons.begin(), downMouseButtons.end(), mouseButton) != downMouseButtons.end();
}

bool InputManager::GetMouseHold(const sf::Mouse::Button mouseButton)
{
	return std::find(holdMouseButtons.begin(), holdMouseButtons.end(), mouseButton) != holdMouseButtons.end();;
}

bool InputManager::GetMouseUp(const sf::Mouse::Button mouseButton)
{
	return std::find(upMouseButtons.begin(), upMouseButtons.end(), mouseButton) != upMouseButtons.end();
}

sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window) const
{
	return mouse.getPosition(window);
}

float InputManager::GetAxisRaw(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end())
		return 0.f;

	auto& axisInfo = findIt->second;
	auto it = holdKeys.rbegin();
	while (it != holdKeys.rend())
	{
		sf::Keyboard::Key key = *it;
		auto keyIt = axisInfo.keyMap.find(key);
		if (keyIt != axisInfo.keyMap.end())
		{
			if(keyIt->second)
				return 1.f;
			else
				return -1.f;
		}
		
		++it;
	}

	return 0.0f;
}

float InputManager::GetAxis(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end())
		return 0.f;

	return findIt->second.value;
}

void InputManager::Clear()
{
	downKeys.clear();
	upKeys.clear();
	
	downMouseButtons.clear();
	upMouseButtons.clear();
}


// Example of Save Isaac AxisInfo by FileManager(Json)

//AxisInfo infoHoriaontalMove;
//infoHoriaontalMove.axis = Axis::HorizontalMove;
//infoHoriaontalMove.AddKey(sf::Keyboard::D, true);
//infoHoriaontalMove.AddKey(sf::Keyboard::A, false);
//
//AxisInfo infoVerticalMove;
//infoVerticalMove.axis = Axis::VerticalMove;
//infoVerticalMove.AddKey(sf::Keyboard::W, true);
//infoVerticalMove.AddKey(sf::Keyboard::S, false);
//
//AxisInfo infoHoriaontalAttack;
//infoHoriaontalAttack.axis = Axis::HorizontalAttack;
//infoHoriaontalAttack.AddKey(sf::Keyboard::Right, true);
//infoHoriaontalAttack.AddKey(sf::Keyboard::Left, false);
//
//AxisInfo infoVerticalAttack;
//infoVerticalAttack.axis = Axis::VerticalAttack;
//infoVerticalAttack.AddKey(sf::Keyboard::Up, true);
//infoVerticalAttack.AddKey(sf::Keyboard::Down, false);
//
//json jArray = { infoHoriaontalMove, infoVerticalMove, infoHoriaontalAttack, infoVerticalAttack };
//FILE_MGR.SaveByJson(jArray, axisFilePath);