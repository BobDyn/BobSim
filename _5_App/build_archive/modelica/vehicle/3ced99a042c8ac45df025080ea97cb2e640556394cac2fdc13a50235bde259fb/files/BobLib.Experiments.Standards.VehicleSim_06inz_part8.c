#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/*
equation index: 5530
type: SIMPLE_ASSIGN
leftSteerAngle = -atan(chassis.leftWheelVector[2] / chassis.leftWheelVector[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5530(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5530};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10222]] /* leftSteerAngle variable */) = (-atan(DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10121]] /* chassis.leftWheelVector[2] variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10120]] /* chassis.leftWheelVector[1] variable */),"chassis.leftWheelVector[1]",equationIndexes)));
  threadData->lastEquationSolved = 5530;
}

/*
equation index: 5531
type: SIMPLE_ASSIGN
chassis.avgSteerAngle = 0.5 * (leftSteerAngle + rightSteerAngle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5531(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5531};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2299]] /* chassis.avgSteerAngle variable */) = (0.5) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10222]] /* leftSteerAngle variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10252]] /* rightSteerAngle variable */));
  threadData->lastEquationSolved = 5531;
}

/*
equation index: 5532
type: SIMPLE_ASSIGN
steerExcess = chassis.avgSteerAngle + (-1.5494) * yawVel / max(chassis.vehicleSpeed, 0.1)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5532(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5532};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10278]] /* steerExcess variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2299]] /* chassis.avgSteerAngle variable */) + (-1.5494) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */),fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10138]] /* chassis.vehicleSpeed variable */),0.1),"max(chassis.vehicleSpeed, 0.1)",equationIndexes));
  threadData->lastEquationSolved = 5532;
}

/*
equation index: 5533
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameFL.r_0[1] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.wheelVelSensor.der1[1].u - chassis.detailedChassis.frameFL.R.T[3,1] * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5533(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5533};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6071]] /* chassis.detailedChassis.frameFL.r_0[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3273]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.wheelVelSensor.der1[1].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3219]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5533;
}

/*
equation index: 5534
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[3,1] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameFL.R.T[1,1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameFL.R.T[2,1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameFL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5534(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5534};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3266]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[3,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3168]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3169]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3170]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5534;
}

/*
equation index: 5535
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,1] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameFL.R.T[1,1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameFL.R.T[2,1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameFL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5535(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5535};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3264]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3165]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3166]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3167]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5535;
}

/*
equation index: 5536
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_spin[1] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5536(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5536};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3080]] /* chassis.detailedChassis.frAxleDW.leftTire.e_spin[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3264]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,1] variable */);
  threadData->lastEquationSolved = 5536;
}

/*
equation index: 5537
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[1,1] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameFL.R.T[1,1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameFL.R.T[2,1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameFL.R.T[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5537(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5537};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3262]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[1,1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3162]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3163]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3164]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */));
  threadData->lastEquationSolved = 5537;
}

/*
equation index: 5538
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[2] = chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] + (-0.0029972) * chassis.detailedChassis.frameFL.R.T[1,2] + 0.04311976745599999 * chassis.detailedChassis.frameFL.R.T[2,2] + 0.08590279999999999 * chassis.detailedChassis.frameFL.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5538(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5538};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3485]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2648]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[2] DUMMY_STATE */) + (-0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6060]] /* chassis.detailedChassis.frameFL.R.T[1,2] DUMMY_STATE */)) + (0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6063]] /* chassis.detailedChassis.frameFL.R.T[2,2] DUMMY_STATE */)) + (0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6066]] /* chassis.detailedChassis.frameFL.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 5538;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32714(DATA *data, threadData_t *threadData);


/*
equation index: 5540
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameFL.r_0[2] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.wheelVelSensor.der1[2].u - chassis.detailedChassis.frameFL.R.T[3,2] * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5540(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5540};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6072]] /* chassis.detailedChassis.frameFL.r_0[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3274]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.wheelVelSensor.der1[2].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6066]] /* chassis.detailedChassis.frameFL.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3219]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5540;
}

/*
equation index: 5541
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[3,2] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameFL.R.T[1,2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameFL.R.T[2,2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameFL.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5541(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5541};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3267]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[3,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3168]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6060]] /* chassis.detailedChassis.frameFL.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3169]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6063]] /* chassis.detailedChassis.frameFL.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3170]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6066]] /* chassis.detailedChassis.frameFL.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 5541;
}

/*
equation index: 5542
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,2] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameFL.R.T[1,2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameFL.R.T[2,2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameFL.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5542(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5542};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3265]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3165]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6060]] /* chassis.detailedChassis.frameFL.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3166]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6063]] /* chassis.detailedChassis.frameFL.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3167]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6066]] /* chassis.detailedChassis.frameFL.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 5542;
}

/*
equation index: 5543
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_spin[2] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5543(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5543};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3081]] /* chassis.detailedChassis.frAxleDW.leftTire.e_spin[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3265]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[2,2] variable */);
  threadData->lastEquationSolved = 5543;
}

/*
equation index: 5544
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[1,2] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameFL.R.T[1,2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameFL.R.T[2,2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameFL.R.T[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5544(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5544};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3263]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.T[1,2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3162]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6060]] /* chassis.detailedChassis.frameFL.R.T[1,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3163]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6063]] /* chassis.detailedChassis.frameFL.R.T[2,2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3164]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6066]] /* chassis.detailedChassis.frameFL.R.T[3,2] DUMMY_STATE */));
  threadData->lastEquationSolved = 5544;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32682(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32683(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32684(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32685(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32686(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32687(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32689(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32688(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32690(DATA *data, threadData_t *threadData);


/*
equation index: 5554
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_b_a1[1] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[1] * (chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5554(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5554};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2974]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_b_a1[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2965]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[1] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2963]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3059]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2964]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3060]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength",equationIndexes));
  threadData->lastEquationSolved = 5554;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32691(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32692(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32709(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32705(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32701(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32697(DATA *data, threadData_t *threadData);


/*
equation index: 5561
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_b_a1[3] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[3] * (chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength - chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[1] / (chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[1] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5561(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5561};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2976]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_b_a1[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2967]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[3] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2963]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3059]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2964]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3060]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2964]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[3] variable */)) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3058]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[1] variable */),((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2965]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[1] variable */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */)),"chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[1] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 5561;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32700(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32699(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32698(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32693(DATA *data, threadData_t *threadData);


/*
equation index: 5566
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_b_a1[2] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[2] * (chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[2] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[3] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[3]) / chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength - chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[2] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[1] / (chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[1] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5566(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5566};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2975]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_b_a1[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2966]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[2] variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2963]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3059]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2964]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3060]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[3] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength",equationIndexes)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2963]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e2_a[2] variable */)) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3058]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.t_ia_a[1] variable */),((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2965]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[1] variable */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */)),"chassis.detailedChassis.frAxleDW.leftTieRod.rod.e3_a[1] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength",equationIndexes)));
  threadData->lastEquationSolved = 5566;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32696(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32712(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32711(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32710(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32695(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32708(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32707(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32706(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32694(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32704(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32703(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32702(DATA *data, threadData_t *threadData);


/*
equation index: 5579
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[3] = chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] + (-0.0029972) * chassis.detailedChassis.frameFL.R.T[1,3] + 0.04311976745599999 * chassis.detailedChassis.frameFL.R.T[2,3] + 0.08590279999999999 * chassis.detailedChassis.frameFL.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5579(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5579};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3486]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2649]] /* chassis.detailedChassis.frAxleDW.leftLCABody.frame_a.r_0[3] DUMMY_STATE */) + (-0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6061]] /* chassis.detailedChassis.frameFL.R.T[1,3] DUMMY_STATE */)) + (0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6064]] /* chassis.detailedChassis.frameFL.R.T[2,3] DUMMY_STATE */)) + (0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6067]] /* chassis.detailedChassis.frameFL.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 5579;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32678(DATA *data, threadData_t *threadData);


/*
equation index: 5581
type: SIMPLE_ASSIGN
chassis.detailedChassis.frameFL.r_0[3] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.wheelVelSensor.der1[3].u - chassis.detailedChassis.frameFL.R.T[3,3] * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5581(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5581};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6073]] /* chassis.detailedChassis.frameFL.r_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3275]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.wheelVelSensor.der1[3].u DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6067]] /* chassis.detailedChassis.frameFL.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3219]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5581;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32680(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32681(DATA *data, threadData_t *threadData);


/*
equation index: 5584
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_zw[3] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameFL.R.T[1,3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameFL.R.T[2,3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameFL.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5584(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5584};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3097]] /* chassis.detailedChassis.frAxleDW.leftTire.e_zw[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3168]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6061]] /* chassis.detailedChassis.frameFL.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3169]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6064]] /* chassis.detailedChassis.frameFL.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3170]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6067]] /* chassis.detailedChassis.frameFL.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 5584;
}

/*
equation index: 5585
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_zw[2] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameFL.R.T[1,3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameFL.R.T[2,3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameFL.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5585(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5585};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3096]] /* chassis.detailedChassis.frAxleDW.leftTire.e_zw[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3165]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6061]] /* chassis.detailedChassis.frameFL.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3166]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6064]] /* chassis.detailedChassis.frameFL.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3167]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6067]] /* chassis.detailedChassis.frameFL.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 5585;
}

/*
equation index: 5586
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.gamma = asin(max(-1.0, min(1.0, chassis.detailedChassis.frAxleDW.leftTire.e_zw[2])))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5586(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5586};
  modelica_real tmp765;
  tmp765 = fmax(-1.0,fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3096]] /* chassis.detailedChassis.frAxleDW.leftTire.e_zw[2] variable */)));
  if(!(tmp765 >= -1.0 && tmp765 <= 1.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of asin(max(-1.0, min(1.0, chassis.detailedChassis.frAxleDW.leftTire.e_zw[2]))) outside the domain -1.0 <= %g <= 1.0", tmp765);
    }
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3137]] /* chassis.detailedChassis.frAxleDW.leftTire.gamma variable */) = asin(tmp765);
  threadData->lastEquationSolved = 5586;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33247(DATA *data, threadData_t *threadData);


/*
equation index: 5588
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_spin[3] = chassis.detailedChassis.frAxleDW.leftTire.e_zw[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5588(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5588};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3082]] /* chassis.detailedChassis.frAxleDW.leftTire.e_spin[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3096]] /* chassis.detailedChassis.frAxleDW.leftTire.e_zw[2] variable */);
  threadData->lastEquationSolved = 5588;
}

