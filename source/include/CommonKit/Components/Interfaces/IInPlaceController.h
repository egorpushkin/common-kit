#ifndef IINPLACECONTROLLER_H__COMPONENTS__COMMONKIT__INCLUDED_
#define IINPLACECONTROLLER_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	interface IInPlaceController : public mc::ICommon
	{

		virtual mc::result SendUnloadRequest() = 0;
		
	};

	typedef mc::ComPtr< IInPlaceController > IInPlaceControllerPtr;
	typedef const IInPlaceControllerPtr& IInPlaceControllerRef;

	// {1fadca1b-1853-4449-883c-e977e50cad61} 
	MC_DEFINE_GUID(IID_IInPlaceController, 
	0x1fadca1b, 0x1853, 0x4449, 0x88, 0x3c, 0xe9, 0x77, 0xe5, 0x0c, 0xad, 0x61);

}

#endif // !IINPLACECONTROLLER_H__COMPONENTS__COMMONKIT__INCLUDED_
