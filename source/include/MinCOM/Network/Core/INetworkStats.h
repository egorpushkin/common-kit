/*
 * File name   : INetworkStats.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2011-10-08  Egor Pushkin        Initial version
 */

#ifndef INETWORKSTATS_H__MINCOM__INCLUDED_
#define INETWORKSTATS_H__MINCOM__INCLUDED_

namespace MinCOM
{
	struct INetworkStats : public ICommon
	{
		virtual void StartSession() = 0;
		
		virtual long GetSessionDuration() const = 0;
		
		virtual void HandleSent(long bytes) = 0;
		
		virtual void HandleReceived(long bytes) = 0;				
				
		virtual long GetTotalSent() const = 0;
		
		virtual long GetTotalReceived() const = 0;
		
		virtual long GetTotalTraffic() const = 0;
		
		virtual float GetSpeed() = 0;		
		
		virtual void Reset() = 0;
	};
	
	typedef Strong< INetworkStats > INetworkStatsPtr;
	typedef const INetworkStatsPtr& INetworkStatsRef;
}

#endif // !INETWORKSTATS_H__MINCOM__INCLUDED_
