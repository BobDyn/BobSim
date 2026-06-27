#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/*
equation index: 989
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_989(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,989};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1492]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1495]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */);
  threadData->lastEquationSolved = 989;
}

/*
equation index: 990
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[3] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_990(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,990};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1456]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1453]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[3] PARAM */);
  threadData->lastEquationSolved = 990;
}

/*
equation index: 991
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.lengthDirection[3] = chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_991(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,991};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1510]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */);
  threadData->lastEquationSolved = 991;
}

/*
equation index: 992
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[2] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_992(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,992};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1455]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1452]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[2] PARAM */);
  threadData->lastEquationSolved = 992;
}

/*
equation index: 993
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.lengthDirection[2] = chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_993(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,993};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1509]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */);
  threadData->lastEquationSolved = 993;
}

/*
equation index: 994
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] = chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[1] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_994(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,994};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1454]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1451]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[1] PARAM */);
  threadData->lastEquationSolved = 994;
}

/*
equation index: 995
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.length = sqrt(chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_995(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,995};
  modelica_real tmp250;
  modelica_real tmp251;
  modelica_real tmp252;
  modelica_real tmp253;
  tmp250 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */);
  tmp251 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1512]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */);
  tmp252 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1513]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */);
  tmp253 = (tmp250 * tmp250) + (tmp251 * tmp251) + (tmp252 * tmp252);
  if(!(tmp253 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[2] ^ 2.0 + chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[3] ^ 2.0) was %g should be >= 0", tmp253);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1507]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.length PARAM */) = sqrt(tmp253);
  threadData->lastEquationSolved = 995;
}

/*
equation index: 996
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.width = chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_996(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,996};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1517]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1507]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 996;
}

/*
equation index: 997
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.height = chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_997(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,997};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1506]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1517]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.width PARAM */);
  threadData->lastEquationSolved = 997;
}

/*
equation index: 998
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.lengthDirection[1] = chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_998(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,998};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1508]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1511]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */);
  threadData->lastEquationSolved = 998;
}

/*
equation index: 999
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] = chassis.detailedChassis.frAxleDW.leftPushrod.n1_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_999(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,999};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[487]] /* chassis.detailedChassis.frAxleDW.leftPushrod.n1_a[3] PARAM */);
  threadData->lastEquationSolved = 999;
}

/*
equation index: 1000
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.r_shape[3] = (-chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1000(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1000};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2823]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1000;
}

/*
equation index: 1001
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] = chassis.detailedChassis.frAxleDW.leftPushrod.n1_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1001(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1001};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[486]] /* chassis.detailedChassis.frAxleDW.leftPushrod.n1_a[2] PARAM */);
  threadData->lastEquationSolved = 1001;
}

/*
equation index: 1002
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.r_shape[2] = (-chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1002(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1002};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2822]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1002;
}

/*
equation index: 1003
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] = chassis.detailedChassis.frAxleDW.leftPushrod.n1_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1003(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1003};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[485]] /* chassis.detailedChassis.frAxleDW.leftPushrod.n1_a[1] PARAM */);
  threadData->lastEquationSolved = 1003;
}

/*
equation index: 1004
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia = smooth(0, if noEvent(sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) / sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0), (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) / sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0), (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) / sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1004(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1004};
  modelica_real tmp254;
  modelica_real tmp255;
  modelica_real tmp256;
  modelica_real tmp257;
  modelica_boolean tmp258;
  real_array tmp259;
  modelica_real tmp260;
  modelica_real tmp261;
  modelica_real tmp262;
  modelica_real tmp263;
  modelica_real tmp264;
  modelica_real tmp265;
  modelica_real tmp266;
  modelica_real tmp267;
  modelica_real tmp268;
  modelica_real tmp269;
  modelica_real tmp270;
  modelica_real tmp271;
  real_array tmp272;
  modelica_boolean tmp273;
  real_array tmp274;
  real_array tmp275;
  tmp254 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)));
  tmp255 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)));
  tmp256 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)));
  tmp257 = (tmp254 * tmp254) + (tmp255 * tmp255) + (tmp256 * tmp256);
  if(!(tmp257 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp257);
    }
  }tmp258 = GreaterEq(sqrt(tmp257),2.220446049250313e-14);
  tmp273 = (modelica_boolean)tmp258;
  if(tmp273)
  {
    tmp260 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)));
    tmp261 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)));
    tmp262 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)));
    tmp263 = (tmp260 * tmp260) + (tmp261 * tmp261) + (tmp262 * tmp262);
    if(!(tmp263 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp263);
      }
    }tmp264 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)));
    tmp265 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)));
    tmp266 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)));
    tmp267 = (tmp264 * tmp264) + (tmp265 * tmp265) + (tmp266 * tmp266);
    if(!(tmp267 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp267);
      }
    }tmp268 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)));
    tmp269 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)));
    tmp270 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)));
    tmp271 = (tmp268 * tmp268) + (tmp269 * tmp269) + (tmp270 * tmp270);
    if(!(tmp271 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp271);
      }
    }array_alloc_scalar_real_array(&tmp259, 3, (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */))),sqrt(tmp263),"sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */))),sqrt(tmp267),"sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */))),sqrt(tmp271),"sqrt((chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes));
    tmp274 = tmp259;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp272, 3, (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)))), (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[507]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)))), (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[506]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)))));
    tmp274 = tmp272;
  }
  real_array_create(&tmp275, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[496]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp274, tmp275);
  threadData->lastEquationSolved = 1004;
}

/*
equation index: 1005
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r_shape[2] = (-chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1005(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1005};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2853]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[497]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1005;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28793(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36362(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36365(DATA *data, threadData_t *threadData);


/*
equation index: 1009
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r_shape[1] = (-chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1009(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1009};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2852]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[496]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1009;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28791(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36361(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36364(DATA *data, threadData_t *threadData);


/*
equation index: 1013
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r_shape[3] = (-chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1013(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1013};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2854]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[498]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1013;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28795(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36363(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36366(DATA *data, threadData_t *threadData);


/*
equation index: 1017
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.r_shape[1] = (-chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1017(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1017};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2821]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[505]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.n1_a[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1017;
}

/*
equation index: 1018
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_ia[1] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[3] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1018(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1018};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[499]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[498]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[497]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 1018;
}

/*
equation index: 1019
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_ia[2] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[1] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1019(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1019};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[500]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[504]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[496]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[498]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 1019;
}

/*
equation index: 1020
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_ia[3] = chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[2] - chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] * chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1020(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1020};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[501]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[502]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[497]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[503]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[496]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 1020;
}

/*
equation index: 1021
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[3] = chassis.detailedChassis.frAxleDW.rightPushrod.r_b[3] - chassis.detailedChassis.frAxleDW.rightPushrod.r_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1021(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1021};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1602]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1585]] /* chassis.detailedChassis.frAxleDW.rightPushrod.r_b[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1582]] /* chassis.detailedChassis.frAxleDW.rightPushrod.r_a[3] PARAM */);
  threadData->lastEquationSolved = 1021;
}

/*
equation index: 1022
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[2] = chassis.detailedChassis.frAxleDW.rightPushrod.r_b[2] - chassis.detailedChassis.frAxleDW.rightPushrod.r_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1022(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1022};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1601]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1584]] /* chassis.detailedChassis.frAxleDW.rightPushrod.r_b[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1581]] /* chassis.detailedChassis.frAxleDW.rightPushrod.r_a[2] PARAM */);
  threadData->lastEquationSolved = 1022;
}

/*
equation index: 1023
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1] = chassis.detailedChassis.frAxleDW.rightPushrod.r_b[1] - chassis.detailedChassis.frAxleDW.rightPushrod.r_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1023(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1023};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1600]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1583]] /* chassis.detailedChassis.frAxleDW.rightPushrod.r_b[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1580]] /* chassis.detailedChassis.frAxleDW.rightPushrod.r_a[1] PARAM */);
  threadData->lastEquationSolved = 1023;
}

/*
equation index: 1024
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia = chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia / sqrt(chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia * chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1024(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1024};
  real_array tmp276;
  real_array tmp277;
  real_array tmp278;
  modelica_real tmp279;
  real_array tmp280;
  real_array_create(&tmp276, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1600]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp277, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1600]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp278, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1600]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp279 = mul_real_scalar_product(tmp277, tmp278);
  if(!(tmp279 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia * chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia) was %g should be >= 0", tmp279);
    }
  }real_array_create(&tmp280, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp276,sqrt(tmp279),"sqrt(chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia * chassis.detailedChassis.frAxleDW.rightPushrod.rod.rRod_ia)"), tmp280);
  threadData->lastEquationSolved = 1024;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28798(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36359(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28800(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36360(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28796(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36358(DATA *data, threadData_t *threadData);


/*
equation index: 1031
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] = chassis.detailedChassis.frAxleDW.rightPushrod.n1_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1031(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1031};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1579]] /* chassis.detailedChassis.frAxleDW.rightPushrod.n1_a[3] PARAM */);
  threadData->lastEquationSolved = 1031;
}

/*
equation index: 1032
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.r_shape[3] = (-chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1032(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1032};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4583]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1032;
}

/*
equation index: 1033
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] = chassis.detailedChassis.frAxleDW.rightPushrod.n1_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1033(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1033};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1578]] /* chassis.detailedChassis.frAxleDW.rightPushrod.n1_a[2] PARAM */);
  threadData->lastEquationSolved = 1033;
}

/*
equation index: 1034
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.r_shape[2] = (-chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1034(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1034};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4582]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1034;
}

/*
equation index: 1035
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] = chassis.detailedChassis.frAxleDW.rightPushrod.n1_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1035(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1035};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1577]] /* chassis.detailedChassis.frAxleDW.rightPushrod.n1_a[1] PARAM */);
  threadData->lastEquationSolved = 1035;
}

/*
equation index: 1036
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia = smooth(0, if noEvent(sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) / sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0), (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) / sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0), (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) / sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]), 4.503599627370496e13 * (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1036(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1036};
  modelica_real tmp281;
  modelica_real tmp282;
  modelica_real tmp283;
  modelica_real tmp284;
  modelica_boolean tmp285;
  real_array tmp286;
  modelica_real tmp287;
  modelica_real tmp288;
  modelica_real tmp289;
  modelica_real tmp290;
  modelica_real tmp291;
  modelica_real tmp292;
  modelica_real tmp293;
  modelica_real tmp294;
  modelica_real tmp295;
  modelica_real tmp296;
  modelica_real tmp297;
  modelica_real tmp298;
  real_array tmp299;
  modelica_boolean tmp300;
  real_array tmp301;
  real_array tmp302;
  tmp281 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)));
  tmp282 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)));
  tmp283 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)));
  tmp284 = (tmp281 * tmp281) + (tmp282 * tmp282) + (tmp283 * tmp283);
  if(!(tmp284 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp284);
    }
  }tmp285 = GreaterEq(sqrt(tmp284),2.220446049250313e-14);
  tmp300 = (modelica_boolean)tmp285;
  if(tmp300)
  {
    tmp287 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)));
    tmp288 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)));
    tmp289 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)));
    tmp290 = (tmp287 * tmp287) + (tmp288 * tmp288) + (tmp289 * tmp289);
    if(!(tmp290 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp290);
      }
    }tmp291 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)));
    tmp292 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)));
    tmp293 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)));
    tmp294 = (tmp291 * tmp291) + (tmp292 * tmp292) + (tmp293 * tmp293);
    if(!(tmp294 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp294);
      }
    }tmp295 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)));
    tmp296 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)));
    tmp297 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)));
    tmp298 = (tmp295 * tmp295) + (tmp296 * tmp296) + (tmp297 * tmp297);
    if(!(tmp298 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp298);
      }
    }array_alloc_scalar_real_array(&tmp286, 3, (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */))),sqrt(tmp290),"sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */))),sqrt(tmp294),"sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */))),sqrt(tmp298),"sqrt((chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes));
    tmp301 = tmp286;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp299, 3, (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)))), (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1599]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)))), (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1598]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)))));
    tmp301 = tmp299;
  }
  real_array_create(&tmp302, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1588]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp301, tmp302);
  threadData->lastEquationSolved = 1036;
}

/*
equation index: 1037
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r_shape[1] = (-chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1037(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1037};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4612]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1588]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1037;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28797(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36352(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36355(DATA *data, threadData_t *threadData);


/*
equation index: 1041
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r_shape[2] = (-chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1041(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1041};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4613]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1589]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1041;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28799(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36353(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36356(DATA *data, threadData_t *threadData);


/*
equation index: 1045
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r_shape[3] = (-chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1045(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1045};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4614]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1590]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1045;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28801(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36354(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36357(DATA *data, threadData_t *threadData);


/*
equation index: 1049
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.r_shape[1] = (-chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1049(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1049};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4581]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1597]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.n1_a[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1049;
}

/*
equation index: 1050
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.e3_ia[1] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[3] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1050(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1050};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1591]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1590]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1589]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 1050;
}

/*
equation index: 1051
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.e3_ia[2] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[1] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1051(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1051};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1592]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1596]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1588]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1590]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 1051;
}

/*
equation index: 1052
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.e3_ia[3] = chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[2] - chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] * chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1052(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1052};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1593]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1594]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1589]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1595]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1588]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 1052;
}

/*
equation index: 1053
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[3] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1053(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1053};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3389]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3369]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[3] PARAM */);
  threadData->lastEquationSolved = 1053;
}

/*
equation index: 1054
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[2] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1054(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1054};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3388]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3368]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[2] PARAM */);
  threadData->lastEquationSolved = 1054;
}

/*
equation index: 1055
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1055(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1055};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3387]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3367]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.n_b[1] PARAM */);
  threadData->lastEquationSolved = 1055;
}

/*
equation index: 1056
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n / sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1056(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1056};
  real_array tmp303;
  real_array tmp304;
  real_array tmp305;
  modelica_real tmp306;
  real_array tmp307;
  real_array_create(&tmp303, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3387]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp304, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3387]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp305, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3387]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp306 = mul_real_scalar_product(tmp304, tmp305);
  if(!(tmp306 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n) was %g should be >= 0", tmp306);
    }
  }real_array_create(&tmp307, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp303,sqrt(tmp306),"sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.n)"), tmp307);
  threadData->lastEquationSolved = 1056;
}

/*
equation index: 1057
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) * 0.5 * (0.02 + Modelica.Math.Vectors.norm({0.22024339999999998, 0.013385800000000003, 0.004800599999999988}, 2.0))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1057(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1057};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7623]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) * ((0.5) * (0.02 + omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT31, 2.0)));
  threadData->lastEquationSolved = 1057;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36351(DATA *data, threadData_t *threadData);


/*
equation index: 1059
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) * 0.5 * (0.02 + Modelica.Math.Vectors.norm({0.22024339999999998, 0.013385800000000003, 0.004800599999999988}, 2.0))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1059(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1059};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7622]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) * ((0.5) * (0.02 + omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT31, 2.0)));
  threadData->lastEquationSolved = 1059;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36350(DATA *data, threadData_t *threadData);


/*
equation index: 1061
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1061(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1061};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7629]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b variable */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7640]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3384]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7641]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] variable */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3385]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7642]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] variable */));
  threadData->lastEquationSolved = 1061;
}

