#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.hpp"
#include <list>

using namespace std;

class CSubject
{
public:

	void AddObserver(CObserver *_observer){ m_observerList.push_back(_observer); }
	void RemoveObserver(CObserver *_observer);

	void notify(int _subject, int _action, int _object);

protected:

	list<CObserver*> m_observerList;

};



#endif