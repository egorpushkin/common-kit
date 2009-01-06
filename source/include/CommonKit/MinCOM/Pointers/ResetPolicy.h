/*
* File name   : ResetPolicy.h
*
* Copyright (c) 2008 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2008-12-29  Egor Pushkin        Initial version based on Loki::StrongPtr.
*/

#ifndef RESET_H__MINCOM__INCLUDED_
#define RESET_H__MINCOM__INCLUDED_

namespace MinCOM
{

	////////////////////////////////////////////////////////////////////////////////
	///  \class CantResetWithStrong
	///
	///  \ingroup  StrongPointerResetGroup 
	///  Implementation of the ResetPolicy used by StrongPtr.  This is the default
	///   ResetPolicy for StrongPtr.  It forbids reset and release only if a strong
	///   copointer exists.
	////////////////////////////////////////////////////////////////////////////////

	template < class P >
	struct CantResetWithStrong
	{
		inline bool OnReleaseAll( bool hasStrongPtr ) const
		{
			return ! hasStrongPtr;
		}

		inline bool OnResetAll( bool hasStrongPtr ) const
		{
			return ! hasStrongPtr;
		}
	};

}

#endif // !RESET_H__MINCOM__INCLUDED_
