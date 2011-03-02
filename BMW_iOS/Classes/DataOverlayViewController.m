//
//  DataOverlayViewController.m
//  BMW_iOS
//
//  Created by Rob Balian on 3/2/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "DataOverlayViewController.h"


@implementation DataOverlayViewController



// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/

-(void)populateLabelsWithAccel:(CMAcceleration)a Location:(CLLocation *)l GPSVelocity:(float)vg AverageVelocity:(float)vav andAccelerometerVelocity:(float *)va {
	[accel setText:[NSString stringWithFormat:@"Accel: [%.3f, %.3f, %.3f]", a.x, a.y, a.z]];
	[altitude setText:[NSString stringWithFormat:@"Altitude: %.3fft ASL", l.altitude]];
	[vaccel setText:[NSString stringWithFormat:@"Vaccel: [%.3f, %.3f, %.3f]", va[0], va[1], va[2]]];
	[vgps setText:[NSString stringWithFormat:@"Vgps: %.3f mph", vg]];
	[latlong setText:[NSString stringWithFormat:@"Lat: %.5f, Long: %.5f", l.coordinate.latitude, l.coordinate.longitude]];
	[vaverage setText:[NSString stringWithFormat:@"Vav: %.3f", vav]];
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
