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

@end
