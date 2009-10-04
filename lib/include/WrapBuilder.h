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

#ifndef WRAPBUILDER_H_
#define WRAPBUILDER_H_

#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <boost/smart_ptr.hpp>

#include "WrapVariant.h"

namespace secret_listener
{

class WrapBuilder : public boost::static_visitor<WrapVariant>
{
public:
	WrapBuilder();
	virtual ~WrapBuilder();

	virtual WrapVariant operator()(boost::shared_ptr<WrapPcap> pcap);
	virtual WrapVariant operator()(boost::shared_ptr<WrapEthernet> ether);
	virtual WrapVariant operator()(boost::shared_ptr<WrapIP> ip);
	virtual WrapVariant operator()(boost::shared_ptr<WrapTCP> tcp);
	virtual WrapVariant operator()(boost::shared_ptr<WrapPayload> tcp);

};

}

#endif /* WRAPBUILDER_H_ */
