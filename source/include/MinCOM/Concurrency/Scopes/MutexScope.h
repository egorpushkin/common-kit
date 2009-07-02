/*
 * File name   : MutexScope.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-07-02  Egor Pushkin        Initial version
 */

#ifndef MUTEXSCOPE_H__MINCOM__INCLUDED_
#define MUTEXSCOPE_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class MutexScope
	{

		/** Copy-constructor not implemented and denied. */
		MutexScope( const MutexScope & );
        
		/** Copy-assignment operator not implemented and denied. */
		MutexScope & operator = ( const MutexScope & );        
        
	public:

		MutexScope(IMutexRef mutex);
		~MutexScope();

	private:

		IMutexPtr mutex_;

	};

}

#endif // !MUTEXSCOPE_H__MINCOM__INCLUDED_
