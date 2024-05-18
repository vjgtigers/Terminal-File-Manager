# Terminal File Browser for Windows
THIS PROGRAM IS NOT READY FOR GENERAL USE

Navigate your computer faster than the basic "dir" and "cd" <br>
This project aims to be a fast, customizable, and lightweight file browser for your terminal


# Road Map
## After the basic file browsing functionality is fully implemented
* ~~customize key press bindings~~
* file management ability's (**Top Priority**)
* view file permissions
* "onboarding process"
* Colors
* Git explorer (tentative)
* encryption symmetrical/asymmetrical 
* Live Search
* ~~Vim/NeoVim like bindings~~
* file compression

# Usage 
| Key Presses | Description           |
|-------------|-----------------------|
| a           | go to parent dir      |
| s           | enter selected dir    |
| h           | down          |
| t           | up            |
| :           | activate command line |
| q           | exit program          |


# Command Line (Work in Progress)
**To activate the command line press ":"** <br>
You will then be able to start typing at the bottom of the screen


| Commands               | Description                                                             |
|------------------------|-------------------------------------------------------------------------|
| cd<sup>1</sup>         | change directory like windows cd                                        |
| help                   | type help then command to get command info                              |
| nvim                   | launch neovim with selected file if non is provided                     |
| mkdir<sup>2</sup>      | create folder in current folder                                         |
| refreshConfig          | reload config settings                                                  |
| setConfigOption (sco)  | modify config option and write it to file                               |
| testConfigOption (tco) | modify config without saving.<br> settings will be lost on program exit |
| mkf                    | create file                                                             |

1. For the most part functions like windows cd except for some edge cases
2. No error message on fail and also fails if dir already present
# Config
allows the ability to customize aspects of the program <br>
see CONFIG.MD for more in depth and TFV_config_template.txt for an example config

# Other
## Contributing
View CONTRIBUTING.md <br>
This is a cmake project, so it can be built that way
If you use CLion drop the src and CMakeLists.txt into the main dir
and drop the helpInfo into the debug folder or where the project is built
