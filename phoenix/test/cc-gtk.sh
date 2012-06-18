g++-4.7 -std=gnu++11 -I.. -g -c ../phoenix.cpp -DPHOENIX_GTK `pkg-config --cflags gtk+-2.0`
g++-4.7 -std=gnu++11 -I.. -g -c test.cpp
g++-4.7 -o test-gtk test.o phoenix.o `pkg-config --libs gtk+-2.0` -lX11
rm *.o
