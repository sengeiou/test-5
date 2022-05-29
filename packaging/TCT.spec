Name:       TCT
Summary:    Native API TC
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache-2.0
Source0:    TCT-%{version}.tar.gz
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:  pkgconfig(capi-appfw-app-manager)
BuildRequires:  pkgconfig(accounts-svc)
BuildRequires:  pkgconfig(core-sync-client)
BuildRequires:  pkgconfig(appcore-agent)
BuildRequires:	pkgconfig(capi-appfw-service-application)
BuildRequires:	pkgconfig(capi-media-camera)
BuildRequires:  cmake
BuildRequires:  pkgconfig(bundle)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(aul)
BuildRequires:  pkgconfig(ail)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(gthread-2.0)
BuildRequires:  pkgconfig(storage)
BuildRequires:  pkgconfig(libtbm)
BuildRequires:  pkgconfig(pthread-stubs)
BuildRequires:  pkgconfig(libdrm)
BuildRequires:  pkgconfig(libdri2)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(capi-system-info)
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(ecore)
BuildRequires:  pkgconfig(evas)
BuildRequires:  pkgconfig(libcurl)
BuildRequires:  pkgconfig(json-glib-1.0)
BuildRequires:  pkgconfig(dbus-glib-1)
BuildRequires:  pkgconfig(ecore-evas)
BuildRequires:  pkgconfig(edje)
BuildRequires:  pkgconfig(eina)
BuildRequires:  pkgconfig(embryo)
BuildRequires:  pkgconfig(utilX)
BuildRequires:  pkgconfig(capi-appfw-application)
BuildRequires:  pkgconfig(capi-appfw-preference)
BuildRequires:  pkgconfig(capi-appfw-alarm)
BuildRequires:  pkgconfig(capi-media-audio-io)
BuildRequires:  pkgconfig(badge)
BuildRequires:  pkgconfig(capi-base-utils-i18n)
BuildRequires:  pkgconfig(capi-network-bluetooth)
BuildRequires:  pkgconfig(bundle)
BuildRequires:  pkgconfig(calendar-service2)
BuildRequires:  pkgconfig(capi-media-camera)
BuildRequires:  pkgconfig(capi-media-tool)
BuildRequires:  pkgconfig(capi-message-port)
BuildRequires:  pkgconfig(capi-network-connection)
BuildRequires:  pkgconfig(capi-network-wifi)
BuildRequires:  pkgconfig(contacts-service2)
BuildRequires:  pkgconfig(libcore-context-manager)
BuildRequires:  pkgconfig(capi-data-control)
BuildRequires:  pkgconfig(capi-system-device)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(libsystemd-journal)
BuildRequires:  pkgconfig(capi-ui-efl-util)
BuildRequires:  pkgconfig(efl-extension)
BuildRequires:  pkgconfig(capi-messaging-email)
BuildRequires:  pkgconfig(capi-media-image-util)
BuildRequires:  pkgconfig(key-manager)
BuildRequires:  pkgconfig(capi-location-manager)
BuildRequires:  pkgconfig(location)
BuildRequires:  pkgconfig(capi-media-codec)
BuildRequires:  pkgconfig(capi-mediademuxer)
BuildRequires:  pkgconfig(capi-mediamuxer)
BuildRequires:  pkgconfig(appcore-efl)
BuildRequires:  pkgconfig(capi-content-media-content)
BuildRequires:  pkgconfig(capi-media-controller)
BuildRequires:  pkgconfig(libmedia-service)
BuildRequires:  pkgconfig(media-thumbnail)
BuildRequires:  pkgconfig(libmedia-utils)
BuildRequires:  pkgconfig(icu-i18n)
BuildRequires:  pkgconfig(capi-system-media-key)
BuildRequires:  pkgconfig(ecore-x)
BuildRequires:  pkgconfig(capi-messaging-messages)
BuildRequires:  pkgconfig(msg-service)
BuildRequires:  pkgconfig(capi-media-metadata-extractor)
BuildRequires:  pkgconfig(capi-content-mime-type)
BuildRequires:  pkgconfig(capi-network-nfc)
BuildRequires:  pkgconfig(capi-network-smartcard)
BuildRequires:  pkgconfig(capi-network-mtp)
BuildRequires:  pkgconfig(notification)
BuildRequires:  pkgconfig(capi-appfw-package-manager)
BuildRequires:  pkgconfig(capi-media-player)
BuildRequires:  pkgconfig(privilege-info)
BuildRequires:  pkgconfig(security-privilege-manager)
BuildRequires:  pkgconfig(push)
BuildRequires:  pkgconfig(capi-media-radio)
BuildRequires:  pkgconfig(mm-radio)
BuildRequires:  pkgconfig(capi-media-recorder)
BuildRequires:  pkgconfig(capi-media-streamrecorder)
BuildRequires:  pkgconfig(audio-session-mgr)
BuildRequires:  pkgconfig(capi-system-runtime-info)
BuildRequires:  pkgconfig(capi-system-sensor)
BuildRequires:  pkgconfig(shortcut)
BuildRequires:  pkgconfig(capi-media-sound-manager)
BuildRequires:  pkgconfig(stt)
BuildRequires:  pkgconfig(stt-engine)
BuildRequires:  pkgconfig(capi-system-system-settings)
BuildRequires:  pkgconfig(capi-telephony)
BuildRequires:  pkgconfig(capi-media-tone-player)
BuildRequires:  pkgconfig(capi-media-sound-pool)
BuildRequires:  pkgconfig(tts)
BuildRequires:	pkgconfig(tts-engine)
BuildRequires:  pkgconfig(capi-web-url-download)
BuildRequires:  pkgconfig(capi-media-wav-player)
BuildRequires:  pkgconfig(dbus-1)
BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  pkgconfig(capi-network-wifi-direct)
BuildRequires:  pkgconfig(capi-network-wifi)
BuildRequires:  efl-assist-devel
BuildRequires:  pkgconfig(sqlite3)
BuildRequires:  pkgconfig(db-util)
BuildRequires:  gettext-tools
BuildRequires:  edje-bin, embryo-bin
BuildRequires:  pkgconfig(deviced)
BuildRequires:  pkgconfig(appcore-common)
BuildRequires:  pkgconfig(pkgmgr-info)
BuildRequires:  pkgconfig(appsvc)
BuildRequires:  pkgconfig(alarm-service)
BuildRequires:  pkgconfig(libsmack)
BuildRequires:  pkgconfig(tapi)
BuildRequires:  pkgconfig(icu-i18n)
BuildRequires:  hash-signer
BuildRequires:  pkgconfig(wayland-client)
BuildRequires:  pkgconfig(chromium-efl)
BuildRequires:  pkgconfig(fido-client)
BuildRequires:  pkgconfig(fido-client-devel)
BuildRequires:  pkgconfig(capi-network-softap)
BuildRequires:  pkgconfig(multi-assistant)
BuildRequires:  pkgconfig(capi-ui-autofill)
BuildRequires:	pkgconfig(capi-system-battery-monitor)
BuildRequires:  pkgconfig(capi-ui-sticker-consumer)
BuildRequires:  pkgconfig(capi-ui-sticker-provider)
BuildRequires:  pkgconfig(capi-media-webrtc)
Requires(post):  /sbin/ldconfig
Requires(postun):  /sbin/ldconfig

# End Adding for UTC******************************************************************************************************************************
#Requires(post):  /sbin/ldconfig
#Requires(postun):  /sbin/ldconfig

%description
Native API TC

#*************Adding ITC***************
%package -n native-app-manager-itc
Summary:    Native API Integration TC for app-manager
Group:      Development/Tools

%description -n native-app-manager-itc
Native API Integration TC for app-manager

%package -n native-accounts-svc-itc
Summary:    Native API Integration TC for accounts-svc
Group:      Development/Tools

%description -n native-accounts-svc-itc
Native API Integration TC for accounts-svc

%package -n native-appcore-agent-itc
Summary:    Native API Integration TC for appcore-agent
Group:      Development/Tools

%description -n native-appcore-agent-itc
Native API Integration TC for appcore-agent

%package -n native-application-itc
Summary:    Native API Integration TC for application
Group:      Development/Tools

%description -n native-application-itc
Native API Integration TC for application

%package -n native-audio-io-itc
Summary:    Native API Integration TC for audio-io
Group:      Development/Tools

%description -n native-audio-io-itc
Native API Integration TC for audio-io

%package -n native-badge-itc
Summary:    Native API Integration TC for badge

%description -n native-badge-itc
Native API Integration TC for badge

%package -n native-base-utils-itc
Summary:    Native API Integration TC for base-utils
Group:      Development/Tools

%description -n native-base-utils-itc
Native API Integration TC for base-utils

%package -n native-battery-monitor-itc
Summary:    Native API Integration TC for battery-monitor
Group:      Development/Tools

%description -n native-battery-monitor-itc
Native API Integration TC for battery-monitor

%package -n native-bluetooth-itc
Summary:    Native API Integration TC for bluetooth
Group:      Development/Tools

%description -n native-bluetooth-itc
Native API Integration TC for bluetooth

%package -n native-bundle-itc
Summary:    Native API Integration TC for bundle
Group:      Development/Tools

%description -n native-bundle-itc
Native API Integration TC for bundle

%package -n native-calendar-service2-itc
Summary:    Native API Integration TC for calendar-service2
Group:      Development/Tools

%description -n native-calendar-service2-itc
Native API Integration TC for calendar-service2

%package -n native-camera-itc
Summary:    Native API Integration TC for camera
Group:      Development/Tools

%description -n native-camera-itc
Native API Integration TC for camera

%package -n native-capi-media-tool-itc
Summary:    Native API Integration TC for capi-media-tool
Group:      Development/Tools

%description -n native-capi-media-tool-itc
Native API Integration TC for capi-media-tool

%package -n native-capi-network-softap-itc
Summary:    Native API Integration TC for capi-network-softap
Group:      Development/Tools

%description -n native-capi-network-softap-itc
Native API Integration TC for capi-network-softap

%package -n native-connection-itc
Summary:    Native API Integration TC for connection
Group:      Development/Tools

%description -n native-connection-itc
Native API Integration TC for connection

%package -n native-contacts-service2-itc
Summary:    Native API Integration TC for contacts-service2
Group:      Development/Tools

%description -n native-contacts-service2-itc
Native API Integration TC for contacts-service2

%package -n native--itc
Summary:    Native API Integration TC for motion
Group:      Development/Tools

%description -n native-motion-itc
Native API Integration TC for motion

%package -n native-data-control-itc
Summary:    Native API Integration TC for data-control
Group:      Development/Tools

%description -n native-data-control-itc
Native API Integration TC for data-control

%package -n native-device-itc
Summary:    Native API Integration TC for device
Group:      Development/Tools

%description -n native-device-itc
Native API Integration TC for device

%package -n native-dlog-itc
Summary:    Native API Integration TC for dlog
Group:      Development/Tools

%description -n native-dlog-itc
Native API Integration TC for dlog

%package -n native-efl-util-itc
Summary:    Native API Integration TC for efl-util
Group:      Development/Tools

%description -n native-efl-util-itc
Native API Integration TC for efl-util

%package -n native-email-itc
Summary:    Native API Integration TC for email
Group:      Development/Tools

%description -n native-email-itc
Native API Integration TC for email

%package -n native-image-util-itc
Summary:    Native API Integration TC for image-util
Group:      Development/Tools

%description -n native-image-util-itc
Native API Integration TC for image-util

%package -n native-key-manager-itc
Summary:    Native API Integration TC for key-manager
Group:      Development/Tools

%description -n native-key-manager-itc
Native API Integration TC for key-manager

%package -n native-libstorage-itc
Summary:    Native API Integration TC for libstorage
Group:      Development/Tools

%description -n native-libstorage-itc
Native API Integration TC for libstorage

%package -n native-location-manager-itc
Summary:    Native API Integration TC for location-manager
Group:      Development/Tools

%description -n native-location-manager-itc
Native API Integration TC for location-manager

%package -n native-media-codec-itc
Summary:    Native API Integration TC for media-codec
Group:      Development/Tools

%description -n native-media-codec-itc
Native API Integration TC for media-codec

%package -n native-media-content-itc
Summary:    Native API Integration TC for media-content
Group:      Development/Tools

%description -n native-media-content-itc
Native API Integration TC for media-content

