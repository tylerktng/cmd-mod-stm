#include "nmea_packet.h"
#include <cstdint>
#include <cstdio>
#include <ctime>

//From "nmea_packet.h"
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
) {
    char buf[BUFSIZ];
    char *pbuf = buf;
    pbuf += sprintf(pbuf,"$GPGGA,"); //Header
    pbuf += parseUTCTime(pbuf, time);
    pbuf += parseLaditude(pbuf, laditude);
    pbuf += parseLongitude(pbuf, longitude);
    pbuf += sprintf(pbuf, "%d,", pos_fix);
    pbuf += sprintf(pbuf, "%d,", satellites);
    pbuf += sprintf(pbuf, "%.1f,", hdop); //Is this only 1 unit of precision?
    pbuf += sprintf(pbuf, "%.1f,", altitude);
    pbuf += sprintf(pbuf, "%.1f,", geoidal_sep);
    pbuf += sprintf(pbuf, "M,,");//NOT using age of diff?
    pbuf += sprintf(pbuf, "%s,", station_id.c_str());
    pbuf += sprintf(pbuf, "%s", checksum.c_str());
    pbuf += sprintf(pbuf, "\r\n"); //end of message
    return buf;
}

size_t parseUTCTime(char *buf, float time) {
    int tm_hr = (int)(time / 3600) % 24;
    int tm_min = (int)(time) % 3600 / 60;
    int tm_sec = (int)(time) % 60;
    float ms = time - (int) time;
    size_t amount = sprintf(buf, "%2d%2d%2d%.3f,", tm_hr, tm_min, tm_sec, ms);
    return amount;
}

size_t parseLaditude(char *buf, float coord) {
    int degs = (int)coord;
    uintptr_t amount;
    float mins = (coord - degs) * 60; //get minutes from decimals
    int int_mins = (int) mins;
    float dec_mins = mins - (int) mins;
    if(degs < 0) {
        //South
        amount += sprintf(buf, "%2d%2d%.4f,S,", -degs, -int_mins, -dec_mins);
    } else {
        //North
        amount += sprintf(buf + amount, "%3d%2d%.4f,N,", degs, int_mins, dec_mins);
    }
    
    return (size_t) amount;
}

size_t parseLongitude(char *buf, float coord) {
    int degs = (int)coord;
    uintptr_t amount;
    float mins = (coord - degs) * 60; //get minutes from decimals
    int int_mins = (int) mins;
    float dec_mins = mins - (int) mins;
    if(degs < 0) {
        //West
        amount += sprintf(buf, "%3d%2d%.4f,W,", -degs, -int_mins, -dec_mins);
    } else {
        //East
        amount += sprintf(buf + amount, "%3d%2d%.4f,E,", degs, int_mins, dec_mins);
    }
    return (size_t) amount;
}