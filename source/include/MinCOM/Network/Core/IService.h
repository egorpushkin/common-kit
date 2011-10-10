/*
 * File name   : IService.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-10  Egor Pushkin        Initial version
 */

#ifndef ISERVICE_H__MINCOM__INCLUDED_
#define ISERVICE_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Powers asynchronous communications facility.
	 */  
	struct IService : public ICommon
	{

		/**
		 * Runs internal event processing loop.
		 * Blocking call.
		 */
		virtual void Run() = 0;

		/**
		 * Signals the service to stop.
		 * Nonblocking call.
		 */
		virtual void Stop() = 0;
		
		/**
		 * Provides access to basic network analytics.
		 */
		virtual INetworkStatsPtr GetStats() const = 0;

	};

	typedef Strong< IService > IServicePtr;
	typedef const IServicePtr& IServiceRef;

}

#endif // !ISERVICE_H__MINCOM__INCLUDED_
