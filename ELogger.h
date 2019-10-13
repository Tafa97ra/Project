/* 
 * File:   ELogger.h
 * Author: Nyaaz
 *
 * Created on 12 October 2019, 20:45
 */

#ifndef ELOGGER_H
#define ELOGGER_H

// DEFINE Constants
const char RTCAddr = 0x6f;
const char SEC = 0x00; // see register table in datasheet
const char MIN = 0x01;
const char HOUR = 0x02;
const char TIMEZONE = 2; // +02H00 (RSA)

// DEFINE i/p and o/p
const int LEDS[] = {0,2,3}; //Alarm LEDS
const int BTNS[] = {27,26,25,23}; // B0, B1, B3, B4