/*
equation index: 5589
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.e_zw[1] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameFL.R.T[1,3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameFL.R.T[2,3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameFL.R.T[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5589(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5589};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3095]] /* chassis.detailedChassis.frAxleDW.leftTire.e_zw[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3162]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6061]] /* chassis.detailedChassis.frameFL.R.T[1,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3163]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6064]] /* chassis.detailedChassis.frameFL.R.T[2,3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3164]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6067]] /* chassis.detailedChassis.frameFL.R.T[3,3] DUMMY_STATE */));
  threadData->lastEquationSolved = 5589;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32234(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32230(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32233(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32232(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32231(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32239(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32235(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32238(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32237(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32236(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32716(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32240(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32747(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32746(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32748(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32753(DATA *data, threadData_t *threadData);


/*
equation index: 5606
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.w_a[1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] * yawVel + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5606(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5606};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3452]] /* chassis.detailedChassis.frAxleDW.leftUCABody.w_a[1] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3841]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3842]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3843]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3850]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5606;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32751(DATA *data, threadData_t *threadData);


/*
equation index: 5608
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.w_a[2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] * yawVel + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5608(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5608};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3453]] /* chassis.detailedChassis.frAxleDW.leftUCABody.w_a[2] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3844]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3845]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3846]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3851]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5608;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32749(DATA *data, threadData_t *threadData);


/*
equation index: 5610
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.w_a[3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] * yawVel + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5610(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5610};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3454]] /* chassis.detailedChassis.frAxleDW.leftUCABody.w_a[3] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3847]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3848]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3849]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3852]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.w[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5610;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32761(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32781(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32762(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32758(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32759(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32760(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32755(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32756(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32805(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32806(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32783(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32784(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32798(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32799(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32800(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32801(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32802(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32814(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32803(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32810(DATA *data, threadData_t *threadData);


/*
equation index: 5631
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5631(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5631};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1081]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3898]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1107]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1092]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3918]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3899]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1101]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1093]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3912]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1150]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1104]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 5631;
}

/*
equation index: 5632
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5632(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5632};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1084]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3900]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1107]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1094]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3918]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3901]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1101]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1095]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3912]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1151]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1104]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 5632;
}

/*
equation index: 5633
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5633(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5633};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1087]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,2]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3902]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1107]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1096]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3918]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3903]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1101]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1097]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3912]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1152]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1104]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[2]) DUMMY_DER */));
  threadData->lastEquationSolved = 5633;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32804(DATA *data, threadData_t *threadData);


/*
equation index: 5635
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5635(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5635};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1080]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3898]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1106]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1092]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3917]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1150]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1103]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 5635;
}

/*
equation index: 5636
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5636(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5636};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1083]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3900]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1106]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1094]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3917]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1151]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1103]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 5636;
}

/*
equation index: 5637
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5637(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5637};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1086]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,1]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3902]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1106]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1096]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3917]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1152]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1103]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[1]) DUMMY_DER */));
  threadData->lastEquationSolved = 5637;
}

/*
equation index: 5638
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5638(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5638};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1082]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[1,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3898]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1108]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1092]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3919]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3899]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1102]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1093]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[1,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3913]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1150]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1105]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 5638;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32822(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32827(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32832(DATA *data, threadData_t *threadData);


/*
equation index: 5642
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5642(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5642};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1085]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[2,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3900]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1108]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1094]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3919]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3901]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1102]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1095]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[2,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3913]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1151]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1105]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 5642;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32821(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32826(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32831(DATA *data, threadData_t *threadData);


/*
equation index: 5646
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5646(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5646};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1088]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia.T[3,3]) DUMMY_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3902]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1108]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1096]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,1]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3919]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_a[3] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3903]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1102]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1097]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.R_rel_ia2.T[3,2]) DUMMY_DER */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3913]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_a[3] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1152]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1105]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_a[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 5646;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32820(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32825(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32830(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32790(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32782(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32787(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32789(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32791(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32788(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32794(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32797(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32793(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32796(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32792(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32795(DATA *data, threadData_t *threadData);


/*
equation index: 5723
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.w</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5723(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5723};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[3690]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.w DUMMY_STATE */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 5723 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 22, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,5723};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 5723 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3690]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.w DUMMY_STATE */) = aux_x[0];

  threadData->lastEquationSolved = 5723;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32893(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32894(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32945(DATA *data, threadData_t *threadData);


/*
equation index: 5727
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.der_rRod_a_L[3] = (chassis.chassisFrame.R.T[3,1] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[1] + chassis.chassisFrame.R.T[3,2] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[2] + chassis.chassisFrame.R.T[3,3] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[3] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[1] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[2]) / chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5727(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5727};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2961]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.der_rRod_a_L[3] variable */) = DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[975]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[976]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[977]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2996]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[1] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2997]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[2] variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength",equationIndexes);
  threadData->lastEquationSolved = 5727;
}

/*
equation index: 5728
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.der_rRod_a_L[2] = (chassis.chassisFrame.R.T[2,1] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[1] + chassis.chassisFrame.R.T[2,2] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[2] + chassis.chassisFrame.R.T[2,3] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[3] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[3] - yawVel * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[1]) / chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5728(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5728};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2960]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.der_rRod_a_L[2] variable */) = DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[975]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[976]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[977]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2998]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[3] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2996]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[1] variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength",equationIndexes);
  threadData->lastEquationSolved = 5728;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32951(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32949(DATA *data, threadData_t *threadData);


/*
equation index: 5731
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.der_rRod_a_L[1] = (chassis.chassisFrame.R.T[1,1] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[1] + chassis.chassisFrame.R.T[1,2] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[2] + chassis.chassisFrame.R.T[1,3] * $DER.chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[3] + yawVel * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[2] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[3]) / chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5731(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5731};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2959]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.der_rRod_a_L[1] variable */) = DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[975]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[976]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[977]] /* der(chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_0[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2997]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[2] variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2998]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rRod_a[3] variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[621]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength PARAM */),"chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodLength",equationIndexes);
  threadData->lastEquationSolved = 5731;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32950(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32956(DATA *data, threadData_t *threadData);


/*
equation index: 5734
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodShape.R.w[3] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[3,3] * yawVel + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5734(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5734};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3010]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodShape.R.w[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2943]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2944]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2945]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2948]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.w[3] variable */);
  threadData->lastEquationSolved = 5734;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32954(DATA *data, threadData_t *threadData);


/*
equation index: 5736
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodShape.R.w[2] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[2,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[2,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[2,3] * yawVel + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5736(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5736};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3009]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodShape.R.w[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2940]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2941]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2942]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2947]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.w[2] variable */);
  threadData->lastEquationSolved = 5736;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32952(DATA *data, threadData_t *threadData);


/*
equation index: 5738
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodShape.R.w[1] = chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[1,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[1,3] * yawVel + chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5738(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5738};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3008]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.rodShape.R.w[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2937]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2938]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2939]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2946]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.R_rel_ia.w[1] variable */);
  threadData->lastEquationSolved = 5738;
}

/*
equation index: 5739
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[1] = chassis.detailedChassis.frAxleDW.leftLCABody.v_0[1] + chassis.detailedChassis.frameFL.R.T[1,1] * (0.08590279999999999 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] + (-0.04311976745599999) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3]) + chassis.detailedChassis.frameFL.R.T[2,1] * ((-0.0029972) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] + (-0.08590279999999999) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1]) + chassis.detailedChassis.frameFL.R.T[3,1] * (0.04311976745599999 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] + 0.0029972 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5739(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5739};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3517]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2689]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[1] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6059]] /* chassis.detailedChassis.frameFL.R.T[1,1] DUMMY_STATE */)) * ((0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3521]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] DUMMY_STATE */)) + (-0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3522]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6062]] /* chassis.detailedChassis.frameFL.R.T[2,1] DUMMY_STATE */)) * ((-0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3522]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] DUMMY_STATE */)) + (-0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3520]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6065]] /* chassis.detailedChassis.frameFL.R.T[3,1] DUMMY_STATE */)) * ((0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3520]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] DUMMY_STATE */)) + (0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3521]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 5739;
}

/*
equation index: 5740
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[1] = chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5740(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5740};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1003]] /* der(chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3517]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5740;
}

/*
equation index: 5741
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.v_g[1] = chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5741(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5741};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3158]] /* chassis.detailedChassis.frAxleDW.leftTire.v_g[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3517]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 5741;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32943(DATA *data, threadData_t *threadData);


/*
equation index: 5743
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[2] = chassis.detailedChassis.frAxleDW.leftLCABody.v_0[2] + chassis.detailedChassis.frameFL.R.T[1,2] * (0.08590279999999999 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] + (-0.04311976745599999) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3]) + chassis.detailedChassis.frameFL.R.T[2,2] * ((-0.0029972) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] + (-0.08590279999999999) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1]) + chassis.detailedChassis.frameFL.R.T[3,2] * (0.04311976745599999 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] + 0.0029972 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5743(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5743};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3518]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2690]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[2] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6060]] /* chassis.detailedChassis.frameFL.R.T[1,2] DUMMY_STATE */)) * ((0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3521]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] DUMMY_STATE */)) + (-0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3522]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6063]] /* chassis.detailedChassis.frameFL.R.T[2,2] DUMMY_STATE */)) * ((-0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3522]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] DUMMY_STATE */)) + (-0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3520]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6066]] /* chassis.detailedChassis.frameFL.R.T[3,2] DUMMY_STATE */)) * ((0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3520]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] DUMMY_STATE */)) + (0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3521]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 5743;
}

/*
equation index: 5744
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[2] = chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5744(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5744};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1004]] /* der(chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3518]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5744;
}

/*
equation index: 5745
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.v_g[2] = chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5745(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5745};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3159]] /* chassis.detailedChassis.frAxleDW.leftTire.v_g[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3518]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 5745;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32940(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32932(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32936(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32934(DATA *data, threadData_t *threadData);


/*
equation index: 5750
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vsx = chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx - chassis.detailedChassis.frAxleDW.leftTire.slipModel.R0 * chassis.detailedChassis.frAxleDW.leftTire.slipModel.omega
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5750(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5750};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3144]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vsx variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3145]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx variable */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3143]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.R0 variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3153]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.omega variable */)));
  threadData->lastEquationSolved = 5750;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32930(DATA *data, threadData_t *threadData);


/*
equation index: 5752
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[3] = chassis.detailedChassis.frAxleDW.leftLCABody.v_0[3] + chassis.detailedChassis.frameFL.R.T[1,3] * (0.08590279999999999 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] + (-0.04311976745599999) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3]) + chassis.detailedChassis.frameFL.R.T[2,3] * ((-0.0029972) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] + (-0.08590279999999999) * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1]) + chassis.detailedChassis.frameFL.R.T[3,3] * (0.04311976745599999 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] + 0.0029972 * chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5752(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5752};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3519]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2691]] /* chassis.detailedChassis.frAxleDW.leftLCABody.v_0[3] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6061]] /* chassis.detailedChassis.frameFL.R.T[1,3] DUMMY_STATE */)) * ((0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3521]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] DUMMY_STATE */)) + (-0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3522]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6064]] /* chassis.detailedChassis.frameFL.R.T[2,3] DUMMY_STATE */)) * ((-0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3522]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[3] DUMMY_STATE */)) + (-0.08590279999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3520]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6067]] /* chassis.detailedChassis.frameFL.R.T[3,3] DUMMY_STATE */)) * ((0.04311976745599999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3520]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[1] DUMMY_STATE */)) + (0.0029972) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3521]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 5752;
}

/*
equation index: 5753
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[3] = chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5753(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5753};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1005]] /* der(chassis.detailedChassis.frAxleDW.leftUnsprungBody.frame_a.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3519]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5753;
}

/*
equation index: 5754
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.v_cp[3] = chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5754(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5754};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3157]] /* chassis.detailedChassis.frAxleDW.leftTire.v_cp[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3519]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.v_0[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 5754;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32926(DATA *data, threadData_t *threadData);


/*
equation index: 5756
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frameFL.r_0[3] = chassis.detailedChassis.frAxleDW.leftTire.v_cp[3] + chassis.detailedChassis.frameFL.R.T[1,3] * (-chassis.detailedChassis.frameFL.R.w[2]) * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s + chassis.detailedChassis.frameFL.R.T[2,3] * chassis.detailedChassis.frameFL.R.w[1] * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5756(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5756};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1421]] /* der(chassis.detailedChassis.frameFL.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3157]] /* chassis.detailedChassis.frAxleDW.leftTire.v_cp[3] variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6061]] /* chassis.detailedChassis.frameFL.R.T[1,3] DUMMY_STATE */)) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6069]] /* chassis.detailedChassis.frameFL.R.w[2] variable */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3219]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6064]] /* chassis.detailedChassis.frameFL.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6068]] /* chassis.detailedChassis.frameFL.R.w[1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3219]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5756;
}

/*
equation index: 5757
type: SIMPLE_ASSIGN
$DER.chassis.ground_1.r_rel_z = $DER.chassis.detailedChassis.frameFL.r_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5757(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5757};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2014]] /* der(chassis.ground_1.r_rel_z) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1421]] /* der(chassis.detailedChassis.frameFL.r_0[3]) DUMMY_DER */);
  threadData->lastEquationSolved = 5757;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32897(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32898(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32899(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32900(DATA *data, threadData_t *threadData);


/*
equation index: 5762
type: SIMPLE_ASSIGN
minTireNormalLoad = min(min(Fz_FL, Fz_FR), min(Fz_RL, Fz_RR))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5762(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5762};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10225]] /* minTireNormalLoad variable */) = fmin(fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2156]] /* Fz_FL variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2157]] /* Fz_FR variable */)),fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2158]] /* Fz_RL variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2159]] /* Fz_RR variable */)));
  threadData->lastEquationSolved = 5762;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32916(DATA *data, threadData_t *threadData);


