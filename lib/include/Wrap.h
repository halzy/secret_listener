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

#ifndef WRAP_H_
#define WRAP_H_

#include <sys/types.h>
#include <string>

#include <boost/smart_ptr.hpp>

namespace secret_listener
{

class Wrap
{
public:
	virtual ~Wrap() {}
	virtual const u_char* getPayload() const = 0;
	virtual const u_int getPayloadLength() const = 0;
	virtual const std::string toString() const = 0;
};

typedef boost::shared_ptr<Wrap> WrapPtr;
WrapPtr getLinktypeWrapper(int link_type, const WrapPtr& wrap);

}

#endif /* WRAP_H_ */
