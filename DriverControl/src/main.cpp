// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// topLeft              motor         1               
// bottomLeft           motor         2               
// topRight             motor         3               
// bottomRight          motor         4               
// intakeLeft           motor         5               
// intakeRight          motor         6               
// intakeRoller         motor         7               
// flywheel             motor         8               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
/*-----------------------------------------------w-----------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
#include <cmath>
#include <map>

#define PI 3.14159265

using namespace vex;

competition Competition;

std::map <std::pair<int, int>, float> quadrant; 


void forward(int v, int d){

}

void backward(int v, int d){

}

void turn90(void){

}

void left_strafe(int v, int d){

}

void right_strafe(int v, int d){
  
}

void turningRight(int v, int d){

}

void turningLeft(int v, int d){
  
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  quadrant[{1, 1}] = 1; quadrant[{0, 1}] = 2; quadrant[{0, 0}] = 3; quadrant[{1, 0}] = 4; 
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}


void usercontrol(void) {
  
  int intakeSpeed = 100;
  int flywheelSpeed = 100;
  while (true) {
    wait(20, msec);
    int ax1 = Controller1.Axis1.value();
    int ax2 = Controller1.Axis2.value();
    int ax3 = Controller1.Axis3.value();
    int ax4 = Controller1.Axis4.value();


    topRight.spin(directionType::fwd, ax2-ax4-ax1, velocityUnits::pct);
    bottomRight.spin(directionType::fwd, ax2-ax4+ax1, velocityUnits::pct);
    topLeft.spin(directionType::fwd, ax2+ax4+ax1, velocityUnits::pct);
    bottomLeft.spin(directionType::fwd, ax2+ax4-ax1, velocityUnits::pct);

    topRight.spin(directionType::fwd, ax3-ax1-ax4, velocityUnits::pct);
    bottomRight.spin(directionType::fwd, ax3-ax1+ax4, velocityUnits::pct);
    topLeft.spin(directionType::fwd, ax3+ax1+ax4, velocityUnits::pct);
    bottomLeft.spin(directionType::fwd, ax3+ax1-ax4, velocityUnits::pct);



    if(Controller1.ButtonR2.pressing()) {
            intakeLeft.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
            intakeRight.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
            intakeRoller.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
        }
    else if(Controller1.ButtonL2.pressing()) {
            intakeLeft.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
            intakeRight.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
            intakeRoller.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
        }
    else if(Controller1.ButtonL1.pressing()){
            intakeRoller.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
    }
    else {
            intakeLeft.stop(brakeType::brake);
            intakeRight.stop(brakeType::brake);
            intakeRoller.stop(brakeType::brake);
        }

    if(Controller1.ButtonR1.pressing()) {
            flywheel.spin(directionType::fwd, flywheelSpeed, velocityUnits::pct);
        }
    else {
            flywheel.stop(brakeType::brake);        
        }

   

  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}


    