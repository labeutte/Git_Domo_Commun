all: domot.o sim.o serieLin.o accesBDD.o rcswitch.o monitFTP.o internet.o compress.o
	g++ -o appli domot.o sim.o serieLin.o monitFTP.o accesBDD.o internet.o \
	rcswitch.o compress.o \
	-lwiringPi -lrt -lcrypt -lpthread -lmysqlclient -std=c++11 \
	-lopencv_highgui -lopencv_core -lopencv_legacy \
	-lopencv_imgproc -lopencv_video -lopencv_features2d -lopencv_calib3d \
	-L/home/gilles/wiringPi/wiringPi -D_REENTRANT

serieLin.o: serieLin.cpp serieLin.h
	g++ -o serieLin.o -c serieLin.cpp  -std=c++11 -W

monitFTP.o: monitFTP.cpp monitFTP.h
	g++ -c monitFTP.cpp -std=c++11 -W

rcswitch.o: RCSwitch.cpp RCSwitch.h
	g++ -o rcswitch.o -c RCSwitch.cpp  -std=c++11

sim.o: sim.cpp sim.h
	g++ -c sim.cpp -std=c++11 -W

accesBDD.o: accesBDD.cpp accesBDD.h
	g++ -c accesBDD.cpp -std=c++11 -W

internet.o: internet.cpp internet.h
	g++ -c internet.cpp -std=c++11 -W

domot.o: domot.cpp
	g++ -c domot.cpp  -std=c++11 -W
	
compress.o: compress.cpp
	g++ -c compress.cpp  -std=c++11 -W
	
clean:
	rm *.o
	
testCSQ: testCSQ.cpp serieLin.o sim.o
	g++ -o testCSQ testCSQ.cpp serieLin.o sim.o -std=c++11 -W
