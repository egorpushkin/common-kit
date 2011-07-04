/*
* File name   : IIterator.h
*
* Copyright (c) 2009 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2009-02-02  Egor Pushkin        Initial version
*/

#ifndef IPRIVATEITERATOR_H__MINCOM__INCLUDED_
#define IPRIVATEITERATOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Private interface declared to provide access to iterator's internals 
	 * from container code.
	 */ 
	template
	<
		/**
		 * Specifies STD container to be iterated.
		 */
		class TStdContainer,
		/**
		 * Specifies MinCOM container.
		 */
		class TMCContainer
	>
	struct IPrivateIterator : public ICommon
	{
#if defined(_MSC_VER)
    // This prevents from accessing by unauthorized tools.
	private:
#endif
        
		// Only specified container is allowed to use this tool.
#if defined(_MSC_VER)
		friend TMCContainer;
#endif

		/** 
		 * Provides access to raw std iterator.
		 */ 
		virtual typename TStdContainer::iterator& GetStdIterator() = 0;
	};

	/**	. */
	// typedef Strong< IPrivateIterator > IPrivateIteratorPtr;

}

#endif // !IPRIVATEITERATOR_H__MINCOM__INCLUDED_
