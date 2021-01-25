# adplay-unix-serial

This fork of [adplay-unix] includes a new player, [serial], that sends all
register writes over a Linux serial port. This is intended to be used with an
Arduino running [opl3serial] attached to an [OPL3 Duo!] board and requires the
[adplug-serial] fork.

Usage:

    adplay -O serial -d /dev/ttyACM0 <file>

[adplay-unix]: https://github.com/adplug/adplay-unix
[serial]: src/serial.cc
[opl3serial]: https://github.com/cknave/opl3serial
[OPL3 Duo!]: https://cheerful.nl/OPL3Duo/index.html
[adplug-serial]: https://github.com/cknave/adplug-serial

---

AdPlay/UNIX - UNIX console-based OPL2 audio player
Copyright (C) 2001 - 2017 Simon Peter <dn.tlp@gmx.net>

Description
-----------
AdPlay/UNIX is AdPlug's UNIX console-based frontend. AdPlug is a free,
universal OPL2 audio playback library. AdPlay/UNIX supports the full range
of AdPlug's file format playback features. Despite this, at the moment, only
emulated OPL2 output is supported by AdPlay/UNIX, but this on a wide range
of output devices.

Prerequisites
-------------
The following libraries are needed in order to compile this program:

|Library|Version|
|-------|-------|
|AdPlug |>= 1.4, or >= 2.2 for full feature support|

git
---
If you checked out from git, first run:

autoreconf --install

to generate the build cruft and get the configure script. You need recent
versions of autoconf, automake and libtool to do this.

Usage
-----
Start AdPlay/UNIX with at least one file to be played as parameter.
Additional commandline parameters are explained by typing:

adplay --help

Or by reading the man page. A more detailed doc will follow when i get the
time to write one. Any help is greatly appreciated!

	- Simon Peter <dn.tlp@gmx.net>
