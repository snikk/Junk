//
//  native.c
//  VMPrototype
//
//  Created by Jeffrey Glenn on 9/11/15.
//  Copyright (c) 2015 Jiff. All rights reserved.
//

#include <UIKit/UIKit.h>
#include <stdio.h>
#include "native.h"
#include "SecondViewController.h"

IOSViewNode* createViewNode(ViewNode* vn) {
    NSMutableArray *viewNodes = nil;
    if (vn->children) {
        viewNodes = [NSMutableArray new];
        LL* arr = vn->children;
        while (arr) {
            [viewNodes addObject:createViewNode(arr->data)];
            arr = arr->n;
        }
    }
    
    NSMutableArray *relationships = nil;
    if (vn->relationships) {
        relationships = [NSMutableArray new];
        LL* arr = vn->relationships;
        while (arr) {
            Relationship* relation = (Relationship*) arr->data;
            IOSRelationship *relObject = [IOSRelationship new];
            relObject.otherID = relation->otherID;
            relObject.relationship = relation->relationship;
            [relationships addObject:relObject];
            arr = arr->n;
        }
    }
    
    float scale = 2.75;
    
    CGRect rect = CGRectMake(vn->margins.left / scale, vn->margins.top / scale, vn->margins.right / scale, vn->margins.bottom / scale);
    IOSViewNode *newNode = [IOSViewNode new];
    newNode.id = vn->id;
    
    newNode.children = viewNodes;
    newNode.margins = rect;
    newNode.width = vn->width / scale;
    newNode.height = vn->height / scale;
    newNode.bgColor = vn->bgColor;
    newNode.type = vn->type;
    newNode.relationships = relationships;
    
    return newNode;
}

void sendViewToNative(ViewNode* vn) {
    printf("Hey there.  This is the sendViewToNative function!\n");
    
    IOSViewNode *iosViewNode = createViewNode(vn);
//    [svc viewDidLoad];
    dispatch_async(dispatch_get_main_queue(), ^{
        UINavigationController *current = (UINavigationController*) [UIApplication sharedApplication].delegate.window.rootViewController;
        SecondViewController *svc = [[SecondViewController alloc] initWithViewNode:iosViewNode];
        
        if ([current isKindOfClass:[UINavigationController class]]) {
            [current pushViewController:svc animated:YES];
        } else {
            [current.viewControllers.lastObject presentViewController:svc animated:YES completion:^ {
                NSLog(@"Finished pushing!");
            }];
        }
    });
//    CFRunLoopWakeUp(CFRunLoopGetCurrent());
}