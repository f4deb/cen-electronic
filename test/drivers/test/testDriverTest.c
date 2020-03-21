#include "testDriverTest.h"

#include <stdlib.h>
#include <time.h>

#include "../../../test/unity/unity.h"
#include "../../../common/clock/clock.h"
#include "../../../common/error/error.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/pc/consoleLogHandler.h"

#include "../../../device/device.h"
#include "../../../device/deviceList.h"
#include "../../../device/transmitMode.h"

#include "../../../device/clock/clockDevice.h"
#include "../../../device/clock/clockDeviceInterface.h"

#include "../../../device/test/testDevice.h"
#include "../../../device/test/testDeviceInterface.h"

#include "../../../device/motor/pwmMotorDevice.h"
#include "../../../device/motor/pwmMotorDeviceInterface.h"


#include "../../../drivers/clock/pc/pcClock.h"
#include "../../../drivers/driverList.h"
#include "../../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../../drivers/test/testDriver.h"

#include "../../../client/clock/clientClock.h"

// Logs
#define TEST_DRIVER_TEST_LOG_HANDLER_LIST_LENGTH 2
static LogHandlerList logHandlerListArray[TEST_DRIVER_TEST_LOG_HANDLER_LIST_LENGTH];

// Dispatchers
#define TEST_DRIVER_TEST_DATA_DISPATCHER_LIST_LENGTH 2
static DriverDataDispatcher driverDataDispatcherListArray[TEST_DRIVER_TEST_DATA_DISPATCHER_LIST_LENGTH];

// Drivers
#define TEST_DRIVER_TEST_REQUEST_DRIVER_BUFFER_LENGTH    40
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[TEST_DRIVER_TEST_REQUEST_DRIVER_BUFFER_LENGTH];
#define TEST_DRIVER_TEST_RESPONSE_DRIVER_BUFFER_LENGTH    40
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[TEST_DRIVER_TEST_RESPONSE_DRIVER_BUFFER_LENGTH];


// Devices
#define TEST_DRIVER_TEST_DEVICE_LIST_LENGTH        10
static Device deviceListArray[TEST_DRIVER_TEST_DEVICE_LIST_LENGTH];

void testDriverTestTestSuite(void) {
    RUN_TEST(test_testDriverGetValue);
}

void test_testDriverGetValue(void) {
    initLogs(LOG_LEVEL_DEBUG, (LogHandler(*)[]) & logHandlerListArray, TEST_DRIVER_TEST_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    addConsoleLogHandler(LOG_LEVEL_DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);

    // Dispatchers
    initDriverDataDispatcherList((DriverDataDispatcher(*)[]) & driverDataDispatcherListArray, TEST_DRIVER_TEST_DATA_DISPATCHER_LIST_LENGTH);
    addLocalDriverDataDispatcher();

    // Init the drivers
    initDrivers(&driverRequestBuffer, (char(*)[]) & driverRequestBufferArray, TEST_DRIVER_TEST_REQUEST_DRIVER_BUFFER_LENGTH,
            &driverResponseBuffer, (char(*)[]) & driverResponseBufferArray, TEST_DRIVER_TEST_RESPONSE_DRIVER_BUFFER_LENGTH);

    // Get test driver for debug purpose
    addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);

    // Devices
    initDeviceList((Device(*)[]) & deviceListArray, TEST_DRIVER_TEST_DEVICE_LIST_LENGTH);
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());

    // Test Driver Test

    int actual = testDriverGetValue(10, 20);
    TEST_ASSERT_EQUAL(30, actual);

    // Clock Driver Test

    Clock clock;
    initPcClock(&clock);
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));

    ClockData clockData;
    clientClockGetClockData(&clockData);

    // Get the real time
    time_t rawtime;
    struct tm timeinfo;
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    int expected = timeinfo.tm_year - 100; // we store the date after 2000 (100 = 2000 - 1900)

    TEST_ASSERT_EQUAL(expected, clockData.year);

    // Motor Driver Test

}