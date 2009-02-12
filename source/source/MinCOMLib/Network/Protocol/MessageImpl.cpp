#include "Common/Common.h"

namespace MinCOM
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
		if ( Error::IsFailed(WriteHeader(stream)) )
			return mc::_E_FAIL;

		if ( Error::IsFailed(WriteBody(stream)) )
			return mc::_E_FAIL;

		if ( Error::IsFailed(WriteFooter(stream)) )
			return mc::_E_FAIL;

		return mc::_S_OK;
	}

	mc::result MessageImpl::Read(std::istream& stream)
	{
		constructed_ = false;

		if ( Error::IsFailed(ReadHeader(stream)) )
			return mc::_E_FAIL;

		if ( Error::IsFailed(ReadBody(stream)) )
			return mc::_E_FAIL;

		if ( Error::IsFailed(ReadFooter(stream)) )
			return mc::_E_FAIL;

		constructed_ = true;

		return mc::_S_OK;
	}

	// Protected wrappers
	mc::result MessageImpl::WriteHeader(std::ostream& stream)
	{
		IMessage::Size_ msgSize = GetSize();

		MessageImpl::Write(stream, beginningMarker);
		MessageImpl::Write(stream, msgSize);
		MessageImpl::Write(stream, code_);

		return mc::_S_OK;
	}

	mc::result MessageImpl::WriteFooter(std::ostream& stream)
	{
		MessageImpl::Write(stream, endingMarker);

		return mc::_S_OK;
	}

	mc::result MessageImpl::ReadHeader(std::istream& /* stream */)
	{
		return mc::_S_OK;
	}

	mc::result MessageImpl::ReadFooter(std::istream& stream)
	{
		IMessage::Marker_ ending;
		MessageImpl::Read(stream, ending);

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
		, code_()
	{
	}

	bool MessageImpl::MsgHeader_::Read(std::istream& stream)
	{
		MessageImpl::Read(stream, marker_);
		MessageImpl::Read(stream, size_);
		MessageImpl::Read(stream, code_);

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
