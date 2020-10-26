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
        std::array<long, 3> value = compute_cross_product(std::array<i16,3>{1,2,3}, std::array<i16,3>{3,2,1});
        for (size_t i = 0; i < 3; ++i)
            std::cout << value[i] << std::endl;
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            self.resultLabel.stringValue=[NSString stringWithFormat: @"Result (%d, %d, %d)", value[0], value[1], value[2]];
        });
    });
    
    return;
}

- (IBAction)didPressMatrixBtn:(id)sender {
    
}


@end
