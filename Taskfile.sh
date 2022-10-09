#!/bin/bash

ARDUINO_CLI="./bin/arduino-cli"
ARDUINO_LINT="./bin/arduino-lint"
ARDUINO_CLI_VERSION=$(cat .arduino.cli.version)
ARDUINO_LINT_VERSION=$(cat .arduino.lint.version)

function install {
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh -s $ARDUINO_CLI_VERSION
    arduino-cli core install arduino:avr
    lib-install 'Servo@1.1.8'

    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-lint/main/etc/install.sh | sh -s $ARDUINO_LINT_VERSION
}

function lib-install {
    $ARDUINO_CLI lib install "${@}"
}

function compile {
    $ARDUINO_CLI compile --fqbn arduino:avr:pro .
}

function lint {
    $ARDUINO_LINT
}

function list-boards {
    $ARDUINO_CLI board list
}

function help {
    echo "$0 <task> <args>"
    echo "Tasks:"
    compgen -A function | cat -n
}

TIMEFORMAT="Task completed in %3lR"
time ${@:-help}