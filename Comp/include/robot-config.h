using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor topLeft;
extern motor backLeft;
extern motor topRight;
extern motor backRight;
extern motor intakeLeft;
extern motor indexer;
extern motor shooter;
extern controller Controller1;
extern motor intakeRight;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );