/*
 * File name   : CallData.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef CALLDATA_H__MINCOM__NCLUDED_
#define CALLDATA_H__MINCOM__NCLUDED_

namespace MinCOM
{

	/** 
	 * Trivial container for synchronous call data storage.
	 * CallData was introduced to reduce number of arguments of ICommon->Invoke call.
	 */
	class CallData
	{
	public:

		CallData();

		void SetMethod(RefIid methodIid) const;

		RefIid GetMethod() const;

		Variants& GetArguments() const;

		Variants& GetResults() const;

	private:

		mutable Iid methodIid_; /* = METHODID_DEFAULT, */

		mutable Variants arguments_; /* = Variants() */

		mutable Variants results_; /* = Variants() */

		// Iid iid_; /* = TypeInfo< ICommon >::GetGuid() */

	};

}

#endif // !CALLDATA_H__MINCOM__NCLUDED_
