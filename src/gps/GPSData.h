#ifndef NMEA_PACKET
#define NMEA_PACKET
#include <string>

/* Holds the raw data read from the serial port */
struct RawGPSData {
    double time; 
    double alt; //altitude
    double x, y;
};


enum Cardinals {
    NORTH, SOUTH, EAST, WEST
};

/*
 * https://www.sparkfun.com/datasheets/GPS/NMEA%20Reference%20Manual-Rev2.1-Dec07.pdf
 * Create a GGA Packet (NMEA), and returns it as a std::string
 * 
 * time - time given in seconds since 00:00:00 UTC
 * laditude - laditude in degrees. Negative if South
 * ns - north or south.
 * longitude - longitude in degrees. Negative if West
 * ew - east or west.
 * pos_fix - 
 * satellites - number of satellites used to make the measurement
 */
std::string createGGAPacket(
    float time,
    float laditude,
    Cardinals ns,
    float longitude,
    Cardinals ew,
    int pos_fix,
    int satellites,
    float hdop,
    float altitude,
    float geoidal_sep,
    std::string& station_id,
    std::string& checksum
);

/*
 * Parses the input time into HHMMSS.SSS format. Adds the string to input buf.
 * Automatically appends a null termination char.
 * Returns the number of bytes written, excluding the null termination char.
 */
size_t parseUTCTime(char *buf, float time);

/*
 * Parses the input coordinate into DDMM.MMMM format. Adds the string to input buf.
 * Automatically appends a null termination char.
 * Returns the number of bytes written, excluding the null termination char.
 */
size_t parseLaditude(char *buf, float coord);


/*
 * Parses the input coordinate into DDDMM.MMMM format. Adds the string to input buf.
 * Automatically appends a null termination char.
 * Returns the number of bytes written, excluding the null termination char.
 */
size_t parseLongitude(char *buf, float coord);

#endif