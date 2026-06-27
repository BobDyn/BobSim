#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/*
equation index: 1483
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] = (chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] * sin(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1483(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1483};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3169]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1483;
}

/*
equation index: 1484
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] = (chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] * sin(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1484(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1484};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3168]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1484;
}

/*
equation index: 1485
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] = (chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] * sin(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1485(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1485};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3167]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1485;
}

/*
equation index: 1486
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1486(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1486};
  modelica_real tmp608;
  modelica_real tmp609;
  tmp608 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */);
  tmp609 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3166]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */) = (tmp608 * tmp608) + (1.0 - ((tmp609 * tmp609))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1486;
}

/*
equation index: 1487
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] = (chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] * sin(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1487(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1487};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3165]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1487;
}

/*
equation index: 1488
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] = (chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] * sin(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1488(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1488};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3164]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1488;
}

/*
equation index: 1489
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] = (chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] + chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] * sin(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1489(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1489};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3163]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[790]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1489;
}

/*
equation index: 1490
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1490(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1490};
  modelica_real tmp610;
  modelica_real tmp611;
  tmp610 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */);
  tmp611 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[789]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3162]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */) = (tmp610 * tmp610) + (1.0 - ((tmp611 * tmp611))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1490;
}

/*
equation index: 1491
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi = $START.chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1491(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1491};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */) = ((modelica_real *)((data->modelData->realVarsData[22] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1491;
}

/*
equation index: 1492
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1492(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1492};
  modelica_real tmp612;
  modelica_real tmp613;
  tmp612 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */);
  tmp613 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4933]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */) = (tmp612 * tmp612) + (1.0 - ((tmp613 * tmp613))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1492;
}

/*
equation index: 1493
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] = (chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] * sin(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1493(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1493};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4932]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1493;
}

/*
equation index: 1494
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] = (chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] * sin(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1494(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1494};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4931]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1494;
}

/*
equation index: 1495
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] = (chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] * sin(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1495(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1495};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4930]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1495;
}

/*
equation index: 1496
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1496(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1496};
  modelica_real tmp614;
  modelica_real tmp615;
  tmp614 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */);
  tmp615 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4929]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */) = (tmp614 * tmp614) + (1.0 - ((tmp615 * tmp615))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1496;
}

/*
equation index: 1497
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] = (chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] * sin(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1497(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1497};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4928]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1497;
}

/*
equation index: 1498
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] = (chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] * sin(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1498(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1498};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4927]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1498;
}

/*
equation index: 1499
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] = (chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] + chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] * sin(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1499(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1499};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4926]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1879]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1880]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1499;
}

/*
equation index: 1500
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] = chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1500(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1500};
  modelica_real tmp616;
  modelica_real tmp617;
  tmp616 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */);
  tmp617 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1878]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4925]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */) = (tmp616 * tmp616) + (1.0 - ((tmp617 * tmp617))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1500;
}

/*
equation index: 1501
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1501(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1501};
  ((modelica_real *)((data->modelData->realVarsData[5689] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2248]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5689]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[5689] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[5689].info /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5689]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] DUMMY_STATE */));
  threadData->lastEquationSolved = 1501;
}

/*
equation index: 1502
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1502(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1502};
  ((modelica_real *)((data->modelData->realVarsData[5690] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2249]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5690]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[5690] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[5690].info /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5690]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] DUMMY_STATE */));
  threadData->lastEquationSolved = 1502;
}

/*
equation index: 1503
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1503(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1503};
  ((modelica_real *)((data->modelData->realVarsData[5691] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2250]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5691]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[5691] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[5691].info /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5691]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1503;
}

/*
equation index: 1504
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1504(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1504};
  ((modelica_real *)((data->modelData->realVarsData[5692] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2248]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5692]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[5692] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[5692].info /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5692]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] DUMMY_STATE */));
  threadData->lastEquationSolved = 1504;
}

/*
equation index: 1505
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1505(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1505};
  ((modelica_real *)((data->modelData->realVarsData[5693] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2249]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5693]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[5693] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[5693].info /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5693]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] DUMMY_STATE */));
  threadData->lastEquationSolved = 1505;
}

/*
equation index: 1506
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1506(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1506};
  ((modelica_real *)((data->modelData->realVarsData[5694] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2250]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5694]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[5694] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[5694].info /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5694]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1506;
}

/*
equation index: 1507
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1507(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1507};
  ((modelica_real *)((data->modelData->realVarsData[4753] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4753]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[4753] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4753].info /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4753]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[1] DUMMY_STATE */));
  threadData->lastEquationSolved = 1507;
}

/*
equation index: 1508
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1508(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1508};
  ((modelica_real *)((data->modelData->realVarsData[4754] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1706]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4754]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[4754] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4754].info /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4754]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[2] DUMMY_STATE */));
  threadData->lastEquationSolved = 1508;
}

/*
equation index: 1509
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1509(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1509};
  ((modelica_real *)((data->modelData->realVarsData[4755] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1707]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4755]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[4755] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4755].info /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4755]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_0[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1509;
}

/*
equation index: 1510
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1510(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1510};
  ((modelica_real *)((data->modelData->realVarsData[4756] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1705]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4756]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] variable */) = ((modelica_real *)((data->modelData->realVarsData[4756] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4756].info /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4756]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[1] variable */));
  threadData->lastEquationSolved = 1510;
}

/*
equation index: 1511
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1511(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1511};
  ((modelica_real *)((data->modelData->realVarsData[4757] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1706]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4757]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] variable */) = ((modelica_real *)((data->modelData->realVarsData[4757] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4757].info /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4757]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[2] variable */));
  threadData->lastEquationSolved = 1511;
}

/*
equation index: 1512
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] = chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1512(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1512};
  ((modelica_real *)((data->modelData->realVarsData[4758] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1707]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4758]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] variable */) = ((modelica_real *)((data->modelData->realVarsData[4758] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4758].info /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4758]] /* chassis.detailedChassis.frAxleDW.rightTieRod.rod.rRod_a[3] variable */));
  threadData->lastEquationSolved = 1512;
}

/*
equation index: 1513
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[1] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1513(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1513};
  ((modelica_real *)((data->modelData->realVarsData[4522] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1600]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4522]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[4522] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4522].info /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4522]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */));
  threadData->lastEquationSolved = 1513;
}

/*
equation index: 1514
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[2] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1514(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1514};
  ((modelica_real *)((data->modelData->realVarsData[4523] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1601]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4523]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[4523] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4523].info /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4523]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */));
  threadData->lastEquationSolved = 1514;
}

/*
equation index: 1515
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[3] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1515(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1515};
  ((modelica_real *)((data->modelData->realVarsData[4524] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1602]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4524]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[4524] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4524].info /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4524]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1515;
}

/*
equation index: 1516
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[1] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1516(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1516};
  ((modelica_real *)((data->modelData->realVarsData[4525] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[1] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1600]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4525]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[1] variable */) = ((modelica_real *)((data->modelData->realVarsData[4525] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[1] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4525].info /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4525]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[1] variable */));
  threadData->lastEquationSolved = 1516;
}

/*
equation index: 1517
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[2] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1517(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1517};
  ((modelica_real *)((data->modelData->realVarsData[4526] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[2] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1601]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4526]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[2] variable */) = ((modelica_real *)((data->modelData->realVarsData[4526] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[2] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4526].info /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4526]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[2] variable */));
  threadData->lastEquationSolved = 1517;
}

/*
equation index: 1518
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[3] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1518(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1518};
  ((modelica_real *)((data->modelData->realVarsData[4527] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[3] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1602]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4527]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[3] variable */) = ((modelica_real *)((data->modelData->realVarsData[4527] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[3] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[4527].info /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4527]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_a[3] variable */));
  threadData->lastEquationSolved = 1518;
}

/*
equation index: 1519
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi = $START.chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1519(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1519};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */) = ((modelica_real *)((data->modelData->realVarsData[28] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1519;
}

/*
equation index: 1520
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1520(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1520};
  modelica_real tmp618;
  modelica_real tmp619;
  tmp618 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */);
  tmp619 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6924]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */) = (tmp618 * tmp618) + (1.0 - ((tmp619 * tmp619))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1520;
}

/*
equation index: 1521
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] = (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] * sin(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1521(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1521};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6923]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,2] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1521;
}

/*
equation index: 1522
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] = (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] * sin(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1522(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1522};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6922]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,1] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1522;
}

/*
equation index: 1523
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] = (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] * sin(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1523(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1523};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6921]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,3] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1523;
}

/*
equation index: 1524
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1524(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1524};
  modelica_real tmp620;
  modelica_real tmp621;
  tmp620 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */);
  tmp621 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6920]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,2] variable */) = (tmp620 * tmp620) + (1.0 - ((tmp621 * tmp621))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1524;
}

/*
equation index: 1525
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] = (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] * sin(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1525(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1525};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6919]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[2,1] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1525;
}

/*
equation index: 1526
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] = (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] * sin(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1526(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1526};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6918]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,3] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1526;
}

/*
equation index: 1527
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] = (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] * sin(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1527(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1527};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6917]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,2] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3039]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3040]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1527;
}

/*
equation index: 1528
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1528(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1528};
  modelica_real tmp622;
  modelica_real tmp623;
  tmp622 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */);
  tmp623 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3038]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6916]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[1,1] variable */) = (tmp622 * tmp622) + (1.0 - ((tmp623 * tmp623))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1528;
}

/*
equation index: 1529
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi = $START.chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1529(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1529};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */) = ((modelica_real *)((data->modelData->realVarsData[34] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1529;
}

/*
equation index: 1530
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1530(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1530};
  modelica_real tmp624;
  modelica_real tmp625;
  tmp624 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */);
  tmp625 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8690]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,3] variable */) = (tmp624 * tmp624) + (1.0 - ((tmp625 * tmp625))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1530;
}

/*
equation index: 1531
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] = (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] * sin(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1531(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1531};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8689]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,2] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1531;
}

/*
equation index: 1532
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] = (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] * sin(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1532(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1532};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8688]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[3,1] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1532;
}

/*
equation index: 1533
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] = (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] * sin(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1533(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1533};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8687]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,3] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1533;
}

/*
equation index: 1534
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1534(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1534};
  modelica_real tmp626;
  modelica_real tmp627;
  tmp626 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */);
  tmp627 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8686]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,2] variable */) = (tmp626 * tmp626) + (1.0 - ((tmp627 * tmp627))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1534;
}

/*
equation index: 1535
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] = (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] * sin(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1535(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1535};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8685]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[2,1] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1535;
}

/*
equation index: 1536
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] = (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] * sin(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1536(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1536};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8684]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,3] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))));
  threadData->lastEquationSolved = 1536;
}

/*
equation index: 1537
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] = (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)) * chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] * sin(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1537(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1537};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8683]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,2] variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4128]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4129]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1537;
}

/*
equation index: 1538
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1538(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1538};
  modelica_real tmp628;
  modelica_real tmp629;
  tmp628 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */);
  tmp629 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4127]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8682]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.R_rel.T[1,1] variable */) = (tmp628 * tmp628) + (1.0 - ((tmp629 * tmp629))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1538;
}

/*
equation index: 1539
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1539(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1539};
  ((modelica_real *)((data->modelData->realVarsData[9446] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4497]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9446]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[9446] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[9446].info /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9446]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[1] DUMMY_STATE */));
  threadData->lastEquationSolved = 1539;
}

/*
equation index: 1540
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1540(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1540};
  ((modelica_real *)((data->modelData->realVarsData[9447] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4498]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9447]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[9447] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[9447].info /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9447]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[2] DUMMY_STATE */));
  threadData->lastEquationSolved = 1540;
}

