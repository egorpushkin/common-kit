#ifndef ITIMER_H__MINCOM__INCLUDED_
#define ITIMER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * 
	 */
	interface ITimer : public ICommon
	{




	};

	typedef ComPtr< IThread > IThreadPtr;
	typedef const IThreadPtr& IThreadRef;

}

#endif // !ITIMER_H__MINCOM__INCLUDED_
