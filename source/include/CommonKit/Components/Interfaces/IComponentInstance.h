#ifndef ICOMPONENTINSTANCE_H__COMPONENTS__COMMONKIT__INCLUDED_
#define ICOMPONENTINSTANCE_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	interface IComponentInstance : public mc::ICommon
	{
	
		virtual IComponentPtr ExtractComponent() = 0;
		
	};

	typedef mc::ComPtr< IComponentInstance > IComponentInstancePtr;
	typedef const IComponentInstancePtr& IComponentInstanceRef;

	// {0a2b4bc9-4347-41c2-9d2b-e2c6d68484a4} 
	MC_DEFINE_GUID(IID_IComponentInstance, 
	0x0a2b4bc9, 0x4347, 0x41c2, 0x9d, 0x2b, 0xe2, 0xc6, 0xd6, 0x84, 0x84, 0xa4);

}

#endif // !ICOMPONENTINSTANCE_H__COMPONENTS__COMMONKIT__INCLUDED_
