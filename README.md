## Overview
Pattern to construct registry in run-time and compile-time

## How
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$
$ # Test registry constructed in runtime
$ ./registry-runtime/registry-runtime
$ Something is = 10
$
$ # Test registry constructed in compile time
$ ./registry-compiletime/registry-compiletime
$ registry size = 3
$ ===================
$ val = 2 | key = C
$ val = 1 | key = B
$ val = 0 | key = A
$
$ Call from A constructor: 
$ Key = A| Val = 0
$ Call from B constructor: 
$ Key = B| Val = 1
$ Call from C constructor: 
$ Key = C| Val = 2
