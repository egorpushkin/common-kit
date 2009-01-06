/*
 * File name   : ICommon.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2008-12-14  Egor Pushkin        Initial version
 */

#ifndef ICOMMON_H__MINCOM__INCLUDED_
#define ICOMMON_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * 
	 */
	interface ICommon : public IReferenceCounter
	{
	public:

		/**
		 * Method to cast pointer to any object's control interface to
		 * pointer to another interface which is potentially supported by 
		 * the object.
		 */
		template
		<
			class T1
		>
		T1 * Cast()
		{
			// Try to cast current type to the specified one dynamically.
			T1 * pT = dynamic_cast< T1* >(this);
			if ( !pT )
				return NULL;
			
			// Increment a number of references to the object.
			pT->IncrementReference();

			// Provide caller with reference to target control interface.
			return pT;
		}

	public:
	
		typedef ComPtr< ICommon > Ptr_;
		
		typedef ComPtr< ICommon, false > Weak_;

		typedef const Ptr_& Ref_;
			
	protected:

		virtual ~ICommon()
		{
		}
		
	};
	
/*
	template<>
	class TypeInfo< ICommon > : public TypeInfoCore
	{
	public: 
		RefGuid GetGuid() 
		{
			return iid_;
		}
	};
*/

	// {3d24c25d-2c73-4a47-9264-a5d5b1bfdf75} 
	const Guid TypeInfo< ICommon >::iid_ = 
		{0x3d24c25d, 0x2c73, 0x4a47, 0x92, 0x64, 0xa5, 0xd5, 0xb1, 0xbf, 0xdf, 0x75};

}

#endif // !ICOMMON_H__MINCOM__INCLUDED_
