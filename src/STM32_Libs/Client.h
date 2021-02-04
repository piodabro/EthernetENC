/*
  Client.h - Base class that provides Client
  Copyright (c) 2011 Adrian McEwen.  All right reserved.

  Modified (ported to mbed) by Zoltan Hudak <hudakz@inbox.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef client_h
#define client_h

#include "IPAddress.h"
#include "Stream.h"
#include "millis.h"

class Client : public Stream
{
public:
    virtual ~Client(){};
    virtual int         connect(IPAddress ip, uint16_t port) = 0;
    virtual int         connect(const char* host, uint16_t port) = 0;
    virtual int 		connectNonBlocking(IPAddress ip, uint16_t port) = 0;
    virtual int 		connectUpdate() = 0;
    virtual size_t      write(uint8_t) = 0;
    virtual size_t      write(const uint8_t* buf, size_t size) = 0;
    virtual int         available(void) = 0;
    virtual int         read(void) = 0;
    virtual int         read(uint8_t* buf, size_t size) = 0;
    virtual int         peek(void) = 0;
    virtual void        flush(void) = 0;
    virtual void        stop(void) = 0;
    virtual uint8_t     connected(void) = 0;
    virtual operator    bool(void) = 0;
    virtual int			timedRead() {
    	int c;
    	  _startMillis = millis();
    	  do {
    	    c = read();
    	    if (c >= 0) {
    	      return c;
    	    }
    	  } while (millis() - _startMillis < _timeout);
    	  return -1;     // -1 indicates timeout
    }
protected:
    uint8_t*    rawIPAddress(IPAddress& addr)   { return addr.raw_address(); };
    uint32_t _timeout, _startMillis;
};
#endif
