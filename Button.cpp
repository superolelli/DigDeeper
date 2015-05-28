#include "Button.hpp"



CButton::CButton()
{
	m_pButtonSprite = NULL;
	m_pRenderWindow = NULL;
}


CButton::~CButton()
{
	SAFE_DELETE(m_pButtonSprite);
}



//Loads the texture, sets the position and type of the button
void CButton::Load(Texture *_texture, int _x, int _y, int _type)
{
	m_pRenderWindow = g_pFramework->GetWindow();

	m_pButtonSprite = new CSprite;

	//Load the texture
	switch(_type)
	{
	case BUTTONTYPE_UP: 
		m_pButtonSprite->Load(_texture, 2, _texture->getSize().x/2, _texture->getSize().y);
		break;

    case BUTTONTYPE_DOWN:
		m_pButtonSprite->Load(_texture, 2, _texture->getSize().x/2, _texture->getSize().y);
		break;

	case BUTTONTYPE_MOTION_UP: 
		m_pButtonSprite->Load(_texture, 3, _texture->getSize().x/3, _texture->getSize().y);
		break;

    case BUTTONTYPE_MOTION_DOWN:
		m_pButtonSprite->Load(_texture, 3, _texture->getSize().x/3, _texture->getSize().y);
		break;
	}

	//set the button's position and type
	m_pButtonSprite->SetPos(_x, _y);
	m_Buttontype = _type;
}



//sets the button's position
void CButton::SetPos(int _x, int _y)
{
	m_pButtonSprite->SetPos(_x, _y);
}




bool CButton::Render(int eventtype)
{
	 //if the mouse is at the button
	if(m_pButtonSprite->GetRect().contains(Mouse::getPosition(*m_pRenderWindow)))
	{
		//If the left mouse button was released
		if(eventtype == MOUSE_LEFT_UP)
		{
			//render the right button frame
			switch(m_Buttontype)
			{
			case BUTTONTYPE_UP:
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 1.0f);
				g_pSound->m_sound.setBuffer(g_pSound->m_buttonClick);
				g_pSound->m_sound.play();
				return true;
				break;

			case BUTTONTYPE_DOWN:
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 0.0f);
				return false;
				break;

			case BUTTONTYPE_MOTION_UP:
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 2.0f);
				g_pSound->m_sound.setBuffer(g_pSound->m_buttonClick);
				g_pSound->m_sound.play();
				return true;
				break;

			case BUTTONTYPE_MOTION_DOWN:
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 0.0f);
				return false;
				break;
			}
		}
		//if the left mouse button was pressed
		else if(Mouse::isButtonPressed(Mouse::Left))
		{
			//Render the right button frame
			switch(m_Buttontype)
			{
			case BUTTONTYPE_UP:
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 1.0f);
				return false;
				break;

			case BUTTONTYPE_DOWN:
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 1.0f);
				g_pSound->m_sound.setBuffer(g_pSound->m_buttonClick);
				g_pSound->m_sound.play();
				return true;
				break;

			case BUTTONTYPE_MOTION_UP:
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 2.0f);
				return false;
				break;

			case BUTTONTYPE_MOTION_DOWN:
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 2.0f);
				g_pSound->m_sound.setBuffer(g_pSound->m_buttonClick);
				g_pSound->m_sound.play();
				return true;
				break;
			}
		}
		else 
		{
			if(m_Buttontype == BUTTONTYPE_UP || m_Buttontype == BUTTONTYPE_DOWN)
			{
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 0.0f);
			}
			else
				m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 1.0f);

			return false;
		}
	}


	m_pButtonSprite->Render(g_pFramework->GetRenderWindow(), 0.0f);
	return false;
}




