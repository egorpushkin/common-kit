#include "Common/Common.h"

namespace Network
{

	const IMessage::Marker_ beginningMarker = 0xfefefefe;

	const IMessage::Marker_ endingMarker = 0xcdcdcdcd;

	MessageImpl::MessageImpl(IMessage::Code_ code)
		: mc::CommonImpl< IMessage >()
		, code_(code)
		, constructed_(false)
		, properties_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(MessageImpl)
		COMMON(IMessage)
		INTERFACE(IMessage)
	END_INTERFACE_MAP()		

	// IMessage section
	IMessage::Code_ MessageImpl::GetCode()
	{
		return code_;
	}

	IMessage::Size_ MessageImpl::GetSize()
	{
		return 
			GetWrapperSize() + 
			GetDataSize();
	}

	void MessageImpl::PutProperty(Property_ property, const mc::Variant& value)
	{
		Properties_::iterator propPos = properties_.find(property);
		if ( properties_.end() != propPos )
		{
			(*propPos).second = value;
			return;
		}

		properties_.insert(Properties_::value_type(property, value));
	}

	mc::Variant& MessageImpl::GetProperty(Property_ property)
	{
		Properties_::iterator propPos = properties_.find(property);
		if ( properties_.end() == propPos )
			throw std::out_of_range("Wrong property");

		return (*propPos).second;
	}

	mc::result MessageImpl::Write(std::ostream& stream)
	{
		if ( mc::IsFailed(WriteHeader(stream)) )
			return mc::_E_FAIL;

		if ( mc::IsFailed(WriteBody(stream)) )
			return mc::_E_FAIL;

		if ( mc::IsFailed(WriteFooter(stream)) )
			return mc::_E_FAIL;

		return mc::_S_OK;
	}

	mc::result MessageImpl::Write(asio::streambuf& stream)
	{
		std::ostream output_stream(&stream);
		return Write(output_stream);
	}

	mc::result MessageImpl::Write(Network::IClientRef client)
	{
		if ( !client )
			return mc::_E_FAIL;

		asio::streambuf message_buffer;		
		if ( mc::IsFailed(Write(message_buffer)) )
			return mc::_E_FAIL;

		return client->Write(message_buffer);
	}

	mc::result MessageImpl::Read(std::istream& stream)
	{
		constructed_ = false;

		if ( mc::IsFailed(ReadHeader(stream)) )
			return mc::_E_FAIL;

		if ( mc::IsFailed(ReadBody(stream)) )
			return mc::_E_FAIL;

		if ( mc::IsFailed(ReadFooter(stream)) )
			return mc::_E_FAIL;

		constructed_ = true;

		return mc::_S_OK;
	}

	mc::result MessageImpl::Read(asio::streambuf& stream)
	{
		std::istream input_stream(&stream);
		return Read(input_stream);
	}

	mc::result MessageImpl::Read(Network::IClientRef client)
	{
		if ( !client )
			return mc::_E_FAIL;

		client->Read();

		return Read(client->GetBuffer());
	}

	// Protected wrappers
	mc::result MessageImpl::WriteHeader(std::ostream& stream)
	{
		stream.write((const char*)&beginningMarker, sizeof(IMessage::Marker_));
		
		IMessage::Size_ msgSize = GetSize();
		stream.write((const char*)&msgSize, sizeof(IMessage::Size_));

		stream.write((const char*)&code_, sizeof(IMessage::Code_));

		return mc::_S_OK;
	}

	mc::result MessageImpl::WriteFooter(std::ostream& stream)
	{
		stream.write((const char*)&endingMarker, sizeof(IMessage::Marker_));

		return mc::_S_OK;
	}

	mc::result MessageImpl::ReadHeader(std::istream& /* stream */)
	{
		return mc::_S_OK;
	}

	mc::result MessageImpl::ReadFooter(std::istream& stream)
	{
		IMessage::Marker_ ending;
		stream.read((char*)&ending, sizeof(IMessage::Marker_));

		if ( ending != endingMarker )
			return mc::_E_FAIL;

		return mc::_S_OK;
	}

	// Static tools
	IMessage::Size_ MessageImpl::GetHeaderSize()
	{
		return	
			sizeof(IMessage::Marker_) + 
			sizeof(IMessage::Size_) + 
			sizeof(IMessage::Code_);
	}

	IMessage::Size_ MessageImpl::GetWrapperSize()
	{
		return	
			GetHeaderSize() + 
			sizeof(IMessage::Marker_);
	}

	bool MessageImpl::IsMsgBodyReady(size_t available, const MsgHeader_& header)
	{
		return ( available >= ( header.GetSize() - GetHeaderSize() ) );
	}

	// MsgHeader_
	////////////////////////////////////////////////////////////////////////// 
	MessageImpl::MsgHeader_::MsgHeader_()
		: marker_()
		, size_(0)
		, code_(0)
	{
	}

	bool MessageImpl::MsgHeader_::Read(asio::streambuf& buffer)
	{
		std::istream stream(&buffer);

		Network::Read(stream, marker_);
		Network::Read(stream, size_);
		Network::Read(stream, code_);

		if ( beginningMarker != marker_ )
			return false;

		return true;
	}
	
	IMessage::Size_ MessageImpl::MsgHeader_::GetSize() const
	{
		return size_;
	}

	IMessage::Code_ MessageImpl::MsgHeader_::GetCode() const
	{
		return code_;
	}

}
