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
#include "Algorithms/Multiplication/multiplication.hpp"
#include "Algorithms/CrossProduct/cross_product.hpp"

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
    uint16_t a = [self.leftTextField.stringValue intValue];
    uint16_t b = [self.rightTextField.stringValue intValue];
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        //auto value = compute_bgv_multiply(a, b);
        u16 value = compute_cross_product(std::array<u16,3>{1,2,3}, std::array<u16,3>{3,2,1})[0];
        std::cout << value << std::endl;
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            self.resultLabel.stringValue=[NSString stringWithFormat: @"Result %u", value];
        });
    });
    
    return;
}

- (IBAction)didPressMatrixBtn:(id)sender {
    
}


@end
