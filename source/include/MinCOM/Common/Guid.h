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

		/**
		 * Generates new global unique identifier.
		 */
		static tagGuid Generate();

		/**
		 * Dumps guid to string.
		 * Format:
		 * {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}
		 */
		std::string ToString() const;
		
		/**
		 * Dumps guid to string.
		 * Format:
		 * XXXXXXXXYYYYZZZZXXXXYYYYYYYYYYYYY
		 */
		std::string ToRawString() const;		

		/**
		 * Restores guid from string.
		 */
		static tagGuid FromString(const std::string& str);
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

}

#endif // !GUID_H__MINCOM__INCLUDED_
