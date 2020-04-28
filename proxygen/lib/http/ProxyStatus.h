/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <folly/Range.h>
#include <proxygen/lib/http/StatusTypeEnum.h>
#include <proxygen/lib/http/structuredheaders/StructuredHeadersEncoder.h>

namespace proxygen {

/**
 * Proxy status returned as a header in HTTP responses.
 *   https://tools.ietf.org/html/draft-ietf-httpbis-proxy-status-00
 *
 * Example:
 *   HTTP/1.1 504 Gateway Timeout
 *   Proxy-Status: server_timeout; proxy=twtraffic1234.prn1;
 *                 upstream_ip=fbfb:face:fbfb:face:fbfb:face:fbfb:face;
 *                 upstream_pool=livestream-proxy; tries=3
 */
class ProxyStatus {
 public:
  ProxyStatus() {
  }
  ~ProxyStatus() {
  }
  explicit ProxyStatus(StatusType statusType);

  StatusType getStatusType() const;
  bool hasUpstreamIP() const;

  void setStatusType(StatusType statusType);
  ProxyStatus& setProxy(const std::string& proxy);
  ProxyStatus& setUpstreamIP(const std::string& upstreamIP);
  ProxyStatus& setProxyStatusParameter(folly::StringPiece name,
                                       const std::string& text);

  std::string str() const;

 protected:
  StructuredHeaders::ParameterisedIdentifier pIdent_;
  StatusType statusType_;
};

} // namespace proxygen
