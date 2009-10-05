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

#ifndef WRAPPCAP_H_
#define WRAPPCAP_H_

#include <string>
#include <sstream>

#include <pcap.h>

#include "PcapPayload.h"

namespace secret_listener
{

class WrapPcap
{
public:
	WrapPcap(const int& link_type, const struct pcap_pkthdr *header, const u_char *bytes);
	virtual ~WrapPcap();

	const u_char* getPayload() const { return payload; };
	const u_int getPayloadLength() const { return header.caplen; };
	const u_int getPacketLength() const { return header.len; };
	const struct timeval getTime() const { return header.ts; };
	const int getLinkType() const { return link_type; };

private:
	int link_type;
	struct pcap_pkthdr header;
	PcapPayload payload;
};

}

#endif /* WRAPPCAP_H_ */
