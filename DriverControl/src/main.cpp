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
#define TURN_MULT 0.75

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
    double front_left  = (double)(Controller1.Axis3.position(pct) + Controller1.Axis4.position(pct));
    double back_left   = (double)(Controller1.Axis3.position(pct) - Controller1.Axis4.position(pct));
    double front_right = (double)(Controller1.Axis3.position(pct) - Controller1.Axis4.position(pct));
    double back_right  = (double)(Controller1.Axis3.position(pct) + Controller1.Axis4.position(pct));
    
    //Find the largest possible sum of X and Y
    double max_raw_sum = (double)(abs(Controller1.Axis3.position(pct)) + abs(Controller1.Axis4.position(pct)));
    
    //Find the largest joystick value
    double max_XYstick_value = (double)(std::max(abs(Controller1.Axis3.position(pct)),abs(Controller1.Axis4.position(pct))));
    
    //The largest sum will be scaled down to the largest joystick value, and the others will be
    //scaled by the same amount to preserve directionality
    if (max_raw_sum != 0) {
      front_left  = front_left / max_raw_sum * max_XYstick_value;
      back_left   = back_left / max_raw_sum * max_XYstick_value;
      front_right = front_right / max_raw_sum * max_XYstick_value;
      back_right  = back_right / max_raw_sum * max_XYstick_value;
    }
    
    //Now to Controller1sider rotation
    //Naively add the rotational axis
    front_left  = front_left  + (TURN_MULT * Controller1.Axis1.position(pct));
    back_left   = back_left   + (TURN_MULT * Controller1.Axis1.position(pct));
    front_right = front_right - (TURN_MULT * Controller1.Axis1.position(pct));
    back_right  = back_right  - (TURN_MULT * Controller1.Axis1.position(pct));
    
    //What is the largest sum, or is 100 larger?
    max_raw_sum = std::max(std::abs(front_left),std::max(std::abs(back_left),std::max(std::abs(front_right),std::max(std::abs(back_right),100.0))));
    
    //Scale everything down by the factor that makes the largest only 100, if it was over
    front_left  = front_left  / max_raw_sum * 100.0;
    back_left   = back_left   / max_raw_sum * 100.0;
    front_right = front_right / max_raw_sum * 100.0;
    back_right  = back_right  / max_raw_sum * 100.0;
    
    //Write the manipulated values out to the motors
    topLeft.spin(fwd,front_left, velocityUnits::pct);
    bottomLeft.spin(fwd,back_left,  velocityUnits::pct);
    topRight.spin(fwd,front_right,velocityUnits::pct);
    bottomRight.spin(fwd,back_right, velocityUnits::pct);



    if (Controller1.ButtonR2.pressing()) {
      intakeLeft.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
      intakeRoller.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonL2.pressing()) {
      intakeLeft.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
      intakeRight.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
      intakeRoller.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonL1.pressing()){
      intakeRoller.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
    } else {
      intakeLeft.stop(brakeType::brake);
      intakeRight.stop(brakeType::brake);
      intakeRoller.stop(brakeType::brake);
    }

    if(Controller1.ButtonR1.pressing()) {
            flywheel.spin(directionType::fwd, flywheelSpeed, velocityUnits::pct);
    } else {
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


    