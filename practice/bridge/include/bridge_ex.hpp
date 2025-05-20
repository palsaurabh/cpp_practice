#include <iostream>
#include <string>
#include <mutex>
/**
 * Bridge Pattern is used to divide complex classes into abstraction and implementation
 * It allows to divide complex classes or related classes into abstraction and 
 * implementation. Bothe abstraction and implementation can be further developed into
 * separate hierachies and developed separately. In the book GOF, they take example of
 * HMI and implementation. For eg. the HMI class for an application which has a frontend
 * for controlling the application and a backend which deals with the platform APIs. Platforms
 * can be of different types like MAC, Linux, Windows etc. The frontend can be also different
 * for each platform type. 
 * After this division we can have two interfaces one for each, defining or declaring the methods
 * which need to be implemented for each concrete subclass for each type of interface and 
 * implementation.
 * Another example can be thought of is about TVs/Radios and remotes. Now here remote can be thought of
 * as abstraction and TV as an implementation. There can be different types of remotes with varied
 * functionalities ranging from simple two button remotes for on/off to multiple functionalities.
 * What is the advantage for client. The client can choose any remote with any TV/Radio.
 * */

class Device
{
    protected:
        enum class Power
        {
            OFF = 0,
            ON = 1,
        };
        static constexpr int AUDIO_MAX{999};
        static constexpr int CHANNEL_MAX{999};
    private:
        int audio{0};
        int channelNumber{0};
        Power pwr{Device::Power::OFF};
    public:
        virtual void togglePower();
        virtual void setAudio(const int val);
        virtual int getAudio();
        virtual Power getPower();
        virtual void setChannel(const int val);
        virtual int getChannel();
};
class Remote
{   
    protected:
        Device &device;
    public:
        Remote(Device &device):device{device}{}
        virtual void powerButton();
        virtual void incrementAudio();
        virtual void decrementAudio();
        virtual void incrementChannel();
        virtual void decrementChannel();
};

class TV : public Device
{
    public:
        void setBrightness(const int val);
        int getBrightness();
        static constexpr int MAX_BRIGHTNESS{100};
    private:
        int brightness{20};
};

class Radio : public Device
{

};

class simpleRemote: Remote
{
    public:
        simpleRemote(Device &dev):Remote(dev){}
};

class advRemote: Remote
{
    public:
        advRemote(Device &dev):Remote(dev){}
        void mute();      
};