/*
equation index: 1062
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) * 0.5 * (0.02 + Modelica.Math.Vectors.norm({0.22024339999999998, 0.013385800000000003, 0.004800599999999988}, 2.0))
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1062(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1062};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7621]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) * ((0.5) * (0.02 + omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT31, 2.0)));
  threadData->lastEquationSolved = 1062;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36349(DATA *data, threadData_t *threadData);


/*
equation index: 1064
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia = smooth(0, if noEvent(sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) >= 2.220446049250313e-14) then {0.0, (-chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3]) / sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0), chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] / sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)} else {0.0, (-4.503599627370496e13) * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3], 4.503599627370496e13 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2]})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1064(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1064};
  modelica_real tmp308;
  modelica_real tmp309;
  modelica_real tmp310;
  modelica_boolean tmp311;
  real_array tmp312;
  modelica_real tmp313;
  modelica_real tmp314;
  modelica_real tmp315;
  modelica_real tmp316;
  modelica_real tmp317;
  modelica_real tmp318;
  real_array tmp319;
  modelica_boolean tmp320;
  real_array tmp321;
  real_array tmp322;
  tmp308 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3403]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
  tmp309 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3404]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
  tmp310 = (tmp308 * tmp308) + (tmp309 * tmp309);
  if(!(tmp310 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp310);
    }
  }tmp311 = GreaterEq(sqrt(tmp310),2.220446049250313e-14);
  tmp320 = (modelica_boolean)tmp311;
  if(tmp320)
  {
    tmp313 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3403]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
    tmp314 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3404]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
    tmp315 = (tmp313 * tmp313) + (tmp314 * tmp314);
    if(!(tmp315 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp315);
      }
    }tmp316 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3403]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
    tmp317 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3404]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
    tmp318 = (tmp316 * tmp316) + (tmp317 * tmp317);
    if(!(tmp318 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp318);
      }
    }array_alloc_scalar_real_array(&tmp312, 3, (modelica_real)0.0, (modelica_real)DIVISION_SIM((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3404]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)),sqrt(tmp315),"sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3403]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */),sqrt(tmp318),"sqrt(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)",equationIndexes));
    tmp321 = tmp312;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp319, 3, (modelica_real)0.0, (modelica_real)(-4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3404]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3403]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)));
    tmp321 = tmp319;
  }
  real_array_create(&tmp322, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3396]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp321, tmp322);
  threadData->lastEquationSolved = 1064;
}

/*
equation index: 1065
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[2] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1065(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1065};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3359]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3397]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */);
  threadData->lastEquationSolved = 1065;
}

/*
equation index: 1066
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]) * 0.5 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1066(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1066};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7754]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3397]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3395]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1066;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28996(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36344(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36347(DATA *data, threadData_t *threadData);


/*
equation index: 1070
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[3] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1070(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1070};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3360]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3398]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */);
  threadData->lastEquationSolved = 1070;
}

/*
equation index: 1071
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]) * 0.5 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1071(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1071};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7755]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3398]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3395]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1071;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28994(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36345(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36348(DATA *data, threadData_t *threadData);


/*
equation index: 1075
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[1] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1075(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1075};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3358]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.e2_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3396]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */);
  threadData->lastEquationSolved = 1075;
}

/*
equation index: 1076
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]) * 0.5 * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1076(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1076};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7753]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3396]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3395]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1076;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28998(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36343(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36346(DATA *data, threadData_t *threadData);


/*
equation index: 1080
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1080(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1080};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3399]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3403]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3398]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3404]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3397]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 1080;
}

/*
equation index: 1081
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1081(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1081};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3400]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3404]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3396]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3402]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3398]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 1081;
}

/*
equation index: 1082
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] = chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] - chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1082(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1082};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3401]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3402]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3397]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3403]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3396]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 1082;
}

/*
equation index: 1083
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] = chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1083(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1083};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3613]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[3] PARAM */);
  threadData->lastEquationSolved = 1083;
}

/*
equation index: 1084
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] = chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1084(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1084};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3612]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[2] PARAM */);
  threadData->lastEquationSolved = 1084;
}

/*
equation index: 1085
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] = chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1085(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1085};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3611]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[1] PARAM */);
  threadData->lastEquationSolved = 1085;
}

/*
equation index: 1086
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] = chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1086(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1086};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3625]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[3] PARAM */);
  threadData->lastEquationSolved = 1086;
}

/*
equation index: 1087
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1087(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1087};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4466]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
  threadData->lastEquationSolved = 1087;
}

/*
equation index: 1088
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1088(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1088};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4499]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4466]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[3] PARAM */);
  threadData->lastEquationSolved = 1088;
}

/*
equation index: 1089
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] = chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1089(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1089};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3624]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[2] PARAM */);
  threadData->lastEquationSolved = 1089;
}

/*
equation index: 1090
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1090(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1090};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4465]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
  threadData->lastEquationSolved = 1090;
}

/*
equation index: 1091
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1091(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1091};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4498]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4465]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[2] PARAM */);
  threadData->lastEquationSolved = 1091;
}

/*
equation index: 1092
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] = chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1092(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1092};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3623]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[1] PARAM */);
  threadData->lastEquationSolved = 1092;
}

/*
equation index: 1093
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n = smooth(0, if noEvent(sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1093(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1093};
  modelica_real tmp323;
  modelica_real tmp324;
  modelica_real tmp325;
  modelica_real tmp326;
  modelica_boolean tmp327;
  real_array tmp328;
  modelica_real tmp329;
  modelica_real tmp330;
  modelica_real tmp331;
  modelica_real tmp332;
  modelica_real tmp333;
  modelica_real tmp334;
  modelica_real tmp335;
  modelica_real tmp336;
  modelica_real tmp337;
  modelica_real tmp338;
  modelica_real tmp339;
  modelica_real tmp340;
  real_array tmp341;
  modelica_boolean tmp342;
  real_array tmp343;
  real_array tmp344;
  tmp323 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
  tmp324 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
  tmp325 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
  tmp326 = (tmp323 * tmp323) + (tmp324 * tmp324) + (tmp325 * tmp325);
  if(!(tmp326 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) was %g should be >= 0", tmp326);
    }
  }tmp327 = GreaterEq(sqrt(tmp326),2.220446049250313e-14);
  tmp342 = (modelica_boolean)tmp327;
  if(tmp342)
  {
    tmp329 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
    tmp330 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
    tmp331 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
    tmp332 = (tmp329 * tmp329) + (tmp330 * tmp330) + (tmp331 * tmp331);
    if(!(tmp332 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) was %g should be >= 0", tmp332);
      }
    }tmp333 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
    tmp334 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
    tmp335 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
    tmp336 = (tmp333 * tmp333) + (tmp334 * tmp334) + (tmp335 * tmp335);
    if(!(tmp336 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) was %g should be >= 0", tmp336);
      }
    }tmp337 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
    tmp338 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */);
    tmp339 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */);
    tmp340 = (tmp337 * tmp337) + (tmp338 * tmp338) + (tmp339 * tmp339);
    if(!(tmp340 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0) was %g should be >= 0", tmp340);
      }
    }array_alloc_scalar_real_array(&tmp328, 3, (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */),sqrt(tmp332),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */),sqrt(tmp336),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */),sqrt(tmp340),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3]) ^ 2.0)",equationIndexes));
    tmp343 = tmp328;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp341, 3, (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */)));
    tmp343 = tmp341;
  }
  real_array_create(&tmp344, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4410]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp343, tmp344);
  threadData->lastEquationSolved = 1093;
}

/*
equation index: 1094
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.e = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n / sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1094(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1094};
  real_array tmp345;
  real_array tmp346;
  real_array tmp347;
  modelica_real tmp348;
  real_array tmp349;
  real_array_create(&tmp345, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4410]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp346, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4410]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp347, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4410]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp348 = mul_real_scalar_product(tmp346, tmp347);
  if(!(tmp348 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n) was %g should be >= 0", tmp348);
    }
  }real_array_create(&tmp349, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4406]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp345,sqrt(tmp348),"sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.n)"), tmp349);
  threadData->lastEquationSolved = 1094;
}

/*
equation index: 1095
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.e[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1095(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1095};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9187]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4406]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.e[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1095;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36325(DATA *data, threadData_t *threadData);


/*
equation index: 1097
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.e[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1097(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1097};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9188]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4407]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.e[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1097;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36326(DATA *data, threadData_t *threadData);


/*
equation index: 1099
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.e[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1099(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1099};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9189]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4408]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.e[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1099;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36327(DATA *data, threadData_t *threadData);


/*
equation index: 1101
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1101(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1101};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4464]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */);
  threadData->lastEquationSolved = 1101;
}

/*
equation index: 1102
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1102(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1102};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4497]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4464]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod1_ia[1] PARAM */);
  threadData->lastEquationSolved = 1102;
}

/*
equation index: 1103
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia / sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1103(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1103};
  real_array tmp350;
  real_array tmp351;
  real_array tmp352;
  modelica_real tmp353;
  real_array tmp354;
  real_array_create(&tmp350, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4497]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp351, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4497]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp352, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4497]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp353 = mul_real_scalar_product(tmp351, tmp352);
  if(!(tmp353 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia) was %g should be >= 0", tmp353);
    }
  }real_array_create(&tmp354, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4491]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp350,sqrt(tmp353),"sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rRod_ia)"), tmp354);
  threadData->lastEquationSolved = 1103;
}

/*
equation index: 1104
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia = smooth(0, if noEvent(sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) >= 2.220446049250313e-14) then {0.0, (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3]) / sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0), chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] / sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)} else {0.0, (-4.503599627370496e13) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3], 4.503599627370496e13 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2]})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1104(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1104};
  modelica_real tmp355;
  modelica_real tmp356;
  modelica_real tmp357;
  modelica_boolean tmp358;
  real_array tmp359;
  modelica_real tmp360;
  modelica_real tmp361;
  modelica_real tmp362;
  modelica_real tmp363;
  modelica_real tmp364;
  modelica_real tmp365;
  real_array tmp366;
  modelica_boolean tmp367;
  real_array tmp368;
  real_array tmp369;
  tmp355 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4492]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
  tmp356 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4493]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
  tmp357 = (tmp355 * tmp355) + (tmp356 * tmp356);
  if(!(tmp357 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp357);
    }
  }tmp358 = GreaterEq(sqrt(tmp357),2.220446049250313e-14);
  tmp367 = (modelica_boolean)tmp358;
  if(tmp367)
  {
    tmp360 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4492]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
    tmp361 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4493]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
    tmp362 = (tmp360 * tmp360) + (tmp361 * tmp361);
    if(!(tmp362 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp362);
      }
    }tmp363 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4492]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
    tmp364 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4493]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
    tmp365 = (tmp363 * tmp363) + (tmp364 * tmp364);
    if(!(tmp365 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0) was %g should be >= 0", tmp365);
      }
    }array_alloc_scalar_real_array(&tmp359, 3, (modelica_real)0.0, (modelica_real)DIVISION_SIM((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4493]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)),sqrt(tmp362),"sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4492]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */),sqrt(tmp365),"sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] ^ 2.0)",equationIndexes));
    tmp368 = tmp359;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp366, 3, (modelica_real)0.0, (modelica_real)(-4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4493]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4492]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)));
    tmp368 = tmp366;
  }
  real_array_create(&tmp369, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4485]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp368, tmp369);
  threadData->lastEquationSolved = 1104;
}

/*
equation index: 1105
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1105(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1105};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4489]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4493]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4485]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4491]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4487]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 1105;
}

/*
equation index: 1106
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1106(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1106};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4490]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4491]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4486]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4492]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4485]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 1106;
}

/*
equation index: 1107
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1107(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1107};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4488]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4492]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4487]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4493]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4486]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 1107;
}

/*
equation index: 1108
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1108(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1108};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4448]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4486]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */);
  threadData->lastEquationSolved = 1108;
}

/*
equation index: 1109
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1109(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1109};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9505]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4486]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[2] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4484]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1109;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28990(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36332(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36335(DATA *data, threadData_t *threadData);


/*
equation index: 1113
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1113(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1113};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4449]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4487]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */);
  threadData->lastEquationSolved = 1113;
}

/*
equation index: 1114
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1114(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1114};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9506]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4487]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[3] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4484]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1114;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28988(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36333(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36336(DATA *data, threadData_t *threadData);


/*
equation index: 1118
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1118(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1118};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4447]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.e2_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4485]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */);
  threadData->lastEquationSolved = 1118;
}

/*
equation index: 1119
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1119(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1119};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9504]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4485]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.e2_ia[1] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4484]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1119;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28992(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36331(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36334(DATA *data, threadData_t *threadData);


/*
equation index: 1123
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1123(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1123};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4451]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4492]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[2] PARAM */);
  threadData->lastEquationSolved = 1123;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28991(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36338(DATA *data, threadData_t *threadData);


/*
equation index: 1126
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1126(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1126};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4452]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4493]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[3] PARAM */);
  threadData->lastEquationSolved = 1126;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28989(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36339(DATA *data, threadData_t *threadData);


/*
equation index: 1129
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1129(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1129};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4450]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.eRod1_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4491]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.eRod_ia[1] PARAM */);
  threadData->lastEquationSolved = 1129;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28993(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36337(DATA *data, threadData_t *threadData);


/*
equation index: 1132
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] = chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1132(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1132};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3619]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[3] PARAM */);
  threadData->lastEquationSolved = 1132;
}

/*
equation index: 1133
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] = chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1133(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1133};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3622]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[3] PARAM */);
  threadData->lastEquationSolved = 1133;
}

/*
equation index: 1134
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1134(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1134};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4421]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */));
  threadData->lastEquationSolved = 1134;
}

/*
equation index: 1135
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1135(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1135};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4418]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4421]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] PARAM */);
  threadData->lastEquationSolved = 1135;
}

/*
equation index: 1136
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1136(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1136};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4437]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */));
  threadData->lastEquationSolved = 1136;
}

/*
equation index: 1137
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1137(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1137};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4434]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4437]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] PARAM */);
  threadData->lastEquationSolved = 1137;
}

