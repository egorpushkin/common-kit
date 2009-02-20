/*
 * File name   : IReadWriteLock.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-19  Egor Pushkin        Initial version
 */

#ifndef IREADWRITELOCK_H__MINCOM__INCLUDED_
#define IREADWRITELOCK_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Provides a way to synchronize simultaneous access to the same 
	 * resource by readers and writers. 
	 */
	interface IReadWriteLock : public ICommon
	{
		/**
		 * Should be called before modifying the resource.
		 */
		virtual result WaitToWrite() = 0;

		/**
		 * Should be called when modification is done.
		 */
		virtual result DoneWriting() = 0;

		/**
		 * Should be called before reading the resource.
		 */
		virtual result WaitToRead() = 0;

		/**
		 * Should be called when reading is done.
		 */
		virtual result DoneReading() = 0;

		/** 
		 * Provide automatic locking for writer routines. 
		 */
		class Writer_
		{
		public:
			Writer_( const Strong< IReadWriteLock >& lock )
				: lock_(lock)
			{
				lock_->WaitToWrite();
			}
			~Writer_()
			{
				lock_->DoneWriting();
			}
		private:
			Strong< IReadWriteLock > lock_;
		};

		/** 
		 * Provide automatic locking for reader routines. 
		 */
		class Reader_
		{
		public:
			Reader_( const Strong< IReadWriteLock >& lock )
				: lock_(lock)
			{
				lock_->WaitToRead();
			}
			~Reader_()
			{
				lock_->DoneReading();
			}
		private:
			Strong< IReadWriteLock > lock_;
		};

	};

	typedef Strong< IReadWriteLock > IReadWriteLockPtr;
	typedef const IReadWriteLockPtr& IReadWriteLockRef;
	typedef Weak< IReadWriteLock > IReadWriteLockWeak;

}

#endif // !IREADWRITELOCK_H__MINCOM__INCLUDED_
