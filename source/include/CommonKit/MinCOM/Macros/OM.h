#ifndef OM_H__MINCOM__COMMONKIT__INCLUDED_
#define OM_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	// Defines are visible outside of namespace (at all scopes) 
	// That is why names must be unique

	// Declares map of supported interfaces ( QueryInterface wrapper )
	//////////////////////////////////////////////////////////////////////////
	#define	DECLARE_INTERFACE_MAP()										\
		MinCOM::result QueryInterface(MinCOM::RefIid iid, void** ppObject);

	// Define map
	//////////////////////////////////////////////////////////////////////////
	#define	BEGIN_INTERFACE_MAP(__impl)									\
		MinCOM::result __impl::QueryInterface(MinCOM::RefIid iid, void** ppObject) {	\
		*ppObject = NULL;

	// Define map inplace
	//////////////////////////////////////////////////////////////////////////
	#define	IMPLACE_INTERFACE_MAP()										\
		MinCOM::result QueryInterface(MinCOM::RefIid iid, void** ppObject) {	\
		*ppObject = NULL;

	// Define inplace empty map 
	//////////////////////////////////////////////////////////////////////////
	#define	EMPTY_IMPLACE_MAP()											\
		MinCOM::result QueryInterface(MinCOM::RefIid /* iid */, void** ppObject) {	\
		*ppObject = NULL;												\
		return MinCOM::_E_NOINTERFACE; }

	// Finalize map
	//////////////////////////////////////////////////////////////////////////
	#define	END_INTERFACE_MAP()											\
		*ppObject = NULL;												\
		return MinCOM::_E_NOINTERFACE; }										

	// Process parent impl class
	//////////////////////////////////////////////////////////////////////////
	#define IMPL(__impl)												\
		if ( MinCOM::IsSucceeded(__impl::QueryInterface(iid, ppObject)) )	\
			return MinCOM::_S_OK;

	// Process interface implementation
	//////////////////////////////////////////////////////////////////////////
	#define INTERFACE(__type)											\
	if ( iid == IID_##__type )											\
		{																\
			*ppObject = static_cast< __type* >(this);					\
			MinCOM::CommonImpl< __type >::GetCommon()->AddRef();		\
			return MinCOM::_S_OK;										\
		}

	#define INTERFACE_(__type, __iid)									\
	if ( iid == __iid )													\
		{																\
			*ppObject = static_cast< __type* >(this);					\
			MinCOM::CommonImpl< __type >::GetCommon()->AddRef();		\
			return MinCOM::_S_OK;										\
		}

	#define INTERFACE__(__child, __type, __iid)							\
	if ( iid == __iid )													\
		{																\
			*ppObject = static_cast< __type* >(this);					\
			MinCOM::CommonImpl< __child >::GetCommon()->AddRef();		\
			return MinCOM::_S_OK;										\
		}

	// Process interface implementation
	//////////////////////////////////////////////////////////////////////////
	#define COMMON(__iid)												\
		if ( iid == MinCOM::IID_ICommon )								\
		{																\
			*ppObject = MinCOM::CommonImpl< __iid >::GetCommon();		\
			MinCOM::CommonImpl< __iid >::GetCommon()->AddRef();			\
			return MinCOM::_S_OK;										\
		}

}

#endif // !OM_H__MINCOM__COMMONKIT__INCLUDED_
