//
//  ViewNode.h
//  VMPrototype
//
//  Created by Jeffrey Glenn on 9/11/15.
//  Copyright (c) 2015 Jiff. All rights reserved.
//

#import <UIKit/UIKit.h>

static const int RELATIVE  = 1;
static const int VIEW = 2;
static const int IMAGE = 3;

@interface IOSViewNode : NSObject

@property (nonatomic) int id;
@property (nonatomic) NSArray *children;
@property (nonatomic) CGRect margins;
@property (nonatomic) int width;
@property (nonatomic) int height;
@property (nonatomic) int bgColor;
@property (nonatomic) int type;
@property (nonatomic) NSArray *relationships;

@end

@interface IOSRelationship : NSObject

@property (nonatomic) int otherID;
@property (nonatomic) int relationship;

@end