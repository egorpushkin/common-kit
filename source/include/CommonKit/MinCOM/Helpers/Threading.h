#ifndef THREADING_H__HELPERS__MINCOM__COMMONKIT__INCLUDED_
#define THREADING_H__HELPERS__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class EventLock
	{
	public:

		EventLock(IEventRef event);

		~EventLock();

	private:

		ISynchroPtr synchro_;

	};

	class MutexLock
	{
	public:

		MutexLock(IMutexRef mutex);

		~MutexLock();

	private:

		IMutexPtr mutex_;

	};

}

#endif // !THREADING_H__HELPERS__MINCOM__COMMONKIT__INCLUDED_