/*
equation index: 1541
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1541(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1541};
  ((modelica_real *)((data->modelData->realVarsData[9448] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4499]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9448]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[9448] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[9448].info /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9448]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_0[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1541;
}

/*
equation index: 1542
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1542(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1542};
  ((modelica_real *)((data->modelData->realVarsData[9449] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4497]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9449]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[9449] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[9449].info /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9449]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[1] DUMMY_STATE */));
  threadData->lastEquationSolved = 1542;
}

/*
equation index: 1543
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1543(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1543};
  ((modelica_real *)((data->modelData->realVarsData[9450] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4498]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9450]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[9450] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[9450].info /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9450]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[2] DUMMY_STATE */));
  threadData->lastEquationSolved = 1543;
}

/*
equation index: 1544
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1544(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1544};
  ((modelica_real *)((data->modelData->realVarsData[9451] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4499]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9451]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[9451] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[9451].info /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9451]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_a[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1544;
}

/*
equation index: 1545
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[1] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1545(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1545};
  ((modelica_real *)((data->modelData->realVarsData[8510] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3954]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8510]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[1] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[8510] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8510].info /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8510]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[1] DUMMY_STATE */));
  threadData->lastEquationSolved = 1545;
}

/*
equation index: 1546
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[2] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1546(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1546};
  ((modelica_real *)((data->modelData->realVarsData[8511] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3955]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8511]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[2] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[8511] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8511].info /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8511]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[2] DUMMY_STATE */));
  threadData->lastEquationSolved = 1546;
}

/*
equation index: 1547
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[3] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1547(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1547};
  ((modelica_real *)((data->modelData->realVarsData[8512] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3956]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8512]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[3] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[8512] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8512].info /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8512]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_0[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1547;
}

/*
equation index: 1548
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[1] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1548(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1548};
  ((modelica_real *)((data->modelData->realVarsData[8513] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[1] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3954]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8513]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[1] variable */) = ((modelica_real *)((data->modelData->realVarsData[8513] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[1] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8513].info /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8513]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[1] variable */));
  threadData->lastEquationSolved = 1548;
}

/*
equation index: 1549
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[2] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1549(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1549};
  ((modelica_real *)((data->modelData->realVarsData[8514] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[2] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3955]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8514]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[2] variable */) = ((modelica_real *)((data->modelData->realVarsData[8514] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[2] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8514].info /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8514]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[2] variable */));
  threadData->lastEquationSolved = 1549;
}

/*
equation index: 1550
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[3] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1550(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1550};
  ((modelica_real *)((data->modelData->realVarsData[8515] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[3] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3956]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8515]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[3] variable */) = ((modelica_real *)((data->modelData->realVarsData[8515] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[3] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8515].info /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8515]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_a[3] variable */));
  threadData->lastEquationSolved = 1550;
}

/*
equation index: 1551
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1551(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1551};
  ((modelica_real *)((data->modelData->realVarsData[8279] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3849]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8279]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[8279] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8279].info /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8279]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[1] DUMMY_STATE */));
  threadData->lastEquationSolved = 1551;
}

/*
equation index: 1552
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1552(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1552};
  ((modelica_real *)((data->modelData->realVarsData[8280] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3850]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8280]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[8280] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8280].info /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8280]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[2] DUMMY_STATE */));
  threadData->lastEquationSolved = 1552;
}

/*
equation index: 1553
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1553(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1553};
  ((modelica_real *)((data->modelData->realVarsData[8281] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3851]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8281]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */) = ((modelica_real *)((data->modelData->realVarsData[8281] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8281].info /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8281]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_0[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1553;
}

/*
equation index: 1554
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1554(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1554};
  ((modelica_real *)((data->modelData->realVarsData[8282] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[1] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3849]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8282]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[1] variable */) = ((modelica_real *)((data->modelData->realVarsData[8282] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[1] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8282].info /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[1] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8282]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[1] variable */));
  threadData->lastEquationSolved = 1554;
}

/*
equation index: 1555
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1555(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1555};
  ((modelica_real *)((data->modelData->realVarsData[8283] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[2] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3850]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[2] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8283]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[2] variable */) = ((modelica_real *)((data->modelData->realVarsData[8283] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[2] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8283].info /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[2] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8283]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[2] variable */));
  threadData->lastEquationSolved = 1555;
}

/*
equation index: 1556
type: SIMPLE_ASSIGN
$START.chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1556(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1556};
  ((modelica_real *)((data->modelData->realVarsData[8284] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[3] variable */).attribute .start.data))[0] = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3851]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[3] PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8284]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[3] variable */) = ((modelica_real *)((data->modelData->realVarsData[8284] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[3] variable */).attribute .start.data))[0];
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[8284].info /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[3] */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8284]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_a[3] variable */));
  threadData->lastEquationSolved = 1556;
}

/*
equation index: 1557
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.w = $START.chassis.detailedChassis.spaceFrame.torsionalRevolute.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1557(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1557};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */) = ((modelica_real *)((data->modelData->realVarsData[39] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1557;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28888(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28887(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28886(DATA *data, threadData_t *threadData);


/*
equation index: 1561
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,1] = (1.0 - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] ^ 2.0) * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1561(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1561};
  modelica_real tmp630;
  tmp630 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2001]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,1]) DUMMY_DER */) = (1.0 - ((tmp630 * tmp630))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)));
  threadData->lastEquationSolved = 1561;
}

/*
equation index: 1562
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,2] = (-chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1]) * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1562(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1562};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2002]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,2]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */))));
  threadData->lastEquationSolved = 1562;
}

/*
equation index: 1563
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,3] = chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1563(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1563};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2003]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,3]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)))));
  threadData->lastEquationSolved = 1563;
}

/*
equation index: 1564
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,1] = chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1564(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1564};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2004]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,1]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)))));
  threadData->lastEquationSolved = 1564;
}

/*
equation index: 1565
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,2] = (1.0 - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] ^ 2.0) * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1565(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1565};
  modelica_real tmp631;
  tmp631 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2005]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,2]) DUMMY_DER */) = (1.0 - ((tmp631 * tmp631))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)));
  threadData->lastEquationSolved = 1565;
}

/*
equation index: 1566
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,3] = (-chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2]) * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1566(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1566};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2006]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,3]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */))));
  threadData->lastEquationSolved = 1566;
}

/*
equation index: 1567
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,1] = (-chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3]) * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1567(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1567};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2007]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,1]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */))));
  threadData->lastEquationSolved = 1567;
}

/*
equation index: 1568
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,2] = chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] * cos(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w * chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1568(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1568};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2008]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,2]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4979]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4980]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[2] PARAM */)))));
  threadData->lastEquationSolved = 1568;
}

/*
equation index: 1569
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,3] = (1.0 - chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] ^ 2.0) * (-sin(chassis.detailedChassis.spaceFrame.torsionalRevolute.phi)) * chassis.detailedChassis.spaceFrame.torsionalRevolute.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1569(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1569};
  modelica_real tmp632;
  tmp632 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4981]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2009]] /* der(chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,3]) DUMMY_DER */) = (1.0 - ((tmp632 * tmp632))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.phi STATE(1,chassis.detailedChassis.spaceFrame.torsionalRevolute.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.w STATE(1,chassis.detailedChassis.spaceFrame.damper.a_rel) */)));
  threadData->lastEquationSolved = 1569;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28761(DATA *data, threadData_t *threadData);


/*
equation index: 1571
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.damper.phi_rel = chassis.detailedChassis.spaceFrame.damper.w_rel
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1571(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1571};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1988]] /* der(chassis.detailedChassis.spaceFrame.damper.phi_rel) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9833]] /* chassis.detailedChassis.spaceFrame.damper.w_rel DUMMY_STATE */);
  threadData->lastEquationSolved = 1571;
}

/*
equation index: 1572
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.damper.tau = chassis.detailedChassis.spaceFrame.damper.d * chassis.detailedChassis.spaceFrame.damper.w_rel
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1572(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1572};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9832]] /* chassis.detailedChassis.spaceFrame.damper.tau variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4843]] /* chassis.detailedChassis.spaceFrame.damper.d PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9833]] /* chassis.detailedChassis.spaceFrame.damper.w_rel DUMMY_STATE */));
  threadData->lastEquationSolved = 1572;
}

/*
equation index: 1573
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.damper.lossPower = chassis.detailedChassis.spaceFrame.damper.tau * chassis.detailedChassis.spaceFrame.damper.w_rel
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1573(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1573};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9830]] /* chassis.detailedChassis.spaceFrame.damper.lossPower variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9832]] /* chassis.detailedChassis.spaceFrame.damper.tau variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9833]] /* chassis.detailedChassis.spaceFrame.damper.w_rel DUMMY_STATE */));
  threadData->lastEquationSolved = 1573;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28841(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28842(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28836(DATA *data, threadData_t *threadData);


/*
equation index: 1577
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.r_rel_a[1] = $START.chassis.cgFreeMotion.r_rel_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1577(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1577};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* chassis.cgFreeMotion.r_rel_a[1] STATE(1,chassis.cgFreeMotion.v_rel_a[1]) */) = ((modelica_real *)((data->modelData->realVarsData[8] /* chassis.cgFreeMotion.r_rel_a[1] STATE(1,chassis.cgFreeMotion.v_rel_a[1]) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1577;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28985(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28986(DATA *data, threadData_t *threadData);


/*
equation index: 1580
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.r_rel_a[2] = $START.chassis.cgFreeMotion.r_rel_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1580(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1580};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* chassis.cgFreeMotion.r_rel_a[2] STATE(1,chassis.cgFreeMotion.v_rel_a[2]) */) = ((modelica_real *)((data->modelData->realVarsData[9] /* chassis.cgFreeMotion.r_rel_a[2] STATE(1,chassis.cgFreeMotion.v_rel_a[2]) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1580;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28983(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28984(DATA *data, threadData_t *threadData);


/*
equation index: 1583
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.r_rel_a[3] = $START.chassis.cgFreeMotion.r_rel_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1583(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1583};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* chassis.cgFreeMotion.r_rel_a[3] STATE(1,chassis.cgFreeMotion.v_rel_a[3]) */) = ((modelica_real *)((data->modelData->realVarsData[10] /* chassis.cgFreeMotion.r_rel_a[3] STATE(1,chassis.cgFreeMotion.v_rel_a[3]) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1583;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28981(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28982(DATA *data, threadData_t *threadData);


/*
equation index: 1586
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.v_rel_a[1] = chassis.initialLongitudinalVelocity
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1586(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1586};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* chassis.cgFreeMotion.v_rel_a[1] STATE(1,chassis.cgFreeMotion.a_rel_a[1]) */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5078]] /* chassis.initialLongitudinalVelocity PARAM */);
  threadData->lastEquationSolved = 1586;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28760(DATA *data, threadData_t *threadData);


/*
equation index: 1588
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.v_0[1] = $DER.aeroModel.sprungChassisFrame.r_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1588(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1588};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9939]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[873]] /* der(aeroModel.sprungChassisFrame.r_0[1]) DUMMY_DER */);
  threadData->lastEquationSolved = 1588;
}

/*
equation index: 1589
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[1] = chassis.detailedChassis.spaceFrame.sprungBody.v_0[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1589(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1589};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1993]] /* der(chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9939]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 1589;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28843(DATA *data, threadData_t *threadData);


/*
equation index: 1591
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.v_rel_a[2] = $START.chassis.cgFreeMotion.v_rel_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1591(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1591};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* chassis.cgFreeMotion.v_rel_a[2] STATE(1,chassis.cgFreeMotion.a_rel_a[2]) */) = ((modelica_real *)((data->modelData->realVarsData[12] /* chassis.cgFreeMotion.v_rel_a[2] STATE(1,chassis.cgFreeMotion.a_rel_a[2]) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1591;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28758(DATA *data, threadData_t *threadData);


/*
equation index: 1593
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.v_0[2] = $DER.aeroModel.sprungChassisFrame.r_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1593(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1593};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9940]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[874]] /* der(aeroModel.sprungChassisFrame.r_0[2]) DUMMY_DER */);
  threadData->lastEquationSolved = 1593;
}

/*
equation index: 1594
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[2] = chassis.detailedChassis.spaceFrame.sprungBody.v_0[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1594(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1594};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1994]] /* der(chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[2]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9940]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 1594;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28844(DATA *data, threadData_t *threadData);


/*
equation index: 1596
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.v_rel_a[3] = $START.chassis.cgFreeMotion.v_rel_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1596(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1596};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* chassis.cgFreeMotion.v_rel_a[3] STATE(1,chassis.cgFreeMotion.a_rel_a[3]) */) = ((modelica_real *)((data->modelData->realVarsData[13] /* chassis.cgFreeMotion.v_rel_a[3] STATE(1,chassis.cgFreeMotion.a_rel_a[3]) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1596;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28756(DATA *data, threadData_t *threadData);


/*
equation index: 1598
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.v_0[3] = $DER.aeroModel.sprungChassisFrame.r_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1598(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1598};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9941]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[3] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[875]] /* der(aeroModel.sprungChassisFrame.r_0[3]) DUMMY_DER */);
  threadData->lastEquationSolved = 1598;
}

/*
equation index: 1599
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[3] = chassis.detailedChassis.spaceFrame.sprungBody.v_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1599(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1599};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1995]] /* der(chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[3]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9941]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 1599;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28845(DATA *data, threadData_t *threadData);


/*
equation index: 1601
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.w_rel_b[1] = chassis.cgFreeMotion.w_rel_a_start[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1601(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1601};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2358]] /* chassis.cgFreeMotion.w_rel_b[1] DUMMY_STATE */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[314]] /* chassis.cgFreeMotion.w_rel_a_start[1] PARAM */);
  threadData->lastEquationSolved = 1601;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29301(DATA *data, threadData_t *threadData);


/*
equation index: 1603
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.w_rel_b[2] = chassis.cgFreeMotion.w_rel_a_start[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1603(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1603};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2359]] /* chassis.cgFreeMotion.w_rel_b[2] DUMMY_STATE */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[315]] /* chassis.cgFreeMotion.w_rel_a_start[2] PARAM */);
  threadData->lastEquationSolved = 1603;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29079(DATA *data, threadData_t *threadData);


