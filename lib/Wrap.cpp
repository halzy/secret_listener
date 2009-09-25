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

#include <pcap.h>

#include "Wrap.h"
#include "PacketExceptions.h"
#include "WrapEthernet.h"

namespace secret_listener
{

WrapPtr getLinktypeWrapper(int link_type, const WrapPtr& wrap)
{
	switch(link_type)
	{
	case DLT_EN10MB:
		return WrapPtr(new WrapEthernet(wrap));
		break;
	default:
		throw pcap_link_type_error() << pt_error_info("No support for link type: " + link_type);
	}
}

}
