//
//  MainVC.m
//  SimpleWeather
//
//  Created by Paul Doersch on 1/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "MainVC.h"
#import "SimpleWeatherAppIDs.h"
#import "SimpleWeatherAppDelegate.h"
#import "WeatherRenderer.h"

@implementation MainVC
@synthesize homeButton;
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
		self.currentButton = [[[IDButton alloc] initWithViewController:self	widgetID:BTN_Current		modelID:-1	imageModelID:-1	actionID:ACT_Current_Clicked targetModelID:-1] autorelease];
		self.destButton = [[[IDButton alloc] initWithViewController:self	widgetID:BTN_Destination	modelID:-1	imageModelID:-1	actionID:ACT_Destination_Clicked targetModelID:-1] autorelease];
		self.lookupButton = [[[IDButton alloc] initWithViewController:self	widgetID:BTN_Lookup			modelID:-1	imageModelID:-1	actionID:ACT_Lookup_Clicked targetModelID:-1] autorelease];
		
		self.viewImage = [[[IDImage alloc] initWithViewController:self widgetID:IMG_View modelID:MDL_Image_View] autorelease];
		self.stateLabel = [[[IDLoadingLabel alloc] initWithViewController:self widgetID:LBL_State modelID:MDL_Text_State] autorelease];
		
//		[[[IDLabel alloc] initWithViewController:self widgetID:LBL_State modelID:MDL_Text_State] autorelease];

		[self addWidget: homeButton];
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
	[currentButton	setTarget:self	selector:@selector(currentButtonClicked:)];
	[destButton		setTarget:self	selector:@selector(destButtonClicked:)];
	[lookupButton	setTarget:self	selector:@selector(lookupButtonClicked:)];
	
	[viewImage setPosition: CGPointMake(10, 10)];
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
	// Get Forcast Object
	Forecast* forecast = [[[Forecast alloc] init] autorelease];
	forecast.locationName = @"Woodside";
	NSMutableArray* days = [[[NSMutableArray alloc] init] autorelease];
	for (int i=1;i<6;i++)
	{
		Day* day = [[[Day alloc] init] autorelease];
		day.highTemp = i * 12.2;
		day.lowTemp = i * 4.6;
		[days addObject: day];
	}
	forecast.days = days;
	
	// Create View
	UIImage* view = [WeatherRenderer renderWithForecast: forecast];
	
	// Display View
	[viewImage setImage: view];
	[stateLabel setText: nil];
	[stateLabel stopAnimating];
}

-(void)currentButtonClicked:(IDButton*)button
{
	[viewImage setImage: nil];
	[stateLabel startAnimating];
	[stateLabel setText: @"Current"];
}

-(void)destButtonClicked:(IDButton*)button
{
	[viewImage setImage: nil];
	[stateLabel setText: @"Destination"];
}

-(void)lookupButtonClicked:(IDButton*)button
{
	[viewImage setImage: nil];
	[stateLabel setText: @"Lookup"];
	
	[menuVC show]; // This doesn't actually present the view as it was originally desinged to do. That is hard-coded into the xml file.
}


@end
