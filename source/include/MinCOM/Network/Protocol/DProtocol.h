/*
 * File name   : DProtocol.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-11  Egor Pushkin        Initial version
 */

#ifndef DPROTOCOL_H__MINCOM__INCLUDED_
#define DPROTOCOL_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * .
	 */
	struct DProtocol : public ICommon
	{	
		/** 
		 * Fired when new message arrives.
		 */
		virtual result MessageArrived(IProtocolRef protocol, IMessageRef message) = 0;

		/**
		 * Fired when arrived data cannot be parsed correctly.
		 */
		virtual result DataErrorOccured(IProtocolRef protocol) = 0;

		/** 
		 * Fired when connection is lost.
		 */
		virtual result Disconnected(IProtocolRef protocol) = 0;
	};

	typedef Strong< DProtocol > DProtocolPtr;
	typedef const DProtocolPtr& DProtocolRef;

}

#endif // !DPROTOCOL_H__MINCOM__INCLUDED_
