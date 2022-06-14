# Arduino Reaction Test

![License](https://img.shields.io/github/license/zS1L3NT/arduino-reaction-test?style=for-the-badge) ![Languages](https://img.shields.io/github/languages/count/zS1L3NT/arduino-reaction-test?style=for-the-badge) ![Top Language](https://img.shields.io/github/languages/top/zS1L3NT/arduino-reaction-test?style=for-the-badge) ![Commit Activity](https://img.shields.io/github/commit-activity/y/zS1L3NT/arduino-reaction-test?style=for-the-badge) ![Last commit](https://img.shields.io/github/last-commit/zS1L3NT/arduino-reaction-test?style=for-the-badge)

This is a reaction test game that you can play on an Arduino board.

This game was tested on an `ESP8266` board, `NodeMCU 1.0 (ESP-12E Module)`.

I will upload an image of the board setup and video demonstration in the future.

## Motivation

I saw this game at a CCA open house when I was 13, and now that I have my own Arduino board, I wanted to rebuild this game for memories.

## Features

-   Button to start/restart the game
-   5 LEDs, 4 red and 1 green

## Usage

### Setup

-   Connect the `ESP8266` board to a computer via USB-A
-   Add `https://arduino.esp8266.com/stable/package_esp8266com_index.json` to the list of Board Manager URLs
-   Under Board Manager, install the board `ESP8266`
-   Select the correct Serial Port of the board in the IDE
-   Change the Board Type to `NodeMCU 1.0 (ESP-12E Module)`
-   Change the Baud Rate to `9600`


## Built with

-   Arduino
