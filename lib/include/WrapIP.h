/*
Copyright (c) 2009 Benjamin G. Halsted

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef WRAPIP_H_
#define WRAPIP_H_

#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "WrapEthernet.h"

namespace secret_listener
{

class WrapIP
{
public:
	WrapIP(const u_char* const payload, const int& length);
	virtual ~WrapIP();
	const u_char * const getPayload() const { return payload; };
	u_int getPayloadLength() const { return payload_length; };

	u_int getHeaderLength() const { return internet_protocol.ip_hl*4; };
	u_int getVersion() const { return internet_protocol.ip_v; };
	u_char getTOS() const { return internet_protocol.ip_tos; };
	u_short getLength() const { return ntohs(internet_protocol.ip_len); };
	u_short getID() const { return ntohs(internet_protocol.ip_id); };
	u_short getFragmentOffset() const { return ntohs(internet_protocol.ip_off); };
	u_char getTTL() const { return internet_protocol.ip_ttl; };
	u_char getProtocol() const { return internet_protocol.ip_p; };
	u_short getChecksum() const { return ntohs(internet_protocol.ip_sum); };
	const in_addr getSrcAddress() const { return internet_protocol.ip_src; };
	const in_addr getDstAddress() const { return internet_protocol.ip_dst; };
	const std::string getSrcAddressString() const { return src_address; };
	const std::string getDstAddressString() const { return dst_address; };

private:
	const struct ip internet_protocol;
	const u_char * const payload;
	const u_int payload_length;
	const std::string dst_address;
	const std::string src_address;
};

}

#endif /* WRAPIP_H_ */
