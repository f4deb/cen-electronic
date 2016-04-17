#include "pll.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printPll(OutputStream* outputStream, Pll* pll) {
    PllData* pllData = &(pll->pllData);
    appendHex2(outputStream, pllData->accel_X);
}

void initPll(Pll* pll, 
        InitPLLFunction* initPLL,
        GetAccelPLLFunction* getAccelPLL, 
        
        int* object) {
    pll->initPLL = initPLL;
    pll->getAccelPLL = getAccelPLL;    
    pll->object = object;
}

bool isPllInitialized(Pll* pll) {
    if (pll->initPLL == NULL 
        | pll->getAccelPLL == NULL ) {
        return false;
    }
    return true;
}