/*
equation index: 1605
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.w_rel_b[3] = chassis.cgFreeMotion.w_rel_a_start[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1605(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1605};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2360]] /* chassis.cgFreeMotion.w_rel_b[3] DUMMY_STATE */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[316]] /* chassis.cgFreeMotion.w_rel_a_start[3] PARAM */);
  threadData->lastEquationSolved = 1605;
}

/*
equation index: 1606
type: SIMPLE_ASSIGN
yawVel = chassis.cgFreeMotion.w_rel_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1606(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1606};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2360]] /* chassis.cgFreeMotion.w_rel_b[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 1606;
}

/*
equation index: 1607
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.w_a[1] = chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] * yawVel + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1607(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1607};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2692]] /* chassis.detailedChassis.frAxleDW.leftLCABody.w_a[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3605]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3606]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3612]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.w[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 1607;
}

/*
equation index: 1608
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.w_a[2] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] * yawVel + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1608(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1608};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2693]] /* chassis.detailedChassis.frAxleDW.leftLCABody.w_a[2] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3607]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3611]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3608]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3613]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.w[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 1608;
}

/*
equation index: 1609
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.w_a[3] = chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] * yawVel + chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1609(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1609};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2694]] /* chassis.detailedChassis.frAxleDW.leftLCABody.w_a[3] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3609]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3610]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3611]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3614]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.R_rel.w[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 1609;
}

/*
equation index: 1610
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.w_a[1] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] * yawVel + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1610(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1610};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4452]] /* chassis.detailedChassis.frAxleDW.rightLCABody.w_a[1] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5359]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5360]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5361]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5368]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.w[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 1610;
}

/*
equation index: 1611
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.w_a[2] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] * yawVel + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1611(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1611};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4453]] /* chassis.detailedChassis.frAxleDW.rightLCABody.w_a[2] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5362]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5363]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5364]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5369]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.w[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 1611;
}

/*
equation index: 1612
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.w_a[3] = chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] * yawVel + chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1612(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1612};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4454]] /* chassis.detailedChassis.frAxleDW.rightLCABody.w_a[3] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5365]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5366]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5367]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5370]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.w[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 1612;
}

/*
equation index: 1613
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleFrame.R.w[1] = chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,3] * yawVel + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.w[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1613(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1613};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9817]] /* chassis.detailedChassis.rrAxleFrame.R.w[1] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9947]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9948]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9949]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9956]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.w[1] DUMMY_STATE */);
  threadData->lastEquationSolved = 1613;
}

/*
equation index: 1614
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleFrame.R.w[2] = chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,3] * yawVel + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.w[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1614(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1614};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9818]] /* chassis.detailedChassis.rrAxleFrame.R.w[2] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9950]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9951]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9952]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9957]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.w[2] DUMMY_STATE */);
  threadData->lastEquationSolved = 1614;
}

/*
equation index: 1615
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleFrame.R.w[3] = chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,2] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,3] * yawVel + chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.w[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1615(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1615};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9819]] /* chassis.detailedChassis.rrAxleFrame.R.w[3] DUMMY_STATE */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9953]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9954]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9955]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.T[3,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9958]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.R_rel.w[3] DUMMY_STATE */);
  threadData->lastEquationSolved = 1615;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30266(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30273(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30804(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29488(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29495(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29865(DATA *data, threadData_t *threadData);


/*
equation index: 1622
type: SIMPLE_ASSIGN
battery.battery.v_rc = $START.battery.battery.v_rc
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1622(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1622};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* battery.battery.v_rc STATE(1) */) = ((modelica_real *)((data->modelData->realVarsData[1] /* battery.battery.v_rc STATE(1) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1622;
}

/*
equation index: 1623
type: SIMPLE_ASSIGN
vcu.handwheelRampCmd = $START.vcu.handwheelRampCmd
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1623(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1623};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* vcu.handwheelRampCmd STATE(1,handwheelRateCmd) */) = ((modelica_real *)((data->modelData->realVarsData[44] /* vcu.handwheelRampCmd STATE(1,handwheelRateCmd) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1623;
}

/*
equation index: 1624
type: SIMPLE_ASSIGN
vcu.tireNormalLoadStopXi = $START.vcu.tireNormalLoadStopXi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1624(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1624};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[48]] /* vcu.tireNormalLoadStopXi STATE(1) */) = ((modelica_real *)((data->modelData->realVarsData[48] /* vcu.tireNormalLoadStopXi STATE(1) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1624;
}

/*
equation index: 1625
type: SIMPLE_ASSIGN
tireNormalLoadRateXi = min(1.0, max(0.0, vcu.tireNormalLoadStopXi))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1625(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1625};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10282]] /* tireNormalLoadRateXi DUMMY_STATE */) = fmin(1.0,fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[48]] /* vcu.tireNormalLoadStopXi STATE(1) */)));
  threadData->lastEquationSolved = 1625;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29014(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29015(DATA *data, threadData_t *threadData);


/*
equation index: 1628
type: SIMPLE_ASSIGN
$DER.handwheelAngle = if vcu.useMode == 0 and noEvent(time >= vcu.steerStart) then handwheelRateCmd else if vcu.useMode == 1 then $DER.steerSine else if vcu.useMode == 2 then $DER.steerStep else if vcu.useMode == 3 then $DER.vcu.steadyStateSteerCmd else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1628(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1628};
  modelica_boolean tmp633;
  tmp633 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6875]] /* vcu.steerStart PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2045]] /* der(handwheelAngle) DUMMY_DER */) = ((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) && tmp633)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10203]] /* handwheelRateCmd DUMMY_STATE */):(((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 1))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2049]] /* der(steerSine) DUMMY_DER */):(((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 2))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2050]] /* der(steerStep) DUMMY_DER */):(((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 3))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[96]] /* der(vcu.steadyStateSteerCmd) STATE_DER */):0.0))));
  threadData->lastEquationSolved = 1628;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29017(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29018(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29019(DATA *data, threadData_t *threadData);


/*
equation index: 1632
type: SIMPLE_ASSIGN
vcu.steadyStateSteerCmd = $START.vcu.steadyStateSteerCmd
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1632(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1632};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[47]] /* vcu.steadyStateSteerCmd STATE(1) */) = ((modelica_real *)((data->modelData->realVarsData[47] /* vcu.steadyStateSteerCmd STATE(1) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1632;
}

/*
equation index: 1633
type: SIMPLE_ASSIGN
$PRE.vcu.steadyStateSteerCmd = vcu.steadyStateSteerCmd
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1633(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1633};
  (data->simulationInfo->realVarsPre[47] /* vcu.steadyStateSteerCmd STATE(1) */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[47]] /* vcu.steadyStateSteerCmd STATE(1) */);
  threadData->lastEquationSolved = 1633;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28975(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28976(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28977(DATA *data, threadData_t *threadData);


/*
equation index: 1637
type: SIMPLE_ASSIGN
$PRE.vcu.rampEndingState = false
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1637(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1637};
  (data->simulationInfo->booleanVarsPre[50] /* vcu.rampEndingState DISCRETE */) = 0 /* false */;
  threadData->lastEquationSolved = 1637;
}

/*
equation index: 1638
type: SIMPLE_ASSIGN
vcu.rampEndingState = $PRE.vcu.rampEndingState
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1638(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1638};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[50]] /* vcu.rampEndingState DISCRETE */) = (data->simulationInfo->booleanVarsPre[50] /* vcu.rampEndingState DISCRETE */);
  threadData->lastEquationSolved = 1638;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32912(DATA *data, threadData_t *threadData);


/*
equation index: 1640
type: SIMPLE_ASSIGN
$whenCondition9 = vcu.useMode == 0 and rampEnding and not $PRE.rampEnding
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1640(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1640};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[21]] /* $whenCondition9 DISCRETE */) = ((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[45]] /* rampEnding DISCRETE */)) && (!(data->simulationInfo->booleanVarsPre[45] /* rampEnding DISCRETE */)));
  threadData->lastEquationSolved = 1640;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32905(DATA *data, threadData_t *threadData);


