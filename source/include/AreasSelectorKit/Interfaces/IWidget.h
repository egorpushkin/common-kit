#ifndef IWIDGET_H__AREASSELECTOR__INCLUDED_
#define IWIDGET_H__AREASSELECTOR__INCLUDED_

namespace AreasSelector
{

	interface IWidget : public mc::ICommon
	{

		virtual mc::result SetBehaviour(IBehaviourRef behaviour) = 0;

		virtual IBehaviourPtr GetBehaviour() = 0;

	};

	typedef mc::ComPtr< IBehaviour > IBehaviourPtr;
	typedef const IBehaviourPtr& IBehaviourRef;

	// {be73c366-30df-4caa-9bc8-535b374e91ee} 
	MC_DEFINE_GUID(IID_IWidget, 
	0xbe73c366, 0x30df, 0x4caa, 0x9b, 0xc8, 0x53, 0x5b, 0x37, 0x4e, 0x91, 0xee);

}

#endif // !IWIDGET_H__AREASSELECTOR__INCLUDED_
