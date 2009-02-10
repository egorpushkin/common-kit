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

		// typedef unsigned long Id_;

		virtual result Establish(const std::string& host, const std::string& service) = 0;

		virtual result Establish(IHostRef host) = 0;

		// virtual mc::result Write(asio::streambuf& buffer) = 0;
		// virtual std::size_t Read(const mc::StringA& delimiter) = 0;
		// virtual std::size_t Read(std::size_t minimum = 1) = 0;

		/** 
		 * Tool to initiate asynchronous read operation. As soon as this is
		 * done all subscribers will start receiving corresponding
		 * DRawData events (DataReceived). 
		 */ 
		virtual void ReadAsync(std::size_t minimum = 1) = 0;

		/**
		 * Use this tool only to produce your own std::istream and std::ostream
		 * objects. Note that lifetime of these objects must not exceed the lifetime
		 * of object implementing IConnection.
		 */ 
		virtual std::streambuf& GetStream() = 0;
	};

	typedef Strong< IConnection > IConnectionPtr;
	typedef const IConnectionPtr& IConnectionRef;

}

#endif // !ICONNECTION_H__MINCOM__INCLUDED_
