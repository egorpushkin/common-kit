#ifndef READWRITELOCK_H__MINCOMLIB__INCLUDED_
#define READWRITELOCK_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	/** 
	 * Implements the following rule:
	 *  - Multiple readers can read the data simultaneously.
	 *  - Only one writer can write the data at any time.
	 *  - A reader and a writer cannot be in critical section together.
	 * 
	 * This is powered by simple and very efficient schema based on 
	 * locking resources but not operations. Two mutexes are required to 
	 * power this schema: one for counters and another one for target
	 * resource.
	 */
	class ReadWriteLock 
		: public mc::CommonImpl< IReadWriteLock >
	{
	public:

		ReadWriteLock();

		// IJobsQueue section
		virtual result WaitToWrite();

		virtual result DoneWriting();

		virtual result WaitToRead();

		virtual result DoneReading();

	private:

		/** Prevents access to the resource from multiple threads. */
		IMutexPtr resourceMutex_;

		/** Prevents access to counters from multiple threads. */
		IMutexPtr countersMutex_;

		/** Number of actual writers. This property was made signed intentionally
		 * for debug purposes. This allows to alert if negative value is met here.*/
		long writersCount_;

		/** Number of actual readers. */
		long readersCount_;

	};

}

#endif // !READWRITELOCK_H__MINCOMLIB__INCLUDED_
