## flow control test with HW UART

This repo contains all data related to an issue where flow control is not working as expected.

On lines 9 & 10 of main.cpp the only change between the to scenarios is made. The two scenarios are:

### 1. flow control not enabled, inter char delay of 5ms

  In this case all the settings are properly received by the Bluefriend UART module, but the transmission is much slower than it needs to be, because the baudrate is artificially slowed down.

### 2. flow control enabled

In this case everything works fine until the Bluefriend UART module pulls high its flow control pin to stop data from incoming. Unfortunately the library doesn't react to that and the command doesn't execute properly.

To demonstrate this, there are logic analyzer recordings in /logic_analyzer_data/ which can be opened with software from saleae: https://www.saleae.com/downloads

The test is being made with a teensy and a Bluefriend UART module with up to date firmware version 0.7.7
