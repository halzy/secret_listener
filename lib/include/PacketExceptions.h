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

#ifndef PACKETEXCEPTIONS_H_
#define PACKETEXCEPTIONS_H_

#include <string>
#include <boost/exception/all.hpp>

namespace secret_listener
{

typedef boost::error_info<struct listener_error_info, std::string> pt_error_info;
struct pcap_link_type_error: virtual boost::exception, virtual std::exception{};
struct pcap_open_error: virtual boost::exception, virtual std::exception{};
struct pcap_lookupnet_error: virtual boost::exception, virtual std::exception{};
struct pcap_compile_error: virtual boost::exception, virtual std::exception{};
struct pcap_setfilter_error: virtual boost::exception, virtual std::exception{};
struct wrap_unwrap_error: virtual boost::exception, virtual std::exception{};

}

#endif /* PACKETEXCEPTIONS_H_ */