/*
equation index: 1138
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] + (-0.5) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1138(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1138};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4469]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4399]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[3] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */));
  threadData->lastEquationSolved = 1138;
}

/*
equation index: 1139
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[3].k = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1139(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1139};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4463]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[3].k PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4469]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3] PARAM */);
  threadData->lastEquationSolved = 1139;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28767(DATA *data, threadData_t *threadData);


/*
equation index: 1141
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1141(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1141};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4515]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4469]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[3] PARAM */);
  threadData->lastEquationSolved = 1141;
}

/*
equation index: 1142
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1142(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1142};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4512]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4515]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] PARAM */);
  threadData->lastEquationSolved = 1142;
}

/*
equation index: 1143
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] = chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1143(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1143};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3618]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[2] PARAM */);
  threadData->lastEquationSolved = 1143;
}

/*
equation index: 1144
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] = chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1144(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1144};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3621]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[2] PARAM */);
  threadData->lastEquationSolved = 1144;
}

/*
equation index: 1145
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1145(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1145};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4420]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */));
  threadData->lastEquationSolved = 1145;
}

/*
equation index: 1146
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1146(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1146};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4417]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4420]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] PARAM */);
  threadData->lastEquationSolved = 1146;
}

/*
equation index: 1147
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1147(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1147};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4436]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */));
  threadData->lastEquationSolved = 1147;
}

/*
equation index: 1148
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1148(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1148};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4433]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4436]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] PARAM */);
  threadData->lastEquationSolved = 1148;
}

/*
equation index: 1149
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] + (-0.5) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1149(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1149};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4468]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4398]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[2] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */));
  threadData->lastEquationSolved = 1149;
}

/*
equation index: 1150
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[2].k = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1150(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1150};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4462]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[2].k PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4468]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2] PARAM */);
  threadData->lastEquationSolved = 1150;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28766(DATA *data, threadData_t *threadData);


/*
equation index: 1152
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1152(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1152};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4514]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4468]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[2] PARAM */);
  threadData->lastEquationSolved = 1152;
}

/*
equation index: 1153
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1153(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1153};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4511]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4514]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] PARAM */);
  threadData->lastEquationSolved = 1153;
}

/*
equation index: 1154
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] = chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1154(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1154};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3617]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[1] PARAM */);
  threadData->lastEquationSolved = 1154;
}

/*
equation index: 1155
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] = chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1155(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1155};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3620]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[1] PARAM */);
  threadData->lastEquationSolved = 1155;
}

/*
equation index: 1156
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1156(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1156};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4419]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */));
  threadData->lastEquationSolved = 1156;
}

/*
equation index: 1157
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.length = sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1157(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1157};
  modelica_real tmp370;
  modelica_real tmp371;
  modelica_real tmp372;
  modelica_real tmp373;
  tmp370 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4419]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] PARAM */);
  tmp371 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4420]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] PARAM */);
  tmp372 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4421]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] PARAM */);
  tmp373 = (tmp370 * tmp370) + (tmp371 * tmp371) + (tmp372 * tmp372);
  if(!(tmp373 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[3] ^ 2.0) was %g should be >= 0", tmp373);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4415]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.length PARAM */) = sqrt(tmp373);
  threadData->lastEquationSolved = 1157;
}

/*
equation index: 1158
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.width = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1158(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1158};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4425]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4415]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1158;
}

/*
equation index: 1159
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.height = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1159(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1159};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4414]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4425]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.width PARAM */);
  threadData->lastEquationSolved = 1159;
}

/*
equation index: 1160
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1160(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1160};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4416]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4419]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToAft.r[1] PARAM */);
  threadData->lastEquationSolved = 1160;
}

/*
equation index: 1161
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1161(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1161};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4435]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */));
  threadData->lastEquationSolved = 1161;
}

/*
equation index: 1162
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.length = sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1162(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1162};
  modelica_real tmp374;
  modelica_real tmp375;
  modelica_real tmp376;
  modelica_real tmp377;
  tmp374 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4435]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] PARAM */);
  tmp375 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4436]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] PARAM */);
  tmp376 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4437]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] PARAM */);
  tmp377 = (tmp374 * tmp374) + (tmp375 * tmp375) + (tmp376 * tmp376);
  if(!(tmp377 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[3] ^ 2.0) was %g should be >= 0", tmp377);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4431]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.length PARAM */) = sqrt(tmp377);
  threadData->lastEquationSolved = 1162;
}

/*
equation index: 1163
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.width = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1163(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1163};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4441]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4431]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1163;
}

/*
equation index: 1164
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.height = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1164(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1164};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4430]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4441]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.width PARAM */);
  threadData->lastEquationSolved = 1164;
}

/*
equation index: 1165
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1165(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1165};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4432]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4435]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperFrameToFore.r[1] PARAM */);
  threadData->lastEquationSolved = 1165;
}

/*
equation index: 1166
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] + (-0.5) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1166(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1166};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4467]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4397]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upper_o[1] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */));
  threadData->lastEquationSolved = 1166;
}

/*
equation index: 1167
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[1].k = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1167(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1167};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4461]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.position_b[1].k PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4467]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1] PARAM */);
  threadData->lastEquationSolved = 1167;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28765(DATA *data, threadData_t *threadData);


/*
equation index: 1169
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1169(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1169};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4513]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4467]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rRod2_ib[1] PARAM */);
  threadData->lastEquationSolved = 1169;
}

/*
equation index: 1170
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.length = sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1170(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1170};
  modelica_real tmp378;
  modelica_real tmp379;
  modelica_real tmp380;
  modelica_real tmp381;
  tmp378 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4513]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] PARAM */);
  tmp379 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4514]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] PARAM */);
  tmp380 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4515]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] PARAM */);
  tmp381 = (tmp378 * tmp378) + (tmp379 * tmp379) + (tmp380 * tmp380);
  if(!(tmp381 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[3] ^ 2.0) was %g should be >= 0", tmp381);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4509]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.length PARAM */) = sqrt(tmp381);
  threadData->lastEquationSolved = 1170;
}

/*
equation index: 1171
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1171(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1171};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4510]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4513]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod2.r[1] PARAM */);
  threadData->lastEquationSolved = 1171;
}

/*
equation index: 1172
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revoluteLength = 0.02 + Modelica.Math.Vectors.norm({chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1], chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2], chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1172(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1172};
  real_array tmp382;
  array_alloc_scalar_real_array(&tmp382, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */));
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4482]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revoluteLength PARAM */) = 0.02 + omc_Modelica_Math_Vectors_norm(threadData, tmp382, 2.0);
  threadData->lastEquationSolved = 1172;
}

/*
equation index: 1173
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revoluteLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1173(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1173};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4471]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4482]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revoluteLength PARAM */);
  threadData->lastEquationSolved = 1173;
}

/*
equation index: 1174
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b = smooth(0, if noEvent(sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1174(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1174};
  modelica_real tmp383;
  modelica_real tmp384;
  modelica_real tmp385;
  modelica_real tmp386;
  modelica_boolean tmp387;
  real_array tmp388;
  modelica_real tmp389;
  modelica_real tmp390;
  modelica_real tmp391;
  modelica_real tmp392;
  modelica_real tmp393;
  modelica_real tmp394;
  modelica_real tmp395;
  modelica_real tmp396;
  modelica_real tmp397;
  modelica_real tmp398;
  modelica_real tmp399;
  modelica_real tmp400;
  real_array tmp401;
  modelica_boolean tmp402;
  real_array tmp403;
  real_array tmp404;
  tmp383 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */);
  tmp384 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */);
  tmp385 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */);
  tmp386 = (tmp383 * tmp383) + (tmp384 * tmp384) + (tmp385 * tmp385);
  if(!(tmp386 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) was %g should be >= 0", tmp386);
    }
  }tmp387 = GreaterEq(sqrt(tmp386),2.220446049250313e-14);
  tmp402 = (modelica_boolean)tmp387;
  if(tmp402)
  {
    tmp389 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */);
    tmp390 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */);
    tmp391 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */);
    tmp392 = (tmp389 * tmp389) + (tmp390 * tmp390) + (tmp391 * tmp391);
    if(!(tmp392 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) was %g should be >= 0", tmp392);
      }
    }tmp393 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */);
    tmp394 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */);
    tmp395 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */);
    tmp396 = (tmp393 * tmp393) + (tmp394 * tmp394) + (tmp395 * tmp395);
    if(!(tmp396 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) was %g should be >= 0", tmp396);
      }
    }tmp397 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */);
    tmp398 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */);
    tmp399 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */);
    tmp400 = (tmp397 * tmp397) + (tmp398 * tmp398) + (tmp399 * tmp399);
    if(!(tmp400 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0) was %g should be >= 0", tmp400);
      }
    }array_alloc_scalar_real_array(&tmp388, 3, (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */),sqrt(tmp392),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */),sqrt(tmp396),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */),sqrt(tmp400),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3]) ^ 2.0)",equationIndexes));
    tmp403 = tmp388;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp401, 3, (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4394]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[1] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4395]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[2] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4396]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.upperAft_i[3] PARAM */)));
    tmp403 = tmp401;
  }
  real_array_create(&tmp404, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4456]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp403, tmp404);
  threadData->lastEquationSolved = 1174;
}

/*
equation index: 1175
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1175(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1175};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4476]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4456]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[1] PARAM */);
  threadData->lastEquationSolved = 1175;
}

/*
equation index: 1176
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1176(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1176};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4477]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4457]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[2] PARAM */);
  threadData->lastEquationSolved = 1176;
}

/*
equation index: 1177
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1177(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1177};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4478]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4458]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.n_b[3] PARAM */);
  threadData->lastEquationSolved = 1177;
}

/*
equation index: 1178
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n / sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1178(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1178};
  real_array tmp405;
  real_array tmp406;
  real_array tmp407;
  modelica_real tmp408;
  real_array tmp409;
  real_array_create(&tmp405, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4476]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp406, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4476]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp407, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4476]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp408 = mul_real_scalar_product(tmp406, tmp407);
  if(!(tmp408 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n) was %g should be >= 0", tmp408);
    }
  }real_array_create(&tmp409, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp405,sqrt(tmp408),"sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.n)"), tmp409);
  threadData->lastEquationSolved = 1178;
}

/*
equation index: 1179
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1179(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1179};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9372]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4471]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1179;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36340(DATA *data, threadData_t *threadData);


/*
equation index: 1181
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1181(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1181};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9373]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4471]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1181;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36341(DATA *data, threadData_t *threadData);


/*
equation index: 1183
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1183(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1183};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9374]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4471]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1183;
}

/*
equation index: 1184
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1184(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1184};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9391]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9392]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] DUMMY_STATE */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9393]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3] DUMMY_STATE */));
  threadData->lastEquationSolved = 1184;
}

/*
equation index: 1185
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * $DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1185(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1185};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1883]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1893]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1]) DUMMY_DER */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1894]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2]) DUMMY_DER */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1895]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]) DUMMY_DER */));
  threadData->lastEquationSolved = 1185;
}

/*
equation index: 1186
type: SIMPLE_ASSIGN
$DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] * $DER.$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1186(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1186};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[774]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e_r_b)) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[1] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[784]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[1])) DUMMY_DER */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4473]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[2] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[785]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[2])) DUMMY_DER */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4474]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.e[3] PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[786]] /* der(der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.r_b[3])) DUMMY_DER */));
  threadData->lastEquationSolved = 1186;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36342(DATA *data, threadData_t *threadData);


/*
equation index: 1188
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] = chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1188(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1188};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3607]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[3] PARAM */);
  threadData->lastEquationSolved = 1188;
}

/*
equation index: 1189
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] = chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1189(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1189};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3610]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[3] PARAM */);
  threadData->lastEquationSolved = 1189;
}

/*
equation index: 1190
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1190(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1190};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4329]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */));
  threadData->lastEquationSolved = 1190;
}

/*
equation index: 1191
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1191(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1191};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4326]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4329]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] PARAM */);
  threadData->lastEquationSolved = 1191;
}

/*
equation index: 1192
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1192(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1192};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4345]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */));
  threadData->lastEquationSolved = 1192;
}

/*
equation index: 1193
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1193(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1193};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4342]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4345]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] PARAM */);
  threadData->lastEquationSolved = 1193;
}

/*
equation index: 1194
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] + (-0.5) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1194(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1194};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4371]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4387]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[3] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */));
  threadData->lastEquationSolved = 1194;
}

/*
equation index: 1195
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1195(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1195};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4368]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4371]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[3] PARAM */);
  threadData->lastEquationSolved = 1195;
}

/*
equation index: 1196
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] = chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1196(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1196};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3606]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[2] PARAM */);
  threadData->lastEquationSolved = 1196;
}

/*
equation index: 1197
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] = chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1197(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1197};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3609]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[2] PARAM */);
  threadData->lastEquationSolved = 1197;
}

/*
equation index: 1198
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1198(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1198};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4328]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */));
  threadData->lastEquationSolved = 1198;
}

/*
equation index: 1199
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1199(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1199};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4325]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4328]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] PARAM */);
  threadData->lastEquationSolved = 1199;
}

/*
equation index: 1200
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1200(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1200};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4344]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */));
  threadData->lastEquationSolved = 1200;
}

/*
equation index: 1201
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1201(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1201};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4341]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4344]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] PARAM */);
  threadData->lastEquationSolved = 1201;
}

/*
equation index: 1202
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] + (-0.5) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1202(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1202};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4370]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4386]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[2] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */));
  threadData->lastEquationSolved = 1202;
}

/*
equation index: 1203
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1203(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1203};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4367]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4370]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[2] PARAM */);
  threadData->lastEquationSolved = 1203;
}

/*
equation index: 1204
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] = chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1204(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1204};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3605]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[1] PARAM */);
  threadData->lastEquationSolved = 1204;
}

/*
equation index: 1205
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] = chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1205(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1205};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3608]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[1] PARAM */);
  threadData->lastEquationSolved = 1205;
}

/*
equation index: 1206
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1206(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1206};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4327]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */));
  threadData->lastEquationSolved = 1206;
}

/*
equation index: 1207
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.length = sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1207(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1207};
  modelica_real tmp410;
  modelica_real tmp411;
  modelica_real tmp412;
  modelica_real tmp413;
  tmp410 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4327]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] PARAM */);
  tmp411 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4328]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] PARAM */);
  tmp412 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4329]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] PARAM */);
  tmp413 = (tmp410 * tmp410) + (tmp411 * tmp411) + (tmp412 * tmp412);
  if(!(tmp413 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[3] ^ 2.0) was %g should be >= 0", tmp413);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4323]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.length PARAM */) = sqrt(tmp413);
  threadData->lastEquationSolved = 1207;
}

