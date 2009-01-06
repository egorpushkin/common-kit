#ifndef FACTORYIMPL_H__MINCOM__COMMONKIT__INCLUDED_
#define FACTORYIMPL_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class FactoryImpl 
		: public CommonImpl< IFactory >
	{
	public:

		FactoryImpl();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IFactory section
		virtual ICommonPtr Create(DispId id);

		virtual result Register(DispId id, FactoryCreator creator);

		virtual result Unregister(DispId id);

		virtual bool IsSupported(DispId id);

	private:

		typedef std::pair< DispId, FactoryCreator > CreatorPair_;

		typedef std::map< CreatorPair_::first_type, CreatorPair_::second_type > CreatorsMap_;

		typedef CreatorsMap_::const_iterator CreatorsCIter_;

		CreatorsMap_ creators_;

	};

}

#endif // !FACTORYIMPL_H__MINCOM__COMMONKIT__INCLUDED_
