// ----------------------------------------------------
// INTERNAL REFERENCES
// ----------------------------------------------------
#include "rgb_main.h"
#include "rgb_dmx.h"
#include "rgb_midi.h"
#include <hidboot.h>
#include <usbhub.h>
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <usbh_midi.h>

// ----------------------------------------------------
// System General Variables
// ----------------------------------------------------
bool testMode = true;
bool mode = true;       // 0 - Audio Reactive Mode (DEFAULT), 1 - Controller Mode
int strobeMode = 0; // 0 - Off, 1/2 - On
bool fogMode = false;

// ----------------------------------------------------
// DMX Variables
// ----------------------------------------------------
//SlimPAR56 slimFixture(1);
//SlimPAR56 slimFixtureInner(9);
SlimPAR56 slimFixtureL(1); // 7 channel
SlimPAR56 slimFixtureInnerL(9); // 7 channel
SlimPAR56 slimFixtureInnerR(17); // 7 channel
SlimPAR56 slimFixtureR(25); //7 channel
DMRGB400 dmrgbFixture(33); // 9 channel
SingleMovingHead singleMovingFixtureL(49, 'L'); // 11 channel
SingleMovingHead singleMovingFixtureR(65, 'R'); // 11 channel
QuadMovingHead quadMovingFixtureL(81, 'L'); // 22 channel
QuadMovingHead quadMovingFixtureR(129, 'R'); // 22 channel
BeamMovingHead beamMovingFixtureL(153, 'L'); // 13 channel
BeamMovingHead beamMovingFixtureR(169, 'R'); // 13 channel
RGBFog rgbFog(185); // 7 channel

//MiniKinta miniKinta(177); // 4 channel

//int dimmerLevelWash = 255;
//int dimmerLevelSpot = 255;

int dimmerLevelWashOL = 255;
int dimmerLevelWashIL = 255;
int dimmerLevelWashIR = 255;
int dimmerLevelWashOR = 255;
int dimmerLevelSpotOL = 255;
int dimmerLevelSpotIL = 255;
int dimmerLevelSpotIR = 255;
int dimmerLevelSpotOR = 255;

bool slowDim = true;
int slowDimWash = 0;
int slowDimSpot = 0;
bool laserEnabled = false;
int alternateColorMode = 1;

bool faderRGB = false;
int r = 255;
int g = 255;
int b = 255;

// ----------------------------------------------------
// MIDI USB Host Shield Variables
// ----------------------------------------------------
USB Usb;
USBHub Hub(&Usb);
USBH_MIDI  Midi(&Usb);

