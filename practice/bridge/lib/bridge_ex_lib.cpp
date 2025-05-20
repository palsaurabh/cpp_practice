#include <iostream>
#include <string>
#include <cmath>
#include "bridge_ex.hpp"
/**
 * Bridge Design Pattern
 * */

void Device::togglePower()
{
    if (pwr == Device::Power::OFF)
    {
        pwr = Device::Power::ON;
    }
    else
    {
        pwr = Device::Power::OFF;
    }
}

void Device::setAudio(const int val)
{
    if (val <= AUDIO_MAX)
        audio = val;
}

int Device::getAudio()
{
    return audio;
}

Device::Power Device::getPower()
{
    return pwr;
}

void Device::setChannel(const int val)
{
    if (val <= CHANNEL_MAX)
        channelNumber = val;
}

int Device::getChannel()
{
    return channelNumber;
}

void Remote::powerButton()
{
    device.togglePower();
}

void Remote::incrementAudio()
{
    auto currAudio = device.getAudio();
    currAudio += 1;
    device.setAudio(currAudio);
}

void Remote::decrementAudio()
{
    auto currAudio = device.getAudio();
    currAudio -= 1;
    device.setAudio(currAudio);
}

void Remote::incrementChannel()
{
    auto currChannel = device.getChannel();
    currChannel += 1;
    device.setChannel(currChannel);
}
void Remote::decrementChannel()
{
    auto currChannel = device.getChannel();
    currChannel -= 1;
    device.setChannel(currChannel);
}

void TV::setBrightness(const int val)
{
    auto currBrightness = getBrightness();
    currBrightness += 1;
    setBrightness(currBrightness);
}

int TV::getBrightness()
{
    return brightness;
}

void advRemote::mute()
{
    device.setAudio(0);
}