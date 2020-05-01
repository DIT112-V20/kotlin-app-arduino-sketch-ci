# CI for Kotlin app and Arduino ![Android CI] ![Arduino CI]

This repository includes a sample project Continuous Integration setup
for a system that is made up of a Kotlin/Android application and an Arduino sketch.

GitHub Actions is used ton run the CI pipeline since it reliably supports launching
an Android emulator (AVD) for running instrumented tests.

## Android

### Kotlin app

The Kotlin app is a simple GitHub browser based on the great
[tutorial](https://github.com/linero-tech/course_github_browser) by
[@hlinero](https://github.com/hlinero).

### CI

The following activities take place on CI:

* Build the Android app
* Run the unit tests
* Run the instrumented tests on an emulator

## Arduino

### Arduino sketches

The Arduino sketches illustrate how one would control and get sernsor data from
a [Smartcar](https://github.com/platisd/smartcar_shield) using GET requests.

The primary purpose of the sketches is to show how one could refactor a typical
Arduino sketch, for testability. The following sketches are included:

* [SmartcarWebserver](arduino/SmartcarWebserver)
  * A classic Arduino sketch. Very difficult to test in a *convenient* manner.
* [SmartcarWebserverWithClass](arduino/SmartcarWebserverWithClass)
  * A slightly more testable Arduino sketch which encapsulates the main functionality
  within a class. Still rather *inconvenient* to test as many things would have to
  be stubbed out.
* [SmartcarWebserverTestable](arduino/SmartcarWebserverTestable)
  * A testable sketch without any stubs or fakes, based on the
  [inversion of control](https://en.wikipedia.org/wiki/Inversion_of_control) principle.
  * [Unit tests](test/ut/SmartCarWebController_test.cpp)

### CI

The following activities take place on CI:

* Build the Arduino sketch for the `ESP32 DOIT Devkit V1` board
* Run the unit tests for the unit-testable sketch

[Android CI]: https://github.com/DIT112-V20/kotlin-app-arduino-sketch-ci/workflows/Android%20CI/badge.svg
[Arduino CI]: https://github.com/DIT112-V20/kotlin-app-arduino-sketch-ci/workflows/Arduino%20CI/badge.svg
