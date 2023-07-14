# BUILDING THE PROJECT
<pre>
  #IF (WINDOWS)
  
    OPTION 1 - If you have mingw-g++ in your path you can just run "build.bat" file -> This file should be always updated.
    
    OPTION 2 - Just run the "build-cmake.bat" if you have CMAKE installed and if you are using *MinGW*
    
    OPTION 3 - *If you have CMAKE and also a compiler you can build the project with CMAKE but you should specify the "GENERATOR" option according to your compiler
               *For example, lets say you are in the same dir with CMakeLists.txt -> cmake . -G "MinGW Makefiles" -> "cmake --help" for other GENERATOR options
                                                                                    
               *If you don't specify the GENERATOR option CMAKE is going to create Visual Studio Solution probably
               
               **NOTE : Check your mingw/bin folder ,
                        *If you are seeing the "make.exe" you can call the "make" command
                        
                        *If you are *not* seeing the "make.exe" you are probably seeing a file like "mingw32-make.exe" -> Rename that as "make.exe"
                        
   #IF (UNIX)

      OPTION 1 - Just run the "cmake ." and then "make" in your terminal
      OPTION 2 - Open your terminal and type "chmod +x build.sh" then type "./build.sh"
</pre>

# TO-DO
- [ ] REFACTOR(delete virtual functions, use glm)
- [ ] CMAKE compilation(there are some issues)
- [X] Memory handling with unique_ptr
- [X] Sphere to Sphere Collision Handling
- [X] Base Class -> "Object"
- [X] Sphere class
- [X] TEST Sphere to Sphere collision
- [x] User Input
- [X] Add WALLS
- [X] Sphere to sphere collision handling
- [ ] Modify Box class
- [ ] Sphere to Box Collision Handling
- [X] Object Factory
- [ ] Rotation
- [ ] Friction
- [ ] Separation of nested spawned objects
- [X] Rendering
- [ ] Better collision check algorithm