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

## Endpoint emulator

Projects involving hardware pose some *physical* limitations on your way of working
since the software you develop, eventually, has to run on the target device and not
your computer.

If each team member has access to the hardware, then this is not much of a problem.
However, there are cases where this hardware is not readily available for everyone
and has to be shared. In such cases, the team should try to decrease its dependency
to hardware so to minimize bottlenecks and risks related to this constraint.

One way to achieve this when using the ESP32 enabled Smartcar platform is creating a
dummy endpoint that runs on the developer's machine and responds in the same or similar
way as a Smartcar would. Doing that, the team can agree on the **inputs** and **outputs**
of their (unavailable) hardware and make the dummy endpoint respond accordingly.<br>
This can decrease the need to have constant access to the *actual* hardware since a
developer may conduct their work according to the **agreed communication interface**.
As long as the endpoint emulator is running, then it should respond (from a web request
pespective) like the Smartcar.

Similarly, the developer(s) who is/are tasked with writing firmware for the Smartcar,
do not need to have access to the *real application* or client. To emulate requests coming
from the application or the client, they can use their **browser** or software such as the
[ARC](https://chrome.google.com/webstore/detail/advanced-rest-client/hgmloofddffdnphfgcellkdfbfbjeloo).

For example, to set the speed to `60` without the application that normally controls
the Smartcar, one would have to visit the following URL on their browser:
`http://smartcar.local/drive?speed=65`.<br>
This way, the dependency on **synchronous collaboration** between developers that work
on the app and those that work on the Smartcar, is decreased.

[smartcar_endpoint.py](endpoint-emulator/smartcar_endpoint.py) uses Python3 and Flask
to expose the same functionality as the Arduino sketches. The main difference from a
client's perspective is that a different IP is used.<br>
That being said, there are probably workarounds (outside the scope of this tutorial) for
this is one *must* use the same IP/hostname as the Smartcar.

[Android CI]: https://github.com/DIT112-V20/kotlin-app-arduino-sketch-ci/workflows/Android%20CI/badge.svg
[Arduino CI]: https://github.com/DIT112-V20/kotlin-app-arduino-sketch-ci/workflows/Arduino%20CI/badge.svg
