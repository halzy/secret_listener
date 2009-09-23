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

#ifndef PACKETDEVICE_H_
#define PACKETDEVICE_H_

#include <pcap.h>
#include <string>

namespace secret_listener
{

class PacketDevice
{
public:
	PacketDevice(const std::string& device);
	void setPacketFilter(const std::string& filter);
	operator pcap_t*() const {
		return pcap_handle;
	}
	virtual ~PacketDevice();
	std::string deviceName() const { return name; }
	std::string getDatalinkTypeDescription() const { return datalink_type_description; }

private:
	// [bgh] we do not want people to copy this object
	PacketDevice(PacketDevice const&);
	PacketDevice& operator=(PacketDevice const&);

	pcap_t* pcap_handle;
	const std::string name;
	int datalink_type;
	std::string datalink_type_description;
	static unsigned int const MAX_SNAPLEN = 65535;
};

}

#endif /* PACKETDEVICE_H_ */
