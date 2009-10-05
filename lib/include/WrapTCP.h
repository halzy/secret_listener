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

#ifndef WRAPTCP_H_
#define WRAPTCP_H_

#include <string>
#include <sstream>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <sys/types.h>

#include "PacketExceptions.h"

namespace secret_listener
{

class WrapTCP
{
public:
	WrapTCP(const u_char * const payload, const int& length);
	virtual ~WrapTCP();
	const u_char * const getPayload() const { return payload; };
	u_int getPayloadLength() const { return payload_length; };

	u_short getSrcPort() const { return ntohs(tcp_header.th_sport); };
	u_short getDstPort() const { return ntohs(tcp_header.th_dport); };
	tcp_seq getSequenceNumber() const { return ntohl(tcp_header.th_seq); };
	tcp_seq getAckNumber() const { return ntohl(tcp_header.th_ack); };
	u_int getDataOffset() const { return tcp_header.th_off * 4; };
	u_char getFlags() const { return tcp_header.th_flags; };
	u_short getWindow() const { return ntohl(tcp_header.th_win); };
	u_short getChecksum() const { return ntohl(tcp_header.th_sum); };
	u_short getUrgentPointer() const { return ntohl(tcp_header.th_urp); };

private:
	const tcphdr tcp_header;
	const u_char * const payload;
	const u_int payload_length;
};

}

#endif /* WRAPTCP_H_ */
