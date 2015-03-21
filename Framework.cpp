#include "Framework.hpp"



//Opens the window
void CFramework::Init()
{
	m_pWindow = new RenderWindow;
    m_pWindow->create(VideoMode::getDesktopMode(), "Dig Deeper", Style::None | Style::Fullscreen);
	m_pWindow->setVerticalSyncEnabled(true);
	m_pWindow->setKeyRepeatEnabled(false);
}




//Closes and deletes the window
void CFramework::Quit()
{
	m_pWindow->close();
	SAFE_DELETE(m_pWindow);
}



//Updates the timer
void CFramework::Update()
{
	g_pTimer->Update();
}



//fills the background black
void CFramework::Clear()
{
	m_pWindow->clear();
}


//shows the new frame
void CFramework::Flip()
{
	m_pWindow->display();
}



//returns a vector with all events happened as int IDs
void CFramework::ProcessEvents()
{

	Event event;

	ClearKeyStates();

	while(m_pWindow->pollEvent(event))
	{
		if(event.type == Event::TextEntered)
		{
			if(event.text.unicode < 128)
			{
				keyStates.text_entered = true;
				keyStates.text_input = static_cast<char>(event.text.unicode);
			}
		}

		switch(event.type)
		{
			case Event::Closed:
				{
					Quit();
					keyStates.escapeDown = true;
				}break;
				
			case Event::KeyPressed:
				{
					if(event.key.code == Keyboard::Escape)
						keyStates.escapeDown = true;
					
					if(event.key.code == Keyboard::E)
						keyStates.eUp = true;

					if(event.key.code == Keyboard::B)
						keyStates.bUp = true;

					if(event.key.code == Keyboard::C)
						keyStates.cUp = true;

					if(event.key.code == Keyboard::Add)
						keyStates.add = true;

					if(event.key.code == Keyboard::Subtract)
						keyStates.subtract = true;

					if(event.key.code == Keyboard::BackSpace)
						keyStates.backspace = true;

					if (event.key.code == Keyboard::F3)
						keyStates.f3 = true;
					
				}break;


			case Event::MouseButtonPressed:
				{
					if(event.key.code == Mouse::Left)
						keyStates.leftMouseDown = true;

					if(event.key.code == Mouse::Right)
						keyStates.rightMouseDown = true;
					
				}break;
				
			case Event::MouseButtonReleased:
				{
					if(event.key.code == Mouse::Left)
						keyStates.leftMouseUp = true;
				}break;

			case Event::MouseWheelMoved:
				{
					keyStates.mouseWheelMovement = event.mouseWheel.delta;
				}break;

		}
	}

	
}



void CFramework::ClearKeyStates()
{
	keyStates.leftMouseDown = false;
	keyStates.leftMouseUp = false;
	keyStates.rightMouseDown = false;
	keyStates.escapeDown = false;
	keyStates.eUp = false;
	keyStates.bUp = false;
	keyStates.cUp = false;
	keyStates.add = false;
	keyStates.subtract = false;
	keyStates.backspace = false;
	keyStates.f3 = false;

	keyStates.text_entered = false;
	keyStates.text_input = 'a';

	keyStates.mouseWheelMovement = 0;
}