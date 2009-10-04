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

#ifndef WRAPVARIANT_H_
#define WRAPVARIANT_H_

#include <boost/mpl/vector.hpp>
#include <boost/variant.hpp>
#include <vector>

#include "WrapPcap.h"
#include "WrapEthernet.h"
#include "WrapIP.h"
#include "WrapTCP.h"
#include "WrapPayload.h"

namespace secret_listener
{
	typedef boost::mpl::vector< boost::shared_ptr<WrapPcap> > _vector_wrap_pcap;
	typedef boost::mpl::push_front< _vector_wrap_pcap, boost::shared_ptr<WrapEthernet> >::type _vector_wrap_ethernet;
	typedef boost::mpl::push_front< _vector_wrap_ethernet, boost::shared_ptr<WrapIP> >::type _vector_wrap_ip;
	typedef boost::mpl::push_front< _vector_wrap_ip, boost::shared_ptr<WrapTCP> >::type _vector_wrap_tcp;
	typedef boost::mpl::push_front< _vector_wrap_tcp, boost::shared_ptr<WrapPayload> >::type _vector_wrap_payload;
	typedef boost::make_variant_over< _vector_wrap_payload >::type WrapVariant;

	typedef std::vector<WrapVariant> WrapList;
}

#endif /* WRAPVARIANT_H_ */
