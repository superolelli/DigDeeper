#ifndef LIGHTMACHINE_HPP
#define LIGHTMACHINE_HPP

#include "Framework.hpp"
#include "Structures.hpp"

class CWorld;


class CLightMachine
{
public:
	CLightMachine();
	//Inits the light machine
	void Init(View* _view, CWorld *_world, bool _fastLight);

	//Quits the light machine
	void Quit();

	//clears the light machine with a background colour
	void Clear(Color _color);

	//renders the light
	void Render();

	//adds a lightcircle
	void AddLightCircle(int _x, int _y, int _radius, Color _color);

	//adds a half lightcircle
	//void AddLightHalfCircle(int _x, int _y, int radius, Color _color);


private:

	RenderTexture m_lightTexture;
	View *m_View;
	CWorld *m_pWorld;

	int m_ViewX, m_ViewY;
	int m_ViewLastWidth;                          //the last width of the view
	int m_currentAlpha;

	bool m_fastLight;

	Vector2f IsLineIntersecting(Vertex _firstPoint, Vertex _secondPoint, int _angle, int _radius);               //checks, wether a line intersects with a block


};


#endif