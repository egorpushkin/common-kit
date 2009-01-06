/*
* File name   : Creator.h
*
* Copyright (c) 2008 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2008-12-14  Egor Pushkin        Initial version
*/

#ifndef CREATOR_H__MINCOM__INCLUDED_
#define CREATOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	namespace Private
	{
		ICommon::Ptr_ ObjectCreatorInternal(ICommon::Ref_ common);
	}

	template< class T > 
	ICommon::Ptr_ ObjectCreator() 
	{ 
		return Private::ObjectCreatorInternal(ICommon::Ptr_(new T())); 
	}	

	template< class T, class T1 > 
	ICommon::Ptr_ ObjectCreator(T1 p1) 
	{ 
		return Private::ObjectCreatorInternal(ICommon::Ptr_(new T(p1))); 
	}	

	template< class T, class T1, class T2 > 
	ICommon::Ptr_ ObjectCreator(T1 p1, T2 p2) 
	{ 
		return Private::ObjectCreatorInternal(ICommon::Ptr_(new T(p1, p2))); 
	}	

	template< class T, class T1, class T2, class T3 > 
	ICommon::Ptr_ ObjectCreator(T1 p1, T2 p2, T3 p3) 
	{ 
		return Private::ObjectCreatorInternal(ICommon::Ptr_(new T(p1, p2, p3))); 
	}	

}

#endif // !CREATOR_H__MINCOM__INCLUDED_
