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

#include "Arguments.h"

namespace po = boost::program_options;

namespace secret_listener
{

Arguments::Arguments(int argc, char ** argv)
{
	po::options_description cmdline_options("Parameters");
	po::variables_map variable_map;

	cmdline_options.add_options()
		("help", "produce help message")
		("list", "lists the available devices to listen on")
		("device", po::value<string>(&device), "network device to listen on")
		("host", po::value<string>(&host)->default_value("all"), "the IP address of the server")
		("port", po::value<int>(&port)->default_value(8080), "port to listen on")
	;

	po::positional_options_description positional_options;
	positional_options.add("device", 1);
	positional_options.add("port", 1);

	try
	{
		po::store(po::command_line_parser(argc, argv).options(cmdline_options).positional(positional_options).run(), variable_map);
	} catch (po::invalid_option_value iov)
	{
		throw argument_error() << arg_error_info(iov.what());
	}
	po::notify(variable_map);

	needs_help = 0 != variable_map.count("help");
	list_devices = 0 != variable_map.count("list");

	std::stringstream help_string;
	help_string << cmdline_options;
	help = help_string.str();
}

Arguments::Arguments(const Arguments& args) :
	help(args.getHelp()), port(args.getPort()), host(args.getHost()), device(args.getDevice()), needs_help(args.needsHelp())
{

}

Arguments&
Arguments::operator = (const Arguments & other)
{
    if (this != &other) // protect against invalid self-assignment
    {
    	help = other.getHelp();
    	port = other.getPort();
    	host = other.getHost();
    	device = other.getDevice();
    	needs_help = other.needsHelp();
    }

    // by convention, always return *this
    return *this;
}


Arguments::~Arguments()
{
}


}