/*
equation index: 1642
type: SIMPLE_ASSIGN
$DER.tireNormalLoadRateXi = if noEvent(1.0 < max(0.0, vcu.tireNormalLoadStopXi)) then 0.0 else if noEvent(0.0 > vcu.tireNormalLoadStopXi) then 0.0 else $DER.vcu.tireNormalLoadStopXi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1642(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1642};
  modelica_boolean tmp634;
  modelica_boolean tmp635;
  modelica_boolean tmp636;
  modelica_real tmp637;
  tmp634 = Less(1.0,fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[48]] /* vcu.tireNormalLoadStopXi STATE(1) */)));
  tmp636 = (modelica_boolean)tmp634;
  if(tmp636)
  {
    tmp637 = 0.0;
  }
  else
  {
    tmp635 = Greater(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[48]] /* vcu.tireNormalLoadStopXi STATE(1) */));
    tmp637 = (tmp635?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[97]] /* der(vcu.tireNormalLoadStopXi) STATE_DER */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2052]] /* der(tireNormalLoadRateXi) DUMMY_DER */) = tmp637;
  threadData->lastEquationSolved = 1642;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32907(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32908(DATA *data, threadData_t *threadData);


/*
equation index: 1645
type: SIMPLE_ASSIGN
$DER.$DER.handwheelAngle = if vcu.useMode == 0 and noEvent(time >= vcu.steerStart) then $DER.handwheelRateCmd else if vcu.useMode == 1 then $DER.$DER.steerSine else if vcu.useMode == 2 then $DER.$DER.steerStep else if vcu.useMode == 3 then $DER.$DER.vcu.steadyStateSteerCmd else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1645(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1645};
  modelica_boolean tmp638;
  tmp638 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6875]] /* vcu.steerStart PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[869]] /* der(der(handwheelAngle)) DUMMY_DER */) = ((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) && tmp638)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2046]] /* der(handwheelRateCmd) DUMMY_DER */):(((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 1))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[870]] /* der(der(steerSine)) DUMMY_DER */):(((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 2))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[871]] /* der(der(steerStep)) DUMMY_DER */):(((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 3))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[872]] /* der(der(vcu.steadyStateSteerCmd)) DUMMY_DER */):0.0))));
  threadData->lastEquationSolved = 1645;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32910(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32911(DATA *data, threadData_t *threadData);


/*
equation index: 1648
type: SIMPLE_ASSIGN
driveline.diffInputRotor.w = driveline.initialOutputAngularVelocity
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1648(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1648};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* driveline.diffInputRotor.w STATE(1,driveline.diffInputRotor.a) */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5902]] /* driveline.initialOutputAngularVelocity PARAM */);
  threadData->lastEquationSolved = 1648;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28868(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28869(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28871(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28872(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28873(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28874(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28875(DATA *data, threadData_t *threadData);


/*
equation index: 1656
type: SIMPLE_ASSIGN
motor.motor.tau_lim_from_power = motor.motor.P_allow / max(abs(motor.rotor.w), motor.motor.w_eps)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1656(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1656};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10244]] /* motor.motor.tau_lim_from_power variable */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10235]] /* motor.motor.P_allow variable */),fmax(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10249]] /* motor.rotor.w DUMMY_STATE */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6028]] /* motor.motor.w_eps PARAM */)),"max(abs(motor.rotor.w), motor.motor.w_eps)",equationIndexes);
  threadData->lastEquationSolved = 1656;
}

/*
equation index: 1657
type: SIMPLE_ASSIGN
motor.tau_lim = min(motor.motor.T_allow, min(motor.motor.tau_lim_from_power, motor.motor.tau_lim_from_current))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1657(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1657};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10251]] /* motor.tau_lim variable */) = fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10240]] /* motor.motor.T_allow variable */),fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10244]] /* motor.motor.tau_lim_from_power variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10243]] /* motor.motor.tau_lim_from_current variable */)));
  threadData->lastEquationSolved = 1657;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28879(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28881(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28880(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28882(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28859(DATA *data, threadData_t *threadData);


/*
equation index: 1663
type: SIMPLE_ASSIGN
$PRE.linearityReferenceValid = false
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1663(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1663};
  (data->simulationInfo->booleanVarsPre[43] /* linearityReferenceValid DISCRETE */) = 0 /* false */;
  threadData->lastEquationSolved = 1663;
}

/*
equation index: 1664
type: SIMPLE_ASSIGN
linearityReferenceValid = $PRE.linearityReferenceValid
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1664(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1664};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[43]] /* linearityReferenceValid DISCRETE */) = (data->simulationInfo->booleanVarsPre[43] /* linearityReferenceValid DISCRETE */);
  threadData->lastEquationSolved = 1664;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35624(DATA *data, threadData_t *threadData);


/*
equation index: 1666
type: SIMPLE_ASSIGN
$PRE.t_qss_hit = -1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1666(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1666};
  (data->simulationInfo->realVarsPre[10799] /* t_qss_hit DISCRETE */) = -1.0;
  threadData->lastEquationSolved = 1666;
}

/*
equation index: 1667
type: SIMPLE_ASSIGN
t_qss_hit = $PRE.t_qss_hit
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1667(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1667};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10799]] /* t_qss_hit DISCRETE */) = (data->simulationInfo->realVarsPre[10799] /* t_qss_hit DISCRETE */);
  threadData->lastEquationSolved = 1667;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35593(DATA *data, threadData_t *threadData);


/*
equation index: 1669
type: SIMPLE_ASSIGN
$PRE.t_ramp_end_hit = -1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1669(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1669};
  (data->simulationInfo->realVarsPre[10800] /* t_ramp_end_hit DISCRETE */) = -1.0;
  threadData->lastEquationSolved = 1669;
}

/*
equation index: 1670
type: SIMPLE_ASSIGN
t_ramp_end_hit = $PRE.t_ramp_end_hit
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1670(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1670};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10800]] /* t_ramp_end_hit DISCRETE */) = (data->simulationInfo->realVarsPre[10800] /* t_ramp_end_hit DISCRETE */);
  threadData->lastEquationSolved = 1670;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32915(DATA *data, threadData_t *threadData);


/*
equation index: 1672
type: SIMPLE_ASSIGN
$PRE.t_linearity_limit_hit = -1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1672(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1672};
  (data->simulationInfo->realVarsPre[10798] /* t_linearity_limit_hit DISCRETE */) = -1.0;
  threadData->lastEquationSolved = 1672;
}

/*
equation index: 1673
type: SIMPLE_ASSIGN
t_linearity_limit_hit = $PRE.t_linearity_limit_hit
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1673(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1673};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10798]] /* t_linearity_limit_hit DISCRETE */) = (data->simulationInfo->realVarsPre[10798] /* t_linearity_limit_hit DISCRETE */);
  threadData->lastEquationSolved = 1673;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35630(DATA *data, threadData_t *threadData);


/*
equation index: 1675
type: SIMPLE_ASSIGN
$PRE.t_spinout_hit = -1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1675(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1675};
  (data->simulationInfo->realVarsPre[10801] /* t_spinout_hit DISCRETE */) = -1.0;
  threadData->lastEquationSolved = 1675;
}

/*
equation index: 1676
type: SIMPLE_ASSIGN
t_spinout_hit = $PRE.t_spinout_hit
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1676(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1676};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10801]] /* t_spinout_hit DISCRETE */) = (data->simulationInfo->realVarsPre[10801] /* t_spinout_hit DISCRETE */);
  threadData->lastEquationSolved = 1676;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29245(DATA *data, threadData_t *threadData);


/*
equation index: 1678
type: SIMPLE_ASSIGN
$PRE.t_yawVel_hit = -1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1678(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1678};
  (data->simulationInfo->realVarsPre[10803] /* t_yawVel_hit DISCRETE */) = -1.0;
  threadData->lastEquationSolved = 1678;
}

/*
equation index: 1679
type: SIMPLE_ASSIGN
t_yawVel_hit = $PRE.t_yawVel_hit
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1679(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1679};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10803]] /* t_yawVel_hit DISCRETE */) = (data->simulationInfo->realVarsPre[10803] /* t_yawVel_hit DISCRETE */);
  threadData->lastEquationSolved = 1679;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_35588(DATA *data, threadData_t *threadData);


/*
equation index: 1681
type: SIMPLE_ASSIGN
driveline.rightHalfshaft.phi_rel = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1681(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1681};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10192]] /* driveline.rightHalfshaft.phi_rel DUMMY_STATE */) = 0.0;
  threadData->lastEquationSolved = 1681;
}

/*
equation index: 1682
type: SIMPLE_ASSIGN
driveline.differential.shaft_right.phi = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi - driveline.rightHalfshaft.phi_rel
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1682(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1682};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10157]] /* driveline.differential.shaft_right.phi DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10192]] /* driveline.rightHalfshaft.phi_rel DUMMY_STATE */);
  threadData->lastEquationSolved = 1682;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28907(DATA *data, threadData_t *threadData);


/*
equation index: 1684
type: SIMPLE_ASSIGN
driveline.leftHalfshaft.phi_rel = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1684(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1684};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10184]] /* driveline.leftHalfshaft.phi_rel DUMMY_STATE */) = 0.0;
  threadData->lastEquationSolved = 1684;
}

/*
equation index: 1685
type: SIMPLE_ASSIGN
driveline.differential.shaft_left.phi = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi - driveline.leftHalfshaft.phi_rel
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1685(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1685};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* driveline.differential.shaft_left.phi STATE(1,driveline.differential.w_l) */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10184]] /* driveline.leftHalfshaft.phi_rel DUMMY_STATE */);
  threadData->lastEquationSolved = 1685;
}

/*
equation index: 1686
type: SIMPLE_ASSIGN
driveline.diffInputRotor.phi = 0.5 * (driveline.differential.shaft_left.phi + driveline.differential.shaft_right.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1686(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1686};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* driveline.diffInputRotor.phi STATE(1,driveline.diffInputRotor.w) */) = (0.5) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* driveline.differential.shaft_left.phi STATE(1,driveline.differential.w_l) */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10157]] /* driveline.differential.shaft_right.phi DUMMY_STATE */));
  threadData->lastEquationSolved = 1686;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28971(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28972(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28904(DATA *data, threadData_t *threadData);


/*
equation index: 1690
type: SIMPLE_ASSIGN
vcu.speedPI.gainPID.y = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1690(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1690};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10319]] /* vcu.speedPI.gainPID.y variable */) = 0.0;
  threadData->lastEquationSolved = 1690;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29149(DATA *data, threadData_t *threadData);


/*
equation index: 1692
type: SIMPLE_ASSIGN
vcu.speedPI.y = homotopy(smooth(0, if vcu.speedPI.limiter.simplifiedExpr > vcu.speedPI.limiter.uMax then vcu.speedPI.limiter.uMax else if vcu.speedPI.limiter.simplifiedExpr < vcu.speedPI.limiter.uMin then vcu.speedPI.limiter.uMin else vcu.speedPI.limiter.simplifiedExpr), vcu.speedPI.limiter.simplifiedExpr)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1692(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1692};
  modelica_boolean tmp639;
  modelica_boolean tmp640;
  modelica_boolean tmp641;
  modelica_real tmp642;
  tmp639 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10321]] /* vcu.speedPI.limiter.simplifiedExpr variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6859]] /* vcu.speedPI.limiter.uMax PARAM */));
  tmp641 = (modelica_boolean)tmp639;
  if(tmp641)
  {
    tmp642 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6859]] /* vcu.speedPI.limiter.uMax PARAM */);
  }
  else
  {
    tmp640 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10321]] /* vcu.speedPI.limiter.simplifiedExpr variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6860]] /* vcu.speedPI.limiter.uMin PARAM */));
    tmp642 = (tmp640?(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6860]] /* vcu.speedPI.limiter.uMin PARAM */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10321]] /* vcu.speedPI.limiter.simplifiedExpr variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10322]] /* vcu.speedPI.y variable */) = homotopy(tmp642, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10321]] /* vcu.speedPI.limiter.simplifiedExpr variable */));
  threadData->lastEquationSolved = 1692;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29151(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29154(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29155(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29217(DATA *data, threadData_t *threadData);


/*
equation index: 1697
type: SIMPLE_ASSIGN
brakes.mechanicalBrakeTorqueRequest = min(brakes.maxTorque, max(0.0, vcu.mechanicalBrakeTorqueCmd))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1697(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1697};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2287]] /* brakes.mechanicalBrakeTorqueRequest variable */) = fmin((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[274]] /* brakes.maxTorque PARAM */),fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10304]] /* vcu.mechanicalBrakeTorqueCmd variable */)));
  threadData->lastEquationSolved = 1697;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29225(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29226(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29221(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29222(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29218(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29152(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29153(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29156(DATA *data, threadData_t *threadData);


/*
equation index: 1706
type: SIMPLE_ASSIGN
vcu.motorTorqueRequest.y = vcu.driveTorqueCmd / max(vcu.finalDriveRatio, 1e-6)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1706(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1706};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10305]] /* vcu.motorTorqueRequest.y variable */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10300]] /* vcu.driveTorqueCmd variable */),fmax((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6824]] /* vcu.finalDriveRatio PARAM */),1e-6),"max(vcu.finalDriveRatio, 1e-6)",equationIndexes);
  threadData->lastEquationSolved = 1706;
}

