#include "LightMachine.hpp"
#include "World.hpp"



CLightMachine::CLightMachine()
{
	m_View = NULL;
}



void CLightMachine::Quit()
{
	m_View = NULL;
}



void CLightMachine::Init(View* _view, CWorld *_world, bool _fastLight) 
{
	//creates the render texture
	m_lightTexture.create(_view->getSize().x +20, _view->getSize().y +20);
	m_lightTexture.clear(Color(0, 0, 0, 0));

	m_View = _view;
	m_pWorld = _world;

	m_fastLight = _fastLight;

	m_ViewLastWidth = m_View->getSize().x;

	m_ViewX = m_View->getCenter().x - m_View->getSize().x / 2;
	m_ViewY = m_View->getCenter().y - m_View->getSize().y / 2;
	m_currentAlpha = 0;
}



void CLightMachine::Clear(Color _color)
{
	//if the user zoomed
	if(m_ViewLastWidth != (int)(m_View->getSize().x))
	{
		m_ViewLastWidth = m_View->getSize().x;
		m_lightTexture.create(m_View->getSize().x + 20, m_View->getSize().y + 20);
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
	lights.setPosition(m_ViewX - 10, m_ViewY - 10);


	g_pFramework->GetRenderWindow()->draw(lights);
}



void CLightMachine::AddLightCircle(int _x, int _y, int _radius, Color _color)
{
	VertexArray circle(TrianglesFan, 92);
	circle[0].position.x = _x - m_ViewX + 10;
	circle[0].position.y = _y - m_ViewY + 10;
	circle[0].color = Color(255, 255, 255, _color.a);

	for (int angle = 1; angle <= 91; angle++)
	{
		circle[angle].position = Vector2f((_x - m_ViewX + 10) + _radius * g_pSinCosLookup->cosLookup[(angle-1)*4], (_y - m_ViewY + 10) + _radius * g_pSinCosLookup->sinLookup[(angle-1)*4]);

		circle[angle].position = IsLineIntersecting(circle[0], circle[angle], (angle-1)*4, _radius);

		circle[angle].color = Color(_color.r, _color.g, _color.b, 255);
	}

	m_lightTexture.draw(circle, BlendMultiply);
}




void CLightMachine::AddLightBeam(int _x, int _y, int _length, int _width, Color _color)
{
	Vector2f newPosition = IsBeamIntersecting(Vector2f(_x, _y),Vector2f(_x, _y + _length));
	int newLength = newPosition.y - _y;
	
	
	VertexArray lightRect(Quads, 4);
	lightRect[0].position.x = _x - m_ViewX + 10;
	lightRect[0].position.y = _y - m_ViewY + 10;
	lightRect[0].color = _color;

	lightRect[1].position.x = _x - m_ViewX + 10 + _width;
	lightRect[1].position.y = lightRect[0].position.y;
	lightRect[1].color = lightRect[0].color;

	lightRect[3].position.x = lightRect[0].position.x;
	lightRect[3].position.y = _y - m_ViewY + 10 + (newLength - 0.15*newLength);
	lightRect[3].color = Color(255, 255, 255, _color.a);

	lightRect[2].position.x = lightRect[1].position.x;
	lightRect[2].position.y = lightRect[3].position.y;
	lightRect[2].color = lightRect[3].color;

	m_lightTexture.draw(lightRect, BlendMultiply);

	lightRect[0].position.x = _x - m_ViewX + 10;
	lightRect[0].position.y = _y - m_ViewY + 10 + (newLength - 0.15*newLength);
	lightRect[0].color = Color(255, 255, 255, _color.a);

	lightRect[1].position.x = _x - m_ViewX + 10 + _width;
	lightRect[1].position.y = lightRect[0].position.y;
	lightRect[1].color = lightRect[0].color;

	lightRect[3].position.x = lightRect[0].position.x;
	lightRect[3].position.y = _y - m_ViewY + 10 + newLength;
	lightRect[3].color = Color(255, 255, 255, 255);

	lightRect[2].position.x = lightRect[1].position.x;
	lightRect[2].position.y = lightRect[3].position.y;
	lightRect[2].color = lightRect[3].color;

	m_lightTexture.draw(lightRect, BlendMultiply);
}



//Vector2f CLightMachine::IsLineIntersecting(Vertex _firstPoint, Vertex _secondPoint, int _angle, int _radius)
//{
//	if (_firstPoint.position.y <= 0 && _secondPoint.position.y < _firstPoint.position.y)
//		return Vector2f(0, 0);
//
//	//coordinates of the first point
//	int centerX = _firstPoint.position.x;
//	int centerY = _firstPoint.position.y;
//
//	//tangens of the angle
//	float tangens = tan(_angle * 3.1415926535 / 180);
//
//	if (_angle == 0 || _angle == 360)
//		_secondPoint.position = IsLineIntersectingHV(Vector2f(centerX, centerY), Vector2f(100,0), _radius);
//	else if (_angle > 0 && _angle < 90)
//	{
//
//	}
//	else if (_angle == 90)
//		_secondPoint.position = IsLineIntersectingHV(Vector2f(centerX, centerY), Vector2f(0, -100), _radius);
//	else if (_angle > 90 && _angle < 180)
//	{
//
//	}
//	else if (_angle == 180)
//		_secondPoint.position = IsLineIntersectingHV(Vector2f(centerX, centerY), Vector2f(-100, 0), _radius);
//	else if (_angle > 180 && _angle < 270)
//	{
//
//	}
//	else if (_angle == 270)
//		_secondPoint.position = IsLineIntersectingHV(Vector2f(centerX, centerY), Vector2f(0, 100), _radius);
//	else
//	{
//
//	}
//
//
//
//
//	return _secondPoint.position;
//}
//
//
//
//Vector2f CLightMachine::IsLineIntersectingHV(Vector2f _point, Vector2f _step, int _radius)
//{
//	Vector2f currentPoint = _point;
//	int length = 0;
//	int x, y;
//
//	while (1)
//	{
//		x = (currentPoint.x - 10 + m_ViewX) / 100;
//		y = (currentPoint.y - 10 + m_ViewY) / 100;
//
//		if (!m_pWorld->isBlockPassable(x,y))
//		{
//			if (_step.x > 0)
//				return Vector2f((currentPoint.x / 100) * 100 + 100, currentPoint.y);
//			else if (_step.x < 0)
//				return Vector2f((currentPoint.x / 100) * 100, currentPoint.y);
//			else if (_step.y > 0)
//				return Vector2f(currentPoint.x, (currentPoint.y / 100) * 100 + 100);
//			else
//				return Vector2f(currentPoint.x, (currentPoint.y / 100) * 100);
//		}
//
//		currentPoint += _step;
//		length += abs(_step.x);
//		length += abs(_step.y);
//
//		if (length >= _radius)
//		{
//			//if the radius was reached
//			if (_step.x > 0)
//				return Vector2f(_point.x + _radius, _point.y);
//			else if (_step.x < 0)
//				return Vector2f(_point.x - _radius, _point.y);
//			else if (_step.y > 0)
//				return Vector2f(_point.x, _point.y + _radius);
//			else
//				return Vector2f(_point.x, _point.y - _radius);
//		}
//
//	}
//}



Vector2f CLightMachine::IsLineIntersecting(Vertex _firstPoint, Vertex _secondPoint, int _angle, int _radius)
{
	if (_firstPoint.position.y <= 0 && _secondPoint.position.y < _firstPoint.position.y)
		return Vector2f(0, 0);


	int currentRadius = 5;
	int x, y;

	bool is_intersecting = false;

	while (is_intersecting == false)
	{
		_secondPoint.position = Vector2f(_firstPoint.position.x + currentRadius * g_pSinCosLookup->cosLookup[_angle], _firstPoint.position.y + currentRadius * g_pSinCosLookup->sinLookup[_angle]);


		x = (_secondPoint.position.x - 10 + m_ViewX) / 100;
		y = (_secondPoint.position.y - 10 + m_ViewY) / 100;


		if (!m_pWorld->isBlockPassable(x, y))
		{
			//calculate the length for the light to shine into the next block
			int length = 0;
			if ((_angle >= 45 && _angle < 135) || (_angle >= 225 && _angle < 315))
				 length = 100 / (abs(g_pSinCosLookup->sinLookup[_angle]));
			else
				length = 100 / (abs(g_pSinCosLookup->cosLookup[_angle]));
			
			//set new length
			if (currentRadius + length > _radius)
				_secondPoint.position = Vector2f(_firstPoint.position.x + _radius * g_pSinCosLookup->cosLookup[_angle], _firstPoint.position.y + _radius * g_pSinCosLookup->sinLookup[_angle]);
			else
				_secondPoint.position = Vector2f(_firstPoint.position.x + (length + currentRadius) * g_pSinCosLookup->cosLookup[_angle], _firstPoint.position.y + (currentRadius + length) * g_pSinCosLookup->sinLookup[_angle]);
			
			//return new point
			return _secondPoint.position;
		}

		
		if (m_fastLight)
			currentRadius += 10;
		else
			currentRadius += 2;

		if (currentRadius > _radius)
			return _secondPoint.position;
	}

	return _secondPoint.position;
}












Vector2f CLightMachine::IsBeamIntersecting(Vector2f _firstPoint, Vector2f _lastPoint)
{
	int xBlock = _firstPoint.x / 100;
	int yBlock = _firstPoint.y / 100;

	while (m_pWorld->isBlockPassable(xBlock, yBlock))
	{
		yBlock++;

		if (yBlock == _lastPoint.y / 100)
			break;
	}

	return Vector2f(_firstPoint.x, (yBlock+1) * 100);
}