#ifndef RGB_MIDI_H
#define RGB_MIDI_H

// EXTERNAL LIBRARIES
#include <usbh_midi.h>

#include "rgb_main.h"

void midiSetup(USBH_MIDI Midi);
void midiColor(USBH_MIDI Midi);

#endif
