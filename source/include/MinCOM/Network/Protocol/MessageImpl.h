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

		/** 
		 * Tool to serialize variable of type T from stream.
		 */
		template< class T >
		static std::istream& Read(std::istream& stream, T& value)
		{
			return stream.read((char*)&value, sizeof(value));
		}

		/** 
		 * Tool to serialize variable of type T to stream.
		 */
		template< class T >
		static std::ostream& Write(std::ostream& stream, const T& value)
		{
			return stream.write((char*)&value, sizeof(value));
		}

		/** 
		 * Tool to serialize variable of type std::string from stream.
		 */
		static std::istream& Read(std::istream& stream, std::string& value)
		{
			size_t dataSize = 0;
			Read(stream, dataSize);
			
			std::string::value_type * buffer = new std::string::value_type[dataSize];
			stream.read(buffer, (std::streamsize)dataSize);			
			std::string rvalue;
			if ( '\x0' == buffer[dataSize - 1] )
				rvalue = std::string(buffer);
			else
				rvalue = std::string(buffer, dataSize);
			delete []buffer;

			value = rvalue;

			return stream;
		}

		/**
		 * Tool to serialize variable of std::string type to stream.
		 */ 
		static std::ostream& Write(std::ostream& stream, const std::string& value)
		{
			size_t dataSize = SizeOf( value );
			Write(stream, dataSize);	
			return stream.write(value.c_str(), (std::streamsize)dataSize);
		}

		/**  
		 * Tool to determine size (in bytes of stream) to transfer variable of 
		 * type T.
		 */
		template< class T >
		static size_t SizeOf(const T& param = T())
		{
			return sizeof( T );
		}

		/**  
		 * Tool to determine size (in bytes of stream) to transfer the contents
		 * of std::string variable. This tool calculates size required to 
		 * serialize the contents of string (with terminator at the end). 
		 * It does not takes into account overhead caused by additional size 
		 * field usually preceding actual string data.
		 */
		static size_t SizeOf(const std::string& param = std::string())
		{
			return 
				// Size of actual string data (including '\x0' terminator).
				( param.size() + 1 ) * sizeof( std::string::value_type );
		}

	public:

		friend class Protocol;

		MessageImpl();

		MessageImpl(IMessage::CodeRef_ code);

		// IMessage section
		virtual Code_ GetCode();

		virtual Size_ GetSize();

		virtual Size_ GetDataSize();

		virtual void PutProperty(Property_ property, const Variant& value);

		virtual Variant& GetProperty(Property_ property);

		virtual result Write(std::ostream& stream);

		virtual result Read(std::istream& stream);

	private:

		virtual void SetCode(const Code_& code);

	protected:

		// Protected wrappers
		virtual result WriteHeader(std::ostream& stream);

		virtual result WriteFooter(std::ostream& stream);

		virtual result ReadHeader(std::istream& stream);

		virtual result ReadFooter(std::istream& stream);

	protected:

		virtual result WriteBody(std::ostream& stream);

		virtual result ReadBody(std::istream& stream);

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
