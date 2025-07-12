#pragma once

class Plugin_Interface {
    public:
        virtual ~Plugin_Interface() = default;

        // Initialize the plugin
        virtual void initialize() = 0;

        // Execute the plugin functionality
        virtual void execute() = 0;

        // Shutdown the plugin
        virtual void shutdown() = 0;
};

extern "C" {
    // Factory function to create a plugin instance
    Plugin_Interface* create_plugin();
    
    // Factory function to destroy a plugin instance
    void destroy_plugin(Plugin_Interface* plugin);
}