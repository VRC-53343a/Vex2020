// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// topLeft              motor         1               
// backLeft           motor         2               
// topRight             motor         3               
// backRight          motor         4               
// intakeLeft           motor         5               
// intakeRight          motor         6               
// indexer         motor         7               
// flywheel             motor         8               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Adam Xu (adx59), Shafin Haque (ShafinH)                   */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  53343A comp / skills code                                 */
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
 
double PI = 3.14159265;
double TURN_MULT = 0.6; // slow down driver turn speed
double INCH_MULT = 28;

int intakeSpeed = 100;
double nja_md = 1;

int MENU_MODE = 0;
int SELECTED_AUTON = 0;
std::string AUTON_CODES[8] = {"R1", "R2", "R3", "L1", "L2", "L3", "S", "CUSTOM"};

double ROUTINE[5][3] = {{0, 100, 0}, {-1, 100, 0}, {-1, 100, 0}, {-1, 100, 0}, {-1, 100, 0}};
int CRT = 0;
std::string CUSTOM_NAME[6] = {"V", "T", "A", "I", "S", "C"}; 
 
void vertical(double v, double dist) {
  topLeft.rotateFor(dist * INCH_MULT, deg, v, velocityUnits::pct, false);
  backLeft.rotateFor(dist * INCH_MULT, deg, v, velocityUnits::pct, false);
  topRight.rotateFor(dist * INCH_MULT, deg, v, velocityUnits::pct, false);
  backRight.rotateFor(dist * INCH_MULT, deg, v, velocityUnits::pct, true);
}

void avertical (double v, double dist) {
  topLeft.rotateFor(dist * INCH_MULT, deg, v, velocityUnits::pct, false);
  backLeft.rotateFor(dist * INCH_MULT, deg, v, velocityUnits::pct, false);
  topRight.rotateFor(dist * INCH_MULT, deg, v, velocityUnits::pct, false);
  backRight.rotateFor(dist * INCH_MULT, deg, v, velocityUnits::pct, false);
}
 
void turn90(double v, double dir) {
  topLeft.rotateFor(dir * 291.1, deg, v, velocityUnits::pct, false);
  topRight.rotateFor(dir * -291.1, deg, v, velocityUnits::pct, false);
  backLeft.rotateFor(dir * 291.1, deg, v, velocityUnits::pct, false);
  backRight.rotateFor(dir * -291.1, deg, v, velocityUnits::pct, true);
}

void arms (double v) {
  intakeLeft.spin(reverse, v, pct); intakeRight.spin(reverse, v, pct);
}

void haltArms () { 
  intakeLeft.stop(); intakeRight.stop(); 
}

void rollers (double v) {
  indexer.spin(directionType::rev, v, percentUnits::pct);
}

void haltRollers () {
  indexer.stop();
}

void intake(double v) {
  indexer.spin(directionType::rev, v, percentUnits::pct);
  intakeLeft.spin(reverse, v, pct);
  intakeRight.spin(reverse, v, pct);
}

void haltIntake() {
  indexer.stop();
  intakeRight.stop();
  intakeLeft.stop();
}

void shoot (double v) { 
  shooter.spin(reverse, v, pct); 
}

void haltShoot () {
  shooter.stop(); 
}

void cycle (double v) {
  indexer.spin(reverse, v, pct);
  intakeLeft.spin(reverse, v, pct);
  intakeRight.spin(reverse, v, pct);
  shooter.spin(reverse, v, pct);
}

void haltCycle () {
  indexer.stop(); 
  intakeLeft.stop(); intakeRight.stop(); 
  shooter.stop();
}

void flipout(){
  intakeLeft.spin(fwd, 50, pct);
  intakeRight.spin(fwd, 50, pct);
  wait(0.75, sec);
  intakeLeft.stop();
  intakeRight.stop();
}

void deploy(){
  shoot(30);
  wait(0.25, sec);
  haltShoot();
}

