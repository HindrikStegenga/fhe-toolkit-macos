//
//  ViewController.h
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 17/10/2020.
//  Copyright © 2020 IBM. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewController : NSViewController <NSWindowDelegate>

@property (weak) IBOutlet NSTextField *leftTextField;
@property (weak) IBOutlet NSTextField *rightTextField;
@property (weak) IBOutlet NSTextField *resultLabel;

@property (weak) IBOutlet NSTextField *lhsX;
@property (weak) IBOutlet NSTextField *lhsY;
@property (weak) IBOutlet NSTextField *lhsZ;

@property (weak) IBOutlet NSTextField *rhsX;
@property (weak) IBOutlet NSTextField *rhsY;
@property (weak) IBOutlet NSTextField *rhsZ;

@property (weak) IBOutlet NSTextField *crossResultX;
@property (weak) IBOutlet NSTextField *crossResultZ;
@property (weak) IBOutlet NSTextField *crossResultY;

@property (weak) IBOutlet NSTextField *ckksLeftTextField;
@property (weak) IBOutlet NSTextField *ckksRightTextField;
@property (weak) IBOutlet NSTextField *ckksResultLbl;
@property (weak) IBOutlet NSTextField *polyXTextField;
@property (weak) IBOutlet NSTextField *polyResult;
@property (weak) IBOutlet NSTextField *polyATextField;
@property (weak) IBOutlet NSTextField *polyBTextField;
@property (weak) IBOutlet NSTextField *polyCTextField;

@property (weak) IBOutlet NSButton *lhsBit0;
@property (weak) IBOutlet NSButton *lhsBit1;
@property (weak) IBOutlet NSButton *lhsBit2;
@property (weak) IBOutlet NSButton *lhsBit3;
@property (weak) IBOutlet NSButton *lhsBit4;

@property (weak) IBOutlet NSButton *rhsBit0;
@property (weak) IBOutlet NSButton *rhsBit1;
@property (weak) IBOutlet NSButton *rhsBit2;
@property (weak) IBOutlet NSButton *rhsBit3;
@property (weak) IBOutlet NSButton *rhsBit4;

@property (weak) IBOutlet NSTextField *muBitTextField;
@property (weak) IBOutlet NSTextField *niBitTextField;

@property (weak) IBOutlet NSButton *bootstrapCheckBox;
@property (weak) IBOutlet NSTextField *complexLeftTextField;
@property (weak) IBOutlet NSTextField *complexRightTextField;
@property (weak) IBOutlet NSTextField *complexResultLabel;

@property (weak) IBOutlet NSTextField *matDetATextField;
@property (weak) IBOutlet NSTextField *matDetBTextField;
@property (weak) IBOutlet NSTextField *matDetCTextField;
@property (weak) IBOutlet NSTextField *matDetDTextField;
@property (weak) IBOutlet NSTextField *matDetETextField;
@property (weak) IBOutlet NSTextField *matDetFTextField;
@property (weak) IBOutlet NSTextField *matDetGTextField;
@property (weak) IBOutlet NSTextField *matDetHTextField;
@property (weak) IBOutlet NSTextField *matDetITextField;

@property (weak) IBOutlet NSTextField *matDeterminantResultLbl;
@property (weak) IBOutlet NSButton *mat2x2btn;
@property (weak) IBOutlet NSButton *mat3x3btn;

@property (weak) IBOutlet NSTextField *complexMulRealA;
@property (weak) IBOutlet NSTextField *complexMulImagA;
@property (weak) IBOutlet NSTextField *complexMulRealB;
@property (weak) IBOutlet NSTextField *complexMulImagB;
@property (weak) IBOutlet NSTextField *complexMulResultField;

@property (weak) IBOutlet NSTextField *ckksRotateResultTextField;
@property (weak) IBOutlet NSTextField *ckksRotateAmountTextField;
@property (weak) IBOutlet NSTextField *ckksRotateRealTextField;
@property (weak) IBOutlet NSTextField *ckksRotateImagTextField;


@property (weak) IBOutlet NSTextField *matmulAR;
@property (weak) IBOutlet NSTextField *matmulAI;
@property (weak) IBOutlet NSTextField *matmulBR;
@property (weak) IBOutlet NSTextField *matmulBI;
@property (weak) IBOutlet NSTextField *matmulCR;
@property (weak) IBOutlet NSTextField *matmulCI;
@property (weak) IBOutlet NSTextField *matmulDR;
@property (weak) IBOutlet NSTextField *matmulDI;
@property (weak) IBOutlet NSTextField *matmulER;
@property (weak) IBOutlet NSTextField *matmulEI;
@property (weak) IBOutlet NSTextField *matmulFR;
@property (weak) IBOutlet NSTextField *matmulFI;
@property (weak) IBOutlet NSTextField *matmulGR;
@property (weak) IBOutlet NSTextField *matmulGI;
@property (weak) IBOutlet NSTextField *matmulHR;
@property (weak) IBOutlet NSTextField *matmulHI;
@property (weak) IBOutlet NSTextField *matmulIR;
@property (weak) IBOutlet NSTextField *matmulII;


@property (weak) IBOutlet NSTextField *matmulAR2;
@property (weak) IBOutlet NSTextField *matmulAI2;
@property (weak) IBOutlet NSTextField *matmulBR2;
@property (weak) IBOutlet NSTextField *matmulBI2;
@property (weak) IBOutlet NSTextField *matmulCR2;
@property (weak) IBOutlet NSTextField *matmulCI2;
@property (weak) IBOutlet NSTextField *matmulDR2;
@property (weak) IBOutlet NSTextField *matmulDI2;
@property (weak) IBOutlet NSTextField *matmulER2;
@property (weak) IBOutlet NSTextField *matmulEI2;
@property (weak) IBOutlet NSTextField *matmulFR2;
@property (weak) IBOutlet NSTextField *matmulFI2;
@property (weak) IBOutlet NSTextField *matmulGR2;
@property (weak) IBOutlet NSTextField *matmulGI2;
@property (weak) IBOutlet NSTextField *matmulHR2;
@property (weak) IBOutlet NSTextField *matmulHI2;
@property (weak) IBOutlet NSTextField *matmulIR2;
@property (weak) IBOutlet NSTextField *matmulII2;

@property (weak) IBOutlet NSTextField *matmulresult1;
@property (weak) IBOutlet NSTextField *matmulresult2;
@property (weak) IBOutlet NSTextField *matmulresult3;

@end
