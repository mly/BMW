//
//  BmwAudioLine.h
//  BMW
//
//  Created by Paul Doersch on 10/15/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iDrive.h"

@protocol IDAudioLineDelegate
	-(void)bmwAudioLinePlay;
	-(void)bmwAudioLinePause;
	-(void)bmwAudioLineSkipNext;
	-(void)bmwAudioLineSkipPrev;
	-(void)bmwAudioLineLongPressNext;
	-(void)bmwAudioLineLongPressPrev;

// Don't react to these for playback directly, because
// Play, Pause, and Stop are automatically called
// as the appropriate (supposedly..) reactions.
	-(void)bmwAudioLineUnplugged;
	-(void)bmwAudioLinePluggedIn;
@end



// When the app starts up, and the mute button has been 
// pressed (the litle speaker with a line thrugh it is 
// up in the top corner), i still get a play command. 
// i have no way of knowing that we are in a mute state.
@interface IDAudioLine : NSObject <IDAVServiceClient> {
	id<IDAudioLineDelegate> delegate;
	IDApplication* application;
	IDAVService* avService;
	BOOL channel;
	BOOL muted;
	BOOL tryingToPlugIn;
}


//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

/**
 * Standard Init Method
 */
-(id)initWithApplication:(IDApplication*)application delegate:(id<IDAudioLineDelegate>)del;


/**
 * Returns the current state of the Bmw Audio Line
 */
-(BOOL)pluggedIn;


/**
 * Attemptes to plug in the Bmw Audio Line.
 * Result will be delivered asyncronously
 * via one of the delegate methods.
 */
-(void)tryToPlugIn;


/**
 * Unplugs the Audio Line
 */
-(void)unplug;


//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////
-(void)setChannel:(BOOL)_channel;
-(void)setMuted:(BOOL)_muted;
@property(retain) IDAVService* avService;

@end
