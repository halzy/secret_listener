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

#include <string>
#include <iostream>
#include <boost/exception/all.hpp>
#include <boost/program_options.hpp>

#include "ListDevices.h"
#include "Listener.h"
#include "Arguments.h"
#include "PacketExceptions.h"

#include "AppPacketReceiver.h"

using namespace std;

string create_packet_filter(const string& host, const int& port)
{
	std::stringstream filter_expression;
	filter_expression << "port " << port;
	return filter_expression.str();
}

int main(int argc, char* argv[]) {
	try {

		secret_listener::Arguments args(argc, argv);

		if(args.needsHelp())
		{
			cerr << args.getHelp() << endl;
			return 0;
		}

		if(args.listDevices())
		{
			secret_listener::ListDevices list;
			return 0;
		}

		if (!args.hasDevice())
		{
			cerr << "ERROR: You must specify an device to listen on." << endl;
			return 1;
		}

		secret_listener::PacketDevice device(args.getDevice());
		device.setPacketFilter(create_packet_filter(args.getHost(), args.getPort()));

		cout << "Listening on device(" << args.getDevice() << ":" << device.getDatalinkTypeDescription() << ") host(" << args.getHost() << ") port (" << args.getPort() << ")" << endl << endl;

		secret_listener::AppPacketReceiver receiver;
		secret_listener::Listener listener(device, receiver);
		listener.capture();

	} catch (secret_listener::argument_error& e)
	{
		if ( string const* error_str=boost::get_error_info<secret_listener::arg_error_info>(e) )
		{
			cerr << *error_str << endl;
		}
		return 1;
	} catch (secret_listener::pcap_open_error& e)
	{
		if ( string const* error_str=boost::get_error_info<secret_listener::pt_error_info>(e) )
			cerr << "pcap_open_error: " << *error_str << endl;
	} catch (secret_listener::pcap_lookupnet_error& e)
	{
		if ( string const* error_str=boost::get_error_info<secret_listener::pt_error_info>(e) )
			cerr << "pcap_lookupnet_error: " << *error_str << endl;
	} catch (secret_listener::pcap_compile_error& e)
	{
		if ( string const* error_str=boost::get_error_info<secret_listener::pt_error_info>(e) )
			cerr << "pcap_compile_error: " << *error_str << endl;
	} catch (secret_listener::pcap_setfilter_error& e)
	{
		if ( string const* error_str=boost::get_error_info<secret_listener::pt_error_info>(e) )
			cerr << "pcap_setfilter_error: " << *error_str << endl;
	}

	return 0;
}

