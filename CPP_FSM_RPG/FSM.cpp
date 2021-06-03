#include <iostream>
#include "Player.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"

int main()
{
	srand(time(NULL));
	
	Player player(ent_Player_Elsa);

	for (int i = 0; 20 > i; i++)
	{
		player.Update();

		Sleep(1000);
	}

	PressAnyKeyToContinue();
}