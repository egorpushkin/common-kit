#ifndef MESSAGEIMPL_H__NETWORK__COMMONKIT__INCLUDED_
#define MESSAGEIMPL_H__NETWORK__COMMONKIT__INCLUDED_

namespace Network
{

	class MessageImpl
		: public mc::CommonImpl< IMessage >
	{
	public:

		friend class Protocol;

		MessageImpl(IMessage::Code_ code);

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IMessage section
		virtual Code_ GetCode();

		virtual Size_ GetSize();

		virtual void PutProperty(Property_ property, const mc::Variant& value);

		virtual mc::Variant& GetProperty(Property_ property);

		virtual mc::result Write(std::ostream& stream);

		virtual mc::result Write(asio::streambuf& stream);

		virtual mc::result Write(Network::IClientRef client);

		virtual mc::result Read(std::istream& stream);

		virtual mc::result Read(asio::streambuf& stream);

		virtual mc::result Read(Network::IClientRef client);

	protected:

		// Protected wrappers
		virtual mc::result WriteHeader(std::ostream& stream);

		virtual mc::result WriteFooter(std::ostream& stream);

		virtual mc::result ReadHeader(std::istream& stream);

		virtual mc::result ReadFooter(std::istream& stream);

	protected:

		virtual mc::result WriteBody(std::ostream& stream) = 0;

		virtual mc::result ReadBody(std::istream& stream) = 0;

	private:

		class MsgHeader_
		{
		public:

			MsgHeader_();

			bool Read(asio::streambuf& buffer);			

			IMessage::Size_ GetSize() const;
			
			IMessage::Code_ GetCode() const;

		private:

			IMessage::Marker_ marker_;

			IMessage::Size_ size_;

			IMessage::Code_ code_;

		};

	private:

		// Static tools
		static IMessage::Size_ GetHeaderSize();

		static IMessage::Size_ GetWrapperSize();

		static bool IsMsgBodyReady(size_t available, const MsgHeader_& header);

	private:

		IMessage::Code_ code_;

		bool constructed_;

		typedef std::map< Property_, mc::Variant > Properties_;

		Properties_ properties_;

	};

}

#endif // !MESSAGEIMPL_H__NETWORK__COMMONKIT__INCLUDED_
