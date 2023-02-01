# utf_analysis

A simple C++ program to print names of Unicode characters from input.

## Dependencies
ICU 72.0+ installed on pkg-config.
(On Linux, you can probably find this in your package manager -
search for `icu` with `-dev` or `-devel` at the end.)

## Build
Configure with `cmake . -B _build`

Build with `cmake --build _build` (optionally add `-j X` where X is number of CPU threads to run with)

## Run
Execute `./_build/utf_analysis`

## License
This project is licensed under GPL-2.0 or later.