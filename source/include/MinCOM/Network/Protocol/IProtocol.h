/*
 * File name   : IProtocol.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-11  Egor Pushkin        Initial version
 */

#ifndef IPROTOCOL_H__MINCOM__INCLUDED_
#define IPROTOCOL_H__MINCOM__INCLUDED_

namespace MinCOM
{

	typedef enum tagProtocolMode 
	{		

		PROTOCOL_SYNC = 0x0,

		PROTOCOL_ASYNC

	} 
	ProtocolMode;

	interface IProtocol : public ICommon
	{

		virtual result AttachConnection(IConnectionRef connection, ProtocolMode mode = PROTOCOL_SYNC) = 0;

		virtual IConnectionPtr GetConnection() = 0;

		virtual void SetMode(ProtocolMode mode) = 0;

		virtual IMessagePtr Receive() = 0;

		virtual result Send(IMessageRef message) = 0;

		virtual void SetMessagesMap(IFactoryRef messagesMap) = 0;

		virtual IFactoryPtr GetMessagesMap() = 0;

	};

	typedef Strong< IProtocol > IProtocolPtr;
	typedef const IProtocolPtr& IProtocolRef;

}

#endif // !IPROTOCOL_H__MINCOM__INCLUDED_
