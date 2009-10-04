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

#ifndef WRAPVARIANTISA_H_
#define WRAPVARIANTISA_H_

#include <boost/type_traits/is_same.hpp>

#include "WrapPcap.h"
#include "WrapEthernet.h"
#include "WrapIP.h"
#include "WrapTCP.h"
#include "WrapPayload.h"

namespace secret_listener
{

template<typename T>
class WrapVariantIsA : public boost::static_visitor<bool>
{
public:
	WrapVariantIsA() {};
	~WrapVariantIsA() {};

	bool operator()(boost::shared_ptr<WrapPcap>& pcap) const
	{ return (boost::is_same<T, WrapPcap>::value); }
	bool operator()(boost::shared_ptr<WrapEthernet>& ether) const
	{ return (boost::is_same<T, WrapEthernet>::value); }
	bool operator()(boost::shared_ptr<WrapIP>& ip) const
	{ return (boost::is_same<T, WrapIP>::value); }
	bool operator()(boost::shared_ptr<WrapTCP>& tcp) const
	{ return (boost::is_same<T, WrapTCP>::value); }
	bool operator()(boost::shared_ptr<WrapPayload>& tcp) const
	{ return (boost::is_same<T, WrapPayload>::value); }

};

}

#endif /* WRAPVARIANTISA_H_ */
