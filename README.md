# Alarm-clock-jukebox

Here is the project repo for my alarm clock that plays cellphone ringtones (i.e., a "jukebox"!)

The device uses a Nios II embedded softcore IP from Quartus, programmed on a MAX 10 FPGA. 
The ringtones are played using RTTTL (Ring Tones Text Transfer Language).

## Navigating the repo:

The C source code can be found in the software/ folder.
Schematics and software flowcharts for the device can be found in the diagrams/ folder.

## Features

- PWM with speaker to control volume 
User will select a "volume" switch and then on the display user
will have the option to increment or decrement the current volume
This will then adjust the duty cycle of the PWM on the speaker
(look into logarithic scaling for this adjustment?)

- Cellphone ringtone format for melodies
User can select a "melody" switch and then on the display
user will have the option to select from a programmed number
of cellphone ringtone songs ("Song 1, Song 2", etc.) jukebox format
Program will read these cellphone ringtone formats to play the appropiate frequencies
on the speaker and for the appropiate duration (for the notes)
