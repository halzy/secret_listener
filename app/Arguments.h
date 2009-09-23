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

#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <boost/exception/all.hpp>
#include <boost/program_options.hpp>
#include <string>

using namespace std;

namespace secret_listener
{

typedef boost::error_info<struct arguments_error_info, std::string> arg_error_info;
struct argument_error: virtual boost::exception, virtual std::exception{};

class Arguments
{
public:
	explicit Arguments(int argc, char ** argv);
	explicit Arguments(const Arguments& args);
	Arguments& operator = (const Arguments & other);
	virtual ~Arguments();
	bool needsHelp() const { return needs_help; };
	bool listDevices() const { return list_devices; };
	string getHelp() const { return help; };
	bool hasDevice() const { return !device.empty(); };
	string getDevice() const { return device; };
	string getHost() const { return host; };
	int getPort() const { return port; };
private:
	string help;
	int port;
	string host;
	string device;
	bool needs_help;
	bool list_devices;
};
}

#endif /* ARGUMENTS_H_ */
