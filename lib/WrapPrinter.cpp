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

#include "WrapPrinter.h"
#include "WrapVariant.h"

namespace secret_listener
{

void hexdump(void *pAddressIn, long  lSize)
{
 char szBuf[100];
 long lIndent = 1;
 long lOutLen, lIndex, lIndex2, lOutLen2;
 long lRelPos;
 struct { char *pData; unsigned long lSize; } buf;
 unsigned char *pTmp,ucTmp;
 unsigned char *pAddress = (unsigned char *)pAddressIn;

   buf.pData   = (char *)pAddress;
   buf.lSize   = lSize;

   while (buf.lSize > 0)
   {
      pTmp     = (unsigned char *)buf.pData;
      lOutLen  = (int)buf.lSize;
      if (lOutLen > 16)
          lOutLen = 16;

      // create a 64-character formatted output line:
      sprintf(szBuf, " >                            "
                     "                      "
                     "    %08dX", pTmp-pAddress);
      lOutLen2 = lOutLen;

      for(lIndex = 1+lIndent, lIndex2 = 53-15+lIndent, lRelPos = 0;
          lOutLen2;
          lOutLen2--, lIndex += 2, lIndex2++
         )
      {
         ucTmp = *pTmp++;

         sprintf(szBuf + lIndex, "%02X ", (unsigned short)ucTmp);
         if(!isprint(ucTmp))  ucTmp = '.'; // nonprintable char
         szBuf[lIndex2] = ucTmp;

         if (!(++lRelPos & 3))     // extra blank after 4 bytes
         {  lIndex++; szBuf[lIndex+2] = ' '; }
      }

      if (!(lRelPos & 3)) lIndex--;

      szBuf[lIndex  ]   = '<';
      szBuf[lIndex+1]   = ' ';

      printf("%s\n", szBuf);

      buf.pData   += lOutLen;
      buf.lSize   -= lOutLen;
   }
}

WrapPrinter::WrapPrinter(std::ostream& output) :
	outstream(output)
{

}

WrapPrinter::~WrapPrinter()
{

}
void
WrapPrinter::operator()(const boost::shared_ptr<WrapPcap>& pcap) const
{
	outstream << "PCAP: " << std::endl << "\tts: " << pcap->getTime().tv_sec << "." << pcap->getTime().tv_usec << std::endl;
	outstream << "\tcaplen: " << pcap->getPayloadLength() << ", len: " << pcap->getPacketLength() << std::endl;

}

void
WrapPrinter::operator()(const boost::shared_ptr<WrapEthernet>& ether) const
{
	outstream << "Ethernet: " << std::endl << "\t type: " << ether->getType() << std::endl;
}

void
WrapPrinter::operator()(const boost::shared_ptr<WrapIP>& ip) const
{
	outstream << "IP: " << std::endl << "\tsrc: " << ip->getSrcAddressString() << " dst:" << ip->getDstAddressString() << std::endl;
	outstream << "\thead_len: " << ip->getHeaderLength() << ", ver: " << ip->getVersion() << std::endl;
	outstream << "\tip_len: " << ip->getLength() << ", payload_len: " << ip->getPayloadLength() << std::endl;
}

void
WrapPrinter::operator()(const boost::shared_ptr<WrapTCP>& tcp) const
{
	outstream << "TCP: " << std::endl << "\tsrc_port: " << tcp->getSrcPort() << " dst_port:" << tcp->getDstPort() << std::endl;
	outstream << "\tseq#: " << tcp->getSequenceNumber() << ", ack: " << tcp->getAckNumber() << std::endl;
	outstream << "\tdata_offset: " << tcp->getDataOffset() << ", payload_len: " << tcp->getPayloadLength() << std::endl;
}

void
WrapPrinter::operator()(const boost::shared_ptr<WrapPayload>& payload) const
{
	std::cout << "Payload:" << std::endl;
	hexdump((void*)payload->getPayload(), payload->getPayloadLength());
}

}
