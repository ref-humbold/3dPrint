# GCode Reader
GCode instructions sender to STM32F411 Nucleo board

-----

## GCode commands

`G0 Xx Yy` - move laser to point `(x, y)`
`G1 Xx Yy` - draw line to point `(x, y)`
`G2 Xx Yy Rr` - draw circle with radius `r` clockwise to point `(x, y)`
`G3 Xx Yy Rr` - draw circle with radius `r` counterclockwise to point `(x, y)`


-----

## Connection schema

1. GCodeReader ---- *Connect* ---------------------> PrinterCtrl
2. GCodeReader <--------------------- *Connect* ---- PrinterCtrl
3. GCodeReader <---------------- *DataExpected* ---- PrinterCtrl
4. GCodeReader ---- *BeginTransmit* ---------------> PrinterCtrl
5. GCodeReader ---- *message.size* ----------------> PrinterCtrl
6. GCodeReader ---- *message.item* ----------------> PrinterCtrl
7. GCodeReader ---- *EndTransmit* -----------------> PrinterCtrl
8. GCodeReader <--------------- *received.size* ---- PrinterCtrl
9. GCodeReader <----------------- *Acknowledge* ---- PrinterCtrl
10. go to 3

## UART Test

+ **TEST 1**
  1. GCodeReader ---- *Connect* ---------------------> PrinterCtrl
  2. GCodeReader <--------------------- *Connect* ---- PrinterCtrl
+ **TEST 2**
  1. GCodeReader ---- *BeginTransmit* ---------------> PrinterCtrl
  2. GCodeReader ---- *0x1234* ----------------------> PrinterCtrl
  3. GCodeReader ---- *EndTransmit* -----------------> PrinterCtrl
  4. GCodeReader <---------------------- *0x0001* ---- PrinterCtrl
  5. GCodeReader <---------------------- *0x1234* ---- PrinterCtrl
  6. GCodeReader <----------------- *Acknowledge* ---- PrinterCtrl
+ **TEST 3**
  1. GCodeReader ---- *DataExpected* ----------------> PrinterCtrl (expected Acknowledge)
  2. GCodeReader <--------------------- *Failure* ---- PrinterCtrl
