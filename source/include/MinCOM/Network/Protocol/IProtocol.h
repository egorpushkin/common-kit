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

	/**
	 * Provides a way of abstraction over tcp/ip raw data exchange. 
	 *
	 * Protocol dispatches 'DataErrorOccured' message as soon as it detects that 
	 * a peace of incorrect data is arrived. Protocol dispatches 'Disconnected' 
	 * message when connection is lost. This behavior does not depends on 
	 * protocol mode. See DProtocol for more details.
	 *
	 * This module introduces messaging concept. See IMessage and MessageImpl 
	 * for more details.
	 */ 
	struct IProtocol : public ICommon
	{
		/** 
		 * Enumerates list of allowed modes.
		 */ 
		typedef enum tagMode_
		{		
			/**
			 * Protocol does not dispatches 'MessageArrived' message to 
			 * subscribers when new messages arrive. Clients should make 
			 * blocking 'IProtocol->Receive' call to receive messages.
			 */ 
			SYNC = 0x0,

			/**
			 * Protocol dispatches 'MessageArrived' message to subscribers when 
			 * new messages arrive. 'IProtocol->Receive' call always returns 
			 * NULL synchronously (instantly).
			 */ 
			ASYNC
		} 
		Mode_;

		virtual IConnectionPtr GetConnection() = 0;

		/**
		 * Provides a way to switch between protocol modes on the fly.
		 *
		 * SYNC -> ASYNC. This causes for 'Receive' call to return NULL 
		 * immediately. All pending messages are processed asynchronously. 
		 *
		 * SYNC -> ASYNC. 
		 */
		virtual void SetMode(Mode_ mode) = 0;

		virtual Mode_ GetMode() = 0;

		/**
		 * SYNC.
		 *
		 * ASYNC. 
		 *
		 */ 
		virtual IMessagePtr Receive() = 0;

		/**
		 * Serializes method to output stream synchronously independently to
		 * the protocol functioning mode.
		 */ 
		virtual result Send(IMessageRef message) = 0;

		virtual void SetMessagesMap(IFactoryRef messagesMap) = 0;

		virtual IFactoryPtr GetMessagesMap() = 0;

	};

	typedef Strong< IProtocol > IProtocolPtr;
	typedef const IProtocolPtr& IProtocolRef;

}

#endif // !IPROTOCOL_H__MINCOM__INCLUDED_
