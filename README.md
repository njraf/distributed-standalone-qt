# Purpose
This project to to demonstrate that it is possible to build an application that is both distributed and standalone. In addition, it will demonstrate that it is possible to create a single project that combines UI elements from each project and run each of them.

# Architecture
## MVVM
Each application will leverage MVVM architecture to make it easy to swap out components. This will be most important when making an application that is both standalone and follows a client-server model.

## Remote objects
The client-server part of a subproject will use Qt Remote Objects to communicate between them.

## CMake components
CMake allows projects to be broken up into components. This allows other projects to use just part of a project as a dependency, which keeps the size of the project smaller than it otherwise would be. Subprojects will expose .ui and .rep files to the `combined` project that will combine the UI and operation of all subprojects.
