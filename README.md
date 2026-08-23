# Purpose
This project to to demonstrate that it is possible to build an application that is both distributed and standalone. In addition, it will demonstrate that it is possible to create a single project that combines UI elements from each project and run each of them.

# Architecture
## MVVM
Each application will leverage MVVM architecture to make it easy to swap out components. This will be most important when making an application that is both standalone and follows a client-server model.

## Remote objects
The client-server part of a subproject will use Qt Remote Objects to communicate between them.

## CMake components (TODO)
CMake allows projects to be broken up into components. This allows other projects to use just part of a project as a dependency, which keeps the size of the project smaller than it otherwise would be. Subprojects will expose .ui and .rep files to the `combined` project that will combine the UI and operation of all subprojects.

## Dependency graph
The processlauncher sits at the top of the dependency hierarchy. This provides two remote objects that other projects can create replicas for: AppService and ControllerService/ControllerCommunicator. A project with its own MainWindow, such as counter, will then use the process launcher as a dependency to obtain a replica of the ControllerService. This replica is used to tell the controller of an application to shutdown and perform various tasks. The bottom of the dependency hierarchy is the combined project. This depends on the processlauncher and any other project with a MainWindow. The subprojects are used to retrieve a replica to communicate with the controller of the application and to provide the UI for a given project. The processlauncher is used to retrieve a replica to command the processlauncher to start and stop an application.

processlauncher---->counter and other standalone applications
  |                  |
  |                  v
  ----------------->combined
NOTE: pointers are dependencies of projects being pointed to

# Subprojects
## Counter
This is a standalone application that increments a counter when a button is clicked. It can also be run in client/server mode using remote objects.

## Combined
This project takes the .ui files and ProxyControllers of other subprojects to create a MainWindow that can display UI from multiple applications. It is also that client-side of each application and communicates with the processlauncher to start the server-side of each application.

## Processlauncher
This is the server side of the Combined project and can be run as a daemon. It will receive requests from the Combined project to start and stop the server-side of other subprojects like counter.
