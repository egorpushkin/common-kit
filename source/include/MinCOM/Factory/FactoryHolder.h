/*
 * File name   : FactoryHolder.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef FACTORYHOLDER_H__MINCOM__INCLUDED_
#define FACTORYHOLDER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Tool to provide access to local registry of objects which can
	 * be instantiated. 
	 */
	class FactoryHolder :
		public CommonHolder< FactoryImpl >
	{	
	public:
		/**
		 * Registers all localy defined MinCOM classes.
		 */
		FactoryHolder();

		/**
		 * Provides convenient access to contained object.
		 */
		static IFactoryPtr Instance();
	};

}

#endif // !FACTORYHOLDER_H__MINCOM__INCLUDED_
