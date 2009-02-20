/*
* File name   : MethodWrapper.h
*
* Copyright (c) 2009 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2009-02-19  Egor Pushkin        Initial version
*/

#ifndef METHODWRAPPER_H__MINCOM__INCLUDED_
#define METHODWRAPPER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/** 
	 * Universal method wrapper. 
	 * You have to derive your own wrapper for user convenience.
	 * What you have to do is to specify correct result types and
	 * override constructor specifying member functions explicitly. 
	 *
	 * Note: This tool is compatible with classes and MinCOM objects
	 * wrapped into mc::Strong as well. 
	 *
	 * Caution: This tool adds certain performance overhead due to 
	 * the specificity of Loki::Functor implementation. So take it 
	 * in into account when estimating performance issues.
	 */
	template
	<
		class LockResultType = result,
		class UnlockResultType = result
	>
	class MethodWrapper
	{
	public:

		template 
		<
			class LockerClass,
			class MemberFn
		>
		MethodWrapper(const LockerClass& object, MemberFn lockFn, MemberFn unlockFn)
			: lock_( object, lockFn )
			, unlock_( object, unlockFn )
		{
			lock_();
		}

		~MethodWrapper()
		{
			unlock_();
		}

	private:

		Loki::Functor< LockResultType > lock_;
		Loki::Functor< UnlockResultType > unlock_;

	private:

		MethodWrapper( const MethodWrapper & );
		MethodWrapper & operator = ( const MethodWrapper & );

	};

}

#endif // !METHODWRAPPER_H__MINCOM__INCLUDED_
