#ifndef IINVOKEMSG_H__REMOTING__CORELIB__INCLUDED_
#define IINVOKEMSG_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	interface IInvokeMsg : public mc::ICommon
	{

		virtual void SetParams(mc::DispParamsRef dispParams) = 0;

		virtual mc::DispParamsPtr GetParams() = 0;

	};

	typedef mc::ComPtr< IInvokeMsg > IInvokeMsgPtr;
	typedef const IInvokeMsgPtr& IInvokeMsgRef;

	// {8c4bd39e-4f70-4a0e-8fb3-c68c7c82d17f} 
	MC_DEFINE_GUID(IID_IInvokeMsg, 
	0x8c4bd39e, 0x4f70, 0x4a0e, 0x8f, 0xb3, 0xc6, 0x8c, 0x7c, 0x82, 0xd1, 0x7f);

}

#endif // !IINVOKEMSG_H__REMOTING__CORELIB__INCLUDED_
