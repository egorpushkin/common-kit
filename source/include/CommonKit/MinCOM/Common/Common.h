#ifndef COMMON_H__MINCOM__NCLUDED_
#define COMMON_H__MINCOM__NCLUDED_

namespace MinCOM
{

#ifndef interface
	#define interface struct
#endif

	typedef void* handle;

	template 
	<
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

	#define MC_GUID_MEMBER(type, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)					\
		const Guid TypeInfo< type >::iid_													\
			= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

	interface IReferenceCounter
	{
	
		virtual unsigned long IncrementReference() = 0;

		virtual unsigned long DecrementReference() = 0;

	};

}

#endif // !COMMON_H__MINCOM__NCLUDED_
