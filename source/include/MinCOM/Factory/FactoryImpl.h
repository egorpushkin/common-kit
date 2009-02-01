/*
 * File name   : FactoryImpl.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef FACTORYIMPL_H__MINCOM__INCLUDED_
#define FACTORYIMPL_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class FactoryImpl 
		: public CommonImpl< IFactory >
	{
	public:

		FactoryImpl();

		// IFactory section
		virtual ICommonPtr Create(Key_ id);

		virtual result Register(Key_ id, Creator_ creator);

		virtual result Unregister(Key_ id);

		virtual bool IsSupported(Key_ id);

	private:

		typedef std::pair< Key_, Creator_ > CreatorPair_;

		typedef std::map< CreatorPair_::first_type, CreatorPair_::second_type > CreatorsMap_;

		typedef CreatorsMap_::const_iterator CreatorsCIter_;

		CreatorsMap_ creators_;

	};

}

#endif // !FACTORYIMPL_H__MINCOM__INCLUDED_