/*
equation index: 1707
type: SIMPLE_ASSIGN
vcu.tau_cmd_limited = min(max(vcu.motorTorqueRequest.y, -vcu.regenLimitCmd), vcu.vcu.tau_max)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1707(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1707};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10324]] /* vcu.tau_cmd_limited variable */) = fmin(fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10305]] /* vcu.motorTorqueRequest.y variable */),(-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10310]] /* vcu.regenLimitCmd variable */))),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6882]] /* vcu.vcu.tau_max PARAM */));
  threadData->lastEquationSolved = 1707;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29160(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29161(DATA *data, threadData_t *threadData);


/*
equation index: 1710
type: SIMPLE_ASSIGN
inverter.inverter.P_req_nameplate = max(min(inverter.P_req, inverter.inverter.P_max_mot), -inverter.inverter.P_max_reg)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1710(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1710};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10216]] /* inverter.inverter.P_req_nameplate variable */) = fmax(fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10209]] /* inverter.P_req variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5946]] /* inverter.inverter.P_max_mot PARAM */)),(-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5947]] /* inverter.inverter.P_max_reg PARAM */)));
  threadData->lastEquationSolved = 1710;
}

/*
equation index: 1711
type: SIMPLE_ASSIGN
inverter.powerFraction = min(max(abs(inverter.inverter.P_req_nameplate) / inverter.inverter.P_nominal, inverter.inverter.powerFractionTable[1]), inverter.inverter.powerFractionTable[6])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1711(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1711};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10221]] /* inverter.powerFraction variable */) = fmin(fmax(DIVISION_SIM(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10216]] /* inverter.inverter.P_req_nameplate variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5948]] /* inverter.inverter.P_nominal PARAM */),"inverter.inverter.P_nominal",equationIndexes),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5969]] /* inverter.inverter.powerFractionTable[1] PARAM */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5974]] /* inverter.inverter.powerFractionTable[6] PARAM */));
  threadData->lastEquationSolved = 1711;
}

/*
equation index: 1712
type: SIMPLE_ASSIGN
inverter.inverter.eta_reg_eff = min(max(Modelica.Math.Vectors.interpolate(inverter.inverter.powerFractionTable, inverter.inverter.eta_reg_table, inverter.powerFraction, 1)[1], inverter.inverter.eta_min), inverter.inverter.eta_max)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1712(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1712};
  real_array tmp643;
  real_array tmp644;
  real_array_create(&tmp643, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5969]] /* inverter.inverter.powerFractionTable[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)6);
  real_array_create(&tmp644, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5963]] /* inverter.inverter.eta_reg_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)6);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10220]] /* inverter.inverter.eta_reg_eff variable */) = fmin(fmax(omc_Modelica_Math_Vectors_interpolate(threadData, tmp643, tmp644, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10221]] /* inverter.powerFraction variable */), ((modelica_integer) 1), NULL),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5954]] /* inverter.inverter.eta_min PARAM */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5953]] /* inverter.inverter.eta_max PARAM */));
  threadData->lastEquationSolved = 1712;
}

/*
equation index: 1713
type: SIMPLE_ASSIGN
inverter.inverter.eta_mot_eff = min(max(Modelica.Math.Vectors.interpolate(inverter.inverter.powerFractionTable, inverter.inverter.eta_mot_table, inverter.powerFraction, 1)[1], inverter.inverter.eta_min), inverter.inverter.eta_max)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1713(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1713};
  real_array tmp645;
  real_array tmp646;
  real_array_create(&tmp645, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5969]] /* inverter.inverter.powerFractionTable[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)6);
  real_array_create(&tmp646, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5956]] /* inverter.inverter.eta_mot_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)6);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10219]] /* inverter.inverter.eta_mot_eff variable */) = fmin(fmax(omc_Modelica_Math_Vectors_interpolate(threadData, tmp645, tmp646, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10221]] /* inverter.powerFraction variable */), ((modelica_integer) 1), NULL),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5954]] /* inverter.inverter.eta_min PARAM */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5953]] /* inverter.inverter.eta_max PARAM */));
  threadData->lastEquationSolved = 1713;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29172(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29231(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29232(DATA *data, threadData_t *threadData);


/*
equation index: 1717
type: SIMPLE_ASSIGN
vcu.speedPI.addPID.y = vcu.speedPI.gainPID.y / vcu.speedPI.gainPID.k
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1717(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1717};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10316]] /* vcu.speedPI.addPID.y variable */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10319]] /* vcu.speedPI.gainPID.y variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6855]] /* vcu.speedPI.gainPID.k PARAM */),"vcu.speedPI.gainPID.k",equationIndexes);
  threadData->lastEquationSolved = 1717;
}

/*
equation index: 1718
type: SIMPLE_ASSIGN
battery.battery.SOC_state = battery.battery.SOC_start
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1718(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1718};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* battery.battery.SOC_state STATE(1) */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[228]] /* battery.battery.SOC_start PARAM */);
  threadData->lastEquationSolved = 1718;
}

/*
equation index: 1719
type: SIMPLE_ASSIGN
battery.SOC = min(max(battery.battery.SOC_state, 0.0), 1.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1719(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1719};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2235]] /* battery.SOC variable */) = fmin(fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* battery.battery.SOC_state STATE(1) */),0.0),1.0);
  threadData->lastEquationSolved = 1719;
}

/*
equation index: 1720
type: SIMPLE_ASSIGN
battery.battery.SOC_lookup = min(max(battery.SOC, battery.battery.SOC_table[1]), battery.battery.SOC_table[7])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1720(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1720};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2253]] /* battery.battery.SOC_lookup variable */) = fmin(fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2235]] /* battery.SOC variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[229]] /* battery.battery.SOC_table[1] PARAM */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[235]] /* battery.battery.SOC_table[7] PARAM */));
  threadData->lastEquationSolved = 1720;
}

/*
equation index: 1721
type: SIMPLE_ASSIGN
battery.SOE = min(max(Modelica.Math.Vectors.interpolate(battery.battery.SOC_table, battery.battery.SOE_table, battery.battery.SOC_lookup, 1)[1], 0.0), 1.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1721(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1721};
  real_array tmp647;
  real_array tmp648;
  real_array_create(&tmp647, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[229]] /* battery.battery.SOC_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)7);
  real_array_create(&tmp648, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[236]] /* battery.battery.SOE_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)7);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2236]] /* battery.SOE variable */) = fmin(fmax(omc_Modelica_Math_Vectors_interpolate(threadData, tmp647, tmp648, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2253]] /* battery.battery.SOC_lookup variable */), ((modelica_integer) 1), NULL),0.0),1.0);
  threadData->lastEquationSolved = 1721;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29027(DATA *data, threadData_t *threadData);


/*
equation index: 1723
type: SIMPLE_ASSIGN
battery.battery.I_chg_table_limit = (*Real*)(battery.battery.Np) * Modelica.Math.Vectors.interpolate(battery.battery.SOC_table, battery.battery.I_chg_cell_max_table, battery.battery.SOC_lookup, 1)[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1723(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1723};
  real_array tmp649;
  real_array tmp650;
  real_array_create(&tmp649, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[229]] /* battery.battery.SOC_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)7);
  real_array_create(&tmp650, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[181]] /* battery.battery.I_chg_cell_max_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)7);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2238]] /* battery.battery.I_chg_table_limit variable */) = (((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[7]] /* battery.battery.Np PARAM */))) * (omc_Modelica_Math_Vectors_interpolate(threadData, tmp649, tmp650, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2253]] /* battery.battery.SOC_lookup variable */), ((modelica_integer) 1), NULL));
  threadData->lastEquationSolved = 1723;
}

/*
equation index: 1724
type: SIMPLE_ASSIGN
battery.battery.I_dis_table_limit = (*Real*)(battery.battery.Np) * Modelica.Math.Vectors.interpolate(battery.battery.SOC_table, battery.battery.I_dis_cell_max_table, battery.battery.SOC_lookup, 1)[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1724(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1724};
  real_array tmp651;
  real_array tmp652;
  real_array_create(&tmp651, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[229]] /* battery.battery.SOC_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)7);
  real_array_create(&tmp652, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[188]] /* battery.battery.I_dis_cell_max_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)7);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2241]] /* battery.battery.I_dis_table_limit variable */) = (((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[7]] /* battery.battery.Np PARAM */))) * (omc_Modelica_Math_Vectors_interpolate(threadData, tmp651, tmp652, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2253]] /* battery.battery.SOC_lookup variable */), ((modelica_integer) 1), NULL));
  threadData->lastEquationSolved = 1724;
}

/*
equation index: 1725
type: SIMPLE_ASSIGN
battery.battery.v_oc_cell = Modelica.Math.Vectors.interpolate(battery.battery.SOC_table, battery.battery.V_ocv_cell_table, battery.battery.SOC_lookup, 1)[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1725(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1725};
  real_array tmp653;
  real_array tmp654;
  real_array_create(&tmp653, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[229]] /* battery.battery.SOC_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)7);
  real_array_create(&tmp654, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[246]] /* battery.battery.V_ocv_cell_table[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)7);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2258]] /* battery.battery.v_oc_cell variable */) = omc_Modelica_Math_Vectors_interpolate(threadData, tmp653, tmp654, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2253]] /* battery.battery.SOC_lookup variable */), ((modelica_integer) 1), NULL);
  threadData->lastEquationSolved = 1725;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29033(DATA *data, threadData_t *threadData);


void BobLib_Experiments_Standards_VehicleSim_eqFunction_1727(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1728(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1729(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1730(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1731(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1732(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1733(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1734(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1735(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1737(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1736(DATA*, threadData_t*);
/*
equation index: 1738
indexNonlinear: 0
type: NONLINEAR

vars: {battery.v, inverter.inverter.V_abs}
eqns: {1727, 1728, 1729, 1730, 1731, 1732, 1733, 1734, 1735, 1737, 1736}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1738(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1738};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 1738 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[0].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2263]] /* battery.v variable */);
  data->simulationInfo->nonlinearSystemData[0].nlsxOld[1] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10218]] /* inverter.inverter.V_abs variable */);
  retValue = solve_nonlinear_system(data, threadData, 0);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,1738};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 1738 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2263]] /* battery.v variable */) = data->simulationInfo->nonlinearSystemData[0].nlsx[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10218]] /* inverter.inverter.V_abs variable */) = data->simulationInfo->nonlinearSystemData[0].nlsx[1];
  threadData->lastEquationSolved = 1738;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29188(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29208(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29209(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29210(DATA *data, threadData_t *threadData);


/*
equation index: 1743
type: SIMPLE_ASSIGN
motor.motor.P_mech_limited = max(min(motor.motor.P_mech_cmd, motor.motor.P_allow), -motor.motor.P_allow)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1743(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1743};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10239]] /* motor.motor.P_mech_limited variable */) = fmax(fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10238]] /* motor.motor.P_mech_cmd variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10235]] /* motor.motor.P_allow variable */)),(-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10235]] /* motor.motor.P_allow variable */)));
  threadData->lastEquationSolved = 1743;
}

