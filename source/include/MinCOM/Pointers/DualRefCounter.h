/*
 * File name   : DualRefCounter.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-08  Egor Pushkin        Initial version
 */

#ifndef DUALREFCOUNTER_H__MINCOM__INCLUDED_
#define DUALREFCOUNTER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Class to provide reference counting for dual smart pointers
	 * (strong and weak).
	 */ 
	class DualRefCounter
	{
	public:

		DualRefCounter( bool strong )
			: strongCount_( strong ? 1 : 0 )
			, weakCount_( strong ? 0 : 1 )
			, mutex_()
		{
		}

		~DualRefCounter()
		{
			assert( 0 == strongCount_ );
			assert( 0 == weakCount_ );
		}

		inline bool HasStrongPointer( void ) const
		{
			return ( 0 < strongCount_ );
		}

		inline bool HasWeakPointer( void ) const
		{
			return ( 0 < weakCount_ );
		}

		inline void IncStrongCount( void )
		{
			CoreMutexLock lock(mutex_);
			++strongCount_;
		}

		inline void IncWeakCount( void )
		{
			CoreMutexLock lock(mutex_);
			++weakCount_;
		}

		inline void DecStrongCount( void )
		{
			CoreMutexLock lock(mutex_);
			assert( 0 < strongCount_ );
			--strongCount_;
		}

		inline void DecWeakCount( void )
		{
			CoreMutexLock lock(mutex_);
			assert( 0 < weakCount_ );
			--weakCount_;
		}

	private:

		/** Copy-constructor not implemented and denied. */
		DualRefCounter( const DualRefCounter & );

		/** Copy-assignment operator not implemented and denied. */
		DualRefCounter & operator = ( const DualRefCounter & );

	private:

		/** Holds a number of strong references. */
		long strongCount_;

		/** Holds a number of weak references. */
		long weakCount_;

		/** Pointer to contained object. */
		mutable CoreMutex mutex_;

	};

}

#endif // !DUALREFCOUNTER_H__MINCOM__INCLUDED_
