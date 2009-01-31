#ifndef CONCURRENT_WIN32_H__MINCOM__INCLUDED_
#define CONCURRENT_WIN32_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class ConcurrentWin32
	{
	public:

		/**
		 * Convenience tool. 
		 *
		 * Problem: This function was not inlined because this causes 
		 * 'Compiler Warning (level 1) C4506' in Visual C++ 2005 SP1.
		 */
		/* inline */ static result Wait(HANDLE object, unsigned long delay);

	};

}

#endif // !CONCURRENT_WIN32_H__MINCOM__INCLUDED_
