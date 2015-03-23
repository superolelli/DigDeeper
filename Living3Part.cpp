#include "Living3Part.hpp"




CLiving3Part::CLiving3Part()
{
	m_pBody = NULL;
	m_pArm = NULL;
	m_pLegs = NULL;
}



CLiving3Part::~CLiving3Part()
{
	SAFE_DELETE(m_pBody);
	SAFE_DELETE(m_pArm);
	SAFE_DELETE(m_pLegs);
}


//Loads the textures
void CLiving3Part::Load(Texture *_body, int _bodyFrameWidth, int _bodyFrameHeight, int _bodyFrameNumber, int _bodyLeftFrame, Texture *_arm, int _armFrameWidth, int _armFrameHeight, int _armFrameNumber, Texture *_legs, int _legsFrameWidth, int _legsFrameHeight, int _legsFrameNumber, int _xPos, int _yPos)
{
	m_pBody = new CSprite;
	m_pBody->Load(_body, _bodyFrameNumber, _bodyFrameWidth, _bodyFrameHeight);
	m_pBody->SetPos(_xPos, _yPos);

	m_pArm = new CSprite;
	m_pArm->Load(_arm, _bodyFrameNumber, _armFrameWidth, _armFrameHeight);

	m_pLegs = new CSprite;
	m_pLegs->Load(_legs, _legsFrameNumber, _legsFrameWidth, _legsFrameHeight);

	m_BodyLeftFrame = _bodyLeftFrame;
	m_LastBodyFrame = _bodyLeftFrame;

	m_Rect.left = _xPos;
	m_Rect.top = _yPos;

	m_RotatingAngleLeft = 0;
}


void CLiving3Part::LoadNewBody(CSprite *_body)
{
	int xPos = m_pBody->GetRect().left;
	int yPos = m_pBody->GetRect().top;

	m_pBody = NULL;

	m_pBody = _body;
	m_pBody->SetPos(xPos, yPos);
}


void CLiving3Part::LoadNewBody(Texture *_body, int _frameWidth, int _frameHeight, int _frameNumber)
{
	int xPos = m_pBody->GetRect().left;
	int yPos = m_pBody->GetRect().top;

	m_pBody = new CSprite;
	m_pBody->Load(_body, _frameNumber, _frameWidth, _frameHeight);
	m_pBody->SetPos(xPos, yPos);
}



void CLiving3Part::LoadNewLegs(CSprite *_legs)
{
	int xPos = m_pLegs->GetRect().left;
	int yPos = m_pLegs->GetRect().top;

	m_pLegs = NULL;

	m_pLegs = _legs;
	m_pLegs->SetPos(xPos, yPos);
}



void CLiving3Part::LoadNewLegs(Texture *_legs, int _frameWidth, int _frameHeight, int _frameNumber)
{
	int xPos = m_pLegs->GetRect().left;
	int yPos = m_pLegs->GetRect().top;

	m_pLegs = new CSprite;
	m_pLegs->Load(_legs, _frameNumber, _frameWidth, _frameHeight);
	m_pLegs->SetPos(xPos, yPos);
}


//Sets the relative Position of the arms and legs for the left side
void CLiving3Part::SetPartsPos(float _armXLeft, float _armXRight, float _armY, float _legsXLeft, float _legsXRight, float _legsY)
{
	m_ArmXLeft = _armXLeft;
	m_ArmXRight = _armXRight;
	m_LegsXLeft = _legsXLeft;
	m_LegsXRight = _legsXRight;

	m_pArm->SetPos(m_pBody->GetRect().left + _armXLeft, m_pBody->GetRect().top + _armY);
	m_pLegs->SetPos(m_pBody->GetRect().left + _legsXLeft, m_pBody->GetRect().top + _legsY);

	m_Rect.width = m_pBody->GetRect().width;
	m_Rect.height =  m_pLegs->GetRect().top + m_pLegs->GetRect().height - m_pBody->GetRect().top;
}


//Sets the position of the main part (body)
void CLiving3Part::SetPos(float _x, float _y)
{
	int oldX, oldY;

	oldX = m_pBody->GetRect().left;
	oldY = m_pBody->GetRect().top;

	m_pBody->SetPos(_x, _y);
	m_pArm->Move((float)(m_pBody->GetRect().left - oldX), (float)(m_pBody->GetRect().top - oldY));
	m_pLegs->Move((float)(m_pBody->GetRect().left - oldX), (float)(m_pBody->GetRect().top - oldY));

	m_Rect.left = (int)_x;
	m_Rect.top = (int)_y;
}


IntRect CLiving3Part::GetRect()
{
	return m_Rect;
}


