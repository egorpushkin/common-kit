#ifndef GUID_H__MINCOM__INCLUDED_
#define GUID_H__MINCOM__INCLUDED_

namespace MinCOM
{

	// Structure which represents Globally Unique Identifier (GUID)
	typedef struct tagGuid
	{
		unsigned long data1_;
		unsigned short data2_;
		unsigned short data3_;
		unsigned char data4_[8];
	} 
	Guid, Guid_, Iid, Clsid;

	// Some macros for operating with GUID objects
	typedef const Guid& RefGuid;
	typedef const Guid& RefIid;
	typedef const Guid&	RefClsid;

	// GUID operators
	__inline int InlineIsEqualGuid(RefGuid guid1, RefGuid guid2)
	{
		return (
			((unsigned long *)&guid1)[0] == ((unsigned long *)&guid2)[0] &&
			((unsigned long *)&guid1)[1] == ((unsigned long *)&guid2)[1] &&
			((unsigned long *)&guid1)[2] == ((unsigned long *)&guid2)[2] &&
			((unsigned long *)&guid1)[3] == ((unsigned long *)&guid2)[3]);
	}

	__inline int IsEqualGuid(RefGuid guid1, RefGuid guid2)
	{
		return !memcmp(&guid1, &guid2, sizeof(Guid));
	}

	__inline int operator==(RefGuid guid1, RefGuid guid2)
	{
		return IsEqualGuid(guid1, guid2);
	}

	__inline int operator!=(RefGuid guid1, RefGuid guid2)
	{
		return !(guid1 == guid2);
	}

	__inline bool operator < (RefGuid left, RefGuid right)
	{
		if ( memcmp(&left, &right, sizeof(sizeof(long) + sizeof(short) * 2 + sizeof(char) * 8)) < 0 )
			return true;
		return false;
	}

	#define MC_INITGUID

	#ifdef MC_INITGUID
		#define MC_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)				\
			const MinCOM::Guid name															\
				= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
	#else // MC_INITGUID
		#define MC_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)	\
			extern const MinCOM::Guid name
	#endif // MC_INITGUID

}

#endif // !GUID_H__MINCOM__INCLUDED_