/*
equation index: 5764
type: SIMPLE_ASSIGN
$whenCondition13 = vcu.useMode == 0 and time > vcu.steerStart and vcu.enableNormalLoadSteerLimiter and minTireNormalLoad <= vcu.tireNormalLoadMin and not $PRE.vcu.rampEndingState
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5764(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5764};
  modelica_boolean tmp766;
  modelica_boolean tmp767;
  tmp766 = Greater(data->localData[0]->timeValue,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6875]] /* vcu.steerStart PARAM */));
  tmp767 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10225]] /* minTireNormalLoad variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6880]] /* vcu.tireNormalLoadMin PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition13 DISCRETE */) = ((((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) && tmp766) && (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[608]] /* vcu.enableNormalLoadSteerLimiter PARAM */)) && tmp767) && (!(data->simulationInfo->booleanVarsPre[50] /* vcu.rampEndingState DISCRETE */)));
  threadData->lastEquationSolved = 5764;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32917(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33248(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32918(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32919(DATA *data, threadData_t *threadData);


/*
equation index: 5769
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.f = chassis.detailedChassis.frAxleDW.leftTire.constantZero.k + chassis.ground_1.f_z
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5769(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5769};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3216]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.f variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[624]] /* chassis.detailedChassis.frAxleDW.leftTire.constantZero.k PARAM */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10065]] /* chassis.ground_1.f_z variable */);
  threadData->lastEquationSolved = 5769;
}

/*
equation index: 5770
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[3] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.f - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.f[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5770(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5770};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3228]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3216]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.f variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3186]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.f[3] variable */);
  threadData->lastEquationSolved = 5770;
}

/*
equation index: 5771
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.f[3] = -chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5771(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5771};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3073]] /* chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.f[3] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3228]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[3] variable */));
  threadData->lastEquationSolved = 5771;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32944(DATA *data, threadData_t *threadData);


/*
equation index: 5773
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.w[3] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] * chassis.detailedChassis.frameFL.R.w[1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] * chassis.detailedChassis.frameFL.R.w[2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] * chassis.detailedChassis.frameFL.R.w[3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5773(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5773};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3270]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.w[3] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3168]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6068]] /* chassis.detailedChassis.frameFL.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3169]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6069]] /* chassis.detailedChassis.frameFL.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3170]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6070]] /* chassis.detailedChassis.frameFL.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3173]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.w[3] variable */);
  threadData->lastEquationSolved = 5773;
}

/*
equation index: 5774
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.w[2] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] * chassis.detailedChassis.frameFL.R.w[1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] * chassis.detailedChassis.frameFL.R.w[2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] * chassis.detailedChassis.frameFL.R.w[3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5774(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5774};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3269]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.w[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3165]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6068]] /* chassis.detailedChassis.frameFL.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3166]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6069]] /* chassis.detailedChassis.frameFL.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3167]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6070]] /* chassis.detailedChassis.frameFL.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3172]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.w[2] variable */);
  threadData->lastEquationSolved = 5774;
}

/*
equation index: 5775
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.w[1] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] * chassis.detailedChassis.frameFL.R.w[1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] * chassis.detailedChassis.frameFL.R.w[2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] * chassis.detailedChassis.frameFL.R.w[3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5775(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5775};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3268]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.voluminousWheel.torus.R.w[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3162]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6068]] /* chassis.detailedChassis.frameFL.R.w[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3163]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6069]] /* chassis.detailedChassis.frameFL.R.w[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3164]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6070]] /* chassis.detailedChassis.frameFL.R.w[3] variable */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3171]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.w[1] variable */);
  threadData->lastEquationSolved = 5775;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32757(DATA *data, threadData_t *threadData);


/*
equation index: 5777
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = (1.0 - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5777(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5777};
  modelica_real tmp768;
  tmp768 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1065]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3]) DUMMY_DER */) = (1.0 - ((tmp768 * tmp768))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 5777;
}

/*
equation index: 5778
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5778(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5778};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1064]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 5778;
}

/*
equation index: 5779
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5779(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5779};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1063]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)))));
  threadData->lastEquationSolved = 5779;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32768(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32767(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32766(DATA *data, threadData_t *threadData);


/*
equation index: 5783
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5783(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5783};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1062]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)))));
  threadData->lastEquationSolved = 5783;
}

/*
equation index: 5784
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = (1.0 - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5784(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5784};
  modelica_real tmp769;
  tmp769 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1061]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2]) DUMMY_DER */) = (1.0 - ((tmp769 * tmp769))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 5784;
}

/*
equation index: 5785
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5785(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5785};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1060]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 5785;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32774(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32773(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32772(DATA *data, threadData_t *threadData);


/*
equation index: 5789
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = (-chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5789(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5789};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1059]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))));
  threadData->lastEquationSolved = 5789;
}

/*
equation index: 5790
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * cos(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5790(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5790};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1058]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1136]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1135]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)))));
  threadData->lastEquationSolved = 5790;
}

/*
equation index: 5791
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = (1.0 - chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * (-sin(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5791(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5791};
  modelica_real tmp770;
  tmp770 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1134]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1057]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1]) DUMMY_DER */) = (1.0 - ((tmp770 * tmp770))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3853]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1069]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */)));
  threadData->lastEquationSolved = 5791;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32780(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32779(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32778(DATA *data, threadData_t *threadData);


/*
equation index: 5795
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.slipModel.v = (-chassis.detailedChassis.frAxleDW.rightTire.slipModel.sigma_alpha) * chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vy / max(abs(chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx), chassis.detailedChassis.frAxleDW.rightTire.slipModel.V_min)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5795(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5795};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.v STATE(1) */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4917]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.sigma_alpha variable */))) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4911]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vy variable */),fmax(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4908]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1870]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.V_min PARAM */)),"max(abs(chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx), chassis.detailedChassis.frAxleDW.rightTire.slipModel.V_min)",equationIndexes));
  threadData->lastEquationSolved = 5795;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33197(DATA *data, threadData_t *threadData);


/*
equation index: 5797
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.alpha = max(min(chassis.detailedChassis.frAxleDW.rightTire.slipModel.alpha_raw, chassis.detailedChassis.frAxleDW.rightTire.slipModel.alpha_max), -chassis.detailedChassis.frAxleDW.rightTire.slipModel.alpha_max)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5797(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5797};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4833]] /* chassis.detailedChassis.frAxleDW.rightTire.alpha variable */) = fmax(fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4912]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.alpha_raw variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1871]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.alpha_max PARAM */)),(-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1871]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.alpha_max PARAM */)));
  threadData->lastEquationSolved = 5797;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33200(DATA *data, threadData_t *threadData);


/*
equation index: 5799
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.slipModel.u = chassis.detailedChassis.frAxleDW.rightTire.slipModel.sigma_kappa * (chassis.detailedChassis.frAxleDW.rightTire.slipModel.R0 * chassis.detailedChassis.frAxleDW.rightTire.slipModel.omega - chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx) / max(abs(chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx), chassis.detailedChassis.frAxleDW.rightTire.slipModel.V_min)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5799(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5799};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[20]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.u STATE(1) */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4918]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.sigma_kappa variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4906]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.R0 variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4916]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.omega variable */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4908]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx variable */),fmax(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4908]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1870]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.V_min PARAM */)),"max(abs(chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx), chassis.detailedChassis.frAxleDW.rightTire.slipModel.V_min)",equationIndexes));
  threadData->lastEquationSolved = 5799;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32147(DATA *data, threadData_t *threadData);


/*
equation index: 5801
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.kappa = max(min(chassis.detailedChassis.frAxleDW.rightTire.slipModel.kappa_raw, chassis.detailedChassis.frAxleDW.rightTire.slipModel.kappa_max), -chassis.detailedChassis.frAxleDW.rightTire.slipModel.kappa_max)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5801(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5801};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4901]] /* chassis.detailedChassis.frAxleDW.rightTire.kappa variable */) = fmax(fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4915]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.kappa_raw variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1872]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.kappa_max PARAM */)),(-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1872]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.kappa_max PARAM */)));
  threadData->lastEquationSolved = 5801;
}

/*
equation index: 5802
type: ALGORITHM

  (chassis.detailedChassis.frAxleDW.rightTire.Fx, chassis.detailedChassis.frAxleDW.rightTire.Fy, chassis.detailedChassis.frAxleDW.rightTire.Mx, chassis.detailedChassis.frAxleDW.rightTire.My, chassis.detailedChassis.frAxleDW.rightTire.Mz, chassis.detailedChassis.frAxleDW.rightTire.t, chassis.detailedChassis.frAxleDW.rightTire.s) := BobLib.Chassis.Suspension.Tires.MF52.Eval(Fz_FR, chassis.detailedChassis.frAxleDW.rightTire.alpha, chassis.detailedChassis.frAxleDW.rightTire.kappa, chassis.detailedChassis.frAxleDW.rightTire.gamma, chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx, chassis.detailedChassis.frAxleDW.rightTire.pTireModel);
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5802(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5802};
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp771;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord tmp772;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp773;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord tmp774;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord tmp775;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord tmp776;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord tmp777;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord tmp778;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord tmp779;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord tmp780;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord tmp781;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord tmp782;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record tmp783;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_wrap_vars(threadData,tmp771, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1855]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.setup.FNOMIN PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1857]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.setup.FZMIN PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1856]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.setup.FZMAX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1858]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.setup.UNLOADED_RADIUS PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_wrap_vars(threadData,tmp772, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1844]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.FNOMIN PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1854]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.UNLOADED_RADIUS PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1845]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.LFZO PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1849]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.PTX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1850]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.PTX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1851]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.PTX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1852]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.PTY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1853]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.PTY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1848]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.PKY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1847]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.LSGKP PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1846]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.relaxation.LSGAL PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_wrap_vars(threadData,tmp773, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1728]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LGAX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1727]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LFZO PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1734]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PCX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1735]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PDX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1736]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PDX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1737]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PDX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1744]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PKX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1745]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PKX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1746]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PKX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1742]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PHX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1743]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PHX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1747]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PVX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1748]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PVX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1738]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PEX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1739]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PEX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1740]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PEX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1741]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.PEX4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1725]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LCX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1731]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LMUX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1730]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LKX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1729]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LHX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1732]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LVX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1726]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LEX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1733]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxPure.LXAL PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_wrap_vars(threadData,tmp774, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1719]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxCombined.RBX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1720]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxCombined.RBX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1721]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxCombined.RCX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1722]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxCombined.REX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1723]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxCombined.REX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1724]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fxCombined.RHX1 PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_wrap_vars(threadData,tmp775, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1765]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LFZO PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1766]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LGAY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1773]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PCY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1774]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PDY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1775]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PDY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1776]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PDY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1784]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PKY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1785]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PKY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1786]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PKY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1781]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PHY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1782]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PHY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1783]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PHY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1787]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PVY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1788]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PVY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1789]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PVY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1790]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PVY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1777]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PEY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1778]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PEY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1779]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PEY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1780]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.PEY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1763]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LCY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1769]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LMUY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1764]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LEY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1768]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LKY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1767]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LHY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1770]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LVY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1772]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LYKA PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1771]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyPure.LVYKA PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_wrap_vars(threadData,tmp776, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1749]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RBY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1750]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RBY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1751]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RBY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1752]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RCY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1753]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.REY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1754]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.REY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1755]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RHY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1756]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RHY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1757]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RVY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1758]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RVY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1759]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RVY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1760]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RVY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1761]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RVY5 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1762]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.fyCombined.RVY6 PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_wrap_vars(threadData,tmp777, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1793]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mxPure.QSX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1794]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mxPure.QSX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1795]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mxPure.QSX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1791]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mxPure.LMX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1792]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mxPure.LVMX PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_wrap_vars(threadData,tmp778);
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_wrap_vars(threadData,tmp779, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1797]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.myPure.QSY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1798]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.myPure.QSY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1799]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.myPure.QSY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1800]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.myPure.QSY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1801]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.myPure.Vref PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1796]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.myPure.LMY PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_wrap_vars(threadData,tmp780);
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_wrap_vars(threadData,tmp781, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1819]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QBZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1821]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QBZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1822]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QBZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1823]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QBZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1824]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QBZ5 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1826]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QCZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1827]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QDZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1828]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QDZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1829]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QDZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1830]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QDZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1835]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QEZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1836]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QEZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1837]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QEZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1838]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QEZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1839]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QEZ5 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1840]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QHZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1841]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QHZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1842]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QHZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1843]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QHZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1825]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QBZ9 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1820]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QBZ10 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1831]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QDZ6 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1832]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QDZ7 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1833]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QDZ8 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1834]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.QDZ9 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1818]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.LTR PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1817]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.LRES PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1815]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.LKY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1816]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.LMUY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1814]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzPure.LGAZ PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_wrap_vars(threadData,tmp782, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1810]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.SSZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1811]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.SSZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1812]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.SSZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1813]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.SSZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1804]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.RVY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1805]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.RVY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1806]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.RVY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1807]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.RVY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1808]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.RVY5 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1809]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.RVY6 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1802]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.LS PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1803]] /* chassis.detailedChassis.frAxleDW.rightTire.pTireModel.mzCombined.LVYKA PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_wrap_vars(threadData,tmp783, tmp771, tmp772, tmp773, tmp774, tmp775, tmp776, tmp777, tmp778, tmp779, tmp780, tmp781, tmp782);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4828]] /* chassis.detailedChassis.frAxleDW.rightTire.Fx variable */) = omc_BobLib_Chassis_Suspension_Tires_MF52_Eval(threadData, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2157]] /* Fz_FR variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4833]] /* chassis.detailedChassis.frAxleDW.rightTire.alpha variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4901]] /* chassis.detailedChassis.frAxleDW.rightTire.kappa variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4900]] /* chassis.detailedChassis.frAxleDW.rightTire.gamma variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4908]] /* chassis.detailedChassis.frAxleDW.rightTire.slipModel.Vx variable */), tmp783 ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4829]] /* chassis.detailedChassis.frAxleDW.rightTire.Fy variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4830]] /* chassis.detailedChassis.frAxleDW.rightTire.Mx variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4831]] /* chassis.detailedChassis.frAxleDW.rightTire.My variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4832]] /* chassis.detailedChassis.frAxleDW.rightTire.Mz variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4919]] /* chassis.detailedChassis.frAxleDW.rightTire.t variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4902]] /* chassis.detailedChassis.frAxleDW.rightTire.s variable */));
  threadData->lastEquationSolved = 5802;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33202(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33203(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33204(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33205(DATA *data, threadData_t *threadData);


/*
equation index: 5807
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[1] = chassis.detailedChassis.frAxleDW.rightTire.Fx - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.f[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5807(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5807};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4989]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4828]] /* chassis.detailedChassis.frAxleDW.rightTire.Fx variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4947]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.f[1] variable */);
  threadData->lastEquationSolved = 5807;
}

/*
equation index: 5808
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.f[1] = -chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5808(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5808};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4834]] /* chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.f[1] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4989]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[1] variable */));
  threadData->lastEquationSolved = 5808;
}

