#ifndef PROXYSTUB_H__MINCOM__COMMONKIT__INCLUDED_
#define PROXYSTUB_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class ProxyStubImpl 
		: public CommonImpl< IProxyStub > 
	{
	public:

		ProxyStubImpl();

		// IProxyStub section
		virtual result SetProxyTarget(IAgentRef proxyTarget);

		virtual result SetStubTarget(ICommonRef stubTarget);

		// ICommon section
		DECLARE_INTERFACE_MAP()		

	protected:

		// Protected tools
		virtual IAgentPtr GetProxyTarget() const;

		virtual ICommonPtr GetStubTarget() const;

		virtual PSState GetMode();

	private:

		PSState mode_;

		IAgentPtr proxyTarget_;

		ICommonPtr stubTarget_;

	};

}

#endif // !PROXYSTUB_H__MINCOM__COMMONKIT__INCLUDED_
