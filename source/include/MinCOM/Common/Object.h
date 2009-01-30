/*
* File name   : Object.h
*
* Copyright (c) 2008 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2008-12-14  Egor Pushkin        Initial version
* 2009-01-23  Egor Pushkin        Routines were organized into class
*/

#ifndef OBJECT_H__MINCOM__INCLUDED_
#define OBJECT_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Provides unified tool to construct all MinCOM objects.
	 * Potentially this tool is responsible for memory management of all
	 * allocated objects.
	 */ 
	template
	<
		/**
		 * Template argument should indicate particular class compatible
		 * to MinCOM object.
		 */ 
		class T
	>
	class Object
	{
	public:

		static Strong<ICommon> Create() 
		{ 
			try
			{
				return PostInit(Strong<ICommon>(new T())); 
			}
			catch ( ... )
			{
				return NULL;
			}
		}	

		template< class T1 > 
		static Strong<ICommon> Create(T1 p1) 
		{ 
			try
			{
				return PostInit(Strong<ICommon>(new T(p1))); 
			}
			catch ( ... )
			{
				return NULL;
			}
		}	

		template< class T1, class T2 > 
		static Strong<ICommon> Create(T1 p1, T2 p2) 
		{ 
			try
			{
				return PostInit(Strong<ICommon>(new T(p1, p2))); 
			}
			catch ( ... )
			{
				return NULL;
			}
		}	

		template< class T1, class T2, class T3 > 
		static Strong<ICommon> Create(T1 p1, T2 p2, T3 p3) 
		{ 
			try
			{
				return PostInit(Strong<ICommon>(new T(p1, p2, p3))); 
			}
			catch ( ... )
			{
				return NULL;
			}
		}	

	private:

		static Strong<ICommon> PostInit(const Strong<ICommon> & common)
		{
			common->SetSelf(common);
			// common->PostInit();
			return common;
		}	

	};

}

#endif // !OBJECT_H__MINCOM__INCLUDED_
