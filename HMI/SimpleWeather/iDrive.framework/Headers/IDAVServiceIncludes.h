/*
 *  IDAVServiceIncludes.h
 *  iDrive
 *
 *  Created by Wolfgang Lenders on 2/2/10.
 *  Copyright 2010 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDAVServiceIncludes.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#define ID_AV_OFFBOARD_SERVICE_SESSION_INTERRUPTED @"ID_AV_OFFBOARD_SERVICE_SESSION_INTERRUPTED"
#define ID_AV_OFFBOARD_SERVICE_SESSION_INTERRUPTION_ENDED @"ID_AV_OFFBOARD_SERVICE_SESSION_INTERRUPTION_ENDED"
#define ID_AV_OFFBOARD_SERVICE_SESSION_AUDIO_ROUTE_CHANGE @"ID_AV_OFFBOARD_SERVICE_SESSION_AUDIO_ROUTE_CHANGE"

typedef enum {
    AVConnectionTypeEntertainment = 0,
    AVConnectionTypeInterrupt = 1,
    AVConnectionTypeInvalid = 2
} AVConnectionType;

typedef enum {
    AVPlayerStatePlay,
    AVPlayerStatePause,
    AVPlayerStateStop,
    AVPlayerStateInvalid
} AVPlayerState;

typedef enum {
    AVButtonEventSkipUp,
    AVButtonEventSkipDown,
    AVButtonEventSkipLongUp,
    AVButtonEventSkipLongDown,
    AVButtonEventSkipStop
} AVButtonEvent;


@protocol IDAudioManagerClient <NSObject>

@required
- (void)connectionOfType:(AVConnectionType)connectionType granted:(BOOL)granted;
- (void)closeConnectionOfType:(AVConnectionType)connectionType;
- (void)setVolume:(float)volume forConnectionType:(AVConnectionType)connectionType;
- (float)volumeForConnectionType:(AVConnectionType)connectionType;
- (void)beginInterruption;
- (void)endInterruption;

@end

@protocol IDFMODServiceProvider

@required
- (NSInteger)setMix:(BOOL)mix;
- (NSInteger)setDuck:(BOOL)duck;
- (NSInteger)restoreAudioSession;

@end

