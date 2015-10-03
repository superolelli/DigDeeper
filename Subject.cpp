#include "Subject.hpp"




void CSubject::RemoveObserver(CObserver *_observer)
{
	list<CObserver*>::iterator i;

	for (i = m_observerList.begin(); i != m_observerList.end(); i++)
	{
		if ((*i) == _observer)
		{
			i = m_observerList.erase(i);
			return;
		}
	}
}




void CSubject::notify(int _subject, int _action, int _object)
{
	list<CObserver*>::iterator i;

	for (i = m_observerList.begin(); i != m_observerList.end(); i++)
	{
		(*i)->onNotify(_subject, _action, _object);
	}
}