# 1 "/home/roygerstner/git_repos/ArduinoTestProject_XL320/ArduinoTestProject_XL320.ino"


/*******************************************************************************

* Copyright 2016 ROBOTIS CO., LTD.

*

* Licensed under the Apache License, Version 2.0 (the "License");

* you may not use this file except in compliance with the License.

* You may obtain a copy of the License at

*

*     http://www.apache.org/licenses/LICENSE-2.0

*

* Unless required by applicable law or agreed to in writing, software

* distributed under the License is distributed on an "AS IS" BASIS,

* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

* See the License for the specific language governing permissions and

* limitations under the License.

*******************************************************************************/
# 19 "/home/roygerstner/git_repos/ArduinoTestProject_XL320/ArduinoTestProject_XL320.ino"
# 20 "/home/roygerstner/git_repos/ArduinoTestProject_XL320/ArduinoTestProject_XL320.ino" 2
# 21 "/home/roygerstner/git_repos/ArduinoTestProject_XL320/ArduinoTestProject_XL320.ino" 2


// Please modify it to suit your hardware.
# 41 "/home/roygerstner/git_repos/ArduinoTestProject_XL320/ArduinoTestProject_XL320.ino"
  const int DXL_DIR_PIN = 28; //OpenCM9.04 EXP Board's DIR PIN. (28 for the DXL port on the OpenCM 9.04 board)
# 61 "/home/roygerstner/git_repos/ArduinoTestProject_XL320/ArduinoTestProject_XL320.ino"
const int32_t baud = 1000000;
uint8_t posMot1, posMot2;

Dynamixel2Arduino dxl(Serial1 /*OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)*/, DXL_DIR_PIN);

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:
  int8_t index = 0;
  int8_t found_dynamixel = 0;

  // Use UART port of DYNAMIXEL Shield to debug.
  Serial.begin(115200); //set debugging port baudrate to 115200bps
  while(!Serial); //Wait until the serial port is opened


    // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
    int8_t protocol = 2;
    dxl.setPortProtocolVersion((float)protocol);
    Serial.print("SCAN PROTOCOL (Roy) ");
    Serial.println(protocol);

      // Set Port baudrate.
      Serial.print("SCAN BAUDRATE ");
      Serial.println(baud);
      dxl.begin(baud);
      for(int id = 0; id < 10; id++) {
        //iterate until all ID in each buadrate is scanned.
        if(dxl.ping(id)) {
          Serial.print("ID : ");
          Serial.print(id);
          Serial.print(", Model Number: ");
          Serial.println(dxl.getModelNumber(id));
          found_dynamixel++;

          // Turn off torque when configuring items in EEPROM area
          dxl.torqueOff(id);
          int8_t mode_result = dxl.setOperatingMode(id, OP_VELOCITY);
          dxl.torqueOn(id);
          Serial.print("OperationMode ");
          Serial.println(mode_result);
          dxl.ledOn(id);


          // dxl.writeControlTableItem(PROFILE_VELOCITY, id, 30);
        }
        else{
          Serial.print("ID : ");
          Serial.print(id);
          Serial.println(" empty");
        }
      }

  Serial.print("Total ");
  Serial.print(found_dynamixel);
  Serial.println(" DYNAMIXEL(s) found!");



  posMot1 = dxl.getPresentPosition(2);
  posMot2 = dxl.getPresentPosition(3);

  Serial.print("Positions:  ");
  Serial.print(posMot1);
  Serial.print(" : ");
  Serial.print(posMot2);

  int8_t result1 = dxl.setGoalVelocity(2, 25.8, UNIT_RPM); //use RPM(2, 100);
  int8_t result2 = dxl.setGoalVelocity(3, 25.8, UNIT_RPM); //use RPM(2, 100);

  Serial.println(" ");
  Serial.print("setGoalVelocity ");
  Serial.print(result1);
  Serial.print(" : ");
  Serial.println(result2);

  result1 = dxl.torqueOn(2);
  result2 = dxl.torqueOn(3);

  Serial.println(" ");
  Serial.print("torqueOn ");
  Serial.print(result1);
  Serial.print(" : ");
  Serial.println(result2);
}

float_t rpm = 0.0;

void loop() {
  // put your main code here, to run repeatedly:
  posMot1 = dxl.getPresentVelocity(2);
  posMot2 = dxl.getPresentVelocity(3);

  Serial.print("Velocity:  ");
  Serial.print(posMot1);
  Serial.print(" : ");
  Serial.println(posMot2);

  // put your main code here, to run repeatedly:

  // Please refer to e-Manual(http://emanual.robotis.com) for available range of value. 
  // Set Goal Velocity using RAW unit
  dxl.setGoalVelocity(2, rpm, UNIT_PERCENT);
  dxl.setGoalVelocity(3, -rpm, UNIT_PERCENT);

  rpm += 1.0;
  if(rpm > 100){
    rpm = 0.0;
  }

  Serial.print("Speed : ");
  Serial.println(rpm);
  HAL_Delay(1000);


}
