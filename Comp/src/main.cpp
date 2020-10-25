// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// topLeft              motor         12              
// bottomLeft           motor         2               
// topRight             motor         3               
// bottomRight          motor         11              
// intakeLeft           motor         5               
// intakeRight          motor         6               
// intakeRoller         motor         7               
// topIndexer           motor         8               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// topLeft              motor         12              
// bottomLeft           motor         2               
// topRight             motor         3               
// bottomRight          motor         11              
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
// bottomRight          motor         11              
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
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Adam Xu, Shafin Haque                                     */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  53343A Comp code                                          */
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
int SELECTED_AUTON = 5;
bool AUTON_LOCKED = false;

double averageEncoderVal() {
  return (topLeft.position(deg) + topRight.position(deg) +
    bottomLeft.position(deg) + bottomRight.position(deg))/4;
}

void accelVertical(double v, double inches) {
  topLeft.resetPosition(); topRight.resetPosition(); 
  bottomLeft.resetPosition(); bottomRight.resetPosition();

  double error; double desired = inches * INCH_MULT;
  double justify = v / (desired*desired);

  while (true) {
    error = desired - averageEncoderVal();
    if (error >= -5 && error <= 5) {
      topLeft.stop(brake);
      topRight.stop(brake);
      bottomLeft.stop(brake);
      bottomRight.stop(brake);
      break;
    }

    double pwr = justify * averageEncoderVal() * averageEncoderVal() + 35;

    topLeft.spin(fwd, pwr, pct); topRight.spin(fwd, pwr, pct); bottomLeft.spin(fwd, pwr, pct); bottomRight.spin(fwd, pwr, pct); 
  }
}

void accelRight(double v, double inches) {
  topLeft.resetPosition(); topRight.resetPosition(); 
  bottomLeft.resetPosition(); bottomRight.resetPosition();

  double error; double desired = inches * INCH_MULT;
  double justify = v / (desired*desired);

  while (true) {
    error = desired - topLeft.position(deg);
    if (error >= -5 && error <= 5) {
      topLeft.stop(brake);
      topRight.stop(brake);
      bottomLeft.stop(brake);
      bottomRight.stop(brake);

      break;
    }
    double pwr = justify * topLeft.position(deg) * topLeft.position(deg) + 35;
    topLeft.spin(fwd, pwr, pct); topRight.spin(fwd, -1 * pwr, pct);
    bottomLeft.spin(fwd, -1 * pwr, pct); bottomRight.spin(fwd, pwr, pct); 
  }
}

void accelLeft(double v, double inches) {
  topLeft.resetPosition(); topRight.resetPosition(); 
  bottomLeft.resetPosition(); bottomRight.resetPosition();

  double error; double desired = inches * INCH_MULT;
  double justify = v / (desired*desired);

  while (true) {
    error = desired - topRight.position(deg);
    if (error >= -5 && error <= 5) {
      topLeft.stop(brake);
      topRight.stop(brake);
      bottomLeft.stop(brake);
      bottomRight.stop(brake);

      break;
    }
    double pwr = justify * topRight.position(deg) * topRight.position(deg) + 35;
    topLeft.spin(fwd, -1*pwr, pct); topRight.spin(fwd, pwr, pct);
    bottomLeft.spin(fwd, pwr, pct); bottomRight.spin(fwd, -1*pwr, pct); 
  }
}
 
void vertical(double v, double inches) {
  topLeft.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  topRight.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, true);
}
 
