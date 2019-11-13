# ChickenHook - StaticInjector

## Intrudiction

The StaticInjector is build for injecting code into an already compiled binary (shared object or executable).

This injected code can use ChickenHook (https://github.com/ChickenHook/ChickenHook) for hook some functions to manipulate the behaviour at runtime.

## How it works

## Build

### Linux
```
ant configure-linux compile-linux test-linux install-linux
```

### Android
WIP


## Build your own attack

This chapter explains how to use StaticInjector for your needs.

### Linux

```
./staticInjector [binaryToInjectInto] [dependency to replace] [path to dependency to generate the stubs]
```


Example:

```
./staticInjector victimTest libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
```
WIP


### Android
WIP


### Example attacks

# Firefox

Check this video (Please enable subtitles):

[![](http://img.youtube.com/vi/_4K2d7FFHqo/0.jpg)](http://www.youtube.com/watch?v=_4K2d7FFHqo "Linux attack firefox")

# Skype


Check this video (Please enable subtitles):

[![](doc/skypeAttack.gif)](http://www.youtube.com/watch?v=kbrenIx8OrI "How to hack Skype on Linux")

http://img.youtube.com/vi/kbrenIx8OrI/0.jpg

Read more in our wiki:
[How to create a linux attack (skype example)](https://github.com/ChickenHook/StaticInjector/wiki/How-to-create-a-linux-attack-(step-by-step-guide) "How to create a linux attack (step by step guide)")


# Feel free to get a part of ChickenHook!