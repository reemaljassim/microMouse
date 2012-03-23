///
/// @file       mouse.h
/// @author     Kyeong Soo (Joseph) Kim <k.s.kim@swansea.ac.uk>
/// @date       2012-02-21
///
/// @brief      Declares system-wide types, macros, variables, and functions
///             for the micro mouse program.
///
/// @remarks    This program is based on Dr Tim Davies' assembly version of
///             micro mouse program and the C port of it by Mr Gareth Evans.
///
/// @copyright  Copyright (C) 2012 Swansea University. All rights reserved.
///
/// @copyright  This software is written and distributed under the GNU General
///             Public License Version 2 (http://www.gnu.org/licenses/gpl-2.0.html).
///             You must not remove this notice, or any other, from this software.
///


#ifndef _MICRO_MOUSE_H	/// to avoid duplicate inclusion of the same header file
#define _MICRO_MOUSE_H


#include <hidef.h> /// for EnableInterrupts macro
#include "derivative.h" /// include peripheral declarations


// avoid duplicate definition of global variables
#ifdef MAIN_PROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif


//------------------------------------------------------------------------------
//  Data types
//------------------------------------------------------------------------------
typedef enum {
    MOUSE_MODE_READY,
    MOUSE_MODE_OBSTACLE_AVOIDING,
    MOUSE_MODE_LINE_FOLLOWING,
    MOUSE_MODE_COMBAT,
    MOUSE_MODE_DEBUG
} MouseMode;

typedef enum {
    MOUSE_STATUS_FORWARD,
    MOUSE_STATUS_REVERSE,
    MOUSE_STATUS_STOP,
    MOUSE_STATUS_TURNLEFT,
    MOUSE_STATUS_TURNRIGHT,
    MOUSE_STATUS_TURNAROUND
} MouseStatus;

typedef enum {
    MOUSE_ACTION_FORWARD,
    MOUSE_ACTION_REVERSE,
    MOUSE_ACTION_STOP,
    MOUSE_ACTION_TURNLEFT,
    MOUSE_ACTION_TURNRIGHT,
    MOUSE_ACTION_TURNAROUND
} MouseAction;

typedef enum {
    MOTOR_LEFT,
    MOTOR_RIGHT
} Motor;

typedef enum {
    MOTOR_STATUS_FORWARD,
    MOTOR_STATUS_REVERSE,
    MOTOR_STATUS_STOP
} MotorStatus;

typedef enum {
    MOTOR_ACTION_FORWARD,
    MOTOR_ACTION_REVERSE,
    MOTOR_ACTION_STOP
} MotorAction;


//------------------------------------------------------------------------------
//  Macros and global constants
//------------------------------------------------------------------------------
/// @name Touch Bar Switches
/// We assume that PTAD2 and PTAD1 are connected to front touch
/// bars left and right, respectively
//@{
#define touchBarFrontLeft   PTAD_PTAD2
#define touchBarFrontRight  PTAD_PTAD1
//@}

/// @name IR sensors
/// We assume that PTAD7 and PTAD6 are connected to front infrared sensors
/// left and right, respectively
//@{
#define infraredFrontLeft   PTAD_PTAD7
#define infraredFrontRight  PTAD_PTAD6
//@}

/// System specific
#define busClock        2   ///< system bus clock in MHz

/// @name Motor speed control
//@{
#define s1  0x1388
#define s2  0x2222
#define f   0xFFFF
#define pwmPeriod       10  ///< period of PWM signal in ms
#define controlPeriod   50  ///< period of motor speed control in ms
#define defaultSpeed    25  ///< default speed in terms of percentage duty cycle (e.g., 100% for full speed)
//@}


//------------------------------------------------------------------------------
//  Variables
//------------------------------------------------------------------------------
EXTERN MouseMode mouseMode;     ///< operation mode of mouse
EXTERN MouseStatus mouseStatus;	///< status of mouse
EXTERN MotorStatus leftMotor;   ///< status of left motor
EXTERN MotorStatus rightMotor;  ///< status of right motor

// Motor speed control
EXTERN int diffLeft;            ///< difference between two consecutive counter values for left motor
EXTERN int diffRight;           ///< difference between two consecutive counter values for right motor
EXTERN int travelDistance;      ///< distance to travel; one unit is approximately 0.5 mm
EXTERN int scaleFactor;         ///< scale factor used in motor speed control
EXTERN int nomSpeed;
EXTERN int pwLeft;
EXTERN int pwRight;
EXTERN int pwMax;
EXTERN int pwMin;


//------------------------------------------------------------------------------
//  Functions
//------------------------------------------------------------------------------
/// @name Functions for mouse
//@{
void AvoidObstacle();
void ControlMouse(MouseAction action);
void Debug();
//@}

/// @name Functions for motors
//@{
void ControlMotor(Motor motor, MotorAction action);
void ControlSpeed();
//@}

/// @name Interrupt service routines (ISRs)
//@{
interrupt VectorNumber_Vkeyboard1 void intSW3_4();
interrupt VectorNumber_Vtpm1ovf void intTPM1OVF();
//@}

/// @name Funcion for serial communicaiton through SCI
//@{
void SCISetup();
byte SCIReceiveChar();
void SCISendChar(char ch);
void SCISendStr(char *str);
void SCIDisplayPrompt();
void SCISendNewline();
//@}


/// @name Misc. functions
//@{
byte BitSet(byte Bit_position, byte Var_old);
byte BitClear(byte Bit_position, byte Var_old);
void Delay(int);
//@}


#endif	// _MICRO_MOUSE_H
