#ifndef NETWORKSTATS_H__MINCOMLIB__INCLUDED_
#define NETWORKSTATS_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{	
	class NetworkStats
		: public CommonImpl< INetworkStats >
	{
	public:
		
		NetworkStats();
		
		// INetworkStats section
		virtual void StartSession();
		
		virtual long GetSessionDuration() const;
		
		virtual void HandleSent(long bytes);
		
		virtual void HandleReceived(long bytes);				
		
		virtual long GetTotalSent() const;
		
		virtual long GetTotalReceived() const;
		
		virtual long GetTotalTraffic() const;
		
		virtual float GetSpeed();		
		
		virtual void Reset();
		
	private:
		
		void AddNewSample(long bytes);
		
		void CleanupSamples();
		
		void CalculateSpeed();
		
	private:
		
		ulonglong sessionStart_;
		
		IMutexPtr sentLock_;
		
		long sent_;
		
		IMutexPtr receivedLock_;
		
		long received_;
		
		IMutexPtr samplesLock_;
		
        unsigned long sampleLifetime_;
		
        unsigned long cleanupInterval_;
		
		bool forciblyRecalc_;
		
		typedef struct tagSample_
		{
			ulonglong timestamp_;
			long size_;
		}
		Sample_;
				
		typedef std::list< Sample_ > Samples_;
		
		Samples_ samples_;
		
		ulonglong lastCleanup_;
		
		float speed_;
		
	};	
}

#endif // !NETWORKSTATS_H__MINCOMLIB__INCLUDED_
