/*
 *  IDAudioManager.h
 *  iDrive
 *
 *  Created by Wolfgang Lenders on 2/19/10.
 *  Copyright 2010 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDAudioManager.h 51165 2010-12-02 15:25:02Z q228287 $
 */

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#import "IDAVServiceIncludes.h"


@class IDAudioManager;
@class IDAudioManagerClient;
@class CTCallCenter;

@interface IDAudioManager : NSObject <AVAudioSessionDelegate> {
    id<IDAudioManagerClient> _waitingEntertainmentClient;
    id<IDAudioManagerClient> _activeEntertainmentClient;
    id<IDAudioManagerClient> _activeInterruptClient;    
    AVAudioSession* _audioSession;
    CTCallCenter* _callCenter;
}

+ (IDAudioManager*)sharedAudioManager;
+ (void)setFMODServiceProvider:(id<IDFMODServiceProvider>)provider;

- (void)setEntertainmentClient:(id<IDAudioManagerClient>)client;
- (void)client:(id<IDAudioManagerClient>)client requestPermissionForConnectionOfType:(AVConnectionType)connectionType;
- (void)client:(id<IDAudioManagerClient>)client deactivatedConnectionOfType:(AVConnectionType)connectionType;
- (void)cancelWaitingClient;
- (void)clientLogsOff:(id<IDAudioManagerClient>)client;
- (BOOL)isEntertainmentActive;
- (BOOL)isFMODPresent;

@end
