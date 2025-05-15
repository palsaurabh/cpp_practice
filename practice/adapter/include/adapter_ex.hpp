#include <iostream>
#include <string>
#include <mutex>
/**
 * Adapter design pattern:
 * Adapter design pattern is used whenever we need to interoperate between two incompatible 
 * interfaces. 
 * For example, let us say, you have some code, that receives stock market data in xml format,
 * processess it and creates nice representations, charts etc. Now, after some time, we want to 
 * integrate a new library which does better data-analytics. But the catch is that the new 
 * library doesn't work with xml files and needs Json format for processing.
 * 
 * In this case, we can use adapter design pattern to adapt one interface to another.
 * We can create a new adapter class which follows the same interface as our old xml processing 
 * library and then also wraps an object of the new library.
 * 
 * The existing code calls the client interface, but internally the client interface coverts
 * the data to json and invokes the methods of the wrapped object. 
 * 
 * This way, the client code remains unaffected by the new library code. It doesn't have to get 
 * coupled with the new library and multiple adapters can be written for each different library
 * without affecting the client code.
 * 
 * Many times, it is possible that we dont have the source code or the class structure for the 
 * third party library, then, we wrap the library object in the adapter class.
 * 
 * Whereas, sometime when we have the interface details, we can have the adapter inherit from
 * both the client and the new library.
 *  */

