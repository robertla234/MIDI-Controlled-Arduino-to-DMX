#include "rgb_dmx.h"

void DMX_Blackout()
{
  for (int i = 1; i <= 512; i++)
  {
    DmxSimple.write(i, 0);
  }
}

// SlimPAR 56
#pragma region SlimPAR56
SlimPAR56::SlimPAR56(int _startAddr)
{
  startAddr = _startAddr;
}
void SlimPAR56::Strobe(bool onOff)
{
  if (onOff)
  {
    Dimmer(255);
    DmxSimple.write(startAddr + 4, 250);
  }
  else
  {
    Dimmer(0);
    DmxSimple.write(startAddr + 4, 0);
  }
}
void SlimPAR56::Color(int R, int G, int B)
{
  DmxSimple.write(startAddr, R);
  DmxSimple.write(startAddr + 1, G);
  DmxSimple.write(startAddr + 2, B);
}
void SlimPAR56::Dimmer(int dimLevel)
{
  //DmxSimple.write(startAddr + 4, 0);
  DmxSimple.write(startAddr + 6, dimLevel);
}

void SlimPAR56::Setup()
{
  Dimmer(255);
  Color(255, 0, 0);
  delay(400);
  Color(0, 255, 0);
  delay(400);
  Color(0, 0, 255);
  delay(400);
  Color(255, 255, 255);
  Strobe(true);
  delay(500);
  Strobe(false);
  Dimmer(0);
  Color(255, 255, 255);
}
#pragma endregion SlimPAR56

// DM-RGB400
#pragma region DM-RGB400
DMRGB400::DMRGB400(int _startAddr)
{
  startAddr = _startAddr;
}
void DMRGB400::LaserOnOff(bool onOff)
{
  if (onOff)
  {
    DmxSimple.write(startAddr, 255);
  }
  else
  {
    DmxSimple.write(startAddr, 0);    
  }
}
void DMRGB400::Color(int colorSelect)
{
  if (colorSelect == 1) //Red
  {
    DmxSimple.write(startAddr + 8, 65);
  }
  else if (colorSelect == 2) //Green
  {
    DmxSimple.write(startAddr + 8, 100);
  }
  else if (colorSelect == 3) //Blue
  {
    DmxSimple.write(startAddr + 8, 130);
  }
  else if (colorSelect == 4) //Yellow
  {
    DmxSimple.write(startAddr + 8, 180);
  }
  else if (colorSelect == 5) //Magenta
  {
    DmxSimple.write(startAddr + 8, 210);
  }
  else if (colorSelect == 6) //Cyan
  {
    DmxSimple.write(startAddr + 8, 255);
  }
}
void DMRGB400::VerticalScan()
{
  DmxSimple.write(startAddr + 1, 155);
  DmxSimple.write(startAddr + 2, 0);
  DmxSimple.write(startAddr + 5, 33);
  DmxSimple.write(startAddr + 6, 128);
  DmxSimple.write(startAddr + 7, 0);
}
void DMRGB400::HorizontalScan()
{
  DmxSimple.write(startAddr + 1, 155);
  DmxSimple.write(startAddr + 2, 0);
  DmxSimple.write(startAddr + 5, 0);
  DmxSimple.write(startAddr + 6, 0);
  DmxSimple.write(startAddr + 7, 128);
}
void DMRGB400::CrossRotate()
{
  DmxSimple.write(startAddr + 1, 187);
  DmxSimple.write(startAddr + 2, 0);
  DmxSimple.write(startAddr + 5, 128);
  DmxSimple.write(startAddr + 6, 0);
  DmxSimple.write(startAddr + 7, 0);
}
void DMRGB400::Bowtie()
{
  DmxSimple.write(startAddr + 1, 78);
  DmxSimple.write(startAddr + 2, 0);
  DmxSimple.write(startAddr + 5, 0);
  DmxSimple.write(startAddr + 6, 0);
  DmxSimple.write(startAddr + 7, 255);
}
void DMRGB400::Circle()
{
  DmxSimple.write(startAddr + 1, 0);
  DmxSimple.write(startAddr + 2, 208);
  DmxSimple.write(startAddr + 5, 0);
  DmxSimple.write(startAddr + 6, 0);
  DmxSimple.write(startAddr + 7, 0);
}
void DMRGB400::Triangle()
{
  DmxSimple.write(startAddr + 1, 18);
  DmxSimple.write(startAddr + 2, 0);
  DmxSimple.write(startAddr + 5, 128);
  DmxSimple.write(startAddr + 6, 0);
  DmxSimple.write(startAddr + 7, 0);
}
void DMRGB400::BlockyZigZag()
{
  DmxSimple.write(startAddr + 1, 148);
  DmxSimple.write(startAddr + 2, 0);
  DmxSimple.write(startAddr + 5, 128);
  DmxSimple.write(startAddr + 6, 0);
  DmxSimple.write(startAddr + 7, 0);
}

