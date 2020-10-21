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
@property (weak) IBOutlet NSTextFieldCell *resultLabel;

@end
