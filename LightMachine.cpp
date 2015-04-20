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



void CLightMachine::Init(View* _view, CWorld *_world) 
{
	//creates the render texture
	m_lightTexture.create(_view->getSize().x +20, _view->getSize().y +20);
	m_lightTexture.clear(Color(0, 0, 0, 0));

	m_View = _view;
	m_pWorld = _world;

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


	//vector<VertexArray> triangles;
	//int lastX, lastY;
	//Vector2f firstPoint, secondPoint;

	////calculate the start point
	//VertexArray StartLine(Lines, 2);
	//StartLine[0].position = Vector2f(_x, _y);
	//StartLine[1].position = Vector2f(_x + _radius, _y);

	//StartLine[1].position = IsLineIntersecting(StartLine);

	//firstPoint = StartLine[1].position;
	//lastX = StartLine[1].position.x;
	//lastY = StartLine[1].position.y;


	//for (int angle = 1; angle <= 360; angle+=2)
	//{

	//		//makes a line
	//		VertexArray line(Lines, 2);
	//		line[0].position = Vector2f(_x, _y);
	//		line[1].position = Vector2f(_x + _radius * cos(angle*3.1415926535 / 180), _y + _radius * sin(angle*3.1415926535 / 180));

	//		//checks for intersecting with solid blocks
	//		line[1].position = IsLineIntersecting(line);

	//		secondPoint = line[1].position;

	//		//if the wall is going on: save this position as second point
	//		if (lastX == line[1].position.x || lastY == line[1].position.y)
	//		{
	//			secondPoint = line[1].position;
	//		}
	//		else
	//		{
	//			//make the triangle
	//			VertexArray triangle(Triangles, 3);

	//			triangle[0].position = Vector2f(_x - m_ViewX + 10, _y - m_ViewY + 10);
	//			triangle[1].position = Vector2f(firstPoint.x - m_ViewX + 10, firstPoint.y - m_ViewY + 10);
	//			triangle[2].position = Vector2f(secondPoint.x - m_ViewX + 10, secondPoint.y - m_ViewY + 10);

	//			triangle[0].color = Color(255, 255, 255, 0);
	//			triangle[1].color = Color(255, 255, 255, 255);
	//			triangle[2].color = Color(255, 255, 255, 255);

	//			triangles.push_back(triangle);

	//			firstPoint = line[1].position;
	//		}
	//		
	//		lastX = line[1].position.x;
	//		lastY = line[1].position.y;

	//		
	//	
	//}



	////draw all triangles
	//for (int i = 0; i < triangles.size(); i++)
	//	m_lightTexture.draw(triangles[i], BlendMultiply);





	//VertexArray circle(TrianglesFan, 362);
	//circle[0].position.x = _x - m_ViewX + 10;
	//circle[0].position.y = _y - m_ViewY + 10;
	//circle[0].color = Color(255, 255, 255, 0);

	//for (int angle = 1; angle <= 361; angle++)
	//{
	//	circle[angle].position = Vector2f((_x - m_ViewX + 10) + _radius * cos(angle*3.1415926535 / 180), (_y - m_ViewY + 10) + _radius * sin(angle*3.1415926535 / 180));
	//	circle[angle].color = Color(_color.r, _color.g, _color.b, 255);
	//}
	//	
	//m_lightTexture.draw(circle, BlendMultiply);



	VertexArray circle(TrianglesFan, 182);
	circle[0].position.x = _x - m_ViewX + 10;
	circle[0].position.y = _y - m_ViewY + 10;
	circle[0].color = Color(255, 255, 255, 0);

	for (int angle = 1; angle <= 181; angle++)
	{
		circle[angle].position = Vector2f((_x - m_ViewX + 10) + _radius * cos(angle*2*3.1415926535 / 180), (_y - m_ViewY + 10) + _radius * sin(angle*2*3.1415926535 / 180));

		circle[angle].position = IsLineIntersecting(circle[0], circle[angle], angle*2, _radius);

		circle[angle].color = Color(_color.r, _color.g, _color.b, 255);
	}

	m_lightTexture.draw(circle, BlendMultiply);
}






