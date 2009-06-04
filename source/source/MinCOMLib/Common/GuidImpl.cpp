#include "Common/Common.h"

#if defined(_MSC_VER) || defined(__MINGW32__)
// This should be done because <objbase.h> declares 'interface' macro in the 
// same way as MinCOM does. 
#undef interface
#include <objbase.h>
#endif

#include <sstream>
#include <iomanip>

#if defined(__MACH__)
#include <CoreFoundation/CoreFoundation.h>
#endif

namespace MinCOM
{

	tagGuid Guid::Generate()
	{
		mc::Guid guid;
		// Determine OS at compile time.
#if defined(_MSC_VER) || defined(__MINGW32__)		
		// This tool may be used because mc::Guid is binary compatible with COM 
		// GUID.
		::CoCreateGuid((GUID*)&guid);
#elif defined(__MACH__)
        // CFUUIDCreate produces the same old 16 bytes unique identifier. 
        CFUUIDRef uuid = CFUUIDCreate(NULL);
        CFUUIDBytes uuidBytes = CFUUIDGetUUIDBytes(uuid);
        CFRelease(uuid);	
        memcpy(&guid, &uuid, sizeof(guid));
#endif			
		return guid;
	}

	std::string Guid::ToString() const
	{
		std::stringstream stream;
		stream 
			<< std::hex << std::setfill('0')
			<< "{"
			<< std::setw(8) << data1_
			<< "-"
			<< std::setw(4) << data2_
			<< "-"
			<< std::setw(4) << data3_
			<< "-"
			<< std::setw(2) << (int)data4_[0] 
			<< std::setw(2) << (int)data4_[1] 
			<< "-"
			<< std::setw(2) << (int)data4_[2] 
			<< std::setw(2) << (int)data4_[3]
			<< std::setw(2) << (int)data4_[4] 
			<< std::setw(2) << (int)data4_[5] 
			<< std::setw(2) << (int)data4_[6] 
			<< std::setw(2) << (int)data4_[7]
			<< "}";
		std::string str;
		stream >> str;
		return str;
	}

	tagGuid Guid::FromString(const std::string& str)
	{
		Guid guid;	
		std::stringstream stream;
		stream << str << std::hex;
		char c;
		stream >> c;
		stream >> guid.data1_;
		stream >> c;
		stream >> guid.data2_;
		stream >> c;
		stream >> guid.data3_;
		stream >> c;
		int s;
		stream >> s;
		unsigned char *buf = (unsigned char *)&s;
		guid.data4_[0] = buf[1];
		guid.data4_[1] = buf[0];
		stream >> c;
		longlong l;
		stream >> l;
		buf = (unsigned char *)&l;
		guid.data4_[2] = buf[5];
		guid.data4_[3] = buf[4];
		guid.data4_[4] = buf[3];
		guid.data4_[5] = buf[2];
		guid.data4_[6] = buf[1];
		guid.data4_[7] = buf[0];
		return guid;
	}

}
