/*
* File name   : Object.h
*
* Copyright (c) 2009 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2009-02-02  Egor Pushkin        Initial version
*/

#ifndef OBJECT_H__MINCOM__INCLUDED_
#define OBJECT_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Provides unified tool to instantiate shared or remote MinCOM objects.
	 */ 
	class Object
	{
	public:

		/**
		 * Common tool to create locally registred object and instantiate 
		 * shared component.
		 */ 
		static Strong<ICommon> Create(RefClsid clsid);

		/**
		 * Creates and configures intermediate object on the ID.
		 */
		static ICommonPtr CreateStub(RefIid clsid, ICommonRef target, bool strong);

	};

}

#endif // !OBJECT_H__MINCOM__INCLUDED_
