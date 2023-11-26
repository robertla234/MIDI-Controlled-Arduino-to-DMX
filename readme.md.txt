This repository contains code for a show-tested Arduino project to run DMX fixtures through a DMX component with input from a MIDI Controller through USB.

Components used:
- Arduino MEGA 2560 REV3
- USB Host Shield by ATNSINC
- 3Pin Terminal Adapter XLR/DMX by Colorful-USA
- RS-485 MAX485 by JIUWU

Fixtures included:
- Chauvet DJ SlimPAR 56 Wash Light
- SUMGER DM-RGB400 Laser Projector
- LIXADA 50W Gobo Mini Moving Head
- ADJ Inno Pocket Z4 Moving Head
- SHEHDS 10W Beam Mini Moving Head
- TCFUNDy 1500W Vertical Spray Fog Machine

MIDI Controller used:
- AKAI APC Mini mk2 Abelton Live Controller

The dimmer, RGB, and effect speed values are all addressed to the faders on the controller. This is for the specific values the fader provides that are quickly changed in a show setting.

All specific effects like color, shape, and enable-disable commands are addressed to the buttons on the controller. This is because these effects are state specific and definite. They do not blend into each other often, if at all.




