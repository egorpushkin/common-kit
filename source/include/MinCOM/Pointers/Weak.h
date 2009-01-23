/*
 * File name   : Weak.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-09  Egor Pushkin        Initial version
 */

#ifndef WEAK_H__MINCOM__INCLUDED_
#define WEAK_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * 
	 */
	template
	<
		/**
		 * 
		 */ 
		typename T
	>
	class Weak
	{
	// Constructors and destructors.
	public:

		/**
		 * Default constructor. Provides a way to declare uninitialized pointer. 
		 */
		Weak()
			: p_(NULL)
			, refCounter_(NULL)
		{
			// Initialize reference counter.
			InitCounter();
		}		

		/**
		 * Provides a way to construct weak pointer from strong one.
		 */
		Weak( const Strong< T > & rhs )
			: p_(NULL)
			, refCounter_(NULL)
		{
			// Check whether input pointer is initialized correctly.
			if ( rhs )
			{
				// Init internal pointer only if casting succeeded.
				p_ = rhs.p_;
				// Initialize reference counter.
				refCounter_ = rhs.refCounter_;
				refCounter_->IncWeakCount();				
			}
			else
			{
				// Initialize reference counter.
				InitCounter();
			}
		}	

		/**
		 * Copy constructor implementation.
		 */
		Weak( const Weak & rhs )
			: p_(rhs.p_)
			, refCounter_(rhs.refCounter_)
		{
			// Increment external reference counter.
			refCounter_->IncWeakCount();
		}

		/** 
		 * Destructor provided to maintain (decrement) references to 
		 * contained object. 
		 */
		~Weak()
		{
			// Decrement a number of external references to the object.
			refCounter_->DecWeakCount();

			// If the last one strong reference has just been destroyed.
			if ( !refCounter_->HasWeakPointer() )
			{
				// Destroy counter object if necessary.
				ReleaseCounter();
			}
		}


	// Comparison operators
	public:

		// Enables 'if ( !sp ) ...'
		inline bool operator ! () const 
		{
			return ( ( 0 == p_ ) || ( !refCounter_->HasStrongPointer() ) );
		}

	// Assignment operators
	public:

		Weak & operator = ( const Strong< T > & rhs )
		{
			if ( p_ != rhs.p_ )
			{
				Weak temp( rhs );
				temp.Swap( *this );
			}
			return *this;
		}

	// Operators
	public:

		void Swap( Weak & rhs )
		{
			std::swap( p_, rhs.p_ );
			std::swap( refCounter_, rhs.refCounter_ );
		}

	// Tricks
	private:

		// Helper for enabling 'if ( sp )'
		struct Tester
		{
			Tester(int) {}
			void dummy() {}
		};

		typedef void (Tester::*unspecified_boolean_type)();

	public:

		// Enables 'if ( sp )'
		operator unspecified_boolean_type() const
		{
			return !*this ? 0 : &Tester::dummy;
		}

	private:
		// Helper for disallowing automatic conversion
		struct Insipid
		{
			Insipid(T*) {}
		};

		typedef Insipid AutomaticConversionResult;

	public:        
		operator AutomaticConversionResult() const
		{
			return p_;
		} 

	// Ownership policy tools
	private:

		void InitCounter()
		{
			refCounter_ = new DualRefCounter( false );
		}

		void ReleaseCounter()
		{
			if ( !refCounter_->HasStrongPointer() )
			{
				// Delete counter if there are no strong references to the object.
				delete refCounter_;
				refCounter_ = NULL;
			}
		}

	private:

		// Establish friendship between all specializations of Strong to allow
		// casting between different pointers.
		template< class Y > friend class Strong;
		template< class Y > friend class Weak;

		/** Pointer to contained object. */
		T * p_;

		/** Holds external reference counter. */
		DualRefCounter * refCounter_;

	};

}

#endif // !WEAK_H__MINCOM__INCLUDED_