// ----------------------------------------------------
// MIDI USB Host Shield Setup
// ----------------------------------------------------
void onInit()
{
  char buf[20];
  uint16_t vid = Midi.idVendor();
  uint16_t pid = Midi.idProduct();
  sprintf(buf, "VID:%04X, PID:%04X", vid, pid);
  Serial.println(buf); 
}
void MIDI_poll()
{
  char buf[16];
  uint8_t bufMidi[MIDI_EVENT_PACKET_SIZE];
  uint16_t  rcvd;
  String midiSignal;

  if (Midi.RecvData( &rcvd,  bufMidi) == 0 ) {
    uint32_t time = (uint32_t)millis();
    sprintf(buf, "%04X%04X:%3d:", (uint16_t)(time >> 16), (uint16_t)(time & 0xFFFF), rcvd); // Split variable to prevent warnings on the ESP8266 platform
    //Serial.print("..");
    //Serial.print(buf);

    for (int i = 0; i < MIDI_EVENT_PACKET_SIZE; i++) {
      if (i < 4)
      {
        sprintf(buf, "%02X", bufMidi[i]);
        //Serial.print(buf);
        midiSignal += buf;
      }
    }

    //Serial.println(midiSignal);
    midiSignalHandler(midiSignal);
  }
}
void midiSignalHandler(String midiSignal)
{
  String event = midiSignal.substring(0, 4);
  String location = midiSignal.substring(4, 6);
  String velocity = midiSignal.substring(6);

  //Serial.println("Event: " + event);
  //Serial.println("Location: " + location);
  //Serial.println("Veloctiy: " + velocity);

  if (event.equals("0990"))
  {
    buttonHandler(location);
  }
  else if (event.equals("0BB0"))
  {
    faderHandler(location, velocity);
  }
}
void buttonHandler(String location)
{
  Serial.println("BLocation: " + location);

  #pragma region Dimmer Levels
  if (location.equals("76"))
  {
    //dimmerLevelWash = dimmerLevelSpot = 255;
    dimmerLevelWashOL = 255;
    dimmerLevelWashIL = 255;
    dimmerLevelWashIR = 255;
    dimmerLevelWashOR = 255;

    dimmerLevelSpotOL = 255;
    dimmerLevelSpotIL = 255;
    dimmerLevelSpotIR = 255;
    dimmerLevelSpotOR = 255;
  }
  else if (location.equals("77"))
  {
    //dimmerLevelWash = dimmerLevelSpot = 0;
    dimmerLevelWashOL = 0;
    dimmerLevelWashIL = 0;
    dimmerLevelWashIR = 0;
    dimmerLevelWashOR = 0;

    dimmerLevelSpotOL = 0;
    dimmerLevelSpotIL = 0;
    dimmerLevelSpotIR = 0;
    dimmerLevelSpotOR = 0;
  }
  else if (location.equals("75"))
  {
    //slowDim = !slowDim;
  }
  else if (location.equals("6B"))
  {
    //dimmerLevelWash = 255;
    //dimmerLevelSpot = 0;
    dimmerLevelWashOL = 255;
    dimmerLevelWashIL = 255;
    dimmerLevelWashIR = 255;
    dimmerLevelWashOR = 255;

    dimmerLevelSpotOL = 0;
    dimmerLevelSpotIL = 0;
    dimmerLevelSpotIR = 0;
    dimmerLevelSpotOR = 0;
  }
  else if (location.equals("6A"))
  {
    //dimmerLevelSpot = 255;
    //dimmerLevelWash = 0;
    dimmerLevelWashOL = 0;
    dimmerLevelWashIL = 0;
    dimmerLevelWashIR = 0;
    dimmerLevelWashOR = 0;

    dimmerLevelSpotOL = 255;
    dimmerLevelSpotIL = 255;
    dimmerLevelSpotIR = 255;
    dimmerLevelSpotOR = 255;
  }
  else if (location.equals("68"))
  {
    dimmerLevelWashOL = 255;
    dimmerLevelWashIL = 255;
    dimmerLevelWashIR = 255;
    dimmerLevelWashOR = 255;
  }
  else if (location.equals("67"))
  {
    dimmerLevelSpotOL = 255;
    dimmerLevelSpotIL = 255;
    dimmerLevelSpotIR = 255;
    dimmerLevelSpotOR = 255;
  }
  else if (location.equals("28"))
  {
    dimmerLevelWashOL = 255;
  }
  else if (location.equals("29"))
  {
    dimmerLevelWashIL = 255;
  }
  else if (location.equals("2A"))
  {
    dimmerLevelWashIR = 255;
  }
  else if (location.equals("2B"))
  {
    dimmerLevelWashOR = 255;
  }
  else if (location.equals("20"))
  {
    dimmerLevelSpotOL = 255;
  }
  else if (location.equals("21"))
  {
    dimmerLevelSpotIL = 255;
  }
  else if (location.equals("22"))
  {
    dimmerLevelSpotIR = 255;
  }
  else if (location.equals("23"))
  {
    dimmerLevelSpotOR = 255;
  }

  #pragma endregion Dimmer Levels

  #pragma region DMX Color Change
  if (location.equals("38")) // White
  {
    singleMovingFixtureL.Color(1);
    singleMovingFixtureR.Color(1);
    r = 255;
    g = 255;
    b = 255;
  }
  else if (location.equals("39")) // Red
  {
    dmrgbFixture.Color(1);
    singleMovingFixtureL.Color(alternateColorMode == 2 ? 1 : 2);
    singleMovingFixtureR.Color(alternateColorMode == 2 ? 1 : 2);
    r = 255;
    g = 0;
    b = 0;
  }
  else if (location.equals("3A")) // Blue
  {
    dmrgbFixture.Color(6);
    singleMovingFixtureL.Color(alternateColorMode == 2 ? 1 : 3);
    singleMovingFixtureR.Color(alternateColorMode == 2 ? 1 : 3);
    r = 75;
    g = 75;
    b = 255;
  }
  else if (location.equals("3B")) // Orange
  {
    singleMovingFixtureL.Color(alternateColorMode == 2 ? 1 : 4);
    singleMovingFixtureR.Color(alternateColorMode == 2 ? 1 : 4);
    r = 255;
    g = 150;
    b = 0;
  }
  else if (location.equals("30")) // Blue
  {
    dmrgbFixture.Color(3);
    singleMovingFixtureL.Color(alternateColorMode == 2 ? 1 : 5);
    singleMovingFixtureR.Color(alternateColorMode == 2 ? 1 : 5);
    r = 0;
    g = 0;
    b = 255;
  }
  else if (location.equals("31")) // Yellow
  {
    dmrgbFixture.Color(4);
    singleMovingFixtureL.Color(alternateColorMode == 2 ? 1 : 6);
    singleMovingFixtureR.Color(alternateColorMode == 2 ? 1 : 6);
    r = 255;
    g = 255;
    b = 0;
  }
  else if (location.equals("32")) // Green
  {
    dmrgbFixture.Color(2);
    singleMovingFixtureL.Color(alternateColorMode == 2 ? 1 : 7);
    singleMovingFixtureR.Color(alternateColorMode == 2 ? 1 : 7);
    r = 0;
    g = 255;
    b = 0;
  }
  else if (location.equals("33")) // Magenta
  {
    dmrgbFixture.Color(5);
    singleMovingFixtureL.Color(alternateColorMode == 2 ? 1 : 8);
    singleMovingFixtureR.Color(alternateColorMode == 2 ? 1 : 8);
    r = 255;
    g = 0;
    b = 255;
  }
  #pragma endregion DMX Color Change

  #pragma region Alternate Color
  if (location.equals("70"))     // NORMAL
  {
    alternateColorMode = 1;
  }
  else if (location.equals("71")) // SINGLE WHITE
  {
    alternateColorMode = 2;
  }
  else if (location.equals("72")) // QUAD WHITE
  {
    alternateColorMode = 3;
  }
  #pragma endregion Alternate Color

  #pragma region Moving Head Movement
  // --SAME POS--
  if (location.equals("3C"))
  {
    quadMovingFixtureL.Front();
    quadMovingFixtureR.Front();
    singleMovingFixtureL.Front();
    singleMovingFixtureR.Front();
  }
  else if (location.equals("3D"))
  {
    quadMovingFixtureL.Down();
    quadMovingFixtureR.Down();
    singleMovingFixtureL.Down();
    singleMovingFixtureR.Down();
  }
  else if (location.equals("3E"))
  {
    quadMovingFixtureL.Inward();
    quadMovingFixtureR.Inward();
    singleMovingFixtureL.Inward();
    singleMovingFixtureR.Inward();
  }
  else if (location.equals("3F"))
  {
    quadMovingFixtureL.Outward();
    quadMovingFixtureR.Outward();
    singleMovingFixtureL.Outward();
    singleMovingFixtureR.Outward();
  }
  // --DIFF POS--
  else if (location.equals("34"))
  {
    quadMovingFixtureL.Down();
    quadMovingFixtureR.Down();
    singleMovingFixtureL.Front();
    singleMovingFixtureR.Front();
  }
  else if (location.equals("35"))
  {
    quadMovingFixtureL.Front();
    quadMovingFixtureR.Front();
    singleMovingFixtureL.Down();
    singleMovingFixtureR.Down();
  }
  else if (location.equals("36"))
  {
    quadMovingFixtureL.Outward();
    quadMovingFixtureR.Outward();
    singleMovingFixtureL.Inward();
    singleMovingFixtureR.Inward();
  }
  else if (location.equals("37"))
  {
    quadMovingFixtureL.Inward();
    quadMovingFixtureR.Inward();
    singleMovingFixtureL.Outward();
    singleMovingFixtureR.Outward();
  }
  else if (location.equals("2C"))
  {
    quadMovingFixtureL.MoveMacro();
    quadMovingFixtureR.MoveMacro();
    singleMovingFixtureL.MoveMacro();
    singleMovingFixtureR.MoveMacro();
  }
  else if (location.equals("24"))
  {
    quadMovingFixtureL.Front();
  }
  else if (location.equals("25"))
  {
    singleMovingFixtureL.Front();
  }
  else if (location.equals("26"))
  {
    singleMovingFixtureR.Front();
  }
  else if (location.equals("27"))
  {
    quadMovingFixtureR.Front();
  }
  else if (location.equals("1C"))
  {
    quadMovingFixtureL.Down();
  }
  else if (location.equals("1D"))
  {
    singleMovingFixtureL.Down();
  }
  else if (location.equals("1E"))
  {
    singleMovingFixtureR.Down();
  }
  else if (location.equals("1F"))
  {
    quadMovingFixtureR.Down();
  }
  else if (location.equals("14"))
  {
    quadMovingFixtureL.Outward();
  }
  else if (location.equals("15"))
  {
    singleMovingFixtureL.Outward();
  }
  else if (location.equals("16"))
  {
    singleMovingFixtureR.Inward();
  }
  else if (location.equals("17"))
  {
    quadMovingFixtureR.Inward();
  }
  else if (location.equals("0C"))
  {
    quadMovingFixtureL.Inward();
  }
  else if (location.equals("0D"))
  {
    singleMovingFixtureL.Inward();
  }
  else if (location.equals("0E"))
  {
    singleMovingFixtureR.Outward();
  }
  else if (location.equals("0F"))
  {
    quadMovingFixtureR.Outward();
  }
  #pragma endregion Moving Head Movement

  #pragma region Laser Pattern Selection
  // --SAME POS--
  if (location.equals("18"))
  {
    dmrgbFixture.HorizontalScan();
  }
  else if (location.equals("19"))
  {
    dmrgbFixture.VerticalScan();
  }
  else if (location.equals("1A"))
  {
    dmrgbFixture.CrossRotate();
  }
  else if (location.equals("1B"))
  {
    dmrgbFixture.Bowtie();
  }
  else if (location.equals("10"))
  {
    dmrgbFixture.Circle();
  }
  else if (location.equals("11"))
  {
    dmrgbFixture.Triangle();
  }
  else if (location.equals("12"))
  {
    dmrgbFixture.BlockyZigZag();
  }
  #pragma endregion Laser Pattern Selection

  #pragma region Motor Speed
  // --Motor Speed
  if (location.equals("66")) // FAST
  {
    quadMovingFixtureL.MoveSpeed(true);
    quadMovingFixtureR.MoveSpeed(true);
    singleMovingFixtureL.MoveSpeed(true);
    singleMovingFixtureR.MoveSpeed(true);

    beamMovingFixtureL.MoveSpeed(true);
    beamMovingFixtureR.MoveSpeed(true);
  }
  else if (location.equals("65")) // SLOW
  {
    quadMovingFixtureL.MoveSpeed(false);
    quadMovingFixtureR.MoveSpeed(false);
    singleMovingFixtureL.MoveSpeed(false);
    singleMovingFixtureR.MoveSpeed(false);
    
    beamMovingFixtureL.MoveSpeed(false);
    beamMovingFixtureR.MoveSpeed(false);
  }
  #pragma endregion Motor Speed

  // --LASER--
  if (location.equals("74"))
  {
    laserEnabled = !laserEnabled;
    dmrgbFixture.LaserOnOff(laserEnabled);
  }

  // --STROBE--
  if (location.equals("7A"))
  {
    if (strobeMode > 0)
    {
      strobeMode = 0;

      slimFixtureL.Strobe(false);
      slimFixtureInnerL.Strobe(false);
      slimFixtureInnerR.Strobe(false);
      slimFixtureR.Strobe(false);
      singleMovingFixtureL.Strobe(false);
      singleMovingFixtureR.Strobe(false);
      quadMovingFixtureL.Strobe(false);
      quadMovingFixtureR.Strobe(false);

      beamMovingFixtureL.Strobe(false);
      beamMovingFixtureR.Strobe(false);

      rgbFog.Strobe(false);
    }
    else
    {
      strobeMode = 1;

      slimFixtureL.Strobe(true);
      slimFixtureInnerL.Strobe(true);
      slimFixtureInnerR.Strobe(true);
      slimFixtureR.Strobe(true);
      singleMovingFixtureL.Strobe(true);
      singleMovingFixtureR.Strobe(true);
      quadMovingFixtureL.Strobe(true);
      quadMovingFixtureR.Strobe(true);

      beamMovingFixtureL.Strobe(true);
      beamMovingFixtureR.Strobe(true);

      rgbFog.Strobe(true);

      dimmerLevelWashOL = 255;
      dimmerLevelWashIL = 255;
      dimmerLevelWashIR = 255;
      dimmerLevelWashOR = 255;

      dimmerLevelSpotOL = 255;
      dimmerLevelSpotIL = 255;
      dimmerLevelSpotIR = 255;
      dimmerLevelSpotOR = 255;
    }
  } 

  // --FOG--
  if (location.equals("64"))
  {
    fogMode = !fogMode;
    rgbFog.Fog(fogMode);
  }
}
void faderHandler(String location, String velocity)
{
  char vel[3];
  velocity.toCharArray(vel, velocity.length() + 1);
  int value = strtol(vel, 0, 16);
  value = map(value, 0, 127, 0, 255);

  Serial.print("FLocation: " + location);
  Serial.print(" FVelocity: ");
  Serial.println(value);

  if (location.equals("38"))
  {
    dimmerLevelWashOL = value;
    dimmerLevelWashIL = value;
    dimmerLevelWashIR = value;
    dimmerLevelWashOR = value;

    dimmerLevelSpotOL = value;
    dimmerLevelSpotIL = value;
    dimmerLevelSpotIR = value;
    dimmerLevelSpotOR = value;
  }
  else if (location.equals("37"))
  {
    dimmerLevelWashOL = value;
    dimmerLevelWashIL = value;
    dimmerLevelWashIR = value;
    dimmerLevelWashOR = value;
  }
  else if (location.equals("36"))
  {
    dimmerLevelSpotOL = value;
    dimmerLevelSpotIL = value;
    dimmerLevelSpotIR = value;
    dimmerLevelSpotOR = value;
  }
  else if (location.equals("30"))
  {
    r = value;
  }
  else if (location.equals("31"))
  {
    g = value;
  }
  else if (location.equals("32"))
  {
    b = value;
  }
  else if (location.equals("35"))
  {
    slowDimWash = map(value, 0, 255, 0, 15);
    slowDimSpot = map(value, 0, 255, 0, 15);
  }
  else if (location.equals("34"))
  {
    slowDimWash = map(value, 0, 255, 0, 15);
  }
  else if (location.equals("33"))
  {
    slowDimSpot = map(value, 0, 255, 0, 15);
  }
}

