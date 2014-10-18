#include <stdlib.h>

#include "../../common/commons.h"

#include "serialOutputStream.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

// ----------------------------------- OUTPUT STREAM INTERFACE ------------------------------------

void flushSerial(OutputStream* outputStream) {
    // don't do anything
}

// -> SERIAL PORT 1

void openOutputStreamSerial1(OutputStream* outputStream, int param1) {
    if (param1 == 0) {
        openSerialAtDefaultSpeed(SERIAL_PORT_1);
    } else {
        openSerial(SERIAL_PORT_1, param1);
    }
}

void closeOutputStreamSerial1(OutputStream* outputStream) {
    closeSerial(SERIAL_PORT_1);
}

void writeChar1(OutputStream* outputStream, char c) {
    serialPutc(SERIAL_PORT_1, c);
}

void initSerialOutputStream1(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamSerial1;
    outputStream->closeOutputStream = closeOutputStreamSerial1;
    outputStream->writeChar = writeChar1;
    outputStream->flush = flushSerial;
}

// -> SERIAL PORT 2

void openOutputStreamSerial2(OutputStream* outputStream, int param1) {
    if (param1 == 0) {
        openSerialAtDefaultSpeed(SERIAL_PORT_2);
    } else {
        openSerial(SERIAL_PORT_2, param1);
    }
}

void closeOutputStreamSerial2(OutputStream* outputStream) {
    closeSerial(SERIAL_PORT_2);
}

void writeChar2(OutputStream* outputStream, char c) {
    serialPutc(SERIAL_PORT_2, c);
}

void initSerialOutputStream2(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamSerial2;
    outputStream->closeOutputStream = closeOutputStreamSerial2;
    outputStream->writeChar = writeChar2;
    outputStream->flush = flushSerial;
}

// -> SERIAL PORT 3

void openOutputStreamSerial3(OutputStream* outputStream, int param1) {
    if (param1 == 0) {
        openSerialAtDefaultSpeed(SERIAL_PORT_3);
    } else {
        openSerial(SERIAL_PORT_3, param1);
    }
}

void closeOutputStreamSerial3(OutputStream* outputStream) {
    closeSerial(SERIAL_PORT_3);
}

void writeChar3(OutputStream* outputStream, char c) {
    serialPutc(SERIAL_PORT_3, c);
}

void initSerialOutputStream3(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamSerial3;
    outputStream->closeOutputStream = closeOutputStreamSerial3;
    outputStream->writeChar = writeChar3;
    outputStream->flush = flushSerial;
}

// -> SERIAL PORT 4

void openOutputStreamSerial4(OutputStream* outputStream, int param1) {
    if (param1 == 0) {
        openSerialAtDefaultSpeed(SERIAL_PORT_4);
    } else {
        openSerial(SERIAL_PORT_4, param1);
    }
}

void closeOutputStreamSerial4(OutputStream* outputStream) {
    closeSerial(SERIAL_PORT_4);
}

void writeChar4(OutputStream* outputStream, char c) {
    serialPutc(SERIAL_PORT_4, c);
}

void initSerialOutputStream4(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamSerial4;
    outputStream->closeOutputStream = closeOutputStreamSerial4;
    outputStream->writeChar = writeChar4;
    outputStream->flush = flushSerial;
}

// -> SERIAL PORT 5

void openOutputStreamSerial5(OutputStream* outputStream, int param1) {
    if (param1 == 0) {
        openSerialAtDefaultSpeed(SERIAL_PORT_5);
    } else {
        openSerial(SERIAL_PORT_5, param1);
    }
}

void closeOutputStreamSerial5(OutputStream* outputStream) {
    closeSerial(SERIAL_PORT_5);
}

void writeChar5(OutputStream* outputStream, char c) {
    serialPutc(SERIAL_PORT_5, c);
}

void initSerialOutputStream5(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamSerial5;
    outputStream->closeOutputStream = closeOutputStreamSerial5;
    outputStream->writeChar = writeChar5;
    outputStream->flush = flushSerial;
}

// -> SERIAL PORT 6

void openOutputStreamSerial6(OutputStream* outputStream, int param1) {
    if (param1 == 0) {
        openSerialAtDefaultSpeed(SERIAL_PORT_6);
    } else {
        openSerial(SERIAL_PORT_6, param1);
    }
}

void closeOutputStreamSerial6(OutputStream* outputStream) {
    closeSerial(SERIAL_PORT_6);
}

void writeChar6(OutputStream* outputStream, char c) {
    serialPutc(SERIAL_PORT_6, c);
}

void initSerialOutputStream6(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamSerial6;
    outputStream->closeOutputStream = closeOutputStreamSerial6;
    outputStream->writeChar = writeChar6;
    outputStream->flush = flushSerial;
}


// PUBLIC INTERFACE

void initSerialOutputStream(OutputStream* outputStream, int serialPortIndex) {
    if (serialPortIndex == SERIAL_PORT_1) {
        initSerialOutputStream1(outputStream);
    } else if (serialPortIndex == SERIAL_PORT_2) {
        initSerialOutputStream2(outputStream);
    } else if (serialPortIndex == SERIAL_PORT_3) {
        initSerialOutputStream3(outputStream);
    } else if (serialPortIndex == SERIAL_PORT_4) {
        initSerialOutputStream2(outputStream);
    } else if (serialPortIndex == SERIAL_PORT_5) {
        initSerialOutputStream5(outputStream);
    } else if (serialPortIndex == SERIAL_PORT_6) {
        initSerialOutputStream6(outputStream);
    }
}
