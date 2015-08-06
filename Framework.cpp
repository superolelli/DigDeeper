#include "Framework.hpp"



//Opens the window
void CFramework::Init()
{
	m_pRealWindow = new RenderWindow;
    m_pRealWindow->create(VideoMode::getDesktopMode(), "Dig Deeper", Style::None | Style::Fullscreen);
	m_pRealWindow->setVerticalSyncEnabled(true);
	m_pRealWindow->setKeyRepeatEnabled(false);

	m_pWindow = new RenderTexture;
	m_pWindow->create(m_pRealWindow->getSize().x, m_pRealWindow->getSize().y, false);

	m_Shader = 0;
	m_fBlurNumber = 0.005f;
	m_fBlurTimer = 0;
	m_moreBlur = true;

	m_pMyLog = new ige::FileLogger("0.2", "logfile.txt");
}




//Closes and deletes the window
void CFramework::Quit()
{
	m_pRealWindow->close();
	SAFE_DELETE(m_pRealWindow);
	SAFE_DELETE(m_pWindow);
	SAFE_DELETE(m_pMyLog);
}



//Updates the timer
void CFramework::Update()
{
	g_pTimer->Update();
}



//fills the background black
void CFramework::Clear(Color _color)
{
	m_pRealWindow->clear(_color);
	m_pWindow->clear(_color);
}


//shows the new frame
void CFramework::Flip()
{
	m_pWindow->display();

	Sprite sprite;
	sprite.setTexture(m_pWindow->getTexture());

	switch (m_Shader)
	{
	case(NO_SHADER) :
		m_pRealWindow->draw(sprite);
		break;
	case(DRUNK) :
		if (m_fBlurTimer <= 0)
		{
			if (m_moreBlur)
			{
				m_fBlurNumber += 0.0001;
				if (m_fBlurNumber >= 0.02)
					m_moreBlur = false;
			}
			else
			{
				m_fBlurNumber -= 0.0001;
				if (m_fBlurNumber <= 0.003)
					m_moreBlur = true;
			}

			m_fBlurTimer = 0.0001;
		}
		else
			m_fBlurTimer -= g_pTimer->GetElapsedTime().asSeconds();

		g_pTextures->s_drunkShader.setParameter("blur_radius", m_fBlurNumber);
		RenderStates states;
		states.shader = &g_pTextures->s_drunkShader;
		m_pRealWindow->draw(sprite, states);
		break;
	}

	m_pRealWindow->display();
}



//returns a vector with all events happened as int IDs
void CFramework::ProcessEvents()
{

	Event event;

	ClearKeyStates();

	while(m_pRealWindow->pollEvent(event))
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

					if (event.key.code == Keyboard::M)
						keyStates.mUp = true;

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

					if (event.key.code == Keyboard::F1)
						keyStates.f1 = true;
					
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

					if (event.key.code == Mouse::Right)
						keyStates.rightMouseUp = true;
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
	keyStates.rightMouseUp = false;
	keyStates.escapeDown = false;
	keyStates.eUp = false;
	keyStates.bUp = false;
	keyStates.mUp = false;
	keyStates.cUp = false;
	keyStates.add = false;
	keyStates.subtract = false;
	keyStates.backspace = false;
	keyStates.f3 = false;
	keyStates.f1 = false;

	keyStates.text_entered = false;
	keyStates.text_input = 'a';

	keyStates.mouseWheelMovement = 0;
}




void CFramework::WriteToLog(int _ID, string _message)
{
	switch (_ID)
	{
	case(ERROR) :
		*m_pMyLog << ige::FileLogger::e_logType::LOG_ERROR << _message.c_str();
		break;
	case(WARNING) :
		*m_pMyLog << ige::FileLogger::e_logType::LOG_WARNING << _message.c_str();
		break;
	default:
		*m_pMyLog << _message.c_str();
		break;
	}
}