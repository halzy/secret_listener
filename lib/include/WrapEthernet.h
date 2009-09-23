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

#ifndef WRAPETHERNET_H_
#define WRAPETHERNET_H_

#include <netinet/if_ether.h>
#include <string>
#include <sstream>

#include "Wrap.h"

namespace secret_listener
{

class WrapEthernet : public virtual Wrap
{
public:
	WrapEthernet(const Wrap& envelope);
	virtual ~WrapEthernet();
	const u_char* getPayload() const { return payload; };
	const u_int getPayloadLength() const { return payload_length; };
	const u_short getType() const { return ntohs(ethernet.ether_type); };
	const std::string toString() const {
		std::stringstream tostring;
		tostring << "Ethernet: " << std::endl << "\t type: " << getType() << std::endl;
		return tostring.str();
	}
private:
	const struct ether_header ethernet;
	const u_char* payload;
	const u_int payload_length;
};

}

#endif /* WRAPETHERNET_H_ */