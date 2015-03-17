#include "LightMachine.hpp"




CLightMachine::CLightMachine()
{
	m_View = NULL;
}



void CLightMachine::Quit()
{
	m_View = NULL;
}



void CLightMachine::Init(View* _view) 
{
	//creates the render texture
	m_lightTexture.create(_view->getSize().x +20, _view->getSize().y +20);
	m_lightTexture.clear(Color(0, 0, 0, 0));

	m_View = _view;

	m_ViewLastWidth = m_View->getSize().x;
	m_currentAlpha = 0;
}



void CLightMachine::Clear(Color _color)
{
	//if the user zoomed
	if(m_ViewLastWidth != (int)(m_View->getSize().x))
	{
		cout <<"Last Width: " << m_ViewLastWidth << endl;
		cout <<"New Width: " << m_View->getSize().x << endl;
		m_ViewLastWidth = m_View->getSize().x;

		m_lightTexture.create(m_View->getSize().x +20, m_View->getSize().y +20);
	}

	m_lightTexture.clear(_color);
	m_currentAlpha = _color.a;

	m_ViewX = m_View->getCenter().x - m_View->getSize().x/2;
	m_ViewY = m_View->getCenter().y - m_View->getSize().y/2;
}


//renders the light
void CLightMachine::Render()
{
	Sprite lights;
	m_lightTexture.display();
	lights.setTexture(m_lightTexture.getTexture());
	lights.setPosition(m_ViewX -10, m_ViewY -10);

	g_pFramework->GetWindow()->draw(lights);
}



void CLightMachine::AddLightCircle(int _x, int _y, int _radius, Color _color)
{
		//create a circle
		CircleShape circle;
		circle.setRadius(_radius);
		circle.setOutlineThickness(0);
		circle.setFillColor(Color(_color.r, _color.g, _color.b, 0));
		circle.setPosition(_x - m_ViewX +10, _y - m_ViewY +10);
	
		//draw this circle, to set the alpha in the render texture to zero
		m_lightTexture.draw(circle, BlendMultiply);

		//draw a second circle for the colour
		circle.setFillColor(Color(_color.r, _color.g, _color.b, (float)(m_currentAlpha)/2.5));
	
		m_lightTexture.draw(circle, BlendAdd);
}