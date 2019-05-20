[TOC]
Follow IEEE 802.3 standard

Ethernet II frame(traditional frame, no JF)

| Preameble | SFD | MAC(DST,SRC)| length or type | payload | FSC(CRC32) | IPG |
|----|----|----|----|-----|----|-----|
| 7 bytes | 1 bytes | 12(6,6) bytes | 2 bytes | 48-1500 bytes | 4 bytes |  12bytes |

* Basis
  64 ~ 1518 Bytes(only include Mac, length or type, payload, FSC)
* Total
  86 ~ 1538 Bytes

* Payload
  MTU for TCP/IP

* Efficiency at each frame
  1500/(12(IPG)+8+14+1500+4) = 98%(it’s up to the frame size)
* IPG
  interpacket gap
* Raw Bandwidth
  100MB/s
* Packet per second
  100*1000*1000 /1538 ~= 65019
* TCP/IP overhead
  * IPv4 header: 20 Bytes ( no options)
  * IPv6 header: 40 Bytes ( no options)
  * TCP header:  20 Bytes ( no options)
  * TCP Option: 10 Bytes( [timestamp](https://tools.ietf.org/html/rfc7323))
* Max TCP throughput:  65019*(1500-50) ~= 94,277,550 (94MB/s)
