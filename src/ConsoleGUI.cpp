#include <tank/ConsoleGUI.h>
#include <tank/Utils.h>
#include <string>
#include <tank/ComponentsFactory.h>
#include <tank/TankFactory.h>
#include <tank/components/InputComponent.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;


void ShowKeysInfo()
{
	std::cout << "Input info:" << std::endl;
	std::cout << "    w - up" << std::endl;
	std::cout << "    s - down" << std::endl;
	std::cout << "    a - left" << std::endl;
	std::cout << "    d - right" << std::endl;
	std::cout << "    e - shot" << std::endl;
	std::cout << std::endl << std::endl;
}

void ShowKeysInfo1()
{
	std::cout << "Input info:" << std::endl;
	std::cout << "    arrow_up    - up" << std::endl;
	std::cout << "    arrow_down  - down" << std::endl;
	std::cout << "    arrow_left  - left" << std::endl;
	std::cout << "    arrow_right - right" << std::endl;
	std::cout << "    num_pad_0   - shot" << std::endl;
	std::cout << std::endl << std::endl;
}


ConsoleGUI::ConsoleGUI() :
	_display(SCREEN_WIDTH, SCREEN_HEIGHT, std::string("Tanks 2d"))
{
	_display.Init();
	_input.RegisterWindow(_display.GetNativeWindow());
	_game = new Game(&_display, &_input);
}

ConsoleGUI::~ConsoleGUI()
{	
	if (_levelGame != nullptr)
		delete _levelGame;
	delete _game;
}

void ConsoleGUI::Reset()
{
	_currentScreen = MENU_SCREEN::SELECT_LEVEL;
	if (_levelGame != nullptr)
		delete _levelGame;
}

void ConsoleGUI::ShowMenu()
{
	ClearScreen();
	switch (_currentScreen)
	{
	case ConsoleGUI::SELECT_LEVEL:
		ShowLevelMenu();
		break;
	case ConsoleGUI::SELECT_PLAYER:
		ShowPlayerMenu();
		break;
	case ConsoleGUI::SELECT_TANK:
		ShowTankMenu();
		break;
	case ConsoleGUI::GAME:
		_game->StartGame(_levelGame, this);
		int state;
		std::cout << "1 - new game" << std::endl;
		std::cout << "2 - quit" << std::endl;
		std::cin >> state;
		switch (state)
		{
		case 1:
			Reset();
			ShowMenu();
			break;
		}
		break;
	}
}

void ConsoleGUI::ClearScreen()
{
	system("cls");
}

void ConsoleGUI::GameEnded(GameObject * won)
{
	std::cout << "GAME OVER!" << std::endl;
}

void ConsoleGUI::ShowLevelMenu()
{
	std::cout << "Please select a level(\"level1.txt\"):" << std::endl;
	std::string path;
	std::cin >> path;
	_levelGame = LevelGame::LoadLevel(GetLevelPath(path.c_str()), SCREEN_WIDTH, SCREEN_HEIGHT);
	_currentScreen = MENU_SCREEN::SELECT_PLAYER;
	ShowMenu();
}

void ConsoleGUI::ShowPlayerMenu()
{
	std::cout << "Please select:" << std::endl;
	std::cout << "1 Players" << std::endl;
	std::cout << "2 Players" << std::endl;
	std::cin >> _players;
	_currentScreen = MENU_SCREEN::SELECT_TANK;
	ShowMenu();
}

void ConsoleGUI::ShowTankMenu()
{
	if (_players == 2)
		ShowKeysInfo1();
	else
		ShowKeysInfo();

	std::cout << "SELECT TANK TYPE:" << std::endl;
	std::cout << "1 tank that have more speed." << std::endl;
	std::cout << "2 tank that have more health." << std::endl;
	std::cout << "3 tank that do more dmg." << std::endl;
	int type;
	std::cin >> type;
	
	auto tank = _levelGame->GetTanks()[_players == 2 ? 1 : 0];

	auto& inputComp = tank->entity.addComponent<InputComponent>();
	tank->entity.activate();

	TankFactory::CreateTank(tank, (TANK_TYPE)type);


	if (_players == 2)
	{
		_players--;
		inputComp.keys.up = G_KEY_UP;
		inputComp.keys.down = G_KEY_DOWN;
		inputComp.keys.left = G_KEY_LEFT;
		inputComp.keys.right = G_KEY_RIGHT;
		inputComp.keys.shot = G_KEY_NUMPAD_0;
	}
	else
	{
		_currentScreen = MENU_SCREEN::GAME;
		SetAI();
	}
	ShowMenu();
}

void ConsoleGUI::SetAI()
{
	SetAI(_levelGame->GetTanks()[3]);
	SetAI(_levelGame->GetTanks()[2]);
	if (!_levelGame->GetTanks()[1]->entity.hasComponent<InputComponent>())
		SetAI(_levelGame->GetTanks()[1]);
}

void ConsoleGUI::SetAI(GameObject * obj)
{
	ComponentsFactory::AddAI(obj->entity);
	TANK_TYPE type = (TANK_TYPE)_random.Next(1, 3);
	TankFactory::CreateTank(obj, type);
}