%package -n native-media-key-itc
Summary:    Native API Integration TC for media-key
Group:      Development/Tools

%description -n native-media-key-itc
Native API Integration TC for media-key

%package -n native-message-port-itc
Summary:    Native API Integration TC for message-port
Group:      Development/Tools

%description -n native-message-port-itc
Native API Integration TC for message-port

%package -n native-messages-itc
Summary:    Native API Integration TC for messages
Group:      Development/Tools

%description -n native-messages-itc
Native API Integration TC for messages

%package -n native-metadata-extractor-itc
Summary:    Native API Integration TC for metadata-extractor
Group:      Development/Tools

%description -n native-metadata-extractor-itc
Native API Integration TC for metadata-extractor

%package -n native-mime-type-itc
Summary:    Native API Integration TC for mime-type
Group:      Development/Tools

%description -n native-mime-type-itc
Native API Integration TC for mime-type

%package -n native-native-common-itc
Summary:    Native API Integration TC for native-common
Group:      Development/Tools

%description -n native-native-common-itc
Native API Integration TC for native-common

%package -n native-nfc-itc
Summary:    Native API Integration TC for nfc
Group:      Development/Tools

%description -n native-nfc-itc
Native API Integration TC for nfc

%package -n native-notification-itc
Summary:    Native API Integration TC for notification
Group:      Development/Tools

%description -n native-notification-itc
Native API Integration TC for notification

%package -n native-package-manager-itc
Summary:    Native API Integration TC for package-manager
Group:      Development/Tools

%description -n native-package-manager-itc
Native API Integration TC for package-manager

%package -n native-player-itc
Summary:    Native API Integration TC for player
Group:      Development/Tools

%description -n native-player-itc
Native API Integration TC for player

%package -n native-privilege-info-itc
Summary:    Native API Integration TC for privilege-info
Group:      Development/Tools

%description -n native-privilege-info-itc
Native API Integration TC for privilege-info

%package -n native-push-itc
Summary:    Native API Integration TC for push
Group:      Development/Tools

%description -n native-push-itc
Native API Integration TC for push

%package -n native-radio-itc
Summary:    Native API Integration TC for radio
Group:      Development/Tools

%description -n native-radio-itc
Native API Integration TC for radio

%package -n native-recorder-itc
Summary:    Native API Integration TC for recorder
Group:      Development/Tools

%description -n native-recorder-itc
Native API Integration TC for recorder

%package -n native-runtime-info-itc
Summary:    Native API Integration TC for runtime-info
Group:      Development/Tools

%description -n native-runtime-info-itc
Native API Integration TC for runtime-info

%package -n native-sensor-itc
Summary:    Native API Integration TC for sensor
Group:      Development/Tools

%description -n native-sensor-itc
Native API Integration TC for sensor

%package -n native-sound-manager-itc
Summary:    Native API Integration TC for sound-manager
Group:      Development/Tools

%description -n native-sound-manager-itc
Native API Integration TC for sound-manager

%package -n native-stt-itc
Summary:    Native API Integration TC for stt
Group:      Development/Tools

%description -n native-stt-itc
Native API Integration TC for stt

%package -n native-system-info-itc
Summary:    Native API Integration TC for system-info
Group:      Development/Tools

%description -n native-system-info-itc
Native API Integration TC for system-info

%package -n native-system-settings-itc
Summary:    Native API Integration TC for system-settings
Group:      Development/Tools

%description -n native-system-settings-itc
Native API Integration TC for system-settings

%package -n native-capi-system-system-settings-itc
Summary:    Native API Integration TC for system-settings
Group:      Development/Tools

%description -n native-capi-system-system-settings-itc
Native API Integration TC for system-settings


%package -n native-tbm-itc
Summary:    Native API Integration TC for tbm
Group:      Development/Tools

%description -n native-tbm-itc
Native API Integration TC for tbm

%package -n native-telephony-itc
Summary:    Native API Integration TC for telephony
Group:      Development/Tools

%description -n native-telephony-itc
Native API Integration TC for telephony

%package -n native-tone-player-itc
Summary:    Native API Integration TC for tone-player
Group:      Development/Tools

%description -n native-tone-player-itc
Native API Integration TC for tone-player

%package -n native-tts-itc
Summary:    Native API Integration TC for tts
Group:      Development/Tools

%description -n native-tts-itc
Native API Integration TC for tts

%package -n native-url-download-itc
Summary:    Native API Integration TC for url-download
Group:      Development/Tools

%description -n native-url-download-itc
Native API Integration TC for url-download

%package -n native-wav-player-itc
Summary:    Native API Integration TC for wav-player
Group:      Development/Tools

%description -n native-wav-player-itc
Native API Integration TC for wav-player

%package -n native-webkit2-itc
Summary:    Native API Integration TC for webkit2
Group:      Development/Tools

%description -n native-webkit2-itc
Native API Integration TC for webkit2

%package -n native-wifi-direct-itc
Summary:    Native API Integration TC for wifi-direct
Group:      Development/Tools

%description -n native-wifi-direct-itc
Native API Integration TC for wifi-direct

%package -n native-wifi-itc
Summary:    Native API Integration TC for wifi
Group:      Development/Tools

%description -n native-wifi-itc
Native API Integration TC for wifi

%package -n native-multi-assistant-itc
Summary:    Native API Integration TC for multi-assistant
Group:      Development/Tools

%description -n native-multi-assistant-itc
Native API Integration TC for multi-assistant
#************End Adding ITC******************************

%package -n core-accounts-svc-tests
Summary:    Native API Unit TC for accounts-svc
Group:      Development/Tools

%description -n core-accounts-svc-tests
Native API Unit TC for accounts-svc

%package -n core-appcore-agent-tests
Summary:    Native API Unit TC for appcore-agent
Group:      Development/Tools

%description -n core-appcore-agent-tests
Native API Unit TC for appcore-agent

%package -n core-application-tests
Summary:    Native API Unit TC for application
Group:      Development/Tools

%description -n core-application-tests
Native API Unit TC for application

%package -n core-app-manager-tests
Summary:    Native API Unit TC for app-manager
Group:      Development/Tools

%description -n core-app-manager-tests
Native API Unit TC for app-manager

%package -n core-audio-io-tests
Summary:    Native API Unit TC for audio-io
Requires:   storage
Group:      Development/Tools

%description -n core-audio-io-tests
Native API Unit TC for audio-io

%package -n core-badge-tests
Summary:    Native API Unit TC for badge
Group:      Development/Tools

%description -n core-badge-tests
Native API Unit TC for badge

%package -n core-base-utils-tests
Summary:    Native API Unit TC for base-utils
Group:      Development/Tools

%description -n core-base-utils-tests
Native API Unit TC for base-utils

%package -n core-bluetooth-tests
Summary:    Native API Unit TC for bluetooth
Group:      Development/Tools

%description -n core-bluetooth-tests
Native API Unit TC for bluetooth

%package -n core-bundle-tests
Summary:    Native API Unit TC for bundle
Group:      Development/Tools

%description -n core-bundle-tests
Native API Unit TC for bundle

%package -n core-calendar-service2-tests
Summary:    Native API Unit TC for calendar-service2
Requires:   storage
Group:      Development/Tools

%description -n core-calendar-service2-tests
Native API Unit TC for calendar-service2

%package -n core-camera-tests
Summary:    Native API Unit TC for camera
Group:      Development/Tools

%description -n core-camera-tests
Native API Unit TC for camera

%package -n core-mediatool-tests
Summary:    Native API Unit TC for mediatool
Group:      Development/Tools

%description -n core-mediatool-tests
Native API Unit TC for mediatool

%package -n core-capi-message-port-tests
Summary:    Native API Unit TC for capi-message-port
Group:      Development/Tools

%description -n core-capi-message-port-tests
Native API Unit TC for capi-message-port

%package -n core-connection-tests
Summary:    Native API Unit TC for connection
Group:      Development/Tools

%description -n core-connection-tests
Native API Unit TC for connection

%package -n core-contacts-service2-tests
Summary:    Native API Unit TC for contacts-service2
Group:      Development/Tools

%description -n core-contacts-service2-tests
Native API Unit TC for contacts-service2

%package -n core-motion-tests
Summary:    Native API Unit TC for motion
Group:      Development/Tools

%description -n core-motion-tests
Native API Unit TC for motion

%package -n core-data-control-tests
Summary:    Native API Unit TC for data-control
Group:      Development/Tools

%description -n core-data-control-tests
Native API Unit TC for data-control

%package -n core-device-tests
Summary:    Native API Unit TC for device
Group:      Development/Tools

%description -n core-device-tests
Native API Unit TC for device

%package -n core-dlog-tests
Summary:    Native API Unit TC for dlog
Group:      Development/Tools

%description -n core-dlog-tests
Native API Unit TC for dlog

%package -n core-efl-util-tests
Summary:    Native API Unit TC for efl-util
Group:      Development/Tools

%description -n core-efl-util-tests
Native API Unit TC for efl-util

%package -n core-efl-extension-tests
Summary:    Native API Unit TC for efl-extension
Group:      Development/Tools

%description -n core-efl-extension-tests
Native API Unit TC for efl-extension

%package -n core-email-tests
Summary:    Native API Unit TC for email
Group:      Development/Tools

%description -n core-email-tests
Native API Unit TC for email

%package -n core-image-util-tests
Summary:    Native API Unit TC for image-util
Group:      Development/Tools

%description -n core-image-util-tests
Native API Unit TC for image-util

%package -n core-key-manager-tests
Summary:    Native API Unit TC for key-manager
Group:      Development/Tools

%description -n core-key-manager-tests
Native API Unit TC for key-manager

%package -n core-libstorage-tests
Summary:    Native API Unit TC for libstorage
Group:      Development/Tools

%description -n core-libstorage-tests
Native API Unit TC for libstorage

%package -n core-location-manager-tests
Summary:    Native API Unit TC for location-manager
Group:      Development/Tools

%description -n core-location-manager-tests
Native API Unit TC for location-manager

%package -n core-mediacodec-tests
Summary:    Native API Unit TC for mediacodec
Group:      Development/Tools

%description -n core-mediacodec-tests
Native API Unit TC for mediacodec

%package -n core-media-content-tests
Summary:    Native API Unit TC for media-content
Group:      Development/Tools

%description -n core-media-content-tests
Native API Unit TC for media-content

%package -n core-media-controller-tests
Summary:    Native API Unit TC for media-controller
Group:      Development/Tools

%description -n core-media-controller-tests
Native API Unit TC for media-controller

%package -n core-media-key-tests
Summary:    Native API Unit TC for media-key
Group:      Development/Tools

%description -n core-media-key-tests
Native API Unit TC for media-key

%package -n core-messages-tests
Summary:    Native API Unit TC for messages
Group:      Development/Tools

%description -n core-messages-tests
Native API Unit TC for messages

%package -n core-metadata-extractor-tests
Summary:    Native API Unit TC for metadata-extractor
Group:      Development/Tools

%description -n core-metadata-extractor-tests
Native API Unit TC for metadata-extractor

%package -n core-mime-type-tests
Summary:    Native API Unit TC for mime-type
Group:      Development/Tools

%description -n core-mime-type-tests
Native API Unit TC for mime-type

%package -n core-native-common-tests
Summary:    Native API Unit TC for native-common
Group:      Development/Tools

%description -n core-native-common-tests
Native API Unit TC for native-common

%package -n core-nfc-tests
Summary:    Native API Unit TC for nfc
Group:      Development/Tools

%description -n core-nfc-tests
Native API Unit TC for nfc

%package -n core-smartcard-tests
Summary:    Native API Unit TC for smartcard
Group:      Development/Tools

%description -n core-smartcard-tests
Native API Unit TC for smartcard

%package -n core-mtp-tests
Summary:    Native API Unit TC for mtp
Group:      Development/Tools

%description -n core-mtp-tests
Native API Unit TC for mtp

%package -n core-notification-tests
Summary:    Native API Unit TC for notification
Group:      Development/Tools

%description -n core-notification-tests
Native API Unit TC for notification

%package -n core-package-manager-tests
Summary:    Native API Unit TC for package-manager
Group:      Development/Tools

%description -n core-package-manager-tests
Native API Unit TC for package-manager

%package -n core-player-tests
Summary:    Native API Unit TC for player
Group:      Development/Tools

%description -n core-player-tests
Native API Unit TC for player

