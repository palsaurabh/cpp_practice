#include "plugin_interface.hpp"
#include <iostream>

class Plugin1 : public Plugin_Interface {
    public:
        void initialize() override {
            std::cout<<"Initializing Plugin1..."<<std::endl;
        }

        void execute() override {
            std::cout<<"Executing the functionality of plugin1..."<<std::endl;
        }

        void shutdown() override {
            std::cout<<"Shutting down Plugin1..."<<std::endl;
        }
};

extern "C" {
    Plugin_Interface* create_plugin() {
        return new Plugin1();
    }

    void destroy_plugin(Plugin_Interface* plugin) {
        delete plugin;
    }
}