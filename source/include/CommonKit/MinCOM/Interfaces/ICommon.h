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

	protected:

		virtual ~ICommon()
		{
		}
		
	};

}

#endif // !ICOMMON_H__MINCOM__INCLUDED_
