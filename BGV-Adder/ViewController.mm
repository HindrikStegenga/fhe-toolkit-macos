//
//  ViewController.m
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 17/10/2020.
//  Copyright © 2020 IBM. All rights reserved.
//

#import "ViewController.h"
#include <iostream>

#include <helib/binaryArith.h>
#include <helib/intraSlot.h>
#include <helib/helib.h>
#include "Algorithms/multiplication.hpp"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
}

- (void)viewDidAppear {
    [super viewDidAppear];
    self.view.window.delegate = self;
}

- (void)windowWillClose:(NSNotification *)notification {
    exit(0);
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (IBAction)didPressAddBtn:(id)sender {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        uint16_t a = [self.leftTextField.stringValue intValue];
        uint16_t b = [self.rightTextField.stringValue intValue];
        
        auto value = compute_bgv_multiply(a, b);
        std::cout << value << std::endl;
        self.resultLabel.stringValue=[NSString stringWithFormat: @"Result %u", value];
    });
    
    return;
}


@end
