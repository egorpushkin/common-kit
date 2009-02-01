/*
 * File name   : CommonHolder.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef COMMONHOLDER_H__MINCOM__INCLUDED_
#define COMMONHOLDER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Tool to hold ICommon based object in Loki::Singletone.
	 */
	template
	<
		class T
	>
	class CommonHolder 
	{
		/**
		 * Internal singleton definition.
		 *
		 * Use 'Loki::DeletableSingleton< mc::CommonHolder< T > >::GracefulDelete();' statement
		 * to remove singleton at any time. See Loki documentation and the source code
		 * for more details on consequences of this action.
		 */
		typedef Loki::SingletonHolder< CommonHolder< T >, Loki::CreateUsingNew, Loki::DeletableSingleton > Holder_;		

	public:

		CommonHolder()
			: containee_( Class< T >::Create() )
		{
		}

		static ICommonPtr Instance()
		{
			return Holder_::Instance().GetContained();
		}

	protected:

		void NullInstance()
		{
			containee_ = NULL;
		}

		ICommonPtr GetContained()
		{
			return containee_;
		}

	private:

		ICommonPtr containee_;

	};

}

#endif // !COMMONHOLDER_H__MINCOM__INCLUDED_