// ----------------------------------------------------
// System-Wide Functions
// ----------------------------------------------------
int dimmerValue(int dimLvl, int slowDim)
{
  if (dimLvl > 0)
  {
    dimLvl = dimLvl - slowDim;
    if (dimLvl < 0)
    {
      dimLvl = 0;
    }
  }
  return dimLvl;
}

// ----------------------------------------------------
// Arduino Required Setup
// ----------------------------------------------------
void setup()
{
  Serial.begin(115200);

  if (Usb.Init() == -1) {
    while (1); //halt
  }//if (Usb.Init() == -1...
  delay( 200 );

  // Register onInit() function
  Midi.attachOnInit(onInit);
  DmxSimple.usePin(DMX_DATAPIN);
}
void loop()
{
  // CONNECTION TEST
  if (testMode)
  {
    Serial.println("[TESTING - BEGIN]");
    DMX_Blackout();

    slimFixtureL.Setup();
    delay(500);
    slimFixtureInnerL.Setup();
    delay(500);
    slimFixtureInnerR.Setup();
    delay(500);
    slimFixtureR.Setup();
    delay(500);
    singleMovingFixtureL.Setup();
    delay(500);
    quadMovingFixtureL.Setup();
    delay(500);
    singleMovingFixtureR.Setup();
    delay(500);
    quadMovingFixtureR.Setup();
    delay(500);

    beamMovingFixtureL.Setup();
    delay(500);
    beamMovingFixtureR.Setup();
    delay(500);

    dmrgbFixture.Setup();
    delay(500);

    rgbFog.Setup();
    delay(500);

    testMode = false;
    Serial.println("[TESTING - END]");
  }
  Usb.Task();
  if ( Midi ) {
    MIDI_poll();
    midiSetup(Midi);
  }
  else{
    Serial.println("Midi inactive.");
  }

  if (mode) // TRIGGERABLE MODE
  {
    // Strobe Mode Logic
    if (strobeMode == 1)
    {
      strobeMode = 2;
    }
    else if (strobeMode == 2)
    {
      strobeMode = 1;
    }

    // DMX Logic
    if (slowDim)
    {
      dimmerLevelWashOL = dimmerValue(dimmerLevelWashOL, slowDimWash);
      dimmerLevelWashIL = dimmerValue(dimmerLevelWashIL, slowDimWash);
      dimmerLevelWashIR = dimmerValue(dimmerLevelWashIR, slowDimWash);
      dimmerLevelWashOR = dimmerValue(dimmerLevelWashOR, slowDimWash);

      dimmerLevelSpotOL = dimmerValue(dimmerLevelSpotOL, slowDimSpot);
      dimmerLevelSpotIL = dimmerValue(dimmerLevelSpotIL, slowDimSpot);
      dimmerLevelSpotIR = dimmerValue(dimmerLevelSpotIR, slowDimSpot);
      dimmerLevelSpotOR = dimmerValue(dimmerLevelSpotOR, slowDimSpot);
    }

    slimFixtureL.Color(r, g, b);
    slimFixtureInnerL.Color(r, g, b);
    slimFixtureInnerR.Color(r, g, b);
    slimFixtureR.Color(r, g, b);
    quadMovingFixtureL.Color(r, g, b);
    quadMovingFixtureR.Color(r, g, b);
    beamMovingFixtureL.Color(r, g, b);
    beamMovingFixtureR.Color(r, g, b);
    rgbFog.Color(r, g, b);

    if (alternateColorMode == 2)
    {
      slimFixtureL.Color(255, 255, 255);
      slimFixtureR.Color(255, 255, 255);
    }
    else if (alternateColorMode == 3)
    {
      slimFixtureInnerL.Color(255, 255, 255);
      slimFixtureInnerR.Color(255, 255, 255);

      quadMovingFixtureL.Color(255, 255, 255);
      quadMovingFixtureR.Color(255, 255, 255);
    }

    slimFixtureL.Dimmer(dimmerLevelWashOL);
    slimFixtureInnerL.Dimmer(dimmerLevelWashIL);
    slimFixtureInnerR.Dimmer(dimmerLevelWashIR);
    slimFixtureR.Dimmer(dimmerLevelWashOR);

    quadMovingFixtureL.Dimmer(dimmerLevelSpotOL);
    singleMovingFixtureL.Dimmer(dimmerLevelSpotIL);
    singleMovingFixtureR.Dimmer(dimmerLevelSpotIR);
    quadMovingFixtureR.Dimmer(dimmerLevelSpotOR);

    beamMovingFixtureL.Dimmer(dimmerLevelSpotOL);
    beamMovingFixtureR.Dimmer(dimmerLevelSpotOR);

    unsigned long delayTime = 5;
  }
  else
  { // AUDIO REACTIVE MODE
    delay(1000);
  }
}
