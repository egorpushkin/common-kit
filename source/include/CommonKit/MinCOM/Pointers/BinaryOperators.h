/*
 * File name   : BinaryOperators.h 
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-09  Egor Pushkin        Initial version
 */

#ifndef BINARYOPERATORS_H__MINCOM__INCLUDED_
#define BINARYOPERATORS_H__MINCOM__INCLUDED_

namespace MinCOM
{

	template < typename T1, typename U >
	inline bool operator != ( const Strong< T1 > & lhs, U * rhs )
	{
		return !( lhs.Equals( rhs ) );
	}

	template < typename T1, typename U >
	inline bool operator != ( U * lhs, const Strong< T1 > & rhs )
	{
		return !( rhs.Equals( lhs ) );
	}

}

#endif // !BINARYOPERATORS_H__MINCOM__INCLUDED_
