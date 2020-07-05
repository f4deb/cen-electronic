#include "motorI2c.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

bool isMotorI2cInitialized(MotorI2c* motorI2c) {
    if (motorI2c->writeMotorI2c == NULL || motorI2c->readMotorI2c == NULL) {
        return false;
    }
    return true;
}