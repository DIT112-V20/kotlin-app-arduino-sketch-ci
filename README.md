# CI for Kotlin app and Arduino ![Android CI] ![Arduino CI]

This repository includes a sample project Continuous Integration setup
for a system that is made up of a Kotlin/Android application and an Arduino sketch.

GitHub Actions is used ton run the CI pipeline since it reliably supports launching
an Android emulator (AVD) for running instrumented tests.

## Android

The following activities take place on CI:

* Build the Android app
* Run the unit tests
* Run the instrumented tests on an emulator

## Arduino

The following activities take place on CI:

* Build the Arduino sketch for the `ESP32 DOIT Devkit V1` board

[Android CI]: https://github.com/DIT112-V20/kotlin-app-arduino-sketch-ci/workflows/Android%20CI/badge.svg
[Arduino CI]: https://github.com/DIT112-V20/kotlin-app-arduino-sketch-ci/workflows/Arduino%20CI/badge.svg
