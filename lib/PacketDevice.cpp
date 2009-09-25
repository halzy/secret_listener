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

#include "PacketDevice.h"
#include "PacketExceptions.h"

#include <iostream>

namespace secret_listener
{

PacketDevice::PacketDevice(const std::string& device) : name(device)
{
	char pcap_errorbuf[PCAP_ERRBUF_SIZE + 1] = "";

	// [bgh] false == not promiscuous mode
	if (!(pcap_handle = pcap_open_live(device.c_str(), MAX_SNAPLEN, false, 0, pcap_errorbuf)))
	{
		throw pcap_open_error() << pt_error_info(std::string(pcap_errorbuf));
	}

	datalink_type = pcap_datalink(pcap_handle);
	datalink_type_description = std::string(pcap_datalink_val_to_description(datalink_type));
}

void
PacketDevice::setPacketFilter(const std::string& filter)
{
	char pcap_errorbuf[PCAP_ERRBUF_SIZE + 1] = "";

	bpf_u_int32 device_netmask;
	bpf_u_int32 device_ip;
	struct bpf_program compiled_filter;

	if (pcap_lookupnet(deviceName().c_str(), &device_ip, &device_netmask, pcap_errorbuf) == -1)
	{
		throw pcap_lookupnet_error() << pt_error_info(std::string(pcap_errorbuf));
	}

	if (pcap_compile(pcap_handle, &compiled_filter, (char*) filter.c_str(), 0, device_ip) == -1)
	{
		throw pcap_compile_error() << pt_error_info(std::string(pcap_geterr(pcap_handle)));
	}

	if (pcap_setfilter(pcap_handle, &compiled_filter) == -1)
	{
		pcap_freecode(&compiled_filter);
		throw pcap_setfilter_error() << pt_error_info(std::string(pcap_geterr(pcap_handle)));
	}
	pcap_freecode(&compiled_filter);
}

PacketDevice::~PacketDevice()
{
	pcap_close(pcap_handle);
	pcap_handle = 0;
}

}
