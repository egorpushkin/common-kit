#ifndef CALLS_H__REMOTING__COMMONKIT__INCLUDED_
#define CALLS_H__REMOTING__COMMONKIT__INCLUDED_

namespace Remoting
{

	class Response;

	typedef Loki::SmartPtr< Response > ResponsePtr;
	typedef const ResponsePtr& ResponseRef;

	class Response
	{
	public:

		friend bool IsFailed(ResponseRef response);

		friend bool IsSucceeded(ResponseRef response);

		Response(mc::IAgentRef remoteObjectAgent, mc::DispId idMember, mc::DispParamsRef params);

		mc::Variant& GetRetVal();

	private:

		mc::result code_;

		mc::IVariantWrapperPtr retVal_;

	};

	bool IsFailed(ResponseRef response);

	bool IsSucceeded(ResponseRef response);

	template
	<
		class T
	>
	ResponsePtr CallSync(const mc::ComPtr< T >& remoteObject, mc::DispId idMember)
	{
		return ResponsePtr(new Response(
			mc::IAgentPtr(remoteObject, mc::IID_IAgent), 
			idMember,
			mc::CreateParams()
		));
	}

	template
	<
		class T, typename T1
	>
	ResponsePtr CallSync(const mc::ComPtr< T >& remoteObject, mc::DispId idMember, T1 p1)
	{
		return ResponsePtr(new Response(
			mc::IAgentPtr(remoteObject, mc::IID_IAgent), 
			idMember,
			mc::CreateParams(
				p1
			)
		));
	}

	template
	<
		class T, typename T1, typename T2
	>
	ResponsePtr CallSync(const mc::ComPtr< T >& remoteObject, mc::DispId idMember, T1 p1, T2 p2)
	{
		return ResponsePtr(new Response(
			mc::IAgentPtr(remoteObject, mc::IID_IAgent), 
			idMember,
			mc::CreateParams(
				p1, p2
			)
		));
	}

	template
	<
		class T, typename T1, typename T2, typename T3
	>
	ResponsePtr CallSync(const mc::ComPtr< T >& remoteObject, mc::DispId idMember, T1 p1, T2 p2, T3 p3)
	{
		return ResponsePtr(new Response(
			mc::IAgentPtr(remoteObject, mc::IID_IAgent), 
			idMember,
			mc::CreateParams(
				p1, p2, p3
			)
		));
	}

}

namespace MinCOM
{
	
	bool IsFailed(Remoting::ResponseRef response);
	bool IsSucceeded(Remoting::ResponseRef response);

}

#endif // !CALLS_H__REMOTING__COMMONKIT__INCLUDED_
