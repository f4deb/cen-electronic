#include <stdbool.h>
#include <stdlib.h>

#include "pllDevice.h"
#include "pllDeviceInterface.h"

#include "../../common/pll/pll.h"
#include "../../common/error/error.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

static Pll* pll;

void _devicePllCheckInitialized() {
    if (pll == NULL) {
        writeError(PLL_NULL);
    }
    if (!isPllInitialized(pll)) {
        writeError(PLL_NOT_INITIALIZED);
    }
}

void devicePllInit(void) {
    _devicePllCheckInitialized();
    pll->initPLL(pll);
}

void devicePllShutDown(void) {
}

bool isPllDeviceOk(void) {
    return true;
}

void devicePllHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    _devicePllCheckInitialized();
    if (header == WRITE_FREQUENCY_PLL) {     
        PllData* pllData = pll->getAccelPLL(pll);
        appendHex4(outputStream, pllData->accel_X);
        append(outputStream,':');
        appendHex4(outputStream, pllData->accel_Y);
        append(outputStream,':');
        appendHex4(outputStream, pllData->accel_Z);
        ackCommand(outputStream, PLL_DEVICE_HEADER, WRITE_FREQUENCY_PLL);
    }
}


      
        


static DeviceDescriptor descriptor = {
    .deviceInit = &devicePllInit,
    .deviceShutDown = &devicePllShutDown,
    .deviceIsOk = &isPllDeviceOk,
    .deviceHandleRawData = &devicePllHandleRawData,
};

DeviceDescriptor* getPllDeviceDescriptor(Pll* pllParam) {
    pll = pllParam;
    return &descriptor;
}