%package -n core-privilege-info-tests
Summary:    Native API Unit TC for privilege-info
Group:      Development/Tools

%description -n core-privilege-info-tests
Native API Unit TC for privilege-info

%package -n core-push-tests
Summary:    Native API Unit TC for push
Group:      Development/Tools

%description -n core-push-tests
Native API Unit TC for push

%package -n core-radio-tests
Summary:    Native API Unit TC for radio
Group:      Development/Tools

%description -n core-radio-tests
Native API Unit TC for radio

%package -n core-recorder-tests
Summary:    Native API Unit TC for recorder
Group:      Development/Tools

%package -n core-steamrecorder-tests
Summary:    Native API Unit TC for streamrecorder
Group:      Development/Tools

%description -n core-streamrecorder-tests
Native API Unit TC for streamrecorder

%description -n core-recorder-tests
Native API Unit TC for recorder

%package -n core-runtime-info-tests
Summary:    Native API Unit TC for runtime-info
Group:      Development/Tools

%description -n core-runtime-info-tests
Native API Unit TC for runtime-info

%package -n core-sensor-tests
Summary:    Native API Unit TC for sensor
Group:      Development/Tools

%description -n core-sensor-tests
Native API Unit TC for sensor

%package -n core-shortcut-tests
Summary:    Native API Unit TC for shortcut
Group:      Development/Tools

%description -n core-shortcut-tests
Native API Unit TC for shortcut

%package -n core-sound-manager-tests
Summary:    Native API Unit TC for sound-manager
Group:      Development/Tools

%description -n core-sound-manager-tests
Native API Unit TC for sound-manager

%package -n core-stt-tests
Summary:    Native API Unit TC for stt
Group:      Development/Tools

%description -n core-stt-tests
Native API Unit TC for stt

%package -n core-sync-manager-tests
Summary:    Native API Unit TC for sync-manager
Group:      Development/Tools

%description -n core-sync-manager-tests
Native API Unit TC for sync-manager

%package -n core-system-info-tests
Summary:    Native API Unit TC for system-info
Group:      Development/Tools

%description -n core-system-info-tests
Native API Unit TC for system-info

%package -n core-capi-system-system-settings-tests
Summary:    Native API Unit TC for capi-system-system-settings
Group:      Development/Tools

%description -n core-capi-system-settings-tests
Native API Unit TC for capi-system-settings

%package -n core-tbm-tests
Summary:    Native API Unit TC for tbm
Group:      Development/Tools

%description -n core-tbm-tests
Native API Unit TC for tbm

%package -n core-telephony-tests
Summary:    Native API Unit TC for telephony
Group:      Development/Tools

%description -n core-telephony-tests
Native API Unit TC for telephony

%package -n core-tone-player-tests
Summary:    Native API Unit TC for tone-player
Group:      Development/Tools

%description -n core-tone-player-tests
Native API Unit TC for tone-player

%package -n core-sound-pool-tests
Summary:    Native API Unit TC for sound-pool
Group:      Development/Tools

%description -n core-sound-pool-tests
Native API Unit TC for sound-pool

%package -n core-tts-tests
Summary:    Native API Unit TC for tts
Group:      Development/Tools

%description -n core-tts-tests
Native API Unit TC for tts

%package -n core-url-download-tests
Summary:    Native API Unit TC for url-download
Group:      Development/Tools

%description -n core-url-download-tests
Native API Unit TC for url-download

%package -n core-wav-player-tests
Summary:    Native API Unit TC for wav-player
Group:      Development/Tools

%description -n core-wav-player-tests
Native API Unit TC for wav-player

%package -n core-webkit2-tests
Summary:    Native API Unit TC for webkit2
Group:      Development/Tools

%description -n core-webkit2-tests
Native API Unit TC for webkit2

%package -n core-wifi-direct-tests
Summary:    Native API Unit TC for wifi-direct
Group:      Development/Tools

%description -n core-wifi-direct-tests
Native API Unit TC for wifi-direct

%package -n core-wifi-tests
Summary:    Native API Unit TC for wifi
Group:      Development/Tools

%description -n core-wifi-tests
Native API Unit TC for wifi

%package -n core-fido-client-tests
Summary:    Native API Unit TC for fido-client
Group:      Development/Tools

%description -n core-fido-client-tests
Native API Unit TC for fido-client

%package -n core-multi-assistant-tests
Summary:    Native API Unit TC for multi-assistant
Group:      Development/Tools

%description -n core-multi-assistant-tests
Native API Unit TC for multi-assistant

%package -n core-capi-ui-sticker-tests
Summary:    Native API Unit TC for sticker
Group:      Development/Tools

%description -n core-capi-ui-sticker-tests
Native API Unit TC for sticker

%package -n core-webrtc-tests
Summary:    Native API Unit TC for webrtc
Group:      Development/Tools

%description -n core-webrtc-tests
Native API Unit TC for webrtc

%package -n native-audio-io-ctc
Summary:    Native API Compatibility TC for audio-io

%description -n native-audio-io-ctc
Native API Compatibility TC for audio-io

%package -n native-camera-ctc
Summary:    Native API Compatibility TC for camera

%description -n native-camera-ctc
Native API Compatibility TC for camera

%package -n native-connection-ctc
Summary:    Native API Compatibility TC for connection

%description -n native-connection-ctc
Native API Compatibility TC for connection

%package -n native-device-ctc
Summary:    Native API Compatibility TC for connection

%description -n native-device-ctc
Native API Compatibility TC for connection

%package -n native-filesystem-permission-ctc
Summary:    Native API Compatibility TC for filesystem-permission

%description -n native-filesystem-permission-ctc
Native API Compatibility TC for filesystem-permission

%package -n native-image-util-ctc
Summary:    Native API Compatibility TC for image-util

%description -n native-image-util-ctc
Native API Compatibility TC for image-util

%package -n native-libstorage-ctc
Summary:    Native API Compatibility TC for libstorage

%description -n native-libstorage-ctc
Native API Compatibility TC for libstorage

%package -n native-system-info-ctc
Summary:    Native API Compatibility TC for native-system-info

%description -n native-system-info-ctc
Native API Compatibility TC for native-system-info

%package -n native-telephony-ctc
Summary:    Native API Compatibility TC for telephony

%description -n native-telephony-ctc
Native API Compatibility TC for telephony

%package -n native-wifi-direct-ctc
Summary:    Native API Compatibility TC for wifi-direct

%description -n native-wifi-direct-ctc
Native API Compatibility TC for wifi-direct

%package -n native-location-manager-ctc
Summary:    Native API Compatibility TC for location-manager

%description -n native-location-manager-ctc
Native API Compatibility TC for location-manager

%package -n native-media-codec-ctc
Summary:    Native API Compatibility TC for media-codec

%description -n native-media-codec-ctc
Native API Compatibility TC for media-codec

%package -n native-opengl-ctc
Summary:    Native API Compatibility TC for opengl

%description -n native-opengl-ctc
Native API Compatibility TC for opengl

%package -n native-platform-permission-ctc
Summary:    Native API Compatibility TC for telephony

%description -n native-platform-permission-ctc
Native API Compatibility TC for telephony

%package -n native-player-ctc
Summary:    Native API Compatibility TC for player

%description -n native-player-ctc
Native API Compatibility TC for player

%package -n native-runtime-info-ctc
Summary:    Native API Compatibility TC for runtime-info

%description -n native-runtime-info-ctc
Native API Compatibility TC for runtime-info

%package -n native-sensor-ctc
Summary:    Native API Compatibility TC for sensor

%description -n native-sensor-ctc
Native API Compatibility TC for sensor

%package -n native-sound-manager-ctc
Summary:    Native API Compatibility TC for sound-manager

%description -n native-sound-manager-ctc
Native API Compatibility TC for sound-manager


# End Adding for UTC******************************************************************************************************************************

%prep
%setup -q

%build

%define PREFIX "%{_libdir}/%{name}"

export LDFLAGS+="-Wl,--rpath=%{PREFIX} -Wl,--as-needed"

cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/opt/usr/share/license
mkdir -p %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/tmp/

#*********Adding ITC*********

#native-app-manager-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-app-manager-itc
cp packaging/itc/native-app-manager-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-app-manager-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-app-manager-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-app-manager-itc/data
cp scripts/appmanagerinstall.sh %{buildroot}/opt/usr/apps/native-app-manager-itc/data/
%ifarch armv7l
cp src/itc/app-manager/org.tizen.appmanagertestfile-1.0.0-arm.tpk %{buildroot}/opt/usr/apps/native-app-manager-itc/data/org.tizen.appmanagertestfile-1.0.0-arm.tpk
cp src/itc/app-manager/org.tizen.testapplication-1.0.0-arm.tpk %{buildroot}/opt/usr/apps/native-app-manager-itc/data/org.tizen.testapplication-1.0.0-arm.tpk
%else
cp src/itc/app-manager/org.tizen.appmanagertestfile-1.0.0-i386.tpk %{buildroot}/opt/usr/apps/native-app-manager-itc/data/org.tizen.appmanagertestfile-1.0.0-i386.tpk
cp src/itc/app-manager/org.tizen.testapplication-1.0.0-i386.tpk %{buildroot}/opt/usr/apps/native-app-manager-itc/data/org.tizen.testapplication-1.0.0-i386.tpk
%endif

#native-accounts-svc-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-accounts-svc-itc
cp packaging/itc/native-accounts-svc-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-accounts-svc-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-accounts-svc-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-accounts-svc-itc/data
cp src/itc/accounts-svc/icontexto_256.png %{buildroot}/opt/usr/apps/native-accounts-svc-itc/data/icontexto_256.png

#native-appcore-agent-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-appcore-agent-itc
cp packaging/itc/native-appcore-agent-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-appcore-agent-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-appcore-agent-itc/bin


#native-application-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-application-itc
cp packaging/itc/native-application-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-application-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-application-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-application-itc/data
%ifarch armv7l
cp src/itc/application/org.tizen.testapplication-1.0.0-arm.tpk %{buildroot}/opt/usr/apps/native-application-itc/data/org.tizen.testapplication-1.0.0-arm.tpk
%else
cp src/itc/application/org.tizen.testapplication-1.0.0-i386.tpk %{buildroot}/opt/usr/apps/native-application-itc/data/org.tizen.testapplication-1.0.0-i386.tpk
%endif

#native-audio-io-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-audio-io-itc
cp packaging/itc/native-audio-io-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-audio-io-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-audio-io-itc/bin

#native-badge-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-badge-itc
cp packaging/itc/native-badge-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-badge-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-badge-itc/bin

#native-base-utils-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-base-utils-itc
cp packaging/itc/native-base-utils-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-base-utils-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-base-utils-itc/bin

#native-battery-monitor-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-battery-monitor-itc
cp packaging/itc/native-battery-monitor-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-battery-monitor-itc/bin

#native-bluetooth-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-bluetooth-itc
cp packaging/itc/native-bluetooth-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-bluetooth-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-bluetooth-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-bluetooth-itc/data
cp src/itc/bluetooth/TestFile.vcf %{buildroot}/opt/usr/apps/native-bluetooth-itc/data/TestFile.vcf

#native-bundle-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-bundle-itc
cp packaging/itc/native-bundle-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-bundle-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-bundle-itc/bin

#native-calendar-service2-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-calendar-service2-itc
cp packaging/itc/native-calendar-service2-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-calendar-service2-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-calendar-service2-itc/bin

#native-camera-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-camera-itc
cp packaging/itc/native-camera-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-camera-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-camera-itc/bin

#native-capi-media-tool-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-capi-media-tool-itc
cp packaging/itc/native-capi-media-tool-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-capi-media-tool-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-capi-media-tool-itc/bin

#native-connection-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-connection-itc
cp packaging/itc/native-connection-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-connection-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-connection-itc/bin

#native-contacts-service2-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-contacts-service2-itc
cp packaging/itc/native-contacts-service2-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-contacts-service2-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-contacts-service2-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-contacts-service2-itc/data
cp src/itc/contacts-service2/TestRingtone.mp3 %{buildroot}/opt/usr/apps/native-contacts-service2-itc/data/TestRingtone.mp3
cp src/itc/contacts-service2/icon.png %{buildroot}/opt/usr/apps/native-contacts-service2-itc/data/icon.png

#native-motion-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-motion-itc
cp packaging/itc/native-motion-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-motion-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-motion-itc/bin

