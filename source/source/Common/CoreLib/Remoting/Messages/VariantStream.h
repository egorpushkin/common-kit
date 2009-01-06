#ifndef VARIANTSTREAM_H__REMOTING__CORELIB__INCLUDED_
#define INVOKEMESSAGE_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class VariantStream
	{
	public:

		VariantStream(mc::Variant& param);

		// Stream tools
		virtual mc::result Write(std::ostream& stream);

		virtual mc::result Read(std::istream& stream);

		// Static helpers
		static size_t SizeOf(const mc::Variant& param);

	private:

		VariantStream& operator=(VariantStream&);

	private:

		mc::Variant& param_;

	};

	// External operators
	std::ostream& operator<<(std::ostream& stream, mc::Variant& param);

	std::istream& operator>>(std::istream& stream, mc::Variant& param);

}

#endif // !VARIANTSTREAM_H__REMOTING__CORELIB__INCLUDED_