void selector () {
  // inputs
  if (MENU_MODE == 0) {
    if (Controller1.ButtonRight.pressing() && SELECTED_AUTON < 6) {
      SELECTED_AUTON++;
    } 

    if (Controller1.ButtonLeft.pressing() && SELECTED_AUTON > 0) {
      SELECTED_AUTON--;
    } 

    if (Controller1.ButtonY.pressing()) {
      MENU_MODE = 1;
      SELECTED_AUTON = 7;
      Controller1.rumble("...");
    }
  } else if (MENU_MODE == 1) {
    ROUTINE[CRT][1] += 0.01 * (double) Controller1.Axis3.position(pct);
    ROUTINE[CRT][2] += 0.01 * (double) Controller1.Axis2.position(pct);
    ROUTINE[CRT][1] = round(10 * ROUTINE[CRT][1])/10; ROUTINE[CRT][2] = round(10 * ROUTINE[CRT][2])/10;

    if (Controller1.ButtonRight.pressing() && ROUTINE[CRT][0] < 5) {
      ROUTINE[CRT][0]++;
    }
    if (Controller1.ButtonLeft.pressing() && ROUTINE[CRT][0] > 0) {
      ROUTINE[CRT][0]--;
    }

    if (Controller1.ButtonUp.pressing() && CRT < 4) {
      ROUTINE[CRT+1][0] = ROUTINE[CRT+1][0] == -1 ? 0 : ROUTINE[CRT+1][0];
      CRT++;
    } 
    else if (Controller1.ButtonDown.pressing() && CRT > 0) {
      CRT--;
    }
  }

  if (Controller1.ButtonA.pressing()) {
      MENU_MODE = 2;
      Controller1.rumble(".");
  }
}

void ctrlRender () {
  Controller1.Screen.clearScreen();
  if (MENU_MODE == 0) {
    std::stringstream SelectorText[2];
    SelectorText[0] << "Battery: " << Brain.Battery.capacity() << "\%"; 
    SelectorText[1] << "Auton: " << AUTON_CODES[SELECTED_AUTON] << ""; 

    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("- SELECT -");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(SelectorText[0].str().c_str());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print(SelectorText[1].str().c_str());
  } else if (MENU_MODE == 1) {
    std::stringstream CustomText[3];
    CustomText[0] << "= Action #" << CRT+1 << " =";
    CustomText[1] << "[" << CUSTOM_NAME[(int) ROUTINE[CRT][0]] << "] / V: " << ROUTINE[CRT][1] << " / D: " << ROUTINE[CRT][2];
    for (int i = 0; i < 5; i++) { CustomText[2] << CUSTOM_NAME[(int) ROUTINE[i][0]] << "; "; } 

    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(CustomText[0].str().c_str());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print(CustomText[1].str().c_str());
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(CustomText[2].str().c_str());
  } else if (MENU_MODE == 2) {
    std::stringstream top;
    std::stringstream bottom;
    top << "Temp: " << round(topLeft.temperature(temperatureUnits::fahrenheit));
    bottom << "Auton: " << AUTON_CODES[SELECTED_AUTON];

    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(top.str().c_str());
    Controller1.Screen.newLine();
    Controller1.Screen.print(bottom.str().c_str());
    Controller1.Screen.newLine();

    if (nja_md == 0.3) {
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("[NINJA]");
    }
  }
}
  
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}
 
