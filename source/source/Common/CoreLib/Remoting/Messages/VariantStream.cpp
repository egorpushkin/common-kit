#include "Common/Common.h"

#include "VariantStream.h"

namespace Remoting
{

	VariantStream::VariantStream(mc::Variant& param)
		: param_(param)
	{
	}

	// Stream tools
	mc::result VariantStream::Write(std::ostream& stream)
	{
		mc::Variant::Type_ type = param_.type();
		
		stream.write((const char*)&type, sizeof(unsigned short));

		switch  ( type )
		{
		case mc::CommonVariant::CE_BOOL: 
			{
				bool boolVal = param_.toBool();
				stream.write((const char*)&boolVal, sizeof(bool));
			}
			break;
		case mc::CommonVariant::CE_I4: 
			{
				long lVal = param_.toLong();
				stream.write((const char*)&lVal, sizeof(long));
			}
			break;
		case mc::CommonVariant::CE_R4: 
			{
				float fltVal = param_.toFloat();
				stream.write((const char*)&fltVal, sizeof(float));
			}
			break;
		case mc::CommonVariant::CE_R8: 
			{
				double dblVal = param_.toDouble();
				stream.write((const char*)&dblVal, sizeof(double));
			}
			break;
		case mc::CommonVariant::CE_COMMON: 
			{
				void* pointer = param_.toCommon().GetPointer();
				stream.write((const char*)&pointer, sizeof(void*));
			}
			break;

			// ...


		}

		return mc::_S_OK;
	}

	mc::result VariantStream::Read(std::istream& stream)
	{		
		unsigned short type;
		stream.read((char*)&type, sizeof(unsigned short));

		switch ( type )
		{
		case mc::CommonVariant::CE_BOOL: 
			{
				bool boolVal;
				stream.read((char*)&boolVal, sizeof(bool));	

				param_ = mc::Variant(boolVal);
			}
			break;
		case mc::CommonVariant::CE_I4: 
			{
				long lVal;
				stream.read((char*)&lVal, sizeof(long));	

				param_ = mc::Variant(lVal);
			}
			break;
		case mc::CommonVariant::CE_R4: 
			{
				float fltVal;
				stream.read((char*)&fltVal, sizeof(float));	

				param_ = mc::Variant(fltVal);
			}
			break;
		case mc::CommonVariant::CE_R8: 
			{
				double dblVal;
				stream.read((char*)&dblVal, sizeof(double));	

				param_ = mc::Variant(dblVal);
			}
			break;
		case mc::CommonVariant::CE_COMMON: 
			{
				mc::ICommon* pointer = NULL;
				stream.read((char*)&pointer, sizeof(void*));	

				param_ = mc::Variant(pointer);
			}
			break;

			// ...


		}


		
		return mc::_S_OK;
	}

	// Static helpers
	size_t VariantStream::SizeOf(const mc::Variant& param)
	{
		size_t size = sizeof(unsigned short);

		mc::Variant::Type_ type = param.type();
		switch  ( type )
		{
		case mc::CommonVariant::CE_BOOL: 
			size += sizeof(bool);
			break;
		case mc::CommonVariant::CE_I4: 
			size += sizeof(long);
			break;
		case mc::CommonVariant::CE_R4: 
			size += sizeof(float);
			break;
		case mc::CommonVariant::CE_R8: 
			size += sizeof(double);
			break;
		case mc::CommonVariant::CE_COMMON: 
			size += sizeof(void*);
			break;

			// ...

		}

		return size;
	}

	// External operators
	std::ostream& operator<<(std::ostream& stream, mc::Variant& param)
	{	
		VariantStream vstream(param);
		
		vstream.Write(stream);

		return stream;		
	}		

	std::istream& operator>>(std::istream& stream, mc::Variant& param)
	{
		VariantStream vstream(param);
		
		vstream.Read(stream);

		return stream;		
	}

}
