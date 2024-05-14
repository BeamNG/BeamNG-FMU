#ifndef config_h
#define config_h

#include <stdbool.h>
#include <stdint.h>

// define class name and unique id
#define MODEL_IDENTIFIER BeamNG
#define INSTANTIATION_TOKEN "{1AE5E10D-9521-4DE3-80B9-D0EAAA7D5AF1}"

#define CO_SIMULATION
#define MODEL_EXCHANGE

#define GET_FLOAT64
#define SET_FLOAT64
#define GET_INT32
#define SET_INT32
#define GET_BOOLEAN
#define SET_BOOLEAN
#define GET_STRING
#define SET_STRING
#define GET_OUTPUT_DERIVATIVE
#define CS_CONFIGURATE
#define CS_TERMINATE
#define CS_DO_FIXED_STEP

#define FIXED_SOLVER_STEP 0.0005
#define DEFAULT_STOP_TIME 10

typedef enum {
    vr_time,
    vr_throttle,
    vr_throttleInput,
    vr_brake,
    vr_brakeInput,
    vr_clutch,
    vr_clutchInput,
    vr_parkingbrake,
    vr_parkingbrakeInput,
    vr_steering,
    vr_steeringInput,
    vr_posX,
    vr_posY,
    vr_posZ,
    vr_velX,
    vr_velY,
    vr_velZ,
    vr_groundspeed,
    vr_accX,
    vr_accY,
    vr_accZ,
    vr_roll,
    vr_pitch,
    vr_yaw,
    vr_altitude,
    vr_ignitionLevel,
    vr_gear,
    vr_fuel,
    vr_engineLoad,
    vr_highbeam,
    vr_lowbeam,
    vr_maxrpm,
    vr_reverse,
    vr_rpm,
    vr_signalL,
    vr_signalR,
    vr_wheelspeed,
    vr_wheelFL_angularVelocity,
    vr_wheelFL_wheelSpeed,
    vr_wheelFL_brakingTorque,
    vr_wheelFL_propulsionTorque,
    vr_wheelFL_frictionTorque,
    vr_wheelFL_downForce,
    vr_wheelFR_angularVelocity,
    vr_wheelFR_wheelSpeed,
    vr_wheelFR_brakingTorque,
    vr_wheelFR_propulsionTorque,
    vr_wheelFR_frictionTorque,
    vr_wheelFR_downForce,
    vr_wheelRL_angularVelocity,
    vr_wheelRL_wheelSpeed,
    vr_wheelRL_brakingTorque,
    vr_wheelRL_propulsionTorque,
    vr_wheelRL_frictionTorque,
    vr_wheelRL_downForce,
    vr_wheelRR_angularVelocity,
    vr_wheelRR_wheelSpeed,
    vr_wheelRR_brakingTorque,
    vr_wheelRR_propulsionTorque,
    vr_wheelRR_frictionTorque,
    vr_wheelRR_downForce,
    vr_input_throttleInput,
    vr_input_brakeInput,
    vr_input_steeringInput,
    vr_input_gear,
    vr_input_wheelFL_brakingTorque,
    vr_input_wheelFL_propulsionTorque,
    vr_input_wheelFR_brakingTorque,
    vr_input_wheelFR_propulsionTorque,
    vr_input_wheelRL_brakingTorque,
    vr_input_wheelRL_propulsionTorque,
    vr_input_wheelRR_brakingTorque,
    vr_input_wheelRR_propulsionTorque,
    vr_input_driveMode,
    vr_socket_inPort,
    vr_socket_inAddress,
    vr_socket_outPort,
    vr_socket_outAddress,
} ValueReference;

typedef struct {
    double throttle;
    double throttleInput;
    double brake;
    double brakeInput;
    double clutch;
    double clutchInput;
    double parkingbrake;
    double parkingbrakeInput;
    double steering;
    double steeringInput;
    double posX;
    double posY;
    double posZ;
    double velX;
    double velY;
    double velZ;
    double groundspeed;
    double accX;
    double accY;
    double accZ;
    double roll;
    double pitch;
    double yaw;
    double altitude;
    int32_t ignitionLevel;
    int32_t gear;
    double fuel;
    double engineLoad;
    bool highbeam;
    bool lowbeam;
    double maxrpm;
    bool reverse;
    double rpm;
    bool signalL;
    bool signalR;
    double wheelspeed;
    double wheelFL_angularVelocity;
    double wheelFL_wheelSpeed;
    double wheelFL_brakingTorque;
    double wheelFL_propulsionTorque;
    double wheelFL_frictionTorque;
    double wheelFL_downForce;
    double wheelFR_angularVelocity;
    double wheelFR_wheelSpeed;
    double wheelFR_brakingTorque;
    double wheelFR_propulsionTorque;
    double wheelFR_frictionTorque;
    double wheelFR_downForce;
    double wheelRL_angularVelocity;
    double wheelRL_wheelSpeed;
    double wheelRL_brakingTorque;
    double wheelRL_propulsionTorque;
    double wheelRL_frictionTorque;
    double wheelRL_downForce;
    double wheelRR_angularVelocity;
    double wheelRR_wheelSpeed;
    double wheelRR_brakingTorque;
    double wheelRR_propulsionTorque;
    double wheelRR_frictionTorque;
    double wheelRR_downForce;

    double input_throttleInput;
    double input_brakeInput;
    double input_steeringInput;
    int32_t input_gear;
    double input_wheelFL_brakingTorque;
    double input_wheelFL_propulsionTorque;
    double input_wheelFR_brakingTorque;
    double input_wheelFR_propulsionTorque;
    double input_wheelRL_brakingTorque;
    double input_wheelRL_propulsionTorque;
    double input_wheelRR_brakingTorque;
    double input_wheelRR_propulsionTorque;
    bool input_driveMode;

    int32_t socket_inPort;
    char socket_inAddress[46];
    int32_t socket_outPort;
    char socket_outAddress[46];
} ModelData;

#endif /* config_h */
