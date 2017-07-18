Intelbacklight
================

A small tool that mimics xbacklight for intel_backlight.

# Usage

```
./intelbacklight 
Usage: ./intelbacklight {-get|-set NUM|-inc NUM|-dec NUM}
```

# Setup

Compile with gcc

```
gcc intelbacklight.c -o intelbacklight 
```

You might want to set the uid bit or run it with sudo rights.