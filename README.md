# Conway-Game-of-Life

Conway's game of life using SDL and CMake.

Run using
```
cmake .
```
And then
```
make
```
```
./conway
```

things to add:
- better file parser
-- dunno why it seg faults, but it does
-- make a file parser for rle (seems to be the standard)

- seperate render and game updates
-- higher fps without ridiculously fast game speed

- multithreading
-- support faster grid
-- seperate render and update

- better grid lines
-- grid lines do not show at higher resolution
-- also add a better border, rn the grey looks ugly.

- higher resolution
-- not sure how, my screen should be able to support more pixels than the window displays though

- bug fixes
-- not sure why but there's some issues with big tests filled with data (10000x10000 random)

- optimization
-- 10000x10000 drops to 1 fps on empty grid, that's frankly trash
