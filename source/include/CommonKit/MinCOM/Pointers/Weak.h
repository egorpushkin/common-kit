/*
 * File name   : Weak.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-09  Egor Pushkin        Initial version
 */

#ifndef WEAK_H__MINCOM__INCLUDED_
#define WEAK_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 *
	 */
	template
	<
		/**
		 * Class used to specialize Strong template must support IReferenceCounter
		 * interface. In other words it must contain prototypes of these functions
		 * in its declaration;
		 *		virtual unsigned long IncrementReference() = 0;
		 *		virtual unsigned long DecrementReference() = 0;
		 */ 
		typename T
	>
	class Weak
	{
	// Constructors and destructors
	public:


	};

}

#endif // !WEAK_H__MINCOM__INCLUDED_