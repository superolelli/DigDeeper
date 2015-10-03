#ifndef OBSERVER_HPP
#define OBSERVER_HPP



class CObserver
{
public:

	virtual void onNotify(int _subject, int _action, int _object) = 0;
};


#endif