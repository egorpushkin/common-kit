#ifndef IMESSAGE_H__NETWORK__COMMONKIT__INCLUDED_
#define IMESSAGE_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	interface IMessage : public mc::ICommon
	{

		typedef mc::DispId Code_;

		typedef unsigned long Marker_;

		typedef size_t Size_;

		typedef unsigned long Property_;

		virtual Code_ GetCode() = 0;

		virtual Size_ GetSize() = 0;

		virtual Size_ GetDataSize() = 0;

		virtual void PutProperty(Property_ property, const mc::Variant& value) = 0;

		virtual mc::Variant& GetProperty(Property_ property) = 0;

		virtual mc::result Write(std::ostream& stream) = 0;

		virtual mc::result Write(asio::streambuf& stream) = 0;

		virtual mc::result Write(IClientRef client) = 0;

		virtual mc::result Read(std::istream& stream) = 0;

		virtual mc::result Read(asio::streambuf& stream) = 0;

		virtual mc::result Read(IClientRef client) = 0;

	};

	typedef mc::ComPtr< IMessage > IMessagePtr;
	typedef const IMessagePtr& IMessageRef;

	// {182b74d5-ecac-4285-9c83-86569fdcac80} 
	MC_DEFINE_GUID(IID_IMessage, 
	0x182b74d5, 0xecac, 0x4285, 0x9c, 0x83, 0x86, 0x56, 0x9f, 0xdc, 0xac, 0x80);

	extern const IMessage::Marker_ beginningMarker;

	extern const IMessage::Marker_ endingMarker;

}

#endif // !IMESSAGE_H__NETWORK__COMMONKIT__INCLUDED_
