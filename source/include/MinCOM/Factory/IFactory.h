/*
 * File name   : IFactory.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef IFACTORY_H__MINCOM__INCLUDED_
#define IFACTORY_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface IFactory : public ICommon
	{

		typedef ICommonPtr (*Creator_)();

		typedef Guid Key_;
		typedef const Key_& KeyRef_;

		virtual ICommonPtr Create(KeyRef_ id) = 0;

		virtual result Register(KeyRef_ id, Creator_ creator) = 0;

		virtual result Unregister(KeyRef_ id) = 0;

		virtual bool IsSupported(KeyRef_ id) = 0;

	};

	typedef Strong< IFactory > IFactoryPtr;
	typedef const IFactoryPtr& IFactoryRef;

}

#endif // !IFACTORY_H__MINCOM__INCLUDED_
