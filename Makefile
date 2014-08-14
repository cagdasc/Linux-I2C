 #Copyright (C) 2014  Cagdas Caglak http://expcodes.blogspot.com.tr/

 #This program is free software: you can redistribute it and/or modify
 #it under the terms of the GNU General Public License as published by
 #the Free Software Foundation, either version 3 of the License, or
 #(at your option) any later version.

 #This program is distributed in the hope that it will be useful,
 #but WITHOUT ANY WARRANTY; without even the implied warranty of
 #MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #GNU General Public License for more details.

 #You should have received a copy of the GNU General Public License
 #along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
EXEC_ARDUINO=TestArduino
EXEC_MPU6050=TestMpu6050
CXX=arm-none-linux-gnueabi-g++
CFLAGS=-Wall -c

all: $(EXEC_ARDUINO) $(EXEC_MPU6050)
	mkdir obj
	mv *.o obj

$(EXEC_ARDUINO): TestArduino.o BBB_I2C.o
	$(CXX) TestArduino.o BBB_I2C.o -o $(EXEC_ARDUINO)

$(EXEC_MPU6050): TestMpu6050.o BBB_I2C.o MPU6050.o
	$(CXX) TestMpu6050.o BBB_I2C.o MPU6050.o -o $(EXEC_MPU6050)

TestArduino.o: TestArduino.cpp
	$(CXX) $(CFLAGS) TestArduino.cpp

TestMpu6050.o: TestMpu6050.cpp
	$(CXX) $(CFLAGS) TestMpu6050.cpp

BBB_I2C.o: BBB_I2C.cpp
	$(CXX) $(CFLAGS) BBB_I2C.cpp

MPU6050.o: MPU6050.cpp
	$(CXX) $(CFLAGS) MPU6050.cpp

clean:
	rm -rf *.o $(EXEC_ARDUINO) $(EXEC_MPU6050) obj
