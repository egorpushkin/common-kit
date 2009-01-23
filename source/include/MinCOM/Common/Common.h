#ifndef COMMON_H__MINCOM__NCLUDED_
#define COMMON_H__MINCOM__NCLUDED_

namespace MinCOM
{

#ifndef interface
	/** . */
	#define interface struct
#endif

	/** . */
	typedef void* handle;

	/**
	 * Class to associate particular interface or class with iid at
	 * compile time. This is a part of mechanism intended to avoid  
	 * 'QueryInterface like methods' of casting between different control 
	 * interfaces of the same object. 
	 *
	 * Example: 
	 * \code 
	 *     const Guid TypeInfo< ICommon >::iid_ = 
	 *         {0x3d24c25d, 0x2c73, 0x4a47, 0x92, 0x64, 0xa5, 0xd5, 0xb1, 0xbf, 0xdf, 0x75};
	 */ 
	template 
	<
		/**
		 * Control interface or class name acts as template parameter.
		 */
		class T	
	>
	class TypeInfo
	{
		static const Guid iid_;
	public:		
		static RefGuid GetGuid()
		{
			return iid_;
		}
		static size_t Size()
		{
			return sizeof(T);
		}
	};

	/**
	 * Core interface providing support for internal reference counting.
	 * Each class should implement this interface. MinCOM utilizes this rule
	 * by inheriting ICommon from IReferenceCounter. 
	 *
	 * This tool is designed to deny arbitrary access to reference counter.
	 * The decision whether to provide debug access to object internals refers 
	 * to the discretion of implementation constitute and is not standardized.
	 *
	 * Implementation of this interface must me thread safe.
	 */ 
	interface IReferenceCounter
	{
		/** Should increase internal reference counter. */
		virtual long IncrementReference() = 0;

		/** Should decrease internal reference counter. */
		virtual long DecrementReference() = 0;
	};

}

#endif // !COMMON_H__MINCOM__NCLUDED_
