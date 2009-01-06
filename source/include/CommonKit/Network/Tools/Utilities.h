#ifndef UTILITIES_H__NETWORK__COMMONKIT__INCLUDED_
#define UTILITIES_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	template< class T >
	std::istream& Read(std::istream& stream, T& value)
	{
		return stream.read((char*)&value, sizeof(value));
	}

	template< class T >
	std::ostream& Write(std::ostream& stream, const T& value)
	{
		return stream.write((char*)&value, sizeof(value));
	}

}

#endif // !UTILITIES_H__NETWORK__COMMONKIT__INCLUDED_
