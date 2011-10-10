#include "Common/Common.h"

#include "NetworkStats.h"

namespace MinCOM
{
	NetworkStats::NetworkStats()
		: sessionStart_( 0 )	
		, sentLock_( Library::Mutex() )
		, sent_( 0 )
		, receivedLock_( Library::Mutex() )	
		, received_( 0 )
		, samplesLock_( Library::Mutex() )	
	    , sampleLifetime_( 5000 )
		, cleanupInterval_( 1000 )
		, forciblyRecalc_( true )
	    , samples_()
	    , lastCleanup_( 0 )
		, speed_( -1.0f )
	{
	}
	
	void NetworkStats::StartSession()
	{
		Reset();
		sessionStart_ = IThread::Time();
	}
	
	long NetworkStats::GetSessionDuration() const
	{
		return IThread::Time() - sessionStart_;
	}
		
	void NetworkStats::HandleSent(long bytes)
	{
		{
			MutexScope locker(sentLock_);
			sent_ += bytes;
		}
		AddNewSample(bytes);
	}
		
	void NetworkStats::HandleReceived(long bytes)
	{
		{
			MutexScope locker(receivedLock_);
			received_ += bytes;
		}
		AddNewSample(bytes);		
	}	
	
	long NetworkStats::GetTotalSent() const
	{
		return sent_;
	}	
	
	long NetworkStats::GetTotalReceived() const
	{
		return received_;
	}	
	
	long NetworkStats::GetTotalTraffic() const
	{
		return sent_ + received_;
	}	
	
	float NetworkStats::GetSpeed()
	{
		if ( forciblyRecalc_ || ( -1.0 == speed_ ) )
		{
			CalculateSpeed();
		}
		return speed_;
	}	
	
	void NetworkStats::Reset()
	{
		MutexScope locker1(sentLock_);		
		MutexScope locker2(receivedLock_);	
		MutexScope locker3(samplesLock_);						
		sent_ = 0;
		received_ = 0;
		samples_.clear();
		speed_ = -1.0f;
	}
	
	void NetworkStats::AddNewSample(long bytes)
	{
		MutexScope locker(samplesLock_);				
		// Add new sample.
		Sample_ sample;
		sample.timestamp_ = IThread::Time();
		sample.size_ = bytes;
		samples_.push_back(sample);
		// Remove old samples.
		CleanupSamples();
		// Request bandwidth update.
		speed_ = -1.0f;
	}
	
	void NetworkStats::CleanupSamples()
	{
		ulonglong time = IThread::Time(); 		
		if ( ( time - lastCleanup_ ) < cleanupInterval_ )
		{
			return;
		}		
		while ( !samples_.empty() )
		{
			Sample_ sample = samples_.front();
			if ( ( time - sample.timestamp_ ) > sampleLifetime_ )
			{
				samples_.pop_front();
			}		
			else 
			{
				break;
			}
		}
		lastCleanup_ = time;
	}
	
	void NetworkStats::CalculateSpeed()
	{
		MutexScope locker(samplesLock_);			
		// Remove old samples.
		CleanupSamples();
		// Calculate bacndwidth.
		speed_ = 0.0f;
		long size = 0;
		Samples_::iterator iter = samples_.begin();
		Samples_::iterator end = samples_.end();		
		for ( ; iter != end ; ++iter )
		{
			size += (*iter).size_;
		}
		if ( !samples_.empty() )
		{
			ulonglong oldestSample = samples_.front().timestamp_;		
			ulonglong time = IThread::Time();		
			speed_ = size / ( ( time - oldestSample ) / 1000.0f );
		}
	}
}