void autonomous(void) {
  topLeft.setBrake(brake);
  topRight.setBrake(brake); 
  backLeft.setBrake(brake);
  backRight.setBrake(brake);

  if (SELECTED_AUTON == 7) {
    for (int n = 0; n < 5; n++) {
      if (ROUTINE[n][0] == 0) {
        vertical(ROUTINE[n][1], ROUTINE[n][2]);
      } else if (ROUTINE[n][0] == 1) {
        turn90(ROUTINE[n][1], ROUTINE[n][2]);
      } else if (ROUTINE[n][0] == 2) {
        arms(ROUTINE[n][1]);
        wait(ROUTINE[n][2], sec);
        haltArms();
      } else if (ROUTINE[n][0] == 3) {
        intake(ROUTINE[n][1]);
        wait(ROUTINE[n][2], sec);
        haltIntake();
      } else if (ROUTINE[n][0] == 4) {
        shoot(ROUTINE[n][1]);
        wait(ROUTINE[n][2], sec);
        haltShoot();
      } else if (ROUTINE[n][0] == 5) {
        cycle(ROUTINE[n][1]);
        wait(ROUTINE[n][2], sec);
        haltCycle();
      }
    }
    return;
  }

  if (SELECTED_AUTON == 0) {
    // Right side, 1 goal
    deploy();

    vertical(30, 23);
    wait(0.5, sec);
    turn90(100, 1.5);

    arms(100);
    vertical(30, 18);
    rollers(100);
    wait(0.5, sec);
    haltRollers();
    haltArms(); 
    vertical(30, 6);

    // 2b no preload
    arms(100);
    rollers(100);
    shoot(100);
    wait(0.5, sec);
    haltArms(); // avoid intaking last ball
    wait(1.2, sec); // shoot red ball
    haltCycle();

    // take last ball
    arms(100);
    wait(0.6, sec);
    haltArms();

    vertical(30, -12);
  } else if (SELECTED_AUTON == 1) {
    // Right side, 2 goal
    deploy();

    vertical(30, 24);
    wait(0.5, sec);
    turn90(100, 1.5);

    // intake gball
    arms(100);
    vertical(50, 21);
    haltArms(); 
    vertical(25, 3.5);

    // shoot 1 ball in
    rollers(100);
    shoot(100);
    wait(0.7, sec);
    haltCycle();
    wait(0.4, sec);

    // back up and position for second goal
    vertical(30, -13.5);
    wait(0.7, sec);
    turn90(100, 1.55);
    wait(0.4, sec);

    vertical(50, 45.5);
    turn90(100, -1.05);

    // move in
    vertical(50, 8);

    // cyc to obtain g2b
    arms(100);
    rollers(100);
    shoot(100);
    wait(0.4, sec);
    haltArms();
    wait(1, sec);
    haltCycle();

    // move out, take ob
    arms(100);
    wait(0.6, sec);
    haltArms();
    vertical(30, -10);
  } else if (SELECTED_AUTON == 2) {

  } else if (SELECTED_AUTON == 3) {
    // left side, 1 goal
    deploy();

    vertical(30, 21);
    wait(0.5, sec);
    turn90(100, -1.53);

    // stop and intake gball
    arms(100);
    vertical(30, 18);
    rollers(100);
    wait(0.5, sec);
    haltRollers();
    haltArms(); 

    // move in
    vertical(30, 6);

    // 2b no preload
    arms(100);
    rollers(100);
    shoot(100);
    wait(0.5, sec);
    haltArms(); // avoid intaking last ball
    wait(1.2, sec); // shoot red ball
    haltCycle();

    // take last ball
    arms(100);
    wait(0.6, sec);
    haltArms();

    vertical(30, -12);
  } else if (SELECTED_AUTON == 4) {
    // left side, 2 goal
    deploy();

    vertical(30, 21);
    wait(0.5, sec);
    turn90(100, -1.53);

    // take in outside gball
    arms(100);
    vertical(50, 21);
    haltArms(); 
    vertical(25, 3);

    rollers(100);
    shoot(100);
    wait(0.7, sec);
    haltCycle();
    wait(0.4, sec);

    // move to second goal
    vertical(30, -13.5);
    wait(0.7, sec);
    turn90(100, -1.55);
    wait(0.3, sec);
    vertical(50, 46);
    turn90(100, 1.05);

    // move in
    vertical(50, 9);

    // shoot 2b second goal
    cycle(100);
    wait(0.7, sec);
    haltArms();
    wait(0.9, sec);
    haltCycle();

    wait(0.5, sec);
    vertical(30, -10);
  } else if (SELECTED_AUTON == 5) {

  } else if (SELECTED_AUTON == 6) { 
    /*
    * Skills Auton
    * Four-goal, encoder, some wait-time utilized
    */
    deploy();
    backLeft.spin(fwd, 100, pct);
    backRight.spin(reverse, 100, pct); 
    topRight.spin(fwd, 60, pct);
    topLeft.spin(fwd, 35, pct);
    wait(330, msec);
    backLeft.stop(brake);
    backRight.stop(brake);
    topRight.stop(brake);
    topLeft.stop(brake);
    wait(0.4, sec);

    // shoot first goal
    shooter.spin(fwd, 75, pct);
    wait(1, sec);
    indexer.spin(reverse, 100, pct);
    wait(0.5, sec);
    indexer.stop();
    wait(0.3, sec);
    shooter.stop();

    // position for intaking second ball
    backLeft.spin(fwd, 100, pct);
    backRight.spin(reverse, 100, pct); 
    topRight.spin(fwd, 60, pct);
    topLeft.spin(fwd, 35, pct);
    wait(500, msec);
    backLeft.stop(brake);
    backRight.stop(brake);
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
    indexer.spin(reverse, 100, pct);
    intakeRight.spin(reverse, 100, pct);
    intakeLeft.spin(reverse, 100, pct);
    //accelVertical(70, 42);
    indexer.stop();
    intakeRight.stop();
    intakeLeft.stop();

    wait(0.4, sec);
    turn90(100, -1.05);
    wait(0.2, sec);

    // shoot 2nd shot
    shooter.spin(fwd, 100, pct);
    wait(1, sec);
    indexer.spin(reverse, 100, pct);
    wait(0.5, sec);
    indexer.stop();
    wait(0.3, sec);
    shooter.stop();

    // position and intake for 3rd shot
    turn90(100, 1);
    wait(0.4, sec);

    indexer.spin(reverse, 100, pct);
    intakeRight.spin(reverse, 100, pct);
    intakeLeft.spin(reverse, 100, pct);
    //accelVertical(75, 35);
    wait(0.2, sec);

    turn90(100, -0.5);
    wait(0.2, sec);
    vertical(100, 5);
    wait(0.2, sec);

    indexer.stop();
    intakeRight.stop();
    intakeLeft.stop();

    // shoot third shot
    shooter.spin(fwd, 100, pct);
    wait(0.5, sec);
    indexer.spin(reverse, 100, pct);
    wait(0.6, sec);
    indexer.stop();
    wait(0.5, sec);
    shooter.stop();

    // fourth
    // vertical(100, -12);
    // turn90(100, 2);

    // indexer.spin(reverse, 100, pct);
    // intakeRight.spin(reverse, 100, pct);
    // intakeLeft.spin(reverse, 100, pct);
    // accelVertical(100, 30);
    // indexer.stop();
    // intakeRight.stop();
    // intakeLeft.stop();

    // turn90(100, -1.1);
    // flywheel.spin(fwd, 100, pct);
    // wait(0.5, sec);
    // indexer.spin(reverse, 100, pct);
    // wait(0.6, sec);
    // indexer.stop();
    // wait(0.3, sec);
    // flywheel.stop();
  } 
}
 