/*
equation index: 5809
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.frame_a.t[2] = chassis.detailedChassis.frAxleDW.rightTire.Fx * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s - chassis.detailedChassis.frAxleDW.rightTire.My
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5809(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5809};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4981]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.frame_a.t[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4828]] /* chassis.detailedChassis.frAxleDW.rightTire.Fx variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4982]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4831]] /* chassis.detailedChassis.frAxleDW.rightTire.My variable */);
  threadData->lastEquationSolved = 5809;
}

/*
equation index: 5810
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[2] = (-chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.frame_a.t[2]) - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.t[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5810(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5810};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4993]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[2] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4981]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.frame_a.t[2] variable */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4951]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.t[2] variable */);
  threadData->lastEquationSolved = 5810;
}

/*
equation index: 5811
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.t[2] = -chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5811(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5811};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4838]] /* chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.t[2] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4993]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[2] variable */));
  threadData->lastEquationSolved = 5811;
}

/*
equation index: 5812
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.frame_a.t[1] = (-chassis.detailedChassis.frAxleDW.rightTire.Mx) - chassis.detailedChassis.frAxleDW.rightTire.Fy * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5812(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5812};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4980]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.frame_a.t[1] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4830]] /* chassis.detailedChassis.frAxleDW.rightTire.Mx variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4829]] /* chassis.detailedChassis.frAxleDW.rightTire.Fy variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4982]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5812;
}

/*
equation index: 5813
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[1] = (-chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.frame_a.t[1]) - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.t[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5813(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5813};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4992]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[1] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4980]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.prismatic_z.frame_a.t[1] variable */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4950]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.t[1] variable */);
  threadData->lastEquationSolved = 5813;
}

/*
equation index: 5814
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.t[1] = -chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5814(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5814};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4837]] /* chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.t[1] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4992]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[1] variable */));
  threadData->lastEquationSolved = 5814;
}

/*
equation index: 5815
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[2] = chassis.detailedChassis.frAxleDW.rightTire.Fy - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.f[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5815(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5815};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4990]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4829]] /* chassis.detailedChassis.frAxleDW.rightTire.Fy variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4948]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.f[2] variable */);
  threadData->lastEquationSolved = 5815;
}

/*
equation index: 5816
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.f[2] = -chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5816(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5816};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4835]] /* chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.f[2] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4990]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.f[2] variable */));
  threadData->lastEquationSolved = 5816;
}

/*
equation index: 5817
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[3] = chassis.detailedChassis.frAxleDW.rightTire.Mz - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.t[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5817(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5817};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4994]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4832]] /* chassis.detailedChassis.frAxleDW.rightTire.Mz variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4952]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.frame_a.t[3] variable */);
  threadData->lastEquationSolved = 5817;
}

/*
equation index: 5818
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.t[3] = -chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5818(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5818};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4839]] /* chassis.detailedChassis.frAxleDW.rightTire.chassisFrame.t[3] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4994]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.toHub.frame_b.t[3] variable */));
  threadData->lastEquationSolved = 5818;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32146(DATA *data, threadData_t *threadData);


/*
equation index: 5820
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.slipModel.v = (-chassis.detailedChassis.frAxleDW.leftTire.slipModel.sigma_alpha) * chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vy / max(abs(chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx), chassis.detailedChassis.frAxleDW.leftTire.slipModel.V_min)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5820(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5820};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.v STATE(1) */) = ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3154]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.sigma_alpha variable */))) * (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3148]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vy variable */),fmax(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3145]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[781]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.V_min PARAM */)),"max(abs(chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx), chassis.detailedChassis.frAxleDW.leftTire.slipModel.V_min)",equationIndexes));
  threadData->lastEquationSolved = 5820;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33249(DATA *data, threadData_t *threadData);


/*
equation index: 5822
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.alpha = max(min(chassis.detailedChassis.frAxleDW.leftTire.slipModel.alpha_raw, chassis.detailedChassis.frAxleDW.leftTire.slipModel.alpha_max), -chassis.detailedChassis.frAxleDW.leftTire.slipModel.alpha_max)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5822(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5822};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3070]] /* chassis.detailedChassis.frAxleDW.leftTire.alpha variable */) = fmax(fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3149]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.alpha_raw variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[782]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.alpha_max PARAM */)),(-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[782]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.alpha_max PARAM */)));
  threadData->lastEquationSolved = 5822;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33252(DATA *data, threadData_t *threadData);


/*
equation index: 5824
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.slipModel.u = chassis.detailedChassis.frAxleDW.leftTire.slipModel.sigma_kappa * (chassis.detailedChassis.frAxleDW.leftTire.slipModel.R0 * chassis.detailedChassis.frAxleDW.leftTire.slipModel.omega - chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx) / max(abs(chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx), chassis.detailedChassis.frAxleDW.leftTire.slipModel.V_min)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5824(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5824};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.u STATE(1) */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3155]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.sigma_kappa variable */)) * (DIVISION_SIM(((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3143]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.R0 variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3153]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.omega variable */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3145]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx variable */),fmax(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3145]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[781]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.V_min PARAM */)),"max(abs(chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx), chassis.detailedChassis.frAxleDW.leftTire.slipModel.V_min)",equationIndexes));
  threadData->lastEquationSolved = 5824;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32937(DATA *data, threadData_t *threadData);


/*
equation index: 5826
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.kappa = max(min(chassis.detailedChassis.frAxleDW.leftTire.slipModel.kappa_raw, chassis.detailedChassis.frAxleDW.leftTire.slipModel.kappa_max), -chassis.detailedChassis.frAxleDW.leftTire.slipModel.kappa_max)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5826(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5826};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3138]] /* chassis.detailedChassis.frAxleDW.leftTire.kappa variable */) = fmax(fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3152]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.kappa_raw variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[783]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.kappa_max PARAM */)),(-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[783]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.kappa_max PARAM */)));
  threadData->lastEquationSolved = 5826;
}

/*
equation index: 5827
type: ALGORITHM

  (chassis.detailedChassis.frAxleDW.leftTire.Fx, chassis.detailedChassis.frAxleDW.leftTire.Fy, chassis.detailedChassis.frAxleDW.leftTire.Mx, chassis.detailedChassis.frAxleDW.leftTire.My, chassis.detailedChassis.frAxleDW.leftTire.Mz, chassis.detailedChassis.frAxleDW.leftTire.t, chassis.detailedChassis.frAxleDW.leftTire.s) := BobLib.Chassis.Suspension.Tires.MF52.Eval(Fz_FL, chassis.detailedChassis.frAxleDW.leftTire.alpha, chassis.detailedChassis.frAxleDW.leftTire.kappa, chassis.detailedChassis.frAxleDW.leftTire.gamma, chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx, chassis.detailedChassis.frAxleDW.leftTire.pTireModel);
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5827(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5827};
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord tmp784;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord tmp785;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord tmp786;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord tmp787;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord tmp788;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord tmp789;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord tmp790;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord tmp791;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord tmp792;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord tmp793;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord tmp794;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord tmp795;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record tmp796;
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_SetupRecord_wrap_vars(threadData,tmp784, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[766]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.setup.FNOMIN PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[768]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.setup.FZMIN PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[767]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.setup.FZMAX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[769]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.setup.UNLOADED_RADIUS PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_RelaxationRecord_wrap_vars(threadData,tmp785, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[755]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.FNOMIN PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[765]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.UNLOADED_RADIUS PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[756]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.LFZO PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[760]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.PTX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[761]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.PTX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[762]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.PTX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[763]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.PTY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[764]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.PTY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[759]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.PKY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[758]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.LSGKP PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[757]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.relaxation.LSGAL PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FxPureRecord_wrap_vars(threadData,tmp786, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[639]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LGAX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[638]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LFZO PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[645]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PCX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[646]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PDX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[647]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PDX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[648]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PDX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[655]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PKX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[656]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PKX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[657]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PKX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[653]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PHX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[654]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PHX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[658]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PVX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[659]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PVX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[649]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PEX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[650]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PEX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[651]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PEX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[652]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.PEX4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[636]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LCX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[642]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LMUX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[641]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LKX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[640]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LHX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[643]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LVX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[637]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LEX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[644]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxPure.LXAL PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FxCombinedRecord_wrap_vars(threadData,tmp787, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[630]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxCombined.RBX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[631]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxCombined.RBX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[632]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxCombined.RCX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[633]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxCombined.REX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[634]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxCombined.REX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[635]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fxCombined.RHX1 PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_FyPureRecord_wrap_vars(threadData,tmp788, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[676]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LFZO PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[677]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LGAY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[684]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PCY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[685]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PDY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[686]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PDY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[687]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PDY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[695]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PKY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[696]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PKY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[697]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PKY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[692]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PHY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[693]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PHY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[694]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PHY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[698]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PVY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[699]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PVY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[700]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PVY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[701]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PVY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[688]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PEY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[689]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PEY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[690]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PEY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[691]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.PEY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[674]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LCY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[680]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LMUY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[675]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LEY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[679]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LKY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[678]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LHY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[681]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LVY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[683]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LYKA PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[682]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyPure.LVYKA PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_FyCombinedRecord_wrap_vars(threadData,tmp789, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[660]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RBY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[661]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RBY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[662]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RBY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[663]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RCY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[664]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.REY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[665]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.REY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[666]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RHY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[667]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RHY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[668]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RVY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[669]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RVY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[670]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RVY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[671]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RVY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[672]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RVY5 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[673]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.fyCombined.RVY6 PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MxPureRecord_wrap_vars(threadData,tmp790, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[704]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mxPure.QSX1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[705]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mxPure.QSX2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[706]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mxPure.QSX3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[702]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mxPure.LMX PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[703]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mxPure.LVMX PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MxCombinedRecord_wrap_vars(threadData,tmp791);
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MyPureRecord_wrap_vars(threadData,tmp792, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[708]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.myPure.QSY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[709]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.myPure.QSY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[710]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.myPure.QSY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[711]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.myPure.QSY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[712]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.myPure.Vref PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[707]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.myPure.LMY PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MyCombinedRecord_wrap_vars(threadData,tmp793);
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_PureSlip_MzPureRecord_wrap_vars(threadData,tmp794, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[730]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QBZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[732]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QBZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[733]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QBZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[734]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QBZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[735]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QBZ5 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[737]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QCZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[738]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QDZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[739]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QDZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[740]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QDZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[741]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QDZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[746]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QEZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[747]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QEZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[748]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QEZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[749]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QEZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[750]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QEZ5 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[751]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QHZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[752]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QHZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[753]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QHZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[754]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QHZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[736]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QBZ9 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[731]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QBZ10 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[742]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QDZ6 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[743]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QDZ7 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[744]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QDZ8 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[745]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.QDZ9 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[729]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.LTR PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[728]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.LRES PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[726]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.LKY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[727]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.LMUY PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[725]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzPure.LGAZ PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_CombinedSlip_MzCombinedRecord_wrap_vars(threadData,tmp795, (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[721]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.SSZ1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[722]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.SSZ2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[723]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.SSZ3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[724]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.SSZ4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[715]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.RVY1 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[716]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.RVY2 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[717]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.RVY3 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[718]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.RVY4 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[719]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.RVY5 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[720]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.RVY6 PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[713]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.LS PARAM */), (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[714]] /* chassis.detailedChassis.frAxleDW.leftTire.pTireModel.mzCombined.LVYKA PARAM */));
  BobLib_Records_VehicleRecord_Chassis_Suspension_Templates_Tire_MF52_MF52Record_wrap_vars(threadData,tmp796, tmp784, tmp785, tmp786, tmp787, tmp788, tmp789, tmp790, tmp791, tmp792, tmp793, tmp794, tmp795);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3065]] /* chassis.detailedChassis.frAxleDW.leftTire.Fx variable */) = omc_BobLib_Chassis_Suspension_Tires_MF52_Eval(threadData, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2156]] /* Fz_FL variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3070]] /* chassis.detailedChassis.frAxleDW.leftTire.alpha variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3138]] /* chassis.detailedChassis.frAxleDW.leftTire.kappa variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3137]] /* chassis.detailedChassis.frAxleDW.leftTire.gamma variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3145]] /* chassis.detailedChassis.frAxleDW.leftTire.slipModel.Vx variable */), tmp796 ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3066]] /* chassis.detailedChassis.frAxleDW.leftTire.Fy variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3067]] /* chassis.detailedChassis.frAxleDW.leftTire.Mx variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3068]] /* chassis.detailedChassis.frAxleDW.leftTire.My variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3069]] /* chassis.detailedChassis.frAxleDW.leftTire.Mz variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3156]] /* chassis.detailedChassis.frAxleDW.leftTire.t variable */) ,&(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3139]] /* chassis.detailedChassis.frAxleDW.leftTire.s variable */));
  threadData->lastEquationSolved = 5827;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33257(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33258(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33259(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_33260(DATA *data, threadData_t *threadData);


/*
equation index: 5832
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[2] = chassis.detailedChassis.frAxleDW.leftTire.Fy - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.f[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5832(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5832};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3227]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3066]] /* chassis.detailedChassis.frAxleDW.leftTire.Fy variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3185]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.f[2] variable */);
  threadData->lastEquationSolved = 5832;
}

/*
equation index: 5833
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.f[2] = -chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5833(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5833};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3072]] /* chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.f[2] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3227]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[2] variable */));
  threadData->lastEquationSolved = 5833;
}

