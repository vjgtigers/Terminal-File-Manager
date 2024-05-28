# Terminal File Manager for Windows
**More features coming soon**

Navigate your computer faster than the basic "dir" and "cd" <br>
With this fast, customizable, and lightweight file browser for your terminal

![SfrQW.gif](https://s12.gifyu.com/images/SfrQW.gif) <br>
example on how to move through folders and open neovim directly from within the program!
<br>
# Config
check out the customizable options! <br>
see [CONFIG.MD](CONFIG.md) for more in depth and TFV_config_template.txt for an example config

# Road Map
## Short Term
* file management ability's (**Top Priority**)
    * copy
    * paste
    * delete folder
* view file permissions
* "onboarding process"
* Colors
* Git explorer (tentative)
* encryption symmetrical/asymmetrical 
* Live Search  - Work In Progress
* file compression
## Longer term
* Linux Support

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
| initConfig             | create config file with defaults. to override pass --override           |
| debug                  | read debug help page for this commands functionality                    |
| del                    | delete file - read help page for detailed functionality                 |
| rm                     | delete empty folder                                                     |



1. For the most part functions like windows cd except for some edge cases
2. No error message on fail and also fails if dir already present

# Other
## Contributing
View [CONTRIBUTING.md](CONTRIBUTING.md) <br>
This is a cmake project, so it can be built that way
If you use CLion drop the src and CMakeLists.txt into the main dir
and drop the helpInfo into the debug folder or where the project is built