/*
equation index: 1208
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.width = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1208(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1208};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4333]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4323]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1208;
}

/*
equation index: 1209
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.height = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1209(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1209};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4322]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4333]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.width PARAM */);
  threadData->lastEquationSolved = 1209;
}

/*
equation index: 1210
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1210(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1210};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4324]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4327]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToAft.r[1] PARAM */);
  threadData->lastEquationSolved = 1210;
}

/*
equation index: 1211
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] = 0.5 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1211(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1211};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4343]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */));
  threadData->lastEquationSolved = 1211;
}

/*
equation index: 1212
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.length = sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1212(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1212};
  modelica_real tmp414;
  modelica_real tmp415;
  modelica_real tmp416;
  modelica_real tmp417;
  tmp414 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4343]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] PARAM */);
  tmp415 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4344]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] PARAM */);
  tmp416 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4345]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] PARAM */);
  tmp417 = (tmp414 * tmp414) + (tmp415 * tmp415) + (tmp416 * tmp416);
  if(!(tmp417 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[3] ^ 2.0) was %g should be >= 0", tmp417);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4339]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.length PARAM */) = sqrt(tmp417);
  threadData->lastEquationSolved = 1212;
}

/*
equation index: 1213
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.width = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1213(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1213};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4349]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4339]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1213;
}

/*
equation index: 1214
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.height = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1214(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1214};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4338]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4349]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.width PARAM */);
  threadData->lastEquationSolved = 1214;
}

/*
equation index: 1215
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1215(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1215};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4340]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4343]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerFrameToFore.r[1] PARAM */);
  threadData->lastEquationSolved = 1215;
}

/*
equation index: 1216
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] + (-0.5) * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1216(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1216};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4369]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4385]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lower_o[1] PARAM */) + (-0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */));
  threadData->lastEquationSolved = 1216;
}

/*
equation index: 1217
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.length = sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1217(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1217};
  modelica_real tmp418;
  modelica_real tmp419;
  modelica_real tmp420;
  modelica_real tmp421;
  tmp418 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4369]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[1] PARAM */);
  tmp419 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4370]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[2] PARAM */);
  tmp420 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4371]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[3] PARAM */);
  tmp421 = (tmp418 * tmp418) + (tmp419 * tmp419) + (tmp420 * tmp420);
  if(!(tmp421 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[3] ^ 2.0) was %g should be >= 0", tmp421);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4365]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.length PARAM */) = sqrt(tmp421);
  threadData->lastEquationSolved = 1217;
}

/*
equation index: 1218
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1218(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1218};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4366]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4369]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerLink.r[1] PARAM */);
  threadData->lastEquationSolved = 1218;
}

/*
equation index: 1219
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n = smooth(0, if noEvent(sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) / sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1219(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1219};
  modelica_real tmp422;
  modelica_real tmp423;
  modelica_real tmp424;
  modelica_real tmp425;
  modelica_boolean tmp426;
  real_array tmp427;
  modelica_real tmp428;
  modelica_real tmp429;
  modelica_real tmp430;
  modelica_real tmp431;
  modelica_real tmp432;
  modelica_real tmp433;
  modelica_real tmp434;
  modelica_real tmp435;
  modelica_real tmp436;
  modelica_real tmp437;
  modelica_real tmp438;
  modelica_real tmp439;
  real_array tmp440;
  modelica_boolean tmp441;
  real_array tmp442;
  real_array tmp443;
  tmp422 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */);
  tmp423 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */);
  tmp424 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */);
  tmp425 = (tmp422 * tmp422) + (tmp423 * tmp423) + (tmp424 * tmp424);
  if(!(tmp425 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) was %g should be >= 0", tmp425);
    }
  }tmp426 = GreaterEq(sqrt(tmp425),2.220446049250313e-14);
  tmp441 = (modelica_boolean)tmp426;
  if(tmp441)
  {
    tmp428 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */);
    tmp429 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */);
    tmp430 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */);
    tmp431 = (tmp428 * tmp428) + (tmp429 * tmp429) + (tmp430 * tmp430);
    if(!(tmp431 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) was %g should be >= 0", tmp431);
      }
    }tmp432 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */);
    tmp433 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */);
    tmp434 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */);
    tmp435 = (tmp432 * tmp432) + (tmp433 * tmp433) + (tmp434 * tmp434);
    if(!(tmp435 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) was %g should be >= 0", tmp435);
      }
    }tmp436 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */);
    tmp437 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */);
    tmp438 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */);
    tmp439 = (tmp436 * tmp436) + (tmp437 * tmp437) + (tmp438 * tmp438);
    if(!(tmp439 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0) was %g should be >= 0", tmp439);
      }
    }array_alloc_scalar_real_array(&tmp427, 3, (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */),sqrt(tmp431),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */),sqrt(tmp435),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */),sqrt(tmp439),"sqrt((chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]) ^ 2.0)",equationIndexes));
    tmp442 = tmp427;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp440, 3, (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */)));
    tmp442 = tmp440;
  }
  real_array_create(&tmp443, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4360]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp442, tmp443);
  threadData->lastEquationSolved = 1219;
}

/*
equation index: 1220
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n / sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1220(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1220};
  real_array tmp444;
  real_array tmp445;
  real_array tmp446;
  modelica_real tmp447;
  real_array tmp448;
  real_array_create(&tmp444, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4360]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp445, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4360]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp446, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4360]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp447 = mul_real_scalar_product(tmp445, tmp446);
  if(!(tmp447 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n) was %g should be >= 0", tmp447);
    }
  }real_array_create(&tmp448, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp444,sqrt(tmp447),"sqrt(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.n)"), tmp448);
  threadData->lastEquationSolved = 1220;
}

/*
equation index: 1221
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1221(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1221};
  modelica_real tmp449;
  modelica_real tmp450;
  tmp449 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */);
  tmp450 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9114]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] DUMMY_STATE */) = (tmp449 * tmp449) + (1.0 - ((tmp450 * tmp450))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 1221;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28890(DATA *data, threadData_t *threadData);


/*
equation index: 1223
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] ^ 2.0) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1223(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1223};
  modelica_real tmp451;
  tmp451 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1826]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,2]) DUMMY_DER */) = (1.0 - ((tmp451 * tmp451))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 1223;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36329(DATA *data, threadData_t *threadData);


/*
equation index: 1225
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1225(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1225};
  modelica_real tmp452;
  modelica_real tmp453;
  tmp452 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */);
  tmp453 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9110]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] DUMMY_STATE */) = (tmp452 * tmp452) + (1.0 - ((tmp453 * tmp453))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 1225;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28891(DATA *data, threadData_t *threadData);


/*
equation index: 1227
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] ^ 2.0) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1227(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1227};
  modelica_real tmp454;
  tmp454 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1822]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,1]) DUMMY_DER */) = (1.0 - ((tmp454 * tmp454))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 1227;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36328(DATA *data, threadData_t *threadData);


/*
equation index: 1229
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1229(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1229};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9111]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 1229;
}

/*
equation index: 1230
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1230(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1230};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9112]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 1230;
}

/*
equation index: 1231
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1231(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1231};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9113]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 1231;
}

/*
equation index: 1232
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1232(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1232};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9115]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 1232;
}

/*
equation index: 1233
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] + chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1233(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1233};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9116]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) + ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 1233;
}

/*
equation index: 1234
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] = (chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1234(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1234};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9117]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] DUMMY_STATE */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))))) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))));
  threadData->lastEquationSolved = 1234;
}

/*
equation index: 1235
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] ^ 2.0) * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1235(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1235};
  modelica_real tmp455;
  modelica_real tmp456;
  tmp455 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */);
  tmp456 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9118]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] DUMMY_STATE */) = (tmp455 * tmp455) + (1.0 - ((tmp456 * tmp456))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)));
  threadData->lastEquationSolved = 1235;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28889(DATA *data, threadData_t *threadData);


/*
equation index: 1237
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1237(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1237};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1823]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,2]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)))));
  threadData->lastEquationSolved = 1237;
}

/*
equation index: 1238
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1]) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1238(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1238};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1824]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[1,3]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 1238;
}

/*
equation index: 1239
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2]) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1239(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1239};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1825]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,1]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 1239;
}

/*
equation index: 1240
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1240(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1240};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1827]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[2,3]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)))));
  threadData->lastEquationSolved = 1240;
}

/*
equation index: 1241
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1] = chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1241(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1241};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1828]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,1]) DUMMY_DER */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */)) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)))));
  threadData->lastEquationSolved = 1241;
}

/*
equation index: 1242
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3]) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] * cos(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1242(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1242};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1829]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,2]) DUMMY_DER */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */)))) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */)) * ((cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */))));
  threadData->lastEquationSolved = 1242;
}

/*
equation index: 1243
type: SIMPLE_ASSIGN
$DER.chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3] = (1.0 - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] ^ 2.0) * (-sin(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi)) * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1243(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1243};
  modelica_real tmp457;
  tmp457 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1830]] /* der(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.R_rel.T[3,3]) DUMMY_DER */) = (1.0 - ((tmp457 * tmp457))) * (((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.phi STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w) */)))) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.w STATE(1,chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.a) */)));
  threadData->lastEquationSolved = 1243;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36330(DATA *data, threadData_t *threadData);


/*
equation index: 1245
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength = 0.02 + Modelica.Math.Vectors.norm({chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1], chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2], chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] - chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1245(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1245};
  real_array tmp458;
  array_alloc_scalar_real_array(&tmp458, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4382]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4379]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4383]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4380]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4384]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerFore_i[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4381]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.pDW.lowerAft_i[3] PARAM */));
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4355]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength PARAM */) = 0.02 + omc_Modelica_Math_Vectors_norm(threadData, tmp458, 2.0);
  threadData->lastEquationSolved = 1245;
}

/*
equation index: 1246
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1246(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1246};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9137]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4358]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[3] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4355]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1246;
}

/*
equation index: 1247
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1247(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1247};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9136]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4357]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[2] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4355]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1247;
}

/*
equation index: 1248
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1]) * 0.5 * chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1248(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1248};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9135]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4356]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.e[1] PARAM */))) * ((0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4355]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinderLength PARAM */)));
  threadData->lastEquationSolved = 1248;
}

/*
equation index: 1249
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia = smooth(0, if noEvent(sqrt(chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0) >= 2.220446049250313e-14) then {0.0, (-chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3]) / sqrt(chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0), chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] / sqrt(chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0)} else {0.0, (-4.503599627370496e13) * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3], 4.503599627370496e13 * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2]})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1249(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1249};
  modelica_real tmp459;
  modelica_real tmp460;
  modelica_real tmp461;
  modelica_boolean tmp462;
  real_array tmp463;
  modelica_real tmp464;
  modelica_real tmp465;
  modelica_real tmp466;
  modelica_real tmp467;
  modelica_real tmp468;
  modelica_real tmp469;
  real_array tmp470;
  modelica_boolean tmp471;
  real_array tmp472;
  real_array tmp473;
  tmp459 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2861]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */);
  tmp460 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2860]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */);
  tmp461 = (tmp459 * tmp459) + (tmp460 * tmp460);
  if(!(tmp461 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp461);
    }
  }tmp462 = GreaterEq(sqrt(tmp461),2.220446049250313e-14);
  tmp471 = (modelica_boolean)tmp462;
  if(tmp471)
  {
    tmp464 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2861]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */);
    tmp465 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2860]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */);
    tmp466 = (tmp464 * tmp464) + (tmp465 * tmp465);
    if(!(tmp466 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp466);
      }
    }tmp467 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2861]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */);
    tmp468 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2860]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */);
    tmp469 = (tmp467 * tmp467) + (tmp468 * tmp468);
    if(!(tmp469 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp469);
      }
    }array_alloc_scalar_real_array(&tmp463, 3, (modelica_real)0.0, (modelica_real)DIVISION_SIM((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2861]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */)),sqrt(tmp466),"sqrt(chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2860]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */),sqrt(tmp469),"sqrt(chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] ^ 2.0)",equationIndexes));
    tmp472 = tmp463;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp470, 3, (modelica_real)0.0, (modelica_real)(-4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2861]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2860]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */)));
    tmp472 = tmp470;
  }
  real_array_create(&tmp473, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2853]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp472, tmp473);
  threadData->lastEquationSolved = 1249;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28813(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36322(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28815(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36323(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28817(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36324(DATA *data, threadData_t *threadData);


/*
equation index: 1256
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_ia[1] = chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[3] - chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1256(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1256};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2856]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2860]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2855]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2861]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2854]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 1256;
}

/*
equation index: 1257
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_ia[2] = chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[1] - chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1257(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1257};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2857]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2861]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2853]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2859]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2855]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 1257;
}

/*
equation index: 1258
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_ia[3] = chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[2] - chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1258(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1258};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2858]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2859]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2854]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2860]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2853]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 1258;
}

/*
equation index: 1259
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[3] = chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1259(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1259};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3939]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3616]] /* chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[3] PARAM */);
  threadData->lastEquationSolved = 1259;
}

/*
equation index: 1260
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[3] = chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[3] - chassis.detailedChassis.rrAxleDW.rightTieRod.r_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1260(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1260};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3956]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3939]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3936]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_a[3] PARAM */);
  threadData->lastEquationSolved = 1260;
}

/*
equation index: 1261
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[2] = chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1261(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1261};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3938]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3615]] /* chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[2] PARAM */);
  threadData->lastEquationSolved = 1261;
}

/*
equation index: 1262
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[2] = chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[2] - chassis.detailedChassis.rrAxleDW.rightTieRod.r_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1262(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1262};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3955]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3938]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3935]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_a[2] PARAM */);
  threadData->lastEquationSolved = 1262;
}

/*
equation index: 1263
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[1] = chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1263(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1263};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3937]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3614]] /* chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[1] PARAM */);
  threadData->lastEquationSolved = 1263;
}

/*
equation index: 1264
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] = chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[1] - chassis.detailedChassis.rrAxleDW.rightTieRod.r_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1264(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1264};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3954]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3937]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_b[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3934]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.r_a[1] PARAM */);
  threadData->lastEquationSolved = 1264;
}

