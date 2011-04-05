//
//  MenuVC.h
//  SimpleWeather
//
//  Created by Paul Doersch on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <iDrive/iDrive.h>

@interface MenuVC : IDViewController {
	IDTable* list;
}
@property(retain) IDTable* list;

-(void)populateList;
-(void)listElementSelected:(NSNumber*)indexNum;

@end
