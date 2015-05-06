#ifndef SPRITE_HPP
#define SPRITE_HPP



#include "SFML\Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;



class CSprite 
{
public:

	CSprite();
	~CSprite();

	//Textures the sprite
	void Load(Texture *_texture);

	//Textures a animated sprite
	void Load(Texture *_texture, int _numFrames, int _frameWidth, int _frameHeight);

	//Sets the Position for float values
	void SetPos(float _x, float _y);

	//Sets the Position for int values
	void SetPos(int _x, int _y);

	//Moves the sprite(float)
	void Move(float _x, float _y);

	//Moves the sprite(int)
	/*void Move(int _x, int _y);*/

	//sets the part of the texture to render
	void setTextureRect(IntRect &_rect);

	//sets the texture rect to default
	void setTextureRectToDefault();

	//sets the rotating point
	void setRotatingPoint(float _x, float _y);

	//rotates the sprite
	void rotate(float _angle);

	//sets the rotation
	void setRotation(float _angle);

	//sets the rotation to 0
	void resetRotation();

	//sets the scale
	void setScale(float _x, float _y);

    //sets the sprite's colour
	void SetColor(int R, int G, int B, int A = 255);

	//Renders a normal sprite
	void Render(RenderTarget *_target, IntRect *clip = NULL);

	//Renders an animated sprite
	void Render(RenderTarget *_target, float _fFrameNumber);

	//returns the sprite's rectangle
	IntRect GetRect(){return m_Rect;}

	//returns the global rect
	IntRect GetGlobalRect();

private:

	Sprite m_Sprite;                   //the sprite
	IntRect m_Rect;                    //the sprite's rect
	IntRect m_FrameRect;               //the rect of an frame
	int m_NumFrames;                   //the number of frames 
	int m_FrameWidth;                  //the width of one frame
	int m_FrameHeight;                 //the height of one frame
	int m_NumFramesX;                  //the number of frames on the x axis


};





#endif