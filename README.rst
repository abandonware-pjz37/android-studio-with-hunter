WORK-IN-PROGRESS

Android Studio with Hunter
==========================

Example of using Android Studio project with Hunter package manager.

This is modified example of HelloJni sample:

* https://github.com/googlesamples/android-ndk/tree/master/hello-jni

Small one-file MD5 hash calculation C library as a third party:

* https://docs.hunter.sh/en/latest/packages/pkg/md5.html

Minimal CMake version 3.9.2:

* https://gitlab.kitware.com/cmake/cmake/issues/17253

Tested with:
* CMake 3.10.1
* Android Studio 3.2 Canary 3, built on February 8, 2018
* Linux

Hints
=====

Create ``android-studio/local.properties`` file before opening Android Studio and
check that ``ndk.dir``, ``sdk.dir`` and ``cmake.dir`` are set:

.. code-block:: none

  ndk.dir=/home/user/opt/android-sdk/ndk-bundle
  sdk.dir=/home/user/opt/android-sdk
  cmake.dir=/home/user/opt/cmake

Build debug APK for arm64-v8a architecture:

.. code-block:: none

  > cd android-studio
  [android-studio]> ./gradlew asDebug -Parch=arm64-v8a

Create debug APKs for all architectures:

.. code-block:: none

  [android-studio]> ./gradlew asDebug

Clean:

.. code-block:: none

  [android-studio]> ./gradlew clean

CMake generate step instructions (including Hunter work) can
be found in file ``cmake_build_output.txt``.

``HUNTER_KEEP_PACKAGE_SOURCES`` is set to ``ON`` to check that stepping into
third party sources Android Studio feature is working.