/*
equation index: 1744
type: SIMPLE_ASSIGN
motor.tau_cmd = max(min(motor.motor.P_mech_limited / motor.motor.w_eff, motor.tau_lim), -motor.tau_lim)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1744(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1744};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10250]] /* motor.tau_cmd variable */) = fmax(fmin(DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10239]] /* motor.motor.P_mech_limited variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10246]] /* motor.motor.w_eff variable */),"motor.motor.w_eff",equationIndexes),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10251]] /* motor.tau_lim variable */)),(-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10251]] /* motor.tau_lim variable */)));
  threadData->lastEquationSolved = 1744;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29215(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29207(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29216(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29204(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29203(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29199(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29195(DATA *data, threadData_t *threadData);


/*
equation index: 1752
type: SIMPLE_ASSIGN
battery.battery.R1_pack = (*Real*)(battery.battery.Ns) * max(battery.battery.R1_cell, battery.battery.R_eps) / (*Real*)(battery.battery.Np)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1752(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1752};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2252]] /* battery.battery.R1_pack variable */) = (((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[8]] /* battery.battery.Ns PARAM */))) * (DIVISION_SIM(fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2251]] /* battery.battery.R1_cell variable */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[226]] /* battery.battery.R_eps PARAM */)),((modelica_real)(data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[7]] /* battery.battery.Np PARAM */)),"/*Real*/(battery.battery.Np)",equationIndexes));
  threadData->lastEquationSolved = 1752;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29198(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29200(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29201(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29202(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29206(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29189(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29190(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29191(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29192(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29193(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29194(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29205(DATA *data, threadData_t *threadData);


/*
equation index: 1765
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w = chassis.initialLongitudinalVelocity / chassis.rearWheelRadius
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1765(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1765};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[35]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.w STATE(1,chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.inertia.a) */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5078]] /* chassis.initialLongitudinalVelocity PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5869]] /* chassis.rearWheelRadius PARAM */),"chassis.rearWheelRadius",equationIndexes);
  threadData->lastEquationSolved = 1765;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28751(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28863(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29229(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28809(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28808(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28807(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28806(DATA *data, threadData_t *threadData);


/*
equation index: 1773
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w = chassis.initialLongitudinalVelocity / chassis.rearWheelRadius
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1773(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1773};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[29]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.w STATE(1,chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.inertia.a) */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5078]] /* chassis.initialLongitudinalVelocity PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5869]] /* chassis.rearWheelRadius PARAM */),"chassis.rearWheelRadius",equationIndexes);
  threadData->lastEquationSolved = 1773;
}

void BobLib_Experiments_Standards_VehicleSim_eqFunction_1774(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1775(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1776(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1777(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1778(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1779(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1780(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1781(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1782(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1783(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1784(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1785(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1786(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1787(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1788(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1789(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1790(DATA*, threadData_t*);
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1791(DATA*, threadData_t*);
/*
equation index: 1805
indexNonlinear: 1
type: NONLINEAR

vars: {driveline.leftHalfshaft.w_rel}
eqns: {1774, 1775, 1776, 1777, 1778, 1779, 1780, 1781, 1782, 1783, 1784, 1785, 1786, 1787, 1788, 1789, 1790, 1791}
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1805(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1805};
  int retValue;
  infoStreamPrint(OMC_LOG_DT, 0, "Solving nonlinear system 1805 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
  /* get old value */
  data->simulationInfo->nonlinearSystemData[1].nlsxOld[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10187]] /* driveline.leftHalfshaft.w_rel DUMMY_STATE */);
  retValue = solve_nonlinear_system(data, threadData, 1);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,1805};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving non-linear system 1805 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10187]] /* driveline.leftHalfshaft.w_rel DUMMY_STATE */) = data->simulationInfo->nonlinearSystemData[1].nlsx[0];
  threadData->lastEquationSolved = 1805;
}

/*
equation index: 1818
type: LINEAR

<var>driveline.diffInputRotor.a</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1818(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1818};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[10143]] /* driveline.diffInputRotor.a variable */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 1818 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 0, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,1818};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 1818 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10143]] /* driveline.diffInputRotor.a variable */) = aux_x[0];

  threadData->lastEquationSolved = 1818;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28965(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28966(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28950(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28944(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28946(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28945(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28943(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28942(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28941(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29230(DATA *data, threadData_t *threadData);


/*
equation index: 1829
type: SIMPLE_ASSIGN
driveline.differential.torqueBiasRatio = (1e-6 + max(abs(driveline.leftHalfshaftTorque), abs(driveline.rightHalfshaftTorque))) / (1e-6 + min(abs(driveline.leftHalfshaftTorque), abs(driveline.rightHalfshaftTorque)))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1829(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1829};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10158]] /* driveline.differential.torqueBiasRatio variable */) = DIVISION_SIM(1e-6 + fmax(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10188]] /* driveline.leftHalfshaftTorque DUMMY_STATE */)),fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10196]] /* driveline.rightHalfshaftTorque DUMMY_STATE */))),1e-6 + fmin(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10188]] /* driveline.leftHalfshaftTorque DUMMY_STATE */)),fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10196]] /* driveline.rightHalfshaftTorque DUMMY_STATE */))),"1e-6 + min(abs(driveline.leftHalfshaftTorque), abs(driveline.rightHalfshaftTorque))",equationIndexes);
  threadData->lastEquationSolved = 1829;
}

/*
equation index: 1830
type: SIMPLE_ASSIGN
driveline.differential.lockingValue = abs(driveline.rightHalfshaftTorque - driveline.leftHalfshaftTorque) / max(abs(driveline.differential.T_in), 1e-6)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1830(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1830};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10156]] /* driveline.differential.lockingValue variable */) = DIVISION_SIM(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10196]] /* driveline.rightHalfshaftTorque DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10188]] /* driveline.leftHalfshaftTorque DUMMY_STATE */)),fmax(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10146]] /* driveline.differential.T_in DUMMY_STATE */)),1e-6),"max(abs(driveline.differential.T_in), 1e-6)",equationIndexes);
  threadData->lastEquationSolved = 1830;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28948(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28949(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28947(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28752(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28862(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29227(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29228(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28805(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28804(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28803(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28802(DATA *data, threadData_t *threadData);


/*
equation index: 1842
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w = chassis.initialLongitudinalVelocity / chassis.frontWheelRadius
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1842(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1842};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* chassis.detailedChassis.frAxleDW.rightTire.wheelModel.hubAxis.w STATE(1,chassis.detailedChassis.frAxleDW.rightTire.wheelModel.inertia.a) */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5078]] /* chassis.initialLongitudinalVelocity PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5061]] /* chassis.frontWheelRadius PARAM */),"chassis.frontWheelRadius",equationIndexes);
  threadData->lastEquationSolved = 1842;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28753(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28861(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29224(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28775(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28774(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28773(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28772(DATA *data, threadData_t *threadData);


/*
equation index: 1850
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w = chassis.initialLongitudinalVelocity / chassis.frontWheelRadius
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1850(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1850};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[17]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.inertia.a) */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5078]] /* chassis.initialLongitudinalVelocity PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5061]] /* chassis.frontWheelRadius PARAM */),"chassis.frontWheelRadius",equationIndexes);
  threadData->lastEquationSolved = 1850;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28754(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28860(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29223(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28771(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28770(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28769(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28768(DATA *data, threadData_t *threadData);


/*
equation index: 1858
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.phi[3] = chassis.cgFreeMotion.phi_start[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1858(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1858};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[313]] /* chassis.cgFreeMotion.phi_start[3] PARAM */);
  threadData->lastEquationSolved = 1858;
}

/*
equation index: 1859
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.phi[2] = chassis.cgFreeMotion.phi_start[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1859(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1859};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[312]] /* chassis.cgFreeMotion.phi_start[2] PARAM */);
  threadData->lastEquationSolved = 1859;
}

/*
equation index: 1860
type: SIMPLE_ASSIGN
chassis.chassisFrame.R.T[1,1] = cos(chassis.cgFreeMotion.phi[3]) * cos(chassis.cgFreeMotion.phi[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1860(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1860};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */)));
  threadData->lastEquationSolved = 1860;
}

/*
equation index: 1861
type: SIMPLE_ASSIGN
chassis.chassisFrame.R.T[2,1] = (-sin(chassis.cgFreeMotion.phi[3])) * cos(chassis.cgFreeMotion.phi[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1861(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1861};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */) = ((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */)))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */)));
  threadData->lastEquationSolved = 1861;
}

