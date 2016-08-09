/*
 *  Copyright 2011 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_P2P_BASE_PACKETSOCKETFACTORY_H_
#define WEBRTC_P2P_BASE_PACKETSOCKETFACTORY_H_

#include "webrtc/base/proxyinfo.h"

namespace rtc {

class AsyncPacketSocket;
class AsyncResolverInterface;

class PacketSocketFactory {
 public:
  enum Options {
    OPT_SSLTCP = 0x01,  // Pseudo-TLS.
    OPT_TLS = 0x02,
    OPT_STUN = 0x04,
  };

  PacketSocketFactory() { }
  virtual ~PacketSocketFactory() { }

  virtual AsyncPacketSocket* CreateUdpSocket(const SocketAddress& address,
                                             uint16 min_port,
                                             uint16 max_port) = 0;
  virtual AsyncPacketSocket* CreateServerTcpSocket(
      const SocketAddress& local_address,
      uint16 min_port,
      uint16 max_port,
      int opts) = 0;

  // TODO: |proxy_info| and |user_agent| should be set
  // per-factory and not when socket is created.
  virtual AsyncPacketSocket* CreateClientTcpSocket(
      const SocketAddress& local_address,
      const SocketAddress& remote_address,
      const ProxyInfo& proxy_info,
      const std::string& user_agent,
      int opts) = 0;

  virtual AsyncResolverInterface* CreateAsyncResolver() = 0;

 private:
  RTC_DISALLOW_COPY_AND_ASSIGN(PacketSocketFactory);
};

}  // namespace rtc

#endif  // WEBRTC_P2P_BASE_PACKETSOCKETFACTORY_H_