/*
equation index: 1265
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia / sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1265(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1265};
  real_array tmp474;
  real_array tmp475;
  real_array tmp476;
  modelica_real tmp477;
  real_array tmp478;
  real_array_create(&tmp474, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3954]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp475, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3954]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp476, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3954]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp477 = mul_real_scalar_product(tmp475, tmp476);
  if(!(tmp477 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia) was %g should be >= 0", tmp477);
    }
  }real_array_create(&tmp478, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3948]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp474,sqrt(tmp477),"sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rRod_ia)"), tmp478);
  threadData->lastEquationSolved = 1265;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28822(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36321(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28818(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36319(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28820(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36320(DATA *data, threadData_t *threadData);


/*
equation index: 1272
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia = smooth(0, if noEvent(sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0) >= 2.220446049250313e-14) then {0.0, (-chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3]) / sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0), chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] / sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0)} else {0.0, (-4.503599627370496e13) * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3], 4.503599627370496e13 * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2]})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1272(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1272};
  modelica_real tmp479;
  modelica_real tmp480;
  modelica_real tmp481;
  modelica_boolean tmp482;
  real_array tmp483;
  modelica_real tmp484;
  modelica_real tmp485;
  modelica_real tmp486;
  modelica_real tmp487;
  modelica_real tmp488;
  modelica_real tmp489;
  real_array tmp490;
  modelica_boolean tmp491;
  real_array tmp492;
  real_array tmp493;
  tmp479 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3950]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */);
  tmp480 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3949]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */);
  tmp481 = (tmp479 * tmp479) + (tmp480 * tmp480);
  if(!(tmp481 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp481);
    }
  }tmp482 = GreaterEq(sqrt(tmp481),2.220446049250313e-14);
  tmp491 = (modelica_boolean)tmp482;
  if(tmp491)
  {
    tmp484 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3950]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */);
    tmp485 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3949]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */);
    tmp486 = (tmp484 * tmp484) + (tmp485 * tmp485);
    if(!(tmp486 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp486);
      }
    }tmp487 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3950]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */);
    tmp488 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3949]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */);
    tmp489 = (tmp487 * tmp487) + (tmp488 * tmp488);
    if(!(tmp489 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0) was %g should be >= 0", tmp489);
      }
    }array_alloc_scalar_real_array(&tmp483, 3, (modelica_real)0.0, (modelica_real)DIVISION_SIM((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3950]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */)),sqrt(tmp486),"sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3949]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */),sqrt(tmp489),"sqrt(chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] ^ 2.0)",equationIndexes));
    tmp492 = tmp483;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp490, 3, (modelica_real)0.0, (modelica_real)(-4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3950]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */)), (modelica_real)(4.503599627370496e13) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3949]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */)));
    tmp492 = tmp490;
  }
  real_array_create(&tmp493, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3942]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp492, tmp493);
  threadData->lastEquationSolved = 1272;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28821(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36317(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28819(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36316(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28823(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36318(DATA *data, threadData_t *threadData);


/*
equation index: 1279
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_ia[1] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[3] - chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1279(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1279};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3945]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3949]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3944]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3950]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3943]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 1279;
}

/*
equation index: 1280
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_ia[2] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[1] - chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1280(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1280};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3946]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3950]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3942]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3948]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3944]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 1280;
}

/*
equation index: 1281
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_ia[3] = chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[2] - chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1281(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1281};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3947]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3948]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3943]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3949]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3942]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 1281;
}

/*
equation index: 1282
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.r[3] = chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[3] - chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1282(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1282};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3921]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3613]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3616]] /* chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[3] PARAM */);
  threadData->lastEquationSolved = 1282;
}

/*
equation index: 1283
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightTieConnection.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1283(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1283};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3918]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3921]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[3] PARAM */);
  threadData->lastEquationSolved = 1283;
}

/*
equation index: 1284
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.r[2] = chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[2] - chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1284(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1284};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3920]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3612]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3615]] /* chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[2] PARAM */);
  threadData->lastEquationSolved = 1284;
}

/*
equation index: 1285
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightTieConnection.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1285(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1285};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3917]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3920]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[2] PARAM */);
  threadData->lastEquationSolved = 1285;
}

/*
equation index: 1286
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.r[1] = chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[1] - chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1286(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1286};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3919]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3611]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3614]] /* chassis.detailedChassis.rrAxleDW.pRightDW.tie_o[1] PARAM */);
  threadData->lastEquationSolved = 1286;
}

/*
equation index: 1287
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.length = sqrt(chassis.detailedChassis.rrAxleDW.rightTieConnection.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieConnection.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieConnection.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1287(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1287};
  modelica_real tmp494;
  modelica_real tmp495;
  modelica_real tmp496;
  modelica_real tmp497;
  tmp494 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3919]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[1] PARAM */);
  tmp495 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3920]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[2] PARAM */);
  tmp496 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3921]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[3] PARAM */);
  tmp497 = (tmp494 * tmp494) + (tmp495 * tmp495) + (tmp496 * tmp496);
  if(!(tmp497 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightTieConnection.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieConnection.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightTieConnection.r[3] ^ 2.0) was %g should be >= 0", tmp497);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3915]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.length PARAM */) = sqrt(tmp497);
  threadData->lastEquationSolved = 1287;
}

/*
equation index: 1288
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.width = chassis.detailedChassis.rrAxleDW.rightTieConnection.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1288(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1288};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3925]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3915]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1288;
}

/*
equation index: 1289
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.height = chassis.detailedChassis.rrAxleDW.rightTieConnection.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1289(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1289};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3914]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3925]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.width PARAM */);
  threadData->lastEquationSolved = 1289;
}

/*
equation index: 1290
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieConnection.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightTieConnection.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1290(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1290};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3916]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3919]] /* chassis.detailedChassis.rrAxleDW.rightTieConnection.r[1] PARAM */);
  threadData->lastEquationSolved = 1290;
}

/*
equation index: 1291
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] = chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[3] - chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1291(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1291};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3628]] /* chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3613]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[3] PARAM */);
  threadData->lastEquationSolved = 1291;
}

/*
equation index: 1292
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1292(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1292};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4816]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */);
  threadData->lastEquationSolved = 1292;
}

/*
equation index: 1293
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] = chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[2] - chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1293(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1293};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3627]] /* chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3612]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[2] PARAM */);
  threadData->lastEquationSolved = 1293;
}

/*
equation index: 1294
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1294(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1294};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4815]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */);
  threadData->lastEquationSolved = 1294;
}

/*
equation index: 1295
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] = chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[1] - chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1295(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1295};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3626]] /* chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3611]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[1] PARAM */);
  threadData->lastEquationSolved = 1295;
}

/*
equation index: 1296
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.length = sqrt(chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1296(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1296};
  modelica_real tmp498;
  modelica_real tmp499;
  modelica_real tmp500;
  modelica_real tmp501;
  tmp498 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */);
  tmp499 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4818]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] PARAM */);
  tmp500 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4819]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] PARAM */);
  tmp501 = (tmp498 * tmp498) + (tmp499 * tmp499) + (tmp500 * tmp500);
  if(!(tmp501 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[3] ^ 2.0) was %g should be >= 0", tmp501);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4813]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.length PARAM */) = sqrt(tmp501);
  threadData->lastEquationSolved = 1296;
}

/*
equation index: 1297
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.width = chassis.detailedChassis.rrAxleDW.toRightWheelCenter.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1297(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1297};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4823]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4813]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1297;
}

/*
equation index: 1298
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.height = chassis.detailedChassis.rrAxleDW.toRightWheelCenter.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1298(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1298};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4812]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4823]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.width PARAM */);
  threadData->lastEquationSolved = 1298;
}

/*
equation index: 1299
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightWheelCenter.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1299(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1299};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4814]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4817]] /* chassis.detailedChassis.rrAxleDW.toRightWheelCenter.r[1] PARAM */);
  threadData->lastEquationSolved = 1299;
}

/*
equation index: 1300
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[3] = -0.199898 + 0.5 * (chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[3] + chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1300(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1300};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4803]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[3] PARAM */) = -0.199898 + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3622]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[3] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3619]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[3] PARAM */));
  threadData->lastEquationSolved = 1300;
}

/*
equation index: 1301
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1301(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1301};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4800]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4803]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[3] PARAM */);
  threadData->lastEquationSolved = 1301;
}

/*
equation index: 1302
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[2] = 0.5 * (chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[2] + chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1302(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1302};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4802]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3621]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[2] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3618]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[2] PARAM */));
  threadData->lastEquationSolved = 1302;
}

/*
equation index: 1303
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1303(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1303};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4799]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4802]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[2] PARAM */);
  threadData->lastEquationSolved = 1303;
}

/*
equation index: 1304
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[1] = 1.5494 + 0.5 * (chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[1] + chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1304(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1304};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4801]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[1] PARAM */) = 1.5494 + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3620]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperFore_i[1] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3617]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upperAft_i[1] PARAM */));
  threadData->lastEquationSolved = 1304;
}

/*
equation index: 1305
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.length = sqrt(chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1305(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1305};
  modelica_real tmp502;
  modelica_real tmp503;
  modelica_real tmp504;
  modelica_real tmp505;
  tmp502 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4801]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[1] PARAM */);
  tmp503 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4802]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[2] PARAM */);
  tmp504 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4803]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[3] PARAM */);
  tmp505 = (tmp502 * tmp502) + (tmp503 * tmp503) + (tmp504 * tmp504);
  if(!(tmp505 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[3] ^ 2.0) was %g should be >= 0", tmp505);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4797]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.length PARAM */) = sqrt(tmp505);
  threadData->lastEquationSolved = 1305;
}

/*
equation index: 1306
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.width = chassis.detailedChassis.rrAxleDW.toRightUpper_i.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1306(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1306};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4807]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4797]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1306;
}

/*
equation index: 1307
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.height = chassis.detailedChassis.rrAxleDW.toRightUpper_i.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1307(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1307};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4796]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4807]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.width PARAM */);
  threadData->lastEquationSolved = 1307;
}

/*
equation index: 1308
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightUpper_i.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1308(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1308};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4798]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4801]] /* chassis.detailedChassis.rrAxleDW.toRightUpper_i.r[1] PARAM */);
  threadData->lastEquationSolved = 1308;
}

/*
equation index: 1309
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.r[3] = -0.199898 + 0.5 * (chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[3] + chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[3])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1309(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1309};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4771]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[3] PARAM */) = -0.199898 + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3610]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[3] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3607]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[3] PARAM */));
  threadData->lastEquationSolved = 1309;
}

/*
equation index: 1310
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.toRightLower_i.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1310(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1310};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4768]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4771]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[3] PARAM */);
  threadData->lastEquationSolved = 1310;
}

/*
equation index: 1311
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.r[2] = 0.5 * (chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[2] + chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[2])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1311(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1311};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4770]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[2] PARAM */) = (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3609]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[2] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3606]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[2] PARAM */));
  threadData->lastEquationSolved = 1311;
}

/*
equation index: 1312
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.toRightLower_i.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1312(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1312};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4767]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4770]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[2] PARAM */);
  threadData->lastEquationSolved = 1312;
}

/*
equation index: 1313
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.r[1] = 1.5494 + 0.5 * (chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[1] + chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[1])
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1313(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1313};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4769]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[1] PARAM */) = 1.5494 + (0.5) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3608]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerFore_i[1] PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3605]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lowerAft_i[1] PARAM */));
  threadData->lastEquationSolved = 1313;
}

/*
equation index: 1314
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.length = sqrt(chassis.detailedChassis.rrAxleDW.toRightLower_i.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightLower_i.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightLower_i.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1314(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1314};
  modelica_real tmp506;
  modelica_real tmp507;
  modelica_real tmp508;
  modelica_real tmp509;
  tmp506 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4769]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[1] PARAM */);
  tmp507 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4770]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[2] PARAM */);
  tmp508 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4771]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[3] PARAM */);
  tmp509 = (tmp506 * tmp506) + (tmp507 * tmp507) + (tmp508 * tmp508);
  if(!(tmp509 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.toRightLower_i.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightLower_i.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.toRightLower_i.r[3] ^ 2.0) was %g should be >= 0", tmp509);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4765]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.length PARAM */) = sqrt(tmp509);
  threadData->lastEquationSolved = 1314;
}

/*
equation index: 1315
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.width = chassis.detailedChassis.rrAxleDW.toRightLower_i.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1315(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1315};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4775]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4765]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1315;
}

/*
equation index: 1316
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.height = chassis.detailedChassis.rrAxleDW.toRightLower_i.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1316(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1316};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4764]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4775]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.width PARAM */);
  threadData->lastEquationSolved = 1316;
}

/*
equation index: 1317
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.toRightLower_i.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.toRightLower_i.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1317(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1317};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4766]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4769]] /* chassis.detailedChassis.rrAxleDW.toRightLower_i.r[1] PARAM */);
  threadData->lastEquationSolved = 1317;
}

/*
equation index: 1318
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[1] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.rCM[1] - chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1318(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1318};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4260]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3589]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.rCM[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3623]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[1] PARAM */);
  threadData->lastEquationSolved = 1318;
}

/*
equation index: 1319
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.r_shape[1] = chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[1] - 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1319(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1319};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8959]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.r_shape[1] variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4260]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[1] PARAM */) - 0.015;
  threadData->lastEquationSolved = 1319;
}

/*
equation index: 1320
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[2] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.rCM[2] - chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1320(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1320};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4261]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3590]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.rCM[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3624]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[2] PARAM */);
  threadData->lastEquationSolved = 1320;
}

/*
equation index: 1321
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[3] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.rCM[3] - chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1321(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1321};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4262]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3591]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.rCM[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3625]] /* chassis.detailedChassis.rrAxleDW.pRightDW.upper_o[3] PARAM */);
  threadData->lastEquationSolved = 1321;
}

/*
equation index: 1322
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.length = if sqrt(chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM * chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM) > 0.015 then sqrt(chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM * chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM) else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1322(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1322};
  real_array tmp510;
  real_array tmp511;
  modelica_real tmp512;
  modelica_boolean tmp513;
  real_array tmp514;
  real_array tmp515;
  modelica_real tmp516;
  modelica_boolean tmp517;
  modelica_real tmp518;
  real_array_create(&tmp510, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4260]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp511, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4260]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp512 = mul_real_scalar_product(tmp510, tmp511);
  if(!(tmp512 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM * chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM) was %g should be >= 0", tmp512);
    }
  }tmp513 = Greater(sqrt(tmp512),0.015);
  tmp517 = (modelica_boolean)tmp513;
  if(tmp517)
  {
    real_array_create(&tmp514, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4260]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    real_array_create(&tmp515, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4260]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    tmp516 = mul_real_scalar_product(tmp514, tmp515);
    if(!(tmp516 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM * chassis.detailedChassis.rrAxleDW.rightUCABody.r_CM) was %g should be >= 0", tmp516);
      }
    }
    tmp518 = sqrt(tmp516);
  }
  else
  {
    tmp518 = 0.0;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8913]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.length variable */) = tmp518;
  threadData->lastEquationSolved = 1322;
}

