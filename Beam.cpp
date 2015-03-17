#include "Beam.hpp"



CBeam::CBeam()
{
	m_pFrame = NULL;
	m_value = NULL;
	m_maxValue = NULL;
}



CBeam::~CBeam()
{
	if(m_pFrame != NULL)
		delete(m_pFrame);

	m_pFrame = NULL;
}




void CBeam::Load(Texture *_beamTexture, Texture *_frameTexture, int *_value, int *_maxValue)
{
	//Set the texture
	m_Beam.setTexture(*_beamTexture);

	//Check, if the texture was set
	if(m_Beam.getTexture() == NULL)
	{
		cout <<"Konnte Textur nicht setzen" << endl;
	}

	m_pFrame = new CSprite;
	m_pFrame->Load(_frameTexture);

	m_value = _value;
	m_maxValue = _maxValue;

	m_frameWidth =  m_Beam.getTextureRect().width/2;

	//set the start values
	m_Beam.setTextureRect(IntRect(0,0, m_frameWidth, m_Beam.getTextureRect().height));

	m_font.loadFromFile("Data/Fonts/coolsville.ttf");
	m_text.setCharacterSize(12);
	m_text.setColor(Color::Black);
	m_text.setFont(m_font);
}



void CBeam::SetPos(int _x, int _y)
{
	m_pFrame->SetPos(_x, _y);
	m_Beam.setPosition((float)(_x), (float)(_y));
}


void CBeam::SetPos(float _x, float _y)
{
	m_pFrame->SetPos(_x, _y);
	m_Beam.setPosition(_x, _y);
}




void CBeam::Render(RenderTarget *_target)
{
	//sets the new Texture rect
	m_Beam.setTextureRect(IntRect(m_frameWidth - (int)(((float)(*m_value) / (float)(*m_maxValue))*m_frameWidth), 0, m_frameWidth, m_Beam.getTextureRect().height));

	//renders the beam
	_target->draw(m_Beam);
	m_pFrame->Render(_target);
}



void CBeam::RenderWithNumbers(RenderTarget *_target)
{
	stringstream stream;
	stream.str("");

	Render(_target);

	stream << *m_value << "/" << *m_maxValue;
	m_text.setString(stream.str());
	m_text.setPosition(m_Beam.getTextureRect().width/2 + m_Beam.getPosition().x - m_text.getGlobalBounds().width/2, m_Beam.getTextureRect().height/2 + m_Beam.getPosition().y - m_text.getGlobalBounds().height/2 - 2);
	_target->draw(m_text);
}



void CBeam::SetText(Font _font, Color _color, int _size)
{
	m_font = _font;
	m_text.setColor(_color);
	m_text.setCharacterSize(_size);
}