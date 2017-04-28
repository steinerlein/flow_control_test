#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_BLE.h>
#include "Adafruit_BluefruitLE_UART.h"

#include "settings.h"

Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN,BLUEFRUIT_UART_CTS_PIN,BLUEFRUIT_UART_RTS_PIN);

int32_t sServiceId;
int32_t sChar1Id;
int32_t sChar2Id;
int32_t sChar3Id;
int32_t sChar4Id;
int32_t sChar5Id;


// A small helper
void error(const __FlashStringHelper*err) {
        Serial.print("error:");
        Serial.println(err);
        while (1) ;
}

// initializes the BLE module and sets all the services and characteristics
bool initBLE(bool echo = false){

        boolean success = false;

        /* Initialise the module */
        if(VERBOSE_MODE) Serial.print(F("Initialising the Bluefruit LE module: "));

        // refer to bluefruitconfig.h for verbose mode
        success = ble.begin(VERBOSE_MODE);
        if (!success) {
                if(VERBOSE_MODE) error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
        }
        if(VERBOSE_MODE) Serial.println( F("OK!") );

        Serial2.println("ATI");

        ble.setInterCharWriteDelay(5);

        /* Disable command echo from Bluefruit */
        ble.echo(false);


        /* Perform a factory reset to make sure everything is in a known state */
        if(VERBOSE_MODE) Serial.println(F("Performing a factory reset: "));
        if (!ble.factoryReset() ) {
                if(VERBOSE_MODE) error(F("Couldn't factory reset"));
        }

        /* Disable command echo from Bluefruit */
        ble.echo(false);

        /* Change the device name to make it easier to find */
        if(VERBOSE_MODE) Serial.println(F("Setting device name to 'example device': "));

        if (!ble.sendCommandCheckOK(F("AT+GAPDEVNAME=EXAMPLE DEVICE")) ) {
                if(VERBOSE_MODE) error(F("Unable to set device name!"));
        }

        /* Add the Smart Chair Service definition */
        /* Service ID should be 1 */
        if(VERBOSE_MODE) Serial.println(F("Adding a custom Service definition"));
        success = ble.sendCommandWithIntReply( F("AT+GATTADDSERVICE=UUID128=7c-33-3f-99-33-c1-49-50-90-dd-85-a1-60-ac-50-97"), &sServiceId);
        if (!success) {
                if(VERBOSE_MODE) error(F("unable to add service"));
        }else {
                if(VERBOSE_MODE) Serial.print("Added service ID: ");
                if(VERBOSE_MODE) Serial.println(sServiceId);
        }

        /*Add the STemperature characteristic*/
        if(VERBOSE_MODE) Serial.println(F("Adding a custom characteristic 1"));
        success = ble.sendCommandWithIntReply( F("AT+GATTADDCHAR=UUID128=3b-de-7e-bd-75-76-46-1d-91-31-35-0b-44-2d-7a-64, PROPERTIES=0x12, MIN_LEN=1, MAX_LEN=4, VALUE=0, DESCRIPTION=Temperature"), &sChar1Id);
        if (!success) {
                if(VERBOSE_MODE) error(F("unable to add characteristic 1"));
        }else {
                if(VERBOSE_MODE) Serial.print("Added characteristic with ID: ");
                if(VERBOSE_MODE) Serial.println(sChar1Id);
        }

        /*Add the Humidity characteristic*/
        if(VERBOSE_MODE) Serial.println(F("Adding a custom characteristic 2"));
        success = ble.sendCommandWithIntReply( F("AT+GATTADDCHAR=UUID128=4b-57-72-83-6a-de-4d-4f-8d-4d-06-b5-f5-fe-40-18, PROPERTIES=0x12, MIN_LEN=1, MAX_LEN=4, VALUE=0, DESCRIPTION=Humidity"), &sChar2Id);
        if (!success) {
                if(VERBOSE_MODE) error(F("unable to add characteristic 2"));
        }else {
                if(VERBOSE_MODE) Serial.print("Added characteristic with ID: ");
                if(VERBOSE_MODE) Serial.println(sChar2Id);
        }

        /*Add the decibel characteristic*/
        if(VERBOSE_MODE) Serial.println(F("Adding a custom characteristic 3"));
        success = ble.sendCommandWithIntReply( F("AT+GATTADDCHAR=UUID128=d6-93-d6-2b-fe-7b-4c-5d-b7-4a-a9-12-ff-46-4a-55, PROPERTIES=0x12, MIN_LEN=1, MAX_LEN=4, VALUE=0, DESCRIPTION=decibel"), &sChar3Id);
        if (!success) {
                if(VERBOSE_MODE) error(F("unable to add characteristic 3"));
        }else {
                if(VERBOSE_MODE) Serial.print("Added characteristic with ID: ");
                if(VERBOSE_MODE) Serial.println(sChar3Id);
        }

        /*Add the gas quality characteristic*/
        if(VERBOSE_MODE) Serial.println(F("Adding a custom characteristic 4"));
        success = ble.sendCommandWithIntReply( F("AT+GATTADDCHAR=UUID128=9c-32-bb-65-52-02-41-a3-80-a0-f1-07-f4-18-8f-a9, PROPERTIES=0x12, MIN_LEN=1, MAX_LEN=4, VALUE=0, DESCRIPTION=gas quality"), &sChar4Id);
        if (!success) {
                if(VERBOSE_MODE) error(F("unable to add characteristic 4"));
        }else {
                if(VERBOSE_MODE) Serial.print("Added characteristic with ID: ");
                if(VERBOSE_MODE) Serial.println(sChar4Id);
        }

        /*Add the gas quality characteristic*/
        if(VERBOSE_MODE) Serial.println(F("Adding a custom characteristic 5"));
        success = ble.sendCommandWithIntReply( F("AT+GATTADDCHAR=UUID128=9c-32-bb-25-5b-02-41-a3-80-a0-f1-07-f4-18-8f-a9, PROPERTIES=0x12, MIN_LEN=1, MAX_LEN=4, VALUE=0, DESCRIPTION=gas quality"), &sChar5Id);
        if (!success) {
                if(VERBOSE_MODE) error(F("unable to add characteristic 5"));
        }else {
                if(VERBOSE_MODE) Serial.print("Added characteristic with ID: ");
                if(VERBOSE_MODE) Serial.println(sChar5Id);
        }



        /* Reset the device for the new service setting changes to take effect */
        if(VERBOSE_MODE) Serial.print(F("Performing a SW reset (service changes require a reset): "));
        ble.reset();
        ble.echo(false);
        ble.verbose(VERBOSE_MODE);

        if(VERBOSE_MODE) Serial.println();
        digitalWrite(13, LOW);
        return success;
}

void setup(){
        Serial.begin(115200);

        pinMode(BLUEFRUIT_UART_CTS_PIN, OUTPUT);
        digitalWrite(BLUEFRUIT_UART_CTS_PIN, LOW);

        bool didinitBLE = initBLE();
        Serial.println(didinitBLE);
}

void loop(){
        delay(50);
}