/*
equation index: 1323
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I_11 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1323(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1323};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4230]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3579]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 1323;
}

/*
equation index: 1324
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[1,1] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_11
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1324(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1324};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4221]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4230]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_11 PARAM */);
  threadData->lastEquationSolved = 1324;
}

/*
equation index: 1325
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I_21 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1325(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1325};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4231]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3582]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 1325;
}

/*
equation index: 1326
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[2,1] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1326(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1326};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4224]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4231]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 1326;
}

/*
equation index: 1327
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[1,2] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1327(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1327};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4222]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4231]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 1327;
}

/*
equation index: 1328
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I_22 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1328(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1328};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4232]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3583]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 1328;
}

/*
equation index: 1329
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[2,2] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_22
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1329(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1329};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4225]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4232]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_22 PARAM */);
  threadData->lastEquationSolved = 1329;
}

/*
equation index: 1330
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I_31 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1330(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1330};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4233]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3585]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 1330;
}

/*
equation index: 1331
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[3,1] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1331(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1331};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4227]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4233]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 1331;
}

/*
equation index: 1332
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[1,3] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1332(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1332};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4223]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4233]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 1332;
}

/*
equation index: 1333
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I_32 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1333(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1333};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4234]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3586]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 1333;
}

/*
equation index: 1334
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[3,2] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1334(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1334};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4228]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4234]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 1334;
}

/*
equation index: 1335
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[2,3] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1335(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1335};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4226]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4234]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 1335;
}

/*
equation index: 1336
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I_33 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1336(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1336};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4235]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3587]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.ucaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 1336;
}

/*
equation index: 1337
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.I[3,3] = chassis.detailedChassis.rrAxleDW.rightUCABody.I_33
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1337(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1337};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4229]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4235]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.I_33 PARAM */);
  threadData->lastEquationSolved = 1337;
}

/*
equation index: 1338
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[1] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.rCM[1] - chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1338(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1338};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3814]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3563]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.rCM[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3611]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[1] PARAM */);
  threadData->lastEquationSolved = 1338;
}

/*
equation index: 1339
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.r_shape[1] = chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[1] - 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1339(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1339};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8201]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.r_shape[1] variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3814]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[1] PARAM */) - 0.015;
  threadData->lastEquationSolved = 1339;
}

/*
equation index: 1340
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[2] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.rCM[2] - chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1340(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1340};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3815]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3564]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.rCM[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3612]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[2] PARAM */);
  threadData->lastEquationSolved = 1340;
}

/*
equation index: 1341
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[3] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.rCM[3] - chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1341(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1341};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3816]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3565]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.rCM[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3613]] /* chassis.detailedChassis.rrAxleDW.pRightDW.lower_o[3] PARAM */);
  threadData->lastEquationSolved = 1341;
}

/*
equation index: 1342
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.length = if sqrt(chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM * chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM) > 0.015 then sqrt(chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM * chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM) else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1342(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1342};
  real_array tmp519;
  real_array tmp520;
  modelica_real tmp521;
  modelica_boolean tmp522;
  real_array tmp523;
  real_array tmp524;
  modelica_real tmp525;
  modelica_boolean tmp526;
  modelica_real tmp527;
  real_array_create(&tmp519, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3814]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp520, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3814]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp521 = mul_real_scalar_product(tmp519, tmp520);
  if(!(tmp521 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM * chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM) was %g should be >= 0", tmp521);
    }
  }tmp522 = Greater(sqrt(tmp521),0.015);
  tmp526 = (modelica_boolean)tmp522;
  if(tmp526)
  {
    real_array_create(&tmp523, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3814]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    real_array_create(&tmp524, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3814]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    tmp525 = mul_real_scalar_product(tmp523, tmp524);
    if(!(tmp525 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM * chassis.detailedChassis.rrAxleDW.rightLCABody.r_CM) was %g should be >= 0", tmp525);
      }
    }
    tmp527 = sqrt(tmp525);
  }
  else
  {
    tmp527 = 0.0;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8155]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.length variable */) = tmp527;
  threadData->lastEquationSolved = 1342;
}

/*
equation index: 1343
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I_11 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1343(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1343};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3784]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3553]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 1343;
}

/*
equation index: 1344
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[1,1] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_11
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1344(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1344};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3775]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3784]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_11 PARAM */);
  threadData->lastEquationSolved = 1344;
}

/*
equation index: 1345
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I_21 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1345(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1345};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3785]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3556]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 1345;
}

/*
equation index: 1346
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[2,1] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1346(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1346};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3778]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3785]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 1346;
}

/*
equation index: 1347
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[1,2] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1347(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1347};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3776]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3785]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_21 PARAM */);
  threadData->lastEquationSolved = 1347;
}

/*
equation index: 1348
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I_22 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1348(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1348};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3786]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3557]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 1348;
}

/*
equation index: 1349
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[2,2] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_22
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1349(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1349};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3779]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3786]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_22 PARAM */);
  threadData->lastEquationSolved = 1349;
}

/*
equation index: 1350
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I_31 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1350(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1350};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3787]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3559]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 1350;
}

/*
equation index: 1351
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[3,1] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1351(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1351};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3781]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3787]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 1351;
}

/*
equation index: 1352
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[1,3] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1352(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1352};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3777]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3787]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_31 PARAM */);
  threadData->lastEquationSolved = 1352;
}

/*
equation index: 1353
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I_32 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1353(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1353};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3788]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3560]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 1353;
}

/*
equation index: 1354
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[3,2] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1354(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1354};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3782]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3788]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 1354;
}

/*
equation index: 1355
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[2,3] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1355(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1355};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3780]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3788]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_32 PARAM */);
  threadData->lastEquationSolved = 1355;
}

/*
equation index: 1356
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I_33 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1356(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1356};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3789]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3561]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.lcaMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 1356;
}

/*
equation index: 1357
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.I[3,3] = chassis.detailedChassis.rrAxleDW.rightLCABody.I_33
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1357(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1357};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3783]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3789]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.I_33 PARAM */);
  threadData->lastEquationSolved = 1357;
}

/*
equation index: 1358
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[1] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.rCM[1] - chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1358(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1358};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4309]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3602]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.rCM[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3626]] /* chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[1] PARAM */);
  threadData->lastEquationSolved = 1358;
}

/*
equation index: 1359
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.r_shape[1] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[1] - 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1359(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1359};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9022]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.r_shape[1] variable */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4309]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[1] PARAM */) - 0.015;
  threadData->lastEquationSolved = 1359;
}

/*
equation index: 1360
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[2] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.rCM[2] - chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1360(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1360};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4310]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3603]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.rCM[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3627]] /* chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[2] PARAM */);
  threadData->lastEquationSolved = 1360;
}

/*
equation index: 1361
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[3] = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.rCM[3] - chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1361(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1361};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4311]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3604]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.rCM[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3628]] /* chassis.detailedChassis.rrAxleDW.pRightDW.wheelCenter[3] PARAM */);
  threadData->lastEquationSolved = 1361;
}

/*
equation index: 1362
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.length = if sqrt(chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM * chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM) > 0.015 then sqrt(chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM * chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM) else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1362(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1362};
  real_array tmp528;
  real_array tmp529;
  modelica_real tmp530;
  modelica_boolean tmp531;
  real_array tmp532;
  real_array tmp533;
  modelica_real tmp534;
  modelica_boolean tmp535;
  modelica_real tmp536;
  real_array_create(&tmp528, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4309]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp529, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4309]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp530 = mul_real_scalar_product(tmp528, tmp529);
  if(!(tmp530 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM * chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM) was %g should be >= 0", tmp530);
    }
  }tmp531 = Greater(sqrt(tmp530),0.015);
  tmp535 = (modelica_boolean)tmp531;
  if(tmp535)
  {
    real_array_create(&tmp532, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4309]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    real_array_create(&tmp533, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4309]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    tmp534 = mul_real_scalar_product(tmp532, tmp533);
    if(!(tmp534 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM * chassis.detailedChassis.rrAxleDW.rightUnsprungBody.r_CM) was %g should be >= 0", tmp534);
      }
    }
    tmp536 = sqrt(tmp534);
  }
  else
  {
    tmp536 = 0.0;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8985]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.length variable */) = tmp536;
  threadData->lastEquationSolved = 1362;
}

/*
equation index: 1363
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_11 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[1,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1363(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1363};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4279]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_11 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3592]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[1,1] PARAM */);
  threadData->lastEquationSolved = 1363;
}

/*
equation index: 1364
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[1,1] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_11
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1364(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1364};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4270]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[1,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4279]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_11 PARAM */);
  threadData->lastEquationSolved = 1364;
}

/*
equation index: 1365
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_21 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[2,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1365(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1365};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4280]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_21 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3595]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[2,1] PARAM */);
  threadData->lastEquationSolved = 1365;
}

/*
equation index: 1366
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[2,1] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1366(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1366};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4273]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[2,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4280]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_21 PARAM */);
  threadData->lastEquationSolved = 1366;
}

/*
equation index: 1367
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[1,2] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_21
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1367(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1367};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4271]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[1,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4280]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_21 PARAM */);
  threadData->lastEquationSolved = 1367;
}

/*
equation index: 1368
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_22 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[2,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1368(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1368};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4281]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_22 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3596]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[2,2] PARAM */);
  threadData->lastEquationSolved = 1368;
}

/*
equation index: 1369
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[2,2] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_22
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1369(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1369};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4274]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[2,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4281]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_22 PARAM */);
  threadData->lastEquationSolved = 1369;
}

/*
equation index: 1370
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_31 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[3,1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1370(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1370};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4282]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_31 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3598]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[3,1] PARAM */);
  threadData->lastEquationSolved = 1370;
}

/*
equation index: 1371
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[3,1] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1371(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1371};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4276]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[3,1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4282]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_31 PARAM */);
  threadData->lastEquationSolved = 1371;
}

/*
equation index: 1372
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[1,3] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_31
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1372(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1372};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4272]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[1,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4282]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_31 PARAM */);
  threadData->lastEquationSolved = 1372;
}

/*
equation index: 1373
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_32 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[3,2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1373(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1373};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4283]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_32 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3599]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[3,2] PARAM */);
  threadData->lastEquationSolved = 1373;
}

/*
equation index: 1374
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[3,2] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1374(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1374};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4277]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[3,2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4283]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_32 PARAM */);
  threadData->lastEquationSolved = 1374;
}

/*
equation index: 1375
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[2,3] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_32
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1375(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1375};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4275]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[2,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4283]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_32 PARAM */);
  threadData->lastEquationSolved = 1375;
}

/*
equation index: 1376
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_33 = chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[3,3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1376(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1376};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4284]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_33 PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3600]] /* chassis.detailedChassis.rrAxleDW.pRightAxleMass.unsprungMass.inertia[3,3] PARAM */);
  threadData->lastEquationSolved = 1376;
}

/*
equation index: 1377
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[3,3] = chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_33
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1377(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1377};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4278]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I[3,3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4284]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.I_33 PARAM */);
  threadData->lastEquationSolved = 1377;
}

/*
equation index: 1378
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[3] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[3] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1378(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1378};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3730]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3699]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3708]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[3] PARAM */);
  threadData->lastEquationSolved = 1378;
}

/*
equation index: 1379
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1379(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1379};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3727]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3730]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[3] PARAM */);
  threadData->lastEquationSolved = 1379;
}

/*
equation index: 1380
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[2] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[2] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1380(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1380};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3729]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3698]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3707]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[2] PARAM */);
  threadData->lastEquationSolved = 1380;
}

/*
equation index: 1381
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1381(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1381};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3726]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3729]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[2] PARAM */);
  threadData->lastEquationSolved = 1381;
}

/*
equation index: 1382
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[1] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1382(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1382};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3728]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3697]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3706]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[1] PARAM */);
  threadData->lastEquationSolved = 1382;
}

/*
equation index: 1383
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.length = sqrt(chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1383(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1383};
  modelica_real tmp537;
  modelica_real tmp538;
  modelica_real tmp539;
  modelica_real tmp540;
  tmp537 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3728]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[1] PARAM */);
  tmp538 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3729]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[2] PARAM */);
  tmp539 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3730]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[3] PARAM */);
  tmp540 = (tmp537 * tmp537) + (tmp538 * tmp538) + (tmp539 * tmp539);
  if(!(tmp540 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[3] ^ 2.0) was %g should be >= 0", tmp540);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3724]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.length PARAM */) = sqrt(tmp540);
  threadData->lastEquationSolved = 1383;
}

/*
equation index: 1384
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.width = chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1384(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1384};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3734]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3724]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1384;
}

/*
equation index: 1385
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.height = chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1385(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1385};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3723]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3734]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.width PARAM */);
  threadData->lastEquationSolved = 1385;
}

/*
equation index: 1386
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1386(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1386};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3725]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3728]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toFirstPickup.r[1] PARAM */);
  threadData->lastEquationSolved = 1386;
}

/*
equation index: 1387
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[3] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1387(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1387};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3702]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3699]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[3] PARAM */);
  threadData->lastEquationSolved = 1387;
}

/*
equation index: 1388
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1388(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1388};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3743]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */);
  threadData->lastEquationSolved = 1388;
}

/*
equation index: 1389
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[2] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1389(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1389};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3701]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3698]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[2] PARAM */);
  threadData->lastEquationSolved = 1389;
}

/*
equation index: 1390
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1390(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1390};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3742]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */);
  threadData->lastEquationSolved = 1390;
}

/*
equation index: 1391
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1391(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1391};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3700]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3697]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1] PARAM */);
  threadData->lastEquationSolved = 1391;
}

/*
equation index: 1392
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.length = sqrt(chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1392(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1392};
  modelica_real tmp541;
  modelica_real tmp542;
  modelica_real tmp543;
  modelica_real tmp544;
  tmp541 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */);
  tmp542 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3745]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] PARAM */);
  tmp543 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3746]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] PARAM */);
  tmp544 = (tmp541 * tmp541) + (tmp542 * tmp542) + (tmp543 * tmp543);
  if(!(tmp544 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[3] ^ 2.0) was %g should be >= 0", tmp544);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3740]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.length PARAM */) = sqrt(tmp544);
  threadData->lastEquationSolved = 1392;
}

/*
equation index: 1393
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.width = chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1393(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1393};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3750]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3740]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1393;
}

/*
equation index: 1394
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.height = chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1394(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1394};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3739]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3750]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.width PARAM */);
  threadData->lastEquationSolved = 1394;
}

