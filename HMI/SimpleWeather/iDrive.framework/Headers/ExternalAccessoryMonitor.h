/*  ----------------------------------------------------------------------------
 Copyright (C) 2009 BMW AG All rights reserved.
 
 Filename:   proxy/ExternalAccessoryMonitor.h
 --------------------------------------------------------------------------- */

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>


@class ProxyInfo;
@class ProxyThread;
@class A4AWatchdogThread;

#define EXTERNAL_ACCESSORY_PROXY_MAX_SUPPORTED_PROTOCOL_VERSION 2;
#define EXTERNAL_ACCESSORY_PROXY_INSTANCE_ID_INVALID 0x0;
#define PROXY_LOG_WITH_IDLOG 1

#define WATCHDOGMONITOR_PORT        5001
#define WATCHDOGMONITOR_INTERVAL    15.0

#define ENABLE_WATCHDOGMONITOR

/// Key into standard user defaults for proxy protocol version to select when
/// connecting to the external accessory
extern NSString *ExternalAccessoryProxyDefaultProtocolVersionKey;


/// Notification sent after the external accessory connects and the 
/// ExternalAccessoryProxy is started.
extern NSString *ExternalAccessoryProxyWillStartNotification;

/// Notification sent when the ExternalAccessoryProxy receives the handshake
/// from the external accessory and is ready to accept connections.
extern NSString *ExternalAccessoryProxyDidStartNotification;

/// Notification sent after the external accessory disconnects and the
/// ExternalAccessoryProxy begins to stop.
extern NSString *ExternalAccessoryProxyWillStopNotification;

/// The external accessory protocol string.
extern NSString *IDProtocol;

/// Notification sent after the external accessory connects.
extern NSString *IDAccessoryDidConnectNotification;

/// Notification sent after the external accessory disconnects.
extern NSString *IDAccessoryDidDisconnectNotification;

/// Notification sent when handshake data is received from the accessory.
extern NSString *A4AWatchdogMonitorDetectedDisconnectNotification;

/// Notification sent when the proxy needs to extend watchdog timer.
extern NSString *A4AWatchdogMonitorExtendTimerNotification;

/// Notification sent when proxy thread main runloop has exited.
extern NSString *ExternalAccessoryProxyDidStopNotification;

/// Monitors external accessory connect and disconnect notifications and 
/// starts and stops the ExternalAccessoryProxy as needed.
@interface ExternalAccessoryMonitor : NSObject {
  ProxyInfo *proxyInfo;
  NSArray *proxyPorts;
  NSArray *highPriorityPorts;
  ProxyThread *proxyThread;
  A4AWatchdogThread *m_watchdogThread;
  NSTimer * m_proxyRestartTimer;
  BOOL m_monitorStarted;
  NSTimer * m_startupTimer;
  BOOL m_externalAccessoryReady;
}

+(NSDictionary*)proxyInfoDict;

- (id)initWithProxyPort:(in_port_t)proxyPort;

- (id)initWithProxyPortNumber:(NSNumber *)proxyPortNumber;

- (id)initWithProxyPorts:(NSArray *)theProxyPorts;

- (BOOL)start;

- (BOOL)stop;

- (BOOL)connected;

- (NSUInteger)instanceID;

+ (void)logWithFormattedProxyMessage:(NSString *)format, ...;

@end
