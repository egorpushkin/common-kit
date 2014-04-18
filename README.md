# Common Kit

## Overview
CommonKit project is driven by the idea of simplifying the development of portable, 
fast and reliable applications in C++. It provides the implementation of the following components:
* smart pointers with internal and external reference counting schemes (based on Loki library);
* events dispatching;
* undo/redo automation;
* concurrency mechanisms;
* transparent support for scalability (smart shared objects loader);
* high-level network interaction (based on boost::asio) and 
* support for distributed systems design and implementation ("Remoting" component).

Supported platforms:
* Windows
* MacOS
* iOS

Dependencies:
* Boost libraries. 
  You have to download Boost (http://www.boost.org/) and configure your IDE and projects to point to correct location of Boost source code. Note that you do not need to build Boost from its source code. 
  CommonKit bases only on header libraries from Boost package.  
* Loki library.

## Copyright

CommonKit is released under GNU Lesser General Public License (see LICENSE file).	
Few additional requirements are applied (see LICENSEA file).
