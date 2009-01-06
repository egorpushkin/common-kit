/*
* File name   : MinorPolicies.h
*
* Copyright (c) 2008 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2008-12-29  Egor Pushkin        Initial version based on Loki::StrongPtr.
*/

#ifndef MINORPOLICIES_H__MINCOM__INCLUDED_
#define MINORPOLICIES_H__MINCOM__INCLUDED_

namespace MinCOM
{

	////////////////////////////////////////////////////////////////////////////////
	///  \class DeleteNothing
	///
	///  \ingroup  StrongPointerDeleteGroup 
	///  Implementation of the DeletePolicy used by StrongPtr.  This will never
	///   delete anything.  You can use this policy with pointers to an undefined
	///   type or a pure interface class with a protected destructor.
	////////////////////////////////////////////////////////////////////////////////

	template < class P >
	class DeleteNothing
	{
	public:
		inline static void Delete( const P * )
		{
			// Do nothing at all!
		}

		inline static P * Default( void )
		{
			return 0;
		}

		inline void Swap( DeleteNothing & ) {}
	};

	////////////////////////////////////////////////////////////////////////////////
	///  \struct AllowConversion
	///  
	///  \ingroup  SmartPointerConversionGroup 
	///  Implementation of the ConversionPolicy used by SmartPtr
	///  Allows implicit conversion from SmartPtr to the pointee type
	////////////////////////////////////////////////////////////////////////////////

	struct AllowConversion
	{
		enum { allow = true };

		void Swap(AllowConversion&)
		{}
	};

	////////////////////////////////////////////////////////////////////////////////
	///  \struct DisallowConversion
	///
	///  \ingroup  SmartPointerConversionGroup 
	///  Implementation of the ConversionPolicy used by SmartPtr
	///  Does not allow implicit conversion from SmartPtr to the pointee type
	///  You can initialize a DisallowConversion with an AllowConversion
	////////////////////////////////////////////////////////////////////////////////

	struct DisallowConversion
	{
		DisallowConversion()
		{}

		DisallowConversion(const AllowConversion&)
		{}

		enum { allow = false };

		void Swap(DisallowConversion&)
		{}
	};

	////////////////////////////////////////////////////////////////////////////////
	///  \struct NoCheck
	///
	///  \ingroup  SmartPointerCheckingGroup 
	///  Implementation of the CheckingPolicy used by SmartPtr
	///  Well, it's clear what it does :o)
	////////////////////////////////////////////////////////////////////////////////

	template <class P>
	struct NoCheck
	{
		NoCheck()
		{}

		template <class P1>
		NoCheck(const NoCheck<P1>&)
		{}

		static void OnDefault(const P&)
		{}

		static void OnInit(const P&)
		{}

		static void OnDereference(const P&)
		{}

		static void Swap(NoCheck&)
		{}
	};

	////////////////////////////////////////////////////////////////////////////////
	///  \struct AssertCheck
	///
	///  \ingroup  SmartPointerCheckingGroup 
	///  Implementation of the CheckingPolicy used by SmartPtr
	///  Checks the pointer before dereference
	////////////////////////////////////////////////////////////////////////////////

	template <class P>
	struct AssertCheck
	{
		AssertCheck()
		{}

		template <class P1>
		AssertCheck(const AssertCheck<P1>&)
		{}

		template <class P1>
		AssertCheck(const NoCheck<P1>&)
		{}

		static void OnDefault(const P&)
		{}

		static void OnInit(const P&)
		{}

		static void OnDereference(P val)
		{ assert(val); (void)val; }

		static void Swap(AssertCheck&)
		{}
	};

	////////////////////////////////////////////////////////////////////////////////
	///  \class DontPropagateConst
	///
	///  \ingroup ConstGroup
	///  Don't propagate constness of pointed or referred object.
	////////////////////////////////////////////////////////////////////////////////

	template< class T >
	struct DontPropagateConst
	{
		typedef T Type;
	};

}

#endif // !MINORPOLICIES_H__MINCOM__INCLUDED_
