#ifndef IFACTORY_H__MINCOM__COMMONKIT__INCLUDED_
#define IFACTORY_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	interface IFactory : public ICommon
	{
		
		typedef ICommonPtr (*FactoryCreator)();

		virtual ICommonPtr Create(DispId id) = 0;

		virtual result Register(DispId id, FactoryCreator creator) = 0;

		virtual result Unregister(DispId id) = 0;

		virtual bool IsSupported(DispId id) = 0;

	};

	typedef ComPtr< IFactory > IFactoryPtr;
	typedef const IFactoryPtr& IFactoryRef;

	// {210dd592-1d09-475e-9c4a-9f14ed0147fd} 
	MC_DEFINE_GUID(IID_IFactory, 
	0x210dd592, 0x1d09, 0x475e, 0x9c, 0x4a, 0x9f, 0x14, 0xed, 0x01, 0x47, 0xfd);

	IFactoryPtr InstantiateFactory();

}

#endif // !IFACTORY_H__MINCOM__COMMONKIT__INCLUDED_
