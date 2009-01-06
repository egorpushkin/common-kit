#ifndef AGENTTIMPL_H__MINCOM__COMMONKIT__INCLUDED_
#define AGENTTIMPL_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	template 
	< 
		class T 
	>
	class AgentTImpl 
		: public CommonImpl< T >
	{
	public:

		AgentTImpl()
			: CommonImpl< T >()
		{
		}

		// ICommon section
		IMPLACE_INTERFACE_MAP()			
			IMPL(CommonImpl< T >)	
			INTERFACE__(T, IAgent, IID_IAgent)
		END_INTERFACE_MAP()	

		// IAgent section
		virtual result GetTypeInfoCount(
			unsigned int& /* infoCount */)
		{
			return _E_NOTIMPL;
		}
		
		virtual result GetTypeInfo(
			unsigned int /* info */, 
			LcId /* id */, 
			ITypeInfoPtr& /* typeInfo */)
		{
			return _E_NOTIMPL;
		}

		virtual result GetIDsOfNames(
			RefIid /* riid */, 
			//StringArRef /* names */,
			unsigned int /* countNames */, 
			unsigned long /* locale */, 
			DispIdArRef /* ids */)
		{
			return _E_NOTIMPL;
		}
		
		virtual result Invoke(
			DispId /* idMember *//* = AGENTID_DEFAULT */, 
			DispParamsRef /* dispParams *//* = NULL */,
			IVariantWrapperRef /* result *//* = NULL */,
			RefIid /* iid */ = /* IID_IAgent */)
		{
			return _E_NOTIMPL;
		}

	};

}

// #include "AgentTImpl_template.h"

#endif // !AGENTIMPL_H__MINCOM__COMMONKIT__INCLUDED_
