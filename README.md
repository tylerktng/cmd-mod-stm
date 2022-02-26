# Command Test Module

This repository contains code for the RPL test board, using MBedOS. It will test
flight control board (FCB) on the following criteria (non-exhaustive):
* Does the FCB properly respond to commands from ground control?
* Does the FCB properly read input signals from the GPS and other peripherals?

The test board will run code from this repository, but will stream data from the
client application. See cmd-mod-client for details about that project.

Tests can be conducted on either the STM32 or the client application. The plan
currently is to tentatively have the client perform the test checks. That is,
send all response data from the FCB to the STM32, and stream it back.