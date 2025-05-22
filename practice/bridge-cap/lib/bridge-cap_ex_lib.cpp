#include <iostream>
#include <string>
#include <cmath>
#include "bridge-cap_ex.hpp"
/**
 * Bridge Design Pattern
 * */

void Device::togglePower()
{
    std::cout<<__func__<<"\n";

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
    std::cout<<__func__<<"\n";

    if (val <= AUDIO_MAX)
        audio = val;
}

int Device::getAudio()
{
    std::cout<<__func__<<"\n";

    return audio;
}

Device::Power Device::getPower()
{
    std::cout<<__func__<<"\n";

    return pwr;
}

void Device::setChannel(const int val)
{
    std::cout<<__func__<<"\n";

    if (val <= CHANNEL_MAX)
        channelNumber = val;
}

int Device::getChannel()
{
    std::cout<<__func__<<"\n";

    return channelNumber;
}

void Remote::powerButton()
{
    std::cout<<__func__<<"\n";

    device.togglePower();
}

void Remote::incrementAudio()
{
    std::cout<<__func__<<"\n";

    auto currAudio = device.getAudio();
    currAudio += 1;
    device.setAudio(currAudio);
}

void Remote::decrementAudio()
{
    std::cout<<__func__<<"\n";

    auto currAudio = device.getAudio();
    currAudio -= 1;
    device.setAudio(currAudio);
}

void Remote::incrementChannel()
{
    std::cout<<__func__<<"\n";

    auto currChannel = device.getChannel();
    currChannel += 1;
    device.setChannel(currChannel);
}
void Remote::decrementChannel()
{
    std::cout<<__func__<<"\n";

    auto currChannel = device.getChannel();
    currChannel -= 1;
    device.setChannel(currChannel);
}

void TV::setBrightness(const int val)
{
    std::cout<<__func__<<"\n";
    brightness = val;
}

int TV::getBrightness()
{
    std::cout<<__func__<<"\n";

    return brightness;
}

void advRemote::mute()
{
    std::cout<<"Muting the Device\n";
    device.setAudio(0);
}

void advRemote::incrementBrightness()
{
    std::cout<<__func__<<"\n";
    try
    {
        std::cout<<"Try Block "<<__func__<<"\n";
        Brightness &tv = dynamic_cast<Brightness&> (device);    
        auto currBrightness = tv.getBrightness();
        currBrightness += 1;
        tv.setBrightness(currBrightness);
    }
    catch (const std::bad_cast &e)
    {
        std::cout<<"Catch Block "<<__func__<<"\n";
        std::cerr << "Cast failed: Device Doesn't Support Adjusting Brightness\n" << e.what() << std::endl;
    }
}

void advRemote::decrementBrightness()
{
    std::cout<<__func__<<"\n";
    try
    {
        std::cout<<"Try Block "<<__func__<<"\n";
        Brightness &tv = dynamic_cast<Brightness&> (device);    
        auto currBrightness = tv.getBrightness();
        currBrightness -= 1;
        tv.setBrightness(currBrightness);
    }
    catch (const std::bad_cast &e)
    {
        std::cout<<"Catch Block "<<__func__<<"\n";
        std::cerr << "Cast failed: " << e.what() << std::endl;
    }
}
