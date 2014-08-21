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
 
ECHO=@echo
ECHO_N=@echo -n

EXEC_ARDUINO=TestArduino
EXEC_MPU6050=TestMpu6050
EXEC_ADXL345=TestADXL345
EXEC_HMC5883L=TestHMC5883L

CXX=g++
CFLAGS=-Wall -c

all: $(EXEC_ARDUINO) $(EXEC_MPU6050) $(EXEC_ADXL345) $(EXEC_HMC5883L)
	@mkdir -p obj
	@mv *.o obj

$(EXEC_ARDUINO): TestArduino.o BBB_I2C.o
	$(ECHO) "$(EXEC_ARDUINO) building..."
	@$(CXX) TestArduino.o BBB_I2C.o -o $(EXEC_ARDUINO)

$(EXEC_MPU6050): TestMpu6050.o BBB_I2C.o MPU6050.o
	$(ECHO) "$(EXEC_MPU6050) building..."
	@$(CXX) TestMpu6050.o BBB_I2C.o MPU6050.o -o $(EXEC_MPU6050)
	
$(EXEC_ADXL345): TestADXL345.o BBB_I2C.o ADXL345.o
	$(ECHO) "$(EXEC_ADXL345) building..."
	@$(CXX) TestADXL345.o BBB_I2C.o ADXL345.o -o $(EXEC_ADXL345)
		
$(EXEC_HMC5883L): TestHMC5883L.o BBB_I2C.o HMC5883L.o
	$(ECHO) "$(EXEC_HMC5883L) building..."
	@$(CXX) TestHMC5883L.o BBB_I2C.o HMC5883L.o -o $(EXEC_HMC5883L)

TestArduino.o: TestArduino.cpp
	@$(CXX) $(CFLAGS) TestArduino.cpp

TestMpu6050.o: TestMpu6050.cpp
	@$(CXX) $(CFLAGS) TestMpu6050.cpp
	
TestADXL345.o: TestADXL345.cpp
	@$(CXX) $(CFLAGS) TestADXL345.cpp
	
TestHMC5883L.o: TestHMC5883L.cpp
	@$(CXX) $(CFLAGS) TestHMC5883L.cpp

BBB_I2C.o: BBB_I2C.cpp
	@$(CXX) $(CFLAGS) BBB_I2C.cpp

MPU6050.o: MPU6050.cpp
	@$(CXX) $(CFLAGS) MPU6050.cpp

ADXL345.o: ADXL345.cpp
	@$(CXX) $(CFLAGS) ADXL345.cpp
	
HMC5883L.o: HMC5883L.cpp
	@$(CXX) $(CFLAGS) HMC5883L.cpp

clean:
	$(ECHO) "Clean."
	@rm -rf *.o $(EXEC_ARDUINO) $(EXEC_MPU6050) $(EXEC_ADXL345) $(EXEC_HMC5883L) obj
