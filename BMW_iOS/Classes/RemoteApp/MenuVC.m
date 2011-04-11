//
//  MenuVC.m
//  SimpleWeather
//
//  Created by Paul Doersch on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "MenuVC.h"
#import "RemoteAppIDs.h"
#import "RemoteApp.h"

@implementation MenuVC
@synthesize list;

/**
 * IDViewController initializer.
 */
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
		self.list = [[[IDTable alloc] initWithViewController:self widgetID:LST_List modelID:MDL_List actionID:ACT_List_Elem_Selected targetModelID:MDL_List_Target] autorelease];
		[self addWidget: list];
	}
	return self;
}

-(void)dealloc {
	self.list = nil;
	[super dealloc];
}


/**
 * Override in Subclass
 * Must call [super rhmiDidStart] at some point.
 */
-(void)rhmiDidStart
{
	[list setTargetView:((RemoteApp*)(self.application)).mainVC];	// Set the view that will be opened when an element is selected
	[list setTarget:self selector:@selector(listElementSelected:)];			// Set the callback when an element is selected
	[self populateList];
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


-(void)populateList
{
	int rows = 10;
	
	// Fill HMI Table
	[list setRows:rows columns:1];
	
	// Stations
	int i;
	for (i=0;i<rows;i++) {
		
		NSString* text;
		
		switch (i) {
			case 0:
				text = @"#14 Top Speed";
				break;
			case 1:
				text = @"#209 Red Lights Run";
				break;
			case 2:
				text = @"#67 Miles Per Gallon";
				break;
			case 3:
				text = @"#1 Cars Passed";
				break;
			case 4:
				text = @"#1 MINI's Passed";
				break;
			case 5:
				text = @"#88 Smooth Braking";
				break;
			case 6:
				text = @"#15 Stop Signs Encountered";
				break;
			default:
				text = [[NSNumber numberWithInt:i] stringValue];
				break;
		}
		
		IDTableCell* cell = [IDTableCell tableCellWithString: text];
		[list setCell:cell row:i column:0];
	}	
}


-(void)listElementSelected:(NSNumber*)indexNum
{
	int index = [indexNum intValue];
	NSLog(@"Element at index: %d selected.", index);
}

@end
