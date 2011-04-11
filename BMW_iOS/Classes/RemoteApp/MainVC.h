//
//  MainVC.h
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <iDrive/iDrive.h>
#import "MenuVC.h"

@interface MainVC : IDViewController {
	
	IDButton* homeButton;
	IDButton* routeButton;
	IDButton* currentButton;
	IDButton* destButton;
	IDButton* lookupButton;
	
	IDImage* viewImage;
	IDLoadingLabel* stateLabel;
	
	MenuVC* menuVC;
	NSTimer *imageTimer;
	IBOutlet UIView *dashboardView;
}
@property(retain) IDButton* homeButton;
@property(retain) IDButton* routeButton;
@property(retain) IDButton* currentButton;
@property(retain) IDButton* destButton;
@property(retain) IDButton* lookupButton;

@property(retain) IDImage* viewImage;
@property(retain) IDLabel* stateLabel;

@property(retain) MenuVC* menuVC;


// Button Callbacks
-(void)homeButtonClicked:(IDButton*)button;
-(void)routeButtonClicked:(IDButton*)button;
-(void)currentButtonClicked:(IDButton*)button;
-(void)destButtonClicked:(IDButton*)button;
-(void)lookupButtonClicked:(IDButton*)button;

@end
