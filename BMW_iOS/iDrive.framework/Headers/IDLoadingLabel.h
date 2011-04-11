//
//  IDLoadingLabel.h
//  iDrive
//
//  Created by Paul Doersch on 12/6/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDLabel.h"

@interface IDLoadingLabel : IDLabel {
	BOOL mHidesWhenStopped;
	BOOL mAnimating;
	BOOL mAnimating_dirty;
	BOOL mFirstFlush;
}
@property BOOL hidesWhenStopped;

-(void)startAnimating;
-(void)stopAnimating;
-(BOOL)isAnimating;

@end