/*
equation index: 1395
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1395(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1395};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3741]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3744]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toSecondPickup.r[1] PARAM */);
  threadData->lastEquationSolved = 1395;
}

/*
equation index: 1396
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[3] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1396(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1396};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3705]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3702]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[3] PARAM */);
  threadData->lastEquationSolved = 1396;
}

/*
equation index: 1397
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.lengthDirection[3] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1397(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1397};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3759]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */);
  threadData->lastEquationSolved = 1397;
}

/*
equation index: 1398
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[2] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1398(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1398};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3704]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3701]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[2] PARAM */);
  threadData->lastEquationSolved = 1398;
}

/*
equation index: 1399
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.lengthDirection[2] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1399(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1399};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3758]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */);
  threadData->lastEquationSolved = 1399;
}

/*
equation index: 1400
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] = chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[1] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1400(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1400};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3703]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3700]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1] PARAM */);
  threadData->lastEquationSolved = 1400;
}

/*
equation index: 1401
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.length = sqrt(chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1401(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1401};
  modelica_real tmp545;
  modelica_real tmp546;
  modelica_real tmp547;
  modelica_real tmp548;
  tmp545 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */);
  tmp546 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3761]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] PARAM */);
  tmp547 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3762]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] PARAM */);
  tmp548 = (tmp545 * tmp545) + (tmp546 * tmp546) + (tmp547 * tmp547);
  if(!(tmp548 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[2] ^ 2.0 + chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[3] ^ 2.0) was %g should be >= 0", tmp548);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3756]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.length PARAM */) = sqrt(tmp548);
  threadData->lastEquationSolved = 1401;
}

/*
equation index: 1402
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.width = chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1402(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1402};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3766]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3756]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1402;
}

/*
equation index: 1403
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.height = chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1403(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1403};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3755]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3766]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.width PARAM */);
  threadData->lastEquationSolved = 1403;
}

/*
equation index: 1404
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.lengthDirection[1] = chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1404(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1404};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3757]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3760]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.toThirdPickup.r[1] PARAM */);
  threadData->lastEquationSolved = 1404;
}

/*
equation index: 1405
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] = chassis.detailedChassis.rrAxleDW.leftPushrod.n1_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1405(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1405};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2736]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.n1_a[3] PARAM */);
  threadData->lastEquationSolved = 1405;
}

/*
equation index: 1406
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1406(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1406};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6577]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1406;
}

/*
equation index: 1407
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] = chassis.detailedChassis.rrAxleDW.leftPushrod.n1_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1407(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1407};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2735]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.n1_a[2] PARAM */);
  threadData->lastEquationSolved = 1407;
}

/*
equation index: 1408
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1408(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1408};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6576]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1408;
}

/*
equation index: 1409
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] = chassis.detailedChassis.rrAxleDW.leftPushrod.n1_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1409(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1409};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2734]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.n1_a[1] PARAM */);
  threadData->lastEquationSolved = 1409;
}

/*
equation index: 1410
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia = smooth(0, if noEvent(sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) / sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) / sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) / sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1410(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1410};
  modelica_real tmp549;
  modelica_real tmp550;
  modelica_real tmp551;
  modelica_real tmp552;
  modelica_boolean tmp553;
  real_array tmp554;
  modelica_real tmp555;
  modelica_real tmp556;
  modelica_real tmp557;
  modelica_real tmp558;
  modelica_real tmp559;
  modelica_real tmp560;
  modelica_real tmp561;
  modelica_real tmp562;
  modelica_real tmp563;
  modelica_real tmp564;
  modelica_real tmp565;
  modelica_real tmp566;
  real_array tmp567;
  modelica_boolean tmp568;
  real_array tmp569;
  real_array tmp570;
  tmp549 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)));
  tmp550 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)));
  tmp551 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)));
  tmp552 = (tmp549 * tmp549) + (tmp550 * tmp550) + (tmp551 * tmp551);
  if(!(tmp552 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp552);
    }
  }tmp553 = GreaterEq(sqrt(tmp552),2.220446049250313e-14);
  tmp568 = (modelica_boolean)tmp553;
  if(tmp568)
  {
    tmp555 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)));
    tmp556 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)));
    tmp557 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)));
    tmp558 = (tmp555 * tmp555) + (tmp556 * tmp556) + (tmp557 * tmp557);
    if(!(tmp558 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp558);
      }
    }tmp559 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)));
    tmp560 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)));
    tmp561 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)));
    tmp562 = (tmp559 * tmp559) + (tmp560 * tmp560) + (tmp561 * tmp561);
    if(!(tmp562 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp562);
      }
    }tmp563 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)));
    tmp564 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)));
    tmp565 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)));
    tmp566 = (tmp563 * tmp563) + (tmp564 * tmp564) + (tmp565 * tmp565);
    if(!(tmp566 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp566);
      }
    }array_alloc_scalar_real_array(&tmp554, 3, (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */))),sqrt(tmp558),"sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */))),sqrt(tmp562),"sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */))),sqrt(tmp566),"sqrt((chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes));
    tmp569 = tmp554;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp567, 3, (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)))), (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2756]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)))), (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2755]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)))));
    tmp569 = tmp567;
  }
  real_array_create(&tmp570, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2745]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp569, tmp570);
  threadData->lastEquationSolved = 1410;
}

/*
equation index: 1411
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1411(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1411};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6607]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2746]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1411;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28827(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36307(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36310(DATA *data, threadData_t *threadData);


/*
equation index: 1415
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1415(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1415};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6608]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2747]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1415;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28829(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36308(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36311(DATA *data, threadData_t *threadData);


/*
equation index: 1419
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1419(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1419};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6606]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2745]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1419;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28825(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36306(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36309(DATA *data, threadData_t *threadData);


/*
equation index: 1423
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1423(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1423};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6575]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2754]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.n1_a[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1423;
}

/*
equation index: 1424
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e3_ia[1] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[3] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1424(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1424};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2748]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2747]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2746]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 1424;
}

/*
equation index: 1425
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e3_ia[2] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[1] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1425(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1425};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2749]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2753]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2745]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2747]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 1425;
}

/*
equation index: 1426
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e3_ia[3] = chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[2] - chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1426(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1426};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2750]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2751]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2746]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2752]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[2745]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 1426;
}

/*
equation index: 1427
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[3] = chassis.detailedChassis.rrAxleDW.rightPushrod.r_b[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.r_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1427(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1427};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3851]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3834]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.r_b[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3831]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.r_a[3] PARAM */);
  threadData->lastEquationSolved = 1427;
}

/*
equation index: 1428
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.r_b[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.r_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1428(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1428};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3850]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3833]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.r_b[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3830]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.r_a[2] PARAM */);
  threadData->lastEquationSolved = 1428;
}

/*
equation index: 1429
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] = chassis.detailedChassis.rrAxleDW.rightPushrod.r_b[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.r_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1429(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1429};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3849]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3832]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.r_b[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3829]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.r_a[1] PARAM */);
  threadData->lastEquationSolved = 1429;
}

/*
equation index: 1430
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia / sqrt(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1430(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1430};
  real_array tmp571;
  real_array tmp572;
  real_array tmp573;
  modelica_real tmp574;
  real_array tmp575;
  real_array_create(&tmp571, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3849]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp572, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3849]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp573, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3849]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp574 = mul_real_scalar_product(tmp572, tmp573);
  if(!(tmp574 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia) was %g should be >= 0", tmp574);
    }
  }real_array_create(&tmp575, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(division_alloc_real_array_scalar(threadData,tmp571,sqrt(tmp574),"sqrt(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rRod_ia)"), tmp575);
  threadData->lastEquationSolved = 1430;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28834(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36305(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28830(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36303(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28832(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36304(DATA *data, threadData_t *threadData);


/*
equation index: 1437
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] = chassis.detailedChassis.rrAxleDW.rightPushrod.n1_a[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1437(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1437};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3828]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.n1_a[3] PARAM */);
  threadData->lastEquationSolved = 1437;
}

/*
equation index: 1438
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1438(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1438};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8340]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1438;
}

/*
equation index: 1439
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.n1_a[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1439(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1439};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3827]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.n1_a[2] PARAM */);
  threadData->lastEquationSolved = 1439;
}

/*
equation index: 1440
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1440(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1440};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8339]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1440;
}

/*
equation index: 1441
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] = chassis.detailedChassis.rrAxleDW.rightPushrod.n1_a[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1441(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1441};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3826]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.n1_a[1] PARAM */);
  threadData->lastEquationSolved = 1441;
}

/*
equation index: 1442
type: ARRAY_CALL_ASSIGN

chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia = smooth(0, if noEvent(sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) >= 2.220446049250313e-14) then {(chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) / sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) / sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0), (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) / sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0)} else {4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]), 4.503599627370496e13 * (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1])})
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1442(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1442};
  modelica_real tmp576;
  modelica_real tmp577;
  modelica_real tmp578;
  modelica_real tmp579;
  modelica_boolean tmp580;
  real_array tmp581;
  modelica_real tmp582;
  modelica_real tmp583;
  modelica_real tmp584;
  modelica_real tmp585;
  modelica_real tmp586;
  modelica_real tmp587;
  modelica_real tmp588;
  modelica_real tmp589;
  modelica_real tmp590;
  modelica_real tmp591;
  modelica_real tmp592;
  modelica_real tmp593;
  real_array tmp594;
  modelica_boolean tmp595;
  real_array tmp596;
  real_array tmp597;
  tmp576 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)));
  tmp577 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)));
  tmp578 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)));
  tmp579 = (tmp576 * tmp576) + (tmp577 * tmp577) + (tmp578 * tmp578);
  if(!(tmp579 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp579);
    }
  }tmp580 = GreaterEq(sqrt(tmp579),2.220446049250313e-14);
  tmp595 = (modelica_boolean)tmp580;
  if(tmp595)
  {
    tmp582 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)));
    tmp583 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)));
    tmp584 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)));
    tmp585 = (tmp582 * tmp582) + (tmp583 * tmp583) + (tmp584 * tmp584);
    if(!(tmp585 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp585);
      }
    }tmp586 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)));
    tmp587 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)));
    tmp588 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)));
    tmp589 = (tmp586 * tmp586) + (tmp587 * tmp587) + (tmp588 * tmp588);
    if(!(tmp589 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp589);
      }
    }tmp590 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)));
    tmp591 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)));
    tmp592 = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)));
    tmp593 = (tmp590 * tmp590) + (tmp591 * tmp591) + (tmp592 * tmp592);
    if(!(tmp593 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0) was %g should be >= 0", tmp593);
      }
    }array_alloc_scalar_real_array(&tmp581, 3, (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */))),sqrt(tmp585),"sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */))),sqrt(tmp589),"sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes), (modelica_real)DIVISION_SIM(((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */))),sqrt(tmp593),"sqrt((chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3]) ^ 2.0 + (chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1]) ^ 2.0)",equationIndexes));
    tmp596 = tmp581;
  }
  else
  {
    array_alloc_scalar_real_array(&tmp594, 3, (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)))), (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3848]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)))), (modelica_real)(4.503599627370496e13) * (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3847]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)))));
    tmp596 = tmp594;
  }
  real_array_create(&tmp597, ((modelica_real*)&((&(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3837]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[1] PARAM */))[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_copy_data(tmp596, tmp597);
  threadData->lastEquationSolved = 1442;
}

/*
equation index: 1443
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1443(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1443};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8369]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3837]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1443;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28831(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36297(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36300(DATA *data, threadData_t *threadData);


/*
equation index: 1447
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r_shape[3] = (-chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[3]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1447(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1447};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8371]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r_shape[3] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3839]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[3] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1447;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28835(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36299(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36302(DATA *data, threadData_t *threadData);


/*
equation index: 1451
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r_shape[2] = (-chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[2]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1451(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1451};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8370]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.r_shape[2] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3838]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[2] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1451;
}
extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_28833(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36298(DATA *data, threadData_t *threadData);

extern void BobLib_Experiments_Standards_VehicleSim_eqFunction_36301(DATA *data, threadData_t *threadData);


/*
equation index: 1455
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.r_shape[1] = (-chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1]) * 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1455(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1455};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8338]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.r_shape[1] variable */) = ((-(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3846]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.n1_a[1] PARAM */))) * (0.015);
  threadData->lastEquationSolved = 1455;
}

/*
equation index: 1456
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_ia[1] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[3] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1456(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1456};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3840]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_ia[1] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3839]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[3] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3838]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[2] PARAM */)));
  threadData->lastEquationSolved = 1456;
}

/*
equation index: 1457
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_ia[2] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[1] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1457(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1457};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3841]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_ia[2] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3845]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[3] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3837]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[1] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3839]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[3] PARAM */)));
  threadData->lastEquationSolved = 1457;
}

/*
equation index: 1458
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_ia[3] = chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[2] - chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] * chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1458(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1458};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3842]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e3_ia[3] PARAM */) = ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3843]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[1] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3838]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[2] PARAM */)) - (((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3844]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.eRod_ia[2] PARAM */)) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3837]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.e2_ia[1] PARAM */)));
  threadData->lastEquationSolved = 1458;
}

/*
equation index: 1459
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.r[3] = chassis.contactPatchPosition_2[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1459(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1459};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5015]] /* chassis.fixedContactPatch_2.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[344]] /* chassis.contactPatchPosition_2[3] PARAM */);
  threadData->lastEquationSolved = 1459;
}

/*
equation index: 1460
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.lengthDirection[3] = chassis.fixedContactPatch_2.r[3] - chassis.fixedContactPatch_2.r_shape[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1460(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1460};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5012]] /* chassis.fixedContactPatch_2.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5015]] /* chassis.fixedContactPatch_2.r[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5018]] /* chassis.fixedContactPatch_2.r_shape[3] PARAM */);
  threadData->lastEquationSolved = 1460;
}

/*
equation index: 1461
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.r[2] = chassis.contactPatchPosition_2[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1461(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1461};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5014]] /* chassis.fixedContactPatch_2.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[343]] /* chassis.contactPatchPosition_2[2] PARAM */);
  threadData->lastEquationSolved = 1461;
}

/*
equation index: 1462
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.lengthDirection[2] = chassis.fixedContactPatch_2.r[2] - chassis.fixedContactPatch_2.r_shape[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1462(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1462};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5011]] /* chassis.fixedContactPatch_2.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5014]] /* chassis.fixedContactPatch_2.r[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5017]] /* chassis.fixedContactPatch_2.r_shape[2] PARAM */);
  threadData->lastEquationSolved = 1462;
}

/*
equation index: 1463
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.r[1] = chassis.contactPatchPosition_2[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1463(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1463};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5013]] /* chassis.fixedContactPatch_2.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[342]] /* chassis.contactPatchPosition_2[1] PARAM */);
  threadData->lastEquationSolved = 1463;
}

