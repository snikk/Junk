//
//  SecondViewController.m
//  VMPrototype
//
//  Created by Jeffrey Glenn on 9/11/15.
//  Copyright (c) 2015 Jiff. All rights reserved.
//

#import "SecondViewController.h"

@interface SecondViewController ()

@end

@implementation SecondViewController {
    IOSViewNode *viewNode;
    
    NSMutableDictionary* dict;
}

- (instancetype)initWithViewNode:(IOSViewNode*) vn {
    if (self = [super init]) {
        viewNode = vn;
        dict = [NSMutableDictionary new];
    }
    
    return self;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    NSLog(@"Yuppers");
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    
//    NSLog(@"viewNode = %@", viewNode);
    [self createView:self.view withNode:viewNode];
    
//    UIView *v = [UIView new];
//    v.backgroundColor = [UIColor blueColor];
//    v.translatesAutoresizingMaskIntoConstraints = NO;
//    [self.view addSubview:v];
//    
//    UIView *v2 = [UIView new];
//    v2.backgroundColor = [UIColor greenColor];
//    v2.translatesAutoresizingMaskIntoConstraints = NO;
//    [self.view addSubview:v2];
////    v.frame = CGRectMake(10, 10, 100, 100);
//    NSDictionary *viewsDictionary = @{@"myView":v};
//    NSDictionary *metrics = @{@"myWidth": @100};
//    
//    // 2. Define the views Sizes
////    NSArray *vConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"V:[myView(myWidth)]"
////                                                                        options:0
////                                                                        metrics:metrics
////                                                                          views:viewsDictionary];
////    
////    NSArray *hConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"H:[myView(myWidth)]"
////                                                                        options:0
////                                                                        metrics:metrics
////                                                                          views:viewsDictionary];
////    
////    [v addConstraints:vConstraints];
////    [v addConstraints:hConstraints];
//    
//    // 3. Define the redView Position
////    NSArray *constraint_POS_V = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|-30-[myView]"
////                                                                        options:0
////                                                                        metrics:nil
////                                                                          views:viewsDictionary];
////    
////    NSArray *constraint_POS_H = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-20-[myView]"
////                                                                        options:0
////                                                                        metrics:nil
////                                                                          views:viewsDictionary];
////    
////    [self.view addConstraints:constraint_POS_H];
//    //    [self.view addConstraints:constraint_POS_V];
//    
//    [v addConstraint:[NSLayoutConstraint constraintWithItem:v
//                                                  attribute:NSLayoutAttributeWidth
//                                                  relatedBy:NSLayoutRelationEqual
//                                                     toItem:nil
//                                                  attribute:NSLayoutAttributeNotAnAttribute
//                                                 multiplier:1.0f
//                                                   constant:150]];
//    
//    [v addConstraint:[NSLayoutConstraint constraintWithItem:v
//                                                  attribute:NSLayoutAttributeHeight
//                                                  relatedBy:NSLayoutRelationEqual
//                                                     toItem:nil
//                                                  attribute:NSLayoutAttributeNotAnAttribute
//                                                 multiplier:1.0f
//                                                   constant:50]];
//    
//    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:v
//                                                          attribute:NSLayoutAttributeLeading
//                                                          relatedBy:NSLayoutRelationEqual
//                                                             toItem:self.view
//                                                          attribute:NSLayoutAttributeLeading
//                                                         multiplier:1.0f
//                                                           constant:100]];
//    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:v
//                                                          attribute:NSLayoutAttributeTop
//                                                          relatedBy:NSLayoutRelationEqual
//                                                             toItem:self.view
//                                                          attribute:NSLayoutAttributeTop
//                                                         multiplier:1.0f
//                                                           constant:100]];
//    
//    [v2 addConstraint:[NSLayoutConstraint constraintWithItem:v2
//                                                  attribute:NSLayoutAttributeWidth
//                                                  relatedBy:NSLayoutRelationEqual
//                                                     toItem:nil
//                                                  attribute:NSLayoutAttributeNotAnAttribute
//                                                 multiplier:1.0f
//                                                   constant:10]];
//    
//    [v2 addConstraint:[NSLayoutConstraint constraintWithItem:v2
//                                                  attribute:NSLayoutAttributeHeight
//                                                  relatedBy:NSLayoutRelationEqual
//                                                     toItem:nil
//                                                  attribute:NSLayoutAttributeNotAnAttribute
//                                                 multiplier:1.0f
//                                                   constant:10]];
//    
//    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:v2
//                                                          attribute:NSLayoutAttributeLeading
//                                                          relatedBy:NSLayoutRelationEqual
//                                                             toItem:v
//                                                          attribute:NSLayoutAttributeRight
//                                                         multiplier:1.0f
//                                                           constant:20]];
//    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:v2
//                                                          attribute:NSLayoutAttributeTop
//                                                          relatedBy:NSLayoutRelationEqual
//                                                             toItem:v
//                                                          attribute:NSLayoutAttributeBottom
//                                                         multiplier:1.0f
//                                                           constant:20]];
//    
////    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:v
////                                                          attribute:NSLayoutAttributeTrailing
////                                                          relatedBy:NSLayoutRelationEqual
////                                                             toItem:self.view
////                                                          attribute:NSLayoutAttributeTrailing
////                                                         multiplier:1.0f
////                                                           constant:0]];
////    [self.view addConstraint:[NSLayoutConstraint constraintWithItem:v
////                                                          attribute:NSLayoutAttributeBottom
////                                                          relatedBy:NSLayoutRelationEqual
////                                                             toItem:self.view
////                                                          attribute:NSLayoutAttributeBottom
////                                                         multiplier:1.0f
////                                                           constant:0]];
//    
//    
//    
////    [v addConstraint:[NSLayoutConstraint constraintWithItem:v
////                                                  attribute:NSLayoutAttributeHeight
////                                                  relatedBy:NSLayoutRelationEqual
////                                                     toItem:nil
////                                                  attribute:NSLayoutAttributeNotAnAttribute
////                                                 multiplier:1.0f
////                                                   constant:100]];

    
    [self.view setNeedsLayout];
    [self.view layoutIfNeeded];
}

