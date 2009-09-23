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

#include "ListDevices.h"
#include "PacketExceptions.h"

#include <iostream>

namespace secret_listener
{

ListDevices::ListDevices()
{
	if(-1 == pcap_findalldevs(&all_devices, pcap_errorbuf))
	{
		throw pcap_open_error() << pt_error_info(std::string(pcap_errorbuf));
	}

	pcap_if_t* dev = all_devices;
	while(dev != 0)
	{
		std::cout << dev->name << std::endl;
		dev = dev->next;
	}

}

ListDevices::~ListDevices()
{
	pcap_freealldevs(all_devices);
}

}
