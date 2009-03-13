/*
 * File name   : IConnection.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-05  Egor Pushkin        Initial version
 */

#ifndef ICONNECTION_H__MINCOM__INCLUDED_
#define ICONNECTION_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface IConnection : public ICommon
	{
		
		/** 
		 * Enumeration of all possible connection states.
		 */
		typedef enum tagState_
		{
			NOT_INITIALIZED = 0,
			CONNECTING = 1,
			CONNECTED = 2,
			DISCONNECTED = 3
		} 
		State_;

		virtual result Establish(const std::string& host, const std::string& service) = 0;

		virtual result Establish(IHostRef host) = 0;

		virtual State_ GetState() = 0;

		virtual std::string GetIpAddress() = 0;

		/** 
		 * Tool to initiate asynchronous read operation. As soon as this is
		 * done all subscribers will start receiving corresponding
		 * DRawData events (DataReceived). 
		 */ 
		virtual void ReadAsync(std::size_t minimum = 1) = 0;

		/**
		 * Asynchronously writes the entire contents of internal output buffer 
		 * to a stream.
		 */
		virtual void WriteAsync() = 0;
        
 		/**
		 * Synchronously writes the entire  contents of internal output buffer 
		 * to a stream.
		 */
		virtual void Write() = 0;       

		/**
		 * Use this tool only to produce your own std::istream objects. 
		 * Note that lifetime of these objects must not exceed the lifetime
		 * of object implementing IConnection.
		 */ 
		virtual std::streambuf& GetIStreamBuf() = 0;

		virtual size_t GetISize() = 0;

		/**
		 * Use this tool only to produce your own std::ostream objects. 
		 * Note that lifetime of these objects must not exceed the lifetime
		 * of object implementing IConnection.
		 */ 
		virtual std::streambuf& GetOStreamBuf() = 0;

		virtual size_t GetOSize() = 0;
	};

	typedef Strong< IConnection > IConnectionPtr;
	typedef const IConnectionPtr& IConnectionRef;

}

#endif // !ICONNECTION_H__MINCOM__INCLUDED_
