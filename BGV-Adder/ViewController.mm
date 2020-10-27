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
#include "Algorithms/CKKSAdd/ckks_add.hpp"
#include "Algorithms/QuadraticPolynomials/quadratic_polynomial.hpp"
#include <iostream>


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
- (IBAction)didPressCkksAddBtn:(id)sender {
    double a = [self.ckksLeftTextField.stringValue doubleValue];
    double b = [self.ckksRightTextField.stringValue doubleValue];
    self.ckksResultLbl.stringValue = @"Please wait...";
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = ckks_add_doubles(a, b);
        dispatch_async(dispatch_get_main_queue(), ^{
            self.ckksResultLbl.stringValue = [NSString stringWithFormat:@"Result %f", value];
        });
    });
    
}

- (IBAction)didPressMulBtn:(id)sender {
       
    uint16_t a = [self.leftTextField.stringValue intValue];
    uint16_t b = [self.rightTextField.stringValue intValue];
    self.resultLabel.stringValue=@"Please wait...";
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = compute_bgv_multiply(a, b);
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            self.resultLabel.stringValue=[NSString stringWithFormat: @"Result %u", value];
        });
    });
    
    return;
}

- (IBAction)didPressCrossProductBtn:(id)sender {
    int16_t ax = [self.lhsX.stringValue intValue];
    int16_t ay = [self.lhsY.stringValue intValue];
    int16_t az = [self.lhsZ.stringValue intValue];
    
    int16_t bx = [self.rhsX.stringValue intValue];
    int16_t by = [self.rhsY.stringValue intValue];
    int16_t bz = [self.rhsZ.stringValue intValue];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        std::array<long, 3> value = compute_cross_product(
                                                          std::array<i16,3>{ax, ay, az}, std::array<i16,3>{bx, by, bz});
        for (size_t i = 0; i < 3; ++i)
            std::cout << value[i] << std::endl;
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            self.crossResultX.stringValue=[NSString stringWithFormat:@"x: %d", value[0]];
            self.crossResultY.stringValue=[NSString stringWithFormat:@"y: %d", value[1]];
            self.crossResultZ.stringValue=[NSString stringWithFormat:@"z: %d", value[2]];
        });
    });
    
    return;
}

- (IBAction)didPressQuadraticPolynomialBtn:(id)sender {
//    int16_t a = [self.polyATextField.stringValue intValue];
//    int16_t b = [self.polyBTextField.stringValue intValue];
//    int16_t c = [self.polyCTextField.stringValue intValue];
//    int16_t x = [self.polyXTextField.stringValue intValue];
    
    int16_t a = -1;
    int16_t b = -2;
    int16_t c = -3;
    int16_t x = -4;
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        long value = quadratic_polynomial(a, b, c, x);
        std::cout << value << std::endl;
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            self.polyResult.stringValue=[NSString stringWithFormat:@"Result =  %d", value];
        });
    });
    
    return;
    
}

@end