/*
equation index: 5834
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[1] = chassis.detailedChassis.frAxleDW.leftTire.Fx - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.f[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5834(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5834};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3226]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3065]] /* chassis.detailedChassis.frAxleDW.leftTire.Fx variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3184]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.f[1] variable */);
  threadData->lastEquationSolved = 5834;
}

/*
equation index: 5835
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.f[1] = -chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5835(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5835};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3071]] /* chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.f[1] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3226]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.f[1] variable */));
  threadData->lastEquationSolved = 5835;
}

/*
equation index: 5836
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.frame_a.t[2] = chassis.detailedChassis.frAxleDW.leftTire.Fx * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s - chassis.detailedChassis.frAxleDW.leftTire.My
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5836(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5836};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3218]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.frame_a.t[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3065]] /* chassis.detailedChassis.frAxleDW.leftTire.Fx variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3219]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3068]] /* chassis.detailedChassis.frAxleDW.leftTire.My variable */);
  threadData->lastEquationSolved = 5836;
}

/*
equation index: 5837
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[2] = (-chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.frame_a.t[2]) - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.t[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5837(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5837};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3230]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[2] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3218]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.frame_a.t[2] variable */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3188]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.t[2] variable */);
  threadData->lastEquationSolved = 5837;
}

/*
equation index: 5838
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.t[2] = -chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5838(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5838};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3075]] /* chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.t[2] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3230]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[2] variable */));
  threadData->lastEquationSolved = 5838;
}

/*
equation index: 5839
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[3] = chassis.detailedChassis.frAxleDW.leftTire.Mz - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.t[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5839(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5839};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3231]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3069]] /* chassis.detailedChassis.frAxleDW.leftTire.Mz variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3189]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.t[3] variable */);
  threadData->lastEquationSolved = 5839;
}

/*
equation index: 5840
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.t[3] = -chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5840(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5840};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3076]] /* chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.t[3] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3231]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[3] variable */));
  threadData->lastEquationSolved = 5840;
}

/*
equation index: 5841
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.frame_a.t[1] = (-chassis.detailedChassis.frAxleDW.leftTire.Mx) - chassis.detailedChassis.frAxleDW.leftTire.Fy * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5841(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5841};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3217]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.frame_a.t[1] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3067]] /* chassis.detailedChassis.frAxleDW.leftTire.Mx variable */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3066]] /* chassis.detailedChassis.frAxleDW.leftTire.Fy variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3219]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 5841;
}

/*
equation index: 5842
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[1] = (-chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.frame_a.t[1]) - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.t[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5842(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5842};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3229]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[1] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3217]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.prismatic_z.frame_a.t[1] variable */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3187]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.frame_a.t[1] variable */);
  threadData->lastEquationSolved = 5842;
}

/*
equation index: 5843
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.t[1] = -chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_5843(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,5843};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3074]] /* chassis.detailedChassis.frAxleDW.leftTire.chassisFrame.t[1] variable */) = (-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3229]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.toHub.frame_b.t[1] variable */));
  threadData->lastEquationSolved = 5843;
}

/*
equation index: 8111
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.leftLCABody.a_0[1]</var>
<var>chassis.detailedChassis.rrAxleDW.leftLCABody.a_0[2]</var>
<var>chassis.detailedChassis.rrAxleDW.rightLCABody.a_0[3]</var>
<var>chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[2]</var>
<var>chassis.detailedChassis.frAxleDW.rightUCABody.z_a[3]</var>
<var>chassis.detailedChassis.frAxleDW.rightUCABody.z_a[2]</var>
<var>chassis.detailedChassis.frAxleDW.rightUCABody.z_a[1]</var>
<var>chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[1]</var>
<var>chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[3]</var>
<var>$DER.yawVel</var>
<var>chassis.detailedChassis.spaceFrame.torsionalRevolute.a</var>
<var>chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_rod</var>
<var>chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a</var>
<var>chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.a</var>
<var>chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_rod</var>
<var>chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.a</var>
<var>chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_rod</var>
<var>chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.a</var>
<var>chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_rod</var>
<var>chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.a</var>
<var>chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a</var>
<var>chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a</var>
<var>chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a</var>
<var>chassis.cgFreeMotion.phi_dd[1]</var>
<var>chassis.cgFreeMotion.phi_dd[2]</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8111(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8111};
  /* Linear equation system */
  int retValue;
  double aux_x[25] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[2625]] /* chassis.detailedChassis.frAxleDW.leftLCABody.a_0[1] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[6380]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.a_0[2] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[8149]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.a_0[3] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[8971]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[2] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5215]] /* chassis.detailedChassis.frAxleDW.rightUCABody.z_a[3] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5214]] /* chassis.detailedChassis.frAxleDW.rightUCABody.z_a[2] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5213]] /* chassis.detailedChassis.frAxleDW.rightUCABody.z_a[1] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[8970]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[1] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[8972]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[3] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9959]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[2980]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_rod variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[3615]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[3658]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[8497]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_rod variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5413]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[4740]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_rod variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[7409]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[6734]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_rod variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9164]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9122]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[7366]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5371]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[2355]] /* chassis.cgFreeMotion.phi_dd[1] variable */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[2356]] /* chassis.cgFreeMotion.phi_dd[2] variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8111 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 23, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8111};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8111 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2625]] /* chassis.detailedChassis.frAxleDW.leftLCABody.a_0[1] variable */) = aux_x[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6380]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.a_0[2] variable */) = aux_x[1];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8149]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.a_0[3] variable */) = aux_x[2];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8971]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[2] variable */) = aux_x[3];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5215]] /* chassis.detailedChassis.frAxleDW.rightUCABody.z_a[3] variable */) = aux_x[4];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5214]] /* chassis.detailedChassis.frAxleDW.rightUCABody.z_a[2] variable */) = aux_x[5];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5213]] /* chassis.detailedChassis.frAxleDW.rightUCABody.z_a[1] variable */) = aux_x[6];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8970]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[1] variable */) = aux_x[7];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8972]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.z_a[3] variable */) = aux_x[8];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */) = aux_x[9];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9959]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.a variable */) = aux_x[10];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2980]] /* chassis.detailedChassis.frAxleDW.leftTieRod.rod.f_rod variable */) = aux_x[11];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3615]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.a variable */) = aux_x[12];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3658]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.steeringAxis.a variable */) = aux_x[13];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8497]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.f_rod variable */) = aux_x[14];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5413]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.steeringAxis.a variable */) = aux_x[15];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4740]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.f_rod variable */) = aux_x[16];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7409]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.a variable */) = aux_x[17];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6734]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.f_rod variable */) = aux_x[18];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9164]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.a variable */) = aux_x[19];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9122]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a variable */) = aux_x[20];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7366]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.a variable */) = aux_x[21];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5371]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.a variable */) = aux_x[22];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2355]] /* chassis.cgFreeMotion.phi_dd[1] variable */) = aux_x[23];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2356]] /* chassis.cgFreeMotion.phi_dd[2] variable */) = aux_x[24];

  threadData->lastEquationSolved = 8111;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35605(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35512(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35516(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35674(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35497(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36109(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35675(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36248(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36111(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35821(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35819(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35652(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35657(DATA *data, threadData_t *threadData);


/*
equation index: 8125
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * ((-cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8125(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8125};
  modelica_real tmp797;
  modelica_real tmp798;
  tmp797 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  tmp798 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[771]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3])) DUMMY_DER */) = (1.0 - ((tmp797 * tmp797))) * (((-cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((tmp798 * tmp798)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8125;
}

/*
equation index: 8126
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] + cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8126(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8126};
  modelica_real tmp799;
  modelica_real tmp800;
  tmp799 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp800 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[770]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp799 * tmp799)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp800 * tmp800)) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8126;
}

/*
equation index: 8127
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] + cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8127(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8127};
  modelica_real tmp801;
  modelica_real tmp802;
  tmp801 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp802 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[769]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp801 * tmp801)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp802 * tmp802)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))));
  threadData->lastEquationSolved = 8127;
}

/*
equation index: 8128
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] + cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8128(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8128};
  modelica_real tmp803;
  modelica_real tmp804;
  tmp803 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp804 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[768]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp803 * tmp803)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp804 * tmp804)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))));
  threadData->lastEquationSolved = 8128;
}

/*
equation index: 8129
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * ((-cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8129(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8129};
  modelica_real tmp805;
  modelica_real tmp806;
  tmp805 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  tmp806 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[767]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2])) DUMMY_DER */) = (1.0 - ((tmp805 * tmp805))) * (((-cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((tmp806 * tmp806)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8129;
}

/*
equation index: 8130
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] + cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8130(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8130};
  modelica_real tmp807;
  modelica_real tmp808;
  tmp807 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp808 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[766]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp807 * tmp807)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp808 * tmp808)) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8130;
}

/*
equation index: 8131
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] + cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8131(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8131};
  modelica_real tmp809;
  modelica_real tmp810;
  tmp809 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp810 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[765]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp809 * tmp809)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp810 * tmp810)) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8131;
}

/*
equation index: 8132
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle - sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0) + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] + cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8132(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8132};
  modelica_real tmp811;
  modelica_real tmp812;
  tmp811 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp812 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[764]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp811 * tmp811)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp812 * tmp812)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))));
  threadData->lastEquationSolved = 8132;
}

/*
equation index: 8133
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * ((-cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8133(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8133};
  modelica_real tmp813;
  modelica_real tmp814;
  tmp813 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  tmp814 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1881]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[763]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1])) DUMMY_DER */) = (1.0 - ((tmp813 * tmp813))) * (((-cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((tmp814 * tmp814)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9362]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[772]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8133;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35654(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35664(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35552(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35541(DATA *data, threadData_t *threadData);


/*
equation index: 8138
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3] = (1.0 - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] ^ 2.0) * ((-cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8138(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8138};
  modelica_real tmp815;
  modelica_real tmp816;
  tmp815 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */);
  tmp816 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[597]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,3])) DUMMY_DER */) = (1.0 - ((tmp815 * tmp815))) * (((-cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((tmp816 * tmp816)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8138;
}

/*
equation index: 8139
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] + cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8139(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8139};
  modelica_real tmp817;
  modelica_real tmp818;
  tmp817 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp818 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[596]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,2])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp817 * tmp817)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp818 * tmp818)) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8139;
}

/*
equation index: 8140
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle - sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] + cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8140(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8140};
  modelica_real tmp819;
  modelica_real tmp820;
  tmp819 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp820 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[595]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[3,1])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp819 * tmp819)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp820 * tmp820)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))));
  threadData->lastEquationSolved = 8140;
}

/*
equation index: 8141
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle - sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] + cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8141(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8141};
  modelica_real tmp821;
  modelica_real tmp822;
  tmp821 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp822 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[594]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,3])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp821 * tmp821)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp822 * tmp822)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))));
  threadData->lastEquationSolved = 8141;
}

/*
equation index: 8142
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2] = (1.0 - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] ^ 2.0) * ((-cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8142(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8142};
  modelica_real tmp823;
  modelica_real tmp824;
  tmp823 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */);
  tmp824 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[593]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,2])) DUMMY_DER */) = (1.0 - ((tmp823 * tmp823))) * (((-cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((tmp824 * tmp824)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8142;
}

/*
equation index: 8143
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] + cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8143(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8143};
  modelica_real tmp825;
  modelica_real tmp826;
  tmp825 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp826 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[592]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[2,1])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp825 * tmp825)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp826 * tmp826)) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8143;
}

/*
equation index: 8144
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] + cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8144(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8144};
  modelica_real tmp827;
  modelica_real tmp828;
  tmp827 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp828 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[591]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,3])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp827 * tmp827)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp828 * tmp828)) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8144;
}

/*
equation index: 8145
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * (cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle - sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0) + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * (sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] + cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8145(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8145};
  modelica_real tmp829;
  modelica_real tmp830;
  tmp829 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  tmp830 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[590]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,2])) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((tmp829 * tmp829)))) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * (((tmp830 * tmp830)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))));
  threadData->lastEquationSolved = 8145;
}

/*
equation index: 8146
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1] = (1.0 - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] ^ 2.0) * ((-cos(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) * $DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle ^ 2.0 - sin(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) * $DER.$DER.chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8146(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8146};
  modelica_real tmp831;
  modelica_real tmp832;
  tmp831 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */);
  tmp832 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1635]] /* der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle) DUMMY_DER */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[589]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.R_rel.T[1,1])) DUMMY_DER */) = (1.0 - ((tmp831 * tmp831))) * (((-cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */)))) * ((tmp832 * tmp832)) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7610]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[598]] /* der(der(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.angle)) DUMMY_DER */))));
  threadData->lastEquationSolved = 8146;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35544(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35542(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35553(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35549(DATA *data, threadData_t *threadData);


/*
equation index: 8151
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.damper.a_rel = chassis.detailedChassis.spaceFrame.torsionalRevolute.a
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8151(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8151};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9829]] /* chassis.detailedChassis.spaceFrame.damper.a_rel variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9959]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.a variable */);
  threadData->lastEquationSolved = 8151;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35651(DATA *data, threadData_t *threadData);


/*
equation index: 8153
type: SIMPLE_ASSIGN
$whenCondition7 = vcu.useMode == 0 and rampEnding and (abs($DER.yawVel) >= der_yawVelTol or abs($DER.handwheelAngle) >= handwheelRateTol)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8153(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8153};
  modelica_boolean tmp833;
  modelica_boolean tmp834;
  tmp833 = GreaterEq(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5870]] /* der_yawVelTol PARAM */));
  tmp834 = GreaterEq(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2045]] /* der(handwheelAngle) DUMMY_DER */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5913]] /* handwheelRateTol PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition7 DISCRETE */) = ((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[45]] /* rampEnding DISCRETE */)) && (tmp833 || tmp834));
  threadData->lastEquationSolved = 8153;
}

