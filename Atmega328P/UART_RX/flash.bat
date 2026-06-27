@echo off
title Flashing Arduino Uno
echo Flashing start...

avrdude -c arduino -p m328p -P COM3 -b 115200 -U flash:w:out/uart_rx.hex:i

echo.
echo Process finished.
pause