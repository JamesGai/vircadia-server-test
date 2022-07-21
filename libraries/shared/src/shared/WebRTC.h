//
//  WebRTC.h
//  libraries/shared/src/shared/
//
//  Copyright 2019 High Fidelity, Inc.
//  Copyright 2021 Vircadia contributors.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_WebRTC_h
#define hifi_WebRTC_h

#ifndef QSYSTEMDETECTION_H
#include <qsystemdetection.h>
#endif

// WEBRTC_AUDIO: WebRTC audio features, e.g., echo canceling (defined in cmake).
// WEBRTC_DATA_CHANNELS: WebRTC client-server connections in parallel with UDP (defined in cmake).

#if defined(Q_OS_MAC)
#  define WEBRTC_POSIX 1
#  define WEBRTC_LEGACY 1
#elif defined(Q_OS_WIN)
#  define WEBRTC_WIN 1
#  define NOMINMAX 1
#  define WIN32_LEAN_AND_MEAN 1
#elif defined(Q_OS_ANDROID)
// #  define WEBRTC_POSIX 1
// #  define WEBRTC_LEGACY 1
#elif defined(Q_OS_LINUX) && defined(Q_PROCESSOR_X86_64)
#  define WEBRTC_POSIX 1
#elif defined(Q_OS_LINUX) && defined(Q_PROCESSOR_ARM)
// #  define WEBRTC_POSIX 1
// #  define WEBRTC_LEGACY 1
#endif

#endif // hifi_WebRTC_h
