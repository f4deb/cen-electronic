#include <peripheral/legacy/i2c_legacy.h>

#include "MPU-6050.h"

#include "../../common/MPU/MPU.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

I2cBusConnection* _mpu6050GetI2cBusConnection(Mpu* mpu) {
    I2cBusConnection* result = (I2cBusConnection*) mpu->object;
    return result;
}
/** @private
 * Setup the MPU6050 
 */
void _setupMPU6050 (Mpu* mpu){
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    
    _writeMpu6050Register(mpu, MPU6050_RA_PWR_MGMT_1, 0);   
}

/**
 * @see MPU.h
 * @private
 * Read the acceleration from the MPU-6050 and store in the structure.
 * @param mpu the mpu
 */
MpuData* _readMpu6050AccMpu(Mpu* mpu) {
    
    //temporary storage
    int data_h;
    int data_l;
    
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    // init pointer
    MpuData* mpuData = &(mpu->mpuData);
       
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_RA_ACCEL_XOUT_H);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_READ_ADDRESS);
    WaitI2C(i2cBus);
    
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_X = ((data_h<<8)|data_l);
    
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_Y = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    
    mpuData->accel_Z = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
        
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    return mpuData;
}

/**
 * @see MPU.h
 * @private
 * Read the gyroscope from the MPU-6050 and store in the structure.
 * @param mpu the mpu
 */
MpuData* _readMpu6050GyroMpu(Mpu* mpu) {
    
    int data_h;
    int data_l;
    
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    MpuData* mpuData = &(mpu->mpuData);
       
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_RA_GYRO_XOUT_H);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_READ_ADDRESS);
    WaitI2C(i2cBus);
    
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_gyro_X = ((data_h<<8)|data_l);   
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_gyro_Y = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    
    mpuData->accel_gyro_Z = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
        
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    return mpuData;
}

/**
 * @see MPU.h
 * @private
 * Read the temperature from the MPU-6050 and store in the structure.
 * @param mpu the mpu
 */
MpuData* _readMpu6050TemperatureMpu(Mpu* mpu) {
    
    int data_h;
    int data_l;
    
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    MpuData* mpuData = &(mpu->mpuData);
       
    // address the temperature register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_RA_TEMP_OUT_H);
    WaitI2C(i2cBus);
//    portableMasterStopI2C(i2cBusConnection);
//    WaitI2C(i2cBus);

    // read the temperature register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_READ_ADDRESS);
    WaitI2C(i2cBus);
    
    // at first, the MSB register
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    // at second the LSB register
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2C(i2cBus);
        
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // temp  =  MSB + LSB
    int temp =((data_h<<8)|data_l);
    
    // Conversion from Kelvin to Celsius
    mpuData->temperature = temp;//((temp/340)*100 + 3653)/100;

    // transfert the result
    return mpuData;
}

/**
 * @see MPU.h
 * @private
 * Read the data from the MPU-6050 and store in the structure.
 * @param mpu the mpu
 */
MpuData* _readMpu6050AllData (Mpu* mpu){
    //temporary storage
    int data_h;
    int data_l;
    
    // I2C Bus Prepare   
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    // init pointer
    MpuData* mpuData = &(mpu->mpuData);
       
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_RA_ACCEL_XOUT_H);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_READ_ADDRESS);
    WaitI2C(i2cBus);
    
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_X = ((data_h<<8)|data_l);
    
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_Y = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_Z = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);    
    
    // at first, the MSB register
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    // at second the LSB register
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
        
    // temp  =  MSB + LSB
    int temp =((data_h<<8)|data_l);   
    
    // Conversion from Kelvin to Celsius
    mpuData->temperature = ((temp/340)*100 + 3653)/100;
    
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_gyro_X = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
    
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    
    mpuData->accel_gyro_Y = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);
    
    WaitI2C(i2cBus);
    data_h = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    data_l = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    
    mpuData->accel_gyro_Z = ((data_h<<8)|data_l);
    WaitI2C(i2cBus);  

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    return mpuData;
}

/**
 * @see MPU.h
 * @private
 * Read one register from the MPU-6050 
 * @param mpu the mpu
 * @return dataRegister the data from register
 */
char _readMpu6050Register (Mpu* mpu, int index){
    char dataRegister;
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    // address the register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, index);
    WaitI2C(i2cBus);

    // select the register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_READ_ADDRESS);
    WaitI2C(i2cBus);
    
    // read the register
    dataRegister = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2C(i2cBus);
        
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    // transfert the result
    return dataRegister;
}

/**
 * @see MPU.h
 * @private
 * Write one register in the MPU-6050 
 * @param mpu the mpu
 * @param index, the index to select the register
 * @return dataRegister the data read from register
 */
void _writeMpu6050Register(Mpu* mpu, char index, char data){
    I2cBusConnection* i2cBusConnection = _mpu6050GetI2cBusConnection(mpu);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    
    portableMasterWaitSendI2C(i2cBusConnection);
    // address the register
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, MPU6050_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, index);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, data);
    WaitI2C(i2cBus);    
    
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void initMpuMPU6050(Mpu* mpu, I2cBusConnection* i2cBusConnection) {
    initMpu(mpu, 
            _setupMPU6050,
            _readMpu6050AccMpu,
            _readMpu6050GyroMpu,
            _readMpu6050TemperatureMpu,
            _readMpu6050AllData,
            _readMpu6050Register,
            _writeMpu6050Register,
            (int*) i2cBusConnection);
}