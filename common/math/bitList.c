#include "bitList.h"

// #define BIT_LIST_DEBUG

#include "../../common/commons.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"

void initBitList(BitList* bitList, unsigned (*array)[], unsigned char arrayLength) {
    bitList->array = array;
    bitList->arrayLength = arrayLength;
    bitList->size = arrayLength * BITS_COUNT_IN_UNSIGNED_INT;
}

void clearBitList(BitList* bitList, bool initValue) {
    int i;
    int size = bitList->size;
    for (i = 0; i < size; i++) {
        setBit(bitList, i, initValue);
    }
}


void setBit(BitList* bitList, unsigned char index, bool value) {
    #ifdef BIT_LIST_DEBUG
        println(getInfoOutputStreamLogger());
        appendStringAndDec(getInfoOutputStreamLogger(), ", index=", index);
        appendStringAndDec(getInfoOutputStreamLogger(), ", value=", value);
    #endif
    if (index > bitList->size) {
        appendStringAndDec(getDebugOutputStreamLogger(), ", index=", index);
        appendStringAndDec(getDebugOutputStreamLogger(), ", size=", bitList->size);
        writeError(BIT_LIST_ARRAY_OUT_OF_BOUNDS);
        return;
    }
    unsigned int* arrayPointer = (unsigned int*) bitList->array;
    #ifdef BIT_LIST_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), "arrayPointer=", (int) arrayPointer);
    #endif

    // Division by 16 (2^4))
    unsigned char arrayIndex = index >> BITS_SHIFT_WIDTH;
    #ifdef BIT_LIST_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), ", arrayIndex=", arrayIndex);
    #endif

    // relative index = modulo
    unsigned char relativeIntIndex = index - (arrayIndex << BITS_SHIFT_WIDTH);
    #ifdef BIT_LIST_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), ", relativeIntIndex=", relativeIntIndex);
    #endif

    // Shift to the right cell index
    arrayPointer += arrayIndex;
    #ifdef BIT_LIST_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), ", newArrayPointer=", (int) arrayPointer);
        appendStringAndDec(getInfoOutputStreamLogger(), ", pointerValue=", *arrayPointer);
    #endif

    unsigned int mask = (1 << relativeIntIndex);
    if (value) {
        *arrayPointer |= mask;
    }
    else {
        *arrayPointer &= (~mask);
    }
    #ifdef BIT_LIST_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), ", newPointerValue=", *arrayPointer);
    #endif
}

bool getBit(BitList* bitList, unsigned char index) {
    #ifdef BIT_LIST_DEBUG
        println(getInfoOutputStreamLogger());
        appendStringAndDec(getInfoOutputStreamLogger(), ", index=", index);
    #endif    

    if (index > bitList->size) {
        writeError(BIT_LIST_ARRAY_OUT_OF_BOUNDS);
        return false;
    }

    unsigned int* arrayPointer = (unsigned int*) bitList->array;

    // Division by 16 (2^4))
    unsigned char arrayIndex = index >> BITS_SHIFT_WIDTH;
    #ifdef BIT_LIST_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), ", arrayIndex=", arrayIndex);
    #endif

    // relative index = modulo
    unsigned char relativeIntIndex = index - (arrayIndex << BITS_SHIFT_WIDTH);
    #ifdef BIT_LIST_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), ", relativeIntIndex=", relativeIntIndex);
    #endif
    
    arrayPointer += arrayIndex;
    #ifdef BIT_LIST_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), ", arrayPointer=", *arrayPointer);
    #endif

    unsigned int mask = (1 << relativeIntIndex);
    return (*arrayPointer & mask) != 0;
}


// DEBUG

void printBitList(OutputStream* outputStream, BitList* bitList) {
    int i;
    int size = bitList->size;
    println(outputStream);    
    appendStringAndDec(outputStream, "bitList->size=", bitList->size);
    println(outputStream);    
    for (i = 0; i < size; i++) {
        if ((i != 0) && (i % BITS_COUNT_IN_UNSIGNED_INT == 0)) {
			appendSpace(outputStream);
		}
        bool value = getBit(bitList, i);
        appendDec(outputStream, value);
    }
}
