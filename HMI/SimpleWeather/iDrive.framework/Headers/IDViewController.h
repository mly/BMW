//
//  IDViewController.h
//  BMW
//
//  Created by Paul Doersch on 9/21/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDWidget.h"
#import "IDFlushProtocol.h"
@class IDApplication;
@class IDVariantMap;

@interface IDViewController : NSObject <IDFlushProtocol> {
	IDApplication* mApplication;
	NSInteger hmiState;
	NSInteger gotoEvent;
	NSInteger titleModel;
	NSMutableSet* widgets;
	NSMutableSet* subViewControllers;
	
	BOOL mVisible;
	BOOL mFocused;
	
	BOOL show_dirty;
	
	NSString* mTitle;
	BOOL mTitle_dirty;
}

@property(assign) IDApplication* application;
@property(retain) NSMutableSet* widgets;
@property(retain) NSMutableSet* subViewControllers;
@property(retain) NSString* title;
@property BOOL visible;
@property BOOL focused;
@property int hmiState;

/**
 * IDViewController initializer.
 */
-(id)initWithIdApplication:(IDApplication*)_idApplication 
				  hmiState:(NSInteger)_hmiState 
				 gotoEvent:(NSInteger)_gotoEvent
				titleModel:(NSInteger)_titleModel;

/**
 * Override in Subclass
 * Must call [super rhmiDidStart] at some point.
 */
-(void)rhmiDidStart;


/**
 * Override in Subclass
 * Must call [super show:] after
 * custom setup and before 
 * custom post work.
 */
-(void)show;


/**
 * Override in Subclass
 * Called when this View was
 * shown or removed from the screen.
 */
-(void)didFocus:(BOOL)focused;

-(void)didBecomeVisible:(BOOL)visible;


/**
 * Override in Subclass
 * Must call [super doDisconnect] at some point.
 */
-(void)doDisconnect;


/**
 * Adds a widget to this View Controller's
 * view.
 */
-(void)addWidget:(IDWidget*)widget;


/**
 * Removes a widget from this View Controller's
 * view.
 */
-(void)removeWidget:(IDWidget*)widget;


/**
 * Adds a view controller to this View Controller's
 * heirarchy.
 */
-(void)addSubViewController:(IDViewController*)viewController;


/**
 * Removes a view controller from this View Controller's
 * heirarchy.
 */
-(void)removeSubViewController:(IDViewController*)viewController;


/**
 * Set the View's Title.
 */
-(void)setTitle:(NSString*)title;


@end
