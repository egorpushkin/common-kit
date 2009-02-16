/*
 * File name   : DRawData.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-16  Egor Pushkin        Initial version
 */

#ifndef DSERVER_H__MINCOM__INCLUDED_
#define DSERVER_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * .
	 */
	interface DServer : public ICommon
	{	
		/** 
		 * .
		 */
		virtual result ConnectionAccepted(IConnectionRef connection) = 0;
	};

	typedef Strong< DServer > DServerPtr;

}

#endif // !DSERVER_H__MINCOM__INCLUDED_
