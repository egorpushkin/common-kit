/*
 * File name   : IMessage.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-02-11  Egor Pushkin        Initial version
 */

#ifndef IMESSAGE_H__MINCOM__INCLUDED_
#define IMESSAGE_H__MINCOM__INCLUDED_

namespace MinCOM
{

	interface IMessage : public mc::ICommon
	{

		typedef Guid Code_;

		typedef unsigned long Marker_;

		typedef size_t Size_;

		typedef unsigned long Property_;

		virtual Code_ GetCode() = 0;

		virtual Size_ GetSize() = 0;

		virtual Size_ GetDataSize() = 0;

		virtual void PutProperty(Property_ property, const Variant& value) = 0;

		virtual Variant& GetProperty(Property_ property) = 0;

/*		virtual result Write(std::ostream& stream) = 0;

		virtual result Write(asio::streambuf& stream) = 0; */

		virtual result Write(IConnectionRef connection) = 0;

//		virtual result Read(std::istream& stream) = 0;

//		virtual result Read(asio::streambuf& stream) = 0;

		virtual result Read(IConnectionRef connection) = 0;

	};

	typedef Strong< IMessage > IMessagePtr;
	typedef const IMessagePtr& IMessageRef;

	extern const IMessage::Marker_ beginningMarker;

	extern const IMessage::Marker_ endingMarker;

}

#endif // !IMESSAGE_H__MINCOM__INCLUDED_