/*
equation index: 1464
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.length = sqrt((chassis.fixedContactPatch_2.r[1] - chassis.fixedContactPatch_2.r_shape[1]) ^ 2.0 + (chassis.fixedContactPatch_2.r[2] - chassis.fixedContactPatch_2.r_shape[2]) ^ 2.0 + (chassis.fixedContactPatch_2.r[3] - chassis.fixedContactPatch_2.r_shape[3]) ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1464(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1464};
  modelica_real tmp598;
  modelica_real tmp599;
  modelica_real tmp600;
  modelica_real tmp601;
  tmp598 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5013]] /* chassis.fixedContactPatch_2.r[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5016]] /* chassis.fixedContactPatch_2.r_shape[1] PARAM */);
  tmp599 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5014]] /* chassis.fixedContactPatch_2.r[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5017]] /* chassis.fixedContactPatch_2.r_shape[2] PARAM */);
  tmp600 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5015]] /* chassis.fixedContactPatch_2.r[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5018]] /* chassis.fixedContactPatch_2.r_shape[3] PARAM */);
  tmp601 = (tmp598 * tmp598) + (tmp599 * tmp599) + (tmp600 * tmp600);
  if(!(tmp601 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.fixedContactPatch_2.r[1] - chassis.fixedContactPatch_2.r_shape[1]) ^ 2.0 + (chassis.fixedContactPatch_2.r[2] - chassis.fixedContactPatch_2.r_shape[2]) ^ 2.0 + (chassis.fixedContactPatch_2.r[3] - chassis.fixedContactPatch_2.r_shape[3]) ^ 2.0) was %g should be >= 0", tmp601);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5009]] /* chassis.fixedContactPatch_2.length PARAM */) = sqrt(tmp601);
  threadData->lastEquationSolved = 1464;
}

/*
equation index: 1465
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.width = chassis.fixedContactPatch_2.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1465(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1465};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5019]] /* chassis.fixedContactPatch_2.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5009]] /* chassis.fixedContactPatch_2.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1465;
}

/*
equation index: 1466
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.height = chassis.fixedContactPatch_2.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1466(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1466};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5008]] /* chassis.fixedContactPatch_2.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5019]] /* chassis.fixedContactPatch_2.width PARAM */);
  threadData->lastEquationSolved = 1466;
}

/*
equation index: 1467
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_2.lengthDirection[1] = chassis.fixedContactPatch_2.r[1] - chassis.fixedContactPatch_2.r_shape[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1467(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1467};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5010]] /* chassis.fixedContactPatch_2.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5013]] /* chassis.fixedContactPatch_2.r[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5016]] /* chassis.fixedContactPatch_2.r_shape[1] PARAM */);
  threadData->lastEquationSolved = 1467;
}

/*
equation index: 1468
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.r[3] = chassis.contactPatchPosition_4[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1468(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1468};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5047]] /* chassis.fixedContactPatch_4.r[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[350]] /* chassis.contactPatchPosition_4[3] PARAM */);
  threadData->lastEquationSolved = 1468;
}

/*
equation index: 1469
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.lengthDirection[3] = chassis.fixedContactPatch_4.r[3] - chassis.fixedContactPatch_4.r_shape[3]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1469(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1469};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5044]] /* chassis.fixedContactPatch_4.lengthDirection[3] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5047]] /* chassis.fixedContactPatch_4.r[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5050]] /* chassis.fixedContactPatch_4.r_shape[3] PARAM */);
  threadData->lastEquationSolved = 1469;
}

/*
equation index: 1470
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.r[2] = chassis.contactPatchPosition_4[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1470(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1470};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5046]] /* chassis.fixedContactPatch_4.r[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[349]] /* chassis.contactPatchPosition_4[2] PARAM */);
  threadData->lastEquationSolved = 1470;
}

/*
equation index: 1471
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.lengthDirection[2] = chassis.fixedContactPatch_4.r[2] - chassis.fixedContactPatch_4.r_shape[2]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1471(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1471};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5043]] /* chassis.fixedContactPatch_4.lengthDirection[2] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5046]] /* chassis.fixedContactPatch_4.r[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5049]] /* chassis.fixedContactPatch_4.r_shape[2] PARAM */);
  threadData->lastEquationSolved = 1471;
}

/*
equation index: 1472
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.r[1] = chassis.contactPatchPosition_4[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1472(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1472};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5045]] /* chassis.fixedContactPatch_4.r[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[348]] /* chassis.contactPatchPosition_4[1] PARAM */);
  threadData->lastEquationSolved = 1472;
}

/*
equation index: 1473
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.length = sqrt((chassis.fixedContactPatch_4.r[1] - chassis.fixedContactPatch_4.r_shape[1]) ^ 2.0 + (chassis.fixedContactPatch_4.r[2] - chassis.fixedContactPatch_4.r_shape[2]) ^ 2.0 + (chassis.fixedContactPatch_4.r[3] - chassis.fixedContactPatch_4.r_shape[3]) ^ 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1473(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1473};
  modelica_real tmp602;
  modelica_real tmp603;
  modelica_real tmp604;
  modelica_real tmp605;
  tmp602 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5045]] /* chassis.fixedContactPatch_4.r[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5048]] /* chassis.fixedContactPatch_4.r_shape[1] PARAM */);
  tmp603 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5046]] /* chassis.fixedContactPatch_4.r[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5049]] /* chassis.fixedContactPatch_4.r_shape[2] PARAM */);
  tmp604 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5047]] /* chassis.fixedContactPatch_4.r[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5050]] /* chassis.fixedContactPatch_4.r_shape[3] PARAM */);
  tmp605 = (tmp602 * tmp602) + (tmp603 * tmp603) + (tmp604 * tmp604);
  if(!(tmp605 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt((chassis.fixedContactPatch_4.r[1] - chassis.fixedContactPatch_4.r_shape[1]) ^ 2.0 + (chassis.fixedContactPatch_4.r[2] - chassis.fixedContactPatch_4.r_shape[2]) ^ 2.0 + (chassis.fixedContactPatch_4.r[3] - chassis.fixedContactPatch_4.r_shape[3]) ^ 2.0) was %g should be >= 0", tmp605);
    }
  }
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5041]] /* chassis.fixedContactPatch_4.length PARAM */) = sqrt(tmp605);
  threadData->lastEquationSolved = 1473;
}

/*
equation index: 1474
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.width = chassis.fixedContactPatch_4.length / world.defaultWidthFraction
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1474(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1474};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5051]] /* chassis.fixedContactPatch_4.width PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5041]] /* chassis.fixedContactPatch_4.length PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6901]] /* world.defaultWidthFraction PARAM */),"world.defaultWidthFraction",equationIndexes);
  threadData->lastEquationSolved = 1474;
}

/*
equation index: 1475
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.height = chassis.fixedContactPatch_4.width
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1475(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1475};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5040]] /* chassis.fixedContactPatch_4.height PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5051]] /* chassis.fixedContactPatch_4.width PARAM */);
  threadData->lastEquationSolved = 1475;
}

/*
equation index: 1476
type: SIMPLE_ASSIGN
chassis.fixedContactPatch_4.lengthDirection[1] = chassis.fixedContactPatch_4.r[1] - chassis.fixedContactPatch_4.r_shape[1]
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1476(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1476};
  (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5042]] /* chassis.fixedContactPatch_4.lengthDirection[1] PARAM */) = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5045]] /* chassis.fixedContactPatch_4.r[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[5048]] /* chassis.fixedContactPatch_4.r_shape[1] PARAM */);
  threadData->lastEquationSolved = 1476;
}

/*
equation index: 1477
type: SIMPLE_ASSIGN
$PRE.linearityReferenceLateralGain = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1477(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1477};
  (data->simulationInfo->realVarsPre[10784] /* linearityReferenceLateralGain DISCRETE */) = 0.0;
  threadData->lastEquationSolved = 1477;
}

/*
equation index: 1478
type: SIMPLE_ASSIGN
linearityReferenceLateralGain = $PRE.linearityReferenceLateralGain
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1478(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1478};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10784]] /* linearityReferenceLateralGain DISCRETE */) = (data->simulationInfo->realVarsPre[10784] /* linearityReferenceLateralGain DISCRETE */);
  threadData->lastEquationSolved = 1478;
}

/*
equation index: 1479
type: SIMPLE_ASSIGN
$PRE.linearityLocalLateralGain = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1479(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1479};
  (data->simulationInfo->realVarsPre[10783] /* linearityLocalLateralGain DISCRETE */) = 0.0;
  threadData->lastEquationSolved = 1479;
}

/*
equation index: 1480
type: SIMPLE_ASSIGN
linearityLocalLateralGain = $PRE.linearityLocalLateralGain
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1480(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1480};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10783]] /* linearityLocalLateralGain DISCRETE */) = (data->simulationInfo->realVarsPre[10783] /* linearityLocalLateralGain DISCRETE */);
  threadData->lastEquationSolved = 1480;
}

/*
equation index: 1481
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi = $START.chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1481(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1481};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */) = ((modelica_real *)((data->modelData->realVarsData[16] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */).attribute .start.data))[0];
  threadData->lastEquationSolved = 1481;
}

/*
equation index: 1482
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] = chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] ^ 2.0 + (1.0 - chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] ^ 2.0) * cos(chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_1482(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,1482};
  modelica_real tmp606;
  modelica_real tmp607;
  tmp606 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */);
  tmp607 = (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[791]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.e[3] PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3170]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.R_rel.T[3,3] variable */) = (tmp606 * tmp606) + (1.0 - ((tmp607 * tmp607))) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.phi STATE(1,chassis.detailedChassis.frAxleDW.leftTire.wheelModel.hubAxis.w) */)));
  threadData->lastEquationSolved = 1482;
}
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_functionInitialEquations_2(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[494])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_989,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_990,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_991,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_992,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_993,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_994,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_995,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_996,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_997,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_998,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_999,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1000,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1001,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1002,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1003,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1004,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1005,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28793,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36362,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36365,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1009,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28791,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36361,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36364,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1013,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28795,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36363,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36366,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1017,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1018,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1019,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1020,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1021,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1022,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1023,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1024,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28798,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36359,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28800,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36360,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28796,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36358,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1031,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1032,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1033,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1034,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1035,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1036,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1037,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28797,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36352,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36355,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1041,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28799,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36353,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36356,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1045,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36354,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36357,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1049,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1050,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1051,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1052,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1053,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1054,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1055,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1056,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1057,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36351,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1059,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36350,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1061,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1062,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36349,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1064,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1065,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1066,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28996,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36344,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36347,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1070,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1071,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28994,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36345,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36348,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1075,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1076,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28998,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36343,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36346,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1080,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1081,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1082,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1083,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1084,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1085,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1086,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1087,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1088,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1089,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1090,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1091,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1092,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1093,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1094,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1095,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36325,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1097,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36326,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1099,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36327,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1101,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1102,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1103,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1104,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1105,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1106,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1107,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1108,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1109,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28990,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36332,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36335,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1113,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1114,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28988,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36333,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36336,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1118,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1119,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28992,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36331,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36334,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1123,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28991,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36338,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1126,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28989,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36339,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1129,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28993,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36337,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1132,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1133,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1134,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1135,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1136,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1137,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1138,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1139,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28767,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1141,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1142,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1143,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1144,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1145,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1146,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1147,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1148,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1149,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1150,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28766,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1152,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1153,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1154,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1155,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1156,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1157,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1158,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1159,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1160,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1161,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1162,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1163,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1164,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1165,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1166,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1167,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28765,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1169,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1170,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1171,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1172,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1173,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1174,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1175,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1176,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1177,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1178,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1179,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36340,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1181,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36341,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1183,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1184,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1185,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1186,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36342,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1188,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1189,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1190,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1191,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1192,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1193,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1194,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1195,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1196,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1197,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1198,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1199,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1200,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1201,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1202,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1203,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1204,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1205,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1206,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1207,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1208,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1209,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1210,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1211,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1212,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1213,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1214,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1215,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1216,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1217,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1218,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1219,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1220,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1221,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28890,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1223,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36329,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1225,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28891,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1227,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36328,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1229,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1230,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1231,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1232,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1233,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1234,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1235,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28889,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1237,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1238,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1239,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1240,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1241,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1242,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1243,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36330,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1245,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1246,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1247,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1248,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1249,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28813,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36322,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28815,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36323,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28817,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36324,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1256,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1257,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1258,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1259,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1260,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1261,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1262,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1263,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1264,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1265,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28822,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36321,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28818,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36319,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28820,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36320,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1272,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28821,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36317,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28819,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36316,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28823,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36318,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1279,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1280,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1281,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1282,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1283,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1284,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1285,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1286,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1287,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1288,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1289,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1290,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1291,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1292,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1293,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1294,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1295,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1296,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1297,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1298,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1299,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1300,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1301,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1302,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1303,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1304,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1305,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1306,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1307,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1308,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1309,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1310,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1311,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1312,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1313,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1314,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1315,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1316,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1317,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1318,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1319,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1320,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1321,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1322,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1323,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1324,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1325,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1326,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1327,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1328,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1329,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1330,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1331,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1332,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1333,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1334,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1335,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1336,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1337,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1338,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1339,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1340,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1341,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1342,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1343,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1344,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1345,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1346,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1347,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1348,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1349,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1350,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1351,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1352,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1353,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1354,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1355,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1356,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1357,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1358,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1359,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1360,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1361,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1362,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1363,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1364,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1365,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1366,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1367,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1368,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1369,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1370,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1371,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1372,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1373,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1374,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1375,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1376,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1377,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1378,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1379,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1380,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1381,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1382,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1383,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1384,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1385,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1386,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1387,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1388,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1389,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1390,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1391,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1392,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1393,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1394,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1395,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1396,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1397,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1398,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1399,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1400,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1402,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1403,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1404,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1405,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1406,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1407,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1408,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1409,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1410,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1411,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28827,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36307,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36310,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1415,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28829,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36308,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36311,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1419,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28825,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36306,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36309,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1423,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1424,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1425,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1426,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1427,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1428,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1429,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1430,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28834,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36305,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28830,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36303,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28832,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36304,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1437,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1438,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1439,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1440,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1441,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1442,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1443,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28831,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36297,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36300,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1447,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28835,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36299,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36302,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1451,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_28833,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36298,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_36301,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1455,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1456,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1457,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1458,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1459,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1460,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1461,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1462,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1463,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1464,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1465,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1466,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1467,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1468,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1469,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1470,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1471,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1472,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1473,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1474,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1475,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1476,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1477,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1478,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1479,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1480,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1481,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_1482
  };
  
  for (int id = 0; id < 494; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif