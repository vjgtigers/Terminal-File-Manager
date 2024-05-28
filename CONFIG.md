# Creating a config

1. Download the TFV_config_template.txt or use the initConfig command in the program to generate a config file
2. Rename to TFV_config.txt and put in same folder as executable
3. Use this [AsciiTable](https://www.asciitable.com/) to help find the ascii codes you want to use
4. replace the ascii codes in the text file with your own

* there are more that I haven't added to this table but can be found in the config file

| Name               | Function                                                                |
|--------------------|-------------------------------------------------------------------------|
| rc-vd              | vertical divisor, default (179)                                         |
| rc-hd              | horizontal divisor, default (196)                                       |
| rc-tc              | combine horizontal divisor with <br> vertical underneath, default (194) |
| rc-bc              | combine horizontal divisor with <br> vertical on top, default (193)     |
| rc-ac              | combine all sides, default (197)                                        |
| rc-pt              | pointer, default (62)                                                   |
| rc-cl              | left part of the cursor for the cmd line, default (217)                 |
| rc-cr              | right part of the cursor for the cmd line, default (192)                |
| nameV              | size of area to display file name (file name)                           |
| extentionV         | 1 or 0 for active and size (file extension)                             |
| sizeV              | 1 or 0 for active and size (file size)                                  |
| modV               | 1 or 0 for active and size (modified date)                              |
| createV            | 1 or 0 for active and size (creation date)                              |
| kc-up              | up key                                                                  |
| kc-down            | down key                                                                |
| kc-quit            | quit key                                                                |
| kc-refresh         | regular refresh key                                                     |
| kc-maintainRefresh | <try to avoid using>                                                    |
| kc-clear           | clear                                                                   |
| kc-enterFolder     | enter folder on current cursor                                          |
| kc-enterPar        | enter parent folder                                                     |

5. save and restart app



* advanced commands
* these generally should be avoided

| Name      | Function                                                   |
|-----------|------------------------------------------------------------|
| ac-debug  | debug mode                                                 |
| ac-config | ON to disable config (read template for more info)         |
| ac-sdd    | display debug info on screen(might break prod builds)      |
| ac-dss    | default mode for file search(regular) Planned: fuzzy/regex |