/*
equation index: 8154
type: SIMPLE_ASSIGN
$whenCondition8 = vcu.useMode == 0 and rampEnding and abs($DER.yawVel) < der_yawVelTol and abs($DER.handwheelAngle) < handwheelRateTol and $PRE.t_qss_hit < 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8154(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8154};
  modelica_boolean tmp835;
  modelica_boolean tmp836;
  modelica_boolean tmp837;
  tmp835 = Less(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5870]] /* der_yawVelTol PARAM */));
  tmp836 = Less(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2045]] /* der(handwheelAngle) DUMMY_DER */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5913]] /* handwheelRateTol PARAM */));
  tmp837 = Less((data->simulationInfo->realVarsPre[10799] /* t_qss_hit DISCRETE */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[20]] /* $whenCondition8 DISCRETE */) = ((((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[45]] /* rampEnding DISCRETE */)) && tmp835) && tmp836) && tmp837);
  threadData->lastEquationSolved = 8154;
}

/*
equation index: 8155
type: SIMPLE_ASSIGN
$whenCondition1 = vcu.useMode == 2 and abs($DER.yawVel) >= der_yawVelTol
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8155(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8155};
  modelica_boolean tmp838;
  tmp838 = GreaterEq(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5870]] /* der_yawVelTol PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = (((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 2)) && tmp838);
  threadData->lastEquationSolved = 8155;
}

/*
equation index: 8156
type: SIMPLE_ASSIGN
$whenCondition2 = vcu.useMode == 2 and time > vcu.steerStart and abs($DER.yawVel) < der_yawVelTol and $PRE.t_yawVel_hit < 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8156(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8156};
  modelica_boolean tmp839;
  modelica_boolean tmp840;
  modelica_boolean tmp841;
  tmp839 = Greater(data->localData[0]->timeValue,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6875]] /* vcu.steerStart PARAM */));
  tmp840 = Less(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5870]] /* der_yawVelTol PARAM */));
  tmp841 = Less((data->simulationInfo->realVarsPre[10803] /* t_yawVel_hit DISCRETE */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition2 DISCRETE */) = (((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 2)) && tmp839) && tmp840) && tmp841);
  threadData->lastEquationSolved = 8156;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35828(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35827(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35826(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35582(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35575(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35574(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35573(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35572(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35571(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35570(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35583(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35581(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35580(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35579(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35578(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35577(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35576(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35648(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35568(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35569(DATA *data, threadData_t *threadData);


/*
equation index: 8177
type: SIMPLE_ASSIGN
$DER.$DER.aeroModel.sprungChassisFrame.r_0[2] = chassis.detailedChassis.spaceFrame.sprungBody.a_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8177(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8177};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[99]] /* der(der(aeroModel.sprungChassisFrame.r_0[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9892]] /* chassis.detailedChassis.spaceFrame.sprungBody.a_0[2] variable */);
  threadData->lastEquationSolved = 8177;
}

/*
equation index: 8178
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.a_rel_a[2] = $DER.$DER.aeroModel.sprungChassisFrame.r_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8178(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8178};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2341]] /* chassis.cgFreeMotion.a_rel_a[2] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[99]] /* der(der(aeroModel.sprungChassisFrame.r_0[2])) DUMMY_DER */);
  threadData->lastEquationSolved = 8178;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35524(DATA *data, threadData_t *threadData);


/*
equation index: 8180
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.sprungBody.v_0[2] = chassis.detailedChassis.spaceFrame.sprungBody.a_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8180(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8180};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1997]] /* der(chassis.detailedChassis.spaceFrame.sprungBody.v_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9892]] /* chassis.detailedChassis.spaceFrame.sprungBody.a_0[2] variable */);
  threadData->lastEquationSolved = 8180;
}

/*
equation index: 8181
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[2] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * ((-0.08178799999999999) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + 0.10664664 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] ^ 2.0 - yawVel * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,2] * ((-0.10664664) * $DER.yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + (-0.08178799999999999) * yawVel * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.10664664 * (-chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) + chassis.chassisFrame.R.T[3,2] * (0.10664664 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8181(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8181};
  modelica_real tmp842;
  modelica_real tmp843;
  tmp842 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */);
  tmp843 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[437]] /* der(der(chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[440]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((-0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (0.10664664) * ((tmp842 * tmp842)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (-0.08178799999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + (0.10664664) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (0.08178799999999999) * ((tmp843 * tmp843)));
  threadData->lastEquationSolved = 8181;
}

/*
equation index: 8182
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[2] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + 0.250754351932 * $DER.yawVel + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] + (-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - yawVel * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,2] * ((-0.042144464098) * $DER.yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + yawVel * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel) + (-chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] + (-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - $DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,2] * ($DER$$DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})[3] + (-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8182(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8182};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[271]] /* der(der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[440]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - ((real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25, _OMC_LIT25, _OMC_LIT25), 2) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8182;
}

/*
equation index: 8183
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[2] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[2] + chassis.chassisFrame.R.T[1,2] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + (-0.250754351932) * $DER.yawVel + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - yawVel * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,2] * ((-0.042144464098) * $DER.yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + yawVel * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])) + chassis.chassisFrame.R.T[3,2] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8183(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8183};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[120]] /* der(der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[440]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8183;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35597(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35602(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35596(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35603(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35601(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35513(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35514(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36112(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36247(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35511(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35510(DATA *data, threadData_t *threadData);


/*
equation index: 8195
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.w = chassis.detailedChassis.spaceFrame.torsionalRevolute.a
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8195(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8195};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[88]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.w) STATE_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9959]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.a variable */);
  threadData->lastEquationSolved = 8195;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35670(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35668(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35666(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35656(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35531(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35563(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35565(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35566(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35564(DATA *data, threadData_t *threadData);


/*
equation index: 8205
type: SIMPLE_ASSIGN
$DER.$DER.aeroModel.sprungChassisFrame.r_0[1] = chassis.detailedChassis.spaceFrame.sprungBody.a_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8205(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8205};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[98]] /* der(der(aeroModel.sprungChassisFrame.r_0[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9891]] /* chassis.detailedChassis.spaceFrame.sprungBody.a_0[1] variable */);
  threadData->lastEquationSolved = 8205;
}

/*
equation index: 8206
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.a_rel_a[1] = $DER.$DER.aeroModel.sprungChassisFrame.r_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8206(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8206};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2340]] /* chassis.cgFreeMotion.a_rel_a[1] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[98]] /* der(der(aeroModel.sprungChassisFrame.r_0[1])) DUMMY_DER */);
  threadData->lastEquationSolved = 8206;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35613(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35669(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35667(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35665(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35817(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35660(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35663(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35529(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35528(DATA *data, threadData_t *threadData);


/*
equation index: 8216
type: SIMPLE_ASSIGN
$DER.$DER.aeroModel.sprungChassisFrame.r_0[3] = chassis.detailedChassis.spaceFrame.sprungBody.a_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8216(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8216};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[100]] /* der(der(aeroModel.sprungChassisFrame.r_0[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9893]] /* chassis.detailedChassis.spaceFrame.sprungBody.a_0[3] variable */);
  threadData->lastEquationSolved = 8216;
}

/*
equation index: 8217
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.a_rel_a[3] = $DER.$DER.aeroModel.sprungChassisFrame.r_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8217(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8217};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2342]] /* chassis.cgFreeMotion.a_rel_a[3] variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[100]] /* der(der(aeroModel.sprungChassisFrame.r_0[3])) DUMMY_DER */);
  threadData->lastEquationSolved = 8217;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35640(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35619(DATA *data, threadData_t *threadData);


/*
equation index: 8220
type: SIMPLE_ASSIGN
linearityGainLossFraction = if vcu.useMode == 0 and enableLinearityTermination and linearityReferenceValid and noEvent(abs(chassis.bodyAcceleration[2]) >= linearityReferenceAy + max(0.0, linearityEvaluationAyMargin)) then max(0.0, 1.0 - linearityGainRatio) else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8220(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8220};
  modelica_boolean tmp844;
  tmp844 = GreaterEq(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2300]] /* chassis.bodyAcceleration[2] variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5985]] /* linearityReferenceAy PARAM */) + fmax(0.0,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5982]] /* linearityEvaluationAyMargin PARAM */)));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10223]] /* linearityGainLossFraction variable */) = ((((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) && (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[572]] /* enableLinearityTermination PARAM */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[43]] /* linearityReferenceValid DISCRETE */)) && tmp844)?fmax(0.0,1.0 - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10224]] /* linearityGainRatio variable */)):0.0);
  threadData->lastEquationSolved = 8220;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35627(DATA *data, threadData_t *threadData);


/*
equation index: 8222
type: SIMPLE_ASSIGN
$whenCondition11 = vcu.useMode == 0 and enableLinearityTermination and linearityReferenceValid and linearityGainLossFraction >= linearityNonlinearityFraction and $PRE.t_linearity_limit_hit < 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8222(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8222};
  modelica_boolean tmp845;
  modelica_boolean tmp846;
  tmp845 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10223]] /* linearityGainLossFraction variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5984]] /* linearityNonlinearityFraction PARAM */));
  tmp846 = Less((data->simulationInfo->realVarsPre[10798] /* t_linearity_limit_hit DISCRETE */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) = ((((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) && (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[572]] /* enableLinearityTermination PARAM */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[43]] /* linearityReferenceValid DISCRETE */)) && tmp845) && tmp846);
  threadData->lastEquationSolved = 8222;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35620(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35618(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35617(DATA *data, threadData_t *threadData);


/*
equation index: 8226
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.sprungBody.v_0[3] = chassis.detailedChassis.spaceFrame.sprungBody.a_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8226(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8226};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1998]] /* der(chassis.detailedChassis.spaceFrame.sprungBody.v_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9893]] /* chassis.detailedChassis.spaceFrame.sprungBody.a_0[3] variable */);
  threadData->lastEquationSolved = 8226;
}

/*
equation index: 8227
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[3] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * ((-0.08178799999999999) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + 0.10664664 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] ^ 2.0 - yawVel * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,3] * ((-0.10664664) * $DER.yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + (-0.08178799999999999) * yawVel * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.10664664 * (-chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) + chassis.chassisFrame.R.T[3,3] * (0.10664664 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8227(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8227};
  modelica_real tmp847;
  modelica_real tmp848;
  tmp847 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */);
  tmp848 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[438]] /* der(der(chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[441]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((-0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (0.10664664) * ((tmp847 * tmp847)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (-0.08178799999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + (0.10664664) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (0.08178799999999999) * ((tmp848 * tmp848)));
  threadData->lastEquationSolved = 8227;
}

/*
equation index: 8228
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[3] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + 0.250754351932 * $DER.yawVel + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] + (-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - yawVel * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,3] * ((-0.042144464098) * $DER.yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + yawVel * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel) + (-chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] + (-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - $DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,3] * ($DER$$DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})[3] + (-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8228(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8228};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[272]] /* der(der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[441]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - ((real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25, _OMC_LIT25, _OMC_LIT25), 2) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8228;
}

/*
equation index: 8229
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[3] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[3] + chassis.chassisFrame.R.T[1,3] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + (-0.250754351932) * $DER.yawVel + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - yawVel * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,3] * ((-0.042144464098) * $DER.yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + yawVel * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])) + chassis.chassisFrame.R.T[3,3] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8229(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8229};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[121]] /* der(der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[441]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2369]] /* chassis.chassisFrame.R.T[3,3] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8229;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35604(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35600(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35517(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35518(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35676(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35816(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35815(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35814(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35655(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35658(DATA *data, threadData_t *threadData);


/*
equation index: 8301
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8301(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8301};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[7917]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8301 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 24, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8301};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8301 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7917]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 8301;
}

/*
equation index: 8302
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] = $DER.$DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8302(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8302};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[708]] /* der(der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[705]] /* der(der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8302;
}

/*
equation index: 8303
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[3] = $DER.$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8303(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8303};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[663]] /* der(der(chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[708]] /* der(der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8325]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8328]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8331]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8303;
}

/*
equation index: 8304
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] = $DER.$DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8304(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8304};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[707]] /* der(der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[704]] /* der(der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8304;
}

/*
equation index: 8305
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[2] = $DER.$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8305(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8305};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[662]] /* der(der(chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[707]] /* der(der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8324]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8327]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8330]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8305;
}

/*
equation index: 8306
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] = $DER.$DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8306(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8306};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[706]] /* der(der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[703]] /* der(der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8306;
}

/*
equation index: 8307
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[1] = $DER.$DER.chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * ($DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]) - $DER.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8307(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8307};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[661]] /* der(der(chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.vis.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[706]] /* der(der(chassis.detailedChassis.rrAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8323]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8326]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1768]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8329]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1766]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8332]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8334]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8333]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1767]] /* der(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8307;
}

/*
equation index: 8375
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.stabar.mountAxis.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8375(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8375};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9547]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8375 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 25, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8375};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8375 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9547]] /* chassis.detailedChassis.rrAxleDW.stabar.mountAxis.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 8375;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36029(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35956(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35659(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35653(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35550(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35546(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35545(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35547(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35661(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35820(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35822(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35530(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35662(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35818(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35548(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36099(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36098(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36102(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35506(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36101(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35551(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36097(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36100(DATA *data, threadData_t *threadData);


/*
equation index: 8399
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[1] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * ((-0.08178799999999999) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + 0.10664664 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] ^ 2.0 - yawVel * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,1] * ((-0.10664664) * $DER.yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + (-0.08178799999999999) * yawVel * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.10664664 * (-chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) + chassis.chassisFrame.R.T[3,1] * (0.10664664 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8399(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8399};
  modelica_real tmp849;
  modelica_real tmp850;
  tmp849 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */);
  tmp850 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[436]] /* der(der(chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[439]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((-0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (0.10664664) * ((tmp849 * tmp849)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (-0.08178799999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + (0.10664664) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (0.08178799999999999) * ((tmp850 * tmp850)));
  threadData->lastEquationSolved = 8399;
}

/*
equation index: 8400
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[1] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + 0.250754351932 * $DER.yawVel + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * ((-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - yawVel * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,1] * ((-0.042144464098) * $DER.yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + yawVel * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel) + (-chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) * ((-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - $DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136}, {0.0, 0.0, 0.0})[3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,1] * ((-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8400(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8400};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[270]] /* der(der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[439]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) * ((-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - ((real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT23, _OMC_LIT25), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8400;
}

/*
equation index: 8401
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[1] = $DER.$DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + (-0.250754351932) * $DER.yawVel + chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]) - yawVel * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])) + chassis.chassisFrame.R.T[2,1] * ((-0.042144464098) * $DER.yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + yawVel * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])) + chassis.chassisFrame.R.T[3,1] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] + chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8401(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8401};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[119]] /* der(der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[439]] /* der(der(chassis.detailedChassis.frAxleFrame.r_0[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2054]] /* der(yawVel) DUMMY_DER */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9944]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[1] variable */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9945]] /* chassis.detailedChassis.spaceFrame.sprungBody.z_a[2] variable */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8401;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35611(DATA *data, threadData_t *threadData);


