#ifndef KEYSTATES_HPP
#define KEYSTATES_HPP



struct KeyStates
{
	bool leftMouseDown;
	bool leftMouseUp;
	bool rightMouseDown;
	bool escapeDown;
	bool eUp;
	bool bUp;
	bool cUp;
	bool add;
	bool subtract;
	bool backspace;
	bool f3;

	bool text_entered;
	char text_input;

	int mouseWheelMovement;
};




#endif