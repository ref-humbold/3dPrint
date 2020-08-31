# GCode Reader
GCode instructions sender to STM32F411 Nucleo board

-----

## GCode commands

`G0 Xx Yy` - move laser to point `(x, y)`
`G1 Xx Yy` - draw line to point `(x, y)`
`G2 Xx Yy Rr` - draw arc with radius `r` clockwise to point `(x, y)`
`G3 Xx Yy Rr` - draw arc with radius `r` counterclockwise to point `(x, y)`

For `G2` and `G3`:
+ when `r` is positive, then move along shorter arc
+ when `r` is negative, then move along longer arc
