# shellcodeloaders

# QueueUserAPC Shellcode Loader

Inspired by Challenge 11 of #flareon7 (https://www.fireeye.com/blog/threat-research/2020/08/announcing-the-seventh-annual-flare-on-challenge.html)

Syntax: `queuserapc.exe [shellcode_binary_file]`


```sh
C:\Users\zin1x\source\repos\eleven\Debug+>queueserapc.exe calcshell.bin

#########################################
# Shellcode Launcher using QueueUserAPC #
#########################################
[-] 195 bytes read
[-] Shellcode loaded to: 006D0000
[-] Pls attach your debugger to: queuserapc.exe
[-] Set Breakpoint at : 006D0000

Press Any Key to Continue
```