/*
equation index: 1862
type: LINEAR

<var>chassis.cgFreeMotion.phi_d[2]</var>
<var>chassis.cgFreeMotion.phi_d[1]</var>
<row>
  <cell>-chassis.cgFreeMotion.w_rel_b[2]</cell>
  <cell>-chassis.cgFreeMotion.w_rel_b[1]</cell>
</row>
<matrix>
  <cell row="0" col="0">
    <residual>-cos(chassis.cgFreeMotion.phi[3])</residual>
  </cell><cell row="0" col="1">
    <residual>-chassis.chassisFrame.R.T[2,1]</residual>
  </cell><cell row="1" col="0">
    <residual>-sin(chassis.cgFreeMotion.phi[3])</residual>
  </cell><cell row="1" col="1">
    <residual>-chassis.chassisFrame.R.T[1,1]</residual>
  </cell>
</matrix>
*/
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1862(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1862};
  /* Linear equation system */
  int retValue;
  double aux_x[2] = { (data->localData[1]->realVars[data->simulationInfo->realVarsIndex[6]] /* chassis.cgFreeMotion.phi_d[2] STATE(1,chassis.cgFreeMotion.phi_dd[2]) */),(data->localData[1]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */) };
  infoStreamPrint(OMC_LOG_DT, 0, "Solving linear system 1862 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);

  retValue = solve_linear_system(data, threadData, 1, &aux_x[0]);

  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,1862};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 1862 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* chassis.cgFreeMotion.phi_d[2] STATE(1,chassis.cgFreeMotion.phi_dd[2]) */) = aux_x[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */) = aux_x[1];

  threadData->lastEquationSolved = 1862;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28847(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28846(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29036(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32170(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32181(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32180(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31392(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31399(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31406(DATA *data, threadData_t *threadData);


/*
equation index: 1872
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToFore.shape.r[1] = chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[1] - ((-0.03544608361872592) * chassis.chassisFrame.R.T[1,1] + 1.7429613639823153e-6 * chassis.chassisFrame.R.T[2,1] + 0.09245073226067826 * chassis.chassisFrame.R.T[3,1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1872(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1872};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9870]] /* chassis.detailedChassis.spaceFrame.midToFore.shape.r[1] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9908]] /* chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[1] DUMMY_STATE */) - ((-0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) + (1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) + (0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1872;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29062(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29064(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29073(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29075(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29074(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29072(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29069(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32182(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32183(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29070(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29071(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29068(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29067(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31407(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31408(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29066(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29065(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29063(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29316(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29317(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29326(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29333(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30263(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30270(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30277(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29485(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29492(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29499(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29341(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29342(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29344(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29343(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29340(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29339(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30278(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29338(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29337(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29500(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29336(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29335(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29334(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29345(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29346(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29347(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29348(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29349(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29350(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29351(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29352(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29353(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29354(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29355(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29356(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29076(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29077(DATA *data, threadData_t *threadData);


/*
equation index: 1928
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.spaceFrame.midToFore.shape.r[1] = chassis.detailedChassis.spaceFrame.sprungBody.v_0[1] - (chassis.chassisFrame.R.T[1,1] * (0.09245073226067826 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-1.7429613639823153e-6) * yawVel) + chassis.chassisFrame.R.T[2,1] * ((-0.03544608361872592) * yawVel + (-0.09245073226067826) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,1] * (1.7429613639823153e-6 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.03544608361872592 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1928(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1928};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1990]] /* der(chassis.detailedChassis.spaceFrame.midToFore.shape.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9939]] /* chassis.detailedChassis.spaceFrame.sprungBody.v_0[1] DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))));
  threadData->lastEquationSolved = 1928;
}

/*
equation index: 1929
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleFrame.r_0[1] = $DER.chassis.detailedChassis.spaceFrame.midToFore.shape.r[1] + 0.7747 * chassis.chassisFrame.R.T[2,1] * yawVel + (-0.7747) * chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1929(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1929};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1990]] /* der(chassis.detailedChassis.spaceFrame.midToFore.shape.r[1]) DUMMY_DER */) + (0.7747) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.7747) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1929;
}

/*
equation index: 1930
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + (-0.08618219999999999) * chassis.chassisFrame.R.T[1,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.chassisFrame.R.T[2,1] * (0.05715 * yawVel + 0.08618219999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + (-0.05715) * chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1930(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1930};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1123]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + (-0.08618219999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((0.05715) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08618219999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (-0.05715) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1930;
}

/*
equation index: 1931
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[1] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[1] + chassis.chassisFrame.R.T[1,1] * (-yawVel) * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s + chassis.chassisFrame.R.T[2,1] * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.v + chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1931(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1931};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1128]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1123]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.vis.r[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * (((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4093]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4094]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.v DUMMY_STATE */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4093]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.s DUMMY_STATE */)));
  threadData->lastEquationSolved = 1931;
}

/*
equation index: 1932
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.r[1] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[1] - (0.2260092 * chassis.chassisFrame.R.T[1,1] * yawVel + (-0.2260092) * chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1932(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1932};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1120]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1128]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[1]) DUMMY_DER */) - ((0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))));
  threadData->lastEquationSolved = 1932;
}

/*
equation index: 1933
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.r[1] = $DER.chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[1] + 0.2260092 * chassis.chassisFrame.R.T[1,1] * yawVel + (-0.2260092) * chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1933(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1933};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1221]] /* der(chassis.detailedChassis.frAxleDW.rightTieRod.rod.rodShape.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1128]] /* der(chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.vis.r[1]) DUMMY_DER */) + (0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + (-0.2260092) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1933;
}

/*
equation index: 1934
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * (0.014833600000000002 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.2366899) * yawVel) + chassis.chassisFrame.R.T[2,1] * (0.016751299999999997 * yawVel + (-0.014833600000000002) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,1] * (0.2366899 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + (-0.016751299999999997) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1934(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1934};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1051]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperFrame_i.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((0.014833600000000002) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.2366899) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((0.016751299999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.014833600000000002) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((0.2366899) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (-0.016751299999999997) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1934;
}

/*
equation index: 1935
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.r[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * ((-0.119888) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.226314) * yawVel) + chassis.chassisFrame.R.T[2,1] * (0.012699999999999996 * yawVel + 0.119888 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,1] * (0.226314 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + (-0.012699999999999996) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1935(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1935};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1022]] /* der(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((-0.119888) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.226314) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((0.012699999999999996) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.119888) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((0.226314) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (-0.012699999999999996) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1935;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32734(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32786(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32785(DATA *data, threadData_t *threadData);


/*
equation index: 1939
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] - yawVel * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2]) + chassis.chassisFrame.R.T[2,1] * (yawVel * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3]) + chassis.chassisFrame.R.T[3,1] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1939(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1939};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1299]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperFrame_i.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2554]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2553]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2552]] /* chassis.detailedChassis.frAxleDW.toRightUpper_i.r[1] PARAM */))));
  threadData->lastEquationSolved = 1939;
}

/*
equation index: 1940
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] - yawVel * chassis.detailedChassis.frAxleDW.toRightLower_i.r[2]) + chassis.chassisFrame.R.T[2,1] * (yawVel * chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[3]) + chassis.chassisFrame.R.T[3,1] * (chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] - chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] * chassis.detailedChassis.frAxleDW.toRightLower_i.r[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1940(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1940};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1270]] /* der(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2522]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[3] PARAM */)))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2521]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[2] PARAM */)) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2520]] /* chassis.detailedChassis.frAxleDW.toRightLower_i.r[1] PARAM */))));
  threadData->lastEquationSolved = 1940;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31784(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31836(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31835(DATA *data, threadData_t *threadData);


/*
equation index: 1944
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * (0.170112000136 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.250754351932) * yawVel) + chassis.chassisFrame.R.T[2,1] * ((-0.042144464098) * yawVel + (-0.170112000136) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,1] * (0.250754351932 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1944(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1944};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[902]] /* der(chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.vis.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.170112000136) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1944;
}

/*
equation index: 1945
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.250754351932 * yawVel) + chassis.chassisFrame.R.T[2,1] * ((-0.042144464098) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.042144464098, 0.250754351932, 0.370010000136})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,1] * ((-0.250754351932) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.042144464098 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1945(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1945};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1145]] /* der(chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.vis.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT23), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((-0.250754351932) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.042144464098) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1945;
}

/*
equation index: 1946
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + (-0.08178799999999999) * chassis.chassisFrame.R.T[1,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + chassis.chassisFrame.R.T[2,1] * ((-0.10664664) * yawVel + 0.08178799999999999 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + 0.10664664 * chassis.chassisFrame.R.T[3,1] * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1946(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1946};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1406]] /* der(chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.r[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + (-0.08178799999999999) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.10664664) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.08178799999999999) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + (0.10664664) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1946;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29444(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29452(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29453(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29455(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29454(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29451(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29450(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30809(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31080(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29449(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29448(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29870(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30090(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29447(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29446(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29445(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29458(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29461(DATA *data, threadData_t *threadData);


/*
equation index: 1965
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.phi_d[3] = chassis.cgFreeMotion.w_rel_b[3] - chassis.chassisFrame.R.T[3,1] * chassis.cgFreeMotion.phi_d[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1965(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1965};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2360]] /* chassis.cgFreeMotion.w_rel_b[3] DUMMY_STATE */) - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* chassis.cgFreeMotion.phi_d[1] STATE(1,chassis.cgFreeMotion.phi_dd[1]) */)));
  threadData->lastEquationSolved = 1965;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28848(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29080(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29081(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29082(DATA *data, threadData_t *threadData);


/*
equation index: 1970
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.rightShockLinkage.frame_b.r_0[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * ((-0.199898 + BobLib.Utilities.Math.Vector.mirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + 0.247847085458 * yawVel) + chassis.chassisFrame.R.T[2,1] * ((-0.020673469702) * yawVel + (0.199898 - BobLib.Utilities.Math.Vector.mirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868})[3]) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,1] * ($DER$BobLib$PUtilities$PMath$PVector$PmirrorXZ({-0.020673469702, 0.247847085458, 0.561456926868}, {0.0, 0.0, 0.0})[3] + (-0.247847085458) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.020673469702 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1970(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1970};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1209]] /* der(chassis.detailedChassis.frAxleDW.rightShockLinkage.frame_b.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((-0.199898 + real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT24), 2)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (0.199898 - (real_get(omc_BobLib_Utilities_Math_Vector_mirrorXZ(threadData, _OMC_LIT24), 2))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (real_get(omc__omcQ_24DER_24BobLib_24PUtilities_24PMath_24PVector_24PmirrorXZ(threadData, _OMC_LIT24, _OMC_LIT25), 2) + (-0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1970;
}

/*
equation index: 1971
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.frAxleDW.leftShockLinkage.frame_b.r_0[1] = $DER.chassis.detailedChassis.frAxleFrame.r_0[1] + chassis.chassisFrame.R.T[1,1] * (0.36155892686799995 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] + (-0.247847085458) * yawVel) + chassis.chassisFrame.R.T[2,1] * ((-0.020673469702) * yawVel + (-0.36155892686799995) * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1]) + chassis.chassisFrame.R.T[3,1] * (0.247847085458 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] + 0.020673469702 * chassis.detailedChassis.spaceFrame.sprungBody.w_a[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1971(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1971};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[966]] /* der(chassis.detailedChassis.frAxleDW.leftShockLinkage.frame_b.r_0[1]) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1409]] /* der(chassis.detailedChassis.frAxleFrame.r_0[1]) DUMMY_DER */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((0.36155892686799995) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)) + (-0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((-0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10782]] /* yawVel DUMMY_STATE */)) + (-0.36155892686799995) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */))) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * ((0.247847085458) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9942]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[1] DUMMY_STATE */)) + (0.020673469702) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9943]] /* chassis.detailedChassis.spaceFrame.sprungBody.w_a[2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 1971;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29083(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29084(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29085(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29086(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29087(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29088(DATA *data, threadData_t *threadData);


/*
equation index: 1978
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[1,1] = cos(chassis.cgFreeMotion.phi[3]) * (-sin(chassis.cgFreeMotion.phi[2])) * chassis.cgFreeMotion.phi_d[2] - sin(chassis.cgFreeMotion.phi[3]) * chassis.cgFreeMotion.phi_d[3] * cos(chassis.cgFreeMotion.phi[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1978(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1978};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[879]] /* der(chassis.chassisFrame.R.T[1,1]) DUMMY_DER */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* chassis.cgFreeMotion.phi_d[2] STATE(1,chassis.cgFreeMotion.phi_dd[2]) */))) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */)))));
  threadData->lastEquationSolved = 1978;
}

/*
equation index: 1979
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[2,1] = (-cos(chassis.cgFreeMotion.phi[3])) * chassis.cgFreeMotion.phi_d[3] * cos(chassis.cgFreeMotion.phi[2]) - sin(chassis.cgFreeMotion.phi[3]) * (-sin(chassis.cgFreeMotion.phi[2])) * chassis.cgFreeMotion.phi_d[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1979(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1979};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[882]] /* der(chassis.chassisFrame.R.T[2,1]) DUMMY_DER */) = ((-cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* chassis.cgFreeMotion.phi_d[3] STATE(1,chassis.cgFreeMotion.phi_dd[3]) */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */)))) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* chassis.cgFreeMotion.phi_d[2] STATE(1,chassis.cgFreeMotion.phi_dd[2]) */))));
  threadData->lastEquationSolved = 1979;
}

/*
equation index: 1980
type: SIMPLE_ASSIGN
$DER.chassis.chassisFrame.R.T[3,1] = cos(chassis.cgFreeMotion.phi[2]) * chassis.cgFreeMotion.phi_d[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1980(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1980};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[885]] /* der(chassis.chassisFrame.R.T[3,1]) DUMMY_DER */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* chassis.cgFreeMotion.phi_d[2] STATE(1,chassis.cgFreeMotion.phi_dd[2]) */));
  threadData->lastEquationSolved = 1980;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32719(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32819(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32818(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31870(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31875(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31880(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29464(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29469(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29474(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31114(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31119(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31124(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30124(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30129(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_30134(DATA *data, threadData_t *threadData);


/*
equation index: 1996
type: SIMPLE_ASSIGN
chassis.cgFreeMotion.phi[1] = chassis.cgFreeMotion.phi_start[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1996(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1996};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[311]] /* chassis.cgFreeMotion.phi_start[1] PARAM */);
  threadData->lastEquationSolved = 1996;
}

/*
equation index: 1997
type: SIMPLE_ASSIGN
chassis.chassisFrame.R.T[1,2] = sin(chassis.cgFreeMotion.phi[3]) * cos(chassis.cgFreeMotion.phi[1]) + cos(chassis.cgFreeMotion.phi[3]) * chassis.chassisFrame.R.T[3,1] * sin(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1997(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1997};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */) = (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) + (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))));
  threadData->lastEquationSolved = 1997;
}

/*
equation index: 1998
type: SIMPLE_ASSIGN
chassis.chassisFrame.R.T[1,3] = sin(chassis.cgFreeMotion.phi[3]) * sin(chassis.cgFreeMotion.phi[1]) - cos(chassis.cgFreeMotion.phi[3]) * chassis.chassisFrame.R.T[3,1] * cos(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1998(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1998};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */) = (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) - ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))));
  threadData->lastEquationSolved = 1998;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29056(DATA *data, threadData_t *threadData);


/*
equation index: 2000
type: SIMPLE_ASSIGN
aeroModel.bodyVelocity[1] = chassis.chassisFrame.R.T[1,1] * $DER.aeroModel.sprungChassisFrame.r_0[1] + chassis.chassisFrame.R.T[1,2] * $DER.aeroModel.sprungChassisFrame.r_0[2] + chassis.chassisFrame.R.T[1,3] * $DER.aeroModel.sprungChassisFrame.r_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2000(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2000};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2205]] /* aeroModel.bodyVelocity[1] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2361]] /* chassis.chassisFrame.R.T[1,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[873]] /* der(aeroModel.sprungChassisFrame.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[874]] /* der(aeroModel.sprungChassisFrame.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2363]] /* chassis.chassisFrame.R.T[1,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[875]] /* der(aeroModel.sprungChassisFrame.r_0[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 2000;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29058(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29059(DATA *data, threadData_t *threadData);


/*
equation index: 2003
type: SIMPLE_ASSIGN
chassis.chassisFrame.R.T[2,2] = cos(chassis.cgFreeMotion.phi[3]) * cos(chassis.cgFreeMotion.phi[1]) - sin(chassis.cgFreeMotion.phi[3]) * chassis.chassisFrame.R.T[3,1] * sin(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2003(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2003};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) - ((sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)))));
  threadData->lastEquationSolved = 2003;
}

/*
equation index: 2004
type: SIMPLE_ASSIGN
chassis.chassisFrame.R.T[2,3] = cos(chassis.cgFreeMotion.phi[3]) * sin(chassis.cgFreeMotion.phi[1]) + sin(chassis.cgFreeMotion.phi[3]) * chassis.chassisFrame.R.T[3,1] * cos(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2004(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2004};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */) = (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))) + (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* chassis.cgFreeMotion.phi[3] STATE(1,chassis.cgFreeMotion.phi_d[3]) */))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2367]] /* chassis.chassisFrame.R.T[3,1] DUMMY_STATE */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */))));
  threadData->lastEquationSolved = 2004;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29137(DATA *data, threadData_t *threadData);


