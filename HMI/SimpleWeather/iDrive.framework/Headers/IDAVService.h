/*
 *  IDAVService.h
 *  iDrive
 *
 *  Created by Wolfgang Lenders on 2/2/10.
 *  Copyright 2010 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDAVService.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>

#import "IDService.h"
#import "IDEventHandler.h"
#import "IDAVServiceIncludes.h"

@class IDApplication;
@protocol IDAudioManagerClient;

@class IDLogger;


#pragma mark -
#pragma mark IDAVServiceClient protocol

@protocol IDAVServiceClient <NSObject>

@required
- (void)setPlayerState:(AVPlayerState)state forConnectionType:(AVConnectionType)connectionType;
- (void)setVolume:(float)volume forConnectionType:(AVConnectionType)connectionType;
- (float)volumeForConnectionType:(AVConnectionType)connectionType;

@optional
- (void)handleAVMultimediaButtonEvent:(AVButtonEvent)button;
- (void)beginInterruption;

@end


#pragma mark -
#pragma mark IDAVServiceTestingClient protocol

@protocol IDAVServiceTestingClient <NSObject>

@required
- (void)handleAVConnectionDeniedEvent:(AVConnectionType)connectionType;
- (void)handleAVRequestPlayerStateEvent:(AVConnectionType)connectionType playerState:(AVPlayerState)state;
- (void)handleAVConnectionGrantedEvent:(AVConnectionType)connectionType;
- (void)handleAVConnectionDeactivatedEvent:(AVConnectionType)connectionType;
- (void)handleAVMultimediaButtonEvent:(AVButtonEvent)button;

@end

#pragma mark -
#pragma mark IDAVService

@interface IDAVService : IDService <IDEventHandler, IDAudioManagerClient>
{
    
    id<IDAVServiceClient> _client;
    id<IDAVServiceTestingClient> _testingClient;
    BOOL _requestedConnections[2];
    BOOL _openConnections[2];
    BOOL _playStateSent;
    BOOL _closingConnection;
    NSNumber* _killFlag;
    NSTimer* _hmiResponseTimer;
	NSThread* _clientThread;
}
@property(retain) NSThread* clientThread;

- (id)initWithApplication:(IDApplication*)app client:(id<IDAVServiceClient>)client;
- (id)initWithApplication:(IDApplication*)app client:(id<IDAVServiceClient>)client testingClient:(id<IDAVServiceTestingClient>)testingClient;
- (void)requestConnection:(AVConnectionType)connectionType;
- (void)closeConnection:(AVConnectionType)connectionType;
- (BOOL)isRequested:(AVConnectionType)connectionType;
- (BOOL)isA4AEntertainmentPlaying;
- (BOOL)isFMODPresent;
- (void)logOffClient:(id<IDAVServiceClient>)client;

@end