#native-data-control-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-data-control-itc
cp packaging/itc/native-data-control-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-data-control-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-data-control-itc/bin

#native-device-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-device-itc
cp packaging/itc/native-device-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-device-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-device-itc/bin

#native-dlog-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-dlog-itc
cp packaging/itc/native-dlog-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-dlog-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-dlog-itc/bin

#native-efl-util-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-efl-util-itc
cp packaging/itc/native-efl-util-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-efl-util-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-efl-util-itc/bin

#native-email-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-email-itc
cp packaging/itc/native-email-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-email-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-email-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-email-itc/data
cp src/itc/email/Image_01.jpg %{buildroot}/opt/usr/apps/native-email-itc/data/Image_01.jpg

#native-image-util-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-image-util-itc
cp packaging/itc/native-image-util-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-image-util-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-image-util-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-image-util-itc/data/
cp src/itc/image-util/Image_01.jpg %{buildroot}/opt/usr/apps/native-image-util-itc/data/Image_01.jpg

#native-key-manager-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-key-manager-itc
cp packaging/itc/native-key-manager-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-key-manager-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-key-manager-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-key-manager-itc/data
cp src/itc/key-manager/certificate.crt %{buildroot}/opt/usr/apps/native-key-manager-itc/data/certificate.crt
cp src/itc/key-manager/signer.p12 %{buildroot}/opt/usr/apps/native-key-manager-itc/data/signer.p12

#native-libstorage-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-libstorage-itc
cp packaging/itc/native-libstorage-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-libstorage-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-libstorage-itc/bin

#native-location-manager-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-location-manager-itc
cp packaging/itc/native-location-manager-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-location-manager-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-location-manager-itc/bin

#native-media-codec-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-media-codec-itc
cp packaging/itc/native-media-codec-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-media-codec-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-media-codec-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-media-codec-itc/data/
cp src/itc/media-codec/TestData.pcm %{buildroot}/opt/usr/apps/native-media-codec-itc/data/TestData.pcm

#native-media-content-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-media-content-itc
cp packaging/itc/native-media-content-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-media-content-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-media-content-itc/bin
mkdir -p %{buildroot}/opt/usr/media/
cp src/itc/media-content/test.jpg %{buildroot}/opt/usr/media/test.jpg
cp src/itc/media-content/test0.jpg %{buildroot}/opt/usr/media/test0.jpg
cp src/itc/media-content/test1.jpg %{buildroot}/opt/usr/media/test1.jpg
cp src/itc/media-content/test2.jpg %{buildroot}/opt/usr/media/test2.jpg
cp src/itc/media-content/test3.jpg %{buildroot}/opt/usr/media/test3.jpg
cp src/itc/media-content/20140709-115007.mp4 %{buildroot}/opt/usr/media/20140709-115007.mp4
cp src/itc/media-content/TestRingtone.mp3 %{buildroot}/opt/usr/media/TestRingtone.mp3

mkdir -p %{buildroot}/opt/usr/media/NewName/.hide/testing
mkdir -p %{buildroot}/opt/usr/media/NewName/.hideDelete/testing
mkdir -p %{buildroot}/opt/usr/media/Sounds
mkdir -p %{buildroot}/opt/usr/media/Images/
mkdir -p %{buildroot}/opt/usr/media/Images/test
mkdir -p %{buildroot}/opt/usr/media/DCIM/Camera
mkdir -p %{buildroot}/opt/usr/media/Dummy
cp src/itc/media-content/test1.jpg %{buildroot}/opt/usr/media/Images/test/test1.jpg
cp src/itc/media-content/20140709-115007.mp4 %{buildroot}/opt/usr/media/DCIM/Camera/20140709-115007.mp4
cp src/itc/media-content/TestRingtone.mp3 %{buildroot}/opt/usr/media/Sounds/TestRingtone.mp3
cp src/itc/media-content/test.jpg %{buildroot}/opt/usr/media/Images/test.jpg


#native-media-key-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-media-key-itc
cp packaging/itc/native-media-key-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-media-key-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-media-key-itc/bin

#native-message-port-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-message-port-itc
cp packaging/itc/native-message-port-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-message-port-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-message-port-itc/bin

#native-messages-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-messages-itc
cp packaging/itc/native-messages-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-messages-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-messages-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-messages-itc/data
cp src/itc/messages/Image.jpg %{buildroot}/opt/usr/apps/native-messages-itc/data/Image.jpg

#native-metadata-extractor-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-metadata-extractor-itc
cp packaging/itc/native-metadata-extractor-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-metadata-extractor-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-metadata-extractor-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-metadata-extractor-itc/data
cp src/itc/metadata-extractor/metadata_video.mp4 %{buildroot}/opt/usr/apps/native-metadata-extractor-itc/data/metadata_video.mp4
cp src/itc/metadata-extractor/metadata_audio.mp3 %{buildroot}/opt/usr/apps/native-metadata-extractor-itc/data/metadata_audio.mp3


#native-mime-type-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-mime-type-itc
cp packaging/itc/native-mime-type-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-mime-type-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-mime-type-itc/bin

#native-native-common-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-native-common-itc
cp packaging/itc/native-native-common-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-native-common-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-native-common-itc/bin

#native-nfc-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-nfc-itc
cp packaging/itc/native-nfc-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-nfc-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-nfc-itc/bin


#native-notification-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-notification-itc
cp packaging/itc/native-notification-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-notification-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-notification-itc/bin

#native-package-manager-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-package-manager-itc
cp packaging/itc/native-package-manager-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-package-manager-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-package-manager-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-package-manager-itc/data
%ifarch i586
cp src/itc/package-manager/native-testapp-itc-0.1-0.i586.rpm %{buildroot}/opt/usr/apps/native-package-manager-itc/data/native-testapp-itc-0.1-0.i586.rpm
cp src/itc/package-manager/org.tizen.testapp-1.0.0-i386.tpk %{buildroot}/opt/usr/apps/native-package-manager-itc/data/org.tizen.testapp-1.0.0-i386.tpk
%else
cp src/itc/package-manager/native-testapp-itc-0.1-0.armv7l.rpm %{buildroot}/opt/usr/apps/native-package-manager-itc/data/native-testapp-itc-0.1-0.armv7l.rpm
cp src/itc/package-manager/org.tizen.testapp-1.0.0-arm.tpk %{buildroot}/opt/usr/apps/native-package-manager-itc/data/org.tizen.testapp-1.0.0-arm.tpk
%endif

#native-player-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-player-itc
cp packaging/itc/native-player-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-player-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-player-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-player-itc/data/
cp src/itc/player/short.mp3 %{buildroot}/opt/usr/apps/native-player-itc/data/short.mp3
cp src/itc/player/file.mp4 %{buildroot}/opt/usr/apps/native-player-itc/data/file.mp4
cp src/itc/player/sub.srt %{buildroot}/opt/usr/apps/native-player-itc/data/sub.srt
cp src/itc/player/v.mp4 %{buildroot}/opt/usr/apps/native-player-itc/data/v.mp4
cp src/itc/player/AWB_header_change_AMR.amr %{buildroot}/opt/usr/apps/native-player-itc/data/AWB_header_change_AMR.amr

#native-privilege-info-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-privilege-info-itc
cp packaging/itc/native-privilege-info-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-privilege-info-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-privilege-info-itc/bin

#native-push-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-push-itc
cp packaging/itc/native-push-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-push-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-push-itc/bin

#native-radio-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-radio-itc
cp packaging/itc/native-radio-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-radio-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-radio-itc/bin

#native-recorder-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-recorder-itc
cp packaging/itc/native-recorder-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-recorder-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-recorder-itc/bin

#native-runtime-info-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-runtime-info-itc
cp packaging/itc/native-runtime-info-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-runtime-info-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-runtime-info-itc/bin

#native-sensor-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-sensor-itc
cp packaging/itc/native-sensor-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-sensor-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-sensor-itc/bin

#native-sound-manager-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-sound-manager-itc
cp packaging/itc/native-sound-manager-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-sound-manager-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-sound-manager-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-sound-manager-itc/data

#native-stt-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-stt-itc
cp packaging/itc/native-stt-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-stt-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-stt-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-stt-itc/data
cp src/itc/stt/start_sound.wav %{buildroot}/opt/usr/apps/native-stt-itc/data/start_sound.wav
cp src/itc/stt/stop_sound.wav %{buildroot}/opt/usr/apps/native-stt-itc/data/stop_sound.wav

#native-system-info-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-system-info-itc
cp packaging/itc/native-system-info-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-system-info-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-system-info-itc/bin

#native-system-settings-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-system-settings-itc
cp packaging/itc/native-system-settings-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-system-settings-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-system-settings-itc/bin

#native-capi-system-system-settings-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-capi-system-system-settings-itc
cp packaging/itc/native-capi-system-system-settings-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-capi-system-system-settings-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-system-settings-itc/bin

#native-tbm-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-tbm-itc
cp packaging/itc/native-tbm-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-tbm-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-tbm-itc/bin

#native-telephony-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-telephony-itc
cp packaging/itc/native-telephony-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-telephony-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-telephony-itc/bin

#native-tone-player-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-tone-player-itc
cp packaging/itc/native-tone-player-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-tone-player-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-tone-player-itc/bin

#native-tts-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-tts-itc
cp packaging/itc/native-tts-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-tts-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-tts-itc/bin

#native-url-download-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-url-download-itc
cp packaging/itc/native-url-download-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-url-download-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-url-download-itc/bin

#native-wav-player-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-wav-player-itc
cp packaging/itc/native-wav-player-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-wav-player-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-wav-player-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-wav-player-itc/data/
cp src/itc/wav-player/WavPlayerTest.wav %{buildroot}/opt/usr/apps/native-wav-player-itc/data/WavPlayerTest.wav

