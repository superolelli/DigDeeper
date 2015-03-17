#ifndef LIVIN3PART_HPP
#define LIVING3PART_HPP

#include <math.h>
#include "Sprite.hpp"
#include "Framework.hpp"



class CLiving3Part
{
public:
	CLiving3Part();
	~CLiving3Part();

	//Loads a new Living 3 Part
	void Load(Texture *_body, int _bodyFrameWidth, int _bodyFrameHeight, int _bodyFrameNumber, int _bodyLeftFrame, Texture *_arm, int _armFrameWidth, int _armFrameHeight, int _armFrameNumber, Texture *_legs, int _legsFrameWidth, int _legsFrameHeight, int _legsFrameNumber, int _xPos, int _yPos);
	
	//Loads a new body
	void LoadNewBody(CSprite *_body);

	//Loads the old body
	void LoadNewBody(Texture *_body, int _frameWidth, int _frameHeight, int _frameNumber);

	//Loads new legs
	void LoadNewLegs(CSprite *_legs);

	//loads the old legs
	void LoadNewLegs(Texture *_legs, int _legsFrameWidth, int _legsFrameHeight, int _legsFrameNumber);

	void Render(float _bodyFrame, float _legsFrame);
	void RenderSecondPart(int _frame);
	void SetPos(float _x, float _y);
	void Move(float _x, float _y);
	void SetPartsPos(float _armXLeft, float _armXRight, float _armY, float _legsXLeft, float _legsXRight, float _legsY);
	void SetArmRotatingPoint(float _x, float _y);
	void SetHandPosition(float _x, float _y) {m_HandXLeft = _x; m_HandYLeft = _y;}
	void RotateArm(float _angle);
	void ResetArmRotation();

	IntRect GetRect();
	Vector2i GetHandPos(bool _left);

private:
	CSprite *m_pBody;               //the body sprite
	CSprite *m_pArm;                //the arm sprite
	CSprite *m_pLegs;               //the leg sprite

	int m_BodyLeftFrame;             //the normal left frame of the body
	int m_LastBodyFrame;             //the last body frame

	float m_ArmXLeft, m_ArmXRight;            //the x Position of the arm relative to the body 
	float m_LegsXLeft, m_LegsXRight;             //the x Position of the legs relative to the body
	float m_ArmXOriginLeft, m_ArmYOriginLeft;          //the rotating point of the arm
	float m_HandXLeft, m_HandYLeft;                      //the point on the arm, where the living should hold things
	float m_RotatingAngleLeft;                                //the rotated angle

	IntRect m_Rect;


};





#endif