//
//  MainVC.m
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "MainVC.h"
#import "RemoteAppIDs.h"
#import "BMW_iOSAppDelegate.h"
#import <MediaPlayer/MediaPlayer.h>


@implementation MainVC
@synthesize homeButton;
@synthesize routeButton;
@synthesize currentButton;
@synthesize destButton;
@synthesize lookupButton;
@synthesize viewImage;
@synthesize stateLabel;
@synthesize menuVC;


-(id)initWithIdApplication:(IDApplication*)_idApplication 
				  hmiState:(NSInteger)_hmiState 
				 gotoEvent:(NSInteger)_gotoEvent
				titleModel:(NSInteger)_titleModel
{
	if (self = [super initWithIdApplication:_idApplication 
								   hmiState:_hmiState 
								  gotoEvent:_gotoEvent
								 titleModel:_titleModel])
	{
		
		// Widgets
		
		self.homeButton = [[[IDButton alloc] initWithViewController:self	widgetID:BTN_Home			modelID:-1	imageModelID:-1	actionID:ACT_Home_Clicked targetModelID:-1] autorelease];
		self.routeButton = [[[IDButton alloc] initWithViewController:self   widgetID:BTN_Route          modelID:-1  imageModelID:-1 actionID:ACT_Route_Clicked targetModelID:-1] autorelease];
		self.currentButton = [[[IDButton alloc] initWithViewController:self	widgetID:BTN_Current		modelID:-1	imageModelID:-1	actionID:ACT_Current_Clicked targetModelID:-1] autorelease];
		self.destButton = [[[IDButton alloc] initWithViewController:self	widgetID:BTN_Destination	modelID:-1	imageModelID:-1	actionID:ACT_Destination_Clicked targetModelID:-1] autorelease];
		self.lookupButton = [[[IDButton alloc] initWithViewController:self	widgetID:BTN_Lookup			modelID:-1	imageModelID:-1	actionID:ACT_Lookup_Clicked targetModelID:-1] autorelease];
		
		self.viewImage = [[[IDImage alloc] initWithViewController:self widgetID:IMG_View modelID:MDL_Image_View] autorelease];
		self.stateLabel = [[[IDLoadingLabel alloc] initWithViewController:self widgetID:LBL_State modelID:MDL_Text_State] autorelease];
		
//		[[[IDLabel alloc] initWithViewController:self widgetID:LBL_State modelID:MDL_Text_State] autorelease];

		[self addWidget: homeButton];
		[self addWidget: routeButton];
		[self addWidget: currentButton];
		[self addWidget: destButton];
		[self addWidget: lookupButton];
		[self addWidget: viewImage];
		[self addWidget: stateLabel];
		
		// Sub Views
		self.menuVC = [[[MenuVC alloc] initWithIdApplication:self.application hmiState:HST_Menu gotoEvent:-1 titleModel:-1] autorelease];
		[self addSubViewController:menuVC];
		
	}
	return self;
}

-(void)setRedLight:(BOOL)light {
	if (light) {
		[stateLabel setText:@"Red Light!"]; 
	} else {
		[stateLabel setText:@"No Red Light"];
	}
}

-(void)dealloc {
	self.homeButton = nil;
	self.currentButton = nil;
	self.destButton = nil;
	self.lookupButton = nil;
	self.viewImage = nil;
	self.stateLabel = nil;
	self.menuVC = nil;
	[super dealloc];
}




/**
 * Override in Subclass
 * Must call [super rhmiDidStart] at some point.
 */
-(void)rhmiDidStart
{
	[homeButton		setTarget:self	selector:@selector(homeButtonClicked:)];
	[routeButton setTarget:self selector:@selector(routeButtonClicked:)];
	[currentButton	setTarget:self	selector:@selector(currentButtonClicked:)];
	[destButton		setTarget:self	selector:@selector(destButtonClicked:)];
	[lookupButton	setTarget:self	selector:@selector(lookupButtonClicked:)];
	
	[viewImage setPosition: CGPointMake(-50, 20)];
	[stateLabel setPosition: CGPointMake(50, 50)];
	[stateLabel setHidesWhenStopped:NO];
	
	[super rhmiDidStart];
}


