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
#include "Algorithms/BinaryOps/binary_ops.hpp"
#include "Algorithms/Multiplication/multiply.hpp"
#include "Algorithms/CrossProduct/cross_product.hpp"
#include "Algorithms/CKKS Rotation/ckks_rotation.hpp"
#include "Algorithms/CKKSAdd/ckks_add.hpp"
#include "Algorithms/CKKSAdd/ckks_mul.hpp"
#include "Algorithms/CKKS Complex Matrix Product/ckks_complex_matrix_product.hpp"
#include "Algorithms/CKKS Matrix Determinants/ckks_mat_det.hpp"
#include "Algorithms/QuadraticPolynomials/quadratic_polynomial.hpp"
#include "Algorithms/ComplexConjugate/complex_conjugate.hpp"
#include <iostream>
#include <complex>

using std::complex;

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
    
    NSButton* button = (NSButton*)sender;
    
    double a = [self.ckksLeftTextField.stringValue doubleValue];
    double b = [self.ckksRightTextField.stringValue doubleValue];
    self.ckksResultLbl.stringValue = @"Please wait...";
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = ckks_add_doubles(a, b);
        dispatch_async(dispatch_get_main_queue(), ^{
            self.ckksResultLbl.stringValue = [NSString stringWithFormat:@"Result %f", value];
            button.enabled = true;
        });
    });
    
}

- (IBAction)didPressMulBtn:(id)sender {
       
    NSButton* button = (NSButton*)sender;
    
    uint16_t a = [self.leftTextField.stringValue intValue];
    uint16_t b = [self.rightTextField.stringValue intValue];
    self.resultLabel.stringValue=@"Please wait...";
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = compute_multiplication(a, b);
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            self.resultLabel.stringValue=[NSString stringWithFormat: @"Result %u", value];
            button.enabled = true;
        });
    });
    
    return;
}

- (IBAction)didPressCrossProductBtn:(id)sender {
    
    NSButton* button = (NSButton*)sender;
    
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
            button.enabled = true;
        });
    });
    
    return;
}

- (IBAction)didPressQuadraticPolynomialBtn:(id)sender {
    int16_t a = [self.polyATextField.stringValue intValue];
    int16_t b = [self.polyBTextField.stringValue intValue];
    int16_t c = [self.polyCTextField.stringValue intValue];
    int16_t x = [self.polyXTextField.stringValue intValue];
    NSButton* button = (NSButton*)sender;
    
    self.polyResult.stringValue= @"Result = computing...";
    button.enabled = false;
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        long value = quadratic_polynomial(a, b, c, x);
        std::cout << value << std::endl;
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            self.polyResult.stringValue=[NSString stringWithFormat:@"Result =  %d", value];
            button.enabled = true;
        });
    });
    
    return;
    
}

- (IBAction)didPressBinaryCompareBtn:(id)sender {
    
    NSButton* button = (NSButton*)sender;
    button.enabled = false;
    
    array<bool, 5> lhs = {
        self.lhsBit4.state == NSOnState ? true : false,
        self.lhsBit3.state == NSOnState ? true : false,
        self.lhsBit2.state == NSOnState ? true : false,
        self.lhsBit1.state == NSOnState ? true : false,
        self.lhsBit0.state == NSOnState ? true : false
    };
    
    array<bool, 5> rhs = {
        self.rhsBit4.state == NSOnState ? true : false,
        self.rhsBit3.state == NSOnState ? true : false,
        self.rhsBit2.state == NSOnState ? true : false,
        self.rhsBit1.state == NSOnState ? true : false,
        self.rhsBit0.state == NSOnState ? true : false
    };
    
    bool bootstrap = self.bootstrapCheckBox.state == NSOnState ? true : false;
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = compare_binary_numbers( lhs, rhs);
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            button.enabled = true;
            self.muBitTextField.stringValue = [NSString stringWithFormat: @"%d", value.first];
            self.niBitTextField.stringValue = [NSString stringWithFormat: @"%d", value.second];
        });
    });
}

- (IBAction)didPressMatDet2x2Btn:(id)sender {
    self.mat2x2btn.enabled = false;
    self.mat3x3btn.enabled = false;
        
    array<double, 4> mat = {
        [self.matDetATextField.stringValue doubleValue],
        [self.matDetBTextField.stringValue doubleValue],
        [self.matDetDTextField.stringValue doubleValue],
        [self.matDetETextField.stringValue doubleValue]
    };
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = ckks_mat_det_2x2(mat);
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            
            self.mat2x2btn.enabled = true;
            self.mat3x3btn.enabled = true;
            
            self.matDeterminantResultLbl.stringValue = [NSString stringWithFormat: @"%f", value];
        });
    });
}

- (IBAction)didPressMatDet3x3Btn:(id)sender {
    self.mat2x2btn.enabled = false;
    self.mat3x3btn.enabled = false;
   
    array<double, 9> mat = {
        [self.matDetATextField.stringValue doubleValue],
        [self.matDetBTextField.stringValue doubleValue],
        [self.matDetCTextField.stringValue doubleValue],
        [self.matDetDTextField.stringValue doubleValue],
        [self.matDetETextField.stringValue doubleValue],
        [self.matDetFTextField.stringValue doubleValue],
        [self.matDetGTextField.stringValue doubleValue],
        [self.matDetHTextField.stringValue doubleValue],
        [self.matDetITextField.stringValue doubleValue],
    };
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = ckks_mat_det_3x3(mat);
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            
            self.mat2x2btn.enabled = true;
            self.mat3x3btn.enabled = true;
            
            self.matDeterminantResultLbl.stringValue = [NSString stringWithFormat: @"%f", value];
        });
    });
}

