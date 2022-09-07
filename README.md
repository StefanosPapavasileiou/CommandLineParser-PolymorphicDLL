# CommandLineParser-PolymorphicDLL
2


Edit a txt file in a user given path, parse file as either decimal or hexadecimal numbers and modify the file's content, with inputs from command line using a dynamic link library using Polymorphism in C++. Only using the standard language features STL (No third party libraries-Boost is used).

3

This polymorphic parser can work on both Windows and Linux OS.

## Descritpion

`CommandLineParser` runs in command line. It takes as user defined arguments : `-f` the path to a txt file with random numbers or symbols, `-format` whether user prefers decimal or hex notation, `-discarded` whether user wants discarded content to be printed first (optional), `-sort` use of different sorting algorithm for data (optional) and finally `-line` whether user wants line number first and content after.

As stated, this application takes parameters from the command line parse's a txt file as inclined by the user (dec/hex format), discards unwanted data and sorts the numbers in file printing out the sequence and the number of line which the number appears on.
 
It also prints the list of files in the given directory.

## Documentation and Quickstart

Concept behind this project is the dynamic linking of a library (dll) to an application (in this project called TestApp) so that no further compilation of the application's solution is needed after some changes are being done on the library's script (in this project called string_lib).

You are invited to check documentation at https://docs.microsoft.com/en-us/cpp/build/dlls-in-visual-cpp?view=msvc-170 about how to set and compile a project in Visual Studio as a dynamic-link library and how to connect this script to a main application solution. 

## Installation 

After cloning this repository to your machine : 

    - Compile TestApp using Debugg x64 architecture on Visual Studio.
    - Go to the scripts path ../TestApp/x64/Debug.
    - Open terminal in this directory and run the TestApp.exe with your inputs.

```bash
TestApp.exe -f C:\dev\vs2017\src\TestApp - format dec -discard last -line first
```  

![sdda](https://user-images.githubusercontent.com/44292683/188904760-02cc9ddf-0744-4ff8-a038-57fd73d7675e.PNG)

This command takes a txt file located in C:\dev\vs2017\src\TestApp and parses it with decimal notation sorting all numbers in ascending order (by default) printing line of content first. 
