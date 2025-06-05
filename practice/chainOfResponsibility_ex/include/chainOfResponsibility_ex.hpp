#include <iostream>
#include <string>
#include <mutex>
#include <vector>
/**
 * Chain of responsibility (CoR) is a design pattern where each element has 
 * a responsibility to perform a taks and then  forward the task for further
 * processing if needed. For example, in case of call-center, there is an IVRS 
 * system that does some verification and filtering and then if needed forwards
 * to a customer representative. The customer representative may also if required
 * forwards the reuest to someone else down the line who is more adept as solving
 * a particular type of problem. 
 * Similarly, in an app, a request may pass through a lot of stages before being 
 * accepted. For ex. a request may have to be verified for access, accesstype, IP
 * checking, caching etc..
 * So at each step there has to be a handler which handles the request and passes
 * it on, based on the need. This is implemented by using a handler interface which
 * generally defines interfaces
* */

/**
 * Here we will implement a simple generic implementation.
 */
class IHandler
{
    public:
        virtual ~IHandler(){}
        virtual void handle(std::string) = 0;
        virtual IHandler *setNext(IHandler *nxtHandler) = 0;
};

/*Abstract Handler implements a basic or default functionality*/
class AbstractHandler: public IHandler
{
    protected:
        IHandler *nexthandler{nullptr};
    public:
        void handle(std::string str);

        IHandler *setNext(IHandler *nxthandler);
};

/*Concrete Handlers*/
class DogHandler : public AbstractHandler
{
    void handle(std::string str);
};

class HorseHandler : public AbstractHandler
{
    void handle(std::string str);
};

class CatHandler : public AbstractHandler
{
    void handle(std::string str);
};