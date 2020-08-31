# 3dPrint
3D Printer controller based on STM32F411 Nucleo board

-----

## Subprojects

+ **GCodeReader** reader of GCode for computers
+ **PrinterCtrl** STM32 controller

-----

## Connection schema

1. GCodeReader ---- *Connect* ---------------------> PrinterCtrl
2. GCodeReader <--------------------- *Connect* ---- PrinterCtrl
3. GCodeReader <---------------- *DataExpected* ---- PrinterCtrl
4. GCodeReader ---- *BeginTransmit* ---------------> PrinterCtrl
5. GCodeReader ---- *message.size* ----------------> PrinterCtrl
6. GCodeReader ---- *message.item...* -------------> PrinterCtrl
7. GCodeReader ---- *EndTransmit* -----------------> PrinterCtrl
8. GCodeReader <--------------- *received.size* ---- PrinterCtrl
9. GCodeReader <------- *Acknowledge / Failure* ---- PrinterCtrl
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
