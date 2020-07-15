#include "motorI2c.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void initMotorI2c(MotorI2c* motorI2c, WriteMotorI2cFunction* writeMotorI2c, ReadMotorI2cFunction* readMotorI2c, int* object) {
    motorI2c->writeMotorI2c = writeMotorI2c;
    motorI2c->readMotorI2c = readMotorI2c;
    motorI2c->object = object;
}

bool isMotorI2cInitialized(MotorI2c* motorI2c) {
    if (motorI2c->writeMotorI2c == NULL || motorI2c->readMotorI2c == NULL) {
        return false;
    }
    return true;
}