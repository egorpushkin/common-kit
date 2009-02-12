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
	interface DProtocol : public ICommon
	{	
		/** 
		 * .
		 */
		virtual result MessageArrived(IMessageRef message) = 0;
	};

	typedef Strong< DProtocol > DProtocolPtr;
	typedef const DProtocolPtr* DProtocolRef;

}

#endif // !DPROTOCOL_H__MINCOM__INCLUDED_
