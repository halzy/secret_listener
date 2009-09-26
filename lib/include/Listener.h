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

#ifndef LISTENER_H_
#define LISTENER_H_

#include "PacketDevice.h"
#include "WrapPcap.h"
#include "PacketHandler.h"

namespace secret_listener
{

class Listener
{
public:
	Listener(const PacketDevice& device, PacketHandler& handler);
	virtual ~Listener();

	void capture();
	void stop();

private:

	static void pcap_loop_callback(u_char *user, const struct pcap_pkthdr *header, const u_char *bytes)
	{
		Listener* listener = reinterpret_cast<Listener*> (user);
		WrapPtr wrap(new WrapPcap(listener->pcap_device.getDatalinkType(), header, bytes));
		listener->packetHandler(wrap);
	}

	void packetHandler(WrapPtr wrap);

	// [bgh] we do not want people to copy this object
	Listener(Listener const&);
	Listener& operator=(Listener const&);

	const PacketDevice& pcap_device;
	PacketHandler& packet_handler;
}
;

}

#endif /* LISTENER_H_ */