/*
equation index: 8464
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8464(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8464};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[4160]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8464 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 26, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8464};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8464 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4160]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 8464;
}

/*
equation index: 8465
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] = $DER.$DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r[3] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8465(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8465};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[320]] /* der(der(chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[317]] /* der(der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4568]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4571]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4574]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8465;
}

/*
equation index: 8466
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.vis.r[3] = $DER.$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8466(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8466};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[275]] /* der(der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.vis.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[320]] /* der(der(chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4568]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4571]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4574]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8466;
}

/*
equation index: 8467
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] = $DER.$DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8467(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8467};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[319]] /* der(der(chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[316]] /* der(der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4567]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4570]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4573]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8467;
}

/*
equation index: 8468
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.vis.r[2] = $DER.$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8468(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8468};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[274]] /* der(der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.vis.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[319]] /* der(der(chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4567]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4570]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4573]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8468;
}

/*
equation index: 8469
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] = $DER.$DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8469(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8469};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[318]] /* der(der(chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[315]] /* der(der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4566]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4569]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4572]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1496]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1497]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8469;
}

/*
equation index: 8470
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.vis.r[1] = $DER.$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] * ($DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) + chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]) - $DER.chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] * chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8470(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8470};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[273]] /* der(der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.vis.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[318]] /* der(der(chassis.detailedChassis.frAxleDW.rightShockLinkage.lineForceWithMass.lineShape.r[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4566]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4569]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1204]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4572]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1202]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4575]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4576]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */)))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1203]] /* der(chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */))));
  threadData->lastEquationSolved = 8470;
}

