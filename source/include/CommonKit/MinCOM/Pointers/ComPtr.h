/*
 * File name   : ICommon.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2008-12-14  Egor Pushkin        Initial version
 */

#ifndef COMPTR_H__MINCOM__INCLUDED_
#define COMPTR_H__MINCOM__INCLUDED_

#include "MinorPolicies.h"
#include "OwnershipPolicy.h"
#include "ResetPolicy.h"

////////////////////////////////////////////////////////////////////////////////
///
///  \par Terminology
///   These terms are used within this file's comments.
///   -# ComPtr : Class used to implement both strong and weak pointers. The
///      second template parameter determines if a ComPtr is weak or strong.
///   -# Strong pointer : A pointer that claims ownership of a shared object.
///      When the last strong copointer dies, the object is destroyed even if
///      there are weak copointers.
///   -# Weak pointer : A pointer that does not own the shared object it points
///       to.  It only destroys the shared object if there no strong copointers
///       exist when it dies.
///   -# Copointers : All the pointers that refer to the same shared object.
///      The copointers must have the same ownership policy, but the other
///      policies may be different.
///   -# Pointee : The shared object.
///
///  \par OwnershipPolicy
///   The ownership policy has the pointer to the actual object, and it also
///   keeps track of the strong and weak copointers so that it can know if any
///   strong copointers remain.  The plain pointer it maintains is stored as a
///   void pointer, which allows the ownership policy classes to be monolithic
///   classes instead of template classes.  As monolithic classes, they reduce
///   amount of code-bloat.
///
///  \par Writing Your Own OwnershipPolicy
///   If you write your own policy, you must implement these 12 functions:
///   -# explicit YourPolicy( bool strong )
///   -# YourPolicy( void * p, bool strong )
///   -# YourPolicy( const YourPolicy & rhs, bool strong )
///   -# bool Release( bool strong )
///   -# void Increment( bool strong )
///   -# bool Decrement( bool strong )
///   -# bool HasStrongPointer( void ) const
///   -# void Swap( YourPolicy & rhs )
///   -# void SetPointer( void * p )
///   -# void ZapPointer( void )
///   -# void * GetPointer( void ) const
///   -# void * & GetPointerRef( void ) const
///   It is strongly recommended that all 12 of these functions be protected
///   instead of public.  These two functions are optional for single-threaded
///   policies, but required for multi-threaded policies:
///   -# void Lock( void ) const
///   -# void Unlock( void ) const
///   This function is entirely optional:
///   -# bool Merge( TwoRefLinks & rhs )
///
///  \par DeletePolicy
///   The delete policy provides a mechanism to destroy an object and a default
///   value for an uninitialized pointer.  You can override this policy with
///   your own when using the Singleton, NullObject, or Prototype design
///   patterns.
///
///  \par Writing Your Own DeletePolicy
///   If you write your own policy, you must implement these 3 functions:
///   -# void static Delete( const P * p )
///   -# static P * Default( void )
///   -# void Swap( YourResetPolicy & )
///
///  \par ResetPolicy
///   A reset policy tells the ReleaseAll and ResetAll functions whether they
///   should release or reset the ComPtr copointers.  These functions do
///   not affect just one ComPtr, but all copointers.  That is unlike
///   SmartPtr where the Release and Reset functions only affect 1 SmartPtr,
///   and leave all copointers untouched.  A useful trick you can do with the
///   ResetPolicy is to not allow reset when a strong pointer exists, and then
///   use the NoCheck policy for all strong pointers.  The reset policy
///   guarantees the strong pointers always have a valid pointee, so checking
///   is not required; but weak pointers may still require checking.
///
///  \par Writing Your Own ResetPolicy
///   If you write your own policy, you must implement these 2 functions:
///   -# bool OnReleaseAll( bool ) const
///   -# bool OnResetAll( bool ) const
///   The bool parameter means that this was called with a strong pointer or
///   one of its copointers is strong.  The return value means the pointer
///   can be reset or released.
///
///  \defgroup  StrongPointerOwnershipGroup ComPtr Ownership policies
///  \ingroup   SmartPointerGroup
///  \defgroup  StrongPointerDeleteGroup Delete policies
///  \ingroup   SmartPointerGroup
///  \defgroup  StrongPointerResetGroup Reset policies
///  \ingroup   SmartPointerGroup
////////////////////////////////////////////////////////////////////////////////

namespace MinCOM
{

	////////////////////////////////////////////////////////////////////////////////
	///  \class ComPtr
	///
	///  \ingroup SmartPointerGroup 
	///
	///  \param Strong           default = true,
	///  \param OwnershipPolicy  default = LockableTwoRefCounts,
	///  \param ConversionPolicy default = DisallowConversion,
	///  \param CheckingPolicy   default = AssertCheck,
	///  \param ResetPolicy      default = CantResetWithStrong,
	///  \param DeletePolicy     default = DeleteNothing,
	///  \param ConstnessPolicy  default = DontPropagateConst
	////////////////////////////////////////////////////////////////////////////////

	template
	<
		typename T,
		bool Strong = true,
		class OwnershipPolicy = LockableTwoRefCounts,
		class ConversionPolicy = DisallowConversion,
		template < class > class CheckingPolicy = AssertCheck,
		template < class > class ResetPolicy = CantResetWithStrong,
		template < class > class DeletePolicy = DeleteNothing,
		template < class > class ConstnessPolicy = DontPropagateConst
	>
	class ComPtr
		: public OwnershipPolicy
		, public ConversionPolicy
		, public CheckingPolicy< T * >
		, public ResetPolicy< T >
		, public DeletePolicy< T >
	{
		typedef ConversionPolicy CP;
		typedef CheckingPolicy< T * > KP;
		typedef ResetPolicy< T > RP;
		typedef DeletePolicy< T > DP;

	public:

		typedef OwnershipPolicy OP;

		typedef T * StoredType;    // the type of the pointer
		typedef T * PointerType;   // type returned by operator->
		typedef T & ReferenceType; // type returned by operator*

		typedef typename ConstnessPolicy< T >::Type * ConstPointerType;
		typedef typename ConstnessPolicy< T >::Type & ConstReferenceType;

	private:
		struct NeverMatched {};

#ifdef LOKI_SMARTPTR_CONVERSION_CONSTRUCTOR_POLICY
		typedef typename Loki::Select< CP::allow, const StoredType&, NeverMatched>::Result ImplicitArg;
		typedef typename Loki::Select<!CP::allow, const StoredType&, NeverMatched>::Result ExplicitArg;
#else
		typedef const StoredType& ImplicitArg;
		typedef typename Loki::Select<false, const StoredType&, NeverMatched>::Result ExplicitArg;
#endif

	public:

		ComPtr( void ) : OP( Strong )
		{
			KP::OnDefault( GetPointer() );
		}

		/*
		explicit ComPtr( ExplicitArg p ) : OP( p, Strong )
		{
			KP::OnInit( GetPointer() );
		}

		ComPtr( ImplicitArg p ) : OP( p, Strong )
		{
			KP::OnInit( GetPointer() );
		}
		*/

		/**
		 * This constructor should present to power assignment operator, etc.
		 */
		ComPtr( const ComPtr & rhs )
			: OP( rhs, Strong ), CP( rhs ), KP( rhs ), DP( rhs )
		{
		}

		/**
		 * Provides a way to init smart pointer with raw pointer to another interface 
		 * of the same object.
		 * MinCOM 0.1.0 enhancement.
		 */
		template
		<
			typename T1
		>
		ComPtr( T1 * p ) 
			: OP( p->Cast<T>(), Strong )
		{
			KP::OnInit( GetPointer() );
		}

	protected:

		// MinCOM 0.1.0 enhancement. 
		template
		<
			typename T1,
			bool Strong1
		>
		const ComPtr< T1, Strong1 > * PointerCast( const ComPtr< T1, Strong1 > & rhs )
		{
			if ( !rhs )
				return NULL;			
			T * p = rhs->Cast<T>();
			if ( !p )
				return NULL;
			if ( !IsStrong() )
				rhs->DecrementReference();
			return &rhs;
		}

	public:

		template
		<
			typename T1,
			bool Strong1
		>
		ComPtr( const ComPtr< T1, Strong1 > & rhs )
			: OP( PointerCast(rhs), Strong )
		{
		}

		template
		<
			typename T1,
			bool Strong1
		>
		ComPtr( ComPtr< T1, Strong1 > & rhs )
			: OP( PointerCast(rhs), Strong )
		{
		}

		template
		<
			bool Strong1
		>
		ComPtr( const ComPtr< T, Strong1 > & rhs )
			: OP( rhs, Strong )
		{
			// MinCOM 0.1.0 enhancement. 
			if ( IsStrong() )
				Private::InternalReferenceCounter::Increment(GetPointer());			
		}

		ComPtr( Loki::RefToValue< ComPtr > rhs )
			: OP( rhs, Strong ), KP( rhs ), CP( rhs ), DP( rhs )
		{
		}

		operator Loki::RefToValue< ComPtr >( void )
		{
			return RefToValue< ComPtr >( *this );
		}

		ComPtr & operator = ( const ComPtr & rhs )
		{
			if ( GetPointer() != rhs.GetPointer() )
			{
				ComPtr temp( rhs );
				temp.Swap( *this );

				// MinCOM 0.1.0 enhancement. 
				if ( IsStrong() )
					Private::InternalReferenceCounter::Increment(GetPointer());
			}
			return *this;
		}

		ComPtr & operator = ( T * p )
		{
			if ( GetPointer() != p )
			{
				ComPtr temp( p );
				Swap( temp );
			}
			return *this;
		}

	private:

		template
		<
			typename T1
		>
		ComPtr & operator = ( T1 * p );

		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		ComPtr & operator = ( const ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & rhs );

	public:

		bool IsStrong( void ) const
		{
			return Strong;
		}

		void Swap( ComPtr & rhs )
		{
			OP::Swap( rhs );
			CP::Swap( rhs );
			KP::Swap( rhs );
			DP::Swap( rhs );
		}

		~ComPtr()
		{
			// This must get pointer before zapping it, and then delete 
			// the temp pointer.
			T * p = GetPointer();

			if ( OP::Release( Strong ) )
			{
				// Must zap the pointer before deleting the object. Otherwise a
				// cycle of weak pointers will lead to recursion, which leads to
				// to deleting the shared object multiple times, which leads to
				// undefined behavior.  
				
				// MinCOM 0.1.0 enhancement. Superfluous check was removed.
				// Pointer should be zapped in any case. This check conduces to 
				// memory leaks in non initialized pointers. 
				
				// if ( p != 0 )
				OP::ZapPointer();
				DP::Delete( p );
			}
			
			bool strong = Strong;
			if ( ( strong ) && ( p ) )
			{
				// Release object's internal counter.
				p->DecrementReference();
			}
		}

		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		friend bool ReleaseAll( ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & sp,
			typename ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 >::StoredType & p );


		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		friend bool ResetAll( ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & sp,
			typename ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 >::StoredType p );

		/** Merges ownership of two ComPtr's that point to same shared object
		but are not copointers.  Requires Merge function in OwnershipPolicy.
		\return True for success, false if not pointer to same object.
		*/
		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		bool Merge( ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & rhs )
		{
			if ( OP::GetPointer() != rhs.OP::GetPointer() )
			{
				return false;
			}
			return OP::Merge( rhs );
		}

		/** Locks ComPtr so other threads can't affect pointer.  Requires the
		OwnershipPolicy to have Lock function.
		*/
		void Lock( void )
		{
			OP::Lock();
		}

		/** Unlocks ComPtr so other threads can affect pointer.  Requires the
		OwnershipPolicy to have Unlock function.
		*/
		void Unlock( void )
		{
			OP::Unlock();
		}

		PointerType operator -> ()
		{
			assert( true == Strong );
			KP::OnDereference( GetPointer() );
			return GetPointer();
		}

		ConstPointerType operator -> () const
		{
			KP::OnDereference( GetPointer() );
			return GetPointer();
		}

		ReferenceType operator * ()
		{
			KP::OnDereference( GetPointer() );
			return * GetPointer();
		}

		ConstReferenceType operator * () const
		{
			KP::OnDereference( GetPointer() );
			return * GetPointer();
		}

		/// Helper function which can be called to avoid exposing GetPointer function.
		template < class T1 >
		bool Equals( const T1 * p ) const
		{
			return ( GetPointer() == p );
		}

		/// Helper function which can be called to avoid exposing GetPointer function.
		template < class T1 >
		bool LessThan( const T1 * p ) const
		{
			return ( GetPointer() < p );
		}

		/// Helper function which can be called to avoid exposing GetPointer function.
		template < class T1 >
		bool GreaterThan( const T1 * p ) const
		{
			return ( GetPointer() > p );
		}

		/// Equality comparison operator is templated to handle ambiguity.
		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
			>
		bool operator == (
			const ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & rhs ) const
		{
			return ( rhs.Equals( GetPointer() ) );
		}

		/// Inequality comparison operator is templated to handle ambiguity.
		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		bool operator != (
			const ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & rhs ) const
		{
			return !( rhs.Equals( GetPointer() ) );
		}

		/// Less-than comparison operator is templated to handle ambiguity.
		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		bool operator < (
			const ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & rhs ) const
		{
			return ( rhs.GreaterThan( GetPointer() ) );
		}

		/// Greater-than comparison operator is templated to handle ambiguity.
		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		inline bool operator > (
			const ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & rhs ) const
		{
			return ( rhs.LessThan( GetPointer() ) );
		}

		/// Less-than-or-equal-to operator is templated to handle ambiguity.
		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		inline bool operator <= (
			const ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & rhs ) const
		{
			return !( rhs.LessThan( GetPointer() ) );
		}

		/// Greater-than-or-equal-to operator is templated to handle ambiguity.
		template
		<
			typename T1,
			bool S1,
			class OP1,
			class CP1,
			template < class > class KP1,
			template < class > class RP1,
			template < class > class DP1,
			template < class > class CNP1
		>
		inline bool operator >= (
			const ComPtr< T1, S1, OP1, CP1, KP1, RP1, DP1, CNP1 > & rhs ) const
		{
			return !( rhs.GreaterThan( GetPointer() ) );
		}

		inline bool operator ! () const // Enables "if ( !sp ) ..."
		{
			return ( 0 == OP::GetPointer() );
		}

	protected:

		inline PointerType GetPointer( void )
		{
			return reinterpret_cast< PointerType >( OP::GetPointer() );
		}

		inline ConstPointerType GetPointer( void ) const
		{
			return reinterpret_cast< ConstPointerType >( OP::GetPointer() );
		}

	private:

		inline ReferenceType GetPointerRef( void )
		{
			return reinterpret_cast< ReferenceType >( OP::GetPointerRef() );
		}

		inline ConstReferenceType GetPointerRef( void ) const
		{
			return reinterpret_cast< ConstReferenceType >( OP::GetPointerRef() );
		}

		// Helper for enabling 'if (sp)'
		struct Tester
		{
			Tester(int) {}
			void dummy() {}
		};

		typedef void (Tester::*unspecified_boolean_type_)();

		typedef typename Loki::Select< CP::allow, Tester, unspecified_boolean_type_ >::Result
			unspecified_boolean_type;

	public:
		// enable 'if (sp)'
		operator unspecified_boolean_type() const
		{
			return !*this ? 0 : &Tester::dummy;
		}

	private:
		// Helper for disallowing automatic conversion
		struct Insipid
		{
			Insipid(PointerType) {}
		};

		typedef typename Loki::Select< CP::allow, PointerType, Insipid >::Result
			AutomaticConversionResult;

	public:        
		operator AutomaticConversionResult() const
		{
			return GetPointer();
		}

	};

	// ----------------------------------------------------------------------------

	// friend functions

	// free comparison operators for class template StrongPtr

	///  operator== for lhs = StrongPtr, rhs = raw pointer
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator == (
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & lhs, U * rhs )
	{
		return ( lhs.Equals( rhs ) );
	}

	///  operator== for lhs = raw pointer, rhs = StrongPtr
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator == ( U * lhs,
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & rhs )
	{
		return ( rhs.Equals( lhs ) );
	}

	///  operator!= for lhs = StrongPtr, rhs = raw pointer
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator != (
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & lhs, U * rhs )
	{
		return !( lhs.Equals( rhs ) );
	}

	///  operator!= for lhs = raw pointer, rhs = StrongPtr
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator != ( U * lhs,
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & rhs )
	{
		return !( rhs.Equals( lhs ) );
	}

	///  operator< for lhs = StrongPtr, rhs = raw pointer
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator < (
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & lhs, U * rhs )
	{
		return ( lhs.LessThan( rhs ) );
	}

	///  operator< for lhs = raw pointer, rhs = StrongPtr
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator < ( U * lhs,
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & rhs )
	{
		return ( rhs.GreaterThan( lhs ) );
	}

	//  operator> for lhs = StrongPtr, rhs = raw pointer
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator > (
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & lhs, U * rhs )
	{
		return ( lhs.GreaterThan( rhs ) );
	}

	///  operator> for lhs = raw pointer, rhs = StrongPtr
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator > ( U * lhs,
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & rhs )
	{
		return ( rhs.LessThan( lhs ) );
	}

	///  operator<= for lhs = StrongPtr, rhs = raw pointer
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator <= (
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & lhs, U * rhs )
	{
		return !( lhs.GreaterThan( rhs ) );
	}

	///  operator<= for lhs = raw pointer, rhs = StrongPtr
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator <= ( U * lhs,
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & rhs )
	{
		return !( rhs.LessThan( lhs ) );
	}

	///  operator>= for lhs = StrongPtr, rhs = raw pointer
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator >= (
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & lhs, U * rhs )
	{
		return !( lhs.LessThan( rhs ) );
	}

	///  operator>= for lhs = raw pointer, rhs = StrongPtr
	///  \ingroup SmartPointerGroup
	template
	<
		typename U,
		typename T,
		bool S,
		class OP,
		class CP,
		template < class > class KP,
		template < class > class RP,
		template < class > class DP,
		template < class > class CNP
	>
	inline bool operator >= ( U * lhs,
		const ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & rhs )
	{
		return !( rhs.GreaterThan( lhs ) );
	}

} // namespace MinCOM

namespace std
{
    ////////////////////////////////////////////////////////////////////////////////
    ///  specialization of std::less for StrongPtr
    ///  \ingroup SmartPointerGroup
    ////////////////////////////////////////////////////////////////////////////////
    template
    <
        typename T,
        bool S,
        class OP,
        class CP,
        template < class > class KP,
        template < class > class RP,
        template < class > class DP,
        template < class > class CNP
    >
    struct less< MinCOM::ComPtr< T, S, OP, CP, KP, RP, DP, CNP > >
        : public binary_function<
            MinCOM::ComPtr< T, S, OP, CP, KP, RP, DP, CNP >,
            MinCOM::ComPtr< T, S, OP, CP, KP, RP, DP, CNP >, bool >
    {
        bool operator () (
            const MinCOM::ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & lhs,
            const MinCOM::ComPtr< T, S, OP, CP, KP, RP, DP, CNP > & rhs ) const
        {
            return ( lhs < rhs );
        }
    };
}

////////////////////////////////////////////////////////////////////////////////

#endif // !COMPTR_H__MINCOM__INCLUDED_
