/*
 * File name   : OwnershipPolicy.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2008-12-29  Egor Pushkin        Initial version based on Loki::StrongPtr.
 */

#ifndef OWNERSHIP_H__MINCOM__INCLUDED_
#define OWNERSHIP_H__MINCOM__INCLUDED_

namespace MinCOM
{
	
	/**
	 * MinCOM 0.1.0 enhancement.
	 * 
	 */
	namespace Private
	{

		class InternalReferenceCounter
		{
		private:

			static IReferenceCounter * GetReferenceCounter(void * p)
			{
				return reinterpret_cast< IReferenceCounter* >(p);
			}

		public:

			template
			<
				class T
			>
			static void Increment(T * p)
			{
				if ( !p )
					return;
				/*
				IReferenceCounter * referenceCounter = GetReferenceCounter(p);
				if ( !referenceCounter )
					return;
				*/
				p->IncrementReference();
			}

			template
			<
				class T
			>
			static void Decrement(T * p)
			{
				if ( !p )
					return;				
				/*
				IReferenceCounter * referenceCounter = GetReferenceCounter(p);
				if ( !referenceCounter )
					return;
				*/
				p->DecrementReference();
			}

		};

	}

	////////////////////////////////////////////////////////////////////////////////
	///  \class TwoRefCountInfo
	///
	///  \ingroup  StrongPointerOwnershipGroup
	///   Implementation detail for reference counting strong and weak pointers.
	///   It maintains a void pointer and 2 reference counts.  Since it is just a
	///   class for managing implementation details, it is not intended to be used
	///   directly - which is why it is in a private namespace.  Each instance is a
	///   shared resource for all copointers, and there should be only one of these
	///   for each set of copointers.  This class is small, trivial, and inline.
	////////////////////////////////////////////////////////////////////////////////

	class TwoRefCountInfo
	{
	public:

		inline explicit TwoRefCountInfo( bool strong )
			: m_pointer( 0 )
			, m_strongCount( strong ? 1 : 0 )
			, m_weakCount( strong ? 0 : 1 )
			, m_strong(strong)
		{
		}

		inline TwoRefCountInfo( void * p, bool strong )
			: m_pointer( p )
			, m_strongCount( strong ? 1 : 0 )
			, m_weakCount( strong ? 0 : 1 )
			, m_strong(strong)

		{
		}

		inline ~TwoRefCountInfo( void )
		{
			assert( 0 == m_strongCount );
			assert( 0 == m_weakCount );
		}

		inline bool HasStrongPointer( void ) const
		{
			return ( 0 < m_strongCount );
		}

		inline bool HasWeakPointer( void ) const
		{
			return ( 0 < m_weakCount );
		}

		inline void IncStrongCount( void )
		{
			++m_strongCount;
		}

		inline void IncWeakCount( void )
		{
			++m_weakCount;
		}

		inline void DecStrongCount( void )
		{
			assert( 0 < m_strongCount );
			--m_strongCount;
		}

		inline void DecWeakCount( void )
		{
			assert( 0 < m_weakCount );
			--m_weakCount;
		}

		inline void ZapPointer( void )
		{
			m_pointer = 0;
		}

		inline void * GetPointer( void ) const
		{
			return m_pointer;
		}

		inline void * & GetPointerRef( void ) const
		{
			return const_cast< void * & >( m_pointer );
		}

		inline bool IsStrong() const
		{
			return m_strong;
		}

	private:
		/// Copy-constructor not implemented.
		TwoRefCountInfo( const TwoRefCountInfo & );
		/// Copy-assignment operator not implemented.
		TwoRefCountInfo & operator = ( const TwoRefCountInfo & );

		void * m_pointer;
		unsigned int m_strongCount;
		unsigned int m_weakCount;
		bool m_strong;
	};

	////////////////////////////////////////////////////////////////////////////////
	///  \class LockableTwoRefCountInfo
	///
	///  \ingroup  StrongPointerOwnershipGroup
	///   Implementation detail for thread-safe reference counting for strong and
	///   weak pointers.  It uses TwoRefCountInfo to manage the pointer and counts.
	///   All this does is provide a thread safety mechanism.  Since it is just a
	///   class for managing implementation details, it is not intended to be used
	///   directly - which is why it is in a private namespace.  Each instance is a
	///   shared resource for all copointers, and there should be only one of these
	///   for each set of copointers.  This class is small, trivial, and inline.
	///
	///  \note This class is not designed for use with a single-threaded model.
	///   Tests using a single-threaded model will not run properly, but tests in a
	///   multi-threaded model with either class-level-locking or object-level-locking
	///   do run properly.
	////////////////////////////////////////////////////////////////////////////////
	
