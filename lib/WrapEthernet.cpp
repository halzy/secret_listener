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

#include "WrapEthernet.h"
#include "PacketExceptions.h"

#include "WrapIP.h"

namespace secret_listener
{

WrapEthernet::WrapEthernet(const Wrap* wrap) :
	ethernet(*(struct ether_header*)wrap->getPayload()),
	payload(wrap->getPayload() + sizeof(ether_header)),
	payload_length(wrap->getPayloadLength() - sizeof(ether_header))
{

}

const WrapPtr
WrapEthernet::getWrap() const {
	switch(getType())
	{
	case ETHERTYPE_IP:
		return WrapPtr(new WrapIP(this));
	default:
		throw wrap_unwrap_error() << pt_error_info(std::string("Ethernet does not know how to unwrap " + getType()));
	}
}


WrapEthernet::~WrapEthernet()
{
}

}
