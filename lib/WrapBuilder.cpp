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

#include <boost/smart_ptr/shared_ptr.hpp>

#include "WrapBuilder.h"

namespace secret_listener
{

WrapBuilder::WrapBuilder()
{

}

WrapBuilder::~WrapBuilder()
{

}


WrapVariant
WrapBuilder::operator()(boost::shared_ptr<WrapPcap> pcap)
{
	switch(pcap->getLinkType())
	{
	case DLT_EN10MB:
		return boost::shared_ptr<WrapEthernet>(new WrapEthernet(pcap->getPayload(), pcap->getPayloadLength()));
	}
	return boost::shared_ptr<WrapPayload>(new WrapPayload(pcap->getPayload(), pcap->getPayloadLength()));
}

WrapVariant
WrapBuilder::operator()(boost::shared_ptr<WrapEthernet> ether)
{
	switch(ether->getType())
	{
	case ETHERTYPE_IP:
		return boost::shared_ptr<WrapIP>(new WrapIP(ether->getPayload(), ether->getPayloadLength()));
	}
	return boost::shared_ptr<WrapPayload>(new WrapPayload(ether->getPayload(), ether->getPayloadLength()));
}

WrapVariant
WrapBuilder::operator()(boost::shared_ptr<WrapIP> ip)
{
	switch(ip->getProtocol())
	{
	case IPPROTO_TCP:
		return boost::shared_ptr<WrapTCP>(new WrapTCP(ip->getPayload(), ip->getPayloadLength()));
	}
	return boost::shared_ptr<WrapPayload>(new WrapPayload(ip->getPayload(), ip->getPayloadLength()));
}

WrapVariant
WrapBuilder::operator()(boost::shared_ptr<WrapTCP> tcp)
{
	return boost::shared_ptr<WrapPayload>(new WrapPayload(tcp->getPayload(), tcp->getPayloadLength()));
}

WrapVariant
WrapBuilder::operator()(boost::shared_ptr<WrapPayload> payload)
{
	throw wrap_unwrap_error() << pt_error_info(std::string("Already at the lowest possible level."));
}

}
