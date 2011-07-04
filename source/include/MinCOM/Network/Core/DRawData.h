/*
 * File name   : DRawData.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-09  Egor Pushkin        Initial version
 */

#ifndef DRAWDATA_H__MINCOM__INCLUDED_
#define DRAWDATA_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * .
	 */
	struct DRawData : public ICommon
	{	
		/** 
		 * .
		 */
		virtual result Connected(IConnectionRef connection) = 0;

		/** 
		 * .
		 */
		virtual result DataReceived(IConnectionRef connection) = 0;

		/** 
		 * .
		 */
		virtual result Disconnected(IConnectionRef connection) = 0;
	};

	typedef Strong< DRawData > DRawDataPtr;

}

#endif // !DRAWDATA_H__MINCOM__INCLUDED_