/*
equation index: 8538
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.stabar.mountAxis.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8538(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8538};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5790]] /* chassis.detailedChassis.frAxleDW.stabar.mountAxis.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8538 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 27, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8538};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8538 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5790]] /* chassis.detailedChassis.frAxleDW.stabar.mountAxis.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 8538;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35813(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35743(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35612(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35523(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35519(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35520(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35522(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35521(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35509(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35609(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35610(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35599(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35607(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36105(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35608(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35606(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35598(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36106(DATA *data, threadData_t *threadData);


/*
equation index: 8618
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8618(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8618};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[2395]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8618 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 28, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8618};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8618 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2395]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 8618;
}

/*
equation index: 8619
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] = $DER.$DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * (0.036645724016000025 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * (0.003465897055999999 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * ((-0.002875737454000049) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8619(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8619};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[169]] /* der(der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[166]] /* der(der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8619;
}

/*
equation index: 8620
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[3] = $DER.$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * ((-0.039062922128) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * ((-0.017982744577999997) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * ((-0.048393882129999954) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8620(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8620};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[124]] /* der(der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[169]] /* der(der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2808]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2811]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2814]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8620;
}

/*
equation index: 8621
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] = $DER.$DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * (0.036645724016000025 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * (0.003465897055999999 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * ((-0.002875737454000049) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8621(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8621};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[168]] /* der(der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[165]] /* der(der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8621;
}

/*
equation index: 8622
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[2] = $DER.$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * ((-0.039062922128) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * ((-0.017982744577999997) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * ((-0.048393882129999954) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8622(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8622};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[123]] /* der(der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[168]] /* der(der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2807]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2810]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2813]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8622;
}

/*
equation index: 8623
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] = $DER.$DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * (0.036645724016000025 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * (0.003465897055999999 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.002875737454000049) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * ((-0.002875737454000049) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.003465897055999999) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.003465897055999999 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.036645724016000025) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.036645724016000025 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.002875737454000049 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8623(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8623};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[167]] /* der(der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[164]] /* der(der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((-0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (-0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.003465897055999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.036645724016000025) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.002875737454000049) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8623;
}

/*
equation index: 8624
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[1] = $DER.$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * ((-0.039062922128) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * ((-0.017982744577999997) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.048393882129999954) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * ((-0.048393882129999954) * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.017982744577999997 * $DER.chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.017982744577999997) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.039062922128 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.039062922128) * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.048393882129999954 * chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8624(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8624};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[122]] /* der(der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.vis.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[167]] /* der(der(chassis.detailedChassis.frAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2806]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2809]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[961]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2812]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((-0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[959]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[960]] /* der(chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.017982744577999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2815]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.039062922128) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2816]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.048393882129999954) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2817]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8624;
}

/*
equation index: 8692
type: LINEAR

<var>chassis.detailedChassis.frAxleDW.stabar.stabarAxis.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8692(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8692};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5820]] /* chassis.detailedChassis.frAxleDW.stabar.stabarAxis.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8692 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 29, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8692};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8692 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5820]] /* chassis.detailedChassis.frAxleDW.stabar.stabarAxis.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 8692;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36246(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36173(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36107(DATA *data, threadData_t *threadData);


/*
equation index: 8696
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.sprungBody.v_0[1] = chassis.detailedChassis.spaceFrame.sprungBody.a_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8696(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8696};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1996]] /* der(chassis.detailedChassis.spaceFrame.sprungBody.v_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9891]] /* chassis.detailedChassis.spaceFrame.sprungBody.a_0[1] variable */);
  threadData->lastEquationSolved = 8696;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35543(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35825(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35824(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35823(DATA *data, threadData_t *threadData);


/*
equation index: 8762
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8762(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8762};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[6149]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8762 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 30, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8762};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8762 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6149]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 8762;
}

/*
equation index: 8763
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] = $DER.$DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[3] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * (0.056759840000000006 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * ((-0.025337289999999957) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * (0.009399680000000021 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8763(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8763};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[537]] /* der(der(chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[534]] /* der(der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6562]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6565]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6568]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8763;
}

/*
equation index: 8764
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[3] = $DER.$DER.chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] * ((-0.018531649999999997) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] * (0.02454310999999998 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] * ((-0.05079721000000004) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8764(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8764};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[492]] /* der(der(chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[3])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[537]] /* der(der(chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[3])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6562]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,3] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6565]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,3] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6568]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,3] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8764;
}

/*
equation index: 8765
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] = $DER.$DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[2] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * (0.056759840000000006 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * ((-0.025337289999999957) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * (0.009399680000000021 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8765(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8765};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[536]] /* der(der(chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[533]] /* der(der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6561]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6564]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6567]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8765;
}

/*
equation index: 8766
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[2] = $DER.$DER.chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] * ((-0.018531649999999997) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] * (0.02454310999999998 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] * ((-0.05079721000000004) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8766(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8766};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[491]] /* der(der(chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[2])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[536]] /* der(der(chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[2])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6561]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,2] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6564]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,2] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6567]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,2] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8766;
}

/*
equation index: 8767
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] = $DER.$DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[1] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * (0.056759840000000006 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * ((-0.025337289999999957) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.009399680000000021 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * (0.009399680000000021 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + 0.025337289999999957 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.025337289999999957) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + (-0.056759840000000006) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * (0.056759840000000006 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + (-0.009399680000000021) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8767(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8767};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[535]] /* der(der(chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[532]] /* der(der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6560]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6563]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6566]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.025337289999999957) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (-0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((0.056759840000000006) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (-0.009399680000000021) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8767;
}

/*
equation index: 8768
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[1] = $DER.$DER.chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] * ((-0.018531649999999997) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * (0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] * (0.02454310999999998 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] * ((-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * ((-0.05079721000000004) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2])) + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] * ((-0.05079721000000004) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] + (-0.02454310999999998) * $DER.chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] * (0.02454310999999998 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] + 0.018531649999999997 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] * ((-0.018531649999999997) * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] + 0.05079721000000004 * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8768(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8768};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[490]] /* der(der(chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.vis.r[1])) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[535]] /* der(der(chassis.detailedChassis.rrAxleDW.leftShockLinkage.lineForceWithMass.lineShape.r[1])) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6560]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[1,1] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6563]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[2,1] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1525]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3]) DUMMY_DER */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */))))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6566]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.T[3,1] DUMMY_STATE */)) * ((-0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1523]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1]) DUMMY_DER */)) + (-0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1524]] /* der(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */)) * ((0.02454310999999998) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)) + (0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6569]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[1] DUMMY_STATE */))) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) * ((-0.018531649999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6570]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[2] DUMMY_STATE */)) + (0.05079721000000004) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6571]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.R.w[3] DUMMY_STATE */)))));
  threadData->lastEquationSolved = 8768;
}

/*
equation index: 8836
type: LINEAR

<var>chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8836(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8836};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[9577]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 8836 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 31, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,8836};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 8836 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9577]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 8836;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36096(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35895(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36249(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36108(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36110(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35515(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32935(DATA *data, threadData_t *threadData);


/*
equation index: 8844
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.widthDirection[1] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8844(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8844};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3868]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.widthDirection[1] variable */) = 0.0;
  threadData->lastEquationSolved = 8844;
}

/*
equation index: 8845
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.widthDirection[2] = 1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8845(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8845};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3869]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.widthDirection[2] variable */) = 1.0;
  threadData->lastEquationSolved = 8845;
}

/*
equation index: 8846
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.widthDirection[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8846(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8846};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3870]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.widthDirection[3] variable */) = 0.0;
  threadData->lastEquationSolved = 8846;
}

/*
equation index: 8847
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.color[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8847(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8847};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3857]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.color[3] variable */) = 0.0;
  threadData->lastEquationSolved = 8847;
}

/*
equation index: 8848
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.color[2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8848(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8848};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3856]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.color[2] variable */) = 0.0;
  threadData->lastEquationSolved = 8848;
}

/*
equation index: 8849
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.color[1] = 255.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8849(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8849};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3855]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.color[1] variable */) = 255.0;
  threadData->lastEquationSolved = 8849;
}

/*
equation index: 8850
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revoluteColor[1] = 255
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8850(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8850};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[138]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revoluteColor[1] DISCRETE */) = ((modelica_integer) 255);
  threadData->lastEquationSolved = 8850;
}

/*
equation index: 8851
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revoluteColor[2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8851(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8851};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[139]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revoluteColor[2] DISCRETE */) = 0.0;
  threadData->lastEquationSolved = 8851;
}

/*
equation index: 8852
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revoluteColor[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8852(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8852};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[140]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revoluteColor[3] DISCRETE */) = 0.0;
  threadData->lastEquationSolved = 8852;
}

/*
equation index: 8853
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.bearing.phi = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8853(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8853};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3854]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.bearing.phi variable */) = 0.0;
  threadData->lastEquationSolved = 8853;
}

/*
equation index: 8854
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.r_shape[1] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8854(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8854};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3952]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.r_shape[1] variable */) = 0.0;
  threadData->lastEquationSolved = 8854;
}

/*
equation index: 8855
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.r_shape[2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8855(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8855};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3953]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.r_shape[2] variable */) = 0.0;
  threadData->lastEquationSolved = 8855;
}

/*
equation index: 8856
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.r_shape[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8856(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8856};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3954]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.r_shape[3] variable */) = 0.0;
  threadData->lastEquationSolved = 8856;
}

/*
equation index: 8857
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.lengthDirection[1] = -0.07885152190457045
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8857(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8857};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3949]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.lengthDirection[1] variable */) = -0.07885152190457045;
  threadData->lastEquationSolved = 8857;
}

/*
equation index: 8858
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.lengthDirection[2] = -0.13456891961399842
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8858(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8858};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3950]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.lengthDirection[2] variable */) = -0.13456891961399842;
  threadData->lastEquationSolved = 8858;
}

/*
equation index: 8859
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.lengthDirection[3] = 0.9877619365855591
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8859(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8859};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3951]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.lengthDirection[3] variable */) = 0.9877619365855591;
  threadData->lastEquationSolved = 8859;
}

/*
equation index: 8860
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.r_shape[1] = -0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8860(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8860};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3968]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.r_shape[1] variable */) = -0.015;
  threadData->lastEquationSolved = 8860;
}

/*
equation index: 8861
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.r_shape[2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8861(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8861};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3969]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.r_shape[2] variable */) = 0.0;
  threadData->lastEquationSolved = 8861;
}

/*
equation index: 8862
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.r_shape[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8862(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8862};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3970]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.r_shape[3] variable */) = 0.0;
  threadData->lastEquationSolved = 8862;
}

/*
equation index: 8863
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.lengthDirection[1] = 1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_8863(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,8863};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3965]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.lengthDirection[1] variable */) = 1.0;
  threadData->lastEquationSolved = 8863;
}
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_functionInitialEquations_8(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[494])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5530,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5531,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5532,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5533,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5534,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5535,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5536,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5537,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5538,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32714,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5540,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5542,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32682,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32683,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32684,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32685,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32686,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32687,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32689,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32688,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32690,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5554,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32691,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32692,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32709,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32705,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32701,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32697,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5561,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32700,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32699,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32698,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32693,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5566,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32696,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32712,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32711,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32710,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32695,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32708,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32707,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32706,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32694,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32704,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32703,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32702,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5579,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32678,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5581,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32680,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32681,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5584,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5586,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33247,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5589,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32234,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32230,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32233,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32232,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32231,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32239,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32235,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32238,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32237,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32236,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32716,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32240,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32747,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32746,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32748,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5606,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32751,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5608,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32749,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5610,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32761,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32781,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32762,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32758,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32759,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32760,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32755,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32806,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32783,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32784,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32798,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32799,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32800,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32802,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32814,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32803,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5631,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5632,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5633,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32804,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5635,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5636,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5637,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5638,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32822,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32827,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32832,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5642,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32821,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32826,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32831,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5646,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32820,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32825,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32830,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32790,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32782,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32787,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32789,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32791,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32788,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32794,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32797,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32793,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32796,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32792,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32795,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5723,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32893,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32894,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32945,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5727,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5728,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32951,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32949,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5731,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32950,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32956,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5734,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32954,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5736,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32952,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5738,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5739,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5740,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5741,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32943,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5745,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32940,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32932,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32936,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32934,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5750,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32930,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5754,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32926,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5757,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32897,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32898,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32899,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32900,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5762,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32916,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5764,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32917,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33248,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32918,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32919,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5769,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5770,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5771,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32944,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5773,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5774,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5775,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32757,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5777,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5778,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5779,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32768,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32767,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32766,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5783,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5784,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5785,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32774,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32773,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32772,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5789,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5790,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5791,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32780,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32779,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32778,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5795,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33197,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5797,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33200,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5799,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32147,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5802,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33202,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33203,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33204,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33205,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5807,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5808,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5809,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5811,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5812,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5813,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5814,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5815,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5816,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5817,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5818,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32146,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5820,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5822,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33252,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5824,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32937,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5826,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5827,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33257,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33258,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33259,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_33260,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5832,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5833,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5834,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5835,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5836,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5837,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5838,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5839,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5840,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5841,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5842,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_5843,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8111,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35605,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35512,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35516,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35674,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35497,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36109,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35675,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36248,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36111,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35821,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35819,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35652,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35657,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8125,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8126,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8127,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8128,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8129,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8130,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8131,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8132,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8133,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35654,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35552,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8138,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8139,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8140,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8141,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8142,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8143,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8144,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8145,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8146,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35542,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35553,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35549,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8151,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35651,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8153,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8154,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8155,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8156,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35828,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35827,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35826,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35582,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35575,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35574,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35573,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35572,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35571,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35570,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35581,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35580,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35579,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35578,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35577,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35576,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35648,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35568,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35569,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8177,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8178,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35524,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8180,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8181,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8182,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8183,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35597,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35602,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35596,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35603,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35601,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35513,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35514,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36112,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36247,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35511,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35510,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8195,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35670,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35668,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35666,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35656,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35531,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35563,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35565,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35566,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35564,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8205,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8206,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35613,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35669,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35667,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35665,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35817,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35663,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35529,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35528,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8216,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8217,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35640,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35619,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8220,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35627,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8222,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35620,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35618,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35617,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8226,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8227,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8228,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8229,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35604,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35600,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35517,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35518,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35676,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35816,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35815,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35814,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35655,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35658,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8301,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8302,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8303,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8304,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8305,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8306,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8307,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8375,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36029,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35956,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35659,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35653,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35550,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35545,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35547,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35661,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35820,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35822,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35530,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35662,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35818,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35548,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36099,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36098,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36102,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35506,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36101,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35551,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36097,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36100,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8399,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8400,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35611,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8464,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8465,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8466,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8467,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8468,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8469,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8470,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8538,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35813,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35612,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35523,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35519,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35520,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35522,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35521,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35509,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35609,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35610,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35599,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35607,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36105,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35608,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35606,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35598,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36106,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8618,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8619,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8620,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8621,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8622,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8623,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8624,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8692,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36246,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36173,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36107,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8696,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35825,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35824,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35823,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8762,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8763,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8764,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8765,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8766,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8767,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8768,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8836,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36096,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35895,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36108,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36110,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35515,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32935,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8844,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8845,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8846,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8847,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8848,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8849,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8850,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8851,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8852,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8853,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8854,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8855,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8856,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8857,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8858,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8859,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8860,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8861,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8862,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_8863
  };
  
  for (int id = 0; id < 494; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif