/*
 * File name   : MessageImpl.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-11  Egor Pushkin        Initial version
 */

#ifndef MESSAGEIMPL_H__MINCOM__INCLUDED_
#define MESSAGEIMPL_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class MessageImpl
		: public CommonImpl< IMessage >
	{
	public:

		template< class T >
		static std::istream& Read(std::istream& stream, T& value)
		{
			return stream.read((char*)&value, sizeof(value));
		}

		template< class T >
		static std::ostream& Write(std::ostream& stream, const T& value)
		{
			return stream.write((char*)&value, sizeof(value));
		}

	public:

		friend class Protocol;

		MessageImpl(IMessage::Code_ code);

		// IMessage section
		virtual Code_ GetCode();

		virtual Size_ GetSize();

		virtual void PutProperty(Property_ property, const Variant& value);

		virtual Variant& GetProperty(Property_ property);

		virtual result Write(std::ostream& stream);

		virtual result Read(std::istream& stream);

	protected:

		// Protected wrappers
		virtual result WriteHeader(std::ostream& stream);

		virtual result WriteFooter(std::ostream& stream);

		virtual result ReadHeader(std::istream& stream);

		virtual result ReadFooter(std::istream& stream);

	protected:

		virtual result WriteBody(std::ostream& stream) = 0;

		virtual result ReadBody(std::istream& stream) = 0;

	private:

		class MsgHeader_
		{
		public:

			MsgHeader_();

			bool Read(std::istream& buffer);			

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

		typedef std::map< Property_, Variant > Properties_;

		Properties_ properties_;

	};

}

#endif // !MESSAGEIMPL_H__MINCOM__INCLUDED_