#native-webkit2-itc
cp LICENSE %{buildroot}/usr/share/license/native-webkit2-itc
cp packaging/itc/native-webkit2-itc.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}/usr/apps/native-webkit2-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-webkit2-itc/bin
mkdir -p %{buildroot}/usr/apps/native-webkit2-itc/data/webkit2_files/resources
mkdir -p %{buildroot}/usr/apps/native-webkit2-itc/data/webkit2_files/resources/common
mkdir -p %{buildroot}/usr/apps/native-webkit2-itc/data/webkit2_files/resources/ewk_context_menu
mkdir -p %{buildroot}/usr/apps/native-webkit2-itc/data/webkit2_files/resources/ewk_view
cp src/itc/webkit2/resources/common/*.html %{buildroot}/usr/apps/native-webkit2-itc/data/webkit2_files/resources/common/
cp src/itc/webkit2/resources/ewk_context_menu/*.png %{buildroot}/usr/apps/native-webkit2-itc/data/webkit2_files/resources/ewk_context_menu/
cp src/itc/webkit2/resources/ewk_context_menu/*.html %{buildroot}/usr/apps/native-webkit2-itc/data/webkit2_files/resources/ewk_context_menu/
cp src/itc/webkit2/resources/ewk_view/*.html %{buildroot}/usr/apps/native-webkit2-itc/data/webkit2_files/resources/ewk_view/

#native-wifi-direct-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-wifi-direct-itc
cp packaging/itc/native-wifi-direct-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-wifi-direct-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-wifi-direct-itc/bin

#native-wifi-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-wifi-itc
cp packaging/itc/native-wifi-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-wifi-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-wifi-itc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-wifi-itc/data/
cp src/itc/wifi/cert.crt %{buildroot}/opt/usr/apps/native-wifi-itc/data/cert.crt
cp src/itc/wifi/testing.pem %{buildroot}/opt/usr/apps/native-wifi-itc/data/testing.pem

#native-multi-assistant-itc
cp LICENSE %{buildroot}/opt/usr/share/license/native-multi-assistant-itc
cp packaging/itc/native-multi-assistant-itc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-multi-assistant-itc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-multi-assistant-itc/bin

#*********End Adding ITC*********

#core-accounts-svc-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-accounts-svc-tests
cp packaging/utc/core-accounts-svc-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-accounts-svc-tests/bin
mkdir -p %{buildroot}/opt/usr/apps/core-accounts-svc-tests/shared/res
cp src/utc/accounts-svc/account.png %{buildroot}/opt/usr/apps/core-accounts-svc-tests/shared/res
cp src/utc/accounts-svc/account_small.png %{buildroot}/opt/usr/apps/core-accounts-svc-tests/shared/res

#core-appcore-agent-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-appcore-agent-tests
cp packaging/utc/core-appcore-agent-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-appcore-agent-tests/bin

#core-application-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-application-tests
cp packaging/utc/core-application-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-application-tests/bin
mkdir -p %{buildroot}/opt/usr/apps/core-application-tests/data
mkdir -p %{buildroot}/opt/usr/apps/core-application-tests/res
cp -r src/utc/application/res/* %{buildroot}/opt/usr/apps/core-application-tests/res

#core-app-manager-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-app-manager-tests
cp packaging/utc/core-app-manager-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-app-manager-tests/bin

#core-audio-io-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-audio-io-tests
cp packaging/utc/core-audio-io-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-audio-io-tests/bin

#core-badge-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-badge-tests
cp packaging/utc/core-badge-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-badge-tests/bin

#core-base-utils-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-base-utils-tests
cp packaging/utc/core-base-utils-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-base-utils-tests/bin

#core-battery-monitor-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-battery-monitor-tests
cp packaging/utc/core-battery-monitor-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-battery-monitor-tests/bin

#core-bluetooth-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-bluetooth-tests
cp packaging/utc/core-bluetooth-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-bluetooth-tests/bin

#core-bundle-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-bundle-tests
cp packaging/utc/core-bundle-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-bundle-tests/bin

#core-calendar-service2-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-calendar-service2-tests
cp packaging/utc/core-calendar-service2-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-calendar-service2-tests/bin

#core-camera-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-camera-tests
cp packaging/utc/core-camera-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-camera-tests/bin

#core-mediatool-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-mediatool-tests
cp packaging/utc/core-mediatool-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-mediatool-tests/bin

#core-capi-message-port-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-capi-message-port-tests
cp packaging/utc/core-capi-message-port-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-capi-message-port-tests/bin
install -m 755 src/utc/capi-message-port/core-capi-message-port-tests.sh %{buildroot}/opt/usr/apps/core-capi-message-port-tests/bin

#core-connection-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-connection-tests
cp packaging/utc/core-connection-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-connection-tests/bin

#core-contacts-service2-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-contacts-service2-tests
cp packaging/utc/core-contacts-service2-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-contacts-service2-tests/bin
mkdir -p %{buildroot}/opt/usr/apps/core-contacts-service2-tests/shared/res
cp src/utc/contacts-service2/account.png %{buildroot}/opt/usr/apps/core-contacts-service2-tests/shared/res
cp src/utc/contacts-service2/account_small.png %{buildroot}/opt/usr/apps/core-contacts-service2-tests/shared/res

#core-motion-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-motion-tests
cp packaging/utc/core-motion-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-motion-tests/bin

#core-data-control-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-data-control-tests
cp packaging/utc/core-data-control-tests.xml %{buildroot}/opt/share/packages/

#core-device-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-device-tests
cp packaging/utc/core-device-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-device-tests/bin

#core-dlog-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-dlog-tests
cp packaging/utc/core-dlog-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-dlog-tests/bin

#core-efl-util-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-efl-util-tests
cp packaging/utc/core-efl-util-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-efl-util-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-efl-util-tests/bin

#core-efl-extension-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-efl-extension-tests
cp packaging/utc/core-efl-extension-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-efl-extension-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-efl-extension-tests/bin

#core-email-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-email-tests
cp packaging/utc/core-email-tests.xml %{buildroot}/opt/share/packages/

#core-fido-client-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-fido-client-tests
cp packaging/utc/core-fido-client-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-fido-client-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-fido-client-tests/bin

#core-image-util-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-image-util-tests
cp packaging/utc/core-image-util-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-image-util-tests/bin

#core-key-manager-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-key-manager-tests
cp packaging/utc/core-key-manager-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-key-manager-tests/bin

#core-libstorage-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-libstorage-tests
cp packaging/utc/core-libstorage-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-libstorage-tests/bin

#core-location-manager-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-location-manager-tests
cp packaging/utc/core-location-manager-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-location-manager-tests/bin

#core-mediacodec-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-mediacodec-tests
cp packaging/utc/core-mediacodec-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-mediacodec-tests/bin

#core-media-content-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-media-content-tests
cp packaging/utc/core-media-content-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-media-content-tests/bin

#core-media-controller-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-media-controller-tests
cp packaging/utc/core-media-controller-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-media-controller-tests/bin

#core-media-key-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-media-key-tests
cp packaging/utc/core-media-key-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-media-key-tests/bin

#core-messages-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-messages-tests
cp packaging/utc/core-messages-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-messages-tests/bin

#core-metadata-extractor-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-metadata-extractor-tests
cp packaging/utc/core-metadata-extractor-tests.xml %{buildroot}/opt/share/packages/

#core-mime-type-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-mime-type-tests
cp packaging/utc/core-mime-type-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-mime-type-tests/bin

#core-native-common-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-native-common-tests
cp packaging/utc/core-native-common-tests.xml %{buildroot}/opt/share/packages/

#core-nfc-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-nfc-tests
cp packaging/utc/core-nfc-tests.xml %{buildroot}/opt/share/packages/

#core-smartcard-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-smartcard-tests
cp packaging/utc/core-smartcard-tests.xml %{buildroot}/opt/share/packages/

#core-notification-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-notification-tests
cp packaging/utc/core-notification-tests.xml %{buildroot}/opt/share/packages/

#core-package-manager-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-package-manager-tests
cp packaging/utc/core-package-manager-tests.xml %{buildroot}/opt/share/packages/

#core-player-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-player-tests
cp packaging/utc/core-player-tests.xml %{buildroot}/opt/share/packages/

#core-privilege-info-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-privilege-info-tests
cp packaging/utc/core-privilege-info-tests.xml %{buildroot}/opt/share/packages/

#core-push-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-push-tests
cp packaging/utc/core-push-tests.xml %{buildroot}/opt/share/packages/

#core-radio-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-radio-tests
cp packaging/utc/core-radio-tests.xml %{buildroot}/opt/share/packages/

#core-streamrecorder-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-streamrecorder-tests
cp packaging/utc/core-streamrecorder-tests.xml %{buildroot}/opt/share/packages/

#core-recorder-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-recorder-tests
cp packaging/utc/core-recorder-tests.xml %{buildroot}/opt/share/packages/

#core-runtime-info-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-runtime-info-tests
cp packaging/utc/core-runtime-info-tests.xml %{buildroot}/opt/share/packages/

#core-sensor-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-sensor-tests
cp packaging/utc/core-sensor-tests.xml %{buildroot}/opt/share/packages/

#core-shortcut-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-shortcut-tests
cp packaging/utc/core-shortcut-tests.xml %{buildroot}/opt/share/packages/

#core-sound-manager-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-sound-manager-tests
cp packaging/utc/core-sound-manager-tests.xml %{buildroot}/opt/share/packages/

#core-stt-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-stt-tests
cp packaging/utc/core-stt-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-stt-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-stt-tests/bin

#core-sync-manager-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-sync-manager-tests
cp packaging/utc/core-sync-manager-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-sync-manager-tests/bin
mkdir -p %{buildroot}/opt/usr/apps/core-sync-manager-tests/shared/res
cp src/utc/sync-manager/sync.png %{buildroot}/opt/usr/apps/core-sync-manager-tests/shared/res
cp src/utc/sync-manager/sync_small.png %{buildroot}/opt/usr/apps/sync-manager-tests/shared/res

#core-system-info-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-system-info-tests
cp packaging/utc/core-system-info-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-system-info-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-system-info-tests/bin

#core-capi-system-system-settings-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-capi-system-system-settings-tests
cp packaging/utc/core-capi-system-system-settings-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-capi-system-system-settings-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-capi-system-system-settings-tests/bin

#core-tbm-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-tbm-tests
cp packaging/utc/core-tbm-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-tbm-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-tbm-tests/bin

#core-telephony-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-telephony-tests
cp packaging/utc/core-telephony-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-telephony-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-telephony-tests/bin

#core-tone-player-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-tone-player-tests
cp packaging/utc/core-tone-player-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-tone-player-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-tone-player-tests/bin

#core-sound-pool-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-sound-pool-tests
cp packaging/utc/core-sound-pool-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-sound-pool-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-sound-pool-tests/bin

#core-tts-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-tts-tests
cp packaging/utc/core-tts-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-tts-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-tts-tests/bin

#core-url-download-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-url-download-tests
cp packaging/utc/core-url-download-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-url-download-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-url-download-tests/bin

#core-wav-player-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-wav-player-tests
cp packaging/utc/core-wav-player-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-wav-player-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-wav-player-tests/bin

#core-webkit2-tests
cp LICENSE %{buildroot}/usr/share/license/core-webkit2-tests
cp packaging/utc/core-webkit2-tests.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}/usr/apps/core-webkit2-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/usr/apps/core-webkit2-tests/bin

#core-wifi-direct-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-wifi-direct-tests
cp packaging/utc/core-wifi-direct-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-wifi-direct-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-wifi-direct-tests/bin

#core-wifi-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-wifi-tests
cp packaging/utc/core-wifi-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-wifi-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-wifi-tests/bin

#core-multi-assistant-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-multi-assistant-tests
cp packaging/utc/core-multi-assistant-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-multi-assistant-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-multi-assistant-tests/bin

#core-capi-ui-sticker-tests
cp LICENSE %{buildroot}/opt/usr/share/license/core-capi-ui-sticker-tests
cp packaging/utc/core-capi-ui-sticker-tests.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/core-capi-ui-sticker-tests/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/core-capi-ui-sticker-tests/bin

# End Adding for UTC******************************************************************************************************************************

#native-audio-io-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-audio-io-ctc
cp packaging/ctc/native-audio-io-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-audio-io-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-audio-io-ctc/bin

#native-camera-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-camera-ctc
cp packaging/ctc/native-camera-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-camera-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-camera-ctc/bin

#native-connection-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-connection-ctc
cp packaging/ctc/native-connection-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-connection-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-connection-ctc/bin

#native-device-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-device-ctc
cp packaging/ctc/native-device-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-device-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-device-ctc/bin

#native-filesystem-permission-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-filesystem-permission-ctc
cp packaging/ctc/native-filesystem-permission-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-filesystem-permission-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-filesystem-permission-ctc/bin

#native-image-util-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-image-util-ctc
cp packaging/ctc/native-image-util-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-image-util-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-image-util-ctc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-image-util-ctc/data/
cp src/ctc/image-util/ImageUtil_sample.jpg %{buildroot}/opt/usr/apps/native-image-util-ctc/data/ImageUtil_sample.jpg

#native-libstorage-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-libstorage-ctc
cp packaging/ctc/native-libstorage-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-libstorage-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-libstorage-ctc/bin

#native-system-info-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-system-info-ctc
cp packaging/ctc/native-system-info-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-system-info-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-system-info-ctc/bin

#native-telephony-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-telephony-ctc
cp packaging/ctc/native-telephony-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-telephony-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-telephony-ctc/bin

#native-wifi-direct-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-wifi-direct-ctc
cp packaging/ctc/native-wifi-direct-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-wifi-direct-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-wifi-direct-ctc/bin

#native-location-manager-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-location-manager-ctc
cp packaging/ctc/native-location-manager-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-location-manager-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-location-manager-ctc/bin

#native-media-codec-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-media-codec-ctc
cp packaging/ctc/native-media-codec-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-media-codec-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-media-codec-ctc/bin

#native-opengl-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-opengl-ctc
cp packaging/ctc/native-opengl-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-opengl-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-opengl-ctc/bin

#native-platform-permission-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-platform-permission-ctc
mkdir -p %{buildroot}/opt/usr/apps/native-platform-permission-ctc/data/
cp src/ctc/platform-permission/native-platform-permission-ctc-0.1-0.armv7l.rpm %{buildroot}/opt/usr/apps/native-platform-permission-ctc/data/native-platform-permission-ctc-0.1-0.armv7l.rpm
cp packaging/ctc/native-platform-permission-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-platform-permission-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-platform-permission-ctc/bin
mkdir -p %{buildroot}/opt/usr/media/Images
cp src/ctc/platform-permission/PlatformPermission_test.jpg %{buildroot}/opt/usr/media/Images/PlatformPermission_test.jpg

%ifarch armv7l
cp src/ctc/platform-permission/org.tizen.datacontrolprovider-0.0.1-1.armv7l.rpm %{buildroot}/tmp/
cp src/ctc/platform-permission/org.tizen.testapplication-1.0.0-arm.tpk %{buildroot}/opt/usr/apps/native-platform-permission-ctc/data/org.tizen.testapplication-1.0.0-arm.tpk
%else
cp src/ctc/platform-permission/org.tizen.datacontrolprovider-0.0.1-1.i586.rpm %{buildroot}/tmp/
cp src/ctc/platform-permission/org.tizen.testapplication-1.0.0-i386.tpk %{buildroot}/opt/usr/apps/native-platform-permission-ctc/data/org.tizen.testapplication-1.0.0-i386.tpk
%endif

#native-player-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-player-ctc
cp packaging/ctc/native-player-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-player-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-player-ctc/bin
mkdir -p %{buildroot}/opt/usr/apps/native-player-ctc/res/
cp src/ctc/player/MediaPlayer.mp3 %{buildroot}/opt/usr/apps/native-player-ctc/res/MediaPlayer.mp3

#native-runtime-info-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-runtime-info-ctc
cp packaging/ctc/native-runtime-info-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-runtime-info-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-runtime-info-ctc/bin

#native-sensor-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-sensor-ctc
cp packaging/ctc/native-sensor-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-sensor-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-sensor-ctc/bin

#native-sound-manager-ctc
cp LICENSE %{buildroot}/opt/usr/share/license/native-sound-manager-ctc
cp packaging/ctc/native-sound-manager-ctc.xml %{buildroot}/opt/share/packages/
mkdir -p %{buildroot}/opt/usr/apps/native-sound-manager-ctc/bin
#cp templates/external_wrapper.sh %{buildroot}/opt/usr/apps/native-sound-manager-ctc/bin


%post
chown -R 5000:5000 /opt/usr/apps/native-app-manager-itc/data
chsmack -a native-app-manager-itc /opt/usr/apps/native-app-manager-itc/data
chown -R 5000:5000 /opt/usr/apps/native-accounts-svc-itc/data
chsmack -a native-accounts-svc-itc /opt/usr/apps/native-accounts-svc-itc/data
chown -R 5000:5000 /opt/usr/apps/native-application-itc/data
chsmack -a native-application-itc /opt/usr/apps/native-application-itc/data
chown -R 5000:5000 /opt/usr/apps/native-audio-io-itc/data
chsmack -a native-audio-io-itc /opt/usr/apps/native-audio-io-itc/data
chown -R 5000:5000 /opt/usr/apps/native-bluetooth-itc/data
chsmack -a native-bluetooth-itc /opt/usr/apps/native-bluetooth-itc/data
chown -R 5000:5000 /opt/usr/apps/native-contacts-service2-itc/data
chsmack -a native-contacts-service2-itc /opt/usr/apps/native-contacts-service2-itc/data
chown -R 5000:5000 /opt/usr/apps/native-data-control-itc/data
chsmack -a native-data-control-itc /opt/usr/apps/native-data-control-itc/data
chown -R 5000:5000 /opt/usr/apps/native-email-itc/data
chsmack -a native-email-itc /opt/usr/apps/native-email-itc/data
chown -R 5000:5000 /opt/usr/apps/native-image-util-itc/data
chsmack -a native-image-util-itc /opt/usr/apps/native-image-util-itc/data
chown -R 5000:5000 /opt/usr/apps/native-key-manager-itc/data
chsmack -a native-key-manager-itc /opt/usr/apps/native-key-manager-itc/data
chown -R 5000:5000 /opt/usr/apps/native-media-codec-itc/data
chsmack -a native-media-codec-itc /opt/usr/apps/native-media-codec-itc/data
chown -R 5000:5000 /opt/usr/apps/native-media-content-itc/data
chown -R app:app /opt/usr/media/Sounds
chown -R app:app /opt/usr/media/Images/
chown -R app:app /opt/usr/media/DCIM/
chown -R app:app /opt/usr/media/Dummy/
chown -R app:app /opt/usr/media/test*
chown -R app:app /opt/usr/media/NewName/
chmod -R 777 /opt/usr/media/Sounds
chmod -R 777 /opt/usr/media/Images
chmod -R 777 /opt/usr/media/DCIM
chmod -R 777 /opt/usr/media/Dummy
chmod -R 777 /opt/usr/media/NewName
chmod -R 777 /opt/usr/media/test*
chsmack -a system::media /opt/usr/media/Sounds
chsmack -a system::media /opt/usr/media/Images
chsmack -a system::media /opt/usr/media/DCIM
chsmack -a system::media /opt/usr/media/Dummy
chsmack -a system::media /opt/usr/media/NewName
chsmack -a system::media /opt/usr/media/test*
chsmack -a native-media-content-itc /opt/usr/apps/native-media-content-itc/data
chown -R 5000:5000 /opt/usr/apps/native-messages-itc/data
chsmack -a native-messages-itc /opt/usr/apps/native-messages-itc/data
chown -R 5000:5000 /opt/usr/apps/native-metadata-extractor-itc/data
chsmack -a native-metadata-extractor-itc /opt/usr/apps/native-metadata-extractor-itc/data
chown -R 5000:5000 /opt/usr/apps/native-package-manager-itc/data
chsmack -a native-package-manager-itc /opt/usr/apps/native-package-manager-itc/data
chown -R 5000:5000 /opt/usr/apps/native-player-itc/data
chsmack -a native-player-itc /opt/usr/apps/native-player-itc/data
chown -R 5000:5000 /opt/usr/apps/native-sensor-itc/data
chsmack -a native-sensor-itc /opt/usr/apps/native-sensor-itc/data
chown -R 5000:5000 /opt/usr/apps/native-sound-manager-itc/data
chsmack -a native-sound-manager-itc /opt/usr/apps/native-sound-manager-itc/data
chown -R 5000:5000 /opt/usr/apps/native-stt-itc/data
chsmack -a native-stt-itc /opt/usr/apps/native-stt-itc/data
chown -R 5000:5000 /opt/usr/apps/native-system-settings-itc/data
chsmack -a native-system-settings-itc /opt/usr/apps/native-system-settings-itc/data
chown -R 5000:5000 /opt/usr/apps/native-tone-player-itc/data
chsmack -a native-tone-player-itc /opt/usr/apps/native-tone-player-itc/data
chown -R 5000:5000 /opt/usr/apps/native-wav-player-itc/data
chsmack -a native-wav-player-itc /opt/usr/apps/native-wav-player-itc/data
chown -R 5000:5000 /opt/usr/apps/native-wifi-itc/data
chsmack -a native-wifi-itc /opt/usr/apps/native-wifi-itc/data

chown -R 5000:5000 /opt/usr/apps/native-image-util-ctc/data
chsmack -a %{name} /opt/usr/apps/native-image-util-ctc/data

chown -R 5000:5000 /opt/usr/apps/native-platform-permission-ctc/data
chsmack -a %{name} /opt/usr/apps/native-platform-permission-ctc/data
%ifarch armv7l
pkgcmd -i -q -t rpm -p /tmp/org.tizen.datacontrolprovider-0.0.1-1.armv7l.rpm &
%else
pkgcmd -i -q -t rpm -p /tmp/org.tizen.datacontrolprovider-0.0.1-1.i586.rpm &
%endif

chown -R 5000:5000 /opt/usr/apps/core-application-tests/data
chsmack -a %{name} /opt/usr/apps/core-application-tests/data

/opt/usr/apps/core-capi-message-port-tests/bin/core-capi-message-port-tests.sh

/usr/bin/mediadb-update -r /opt/usr/media

%post -n native-application-itc
%ifarch armv7l
pkgcmd -i -q -t tpk -p /opt/usr/apps/native-application-itc/data/org.tizen.testapplication-1.0.0-arm.tpk &
%else
pkgcmd -i -q -t tpk -p /opt/usr/apps/native-application-itc/data/org.tizen.testapplication-1.0.0-i386.tpk &
%endif

%post -n native-data-control-itc
%ifarch i586
pkgcmd -i -q -t rpm -p /opt/usr/apps/native-data-control-itc/data/org.tizen.datacontrolprovider-0.0.1-1.i586.rpm &
%else
pkgcmd -i -q -t rpm -p /opt/usr/apps/native-data-control-itc/data/org.tizen.datacontrolprovider-0.0.1-1.armv7l.rpm &
%endif

%post -n native-package-manager-itc
%ifarch i586
pkgcmd -i -q -t rpm -p /opt/usr/apps/native-package-manager-itc/data/native-testapp-itc-0.1-0.i586.rpm &
pkgcmd -i -q -t tpk -p /opt/usr/apps/native-package-manager-itc/data/org.tizen.testapp-1.0.0-i386.tpk &
%else
pkgcmd -i -q -t rpm -p /opt/usr/apps/native-package-manager-itc/data/native-testapp-itc-0.1-0.armv7l.rpm &
pkgcmd -i -q -t tpk -p /opt/usr/apps/native-package-manager-itc/data/org.tizen.testapp-1.0.0-arm.tpk &
%endif

%postun
pkgcmd -un  org.tizen.appmanagertestfile
pkgcmd -un  org.tizen.testapplication

%postun -n native-application-itc
pkgcmd -un org.tizen.testapplication &

%postun -n native-data-control-itc
pkgcmd -u -n org.tizen.datacontrolprovider &

%postun -n native-package-manager-itc
pkgcmd -un native-testapp-itc &
pkgcmd -un org.tizen.testapp &

#******************files processing entry start******************

%files -n native-app-manager-itc
/opt/usr/apps/native-app-manager-itc/*
/opt/share/packages/native-app-manager-itc.xml
/opt/usr/share/license/native-app-manager-itc

%files -n native-accounts-svc-itc
/opt/usr/apps/native-accounts-svc-itc/*
/opt/share/packages/native-accounts-svc-itc.xml
/opt/usr/share/license/native-accounts-svc-itc

%files -n native-appcore-agent-itc
/opt/usr/apps/native-appcore-agent-itc/*
/opt/share/packages/native-appcore-agent-itc.xml
/opt/usr/share/license/native-appcore-agent-itc

%files -n native-application-itc
/opt/usr/apps/native-application-itc/*
/opt/share/packages/native-application-itc.xml
/opt/usr/share/license/native-application-itc

%files -n native-audio-io-itc
/opt/usr/apps/native-audio-io-itc/*
/opt/share/packages/native-audio-io-itc.xml
/opt/usr/share/license/native-audio-io-itc

%files -n native-badge-itc
/opt/usr/apps/native-badge-itc/*
/opt/share/packages/native-badge-itc.xml
/opt/usr/share/license/native-badge-itc

%files -n native-base-utils-itc
/opt/usr/apps/native-base-utils-itc/*
/opt/share/packages/native-base-utils-itc.xml
/opt/usr/share/license/native-base-utils-itc

%files -n native-battery-monitor-itc
/opt/usr/apps/native-battery-monitor-itc/*
/opt/share/packages/native-battery-monitor-itc.xml
/opt/usr/share/license/native-battery-monitor-itc

%files -n native-bluetooth-itc
/opt/usr/apps/native-bluetooth-itc/*
/opt/share/packages/native-bluetooth-itc.xml
/opt/usr/share/license/native-bluetooth-itc

%files -n native-bundle-itc
/opt/usr/apps/native-bundle-itc/*
/opt/share/packages/native-bundle-itc.xml
/opt/usr/share/license/native-bundle-itc

%files -n native-calendar-service2-itc
/opt/usr/apps/native-calendar-service2-itc/*
/opt/share/packages/native-calendar-service2-itc.xml
/opt/usr/share/license/native-calendar-service2-itc

%files -n native-camera-itc
/opt/usr/apps/native-camera-itc/*
/opt/share/packages/native-camera-itc.xml
/opt/usr/share/license/native-camera-itc

%files -n native-capi-media-tool-itc
/opt/usr/apps/native-capi-media-tool-itc/*
/opt/share/packages/native-capi-media-tool-itc.xml
/opt/usr/share/license/native-capi-media-tool-itc

%files -n native-connection-itc
/opt/usr/apps/native-connection-itc/*
/opt/share/packages/native-connection-itc.xml
/opt/usr/share/license/native-connection-itc

%files -n native-contacts-service2-itc
/opt/usr/apps/native-contacts-service2-itc/*
/opt/share/packages/native-contacts-service2-itc.xml
/opt/usr/share/license/native-contacts-service2-itc

%files -n native-motion-itc
/opt/usr/apps/native-motion-itc/*
/opt/share/packages/native-motion-itc.xml
/opt/usr/share/license/native-motion-itc

%files -n native-data-control-itc
/opt/usr/apps/native-data-control-itc/*
/opt/share/packages/native-data-control-itc.xml
/opt/usr/share/license/native-data-control-itc

%files -n native-device-itc
/opt/usr/apps/native-device-itc/*
/opt/share/packages/native-device-itc.xml
/opt/usr/share/license/native-device-itc

%files -n native-dlog-itc
/opt/usr/apps/native-dlog-itc/*
/opt/share/packages/native-dlog-itc.xml
/opt/usr/share/license/native-dlog-itc

%files -n native-efl-util-itc
/opt/usr/apps/native-efl-util-itc/*
/opt/share/packages/native-efl-util-itc.xml
/opt/usr/share/license/native-efl-util-itc

%files -n native-email-itc
/opt/usr/apps/native-email-itc/*
/opt/share/packages/native-email-itc.xml
/opt/usr/share/license/native-email-itc

%files -n native-image-util-itc
/opt/usr/apps/native-image-util-itc/*
/opt/share/packages/native-image-util-itc.xml
/opt/usr/share/license/native-image-util-itc

%files -n native-key-manager-itc
/opt/usr/apps/native-key-manager-itc/*
/opt/share/packages/native-key-manager-itc.xml
/opt/usr/share/license/native-key-manager-itc

%files -n native-libstorage-itc
/opt/usr/apps/native-libstorage-itc/*
/opt/share/packages/native-libstorage-itc.xml
/opt/usr/share/license/native-libstorage-itc

%files -n native-location-manager-itc
/opt/usr/apps/native-location-manager-itc/*
/opt/share/packages/native-location-manager-itc.xml
/opt/usr/share/license/native-location-manager-itc

%files -n native-media-codec-itc
/opt/usr/apps/native-media-codec-itc/*
/opt/share/packages/native-media-codec-itc.xml
/opt/usr/share/license/native-media-codec-itc

%files -n native-media-content-itc
/opt/usr/apps/native-media-content-itc/*
/opt/share/packages/native-media-content-itc.xml
/opt/usr/share/license/native-media-content-itc
/opt/usr/media/*

%files -n native-media-key-itc
/opt/usr/apps/native-media-key-itc/*
/opt/share/packages/native-media-key-itc.xml
/opt/usr/share/license/native-media-key-itc

%files -n native-message-port-itc
/opt/usr/apps/native-message-port-itc/*
/opt/share/packages/native-message-port-itc.xml
/opt/usr/share/license/native-message-port-itc

%files -n native-messages-itc
/opt/usr/apps/native-messages-itc/*
/opt/share/packages/native-messages-itc.xml
/opt/usr/share/license/native-messages-itc

%files -n native-metadata-extractor-itc
/opt/usr/apps/native-metadata-extractor-itc/*
/opt/share/packages/native-metadata-extractor-itc.xml
/opt/usr/share/license/native-metadata-extractor-itc

%files -n native-mime-type-itc
/opt/usr/apps/native-mime-type-itc/*
/opt/share/packages/native-mime-type-itc.xml
/opt/usr/share/license/native-mime-type-itc

%files -n native-native-common-itc
/opt/usr/apps/native-native-common-itc/*
/opt/share/packages/native-native-common-itc.xml
/opt/usr/share/license/native-native-common-itc

%files -n native-nfc-itc
/opt/usr/apps/native-nfc-itc/*
/opt/share/packages/native-nfc-itc.xml
/opt/usr/share/license/native-nfc-itc

%files -n native-notification-itc
/opt/usr/apps/native-notification-itc/*
/opt/share/packages/native-notification-itc.xml
/opt/usr/share/license/native-notification-itc

%files -n native-package-manager-itc
/opt/usr/apps/native-package-manager-itc/*
/opt/share/packages/native-package-manager-itc.xml
/opt/usr/share/license/native-package-manager-itc

%files -n native-player-itc
/opt/usr/apps/native-player-itc/*
/opt/share/packages/native-player-itc.xml
/opt/usr/share/license/native-player-itc

%files -n native-privilege-info-itc
/opt/usr/apps/native-privilege-info-itc/*
/opt/share/packages/native-privilege-info-itc.xml
/opt/usr/share/license/native-privilege-info-itc

%files -n native-push-itc
/opt/usr/apps/native-push-itc/*
/opt/share/packages/native-push-itc.xml
/opt/usr/share/license/native-push-itc

%files -n native-radio-itc
/opt/usr/apps/native-radio-itc/*
/opt/share/packages/native-radio-itc.xml
/opt/usr/share/license/native-radio-itc

%files -n native-recorder-itc
/opt/usr/apps/native-recorder-itc/*
/opt/share/packages/native-recorder-itc.xml
/opt/usr/share/license/native-recorder-itc

%files -n native-runtime-info-itc
/opt/usr/apps/native-runtime-info-itc/*
/opt/share/packages/native-runtime-info-itc.xml
/opt/usr/share/license/native-runtime-info-itc

%files -n native-sensor-itc
/opt/usr/apps/native-sensor-itc/*
/opt/share/packages/native-sensor-itc.xml
/opt/usr/share/license/native-sensor-itc

%files -n native-sound-manager-itc
/opt/usr/apps/native-sound-manager-itc/*
/opt/share/packages/native-sound-manager-itc.xml
/opt/usr/share/license/native-sound-manager-itc

%files -n native-stt-itc
/opt/usr/apps/native-stt-itc/*
/opt/share/packages/native-stt-itc.xml
/opt/usr/share/license/native-stt-itc

%files -n native-system-info-itc
/opt/usr/apps/native-system-info-itc/*
/opt/share/packages/native-system-info-itc.xml
/opt/usr/share/license/native-system-info-itc

%files -n native-system-settings-itc
/opt/usr/apps/native-system-settings-itc/*
/opt/share/packages/native-system-settings-itc.xml
/opt/usr/share/license/native-system-settings-itc

%files -n native-capi-system-system-settings-itc
/opt/usr/apps/native-capi-system-system-settings-itc/*
/opt/share/packages/native-capi-system-system-settings-itc.xml
/opt/usr/share/license/native-capi-system-system-settings-itc

%files -n native-tbm-itc
/opt/usr/apps/native-tbm-itc/*
/opt/share/packages/native-tbm-itc.xml
/opt/usr/share/license/native-tbm-itc

%files -n native-telephony-itc
/opt/usr/apps/native-telephony-itc/*
/opt/share/packages/native-telephony-itc.xml
/opt/usr/share/license/native-telephony-itc

%files -n native-tone-player-itc
/opt/usr/apps/native-tone-player-itc/*
/opt/share/packages/native-tone-player-itc.xml
/opt/usr/share/license/native-tone-player-itc

%files -n native-tts-itc
/opt/usr/apps/native-tts-itc/*
/opt/share/packages/native-tts-itc.xml
/opt/usr/share/license/native-tts-itc

%files -n native-url-download-itc
/opt/usr/apps/native-url-download-itc/*
/opt/share/packages/native-url-download-itc.xml
/opt/usr/share/license/native-url-download-itc

%files -n native-wav-player-itc
/opt/usr/apps/native-wav-player-itc/*
/opt/share/packages/native-wav-player-itc.xml
/opt/usr/share/license/native-wav-player-itc

%files -n native-webkit2-itc
/usr/apps/native-webkit2-itc/*
/usr/share/packages/native-webkit2-itc.xml
/usr/share/license/native-webkit2-itc

%files -n native-wifi-direct-itc
/opt/usr/apps/native-wifi-direct-itc/*
/opt/share/packages/native-wifi-direct-itc.xml
/opt/usr/share/license/native-wifi-direct-itc

%files -n native-wifi-itc
/opt/usr/apps/native-wifi-itc/*
/opt/share/packages/native-wifi-itc.xml
/opt/usr/share/license/native-wifi-itc

%files -n native-multi-assistant-itc
/opt/usr/apps/native-multi-assistant-itc/*
/opt/share/packages/native-multi-assistant-itc.xml
/opt/usr/share/license/native-multi-assistant-itc

#******************End Adding ITC******************

%files -n core-accounts-svc-tests
/opt/usr/apps/core-accounts-svc-tests/*
/opt/share/packages/core-accounts-svc-tests.xml
/opt/usr/share/license/core-accounts-svc-tests

%files -n core-appcore-agent-tests
/opt/usr/apps/core-appcore-agent-tests/*
/opt/share/packages/core-appcore-agent-tests.xml
/opt/usr/share/license/core-appcore-agent-tests

%files -n core-application-tests
/opt/usr/apps/core-application-tests/*
/opt/share/packages/core-application-tests.xml
/opt/usr/share/license/core-application-tests

%files -n core-app-manager-tests
/opt/usr/apps/core-app-manager-tests/*
/opt/share/packages/core-app-manager-tests.xml
/opt/usr/share/license/core-app-manager-tests

%files -n core-audio-io-tests
/opt/usr/apps/core-audio-io-tests/*
/opt/share/packages/core-audio-io-tests.xml
/opt/usr/share/license/core-audio-io-tests

%files -n core-badge-tests
/opt/usr/apps/core-badge-tests/*
/opt/share/packages/core-badge-tests.xml
/opt/usr/share/license/core-badge-tests

%files -n core-base-utils-tests
/opt/usr/apps/core-base-utils-tests/*
/opt/share/packages/core-base-utils-tests.xml
/opt/usr/share/license/core-base-utils-tests

%files -n core-bluetooth-tests
/opt/usr/apps/core-bluetooth-tests/*
/opt/share/packages/core-bluetooth-tests.xml
/opt/usr/share/license/core-bluetooth-tests

%files -n core-bundle-tests
/opt/usr/apps/core-bundle-tests/*
/opt/share/packages/core-bundle-tests.xml
/opt/usr/share/license/core-bundle-tests

%files -n core-calendar-service2-tests
/opt/usr/apps/core-calendar-service2-tests/*
/opt/share/packages/core-calendar-service2-tests.xml
/opt/usr/share/license/core-calendar-service2-tests

%files -n core-camera-tests
/opt/usr/apps/core-camera-tests/*
/opt/share/packages/core-camera-tests.xml
/opt/usr/share/license/core-camera-tests

%files -n core-mediatool-tests
/opt/usr/apps/core-mediatool-tests/*
/opt/share/packages/core-mediatool-tests.xml
/opt/usr/share/license/core-mediatool-tests

%files -n core-capi-message-port-tests
/opt/usr/apps/core-capi-message-port-tests/*
/opt/share/packages/core-capi-message-port-tests.xml
/opt/usr/share/license/core-capi-message-port-tests

%files -n core-connection-tests
/opt/usr/apps/core-connection-tests/*
/opt/share/packages/core-connection-tests.xml
/opt/usr/share/license/core-connection-tests

%files -n core-contacts-service2-tests
/opt/usr/apps/core-contacts-service2-tests/*
/opt/share/packages/core-contacts-service2-tests.xml
/opt/usr/share/license/core-contacts-service2-tests

%files -n core-motion-tests
/opt/usr/apps/core-motion-tests/*
/opt/share/packages/core-motion-tests.xml
/opt/usr/share/license/core-motion-tests

%files -n core-data-control-tests
/opt/usr/apps/core-data-control-tests/*
/opt/share/packages/core-data-control-tests.xml
/opt/usr/share/license/core-data-control-tests

%files -n core-device-tests
/opt/usr/apps/core-device-tests/*
/opt/share/packages/core-device-tests.xml
/opt/usr/share/license/core-device-tests

%files -n core-dlog-tests
/opt/usr/apps/core-dlog-tests/*
/opt/share/packages/core-dlog-tests.xml
/opt/usr/share/license/core-dlog-tests

%files -n core-efl-util-tests
/opt/usr/apps/core-efl-util-tests/*
/opt/share/packages/core-efl-util-tests.xml
/opt/usr/share/license/core-efl-util-tests

%files -n core-efl-extension-tests
/opt/usr/apps/core-efl-extension-tests/*
/opt/share/packages/core-efl-extension-tests.xml
/opt/usr/share/license/core-efl-extension-tests

%files -n core-email-tests
/opt/usr/apps/core-email-tests/*
/opt/share/packages/core-email-tests.xml
/opt/usr/share/license/core-email-tests

%files -n core-image-util-tests
/opt/usr/apps/core-image-util-tests/*
/opt/share/packages/core-image-util-tests.xml
/opt/usr/share/license/core-image-util-tests

%files -n core-key-manager-tests
/opt/usr/apps/core-key-manager-tests/*
/opt/share/packages/core-key-manager-tests.xml
/opt/usr/share/license/core-key-manager-tests

%files -n core-libstorage-tests
/opt/usr/apps/core-libstorage-tests/*
/opt/share/packages/core-libstorage-tests.xml
/opt/usr/share/license/core-libstorage-tests

%files -n core-location-manager-tests
/opt/usr/apps/core-location-manager-tests/*
/opt/share/packages/core-location-manager-tests.xml
/opt/usr/share/license/core-location-manager-tests

%files -n core-mediacodec-tests
/opt/usr/apps/core-mediacodec-tests/*
/opt/share/packages/core-mediacodec-tests.xml
/opt/usr/share/license/core-mediacodec-tests

%files -n core-media-content-tests
/opt/usr/apps/core-media-content-tests/*
/opt/share/packages/core-media-content-tests.xml
/opt/usr/share/license/core-media-content-tests

%files -n core-media-controller-tests
/opt/usr/apps/core-media-controller-tests/*
/opt/share/packages/core-media-controller-tests.xml
/opt/usr/share/license/core-media-controller-tests

%files -n core-media-key-tests
/opt/usr/apps/core-media-key-tests/*
/opt/share/packages/core-media-key-tests.xml
/opt/usr/share/license/core-media-key-tests

%files -n core-messages-tests
/opt/usr/apps/core-messages-tests/*
/opt/share/packages/core-messages-tests.xml
/opt/usr/share/license/core-messages-tests

%files -n core-metadata-extractor-tests
/opt/usr/apps/core-metadata-extractor-tests/*
/opt/share/packages/core-metadata-extractor-tests.xml
/opt/usr/share/license/core-metadata-extractor-tests

%files -n core-mime-type-tests
/opt/usr/apps/core-mime-type-tests/*
/opt/share/packages/core-mime-type-tests.xml
/opt/usr/share/license/core-mime-type-tests

%files -n core-native-common-tests
/opt/usr/apps/core-native-common-tests/*
/opt/share/packages/core-native-common-tests.xml
/opt/usr/share/license/core-native-common-tests

%files -n core-nfc-tests
/opt/usr/apps/core-nfc-tests/*
/opt/share/packages/core-nfc-tests.xml
/opt/usr/share/license/core-nfc-tests

%files -n core-smartcard-tests
/opt/usr/apps/core-smartcard-tests/*
/opt/share/packages/core-smartcard-tests.xml
/opt/usr/share/license/core-smartcard-tests

%files -n core-mtp-tests
/opt/usr/apps/core-mtp-tests/*
/opt/share/packages/core-mtp-tests.xml
/opt/usr/share/license/core-mtp-tests

%files -n core-notification-tests
/opt/usr/apps/core-notification-tests/*
/opt/share/packages/core-notification-tests.xml
/opt/usr/share/license/core-notification-tests

%files -n core-package-manager-tests
/opt/usr/apps/core-package-manager-tests/*
/opt/share/packages/core-package-manager-tests.xml
/opt/usr/share/license/core-package-manager-tests

%files -n core-player-tests
/opt/usr/apps/core-player-tests/*
/opt/share/packages/core-player-tests.xml
/opt/usr/share/license/core-player-tests

%files -n core-privilege-info-tests
/opt/usr/apps/core-privilege-info-tests/*
/opt/share/packages/core-privilege-info-tests.xml
/opt/usr/share/license/core-privilege-info-tests

%files -n core-push-tests
/opt/usr/apps/core-push-tests/*
/opt/share/packages/core-push-tests.xml
/opt/usr/share/license/core-push-tests

%files -n core-radio-tests
/opt/usr/apps/core-radio-tests/*
/opt/share/packages/core-radio-tests.xml
/opt/usr/share/license/core-radio-tests

%files -n core-streamrecorder-tests
/opt/usr/apps/core-streamrecorder-tests/*
/opt/share/packages/core-streamrecorder-tests.xml
/opt/usr/share/license/core-streamrecorder-tests

%files -n core-recorder-tests
/opt/usr/apps/core-recorder-tests/*
/opt/share/packages/core-recorder-tests.xml
/opt/usr/share/license/core-recorder-tests

%files -n core-runtime-info-tests
/opt/usr/apps/core-runtime-info-tests/*
/opt/share/packages/core-runtime-info-tests.xml
/opt/usr/share/license/core-runtime-info-tests

%files -n core-sensor-tests
/opt/usr/apps/core-sensor-tests/*
/opt/share/packages/core-sensor-tests.xml
/opt/usr/share/license/core-sensor-tests

%files -n core-shortcut-tests
/opt/usr/apps/core-shortcut-tests/*
/opt/share/packages/core-shortcut-tests.xml
/opt/usr/share/license/core-shortcut-tests

%files -n core-sound-manager-tests
/opt/usr/apps/core-sound-manager-tests/*
/opt/share/packages/core-sound-manager-tests.xml
/opt/usr/share/license/core-sound-manager-tests

%files -n core-stt-tests
/opt/usr/apps/core-stt-tests/*
/opt/share/packages/core-stt-tests.xml
/opt/usr/share/license/core-stt-tests

%files -n core-sync-manager-tests
/opt/usr/apps/core-sync-manager-tests/*
/opt/share/packages/core-sync-manager-tests.xml
/opt/usr/share/license/core-sync-manager-tests

%files -n core-system-info-tests
/opt/usr/apps/core-system-info-tests/*
/opt/share/packages/core-system-info-tests.xml
/opt/usr/share/license/core-system-info-tests

%files -n core-system-settings-tests
/opt/usr/apps/core-system-settings-tests/*
/opt/share/packages/core-system-settings-tests.xml
/opt/usr/share/license/core-system-settings-tests

%files -n core-tbm-tests
/opt/usr/apps/core-tbm-tests/*
/opt/share/packages/core-tbm-tests.xml
/opt/usr/share/license/core-tbm-tests

%files -n core-telephony-tests
/opt/usr/apps/core-telephony-tests/*
/opt/share/packages/core-telephony-tests.xml
/opt/usr/share/license/core-telephony-tests

%files -n core-tone-player-tests
/opt/usr/apps/core-tone-player-tests/*
/opt/share/packages/core-tone-player-tests.xml
/opt/usr/share/license/core-tone-player-tests

%files -n core-sound-pool-tests
/opt/usr/apps/core-sound-pool-tests/*
/opt/share/packages/core-sound-pool-tests.xml
/opt/usr/share/license/core-sound-pool-tests

%files -n core-tts-tests
/opt/usr/apps/core-tts-tests/*
/opt/share/packages/core-tts-tests.xml
/opt/usr/share/license/core-tts-tests

%files -n core-url-download-tests
/opt/usr/apps/core-url-download-tests/*
/opt/share/packages/core-url-download-tests.xml
/opt/usr/share/license/core-url-download-tests

%files -n core-wav-player-tests
/opt/usr/apps/core-wav-player-tests/*
/opt/share/packages/core-wav-player-tests.xml
/opt/usr/share/license/core-wav-player-tests

%files -n core-webkit2-tests
/usr/apps/core-webkit2-tests/*
/usr/share/packages/core-webkit2-tests.xml
/usr/share/license/core-webkit2-tests

%files -n core-wifi-direct-tests
/opt/usr/apps/core-wifi-direct-tests/*
/opt/share/packages/core-wifi-direct-tests.xml
/opt/usr/share/license/core-wifi-direct-tests

%files -n core-wifi-tests
/opt/usr/apps/core-wifi-tests/*
/opt/share/packages/core-wifi-tests.xml
/opt/usr/share/license/core-wifi-tests

%files -n core-multi-assistant-tests
/opt/usr/apps/core-multi-assistant-tests/*
/opt/share/packages/core-multi-assistant-tests.xml
/opt/usr/share/license/core-multi-assistant-tests

%files -n core-capi-ui-sticker-tests
/opt/usr/apps/core-capi-ui-sticker-tests/*
/opt/share/packages/core-capi-ui-sticker-tests.xml
/opt/usr/share/license/core-capi-ui-sticker-tests

%files -n core-webrtc-tests
/opt/usr/apps/core-webrtc-tests/*
/opt/share/packages/core-webrtc-tests.xml
/opt/usr/share/license/core-webrtc-tests

# End Adding for UTC******************************************************************************************************************************

%files -n native-audio-io-ctc
/opt/usr/apps/native-audio-io-ctc/*
/opt/share/packages/native-audio-io-ctc.xml
/opt/usr/share/license/native-audio-io-ctc

%files -n native-camera-ctc
/opt/usr/apps/native-camera-ctc/*
/opt/share/packages/native-camera-ctc.xml
/opt/usr/share/license/native-camera-ctc

%files -n native-connection-ctc
/opt/usr/apps/native-connection-ctc/*
/opt/share/packages/native-connection-ctc.xml
/opt/usr/share/license/native-connection-ctc

%files -n native-device-ctc
/opt/usr/apps/native-device-ctc/*
/opt/share/packages/native-device-ctc.xml
/opt/usr/share/license/native-device-ctc

%files -n native-filesystem-permission-ctc
/opt/usr/apps/native-filesystem-permission-ctc/*
/opt/share/packages/native-filesystem-permission-ctc.xml
/opt/usr/share/license/native-filesystem-permission-ctc

%files -n native-image-util-ctc
/opt/usr/apps/native-image-util-ctc/*
/opt/share/packages/native-image-util-ctc.xml
/opt/usr/share/license/native-image-util-ctc

%files -n native-libstorage-ctc
/opt/usr/apps/native-libstorage-ctc/*
/opt/share/packages/native-libstorage-ctc.xml
/opt/usr/share/license/native-libstorage-ctc

%files -n native-system-info-ctc
/opt/usr/apps/native-system-info-ctc/*
/opt/share/packages/native-system-info-ctc.xml
/opt/usr/share/license/native-system-info-ctc

%files -n native-telephony-ctc
/opt/usr/apps/native-telephony-ctc/*
/opt/share/packages/native-telephony-ctc.xml
/opt/usr/share/license/native-telephony-ctc

%files -n native-wifi-direct-ctc
/opt/usr/apps/native-wifi-direct-ctc/*
/opt/share/packages/native-wifi-direct-ctc.xml
/opt/usr/share/license/native-wifi-direct-ctc

%files -n native-location-manager-ctc
/opt/usr/apps/native-location-manager-ctc/*
/opt/share/packages/native-location-manager-ctc.xml
/opt/usr/share/license/native-location-manager-ctc

%files -n native-media-codec-ctc
/opt/usr/apps/native-media-codec-ctc/*
/opt/share/packages/native-media-codec-ctc.xml
/opt/usr/share/license/native-media-codec-ctc

%files -n native-opengl-ctc
/opt/usr/apps/native-opengl-ctc/*
/opt/share/packages/native-opengl-ctc.xml
/opt/usr/share/license/native-opengl-ctc


%files -n native-platform-permission-ctc
/opt/usr/apps/native-platform-permission-ctc/*
/opt/share/packages/native-platform-permission-ctc.xml
/opt/usr/media/*
/opt/usr/share/license/native-platform-permission-ctc
%ifarch i586
/tmp/org.tizen.datacontrolprovider-0.0.1-1.i586.rpm
%else
/tmp/org.tizen.datacontrolprovider-0.0.1-1.armv7l.rpm
%endif


%files -n native-player-ctc
/opt/usr/apps/native-player-ctc/*
/opt/share/packages/native-player-ctc.xml
/opt/usr/share/license/native-player-ctc

%files -n native-runtime-info-ctc
/opt/usr/apps/native-runtime-info-ctc/*
/opt/share/packages/native-runtime-info-ctc.xml
/opt/usr/share/license/native-runtime-info-ctc

%files -n native-sensor-ctc
/opt/usr/apps/native-sensor-ctc/*
/opt/share/packages/native-sensor-ctc.xml
/opt/usr/share/license/native-sensor-ctc

%files -n native-sound-manager-ctc
/opt/usr/apps/native-sound-manager-ctc/*
/opt/share/packages/native-sound-manager-ctc.xml
/opt/usr/share/license/native-sound-manager-ctc