void usercontrol(void) {
  topLeft.setBrake(brake);
  topRight.setBrake(brake); 
  backLeft.setBrake(brake);
  backRight.setBrake(brake);

  while (true) {
    if (MENU_MODE == 2) {
      // drive train
      topLeft.spin(fwd, nja_md*(Controller1.Axis3.position(pct) + 0.7*Controller1.Axis1.position()), pct);
      topRight.spin(fwd, nja_md*(Controller1.Axis3.position(pct) - 0.7*Controller1.Axis1.position()), pct);
      backLeft.spin(fwd, nja_md*(Controller1.Axis3.position(pct) + 0.7*Controller1.Axis1.position()), pct);
      backRight.spin(fwd, nja_md*(Controller1.Axis3.position(pct) - 0.7*Controller1.Axis1.position()), pct);
    }
 
    if (Controller1.ButtonL1.pressing()) { // cycle
      intakeLeft.spin(reverse, intakeSpeed, pct);
      intakeRight.spin(reverse, intakeSpeed, pct);
      indexer.spin(reverse, intakeSpeed, pct);
      shooter.spin(reverse, intakeSpeed, pct);
    } else if (Controller1.ButtonR1.pressing()) {
      intakeLeft.spin(fwd, intakeSpeed, pct);
      intakeRight.spin(fwd, intakeSpeed, pct);
      indexer.spin(fwd, intakeSpeed, pct);
      shooter.spin(fwd, intakeSpeed, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      intakeLeft.spin(fwd, intakeSpeed, pct);
      intakeRight.spin(fwd, intakeSpeed, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      intakeLeft.spin(reverse, intakeSpeed, pct);
      intakeRight.spin(reverse, intakeSpeed, pct);
    } else {
      intakeLeft.stop(brake);
      intakeRight.stop(brake);
      indexer.stop(brake);
      shooter.stop(brake);
    }

    if (Controller1.ButtonLeft.pressing() && Controller1.ButtonDown.pressing()) {
      MENU_MODE = 0;
      SELECTED_AUTON = 0;
    }

    if (Controller1.ButtonB.pressing()) {
      nja_md =  nja_md == 1.0 ? 0.3 : 1.0;
    }

    if (Controller1.ButtonX.pressing() && Controller1.ButtonY.pressing()) {
      autonomous();
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
    if (MENU_MODE != 2) {
      selector();
    }
    ctrlRender();
  }
}
