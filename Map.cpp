#include "Map.h"
#include "TextureMngr.h"
#include "Components.h"


Map::Map()
{
	sand = TextureManager::LoadTexture("assets/sand.png");
	dirt = TextureManager::LoadTexture("assets/dirt.png"); 
	water = TextureManager::LoadTexture("assets/water.png");

	LoadMap(lvl1);

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
}



void Map::LoadMap(int arr[20][25])
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int tip = 0;
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			tip = map[row][column];

			dest.x = column * 32;			
			dest.y = row * 32;			

			switch (tip)
			{
			case 0:
				TextureManager::draw(water, src, dest);
				break;
			case 1:
				TextureManager::draw(sand, src, dest);
				break;
			case 2:
				TextureManager::draw(dirt, src, dest);
			default:
				break;
			}
		}
	}
}

