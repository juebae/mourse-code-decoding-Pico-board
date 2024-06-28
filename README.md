## Morse Code Project

Welcome to my Morse Code Project! This project translates Morse code inputs from a button into English letters, displaying them on a seven-segment display. The project is implemented using the Raspberry Pi Pico and C.

## Introduction

This project uses a button to input Morse code and a seven-segment display to show the corresponding English letter. The code captures the duration of button presses to determine whether the input is a dot or a dash and then decodes the Morse code into a letter of the English alphabet.

## Hardware Requirements
- Raspberry Pi Pico
- Seven-segment display (5161BS)
- Push button
- Connecting wires
- Breadboard
## Software Requirements
- Pico SDK
- CMake (version 3.13 or higher)
- GCC for ARM


## Installation
- Clone the Repository:

- Initialize the Pico SDK:

git submodule update --init

export PICO_SDK_PATH=<.path-to-pico-sdk.>

- Build the Project:

mkdir build

cd build

cmake ..

make

## Upload to Raspberry Pi Pico:

Connect your Raspberry Pi Pico to your computer.

Copy the generated out.uf2 file to the Pico’s storage.

## Usage
Connect the Hardware:

Connect the seven-segment display to the Raspberry Pi Pico as per the pinout defined in attached setup and use.pdf.

Connect the push button to GPIO 16 (Pin 21).
- Run the Program:

Once the code is uploaded, the Pico will start the program automatically.
Press the button to input Morse code:
Short press (< 250 ms) for a dot.
Long press (250 ms - 700 ms) for a dash.
View Output:

The corresponding letter will be displayed on the seven-segment display after a pause of 700 ms (indicating the end of a Morse code sequence).
