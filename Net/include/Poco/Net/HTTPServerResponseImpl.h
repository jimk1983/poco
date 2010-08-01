//
// HTTPServerResponseImpl.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/HTTPServerResponseImpl.h#2 $
//
// Library: Net
// Package: HTTPServer
// Module:  HTTPServerResponseImpl
//
// Definition of the HTTPServerResponseImpl class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Net_HTTPServerResponseImpl_INCLUDED
#define Net_HTTPServerResponseImpl_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPServerResponse.h"


namespace Poco {
namespace Net {


class HTTPServerSession;
class HTTPCookie;


class Net_API HTTPServerResponseImpl: public HTTPServerResponse
	/// This subclass of HTTPServerResponse is used for
	/// representing server-side HTTP responses.
	///
	/// A HTTPServerResponse is passed to the
	/// handleRequest() method of HTTPRequestHandler.
	///
	/// handleRequest() must set a status code
	/// and optional reason phrase, set headers
	/// as necessary, and provide a message body.
{
public:
	HTTPServerResponseImpl(HTTPServerSession& session);
		/// Creates the HTTPServerResponseImpl.

	~HTTPServerResponseImpl();
		/// Destroys the HTTPServerResponseImpl.

	void sendContinue();
		/// Sends a 100 Continue response to the
		/// client.
		
	std::ostream& send();
		/// Sends the response header to the client and
		/// returns an output stream for sending the
		/// response body.
		///
		/// The returned stream is valid until the response
		/// object is destroyed.
		///
		/// Must not be called after sendFile(), sendBuffer() 
		/// or redirect() has been called.
		
	void sendFile(const std::string& path, const std::string& mediaType);
		/// Sends the response header to the client, followed
		/// by the content of the given file.
		///
		/// Must not be called after send(), sendBuffer() 
		/// or redirect() has been called.
		///
		/// Throws a FileNotFoundException if the file
		/// cannot be found, or an OpenFileException if
		/// the file cannot be opened.
		
	void sendBuffer(const void* pBuffer, std::size_t length);
		/// Sends the response header to the client, followed
		/// by the contents of the given buffer.
		///
		/// The Content-Length header of the response is set
		/// to length and chunked transfer encoding is disabled.
		///
		/// If both the HTTP message header and body (from the
		/// given buffer) fit into one single network packet, the 
		/// complete response can be sent in one network packet.
		///
		/// Must not be called after send(), sendFile()  
		/// or redirect() has been called.
		
	void redirect(const std::string& uri, HTTPStatus status = HTTP_FOUND);
		/// Sets the status code, which must be one of
		/// HTTP_MOVED_PERMANENTLY (301), HTTP_FOUND (302),
		/// or HTTP_SEE_OTHER (303),
		/// and sets the "Location" header field
		/// to the given URI, which according to
		/// the HTTP specification, must be absolute.
		///
		/// Must not be called after send() has been called.
		
	void requireAuthentication(const std::string& realm);
		/// Sets the status code to 401 (Unauthorized)
		/// and sets the "WWW-Authenticate" header field
		/// according to the given realm.
		
	bool sent() const;
		/// Returns true if the response (header) has been sent.

private:
	HTTPServerSession& _session;
	std::ostream*      _pStream;
};


//
// inlines
//
inline bool HTTPServerResponseImpl::sent() const
{
	return _pStream != 0;
}


} } // namespace Poco::Net


#endif // Net_HTTPServerResponseImpl_INCLUDED