- (IBAction)didPressComplexComputeBtn:(id)sender {
    
    int16_t a = [self.complexLeftTextField.stringValue intValue];
    int16_t b = [self.complexRightTextField.stringValue intValue];
       
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        std::array<long, 2> value = complex_conjugate(a, b);
           
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            
            if (value[1] > -1) {
                self.complexResultLabel.stringValue=[NSString stringWithFormat:@"Result = %d + %di", value[0], value[1]];
            }
            else {
                self.complexResultLabel.stringValue=[NSString stringWithFormat:@"Result = %d %di", value[0], value[1]];
            }
        });
    });
       
    return;
    
}
- (IBAction)didPressComplexProductBtn:(id)sender {
    NSButton* button = (NSButton*)sender;
    
    double a = [self.complexMulRealA.stringValue doubleValue];
    double ai = [self.complexMulImagA.stringValue doubleValue];
    double b = [self.complexMulRealB.stringValue doubleValue];
    double bi = [self.complexMulImagB.stringValue doubleValue];
    
    self.complexMulResultField.stringValue = @"Please wait...";
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = ckks_mul_complex(a, ai, b, bi);
        dispatch_async(dispatch_get_main_queue(), ^{
            self.complexMulResultField.stringValue = [NSString stringWithFormat:@"Result: %f + %fi", value.real(), value.imag()];
            button.enabled = true;
        });
    });
}
- (IBAction)didPressCkksRotateBtn:(id)sender {
    NSButton* button = (NSButton*)sender;
    
    double ar = [self.ckksRotateRealTextField.stringValue doubleValue];
    double ai = [self.ckksRotateImagTextField.stringValue doubleValue];
    double rotate = [self.ckksRotateAmountTextField.stringValue doubleValue];
    button.enabled = false;
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        auto value = ckks_rotation(ar, ai, rotate);
        dispatch_async(dispatch_get_main_queue(), ^{
            self.ckksRotateResultTextField.stringValue = [NSString stringWithFormat:@"Result: %f + %fi", value.real(), value.imag()];
            button.enabled = true;
        });
    });
}
- (IBAction)didPressMatComplexMulBtn:(id)sender {
    
    
    NSButton* button = (NSButton*)sender;

    auto lhs = array<array<complex<double>,3>, 3>({
        array<complex<double>, 3>({
            complex<double>([self.matmulAR.stringValue doubleValue], [self.matmulAI.stringValue doubleValue]),
            complex<double>([self.matmulBR.stringValue doubleValue], [self.matmulBI.stringValue doubleValue]),
            complex<double>([self.matmulCR.stringValue doubleValue], [self.matmulCI.stringValue doubleValue])
            
        }),
        array<complex<double>, 3>({
            complex<double>([self.matmulDR.stringValue doubleValue], [self.matmulDI.stringValue doubleValue]),
            complex<double>([self.matmulER.stringValue doubleValue], [self.matmulEI.stringValue doubleValue]),
            complex<double>([self.matmulFR.stringValue doubleValue], [self.matmulFI.stringValue doubleValue])
            
        }),
        array<complex<double>, 3>({
            complex<double>([self.matmulGR.stringValue doubleValue], [self.matmulGI.stringValue doubleValue]),
            complex<double>([self.matmulHR.stringValue doubleValue], [self.matmulHI.stringValue doubleValue]),
            complex<double>([self.matmulIR.stringValue doubleValue], [self.matmulII.stringValue doubleValue])
            
        }),
    });
    
    auto rhs = array<array<complex<double>,3>, 3>({
        array<complex<double>, 3>({
            complex<double>([self.matmulAR2.stringValue doubleValue], [self.matmulAI2.stringValue doubleValue]),
            complex<double>([self.matmulBR2.stringValue doubleValue], [self.matmulBI2.stringValue doubleValue]),
            complex<double>([self.matmulCR2.stringValue doubleValue], [self.matmulCI2.stringValue doubleValue])
            
        }),
        array<complex<double>, 3>({
            complex<double>([self.matmulDR2.stringValue doubleValue], [self.matmulDI2.stringValue doubleValue]),
            complex<double>([self.matmulER2.stringValue doubleValue], [self.matmulEI2.stringValue doubleValue]),
            complex<double>([self.matmulFR2.stringValue doubleValue], [self.matmulFI2.stringValue doubleValue])
            
        }),
        array<complex<double>, 3>({
            complex<double>([self.matmulGR2.stringValue doubleValue], [self.matmulGI2.stringValue doubleValue]),
            complex<double>([self.matmulHR2.stringValue doubleValue], [self.matmulHI2.stringValue doubleValue]),
            complex<double>([self.matmulIR2.stringValue doubleValue], [self.matmulII2.stringValue doubleValue])
            
        }),
    });
    
    
    button.enabled = false;
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        
        auto value = compute_complex_matrix_product(lhs, rhs);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            self.matmulresult1.stringValue = [NSString stringWithFormat:@"[ %f + %fi, %f + %fi, %f + %fi ]", value[0][0].real(), value[0][0].imag(), value[0][1].real(), value[0][1].imag(), value[0][2].real(), value[0][2].imag()];
            
            self.matmulresult2.stringValue = [NSString stringWithFormat:@"[ %f + %fi, %f + %fi, %f + %fi ]", value[1][0].real(), value[1][0].imag(), value[1][1].real(), value[1][1].imag(), value[1][2].real(), value[1][2].imag()];
            
            self.matmulresult3.stringValue = [NSString stringWithFormat:@"[ %f + %fi, %f + %fi, %f + %fi ]", value[2][0].real(), value[2][0].imag(), value[2][1].real(), value[2][1].imag(), value[2][2].real(), value[2][2].imag()];
            
            button.enabled = true;
        });
    });
    
}

@end
