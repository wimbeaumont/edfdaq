# edfdaq
general repository for  programs. 

 gcc -O3  -Wall  -I/usr/local/include -Winline -pipe -o bin/ultra    -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt src/ultra.c

gcc  -lpigpio -lpthread   -o bin/blink  src/blink_leds.c
gcc  -lpigpio -lpthread   -o bin/blink_all  src/blink_all.c