/**
 * Override in Subclass
 * Must call [super show:] after
 * custom setup and before 
 * custom post work.
 */
-(void)show 
{
	[super show];
}


/**
 * Override in Subclass
 * Called when this View was
 * shown or removed from the screen.
 */
-(void)didFocus:(BOOL)focused 
{
	
}

-(void)didBecomeVisible:(BOOL)visible 
{
	
}


/**
 * Override in Subclass
 * Must call [super doDisconnect] at some point.
 */
-(void)doDisconnect
{
	[super doDisconnect];
}



/**
 * Button Callbacks
 */
-(void)homeButtonClicked:(IDButton*)button
{
	// Display View
	//[viewImage setImage: [UIImage imageNamed:@"Dashboard.png"]];
	[viewImage setImage:nil];
	[stateLabel setText: @"No Red Light"];
	
	//imageTimer = [NSTimer scheduledTimerWithTimeInterval:3.0 target:self selector:@selector(updateDashboardImage:) userInfo:nil repeats:YES];
	//[stateLabel stopAnimating];
}

-(void)routeButtonClicked:(IDButton *)button {
	[viewImage setImage:[UIImage imageNamed:@"Routing.png"]];
	[stateLabel setText:@""];
}

-(void)currentButtonClicked:(IDButton*)button
{
	[viewImage setImage: [UIImage imageNamed:@"Achievements.png"]];
	//[stateLabel startAnimating];
	[stateLabel setText: @""];
}

-(void)destButtonClicked:(IDButton*)button
{
	[viewImage setImage:nil];
	//[viewImage setImage: [UIImage imageNamed:@"DrivingProfile.png"]];
	[stateLabel setText: @"Jams!"];
	
	MPMusicPlayerController *myPlayer = [MPMusicPlayerController applicationMusicPlayer];
	
	// assign a playback queue containing all media items on the device
	MPMediaQuery *query = [MPMediaQuery songsQuery];
	MPMediaItemCollection *collection;
	for (MPMediaItem *item in query.items) {
		if ([[item valueForProperty:MPMediaItemPropertyTitle] isEqualToString:@"Bad Romance"]) {
			NSLog(@"%@", [item valueForProperty:MPMediaItemPropertyTitle]);
			collection = [MPMediaItemCollection collectionWithItems:[NSArray arrayWithObject:item]];
			[myPlayer setQueueWithItemCollection:collection];
		}
	}
	
	//[myPlayer setQueueWithQuery: [MPMediaQuery songsQuery]];
	
	
	// start playing from the beginning of the queue
	[myPlayer play];
}

-(void)lookupButtonClicked:(IDButton*)button
{
	[viewImage setImage: nil];
	[stateLabel setText: @"Leaderboards"];
	
	[menuVC show]; // This doesn't actually present the view as it was originally desinged to do. That is hard-coded into the xml file.
}

-(void)updateDashboardImage:(id)sender {
	if (!dashboardView) {
		[[NSBundle mainBundle] loadNibNamed:@"Dashboard" owner:self options:nil];
		//dashboardView = [[UIView alloc] init];
		NSLog(@"WTF view not initialized");
	}
	
	
	
	
	NSLog(@"updating dash image");
	//UIView *myView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 400, 400)];
	//myView.backgroundColor = [UIColor clearColor];
	//UILabel *myLabel = [[UILabel alloc] initWithFrame:CGRectMake(100, 100, 100, 30)];
	//myLabel.text = @"Hello World";
	//myLabel.textColor = [UIColor whiteColor];
	//[myView addSubview:myLabel];				  
	
	UIGraphicsBeginImageContext(dashboardView.bounds.size);
	[dashboardView.layer renderInContext:UIGraphicsGetCurrentContext()];
	UIImage *dashImage = UIGraphicsGetImageFromCurrentImageContext();
	UIGraphicsEndImageContext();
	
	[viewImage setImage:dashImage];
}


@end
