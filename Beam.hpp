#ifndef BEAM_HPP
#define BEAM_HPP

#include "Sprite.hpp"
#include "sstream"

using namespace sf;

class CBeam
{
public:
	CBeam();
	~CBeam();

	//Textures the sprite
	void Load(Texture *_beamTexture, Texture *_frameTexture, int *_value, int *_maxValue);

	//Sets the Position for float values
	void SetPos(float _x, float _y);

	//Sets the Position for int values
	void SetPos(int _x, int _y);

	//sets the font
	void SetText(Font _font, Color _color, int _size);

	//sets the character size
	void SetCharacterSize(int _size){m_text.setCharacterSize(_size);}

	//Renders the beam
	void Render(RenderTarget *_target);

	//renders the beam with numbers
	void RenderWithNumbers(RenderTarget *_target);


private:

	Sprite m_Beam;                //the beam sprite
	CSprite *m_pFrame;                //the frame sprite

	int * m_value;                    //the current value
	int *m_maxValue;                //the maximum of the value

	int m_frameWidth;              //the width of one frame

	Font m_font;
	Text m_text;                    //the text


};

#endif