#ifndef RGB_DMX_H
#define RGB_DMX_H

// EXTERNAL LIBRARIES
#include <DmxSimple.h>

#include "rgb_main.h"

void DMX_Blackout();

// SlimPAR 56
class SlimPAR56
{
  public:
    SlimPAR56(int _startAddr);

    void Strobe(bool onOff);
    void Color(int R, int G, int B);
    void Dimmer(int dimLevel);

    void Setup();
  private:
    int startAddr;
};

// DM-RGB400
class DMRGB400
{
  public:
    DMRGB400(int _startAddr);

    void LaserOnOff(bool onOff);
    void Color(int colorSelect);
    void VerticalScan();
    void HorizontalScan();
    void CrossRotate();
    void Bowtie();
    void Circle();
    void Triangle();
    void BlockyZigZag();

    void Setup();
  private:
    int startAddr;
};

// ADJ Quad Moving Head
class QuadMovingHead
{
  public:
    QuadMovingHead(int _startAddr, char _side);

    void Strobe(bool onOff);
    void Color(int R, int G, int B);
    void Dimmer(int dimLevel);
    void MoveSpeed(bool fastSlow);
    void Front();
    void Outward();
    void Inward();
    void Down();

    void MoveMacro();
    
    void Setup();
  private:
    int startAddr;
    char side;
    int center;
};

// LIXADA Moving Head
class SingleMovingHead
{
  public:
    SingleMovingHead(int _startAddr, char _side);

    void Strobe(bool onOff);
    void Color(int colorSelect);
    void Dimmer(int dimLevel);
    void MoveSpeed(bool fastSlow);
    void Front();
    void Outward();
    void Inward();
    void Down();

    void MoveMacro();
    
    void Setup();
  private:
    int startAddr;
    char side;
    int center;
};

// Mini Kinta IRC
class MiniKinta
{
  public:
    MiniKinta(int _startAddr);

    void Strobe(bool onOff);
    void Color(int R, int G, int B);
    void Dimmer(int dimLevel);

    void Setup();
  private:
    int startAddr;
};

//Shehds Beam
class BeamMovingHead
{
  public:
    BeamMovingHead(int _startAddr, char _side);

    void Strobe(bool onOff);
    void Color(int R, int G, int B);
    void Dimmer(int dimLevel);
    void MoveSpeed(bool fastSlow);
    void Front();
    void Outward();
    void Inward();
    void Down();

    void MoveMacro();
    
    void Setup();
  private:
    int startAddr;
    char side;
    int center;
};

//RGB Fog
class RGBFog
{
  public:
    RGBFog(int _startAddr);

    void Strobe(bool onOff);
    void Color(int R, int G, int B);
    void Dimmer(int dimLevel);
    void Fog(bool onOff);

    void Setup();
  private:
    int startAddr;
};

#endif