//Moves the living thing
void CLiving3Part::Move(float _x, float _y)
{
	m_pBody->Move(_x, _y);
	m_pArm->Move(_x, _y);
	m_pLegs->Move(_x, _y);

	m_Rect.left = m_pBody->GetRect().left;
	m_Rect.top = m_pBody->GetRect().top;
}




//renders the living thing
void CLiving3Part::Render(float _bodyFrame,  float _legsFrame)
{
	//if the direction has changed
	if(m_LastBodyFrame <= m_BodyLeftFrame && _bodyFrame > m_BodyLeftFrame || m_LastBodyFrame > m_BodyLeftFrame && _bodyFrame <= m_BodyLeftFrame)
	{
		//change the part's position
		//if it is left sided
		if(_bodyFrame <= m_BodyLeftFrame)
		{
			m_pArm->SetPos((int)(m_pBody->GetRect().left + m_ArmXLeft), m_pArm->GetRect().top);
			m_pLegs->SetPos((int)(m_pBody->GetRect().left + m_LegsXLeft), m_pLegs->GetRect().top);
			m_pArm->setRotatingPoint(m_ArmXOriginLeft, m_ArmYOriginLeft);
		}
		else
		{
			m_pArm->SetPos((int)(m_pBody->GetRect().left + m_ArmXRight), m_pArm->GetRect().top);
			m_pLegs->SetPos((int)(m_pBody->GetRect().left + m_LegsXRight), m_pLegs->GetRect().top);
			m_pArm->setRotatingPoint(m_pArm->GetRect().width - m_ArmXOriginLeft, m_ArmYOriginLeft);			
		}
	}

	if(_bodyFrame <= m_BodyLeftFrame)
		m_pArm->setRotation(m_RotatingAngleLeft);
	else
		m_pArm->setRotation(-m_RotatingAngleLeft);


	//render the living 
	    m_pLegs->Render(g_pFramework->GetWindow(), _legsFrame);
		m_pBody->Render(g_pFramework->GetWindow(), _bodyFrame);
	//	m_pArm->Render(g_pFramework->GetWindow(), _armFrame);		

		//the current frame becomes the last frame
		m_LastBodyFrame = (int)_bodyFrame;

		
}


//Renders the arm
void CLiving3Part::RenderSecondPart(int _frame)
{
	m_pArm->Render(g_pFramework->GetWindow(), (float)(_frame));
}



//sets the arm's rotating point
void CLiving3Part::SetArmRotatingPoint(float _x, float _y)
{
	m_pArm->setRotatingPoint(_x, _y);
	m_ArmXOriginLeft = _x;
	m_ArmYOriginLeft = _y;
	SetPartsPos(m_ArmXLeft + _x, m_ArmXRight + ((float)(m_pArm->GetRect().width) - _x), (float)(m_pArm->GetRect().top - m_pBody->GetRect().top) + _y, m_LegsXLeft, m_LegsXRight, (float)(m_pLegs->GetRect().top - m_pBody->GetRect().top));
}


//rotates the arm
void CLiving3Part::RotateArm(float _angle)
{
	m_RotatingAngleLeft = _angle;
}


//sets the arm's rotation to zero
void CLiving3Part::ResetArmRotation()
{
	m_pArm->resetRotation();
	m_RotatingAngleLeft = 0;
}


//returns the position of the hand
Vector2i CLiving3Part::GetHandPos(bool _left)
{
	Vector2i handPos;
	Vector2f vec;
	float radius;
	
	double angle;
	
	//if object is leftsided
	if(_left)
	{
		vec = Vector2f(m_ArmXOriginLeft, m_ArmYOriginLeft) - Vector2f(m_HandXLeft, m_HandYLeft);                                           //gets the vector that is equal to the radius
		radius = sqrt(vec.x* vec.x + vec.y * vec.y);                                                                                       //calculates the vector's length (= radius)
		angle = -(180 - m_RotatingAngleLeft)*(3.1415926535/180) - atan((m_HandYLeft - m_ArmYOriginLeft) / (m_ArmXOriginLeft - m_HandXLeft));  //gets the rotating angle
	
		handPos.x = (int)(m_pArm->GetRect().left + radius*cos(angle));
		handPos.y = (int)(m_pArm->GetRect().top + radius*sin(angle));
}
	else
	{
		angle = -(m_RotatingAngleLeft)*3.1415926535/180 + atan((m_HandYLeft - m_ArmYOriginLeft) / (m_ArmXOriginLeft - m_HandXLeft));
		vec = Vector2f(m_ArmXOriginLeft, m_ArmYOriginLeft) - Vector2f(m_HandXLeft, m_HandYLeft); 
		radius = sqrt(vec.x* vec.x + vec.y * vec.y);

		handPos.x = (int)(m_pArm->GetRect().left + radius*cos(angle));
		handPos.y = (int)(m_pArm->GetRect().top + radius*sin(angle));
	}

	return handPos;
}