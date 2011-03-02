/*
 *  ExternalAccessoryConnection.h
 *  iDrive
 *
 *  Copyright 2009 BMW AG. All rights reserved.
 *
 *  $Id: ExternalAccessoryConnection.h 50952 2010-11-29 12:36:19Z q188463 $
 */

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>


@class ExternalAccessoryProxy;
@class ProxyPacket;


/// The connection between the proxy and the external accessory.  Reads and
/// writes proxy packets to/from the external accessory.
@interface ExternalAccessoryConnection : NSObject <NSStreamDelegate> {
  NSUInteger availableBufferSize;
  ExternalAccessoryProxy *externalAccessoryProxy; // not retained
  ProxyPacket *incomingProxyPacket;
  NSUInteger maxAvailableBufferSize;
  BOOL readyToWrite; 
  uint16_t selectedProxyProtocolVersion;
  EASession *session;
  NSMutableArray *writeQueue;
  NSMutableArray *priorityWriteQueue;
  UInt8 indexOfNextFreeQueueSlot;
  BOOL writeQueueHasHalfWrittenData;
}

- (id)initWithExternalAccessoryProxy:(ExternalAccessoryProxy *)theExternalAccessoryProxy
                        andAccessory:(EAAccessory *)accessory
                         forProtocol:(NSString *)protocolString;

- (void)sendCloseCommandWithSocketId:(in_port_t)socketId
                       andAcceptPort:(in_port_t)acceptPort;

- (void)sendCloseCommandWithSocketId:(in_port_t)socketId
                       andAcceptPort:(in_port_t)acceptPort
                     andDataPriority:(int)priorityLevel;

- (void)sendDataCommandWithSocketId:(in_port_t)socketId
                         acceptPort:(in_port_t)acceptPort
                            andData:(NSData *)data;

- (void)sendDataCommandWithSocketId:(in_port_t)socketId
                         acceptPort:(in_port_t)acceptPort
                            andData:(NSData *)data
                    andDataPriority:(int)priorityLevel;

- (void)sendOpenCommandWithSocketId:(in_port_t)socketId
                      andAcceptPort:(in_port_t)acceptPort;

- (void)sendOpenCommandWithSocketId:(in_port_t)socketId
                      andAcceptPort:(in_port_t)acceptPort
                    andDataPriority:(int)priorityLevel;

@end