void DMRGB400::Setup()
{
  LaserOnOff(true);
  Color(1);
  Circle();
  delay(400);
  Color(2);
  HorizontalScan();
  delay(400);
  Color(3);
  CrossRotate();
  delay(400);
  Color(4);
  Bowtie();
  delay(400);
  Color(5);
  VerticalScan();
  delay(400);  
  LaserOnOff(false);
}
#pragma endregion DM-RGB400

// ADJ Quad Moving Head
#pragma region ADJQuadMovingHead
QuadMovingHead::QuadMovingHead(int _startAddr, char _side)
{
  startAddr = _startAddr;
  side = _side;
  center = 170;
  if (side = 'R')
  {
    center = 86;
  }
  else if (side = 'L')
  {
    center = 170;
  }
}
void QuadMovingHead::Strobe(bool onOff)
{
  if (onOff)
  {
    Dimmer(255);
    DmxSimple.write(startAddr + 17, 128);
  }
  else
  {
    Dimmer(0);
    DmxSimple.write(startAddr + 17, 12);
  }
}
void QuadMovingHead::Color(int R, int G, int B)
{
  DmxSimple.write(startAddr + 4, R);
  DmxSimple.write(startAddr + 8, R);

  DmxSimple.write(startAddr + 5, G);
  DmxSimple.write(startAddr + 9, G);

  DmxSimple.write(startAddr + 6, B);
  DmxSimple.write(startAddr + 10, B);

}
void QuadMovingHead::Dimmer(int dimLevel)
{
  DmxSimple.write(startAddr + 18, dimLevel);
  //DmxSimple.write(startAddr + 17, 12);
}
void QuadMovingHead::MoveSpeed(bool fastSlow)
{
  if (fastSlow)
  {
    DmxSimple.write(startAddr + 15, 20);
    DmxSimple.write(startAddr + 19, 20);
  }
  else
  {
    DmxSimple.write(startAddr + 15, 255);
    DmxSimple.write(startAddr + 19, 255);
  }  
}
void QuadMovingHead::Front()
{
  DmxSimple.write(startAddr + 14, 0);
  DmxSimple.write(startAddr, center);
  DmxSimple.write(startAddr + 2, 0);
}
void QuadMovingHead::Outward()
{
  DmxSimple.write(startAddr + 14, 0);
  DmxSimple.write(startAddr, center + 30);
  DmxSimple.write(startAddr + 2, 40);
}
void QuadMovingHead::Inward()
{
  DmxSimple.write(startAddr + 14, 0);
  DmxSimple.write(startAddr, center - 30);
  DmxSimple.write(startAddr + 2, 40);
}
void QuadMovingHead::Down()
{
  DmxSimple.write(startAddr + 14, 0);
  DmxSimple.write(startAddr, center);
  DmxSimple.write(startAddr + 2, 127);
}

void QuadMovingHead::MoveMacro()
{
  DmxSimple.write(startAddr + 14, random(16, 255));
}

