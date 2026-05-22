#ifndef ADXL_H
#define ADXL_H

#include "IAdxlTransport.h"

class Adxl {
private:
    IAdxlTransport* transport;
    
    short xValue;
    short yValue;
    short zValue;

    int lastReadAxis;
    
    static const int DEVICE_ID_ADDR = 0x00;
    static const int POWER_CTL_ADDR = 0x2D;
    static const int X_AXIS_ADDR = 0x32;
    static const int Y_AXIS_ADDR = 0x34;
    static const int Z_AXIS_ADDR = 0x36;
    
    static const char DEVICE_ID = 0xE5;
    static const char POWER_CTL_MEASURE_BIT = 0x08;

public:
    Adxl(IAdxlTransport* transport) : transport(transport), xValue(0), yValue(0), zValue(0), lastReadAxis(0) {}

    bool init();

    bool isConnected();
    bool startMeasurement();

    /// @brief Stop measurement mode
    /// @return True if successful
    bool stopMeasurement();

    /// @brief Read fresh data from sensor and update cached values
    /// @return True if successful
    bool readData();

    /// @brief Get X-axis value (triggers update on first call, then uses cache)
    /// @return X-axis acceleration value
    short getX();

    /// @brief Get Y-axis value (triggers update on first call, then uses cache)
    /// @return Y-axis acceleration value
    short getY();

    /// @brief Get Z-axis value (triggers update on first call, then uses cache)
    /// @return Z-axis acceleration value
    short getZ();
};

#endif // ADXL_H