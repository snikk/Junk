//
//  ViewController.m
//  VMPrototype
//
//  Created by Jeffrey Glenn on 9/11/15.
//  Copyright (c) 2015 Jiff. All rights reserved.
//

#import "ViewController.h"
#import "interpreter.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidAppear:(BOOL)animated {
    [self performSelector:@selector(loadBinary) withObject:nil afterDelay:1.5f];
}

- (void)loadBinary {
//    UIViewController *vc = [UIViewController new];
//    [self.navigationController pushViewController:vc animated:YES];
    
    NSString *urlString = @"http://127.0.0.1:8080";
    NSLog(@"url = %@", urlString);
    NSURLSession *session = [NSURLSession sharedSession];
    [[session dataTaskWithURL:[NSURL URLWithString:urlString]
           completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
               char* bytes = (char*) [data bytes];
               runProgramCode(bytes, (int) data.length);
           }] resume];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
