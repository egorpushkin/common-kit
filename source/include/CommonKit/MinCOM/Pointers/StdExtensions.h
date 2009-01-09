/*
 * File name   : StdExtensions.h 
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-09  Egor Pushkin        Initial version
 */

#ifndef STDEXTENSIONS_H__MINCOM__INCLUDED_
#define STDEXTENSIONS_H__MINCOM__INCLUDED_

namespace std
{
	/**
	 * Specialization of std::less for Strong.
	 */
	template
	<
		typename T
	>
	struct less< MinCOM::Strong< T > >
		: public binary_function<
			MinCOM::Strong< T >,
			MinCOM::Strong< T >, bool >
	{
		bool operator () (
			const MinCOM::Strong< T > & lhs,
			const MinCOM::Strong< T > & rhs ) const
		{
			return ( lhs < rhs );
		}
	};
}

#endif // !STDEXTENSIONS_H__MINCOM__INCLUDED_
