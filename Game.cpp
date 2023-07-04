#include "Game.h"
#include "TextureMngr.h"
#include "Components.h"
#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Garbage.h"
#include "Enemy.h"
#include "Player.h"
#include "GameObject.h"
#include "MainMenuComponent.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <vector>

MainMenu *menu;

Map *maP;

SDL_Renderer *Game::renderer = nullptr;

SDL_Event Game::event;

Manager manager;

bool Game::isRunning = false;

vector<ColliderComponent*> Game::colliders;

//auto &player(manager.addEntity());


enum groupLabels : size_t 
{
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto &players(manager.getGroup(groupPlayers));


Game::Game()
{
	srand(time(0));
}


Game::~Game()
{

}

Vector2D Game::Seterup(bool onland)
{
	bool IsPosOk = false;
	Vector2D tmp;
	int x, y;
	while (!IsPosOk)
	{
		x = rand() % 25;
		y = rand() % 20;
		if (lvl1[y][x] > 0 && onland==true)
		{
			tmp.x = x*32;
			tmp.y = y*32;
			IsPosOk = true;
		}
		if (lvl1[y][x] == 0 && onland == false)
		{
			tmp.x = x * 32;
			tmp.y = y * 32;
			IsPosOk = true;
		}
	}
	return tmp;
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	bool postavljen=false;
	int flags = 0, post=0;
	Vector2D SetupVector;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			if (window)
			{
			//	std::cout << "Window created!" << std::endl;
			}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			//std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	//saveScore();
	//loadScoreBoard();
	maP = new Map();
	menu = new MainMenu("Assets/Menu.png", 0, 0);
	ifstream data;
	struct dingdong ding;
	int countercount = 0;
	data.open("Quicksave.bin", ios::binary);
	if (data.is_open())
	{


		while (data.read((char *)&ding, sizeof(ding)))
		{
			if (countercount <=0)
			{
				playerpl = new Player(ding.x, ding.y, manager, EntityType::PLAYER);
				manager.addEntity(playerpl);
				
			}
			else if (countercount < 21)
				manager.addEntity(new Enemy(ding.x, ding.y, manager, EntityType::ENEMY));
			else
			{
				manager.addEntity(new Garbage(ding.x, ding.y, manager, EntityType::GARBAGE));

			}
			countercount++;

		}
		data.close();
		remove("Quicksave.bin");

	}

	else
	{
		playerpl = new Player(64, 256, manager, EntityType::PLAYER);
		manager.addEntity(playerpl);
		while (!postavljen)
		{
			SetupVector = Seterup(1);
			manager.addEntity(new Enemy(SetupVector.x, SetupVector.y, manager, EntityType::ENEMY));
			post++;
			if (post >= 20)
			{
				postavljen = true;
			}
		}
		postavljen = false;
		post = 0;
		while (!postavljen)
		{
			SetupVector = Seterup(0);
			manager.addEntity(new Garbage(SetupVector.x, SetupVector.y, manager, EntityType::GARBAGE));
			post++;
			if (post >= 10)
			{
				postavljen = true;
			}
		}
	}
	/*manager.addEntity(new Enemy(544, 128, manager, EntityType::ENEMY));
	manager.addEntity(new Enemy(544, 128, manager, EntityType::ENEMY));
	auto &entities = manager.GetEntities();
	for (int i = 0; i < entities.size(); i++)
	{
		cout << entities[i]->getComponent<TransformComponent>().position.x << " " << entities[i]->getComponent<TransformComponent>().position.y << endl;
	}
	*/
}

void Game::saveScore()
{
	scoreboard score;
	ofstream data;
	data.open("Score.bin", ios::binary | ios::app);
	strcpy_s(score.ime, playerpl->ime);
	score.x = playerpl->score;
	cout << playerpl->score << endl;
	data.write((char*)&score, sizeof(score));
	data.close();
}

int Game::numEnemiesLeft()
{
	auto &entities = manager.GetEntities();
	int temp = 0;
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getType() == EntityType::ENEMY || entities[i]->getType() == EntityType::GARBAGE)
		{
			temp++;
		}
	}
	return temp;
}

int Game::numEnemiesAt(int x, int y)
{
	auto &entities = manager.GetEntities();
	int temp = 0;
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getType() == EntityType::ENEMY && entities[i]->getComponent<TransformComponent>().position.x == x && entities[i]->getComponent<TransformComponent>().position.y == y)
		{
			temp++;
		}
	}
	return temp;
}



void Game::loadScoreBoard()
{
	struct scoreboard score;
	ifstream data;
	vector<scoreboard> scores;
	data.open("Score.bin", ios::binary);
	if (data.is_open())
	{
		while (data.read((char*)&score, sizeof(score)))
		{
			scores.push_back(score);
		}

		data.close();
		std::sort(scores.begin(), scores.end(), [](scoreboard s1, scoreboard s2) {
			return s1.x > s2.x;
		});
		cout << "scoreboard:" << endl;
		for (int i = 0; i < scores.size() && i<5; i++)
		{
			cout << scores[i].ime << " " << scores[i].x << endl;
		}
	}
}

void Game::handleEvents()
{
	if (Game::event.type == SDL_KEYDOWN) {

		switch (Game::event.key.keysym.sym)
		{
		case SDLK_1:
			if (mainmenu)
				mainmenu = false;
				break;
		case SDLK_2:
			loadScoreBoard();
			break;

		case SDLK_ESCAPE:
			if (numEnemiesLeft() == 0)
			{
				saveScore();
			}
			Game::isRunning = false;
		default:
			break;
		}
	}
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

}



void Game::update()
{
	if (mainmenu)
	{
		menu->Update();
	}
	else
	{
		if (numEnemiesLeft() == 0)
		{
			playerpl->isDead = true;
		}
		if(playerpl->isDead)
		{ 
			static bool firstTime = true;
			if (firstTime) {
				firstTime = false;
				for (int i = 1; i < manager.GetEntities().size(); i++) {
					manager.GetEntities()[i]->destroy();
				}

			}
			if (!playerpl->replay())
			{
				saveScore();
				Game::isRunning = false;
			}
		
		}
		manager.update();
		manager.refresh();
	}
}


void Game::render()
{
	SDL_RenderClear(renderer);
	if (mainmenu)
	{
		menu->Render();
	}
	else
	{
		maP->DrawMap();

		/*for (auto& p : players) {
			p->draw();
		}

		for (auto& e : enemies) {
			e->draw();
		}*/
		manager.Draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::replay()
{

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}

