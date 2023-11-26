#include "rgb_midi.h"

void midiSetup(USBH_MIDI Midi)
{
  //Serial.println("[TESTING - BEGIN SET MIDI BOARD]");

  uint8_t buf[3];
  //buf[0] BEHAVIOR, buf[1] ADDRESS, buf[2] COLOR

  // -- GRID BUTTONS --
  buf[0] = 0x92; //50% brightness
  
  buf[2] = 0x39;
  buf[1] = 0x38;
  Midi.SendData(buf);
  buf[1] = 0x39;
  Midi.SendData(buf);
  buf[1] = 0x3A;
  Midi.SendData(buf);
  buf[1] = 0x3B;
  Midi.SendData(buf);
  buf[1] = 0x30;
  Midi.SendData(buf);
  buf[1] = 0x31;
  Midi.SendData(buf);
  buf[1] = 0x32;
  Midi.SendData(buf);
  buf[1] = 0x33;
  Midi.SendData(buf);

  buf[2] = 0x15;
  buf[1] = 0x3C;
  Midi.SendData(buf);
  buf[1] = 0x3D;
  Midi.SendData(buf);
  buf[1] = 0x3E;
  Midi.SendData(buf);
  buf[1] = 0x3F;
  Midi.SendData(buf);
  buf[1] = 0x34;
  Midi.SendData(buf);
  buf[1] = 0x35;
  Midi.SendData(buf);
  buf[1] = 0x36;
  Midi.SendData(buf);
  buf[1] = 0x37;
  Midi.SendData(buf);
  buf[1] = 0x2C;
  Midi.SendData(buf);

  buf[1] = 0x24;
  Midi.SendData(buf);
  buf[1] = 0x25;
  Midi.SendData(buf);
  buf[1] = 0x26;
  Midi.SendData(buf);
  buf[1] = 0x27;
  Midi.SendData(buf);
  buf[1] = 0x1C;
  Midi.SendData(buf);
  buf[1] = 0x1D;
  Midi.SendData(buf);
  buf[1] = 0x1E;
  Midi.SendData(buf);
  buf[1] = 0x1F;
  Midi.SendData(buf);
  buf[1] = 0x14;
  Midi.SendData(buf);
  buf[1] = 0x15;
  Midi.SendData(buf);
  buf[1] = 0x16;
  Midi.SendData(buf);
  buf[1] = 0x17;
  Midi.SendData(buf);
  buf[1] = 0x0C;
  Midi.SendData(buf);
  buf[1] = 0x0D;
  Midi.SendData(buf);
  buf[1] = 0x0E;
  Midi.SendData(buf);
  buf[1] = 0x0F;
  Midi.SendData(buf);

  buf[2] = 0x25;
  buf[1] = 0x18;
  Midi.SendData(buf);
  buf[1] = 0x19;
  Midi.SendData(buf);
  buf[1] = 0x1A;
  Midi.SendData(buf);
  buf[1] = 0x1B;
  Midi.SendData(buf);
  buf[1] = 0x10;
  Midi.SendData(buf);
  buf[1] = 0x11;
  Midi.SendData(buf);
  buf[1] = 0x12;
  Midi.SendData(buf);

  buf[2] = 0x09;
  buf[1] = 0x28;
  Midi.SendData(buf);
  buf[1] = 0x29;
  Midi.SendData(buf);
  buf[1] = 0x2A;
  Midi.SendData(buf);
  buf[1] = 0x2B;
  Midi.SendData(buf);
  buf[1] = 0x20;
  Midi.SendData(buf);
  buf[1] = 0x21;
  Midi.SendData(buf);
  buf[1] = 0x22;
  Midi.SendData(buf);
  buf[1] = 0x23;
  Midi.SendData(buf);

  // -- SINGLE BUTTONS --
  buf[0] = 0x90;
  buf[2] = 0x01;
  
  buf[1] = 0x76;
  Midi.SendData(buf);
  buf[1] = 0x77;
  Midi.SendData(buf);
  //buf[2] = 0x02;
  //buf[1] = 0x75;
  //Midi.SendData(buf);

  buf[2] = 0x01;

  buf[1] = 0x70;
  Midi.SendData(buf);
  buf[1] = 0x71;
  Midi.SendData(buf);
  buf[1] = 0x72;
  Midi.SendData(buf);

  buf[1] = 0x67;
  Midi.SendData(buf);
  buf[1] = 0x68;
  Midi.SendData(buf);

  buf[1] = 0x6A;
  Midi.SendData(buf);
  buf[1] = 0x6B;
  Midi.SendData(buf);

  buf[1] = 0x64;
  Midi.SendData(buf);

  buf[2] = 0x02;

  buf[1] = 0x66;
  Midi.SendData(buf);
  buf[1] = 0x65;
  Midi.SendData(buf);

  buf[2] = 0x02;

  buf[1] = 0x74;
  Midi.SendData(buf);
  buf[2] = 0x01;
  buf[1] = 0x7A;
  Midi.SendData(buf);

  //buf[1] = 0x64;
  //Midi.SendData(buf);

  //Serial.println("[TESTING - END SET MIDI BOARD]");
}

void midiColor(USBH_MIDI Midi)
{
  uint8_t buf[3];
  //buf[0] BEHAVIOR, buf[1] ADDRESS, buf[2] COLOR

  // -- GRID BUTTONS --
  buf[0] = 0x96;
  buf[1] = 0x00;
  buf[2] = 0x3F;
  for (int i = 0; i < 64; i++)
  {
    Midi.SendData(buf);

    buf[1] = buf[1] + 0x01;
    buf[2] = buf[2] + 0x01;
  }
}