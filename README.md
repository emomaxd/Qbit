# BUILDING THE PROJECT
<pre>
  #IF (WINDOWS)
  
    OPTION 1 - If you have mingw-g++ in your path you can just run "build.bat" file -> This file should be always updated.
    
    OPTION 2 - *If you have CMAKE and also a compiler you can build the project with CMAKE but you should specify the "GENERATOR" option according to your compiler
               *For example, lets say you are in the same dir with CMakeLists.txt -> cmake . -G "MinGW Makefiles" -> "cmake --help" for other GENERATOR options
                                                                                     cmake . -G "MSYS Makefiles"
               *If you don't specify the GENERATOR option CMAKE is going to create Visual Studio Solution
               
               **NOTE : Check your mingw/bin folder ,
                        *If you are seeing the "make.exe" you can call the "make" command
                        
                        *I have downloaded "g++" from MSYS and the second NOTE happened to me. Be careful!
                          *If you are *not* seeing the "make.exe" you are probably seeing a file like "mingw32-make.exe" -> Rename that as "make.exe"
                        
   #IF (UNIX)
   
      Just run the "cmake ." and then "make"
<pre/>