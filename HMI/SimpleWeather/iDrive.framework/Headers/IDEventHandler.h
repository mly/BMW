/*
 *  IDEventHandler.h
 *  iDrive
 *
 *  Created by Wolfram Manthey on 02.12.09.
 *  Copyright 2009 BMW Car IT GmbH. All rights reserved.
 *
 *  $Id: IDEventHandler.h 50948 2010-11-29 12:20:12Z q188463 $
 */

#import <Foundation/Foundation.h>
#import "IDAVServiceIncludes.h"

@class IDVariantMap;

@protocol IDEventHandler <NSObject>

@optional
- (void)handleHmiEvent:(NSString*)eventKey component:(NSUInteger)componentId info:(IDVariantMap*)info;
- (void)handleActionEvent:(NSString*)eventKey info:(IDVariantMap*)info;
- (void)handleAsyncPropertyEvent:(NSString*)ident value:(id)propertyValue;
- (void)handlePropertyChangedEvent:(NSString*)propertyName value:(id)propertyValue;
- (void)handleAVConnectionDeniedEvent:(AVConnectionType)connectionType;
- (void)handleAVRequestPlayerStateEvent:(AVConnectionType)connectionType playerState:(AVPlayerState)state;
- (void)handleAVConnectionGrantedEvent:(AVConnectionType)connectionType;
- (void)handleAVConnectionDeactivatedEvent:(AVConnectionType)connectionType;
- (void)handleAVMultimediaButtonEvent:(AVButtonEvent)button;

@end
