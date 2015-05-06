#include "Sprite.hpp"




CSprite::CSprite()
{
	m_NumFrames = 0;
}




CSprite::~CSprite()
{

}




void CSprite::Load(Texture *_texture)
{
	//Set the texture
	m_Sprite.setTexture(*_texture);

	//Check, if the texture was set
	if(m_Sprite.getTexture() == NULL)
	{
		cout <<"Konnte Textur nicht setzen" << endl;
	}

	//Set the rectangle
	m_Rect.top = 0;
	m_Rect.left = 0;
	m_Rect.height = m_Sprite.getTextureRect().height;
	m_Rect.width = m_Sprite.getTextureRect().width;
}



void CSprite::Load(Texture *_texture, int _numFrames, int _frameWidth, int _frameHeight)
{
	//Set the texture
	Load(_texture);

	//set the frame rect
	m_NumFrames = _numFrames;
	m_FrameHeight = _frameHeight;
	m_FrameWidth = _frameWidth;
	m_FrameRect.height = _frameHeight;
	m_FrameRect.width = _frameWidth;
	m_NumFramesX = m_Rect.width / m_FrameWidth;

	m_Rect.height = _frameHeight;
	m_Rect.width = _frameWidth;
}



void CSprite::SetPos(int _x, int _y)
{
	//set the rect position
	m_Rect.left = _x;
	m_Rect.top = _y;

	//set the "real" position
	m_Sprite.setPosition(static_cast<float>(_x),static_cast<float>(_y));
}



void CSprite::SetPos(float _x, float _y)
{
	//set the rect position
	m_Rect.left = static_cast<int>(_x);
	m_Rect.top = static_cast<int>(_y);

	//set the real position
	m_Sprite.setPosition(_x, _y);
}



//void CSprite::Move(int _x, int _y)
//{
//	m_Sprite.move(static_cast<float>(_x), static_cast<float>(_y));
//
//	m_Rect.left = (int)m_Sprite.getPosition().x;
//	m_Rect.top = (int)m_Sprite.getPosition().y;
//}



void CSprite::Move(float _x, float _y)
{
	m_Sprite.move(_x, _y);

	m_Rect.left = (int)m_Sprite.getPosition().x;
	m_Rect.top = (int)m_Sprite.getPosition().y;
}


//sets the texture rect
void CSprite::setTextureRect(IntRect &_rect)
{
	m_Sprite.setTextureRect(_rect);
}


void CSprite::setTextureRectToDefault()
{
	m_Sprite.setTextureRect(IntRect(0,0, m_Sprite.getTexture()->getSize().x, m_Sprite.getTexture()->getSize().y));
}


void CSprite::setRotatingPoint(float _x, float _y)
{
	m_Sprite.setOrigin(_x, _y);
}


void CSprite::rotate(float _angle)
{
	m_Sprite.rotate(_angle);
}


void CSprite::setRotation(float _angle)
{
	m_Sprite.setRotation(_angle);
}


void CSprite::resetRotation()
{
	m_Sprite.setRotation(0.0f);
}


void CSprite::setScale(float _x, float _y)
{
	m_Sprite.setScale(_x, _y);
}

//render "normal" sprites
void CSprite::Render(RenderTarget *_target, IntRect *clip)
{
	//check if a clip was given
	if(clip != NULL)
	{
		m_Sprite.setTextureRect(*clip);
		_target->draw(m_Sprite);
	}
	else
		_target->draw(m_Sprite);
}


//render animated sprites
void CSprite::Render(RenderTarget *_target, float _fFrameNumber)
{
	//calculate column
	int Column = static_cast<int>(_fFrameNumber)%m_NumFramesX;

	//calculate row
	int Row = static_cast<int>(_fFrameNumber)/m_NumFramesX;

	//calculate rect
	m_FrameRect.left = Column* m_FrameWidth;
	m_FrameRect.top = Row * m_FrameHeight;


	//render Sprite
    Render(_target, &m_FrameRect);

}



void CSprite::SetColor(int R, int G, int B, int A)
{
	m_Sprite.setColor(Color(R,G,B,A));
}



IntRect CSprite::GetGlobalRect()
{
	return (IntRect)m_Sprite.getGlobalBounds();
}