void turn90(double v, double dir) {
  topLeft.rotateFor(dir * 350, deg, v, velocityUnits::pct, false);
  topRight.rotateFor(-1 * dir * 350, deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(dir * 350, deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(-1 * dir * 350, deg, v, velocityUnits::pct, true);
}
 
void left_strafe(double v, double inches) {
  topLeft.rotateFor(-1 * inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  topRight.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(-1 * inches * INCH_MULT, deg, v, velocityUnits::pct, true);
}
 
void right_strafe(double v, double inches) {
  topLeft.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  topRight.rotateFor(-1 * inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(-1 * inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, true);
}
 
void flipout(){
  intakeLeft.spin(fwd, 50, pct);
  intakeRight.spin(fwd, 50, pct);
  wait(0.75, sec);
  intakeLeft.stop();
  intakeRight.stop();
}

void deploy(){
  intakeRoller.spin(fwd, 25, percentUnits:: pct);
  wait(0.75, sec);
  intakeRoller.stop();
}

void vertical_noBlock(double v, double inches) {
  topLeft.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  bottomLeft.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  topRight.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
  bottomRight.rotateFor(inches * INCH_MULT, deg, v, velocityUnits::pct, false);
}

void intake(double v, double time_intaking) {
  intakeRoller.spin(directionType::rev, 100, percentUnits::pct);
  intakeLeft.spin(fwd, 1 * v, pct);
  intakeRight.spin(fwd, v, pct);
  wait(time_intaking, timeUnits::sec); 
  intakeRoller.stop();
  intakeRight.stop();
  intakeLeft.stop();
}

void run_top(double v, double time_flywheel) {
  topIndexer.spin(fwd, v, pct);
  wait(time_flywheel, timeUnits::sec);
  topIndexer.stop();
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

    if (Controller1.ButtonA.pressing()) {
      AUTON_LOCKED = true;
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("LOCKED");
      Controller1.rumble(".");
    } 
  }
}
 
void autonomous(void) {
  if (SELECTED_AUTON == 1) {
    // red left side and blue left  side 2 goal auton
    right_strafe(100, 21);  // strafe right (start bot facing goal)
    flipout(); 
    deploy();
    turn90(100, -0.5); // turn left 45 deg
    vertical(50, 18); // go forward 

    intake(100, 1.7); // intake the first ball

    vertical(100, 10); // go into goal
    topIndexer.spin(directionType::fwd, 100, percentUnits::pct);
    wait(0.2, timeUnits::sec);

    intake(100, 1.7); // cycle balls

    // at this point we will have 2 balls in the goal and 1 opposing ball in our bot and 1 of our balls in the bot 

    vertical(100, -21); // go backwards
    turn90(100, 0.5); // turn right 45 deg

    vertical_noBlock(100, -50); // go backwards to get to the middle goal 

    intake(-100, 0.5);
    
    turn90(100, -1); // turn left 90 deg
    vertical(100, 20); // go forward into the goal
    
    intakeRoller.spin(directionType::rev, 100, percentUnits::pct);
    intakeLeft.spin(fwd, -100, pct);
    intakeRight.spin(fwd, 100, pct);
    wait(1.7, timeUnits::sec); // cycle balls
    intakeRoller.stop();
    intakeRight.stop();
    intakeLeft.stop();
    
    // stop with 1 opposing ball in the robot
    // final auton will end with both side and middle goal with only 2 of our balls, and bot will end with 1 opposing ball in bot

  } else if (SELECTED_AUTON == 2) {
    //red right side and right left side 2 goal auton
  
    right_strafe(100, 21);  // strafe left (start bot facing goal)
    flipout(); 
    deploy();
    turn90(100, 0.5); // turn right 45 deg
    vertical(50, 18); // go forward 

    intake(100, 1.7); // intake the first ball

    vertical(100, 10); // go into goal

    topIndexer.spin(directionType::fwd, 100, percentUnits::pct);
    wait(0.2, timeUnits::sec);

    intake(100, 1.7); // cycle balls

    // at this point we will have 2 balls in the goal and 1 opposing ball in our bot and 1 of our balls in the bot 

    vertical(100, -28); // go backwards
    turn90(100, -0.5); // turn left 45 deg

    vertical_noBlock(100, -50); // go backwards to get to the middle goal 

    intake(-100, 0.5);
    
    turn90(100, 1); // turn right 90 deg
    vertical(100, 20); // go forward into the goal
    
    intakeRoller.spin(directionType::rev, 100, percentUnits::pct);
    intakeLeft.spin(fwd, -100, pct);
    intakeRight.spin(fwd, 100, pct);
    wait(1.7, timeUnits::sec); // cycle balls
    intakeRoller.stop();
    intakeRight.stop();
    intakeLeft.stop();
    
    // stop with 1 opposing ball in the robot
    // final auton will end with both side and middle goal with only 2 of our balls, and bot will end with 1 opposing ball in bot
  } else if (SELECTED_AUTON == 3) {
    // left side red and left side blue 3 goal auton
    vertical_noBlock(100,10); //start near the goal and go forward very little 
    intake(100, 0.3); // move while intaking

    turn90(100, -0.4);
    topIndexer.spin(fwd, 100, pct);
    wait(0.3, sec);
    intakeRoller.spin(fwd, 100, pct); // ball in hole
    wait(0.5, sec);

    vertical(100, -30); // move back 

    // at this point scored 1 ball and have 1 in bot

    turn90(100, -90); // turn left to go to mid goal
    vertical(100, 50);
    intakeRoller.spin(fwd, 100, pct);
    wait(0.8, sec); // ball in hole mid goal

    // at this point we have 0 balls in the bot and scored another ball in mid goal

    vertical(-100, 15); // go backwards
    left_strafe(100, 50);
    vertical(100, 50); // go into the goal
    vertical_noBlock(100, 10); // once near the goal use no block so we can move and intake
    intake(100, 0.5); // intake ball
    vertical(100, 10); // move into goal

    intakeRoller.spin(fwd, 100, pct);
    wait(0.5, sec);

  } else if (SELECTED_AUTON == 4) {
    // right side red and right side blue 3 goal auton
    vertical_noBlock(100,10); //start near the goal and go forward very little 
    intake(100, 0.3); // move while intaking

    turn90(100, 0.4);
    topIndexer.spin(fwd, 100, pct);
    wait(0.3, sec);
    intakeRoller.spin(fwd, 100, pct); // ball in hole
    wait(0.5, sec);

    vertical(100, -30); // move back 

    // at this point scored 1 ball and have 1 in bot

    turn90(100, 90); // turn right  to go to jmid goal
    vertical(100, 50);
    intakeRoller.spin(fwd, 100, pct);
    wait(0.8, sec); // ball in hole mid goal

    // at this point we have 0 balls in the bot and scored another ball in mid goal

    vertical(-100, 15); // go backwards
    right_strafe(100, 50);
    vertical(100, 50); // go into the goal
    vertical_noBlock(100, 10); // once near the goal use no block so we can move and intake
    intake(100, 0.5); // intake ball
    vertical(100, 10); // move into goal

    intakeRoller.spin(fwd, 100, pct);
    wait(0.5, sec);
 } else if (SELECTED_AUTON == 5) { // skills
    deploy();
    bottomLeft.spin(fwd, 100, pct);
    bottomRight.spin(reverse, 100, pct); 
    topRight.spin(fwd, 60, pct);
    topLeft.spin(fwd, 35, pct);
    wait(330, msec);
    bottomLeft.stop(brake);
    bottomRight.stop(brake);
    topRight.stop(brake);
    topLeft.stop(brake);
    wait(0.4, sec);

    // shoot first goal
    topIndexer.spin(fwd, 75, pct);
    wait(1, sec);
    intakeRoller.spin(reverse, 100, pct);
    wait(0.5, sec);
    intakeRoller.stop();
    wait(0.3, sec);
    topIndexer.stop();

    // position for intaking second ball
    bottomLeft.spin(fwd, 100, pct);
    bottomRight.spin(reverse, 100, pct); 
    topRight.spin(fwd, 60, pct);
    topLeft.spin(fwd, 35, pct);
    wait(500, msec);
    bottomLeft.stop(brake);
    bottomRight.stop(brake);
    topRight.stop(brake);
    topLeft.stop(brake);
    wait(0.4, sec);

    vertical(50, -4);
    wait(0.2, sec);
    turn90(100, 1.25);
    vertical(75, -7);
    wait(0.5, sec);

    flipout();
    wait(1, sec);

    // intake second ball
    intakeRoller.spin(reverse, 100, pct);
    intakeRight.spin(reverse, 100, pct);
    intakeLeft.spin(reverse, 100, pct);
    accelVertical(70, 42);
    intakeRoller.stop();
    intakeRight.stop();
    intakeLeft.stop();

    wait(0.4, sec);
    turn90(100, -1.05);
    wait(0.2, sec);

    // shoot 2nd shot
    topIndexer.spin(fwd, 100, pct);
    wait(1, sec);
    intakeRoller.spin(reverse, 100, pct);
    wait(0.5, sec);
    intakeRoller.stop();
    wait(0.3, sec);
    topIndexer.stop();

    // position and intake for 3rd shot
    turn90(100, 1);
    wait(0.4, sec);

    intakeRoller.spin(reverse, 100, pct);
    intakeRight.spin(reverse, 100, pct);
    intakeLeft.spin(reverse, 100, pct);
    accelVertical(75, 35);
    wait(0.2, sec);

    turn90(100, -0.5);
    wait(0.2, sec);
    vertical(100, 5);
    wait(0.2, sec);

    intakeRoller.stop();
    intakeRight.stop();
    intakeLeft.stop();

    // shoot third shot
    topIndexer.spin(fwd, 100, pct);
    wait(0.5, sec);
    intakeRoller.spin(reverse, 100, pct);
    wait(0.6, sec);
    intakeRoller.stop();
    wait(0.5, sec);
    topIndexer.stop();

    // fourth
    // vertical(100, -12);
    // turn90(100, 2);

    // intakeRoller.spin(reverse, 100, pct);
    // intakeRight.spin(reverse, 100, pct);
    // intakeLeft.spin(reverse, 100, pct);
    // accelVertical(100, 30);
    // intakeRoller.stop();
    // intakeRight.stop();
    // intakeLeft.stop();

    // turn90(100, -1.1);
    // flywheel.spin(fwd, 100, pct);
    // wait(0.5, sec);
    // intakeRoller.spin(reverse, 100, pct);
    // wait(0.6, sec);
    // intakeRoller.stop();
    // wait(0.3, sec);
    // flywheel.stop();
  } else if (SELECTED_AUTON == 6) {
    accelVertical(100, 20);
  }
}
 
void usercontrol(void) {
  int intakeSpeed = 100;
  double nja_md = 1;

  topLeft.setBrake(brake);
  topRight.setBrake(brake); 
  bottomLeft.setBrake(brake);
  bottomRight.setBrake(brake);
 
  while (true) {
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
    // it was over    wait(100, msec);
    front_left = front_left / max_raw_sum * 100.0;
    back_left = back_left / max_raw_sum * 100.0;
    front_right = front_right / max_raw_sum * 100.0;
    back_right = back_right / max_raw_sum * 100.0;
 
    // Write the manipulated values out to the motors
    bottomRight.spin(fwd, back_right * nja_md, pct);
    topLeft.spin(fwd, front_left * nja_md, pct);
    bottomLeft.spin(fwd, back_left * nja_md, pct);
    topRight.spin(fwd, front_right * nja_md, pct);
 
    if (Controller1.ButtonR2.pressing()) {
      intakeLeft.spin(fwd, intakeSpeed, pct);
      intakeRight.spin(fwd, intakeSpeed, pct);
      intakeRoller.spin(fwd, intakeSpeed, pct);
      topIndexer.spin(fwd, intakeSpeed, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      intakeLeft.spin(reverse, intakeSpeed, pct);
      intakeRight.spin(reverse, intakeSpeed, pct);
      intakeRoller.spin(reverse, intakeSpeed, pct);
      topIndexer.spin(fwd, intakeSpeed, pct);
    } else if (Controller1.ButtonL1.pressing()) {
      intakeRoller.spin(reverse, intakeSpeed, pct);
      topIndexer.spin(reverse, intakeSpeed, pct);
    } else if (Controller1.ButtonR1.pressing()) {
      intakeLeft.spin(reverse, intakeSpeed, pct);
      intakeRight.spin(reverse, intakeSpeed, pct);
    } else {
      intakeLeft.stop(brake);
      intakeRight.stop(brake);
      intakeRoller.stop(brake);
      topIndexer.stop(brake);
    }

    if (Controller1.ButtonR1.pressing()) {
      intakeLeft.spin(reverse, intakeSpeed, pct);
      intakeRight.spin(reverse, intakeSpeed, pct);
    } 

    if (Controller1.ButtonB.pressing()) {
      nja_md = 0.3;
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("[NINJA]");
    } else {
      nja_md = 1;
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
    if (AUTON_LOCKED  && DEBUG_MODE) {
      std::stringstream top;
      std::stringstream bottom;
      top << "[" << round(topLeft.temperature(temperatureUnits::fahrenheit)) << 
        "] [" << round(topRight.temperature(temperatureUnits::fahrenheit)) << "]";
      bottom << "[" << round(bottomLeft.temperature(temperatureUnits::fahrenheit)) << 
        "] [" << round(bottomRight.temperature(temperatureUnits::fahrenheit)) << "]";

      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(top.str().c_str());
      Controller1.Screen.newLine();
      Controller1.Screen.print(bottom.str().c_str());
      Controller1.Screen.newLine();
    }

    wait(1000, msec);
    Controller1.Screen.clearScreen();
  }
}