void QuadMovingHead::Setup()
{
  Dimmer(255);
  Color(255, 0, 0);
  Outward();
  delay(400);
  Color(0, 255, 0);
  Inward();
  delay(400);
  Color(0, 0, 255);
  Front();
  delay(400);
  Color(255, 255, 255);
  Down();
  Strobe(true);
  delay(500);
  Strobe(false);
  Dimmer(0);
  Color(255, 255, 255);
  Front();
}
#pragma endregion ADJQuadMovingHead

// LIXADA Moving Head
#pragma region LIXADAMovingHead
SingleMovingHead::SingleMovingHead(int _startAddr, char _side)
{
  startAddr = _startAddr;
  side = _side;
  center = 86;
  if (side = 'L')
  {
    center = 86;
  }
  else if (side = 'R')
  {
    center = 170;
  }
}

void SingleMovingHead::Strobe(bool onOff)
{
  if (onOff)
  {
    Dimmer(255);
    DmxSimple.write(startAddr + 6, 100);
  }
  else
  {
    Dimmer(0);
    DmxSimple.write(startAddr + 6, 255);
  }
}
void SingleMovingHead::Color(int colorSelect)
{
  DmxSimple.write(startAddr + 5, 20);
  if (colorSelect == 1) //White
  {
    DmxSimple.write(startAddr + 4, 0);
  }
  else if (colorSelect == 2) //Red
  {
    DmxSimple.write(startAddr + 4, 20);
  }
  else if (colorSelect == 3) //Blue
  {
    DmxSimple.write(startAddr + 4, 40);
  }
  else if (colorSelect == 4) //Orange
  {
    DmxSimple.write(startAddr + 4, 60);
  }
  else if (colorSelect == 5) //Blue
  {
    DmxSimple.write(startAddr + 4, 70);
  }
  else if (colorSelect == 6) //Yellow
  {
    DmxSimple.write(startAddr + 4, 90);
  }
  else if (colorSelect == 7) //Green
  {
    DmxSimple.write(startAddr + 4, 100);
  }
  else if (colorSelect == 8) //Magenta
  {
    DmxSimple.write(startAddr + 4, 120);
  }
}
void SingleMovingHead::Dimmer(int dimLevel)
{
  //DmxSimple.write(startAddr + 6, 255);
  DmxSimple.write(startAddr + 7, dimLevel);
}
void SingleMovingHead::MoveSpeed(bool fastSlow)
{
  if (fastSlow)
  {
    DmxSimple.write(startAddr + 8, 0);
  }
  else
  {
    DmxSimple.write(startAddr + 8, 225);
  }  
}
void SingleMovingHead::Front()
{
  DmxSimple.write(startAddr + 9, 0);
  DmxSimple.write(startAddr, center);
  DmxSimple.write(startAddr + 2, 0);
}
void SingleMovingHead::Outward()
{
  DmxSimple.write(startAddr + 9, 0);
  DmxSimple.write(startAddr, center + 30);
  DmxSimple.write(startAddr + 2, 40);
}
void SingleMovingHead::Inward()
{
  DmxSimple.write(startAddr + 9, 0);
  DmxSimple.write(startAddr, center - 30);
  DmxSimple.write(startAddr + 2, 40);
}
void SingleMovingHead::Down()
{
  DmxSimple.write(startAddr + 9, 0);
  DmxSimple.write(startAddr, center);
  DmxSimple.write(startAddr + 2, 127);
}

void SingleMovingHead::MoveMacro()
{
  DmxSimple.write(startAddr + 9, 255);
}

void SingleMovingHead::Setup()
{
  DmxSimple.write(startAddr + 5, 20);
  Strobe(false);
  Dimmer(255);
  Color(0);
  Outward();
  delay(400);
  Color(0);
  Inward();
  delay(400);
  Color(0);
  Front();
  delay(400);
  Color(0);
  Down();
  Strobe(true);
  delay(500);
  Strobe(false);
  Dimmer(0);
  Color(0);
  Front();
}
#pragma endregion LIXADAMovingHead

