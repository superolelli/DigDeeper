#include "Framework.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include <thread>





void load_textures(bool *is_loading)
{
	
		//Load all textures
	g_pTextures->LoadTextures();

	*is_loading = false;
	
}


void loading_screen(bool *is_loading)
{
	Texture texture;
	texture.loadFromFile("Data/Sprites/Loading_screen.png");

	CSprite Loading_screen;
	Loading_screen.Load(&texture);

	while(*is_loading == true)
	{
		g_pFramework->Update();
		Loading_screen.Render(g_pFramework->GetWindow());
		g_pFramework->Flip();
	}
}



int main()
{
	//Init the framework
	g_pFramework->Init();

	bool is_loading = true;

	thread load;
	load = thread(load_textures, &is_loading);

	loading_screen(&is_loading);

	load.join();


	bool quit = false;

	g_pTextures->m_musicMenu.play();

	//Create the menu and start the main loop
	CMenu menu;
	while(quit == false)
	{
	    //Init the menu
		menu.Init();

		
		switch(menu.Run())
		{
		case(1):
			{
				//quit the program
				menu.Quit();
				quit = true;
			}break;
		case(2):
			{
				SNewWorldAttributes attributes = menu.Quit();

				g_pTextures->m_musicMenu.stop();

				CGame Game;

				Game.Init(attributes);
				Game.Run();
				Game.Quit();

				g_pTextures->m_musicMenu.play();

			}break;
		case(3):
			{
				menu.Quit();
			}break;
		case(10):
			{
				SNewWorldAttributes attributes = menu.Quit();

				g_pTextures->m_musicMenu.stop();

				CGame Game;

				Game.Load(attributes.GameName);
				Game.Run();
				Game.Quit();

				g_pTextures->m_musicMenu.play();

			}break;
		default:
			menu.Quit();
		}

			
	}

	g_pFramework->Quit();
}