	class LockableTwoRefCountInfo
		: private TwoRefCountInfo
	{
	public:

		inline explicit LockableTwoRefCountInfo( bool strong )
			: TwoRefCountInfo( strong )
			, m_Mutex()
		{
		}

		LockableTwoRefCountInfo( void * p, bool strong )
			: TwoRefCountInfo( p, strong )
			, m_Mutex()
		{
		}

		inline ~LockableTwoRefCountInfo( void )
		{
		}

		inline void Lock( void ) const
		{
			m_Mutex.Lock();
		}

		inline void Unlock( void ) const
		{
			m_Mutex.Unlock();
		}

		inline bool HasStrongPointer( void ) const
		{
			m_Mutex.Lock();
			const bool has = TwoRefCountInfo::HasStrongPointer();
			m_Mutex.Unlock();
			return has;
		}

		inline bool HasWeakPointer( void ) const
		{
			m_Mutex.Lock();
			const bool has = TwoRefCountInfo::HasWeakPointer();
			m_Mutex.Unlock();
			return has;
		}

		inline void IncStrongCount( void )
		{
			m_Mutex.Lock();
			TwoRefCountInfo::IncStrongCount();
			m_Mutex.Unlock();
		}

		inline void IncWeakCount( void )
		{
			m_Mutex.Lock();
			TwoRefCountInfo::IncWeakCount();
			m_Mutex.Unlock();
		}

		inline void DecStrongCount( void )
		{
			m_Mutex.Lock();
			TwoRefCountInfo::DecStrongCount();
			m_Mutex.Unlock();
		}

		inline void DecWeakCount( void )
		{
			m_Mutex.Lock();
			TwoRefCountInfo::DecWeakCount();
			m_Mutex.Unlock();
		}

		inline void ZapPointer( void )
		{
			m_Mutex.Lock();
			TwoRefCountInfo::ZapPointer();
			m_Mutex.Unlock();
		}

		inline void * GetPointer( void ) const
		{
			return TwoRefCountInfo::GetPointer();
		}

		inline void * & GetPointerRef( void ) const
		{
			return TwoRefCountInfo::GetPointerRef();
		}

		inline bool IsStrong() const
		{
			return TwoRefCountInfo::IsStrong();
		}

	private:
		/// Default constructor is not available.
		LockableTwoRefCountInfo( void );
		/// Copy constructor is not available.
		LockableTwoRefCountInfo( const LockableTwoRefCountInfo & );
		/// Copy-assignment operator is not available.
		LockableTwoRefCountInfo & operator = ( const LockableTwoRefCountInfo & );

		mutable CoreMutex m_Mutex;
	};

	////////////////////////////////////////////////////////////////////////////////
	///  \class LockableTwoRefCounts
	///
	///  \ingroup  StrongPointerOwnershipGroup
	///   This implementation of StrongPtr's OwnershipPolicy uses a pointer to a
	///   shared instance of LockableTwoRefCountInfo.  It behaves very similarly to
	///   TwoRefCounts, except that it provides thread-safety.  Some functions are
	///   trivial enough to be inline, while others are implemented elsewhere.
	///
	///  \note This class is not designed for use with a single-threaded model.
	///   Tests using a single-threaded model will not run properly, but tests in a
	///   multi-threaded model with either class-level-locking or object-level-locking
	///   do run properly.
	////////////////////////////////////////////////////////////////////////////////

	class LockableTwoRefCounts
	{
	protected:

		explicit LockableTwoRefCounts( bool strong )
			: m_counts( NULL )
		{
			m_counts = new LockableTwoRefCountInfo( strong );
		}

		LockableTwoRefCounts( const void * p, bool strong )
			: m_counts( NULL )
		{
			m_counts = new LockableTwoRefCountInfo( const_cast< void * >( p ), strong );
		}

		LockableTwoRefCounts( const LockableTwoRefCounts & rhs, bool strong ) 
			: m_counts( rhs.m_counts )
		{
			Increment( strong );
		}

		// MinCOM 0.1.0 enhancement.
		LockableTwoRefCounts( const LockableTwoRefCounts * rhs, bool strong ) 
			: m_counts( NULL )
		{
			if ( rhs )
			{
				m_counts = rhs->m_counts;
				Increment( strong );
			}
			else
			{
				m_counts = new LockableTwoRefCountInfo( strong );
			}
		}

		inline void Lock( void ) const
		{
			m_counts->Lock();
		}

		inline void Unlock( void ) const
		{
			m_counts->Unlock();
		}

		inline bool Release( bool strong )
		{
			return Decrement( strong );
		}

		void Increment( bool strong )
		{
			if ( strong )
			{
				m_counts->IncStrongCount();
			}
			else
			{
				m_counts->IncWeakCount();
			}
		}

		bool Decrement( bool strong )
		{
			if ( strong )
			{
				m_counts->DecStrongCount();
			}
			else
			{
				m_counts->DecWeakCount();
			}
			return !m_counts->HasStrongPointer();
		}

		bool HasStrongPointer( void ) const
		{
			return m_counts->HasStrongPointer();
		}

		void Swap( LockableTwoRefCounts & rhs )
		{
			std::swap( m_counts, rhs.m_counts );
		}

		void ZapPointer( void )
		{
#ifdef DO_EXTRA_LOKI_TESTS
			assert( !m_counts->HasStrongPointer() );
#endif
			if ( m_counts->HasWeakPointer() )
			{
				m_counts->ZapPointer();
			}
			else
			{
				delete m_counts;
				m_counts = NULL;
			}
		}

		inline void * GetPointer( void ) const
		{
			return m_counts->GetPointer();
		}

		inline void * & GetPointerRef( void ) const
		{
			return m_counts->GetPointerRef();
		}

	private:
		LockableTwoRefCounts( void );
		LockableTwoRefCounts & operator = ( const LockableTwoRefCounts & );

		/// Pointer to all shared data.
		LockableTwoRefCountInfo * m_counts;
	};

}

#endif // !OWNERSHIP_H__MINCOM__INCLUDED_