- (void)createView:(UIView*)parent withNode:(IOSViewNode*) iosViewNode {
    UIView *view = [UIView new];
    view.tag = iosViewNode.id;
    view.translatesAutoresizingMaskIntoConstraints = NO;
//    [view setContentCompressionResistancePriority:1000 forAxis:UILayoutConstraintAxisHorizontal];
//    [view setContentCompressionResistancePriority:1000 forAxis:UILayoutConstraintAxisVertical];
//    [view setContentHuggingPriority:0 forAxis:UILayoutConstraintAxisHorizontal];
//    [view setContentHuggingPriority:0 forAxis:UILayoutConstraintAxisVertical];
    
    [parent addSubview:view];
    
    BOOL isWidthSet = NO;
    BOOL isHeightSet = NO;
    
    if (iosViewNode.width > 0) {
        [view addConstraint:[NSLayoutConstraint constraintWithItem:view
                                                         attribute:NSLayoutAttributeWidth
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:nil
                                                         attribute:NSLayoutAttributeNotAnAttribute
                                                        multiplier:1.0f
                                                          constant:iosViewNode.width]];
        
        [parent addConstraint:[NSLayoutConstraint constraintWithItem:view
                                                           attribute:NSLayoutAttributeLeading
                                                           relatedBy:NSLayoutRelationEqual
                                                              toItem:parent
                                                           attribute:NSLayoutAttributeLeading
                                                          multiplier:1.0f
                                                            constant:iosViewNode.margins.origin.x]];
        
        isWidthSet = YES;
    } else {
        [parent addConstraint:[NSLayoutConstraint constraintWithItem:view
                                                           attribute:NSLayoutAttributeLeading
                                                           relatedBy:NSLayoutRelationEqual
                                                              toItem:parent
                                                           attribute:NSLayoutAttributeLeading
                                                          multiplier:1.0f
                                                            constant:iosViewNode.margins.origin.x]];
        
        [parent addConstraint:[NSLayoutConstraint constraintWithItem:view
                                                           attribute:NSLayoutAttributeTrailing
                                                           relatedBy:NSLayoutRelationEqual
                                                              toItem:parent
                                                           attribute:NSLayoutAttributeTrailing
                                                          multiplier:1.0f
                                                            constant:-iosViewNode.margins.size.width]];
    }
    
    if (iosViewNode.height > 0) {
        [view addConstraint:[NSLayoutConstraint constraintWithItem:view
                                                         attribute:NSLayoutAttributeHeight
                                                         relatedBy:NSLayoutRelationEqual
                                                            toItem:nil
                                                         attribute:NSLayoutAttributeNotAnAttribute
                                                        multiplier:1.0f
                                                          constant:iosViewNode.height]];
        
        [parent addConstraint:[NSLayoutConstraint constraintWithItem:view
                                                           attribute:NSLayoutAttributeTop
                                                           relatedBy:NSLayoutRelationEqual
                                                              toItem:parent
                                                           attribute:NSLayoutAttributeTop
                                                          multiplier:1.0f
                                                            constant:iosViewNode.margins.origin.y]];
        
        isHeightSet = YES;
    } else {
        [parent addConstraint:[NSLayoutConstraint constraintWithItem:view
                                                           attribute:NSLayoutAttributeTop
                                                           relatedBy:NSLayoutRelationEqual
                                                              toItem:parent
                                                           attribute:NSLayoutAttributeTop
                                                          multiplier:1.0f
                                                            constant:iosViewNode.margins.origin.y]];
        
        [parent addConstraint:[NSLayoutConstraint constraintWithItem:view
                                                           attribute:NSLayoutAttributeBottom
                                                           relatedBy:NSLayoutRelationEqual
                                                              toItem:parent
                                                           attribute:NSLayoutAttributeBottom
                                                          multiplier:1.0f
                                                            constant:-iosViewNode.margins.size.height]];
    }
    
    
//    [parent addConstraint:[NSLayoutConstraint constraintWithItem:view
//                                                       attribute:NSLayoutAttributeLeftMargin
//                                                       relatedBy:NSLayoutRelationEqual
//                                                          toItem:parent
//                                                       attribute:NSLayoutAttributeLeft
//                                                      multiplier:1.0f
//                                                        constant:iosViewNode.margins.origin.x]];
//    
//    [parent addConstraint:[NSLayoutConstraint constraintWithItem:view
//                                                       attribute:NSLayoutAttributeTopMargin
//                                                       relatedBy:NSLayoutRelationEqual
//                                                          toItem:parent
//                                                       attribute:NSLayoutAttributeTop
//                                                      multiplier:1.0f
//                                                        constant:iosViewNode.margins.origin.y]];
    
    for (IOSViewNode* child in iosViewNode.children) {
        [self createView:view withNode:child];
    }
    
    for (IOSViewNode* child in iosViewNode.children) {
        for (IOSRelationship* relation in child.relationships) {
            UIView *mainView = [view viewWithTag:child.id];
            UIView *otherView = [view viewWithTag:relation.otherID];
            IOSViewNode* other;
            for (IOSViewNode* otherChild in iosViewNode.children) {
                if (otherChild.id == relation.otherID)
                    other = otherChild;
            }
            
            switch (relation.relationship) {
                case 3: // BELOW
                {
                    for (NSLayoutConstraint *constraint in view.constraints) {
                        if (constraint.firstItem == mainView && constraint.firstAttribute == NSLayoutAttributeTop) {
                            [view removeConstraint:constraint];
                            break;
                        }
                    }
                    
                    
                    [view addConstraint:[NSLayoutConstraint constraintWithItem:mainView
                                                                       attribute:NSLayoutAttributeTop
                                                                       relatedBy:NSLayoutRelationEqual
                                                                          toItem:otherView
                                                                       attribute:NSLayoutAttributeBottom
                                                                      multiplier:1.0f
                                                                        constant:child.margins.origin.y + other.margins.size.height]];
                    break;
                }
                case 1: // RIGHT
                {
                    for (NSLayoutConstraint *constraint in view.constraints) {
                        if (constraint.firstItem == mainView && constraint.firstAttribute == NSLayoutAttributeLeading) {
                            [view removeConstraint:constraint];
                            break;
                        }
                    }
                    
                    
                    [view addConstraint:[NSLayoutConstraint constraintWithItem:mainView
                                                                     attribute:NSLayoutAttributeLeading
                                                                     relatedBy:NSLayoutRelationEqual
                                                                        toItem:otherView
                                                                     attribute:NSLayoutAttributeTrailing
                                                                    multiplier:1.0f
                                                                      constant:child.margins.origin.x + other.margins.size.width]];
                    break;
                }
                    
                default:
                    break;
            }
        }
    }
    
    float a = (iosViewNode.bgColor >> 24) & 0xFF;
    float r = (iosViewNode.bgColor >> 16) & 0xFF;
    float g = (iosViewNode.bgColor >> 8) & 0xFF;
    float b = iosViewNode.bgColor & 0xFF;
    view.backgroundColor = [UIColor colorWithRed:r / 255.0f green:g / 255.0f blue:b / 255.0f alpha:a / 255.0f];
}

@end
