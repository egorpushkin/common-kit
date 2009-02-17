/*
 * File name   : Strong.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-08  Egor Pushkin        Initial version
 */

#ifndef STRONG_H__MINCOM__INCLUDED_
#define STRONG_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Preliminary declaration of weak pointers.
	 */ 
	template
	<
		typename T
	>
	class Weak;

	/**
	 * Preliminary declaration of object model basics.
	 */ 
	interface ICommon;

	/**
	 * Preliminary declaration of default ICommon implementation.
	 */     
    template
	<
        class T
	>
	class CommonImpl;
    
    /**
     * Preliminary declaration of objects instantiator.
     */
    template
    <
        class T
    >
    class Class;

	/**
	 * Strong pointer intended to host pointers to native MinCOM and
	 * inherited control interfaces. Implementation of this helper class 
	 * provides support for MinCOM memory (life-circle) management.
	 *
	 * This class provides external (in relation to an object) reference 
	 * counter.
	 *
	 * Current implementation maintains internal counting in the following way:
	 *  - counter is increased each time, when next external object (strong smart
	 *    pointer), referencing contained object, appears;
	 *  - counter is decreased each time when strong smart pointer is destroyed.
	 * Future: This schema may be changed in the following way. We can only 
	 * refer to internal count twice for the entire hierarchy of smart pointers 
	 * sharing the same DualRefCounter object.
	 * 
	 * Requirements (this implementation should...):
	 *  - be fast;
	 *  - be thread safe;
	 *  - provide debug info (a way to get a number of referrers at run time);
	 */ 
	template
	<
		/**
		 * Class used to specialize Strong template must support IReferenceCounter
		 * interface. In other words it must contain prototypes of these functions
		 * in its declaration;
		 *		virtual unsigned long IncrementReference() = 0;
		 *		virtual unsigned long DecrementReference() = 0;
		 */ 
		typename T
	>
	class Strong
	{
	// Initialization section.
	private:

		/** Establish friendship with creators. */
		template< class Y > friend class mc::Class;

		/**
		 * Provides a way to init smart pointer with raw pointer to object.
		 * Client cannot perform this operation directly as there should be no way
		 * to construct object by means of native 'new' operator.
         * That is why this tool is private. The only tool responsible for
         * Strong pointers initialization is Class template, which builds objects 
         * taking into account all specific MinCOM rules and idioms.
		 */
		template
		<
			/**
 			 * Template parameter must support ICommon interface.
			 */
			typename T1
		>
		Strong( T1 * p1 ) 
			: p_(NULL)
			, refCounter_(NULL)
		{
			// Check whether input parameter is correct.
			if ( NULL != p1 )
			{
				// Try to cast raw pointer to the type of current pointer.
				// T * p = p1->Cast();  
				T * p = dynamic_cast< T* >( dynamic_cast< T1::ClassRoot_* >( p1 ) );  
				if ( p )
				{
					// Init internal pointer only if casting succeeded.
					p_ = p;
					// Increase internal reference counter.
					p_->IncrementReference();
				}	
			}
			// Init smart pointer.
			InitCounter();
		} 
        
	// Constructors and destructors.
	public:
		
		/**
		 * Default constructor. Provides a way to declare uninitialized pointer. 
		 */
		Strong()
			: p_(NULL)
			, refCounter_(NULL)
		{
			// Initialize reference counter.
			InitCounter();
		}

		/**
		 * Enables 'Strong<T> ptr = NULL;' syntax. Always initializes internal pointer to NULL
		 * nomatter what argument is passed. This prevents user from mistakes like:
		 *  Strong<T> ptr((T*)123);
		 *  Strong<T> ptr(new T()); 
		 */
		Strong( T * /* p */ ) 
			: p_(NULL)
			, refCounter_(NULL)
		{
			// Init smart pointer.
			InitCounter();
		}

		/**
		 * Copy constructor implementation.
		 */
		Strong( const Strong & rhs )
			: p_(rhs.p_)
			, refCounter_(rhs.refCounter_)
		{
			// Increment internal object's reference counter 
			if ( p_ )
			{
				p_->IncrementReference();
			}
			// Increment external reference counter
			refCounter_->IncStrongCount();
		}
		
		/**
		 * Provides a way to init smart pointer with another strong smart pointer to 
		 * another interface of the same object.
		 */
		template
		<
			/**
 			 * Template parameter must support ICommon interface.
			 */
			typename T1
		>
		Strong( const Strong< T1 > & rhs ) 
			: p_(NULL)
			, refCounter_(NULL)
		{
			Init(rhs);
		}	

		/**
		 * Provides a way to init smart pointer with another strong smart pointer to 
		 * another interface of the same object.
		 */
		template
		<
			/**
 			 * Template parameter must support ICommon interface.
			 */
			typename T1
		>
		Strong( Strong< T1 > & rhs ) 
			: p_(NULL)
			, refCounter_(NULL)
		{
			Init(rhs);
		}	

		/** 
		 * Destructor provided to maintain (decrement) references to 
		 * contained object. 
		 */
		~Strong()
		{
			// This must get pointer before zapping it, and then perform other 
			// operations over the temp pointer. This should be done to avoid 
			// multiple deleting object. 
			T * p = p_;
			p_ = NULL;

			// Decrement a number of external references to the object.
			refCounter_->DecStrongCount();

			// If the last one strong reference has just been destroyed.
			if ( !refCounter_->HasStrongPointer() )
			{
				// Destroy counter object if necessary.
				ReleaseCounter();
			}

			// Assuming the fact that this class maintains only strong pointers
			// the only thing should be checked is validity of contained pointer.
			if ( NULL != p )
			{
				// Decrement object's internal counter.
				p->DecrementReference();
			}
		}

	// Reconstruction tools
	public:
		
		/**
		 * Provides a way to reconstruct strong pointer from weak one.
		 */
		Strong( const Weak< T > & rhs )
			: p_(rhs.p_)
			, refCounter_(rhs.refCounter_)
		{
			if ( rhs )
			{
				// Increment internal object's reference counter 
				if ( p_ )
				{
					p_->IncrementReference();
				}
				// Increment external reference counter
				refCounter_->IncStrongCount();
			}
			else
			{
				// Clear pointer fields.
				p_ = NULL;
				// Init smart pointer.
				InitCounter();
			}
		}

		/**
		 * Provides a way to reconstruct strong pointer from weak one.
		 */
		Strong & operator = ( const Weak< T > & rhs )
		{
			if ( p_ != rhs.p_ )
			{
				Strong temp( rhs );
				temp.Swap( *this );
			}
			return *this;
		}	

	// Initialization tools
	private:

		/**
		 * Provides a way to init smart pointer with another strong smart pointer to 
		 * another interface of the same object.
		 */
		template
		<
			/**
 			 * Template parameter must support ICommon interface.
			 */
			typename T1
		>
		void Init( const Strong< T1 > & rhs ) 
		{
			// Initialization success flag.
			bool isInitied = false;

			// Check whether input parameter is correct.
			if ( rhs )
			{
				// Try to cast pointer to the type of current pointer.
				T * p = dynamic_cast< T* >( rhs.p_ );
				if ( p )
				{
					// Init pointer only if casting succeeded.
					Init(p, rhs.refCounter_);

					// Indicate operation success.
					isInitied = true;
				}	
				else
				{
					// Try to cast pointer in object specific manner.
					Strong< ICommon > proxy = rhs.p_->Query( TypeInfo< T >::GetGuid() );
					if ( proxy )
					{
						// Try to query target interface from proxy object.
						T * pp = dynamic_cast< T* >( proxy.p_ );
						if ( pp )
						{
							// Init internal pointer only if querying succeeded.
							Init(pp, proxy.refCounter_);
								
							// Indicate on operation success.
							isInitied = true;
						}
					}
				}
			}

			// Check whether initialization procedure succeeded.
			if ( !isInitied )
			{
				// Init smart pointer.
				InitCounter();
			}
		}	

		void Init(T * p, DualRefCounter * refCounter)
		{
			// Initialize reference to object.
			p_ = p;
			p_->IncrementReference();
			// Initialize reference counter.
			refCounter_ = refCounter;
			refCounter_->IncStrongCount();
		}

	// Assignment operators
	public:

		Strong & operator = ( const Strong & rhs )
		{
			if ( p_ != rhs.p_ )
			{
				Strong temp( rhs );
				temp.Swap( *this );
			}
			return *this;
		}
		
	// Operators
	public:

		/**
		 * Provides a way to call methods of contained object via -> operator.
		 */
		/* T * operator -> ()
		{
			if ( !p_ )
			{
				// TODO: This exception should be supplied with additional information
				// to provide better way of problem resolution at runtime and better
				// support for logging.
				throw std::exception("Pointer is not initialized");
			}
			return p_;
		} */

		/**
		* Provides a way to call methods of contained object via -> operator.
		*/
		T * operator -> () const
		{
			if ( !p_ )
			{
				throw std::exception();
			}
			return p_;
		}

		/**
  		 * Provides a way to call methods of contained object via *(object). syntax.
 		 */
		T & operator * ()
		{
			if ( !p_ )
			{
				throw std::exception();
			}
			return *p_;
		}

		/**
  		 * Provides a way to call methods of contained object via *(object). syntax.
 		 */
		const T & operator * () const
		{
			if ( !p_ )
			{
				throw std::exception();
			}
			return *p_;
		}

		void Swap( Strong & rhs )
		{
			std::swap( p_, rhs.p_ );
			std::swap( refCounter_, rhs.refCounter_ );
		}

	// Comparison tools
	// private:

		template < typename T1 >
		bool Equals( const T1 * p ) const
		{
			return ( p_ == p );
		}

		template < typename T1 >
		bool LessThan( const T1 * p ) const
		{
			return ( p_ < p );
		}

		template < typename T1 >
		bool GreaterThan( const T1 * p ) const
		{
			return ( p_ > p );
		}

	// Comparison operators
	public:

		template < typename T1 >
		inline bool operator != ( const Strong< T1 > & rhs ) const
		{
			return !( rhs.Equals( p_ ) );
		}

		// Enables 'if ( !sp ) ...'
		inline bool operator ! () const 
		{
			return ( 0 == p_ );
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
			refCounter_ = new DualRefCounter( true );
		}

		void ReleaseCounter()
		{
			if ( refCounter_->HasWeakPointer() )
			{
				// Zap operation should be propagated to refCounter_ if it 
				// holds reference to contained object. Currently it does not.
			}
			else
			{
				// Delete counter if there are no weak references to the object.
				delete refCounter_;
				refCounter_ = NULL;
			}
		}

	// Data members
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

#endif // !STRONG_H__MINCOM__INCLUDED_
