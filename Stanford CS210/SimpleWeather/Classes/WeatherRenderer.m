//
//  WeatherRenderer.m
//  SimpleWeather
//
//  Created by Paul Doersch on 1/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "WeatherRenderer.h"

@implementation WeatherRenderer

+(UIImage*)renderWithForecast:(Forecast*)forecast
{
	int width = 600;
	int height = 400;
	UIImage* finalImage = nil;
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	CGContextRef ctx = CGBitmapContextCreate (NULL, width, height, 8,0, colorSpace, kCGImageAlphaPremultipliedLast);
	CGColorSpaceRelease(colorSpace);	
	if (ctx == NULL) return NULL;
	
	// Push Context
	{
		UIGraphicsPushContext(ctx);
		
		
		// Pre Fill with Background Color
		{
			CGContextSetFillColorWithColor(ctx, [UIColor clearColor].CGColor);
			CGContextFillRect(ctx, CGRectMake(0, 0, width, height));
		}
		
		
		// Today's Big Weather Image
		{
			UIImage* todayMainImage = [UIImage imageNamed:@"Sunny-Interval-icon.png"];
			CGContextDrawImage(ctx, CGRectMake(0, 140, todayMainImage.size.width, todayMainImage.size.height), todayMainImage.CGImage);
		}
		
		
		// Transformation for String Work
		{
			CGContextSaveGState(ctx);
			CGContextTranslateCTM(ctx, 0.0f, height);
			CGContextScaleCTM(ctx, 1.0f, -1.0f);
			
			
			// Mode String
			{
				CGContextSetFillColorWithColor(ctx, [UIColor colorWithWhite:0.5 alpha:1.0].CGColor);
				[@"Home" drawAtPoint:CGPointMake(0.0f, 0.0f) withFont:[UIFont boldSystemFontOfSize:20]];
			}
			
			
			// Location String
			{
				CGContextSetFillColorWithColor(ctx, [UIColor whiteColor].CGColor);
				[forecast.locationName drawAtPoint:CGPointMake(0.0f, 22.0f) withFont:[UIFont systemFontOfSize:36]];
			}
			
			
			// 5 Day Forecast
			{
				for (int i = 0; i<[forecast.days count]; i++)
				{
					Day* day = [forecast.days objectAtIndex:i];
					NSString* highTempStr = [[NSNumber numberWithFloat:day.highTemp] stringValue];
					NSString* lowTempStr = [[NSNumber numberWithFloat:day.lowTemp] stringValue];
					CGContextSetFillColorWithColor(ctx, [UIColor whiteColor].CGColor);
					[highTempStr drawAtPoint:CGPointMake(0+(i*100), 300) withFont:[UIFont systemFontOfSize:24]];
					CGContextSetFillColorWithColor(ctx, [UIColor colorWithWhite:0.5 alpha:1.0].CGColor);
					[lowTempStr drawAtPoint:CGPointMake(0+(i*100), 350) withFont:[UIFont systemFontOfSize:24]];
				}
			}
			
			// Undo Transformation
			CGContextRestoreGState(ctx);
		}
		
		// Pop Context
		UIGraphicsPopContext();
	}
	
	// Convert Context to UIImage
	{
		CGImageRef contentBitmapContext = CGBitmapContextCreateImage(ctx);
		finalImage = [UIImage imageWithCGImage:contentBitmapContext];
		CGImageRelease(contentBitmapContext);
		CGContextRelease(ctx);
	}
	
	
	// return the image
	return finalImage;
}

@end