/*
equation index: 2006
type: SIMPLE_ASSIGN
aeroModel.bodyVelocity[2] = chassis.chassisFrame.R.T[2,1] * $DER.aeroModel.sprungChassisFrame.r_0[1] + chassis.chassisFrame.R.T[2,2] * $DER.aeroModel.sprungChassisFrame.r_0[2] + chassis.chassisFrame.R.T[2,3] * $DER.aeroModel.sprungChassisFrame.r_0[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2006(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2006};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2206]] /* aeroModel.bodyVelocity[2] variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2364]] /* chassis.chassisFrame.R.T[2,1] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[873]] /* der(aeroModel.sprungChassisFrame.r_0[1]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[874]] /* der(aeroModel.sprungChassisFrame.r_0[2]) DUMMY_DER */)) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2366]] /* chassis.chassisFrame.R.T[2,3] DUMMY_STATE */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[875]] /* der(aeroModel.sprungChassisFrame.r_0[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 2006;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29139(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29143(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29238(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29242(DATA *data, threadData_t *threadData);


/*
equation index: 2011
type: SIMPLE_ASSIGN
$whenCondition4 = (vcu.useMode == 0 or vcu.useMode == 3) and terminateOnSpinout and time > vcu.steerStart and abs(sideslip) >= sideslipTerminate and $PRE.t_spinout_hit < 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2011(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2011};
  modelica_boolean tmp655;
  modelica_boolean tmp656;
  modelica_boolean tmp657;
  tmp655 = Greater(data->localData[0]->timeValue,(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6875]] /* vcu.steerStart PARAM */));
  tmp656 = GreaterEq(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10274]] /* sideslip variable */)),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6808]] /* sideslipTerminate PARAM */));
  tmp657 = Less((data->simulationInfo->realVarsPre[10801] /* t_spinout_hit DISCRETE */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[16]] /* $whenCondition4 DISCRETE */) = (((((((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 0)) || ((data->simulationInfo->integerParameter[data->simulationInfo->integerParamsIndex[287]] /* vcu.useMode PARAM */) == ((modelica_integer) 3))) && (data->simulationInfo->booleanParameter[data->simulationInfo->booleanParamsIndex[591]] /* terminateOnSpinout PARAM */)) && tmp655) && tmp656) && tmp657);
  threadData->lastEquationSolved = 2011;
}

/*
equation index: 2012
type: SIMPLE_ASSIGN
chassis.chassisFrame.R.T[3,2] = (-cos(chassis.cgFreeMotion.phi[2])) * sin(chassis.cgFreeMotion.phi[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2012(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2012};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */) = ((-cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* chassis.cgFreeMotion.phi[2] STATE(1,chassis.cgFreeMotion.phi_d[2]) */)))) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* chassis.cgFreeMotion.phi[1] STATE(1,chassis.cgFreeMotion.phi_d[1]) */)));
  threadData->lastEquationSolved = 2012;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32171(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32185(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32184(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31393(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31400(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_31409(DATA *data, threadData_t *threadData);


/*
equation index: 2019
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToFore.shape.r[2] = chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[2] - ((-0.03544608361872592) * chassis.chassisFrame.R.T[1,2] + 1.7429613639823153e-6 * chassis.chassisFrame.R.T[2,2] + 0.09245073226067826 * chassis.chassisFrame.R.T[3,2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_2019(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,2019};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9871]] /* chassis.detailedChassis.spaceFrame.midToFore.shape.r[2] DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9909]] /* chassis.detailedChassis.spaceFrame.sprungBody.frame_a.r_0[2] DUMMY_STATE */) - ((-0.03544608361872592) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2362]] /* chassis.chassisFrame.R.T[1,2] DUMMY_STATE */)) + (1.7429613639823153e-6) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2365]] /* chassis.chassisFrame.R.T[2,2] DUMMY_STATE */)) + (0.09245073226067826) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2368]] /* chassis.chassisFrame.R.T[3,2] DUMMY_STATE */)));
  threadData->lastEquationSolved = 2019;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29091(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29093(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29102(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29104(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29103(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29101(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29098(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32186(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_32187(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29099(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_29100(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_functionInitialEquations_3(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[494])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1483,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1484,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1485,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1486,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1487,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1488,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1489,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1490,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1491,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1492,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1493,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1494,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1495,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1496,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1497,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1498,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1499,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1500,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1501,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1502,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1503,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1504,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1505,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1506,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1507,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1508,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1509,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1510,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1511,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1512,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1513,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1514,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1515,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1516,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1517,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1518,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1519,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1520,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1521,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1522,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1523,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1524,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1525,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1526,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1527,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1528,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1529,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1530,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1531,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1532,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1533,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1534,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1535,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1536,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1537,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1538,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1539,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1540,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1542,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1545,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1547,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1548,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1549,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1550,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1551,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1552,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1553,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1554,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1555,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1556,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1557,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28888,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28887,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28886,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1561,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1562,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1563,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1564,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1565,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1566,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1567,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1568,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1569,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28761,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1571,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1572,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1573,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28841,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28842,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28836,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1577,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28985,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28986,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1580,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28983,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28984,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28981,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28982,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1586,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28760,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1589,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28843,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1591,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28758,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1593,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1594,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28844,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1596,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1598,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1599,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28845,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1601,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29301,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1603,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29079,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1605,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1606,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1607,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1608,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1609,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1610,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1611,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1612,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1613,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1614,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1615,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30266,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30273,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30804,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29488,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29495,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29865,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1622,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1623,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1624,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1625,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29014,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29015,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1628,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29017,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29018,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29019,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1632,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1633,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28975,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28976,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28977,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1637,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1638,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32912,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1640,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32905,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1642,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32907,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32908,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1645,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32910,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32911,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1648,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28868,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28869,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28871,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28872,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28873,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28874,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28875,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1656,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1657,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28879,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28881,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28880,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28882,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28859,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1663,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35624,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1666,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1667,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35593,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1669,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1670,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32915,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1672,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1673,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35630,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1675,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1676,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29245,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1678,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1679,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_35588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1681,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1682,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28907,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1684,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1685,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1686,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28971,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28972,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28904,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1690,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29149,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1692,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29151,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29154,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29155,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29217,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1697,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29225,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29226,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29221,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29222,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29218,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29152,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29153,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29156,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1706,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1707,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29160,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29161,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1710,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1711,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1712,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1713,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29172,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29231,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29232,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1717,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1718,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1719,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1720,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1721,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29027,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1723,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1724,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1725,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29033,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1738,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29188,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29208,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29209,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29210,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29215,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29207,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29216,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29204,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29203,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29199,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29195,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29198,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29200,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29201,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29202,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29206,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29189,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29190,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29191,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29192,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29193,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29194,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29205,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1765,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28751,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28863,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29229,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28809,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28808,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28807,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28806,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1773,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1818,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28965,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28966,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28950,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28944,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28946,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28945,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28943,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28942,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28941,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29230,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1829,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1830,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28948,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28949,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28947,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28862,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29227,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29228,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28804,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28803,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28802,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1842,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28861,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29224,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28775,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28774,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28773,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28772,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1850,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28754,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28860,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29223,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28771,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28770,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28769,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28768,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1858,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1859,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1860,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1861,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1862,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28847,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28846,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29036,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32170,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32181,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32180,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31392,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31399,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31406,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1872,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29062,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29064,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29073,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29075,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29074,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29072,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29069,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32182,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32183,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29070,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29071,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29068,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29067,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31407,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31408,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29066,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29065,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29063,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29316,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29317,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29326,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29333,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30263,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30270,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30277,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29485,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29492,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29499,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29341,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29342,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29344,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29343,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29340,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29339,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30278,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29338,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29337,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29500,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29336,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29335,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29334,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29345,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29346,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29347,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29348,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29349,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29350,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29351,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29352,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29353,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29354,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29355,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29356,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29076,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29077,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1928,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1929,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1930,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1931,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1932,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1933,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1934,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1935,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32734,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32786,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32785,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1939,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1940,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31784,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31836,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31835,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1944,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1945,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1946,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29444,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29452,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29453,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29455,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29454,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29451,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29450,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30809,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31080,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29449,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29448,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29870,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30090,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29447,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29446,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29445,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29458,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29461,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1965,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28848,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29080,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29081,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29082,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1970,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1971,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29083,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29084,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29085,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29086,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29087,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29088,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1978,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1979,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1980,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32719,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32819,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32818,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31870,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31875,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31880,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29464,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29469,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29474,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31114,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31119,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31124,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30124,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30129,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_30134,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1996,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1997,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1998,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29056,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2000,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29058,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29059,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2003,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2004,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29137,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2006,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29139,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29143,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29238,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29242,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2011,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2012,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32171,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32185,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32184,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31393,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31400,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_31409,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_2019,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29091,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29093,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29102,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29104,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29103,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29101,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29098,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32186,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_32187,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29099,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_29100
  };
  
  for (int id = 0; id < 494; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif