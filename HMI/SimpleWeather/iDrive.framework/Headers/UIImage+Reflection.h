//
//  UIImage+Reflection.h
//  BMW
//
//  Created by Paul Doersch on 9/27/10.
//  Copyright 2010 BMW Technology Office Palo Alto. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface UIImage (reflection_additions)


//////////////////////////////////////////////////////////////
// Public
//////////////////////////////////////////////////////////////

-(UIImage*) reflection:(float)gloss;
-(UIImage*) reflection:(float)gloss roughness:(float)roughness;
-(UIImage*) withReflection:(float)gloss; // gloss = [0.0-1.0] (.25 is a good default)
-(UIImage*) withFrame:(int)width color:(UIColor*)color;
-(UIImage*)appendEmptySpaceAbove:(int)pixels color:(UIColor*)color;


//////////////////////////////////////////////////////////////
// Private
//////////////////////////////////////////////////////////////

-(CGImageRef) reflectionPart:(float)gloss roughness:(float)roughness;
+(NSString*) newSavePath;


@end
