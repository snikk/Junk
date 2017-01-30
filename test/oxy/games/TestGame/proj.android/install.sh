#!/usr/bin/env sh
adb install -r bin/TestGame-debug.apk
adb shell am start -n org.oxygine.TestGame/org.oxygine.TestGame.MainActivity
