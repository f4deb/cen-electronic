#include "../../../common/commons.h"

#include "i2cMaster.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/buffer.h"

void i2cMasterWriteBuffer(char address, Buffer* buffer) {


    portableMasterWaitSendI2C();
    // Wait till Start sequence is completed
    //WaitI2C();

    portableStartI2C();
    // Adress
    portableMasterWriteI2C(address);
    WaitI2C();

    int count = getBufferElementsCount(buffer);
    int i;
    for (i = 0; i < count; i++) {
        char c = bufferReadChar(buffer);
        portableMasterWriteI2C(c);
        WaitI2C();
    }

    portableStopI2C();
}

void i2cMasterWriteChar(char address, char c) {
    // We append to a buffer
    portableStartI2C();
    // Wait till Start sequence is completed
    //WaitI2C();

    // Adress
    portableMasterWriteI2C(address);
    WaitI2C();

    // Data
    portableMasterWriteI2C(c);
    WaitI2C();

    portableStopI2C();
}

char i2cMasterReadChar(char address) {

    portableStartI2C();

    // send the address again with read bit
    portableMasterWriteI2C(address | 0x01);
    WaitI2C();

    unsigned char data = portableMasterReadI2C();

    portableStopI2C();
    return data;
}

char i2cMasterReadRegisterValue(char address, char commandRegister) {
    // Set the register command
    WaitI2C();
    portableStartI2C();
    portableMasterWaitSendI2C();
    // send the address
    portableMasterWriteI2C(address);
    WaitI2C();
    // send the register
    portableMasterWriteI2C(commandRegister);
    WaitI2C();
    portableStopI2C();
    WaitI2C();

    // Read the register command
    portableStartI2C();
    portableMasterWaitSendI2C();
    // send the address again with read bit
    portableMasterWriteI2C(address | 0x01);
    WaitI2C();
    // read the data
    char data = portableMasterReadI2C();
    portableStopI2C();
    return data;
}
