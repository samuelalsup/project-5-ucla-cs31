//
//  utilities.h
//  Project_5_CStrings
//
//  Created by Sam Alsup on 11/11/19.
//  Copyright © 2019 Sam Alsup. All rights reserved.
//

#ifndef utilities_h
#define utilities_h

#include <stdio.h>

#endif /* utilities_h */

const int MINWORDLEN = 4;
const int MAXWORDLEN = 6;

int getWords(char words[][MAXWORDLEN+1], int maxWords, const char wordfilename[]);
int randInt(int min, int max);
