#ifndef IAGENT_H__MINCOM__COMMONKIT__INCLUDED_
#define IAGENT_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	typedef enum tagAgentIds
	{

		AGENTID_DEFAULT = 0x00000001

	} AgentIds;

	// {9a28cb29-254b-41cc-8a1b-5693e51ba485} 
	MC_DEFINE_GUID(IID_IAgent, 
	0x9a28cb29, 0x254b, 0x41cc, 0x8a, 0x1b, 0x56, 0x93, 0xe5, 0x1b, 0xa4, 0x85);

	interface IAgent : public ICommon
	{

		virtual result GetTypeInfoCount(
			unsigned int& infoCount) = 0;
		
		virtual result GetTypeInfo(
			unsigned int info, 
			LcId id, 
			ITypeInfoPtr& typeInfo) = 0;

		virtual result GetIDsOfNames(
			RefIid riid, 
			//StringArRef names,
			unsigned int countNames, 
			unsigned long locale, 
			DispIdArRef ids) = 0; 
		
		virtual result Invoke(
			DispId idMember = AGENTID_DEFAULT, 
			DispParamsRef dispParams = NULL,
			IVariantWrapperRef result = NULL,
			RefIid iid = IID_IAgent) = 0;

	};

	typedef ComPtr< IAgent > IAgentPtr;
	typedef ComPtr< IAgent, false > IAgentWeak;

	typedef const IAgentPtr& IAgentRef;

	template
	<
		class T
	>
	IAgentPtr InstantiateAgent()
	{
		return IAgentPtr(ObjectCreator< T >(), IID_IAgent);
	}	

}

#endif // !IAGENT_H__MINCOM__COMMONKIT__INCLUDED_
