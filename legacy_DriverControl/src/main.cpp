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

float * strafeMotorValues (std::pair<float, float> axes) {
  // TODO: justify max motor values to 100
  // use static multiplier or some fancy algebra idgaf

  int strafeQuadrant = quadrant[{axes.first < 0 ? 0: 1, axes.second < 0 ? 0: 1}];

  float strafeHeading;
  if (strafeQuadrant == 1 || strafeQuadrant == 3) {
    strafeHeading = fabs(atan(axes.second / axes.first))
                      + ((strafeQuadrant-1)*(PI/2));
  } else {
    strafeHeading = fabs(atan(axes.first / axes.second)) 
                      + ((strafeQuadrant-1)*(PI/2));
  }

  float strafeMagnitude = sqrt(pow(axes.first, 2) + pow(axes.second, 2));

  float * motorValues = new float[4] {
    static_cast<float>(round(strafeMagnitude * cos((3 * PI / 4) + strafeHeading))), // front left
    static_cast<float>(round(strafeMagnitude * cos ((3 * PI / 4) - strafeHeading))), // front right
    static_cast<float>(round((-1 * strafeMagnitude) * cos((3 * PI / 4) - strafeHeading))), // back left 
    static_cast<float>(round((-1 * strafeMagnitude) * cos ((3 * PI / 4) + strafeHeading))) // back right
  };

  return motorValues;
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

    std::pair<float, float> strafeAxes (Controller1.Axis4.position(percent),
                                        Controller1.Axis3.position(percent));

    float * motorVals = strafeMotorValues(strafeAxes);

    topLeft.spin(directionType::fwd, *(motorVals), velocityUnits::pct);
    topRight.spin(directionType::fwd, *(motorVals + 1), velocityUnits::pct);
    bottomLeft.spin(directionType::fwd, *(motorVals + 2), velocityUnits::pct);
    bottomRight.spin(directionType::fwd, *(motorVals + 3), velocityUnits::pct);

    if(Controller1.ButtonR2.pressing()) {
            intakeLeft.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
            intakeRight.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
            intakeRoller.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
        }
    else if(Controller1.ButtonDown.pressing()) {
            intakeLeft.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
            intakeRight.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
            intakeRoller.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
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


    