// SHEHDS Moving Head
#pragma region SHEHDSMovingHead
BeamMovingHead::BeamMovingHead(int _startAddr, char _side)
{
  startAddr = _startAddr;
  side = _side;
  center = 170;
  if (side = 'R')
  {
    center = 86;
  }
  else if (side = 'L')
  {
    center = 170;
  }
}
void BeamMovingHead::Strobe(bool onOff)
{
  if (onOff)
  {
    Dimmer(255);
    DmxSimple.write(startAddr + 6, 255);
  }
  else
  {
    Dimmer(0);
    DmxSimple.write(startAddr + 6, 0);
  }
}
void BeamMovingHead::Color(int R, int G, int B)
{
  DmxSimple.write(startAddr + 7, R);

  DmxSimple.write(startAddr + 8, G);

  DmxSimple.write(startAddr + 9, B);

}
void BeamMovingHead::Dimmer(int dimLevel)
{
  DmxSimple.write(startAddr + 5, dimLevel);
  //DmxSimple.write(startAddr + 17, 12);
}
void BeamMovingHead::MoveSpeed(bool fastSlow)
{
  if (fastSlow)
  {
    DmxSimple.write(startAddr + 4, 20);
  }
  else
  {
    DmxSimple.write(startAddr + 4, 255);
  }  
}
void BeamMovingHead::Front()
{
  DmxSimple.write(startAddr, center);
  DmxSimple.write(startAddr + 2, 0);
}
void BeamMovingHead::Outward()
{
  DmxSimple.write(startAddr, center + 30);
  DmxSimple.write(startAddr + 2, 40);
}
void BeamMovingHead::Inward()
{
  DmxSimple.write(startAddr, center - 30);
  DmxSimple.write(startAddr + 2, 40);
}
void BeamMovingHead::Down()
{
  DmxSimple.write(startAddr, center);
  DmxSimple.write(startAddr + 2, 127);
}

void BeamMovingHead::MoveMacro()
{
  DmxSimple.write(startAddr + 11, random(0, 249));
}

void BeamMovingHead::Setup()
{
  Dimmer(255);
  Color(255, 0, 0);
  Outward();
  delay(400);
  Color(0, 255, 0);
  Inward();
  delay(400);
  Color(0, 0, 255);
  Front();
  delay(400);
  Color(255, 255, 255);
  Down();
  Strobe(true);
  delay(500);
  Strobe(false);
  Dimmer(0);
  Color(255, 255, 255);
  Front();
}
#pragma endregion SHEHDSMovingHead

// RGBFog
#pragma region RGBFog
RGBFog::RGBFog(int _startAddr)
{
  startAddr = _startAddr;
}
void RGBFog::Strobe(bool onOff)
{
  if (onOff)
  {
    //Dimmer(255);
    DmxSimple.write(startAddr + 4, 230);
  }
  else
  {
    //Dimmer(0);
    DmxSimple.write(startAddr + 4, 0);
  }
}
void RGBFog::Fog(bool onOff)
{
  if (onOff)
  {
    DmxSimple.write(startAddr, 250);
  }
  else
  {
    DmxSimple.write(startAddr, 0);
  }
}
void RGBFog::Color(int R, int G, int B)
{
  DmxSimple.write(startAddr + 1, R);
  DmxSimple.write(startAddr + 2, G);
  DmxSimple.write(startAddr + 3, B);
}
void RGBFog::Dimmer(int dimLevel)
{
  //DmxSimple.write(startAddr, dimLevel);
}

void RGBFog::Setup()
{
  Color(255, 0, 0);
  delay(400);
  Color(0, 255, 0);
  delay(400);
  Color(0, 0, 255);
  delay(400);
  Color(255, 255, 255);
  Strobe(true);
  delay(500);
  Strobe(false);
  Color(0, 0, 0);
}
#pragma endregion RGBFog
