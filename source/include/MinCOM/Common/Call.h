/*
 * File name   : CallData.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-01  Egor Pushkin        Initial version
 */

#ifndef CALL_H__MINCOM__NCLUDED_
#define CALL_H__MINCOM__NCLUDED_

namespace MinCOM
{

	/** 
	 * Trivial container for synchronous call data storage.
	 * Call container was introduced to reduce number of arguments of ICommon->Invoke call.
	 */
	class Call
	{
	public:

		Call();

		Call(RefIid methodIid);

		void SetMethod(RefIid methodIid) const;

		RefIid GetMethod() const;

		Variants& GetArguments() const;

		Variants& GetResults() const;

		// static Variant Make(ICommonRef invoker, RefIid methodId);

		static Variant Make(const Strong< ICommon >& invoker, RefIid methodId, 
		 	const Variant& arg1);

		static Variant Make(const Strong< ICommon >& invoker, RefIid methodId, 
		 	const Variant& arg1, 
		 	const Variant& arg2);

		// static Variant Make(ICommonRef invoker, RefIid methodId, 
		// 	const Variant& arg1, 
		// 	const Variant& arg2, 
		// 	const Variant& arg3);

		// static Variant Make(ICommonRef invoker, RefIid methodId, 
		// 	const Variant& arg1, 
		// 	const Variant& arg2, 
		// 	const Variant& arg3,
		// 	const Variant& arg4);

		// static Variant Make(ICommonRef invoker, RefIid methodId, 
		// 	const Variant& arg1, 
		// 	const Variant& arg2, 
		// 	const Variant& arg3,
		// 	const Variant& arg4,
		// 	const Variant& arg5);

	private:

		static Variant Make(const Strong< ICommon >& invoker, const Call& call);

	private:

		mutable Iid methodIid_; /* = METHODID_DEFAULT, */

		mutable Variants arguments_; /* = Variants() */

		mutable Variants results_; /* = Variants() */

		// Iid iid_; /* = TypeInfo< ICommon >::GetGuid() */

	};

}

#endif // !CALL_H__MINCOM__NCLUDED_