Vector2f CLightMachine::IsLineIntersecting(Vertex _firstPoint, Vertex _secondPoint, int _angle, int _radius)
{

	int currentRadius = 5;
	int x, y;

	bool is_intersecting = false;

	while (is_intersecting == false)
	{
		_secondPoint.position = Vector2f(_firstPoint.position.x + currentRadius * cos(_angle*3.1415926535 / 180), _firstPoint.position.y + currentRadius * sin(_angle*3.1415926535 / 180));


		x = (_secondPoint.position.x - 10 + m_ViewX) / 100;
		y = (_secondPoint.position.y - 10 + m_ViewY) / 100;


		if (!m_pWorld->isBlockPassable(x, y))
		{
			int length = 100 / (abs(cos(_angle*3.1415926535 / 180)));
			
			if (currentRadius + length > _radius)
				_secondPoint.position = Vector2f(_firstPoint.position.x + _radius * cos(_angle*3.1415926535 / 180), _firstPoint.position.y + _radius * sin(_angle*3.1415926535 / 180));
			else
				_secondPoint.position = Vector2f(_firstPoint.position.x + (length + currentRadius) * cos(_angle*3.1415926535 / 180), _firstPoint.position.y + (currentRadius + length) * sin(_angle*3.1415926535 / 180));

			//_secondPoint.position = Vector2f(x - m_ViewX + 10, y - m_ViewY + 10);
			
			return _secondPoint.position;
		}

		currentRadius += 1;

		if (currentRadius > _radius)
			return _secondPoint.position;
	}



	//int startX, startY, destinationX, destinationY;

	//startX = ((_line[0].position.x - m_ViewX + 10) /100) +2;
	//startY = ((_line[0].position.y - m_ViewY + 10) / 100) + 2;

	//destinationX = ((_line[1].position.x - m_ViewX + 10) / 100) + 2;
	//destinationY = ((_line[1].position.y - m_ViewY + 10) / 100) + 2;

	//if (startX == destinationX && startY == destinationY)
	//	return nearestPoint;

	//if (startX >= 0 && startY >= 0 && destinationX >= 0 && destinationY >= 0 && startX < m_WorldMatrix.size() && startY < m_WorldMatrix[0].size() && destinationX < m_WorldMatrix.size() && destinationY < m_WorldMatrix[0].size())
	//{

	//	float currentX = startX;
	//	float currentY = startY;
	//	float changeRateX, changeRateY;

	//	//set change rate
	//	if (abs(startX - destinationX) > (abs(startY - destinationY)))
	//	{
	//		if (startX > destinationX)
	//			changeRateX = -1;
	//		else
	//			changeRateX = 1;

	//		if (startY > destinationY)
	//			changeRateY = -(abs(startY - destinationY)) / abs(startX - destinationX);
	//		else
	//			changeRateY = abs(startY - destinationY) / abs(startX - destinationX);
	//	}
	//	else
	//	{
	//		if (startX > destinationX)
	//			changeRateX = -abs(startX - destinationX) / abs(startY - destinationY);
	//		else
	//			changeRateX = abs(startX - destinationX) / abs(startY - destinationY);

	//		if (startY > destinationY)
	//			changeRateY = -1;
	//		else
	//			changeRateY = 1;
	//	}

	//	currentX += changeRateX;
	//	currentY += changeRateY;

	//	cout << "change rate: " << changeRateX << endl;

	//	while (currentX != destinationX && currentY != destinationY)
	//	{
	//		if (!m_WorldMatrix[(int)currentX][(int)currentY].passable)
	//		{
	//			if (abs(m_WorldMatrix[(int)currentX][(int)currentY].xPos - _line[0].position.x) < abs(nearestPoint.x - _line[0].position.x))
	//				nearestPoint.x = m_WorldMatrix[(int)currentX][(int)currentY].xPos;
	//			if (abs((m_WorldMatrix[(int)currentX][(int)currentY].xPos + 100) - _line[0].position.x) < abs(nearestPoint.x - _line[0].position.x))
	//				nearestPoint.x = m_WorldMatrix[(int)currentX][(int)currentY].xPos + 100;

	//			if (abs(m_WorldMatrix[(int)currentX][(int)currentY].yPos - _line[0].position.y) < abs(nearestPoint.y - _line[0].position.y))
	//				nearestPoint.y = m_WorldMatrix[(int)currentX][(int)currentY].yPos;
	//			if (abs((m_WorldMatrix[(int)currentX][(int)currentY].yPos + 100) - _line[0].position.y) < abs(nearestPoint.y - _line[0].position.y))
	//				nearestPoint.y = m_WorldMatrix[(int)currentX][(int)currentY].yPos + 100;

	//			return nearestPoint;
	//		}
	//		else
	//		{
	//			currentX += changeRateX;
	//			currentY += changeRateY;
	//		}
	//	}
	//}






	//for (int y = 0; y < m_WorldMatrix[0].size(); y++)
	//{
	//	for (int x = 0; x < m_WorldMatrix.size(); x++)
	//	{
	//		if (!m_WorldMatrix[x][y].passable)
	//		{
	//			if (_line.getBounds().intersects(FloatRect(m_WorldMatrix[x][y].xPos, m_WorldMatrix[x][y].yPos, 100, 100)))
	//			{
	//				if (abs(m_WorldMatrix[x][y].xPos - _line[0].position.x) < abs(nearestPoint.x - _line[0].position.x))
	//					nearestPoint.x = m_WorldMatrix[x][y].xPos;
	//				if (abs((m_WorldMatrix[x][y].xPos + 100) - _line[0].position.x) < abs(nearestPoint.x - _line[0].position.x))
	//					nearestPoint.x = m_WorldMatrix[x][y].xPos + 100;

	//				if (abs(m_WorldMatrix[x][y].yPos - _line[0].position.y) < abs(nearestPoint.y - _line[0].position.y))
	//					nearestPoint.y = m_WorldMatrix[x][y].yPos;
	//				if (abs((m_WorldMatrix[x][y].yPos + 100) - _line[0].position.y) < abs(nearestPoint.y - _line[0].position.y))
	//					nearestPoint.y = m_WorldMatrix[x][y].yPos + 100;
	//			}
	//		}

	//	}
	//}




	return _secondPoint.position;
}