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
