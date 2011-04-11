/*  ----------------------------------------------------------------------------
 Copyright (C) 2009 BMW AG All rights reserved.
 
 Filename:   proxy/ExternalAccessoryProxy.h
 --------------------------------------------------------------------------- */
#import <Foundation/Foundation.h>


/// Notification sent when proxy is again able to write data to the accessory
/// after a buffer full notification
extern NSString *ExternalAccessoryProxyBufferAvailableNotification;

/// Notification sent when proxy is unable to write data to the accessory
extern NSString *ExternalAccessoryProxyBufferFullNotification;

/// Notification sent when handshake data is received from the accessory
extern NSString *ExternalAccessoryProxyReceivedHandshakeNotification;

/// Key into userInfo dictionary of ExternalAccessoryProxyBufferAvailableNotification
/// containing number of bytes available for writing
extern NSString *ExternalAccessoryProxyAvailableBufferSizeKey;

/// Key into userInfo dictionary of ExternalAccessoryProxyReceivedHandshakeNotification
/// for the ProxyInfo object
extern NSString *ExternalAccessoryProxyInfoKey;

/// Key into userInfo dictionary of ExternalAccessoryProxyReceivedHandshakeNotification
/// for the selected proxy protocol version object
extern NSString *ExternalAccessoryProxySelectedProtocolVersionKey;


@class EAAccessory;
@class ExternalAccessoryConnection;
@class ProxyInfo;
@class TcpConnection;


/// Proxy that accepts TCP connections and routes them to an external accessory.
@interface ExternalAccessoryProxy : NSObject {
  ExternalAccessoryConnection *externalAccessoryConnection;
  NSMutableDictionary *tcpConnections;
  NSMutableArray *tcpListeners;
}

/// Send a close command to the external accessory and release the 
/// TcpConnection object immediately.  Called by a TcpConnection object when it
/// detects an error or closed socket connection.
- (void)closeExternalAccessoryForTcpConnection:(TcpConnection *)tcpConnection;

/// Tell a TcpConnection object to finish any pending writes and close.
/// Called by the ExternalAccessoryConnection when it receives a close command.
- (void)closeTcpConnectionWithSocketId:(NSNumber *)socketId;

- (id)initWithAccessory:(EAAccessory *)accessory
      forProtocolString:(NSString *)protocolString
     andSocketAddresses:(NSArray *)socketAddresses;

/// Send an open command to the external accessory and retains the 
/// TcpConnection object.
- (void)openExternalAccessoryForTcpConnection:(TcpConnection *)tcpConnection;

/// Called by the ExternalAccessoryConnection when it connects to the
/// accessory and receives a handshake command.
- (void)receivedHandshakeWithProxyInfo:(ProxyInfo *)proxyInfo
       andSelectedProxyProtocolVersion:(uint16_t)version;

/// Immediately release the TcpConnection object.
- (void)releaseTcpConnection:(TcpConnection *)tcpConnection;

/// Called by the ExternalAccessoryConnection when the remote proxy's read
/// buffer has space available.
- (void)remoteProxyBufferIsAvailable;

/// Called by the ExternalAccessoryConnection when the remote proxy's read
/// buffer is full.
- (void)remoteProxyBufferIsFull;

- (void)                   sendData:(NSData *)data
toExternalAccessoryForTcpConnection:(TcpConnection *)tcpConnection;

- (void)           sendData:(NSData *)data
toTcpConnectionWithSocketId:(NSNumber *)socketId;

@end
