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
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>
 
using namespace vex;
 
competition Competition;
 
bool DEBUG_MODE = true;
float PI = 3.14159265;
float TURN_MULT = 0.6;
float INCH_MULT = 28;
int SELECTED_AUTON = 1;
bool AUTON_LOCKED = false;
 
void vertical(double v, double inches) {
  topLeft.rotateFor(inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  topRight.rotateFor(inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, true);
}
 
void turn90(double v, double dir) {
  topLeft.rotateFor(dir * 350, rotationUnits::deg, v, velocityUnits::pct, false);
  topRight.rotateFor(-1 * dir * 350, rotationUnits::deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(dir * 350, rotationUnits::deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(-1 * dir * 350, rotationUnits::deg, v, velocityUnits::pct, true);
}
 
void left_strafe(double v, double inches) {
  topLeft.rotateFor(-1 * inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  topRight.rotateFor(inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(-1 * inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, true);
}
 
void right_strafe(double v, double inches) {
  topLeft.rotateFor(inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  topRight.rotateFor(-1 * inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(-1 * inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(inches * INCH_MULT, rotationUnits::deg, v, velocityUnits::pct, true);
}
 
void flipout(){
  intakeLeft.spin(fwd, 50, pct);
  intakeRight.spin(fwd, 50, pct);
  wait(0.5, sec);
  intakeLeft.stop();
  intakeRight.stop();
}

void deploy(){
  intakeRoller.spin(fwd, 25, percentUnits:: pct);
  wait(0.5, sec);
  intakeRoller.stop();
}
 
void pre_auton(void) {
 // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
 
  while (AUTON_LOCKED == false) {
    if (Controller1.ButtonUp.pressing() && SELECTED_AUTON < 8) {
      SELECTED_AUTON++;
    } else if (Controller1.ButtonDown.pressing() && SELECTED_AUTON > 1) {
      SELECTED_AUTON--;
    } 

    std::stringstream preAutText;
    preAutText << "(" << Brain.Battery.capacity() << "\%)" << " [AUT" << SELECTED_AUTON << "]"; 
 
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(preAutText.str().c_str());

    if (Controller1.ButtonY.pressing()) {
      AUTON_LOCKED = true;
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("LOCKED");
      Controller1.rumble(".");
    } 
  }
}
 
void autonomous(void) {
 // ..........................................................................
 // Insert autonomous user code here.
 // ..........................................................................
 
  if (SELECTED_AUTON == 1) {
    // red left side and blue right side
    right_strafe(100, 21);
    flipout();
    deploy();
    turn90(100, -0.5);
    vertical(50, 18);
    intakeRoller.spin(directionType::rev, 100, percentUnits::pct);
    intakeLeft.spin(fwd, -100, pct);
    intakeRight.spin(fwd, 100, pct);
    wait(1.7, timeUnits::sec);
    intakeRoller.stop();
    intakeRight.stop();
    intakeLeft.stop();
    vertical(50, 10);
    flywheel.spin(directionType::fwd, 100, percentUnits::pct);
    intakeRoller.spin(directionType::rev, 100, percentUnits::pct);
    intakeLeft.spin(fwd, -100, pct);
    intakeRight.spin(fwd, 100, pct);
    wait(1.7, timeUnits::sec);
    intakeRoller.stop();
    intakeRight.stop();
    intakeLeft.stop();
    // vertical(-100, -6);
    // intakeRight.spin(fwd, -100, pct);
    // intakeLeft.spin(fwd, -100, pct);
    // intakeRoller.spin(fwd, -100, pct);
    // left_strafe(100, 48);
    // wait(0.5, timeUnits::sec);
    // turn90(100, 0.5);
    // intakeRight.spin(fwd, 100, pct);
    // intakeLeft.spin(fwd, 100, pct);
    // intakeRoller.spin(fwd, 100, pct);
    // vertical(100, 5);
    // intakeLeft.stop();
    // intakeRight.stop();
    // vertical(100, 3);
    // wait(1, timeUnits::sec);
    // vertical(-100, -5);
    //     go straight
    // turn right 90
    // go straight
    // turn right 90
    // go forward
    // full cycle preload and bottom ball in
    // intake blue but dont shoot
    // go back a bit release read ball
    // turn right 90
    // go straight
    // turn left 45
    // go straight intake
    // go into goal intake
    // full cycle
    // intake blue but just keep it in bot
  } else if (SELECTED_AUTON == 2) {
    // run auton 2
    //red right side and blue left side
    vertical(100, -18);
    flipout();
    deploy();
    right_strafe(100, 12);
    flywheel.spin(directionType::fwd, 100, percentUnits::pct);
    intakeRoller.spin(directionType::fwd, 100, percentUnits::pct);
    intakeLeft.spin(fwd, 100, pct);
    intakeRight.spin(fwd, 100, pct);
    wait(1.7, timeUnits::sec);
    intakeRoller.stop();
    intakeRight.stop();
    intakeLeft.stop();
    vertical(-100, -6);
    intakeRight.spin(fwd, -100, pct);
    intakeLeft.spin(fwd, -100, pct);
    intakeRoller.spin(fwd, -100, pct);
    left_strafe(100, 48);
    wait(0.5, timeUnits::sec);
    turn90(100, -0.5);
    intakeRight.spin(fwd, 100, pct);
    intakeLeft.spin(fwd, 100, pct);
    intakeRoller.spin(fwd, 100, pct);
    vertical(100, 5);
    intakeLeft.stop();
    intakeRight.stop();
    vertical(100, 3);
    wait(1.7, timeUnits::sec);
    vertical(-100, -5);
  } else if (SELECTED_AUTON == 3) {
    // run auton 3
    // red side 3 goal auton
  } else if (SELECTED_AUTON == 4) {
    // run auton 4
    // blue side 3 goal auton
 } 
}
 
void usercontrol(void) {
  int intakeSpeed = 100;
  int flywheelSpeed = 75;
  double nja_md = 1;
 
  while (true) {
    wait(20, msec);
    double front_left = (double)(Controller1.Axis3.position(pct) +
                                Controller1.Axis4.position(pct));
    double back_left = (double)(Controller1.Axis3.position(pct) -
                               Controller1.Axis4.position(pct));
    double front_right = (double)(Controller1.Axis3.position(pct) -
                                 Controller1.Axis4.position(pct));
    double back_right = (double)(Controller1.Axis3.position(pct) +
                                Controller1.Axis4.position(pct));
 
   // Find the largest possible sum of X and Y
    double max_raw_sum = (double)(abs(Controller1.Axis3.position(pct)) +
                                 abs(Controller1.Axis4.position(pct)));
 
    // Find the largest joystick value
    double max_XYstick_value =
       (double)(std::max(abs(Controller1.Axis3.position(pct)),
                         abs(Controller1.Axis4.position(pct))));
 
    // The largest sum will be scaled down to the largest joystick value, and
    // the others will be scaled by the same amount to preserve directionality
    if (max_raw_sum != 0) {
      front_left = front_left / max_raw_sum * max_XYstick_value;
      back_left = back_left / max_raw_sum * max_XYstick_value;
      front_right = front_right / max_raw_sum * max_XYstick_value;
      back_right = back_right / max_raw_sum * max_XYstick_value;
    }
 
    // Now to Controller1sider rotation
    // Naively add the rotational axis
    front_left = front_left + (TURN_MULT * Controller1.Axis1.position(pct));
    back_left = back_left + (TURN_MULT * Controller1.Axis1.position(pct));
    front_right = front_right - (TURN_MULT * Controller1.Axis1.position(pct));
    back_right = back_right - (TURN_MULT * Controller1.Axis1.position(pct));
 
    // What is the largest sum, or is 100 larger?
    max_raw_sum =
        std::max(std::abs(front_left),
                std::max(std::abs(back_left),
                         std::max(std::abs(front_right),
                                  std::max(std::abs(back_right), 100.0))));
 
    // Scale everything down by the factor that makes the largest only 100, if
    // it was over
    front_left = front_left / max_raw_sum * 100.0;
    back_left = back_left / max_raw_sum * 100.0;
    front_right = front_right / max_raw_sum * 100.0;
    back_right = back_right / max_raw_sum * 100.0;
 
    // Write the manipulated values out to the motors
    topLeft.spin(fwd, front_left * nja_md, velocityUnits::pct);
    bottomLeft.spin(fwd, back_left * nja_md, velocityUnits::pct);
    topRight.spin(fwd, front_right * nja_md, velocityUnits::pct);
    bottomRight.spin(fwd, back_right * nja_md, velocityUnits::pct);
 
    if (Controller1.ButtonR2.pressing()) {
      intakeLeft.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
      intakeRoller.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonL2.pressing()) {
      intakeLeft.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
      intakeRight.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
      intakeRoller.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
    } else if (Controller1.ButtonL1.pressing()) {
      intakeRoller.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
    } else {
      intakeLeft.stop(brakeType::brake);
      intakeRight.stop(brakeType::brake);
      intakeRoller.stop(brakeType::brake);
    }
 
    if (Controller1.ButtonR1.pressing()) {
      flywheel.spin(directionType::fwd, flywheelSpeed, velocityUnits::pct);
    } else {
      flywheel.stop(brakeType::brake);
    }
 
    if (Controller1.ButtonX.pressing()) {
      autonomous();
    }
 
    if (Controller1.ButtonA.pressing()) {
      nja_md = 0.3;
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("ninja");
    } else {
      Controller1.Screen.clearScreen();
      nja_md = 1;
    }

    if (AUTON_LOCKED  && DEBUG_MODE) {
      std::stringstream top;
      std::stringstream bottom;
      top << "[" << round(topLeft.velocity(velocityUnits::pct)) << 
        "] [" << round(topRight.velocity(velocityUnits::pct)) << "]";
      bottom << "[" << round(bottomLeft.velocity(velocityUnits::pct)) << 
        "] [" << round(bottomRight.velocity(velocityUnits::pct)) << "]";

      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(top.str().c_str());
      Controller1.Screen.newLine();
      Controller1.Screen.print(bottom.str().c_str());
      Controller1.Screen.newLine();
      Controller1.Screen.clearScreen();
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
