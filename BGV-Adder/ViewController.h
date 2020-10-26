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

@end
