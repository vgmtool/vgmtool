moc -i -o ../qt/platform.moc ../qt/platform.moc.hpp
g++-4.7 -std=gnu++11 -I.. -g -c ../phoenix.cpp `pkg-config --cflags QtCore QtGui` -DPHOENIX_QT
g++-4.7 -std=gnu++11 -I.. -g -c test.cpp
g++-4.7 -o test-qt test.o phoenix.o `pkg-config --libs QtCore QtGui`
rm *.o
