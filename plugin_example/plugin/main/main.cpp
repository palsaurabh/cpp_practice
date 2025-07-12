#include "plugin_interface.hpp"
#include <iostream>
#include <dlfcn.h>

int main() {
    void *plugin_handle = dlopen("./libplugin1_lib.so", RTLD_LAZY);
    if (!plugin_handle) {
        std::cerr << "Failed to load plugin: " << dlerror() << std::endl;
        return 1;
    }

    // Clear any existing errors
    dlerror();

    // Load the factory function
    using CreatePluginFunc = Plugin_Interface* (*)();
    CreatePluginFunc create_plugin = (CreatePluginFunc)dlsym(plugin_handle, "create_plugin");
    using DestroyPluginFunc = void (*)(Plugin_Interface*);
    DestroyPluginFunc destroy_plugin = (DestroyPluginFunc)dlsym(plugin_handle, "destroy_plugin");
    
    const char *error = dlerror();
    if (error) {
        std::cerr << "Failed to load symbols: " << error << std::endl;
        dlclose(plugin_handle);
        return 1;  
    }
    
    // Create a plugin instance
    Plugin_Interface* plugin = create_plugin();
    if (!plugin) {
        std::cerr << "Failed to create plugin instance." << std::endl;
        dlclose(plugin_handle);
        return 1;
    }
    // Initialize the plugin
    plugin->initialize();
    // Execute the plugin functionality
    plugin->execute();
    // Shutdown the plugin
    plugin->shutdown();
    // Destroy the plugin instance
    destroy_plugin(plugin);
    // Close the plugin handle
    dlclose(plugin_handle);
    return 0;
}