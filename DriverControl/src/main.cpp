<<<<<<< HEAD
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
#include <map>
 
#define PI 3.14159265
#define TURN_MULT 0.6
 
using namespace vex;
 
competition Competition;
 
int clm = 1;
bool conf = false;
 
void vertical(double v, double d) {
 topLeft.rotateTo(d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomLeft.rotateTo(d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 topRight.rotateTo(d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomRight.rotateTo(d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, true);
}
 
void turn90(double dir) {
 topLeft.rotateTo(dir * 90, rotationUnits::deg, false);
 topRight.rotateTo(-1 * dir * 90, rotationUnits::deg, false);
 bottomLeft.rotateTo(dir * 90, rotationUnits::deg, false);
 bottomRight.rotateTo(-1 * dir * 90, rotationUnits::deg, true);
}
 
void left_strafe(float v, float d) {
 topLeft.rotateTo(-1 * d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 topRight.rotateTo(d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomLeft.rotateTo(d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomRight.rotateTo(-1 * d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, true);
}
 
void right_strafe(float v, float d) {
 topLeft.rotateTo(d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 topRight.rotateTo(-1 * d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomLeft.rotateTo(-1 * d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomRight.rotateTo(d * 20.25711711353, rotationUnits::deg, v, velocityUnits::pct, true);
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
 
 while (conf == false) {
   if (Controller1.ButtonUp.pressing() && clm < 8 && conf == false) {
     clm++;
   } else if (Controller1.ButtonDown.pressing() && clm > 1 && conf == false) {
     clm--;
   } else {
   }
   while (conf == false) {
     if (Controller1.ButtonUp.pressing() && clm < 8 && conf == false) {
       clm++;
     } else if (Controller1.ButtonDown.pressing() && clm > 1 &&
                conf == false) {
       clm--;
     } else {
     }
 
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.newLine();
    Controller1.Screen.print(clm);
    Controller1.Screen.newLine();
    Controller1.Screen.print(Brain.Battery.capacity());

     if (Controller1.ButtonA.pressing()) {
       conf = true;
       Controller1.Screen.clearScreen();
       Controller1.Screen.newLine();
       Controller1.Screen.print("locked");
       Controller1.rumble("...");
     } else {
     }
   }
 }
}
 
void autonomous(void) {
 // ..........................................................................
 // Insert autonomous user code here.
 // ..........................................................................
 
 if (clm == 1) {
   // run auton 1()
   // red left side and blue right side
   vertical(-100, -18);
   flipout();
   deploy();
   left_strafe(100, 12);
   vertical(100, 6);
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
   turn90(0.5);
   intakeRight.spin(fwd, 100, pct);
   intakeLeft.spin(fwd, 100, pct);
   intakeRoller.spin(fwd, 100, pct);
   vertical(100, 5);
   intakeLeft.stop();
   intakeRight.stop();
   vertical(100, 3);
   wait(1, timeUnits::sec);
   vertical(-100, -5);
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
 } else if (clm == 2) {
   // run auton 2
   //red right side and blue left side
   vertical(-100, -18);
   flipout();
   deploy();
   right_strafe(100, 12);
   vertical(100, 6);
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
   turn90(-0.5);
   intakeRight.spin(fwd, 100, pct);
   intakeLeft.spin(fwd, 100, pct);
   intakeRoller.spin(fwd, 100, pct);
   vertical(100, 5);
   intakeLeft.stop();
   intakeRight.stop();
   vertical(100, 3);
   wait(1.7, timeUnits::sec);
   vertical(-100, -5);
 } else if (clm == 3) {
   // run auton 3
   // red side 3 goal auton
 } else if (clm == 4) {
   // run auton 4
   // blue side 3 goal auton

 } 
}
 
void usercontrol(void) {
 int intakeSpeed = 100;
 int flywheelSpeed = 100;
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
     intakeLeft.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
     intakeRight.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
     intakeRoller.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
   } else if (Controller1.ButtonL2.pressing()) {
     intakeLeft.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
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
     // vertical(100, 720);
     // vertical(100, -720);
     left_strafe(100, 360);
   } else {
   }
 
   if (Controller1.ButtonA.pressing() && nja_md == 1) {
     nja_md = 0.5;
   } else if (Controller1.ButtonA.pressing() && nja_md == 0.5) {
     nja_md = 1;
   } else {
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

=======
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
#include <iostream>
#include <cmath>
#include <map>
 
#define PI 3.14159265
#define TURN_MULT 0.6
 
using namespace vex;
 
competition Competition;
 
int clm = 1;
bool conf = false;
 
void vertical(double v, double d){
 topLeft.rotateTo(d, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomLeft.rotateTo(d, rotationUnits::deg, v, velocityUnits::pct, false);
 topRight.rotateTo(d, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomRight.rotateTo(d, rotationUnits::deg,v, velocityUnits::pct, true);
}
 
void turn90(int dir){
 topLeft.rotateTo(dir * 90, rotationUnits::deg, false);
 topRight.rotateTo(-1 * dir * 90, rotationUnits::deg, false);
 bottomLeft.rotateTo(dir * 90, rotationUnits::deg, false);
 bottomRight.rotateTo(-1 * dir * 90, rotationUnits::deg, true);
}
 
void left_strafe(float v, float d){
 topLeft.rotateTo(-1 * d, rotationUnits::deg, v, velocityUnits::pct, false);
 topRight.rotateTo(d, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomLeft.rotateTo(d, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomRight.rotateTo(-1 * d, rotationUnits::deg, v, velocityUnits::pct, true);
}
 
void right_strafe(float v, float d){
 topLeft.rotateTo(d, rotationUnits::deg, v, velocityUnits::pct, false);
 topRight.rotateTo(-1 * d, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomLeft.rotateTo(-1 * d, rotationUnits::deg, v, velocityUnits::pct, false);
 bottomRight.rotateTo(d, rotationUnits::deg, v, velocityUnits::pct, true);
}
 
void pre_auton(void) {
 // Initializing Robot Configuration. DO NOT REMOVE!
 vexcodeInit();
 
 while (conf == false) {
if (Controller1.ButtonUp.pressing() && clm < 8 && conf == false) {
clm++;
}  else if (Controller1.ButtonDown.pressing() && clm > 1 && conf == false) {
clm--;
} else {
}
while (conf == false) {
if (Controller1.ButtonUp.pressing() && clm < 8 && conf == false) {
clm++;
} else if (Controller1.ButtonDown.pressing() && clm > 1 && conf == false) {
clm--;
} else {
}
 
if (clm == 1) {
Controller1.Screen.clearScreen();
Controller1.Screen.newLine();
Controller1.Screen.print("1");
 
} else if (clm == 2) {
Controller1.Screen.clearScreen();
Controller1.Screen.newLine();
Controller1.Screen.print("2");
 
Controller1.Screen.clearScreen();
Controller1.Screen.newLine();
Controller1.Screen.print("3");
 
} else if (clm == 4) {
Controller1.Screen.clearScreen();
Controller1.Screen.newLine();
Controller1.Screen.print("4");
 
} else if (clm == 5) {
Controller1.Screen.clearScreen();
Controller1.Screen.newLine();
Controller1.Screen.print("5");
 
} else if (clm == 6) {
Controller1.Screen.clearScreen();
Controller1.Screen.newLine();
Controller1.Screen.print("6");
 
Controller1.Screen.newLine();
Controller1.Screen.print("7");
 
}
else if (clm == 7) {
Controller1.Screen.newLine();
Controller1.Screen.print("8");
 
} else {
}
 
if (Controller1.ButtonA.pressing()) {
conf = true;
Controller1.Screen.clearScreen();
Controller1.Screen.newLine();
Controller1.Screen.print("locked");
Controller1.rumble("...");
}else {
}
}
}
}
 
void autonomous(void) {
 // ..........................................................................
 // Insert autonomous user code here.
 // ..........................................................................
 
 if (clm == 1) {
// run auton 1
// red left side 2 goal auton

/* 
move forward
turn left 90
move forward toward the goal
turn x degrees so facing the goal
intake red ball there
run a full cycle of intake + indexer + flywheel(will score two red balls and intake the blue)
turn -x degrees 
strafe left while outtaking the blue ball
move forward into the goal
do another full cycle scoring 2 balls and then intaking the blue ball
  */

} else if (clm == 2) {
// run auton 2
// red right side 2 goal auton 

} else if (clm == 3) {
// run auton 3
// red side 3 goal auton

} else if (clm == 4) {
// run auton 4
// blue left side 2 goal auton

} else if (clm == 5) {
// run auton 5
// blue left side 2 goal auton

} else if (clm == 6) {
// run auton 6
// blue side 3 goal auton

}

}
 
 
void usercontrol(void) {
 int intakeSpeed = 100;
 int flywheelSpeed = 100;
 double nja_md = 1;
 
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
   topLeft.spin(fwd,front_left * nja_md, velocityUnits::pct);
   bottomLeft.spin(fwd,back_left * nja_md,  velocityUnits::pct);
   topRight.spin(fwd,front_right * nja_md,velocityUnits::pct);
   bottomRight.spin(fwd,back_right * nja_md, velocityUnits::pct);
 
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
 
   if (Controller1.ButtonX.pressing()){
     // vertical(100, 720);
     // vertical(100, -720);
     left_strafe(100, 360);
   } else{}
 
   if(Controller1.ButtonA.pressing() && nja_md == 1){
     nja_md = 0.5;
   } else if (Controller1.ButtonA.pressing() && nja_md == 0.5){
     nja_md = 1;
   } else {}
 
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

>>>>>>> b40bb1d2fffd3ef58574d1cbcf56035084669e18
