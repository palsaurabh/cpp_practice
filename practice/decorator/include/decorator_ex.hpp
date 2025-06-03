#include <iostream>
#include <string>
#include <mutex>
#include <vector>
/**
 * Decorator is a design pattern that lets us add new functionalities on objects by 
 * wrapping them inside another decorator object. The decorator object also follows
 * the common interface that is follwed by the original object. The decorator design 
 * pattern is same as composite as both work in the same way in recursive way. Only 
 * difference between the two is that composite contains multiple components, which
 * may be composite components or a simple leaf component. Whereas in decorator,
 * there is only one element aggregated.
 * 
 * We will take an example of a notifier. Where, some events are notified to the
 * customer via email or facebook or slack etc.  
 * */

class Notifier
{
    public:
        virtual void notify() = 0;
};

class NotifierDecorator : public Notifier
{
    private:
        Notifier *wrappedNotifier;
    public:
        NotifierDecorator(Notifier *wrappee):wrappedNotifier{wrappee}{}
        void notify()
        {
            wrappedNotifier->notify();
        }
};

class BasicNotifier : public Notifier
{
    void notify()
    {
        std::cout<<"Basic Notification\n";
    }

};

class FacebookNotifier : public NotifierDecorator
{
    private:
    public:
    FacebookNotifier(Notifier *wrappee):NotifierDecorator{wrappee}{}
    void notify()
    {
        std::cout<<"Notifying over Facebook\n";
        NotifierDecorator::notify();    
    }
};

class WhatsappNotifier : public NotifierDecorator
{
    private:
    public:
    WhatsappNotifier(Notifier *wrappee):NotifierDecorator{wrappee}{}
    void notify()
    {
        std::cout<<"Notifying over Whatsapp\n";
        NotifierDecorator::notify();    
    }
};