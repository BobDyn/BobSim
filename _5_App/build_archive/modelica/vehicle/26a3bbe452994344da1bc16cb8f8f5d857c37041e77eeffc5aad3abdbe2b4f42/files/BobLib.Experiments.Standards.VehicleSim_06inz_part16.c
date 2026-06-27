#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/*
equation index: 12322
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.box.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12322(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12322};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4079]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.rackAxis.box.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12322;
}

/*
equation index: 12323
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12323(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12323};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4040]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12323;
}

/*
equation index: 12324
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12324(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12324};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4030]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.fromLeft.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12324;
}

/*
equation index: 12325
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.toRight.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12325(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12325};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4113]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.toRight.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12325;
}

/*
equation index: 12326
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.toRight.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12326(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12326};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4106]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.toRight.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12326;
}

/*
equation index: 12327
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.length = 0.3183098861837907 * chassis.detailedChassis.frAxleDW.rackAndPinion.pRack.cFactor
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12327(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12327};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4058]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.length variable */) = (0.3183098861837907) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1414]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.pRack.cFactor PARAM */));
  threadData->lastEquationSolved = 12327;
}

/*
equation index: 12328
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.width = 0.1989436788648692 * chassis.detailedChassis.frAxleDW.rackAndPinion.pRack.cFactor
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12328(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12328};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4071]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.width variable */) = (0.1989436788648692) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1414]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.pRack.cFactor PARAM */));
  threadData->lastEquationSolved = 12328;
}

/*
equation index: 12329
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.height = 0.1989436788648692 * chassis.detailedChassis.frAxleDW.rackAndPinion.pRack.cFactor
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12329(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12329};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4057]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.height variable */) = (0.1989436788648692) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1414]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.pRack.cFactor PARAM */));
  threadData->lastEquationSolved = 12329;
}

/*
equation index: 12330
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12330(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12330};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4050]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.pinionVisualizer.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12330;
}

/*
equation index: 12331
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.length = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12331(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12331};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4125]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.length variable */) = 0.02;
  threadData->lastEquationSolved = 12331;
}

/*
equation index: 12332
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.width = 0.022000000000000002
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12332(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12332};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4138]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.width variable */) = 0.022000000000000002;
  threadData->lastEquationSolved = 12332;
}

/*
equation index: 12333
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.height = 0.022000000000000002
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12333(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12333};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4124]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.height variable */) = 0.022000000000000002;
  threadData->lastEquationSolved = 12333;
}

/*
equation index: 12334
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12334(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12334};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4117]] /* chassis.detailedChassis.frAxleDW.rackAndPinion.travelVisualizer.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12334;
}

/*
equation index: 12335
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.cylinder.length = 0.08505446459299475
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12335(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12335};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3393]] /* chassis.detailedChassis.frAxleDW.leftUCABody.cylinder.length variable */) = 0.08505446459299475;
  threadData->lastEquationSolved = 12335;
}

/*
equation index: 12336
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12336(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12336};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3400]] /* chassis.detailedChassis.frAxleDW.leftUCABody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12336;
}

/*
equation index: 12337
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12337(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12337};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3392]] /* chassis.detailedChassis.frAxleDW.leftUCABody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12337;
}

/*
equation index: 12338
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12338(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12338};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3391]] /* chassis.detailedChassis.frAxleDW.leftUCABody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12338;
}

/*
equation index: 12339
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12339(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12339};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3438]] /* chassis.detailedChassis.frAxleDW.leftUCABody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12339;
}

/*
equation index: 12340
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12340(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12340};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3445]] /* chassis.detailedChassis.frAxleDW.leftUCABody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12340;
}

/*
equation index: 12341
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12341(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12341};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3437]] /* chassis.detailedChassis.frAxleDW.leftUCABody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12341;
}

/*
equation index: 12342
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUCABody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12342(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12342};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3436]] /* chassis.detailedChassis.frAxleDW.leftUCABody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12342;
}

/*
equation index: 12343
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.cylinder.length = 0.15798418545749857
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12343(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12343};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2633]] /* chassis.detailedChassis.frAxleDW.leftLCABody.cylinder.length variable */) = 0.15798418545749857;
  threadData->lastEquationSolved = 12343;
}

/*
equation index: 12344
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12344(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12344};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2640]] /* chassis.detailedChassis.frAxleDW.leftLCABody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12344;
}

/*
equation index: 12345
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12345(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12345};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2632]] /* chassis.detailedChassis.frAxleDW.leftLCABody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12345;
}

/*
equation index: 12346
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12346(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12346};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2631]] /* chassis.detailedChassis.frAxleDW.leftLCABody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12346;
}

/*
equation index: 12347
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12347(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12347};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2678]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12347;
}

/*
equation index: 12348
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12348(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12348};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2685]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12348;
}

/*
equation index: 12349
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12349(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12349};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2677]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12349;
}

/*
equation index: 12350
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftLCABody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12350(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12350};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2676]] /* chassis.detailedChassis.frAxleDW.leftLCABody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12350;
}

/*
equation index: 12351
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.cylinder.length = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12351(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12351};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3470]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.cylinder.length variable */) = 0.0;
  threadData->lastEquationSolved = 12351;
}

/*
equation index: 12352
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12352(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12352};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3477]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12352;
}

/*
equation index: 12353
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12353(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12353};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3469]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12353;
}

/*
equation index: 12354
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12354(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12354};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3468]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12354;
}

/*
equation index: 12355
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12355(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12355};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3506]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12355;
}

/*
equation index: 12356
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12356(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12356};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3513]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12356;
}

/*
equation index: 12357
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12357(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12357};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3505]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12357;
}

/*
equation index: 12358
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftUnsprungBody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12358(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12358};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3504]] /* chassis.detailedChassis.frAxleDW.leftUnsprungBody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12358;
}

/*
equation index: 12359
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12359(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12359};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5160]] /* chassis.detailedChassis.frAxleDW.rightUCABody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12359;
}

/*
equation index: 12360
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12360(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12360};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5155]] /* chassis.detailedChassis.frAxleDW.rightUCABody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12360;
}

/*
equation index: 12361
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12361(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12361};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5154]] /* chassis.detailedChassis.frAxleDW.rightUCABody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12361;
}

/*
equation index: 12362
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12362(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12362};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5198]] /* chassis.detailedChassis.frAxleDW.rightUCABody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12362;
}

/*
equation index: 12363
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12363(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12363};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5203]] /* chassis.detailedChassis.frAxleDW.rightUCABody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12363;
}

/*
equation index: 12364
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12364(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12364};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5197]] /* chassis.detailedChassis.frAxleDW.rightUCABody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12364;
}

/*
equation index: 12365
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUCABody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12365(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12365};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5196]] /* chassis.detailedChassis.frAxleDW.rightUCABody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12365;
}

/*
equation index: 12366
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12366(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12366};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4402]] /* chassis.detailedChassis.frAxleDW.rightLCABody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12366;
}

/*
equation index: 12367
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12367(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12367};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4397]] /* chassis.detailedChassis.frAxleDW.rightLCABody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12367;
}

/*
equation index: 12368
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12368(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12368};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4396]] /* chassis.detailedChassis.frAxleDW.rightLCABody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12368;
}

/*
equation index: 12369
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12369(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12369};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4440]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12369;
}

/*
equation index: 12370
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12370(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12370};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4445]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12370;
}

/*
equation index: 12371
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12371(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12371};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4439]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12371;
}

/*
equation index: 12372
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightLCABody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12372(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12372};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4438]] /* chassis.detailedChassis.frAxleDW.rightLCABody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12372;
}

/*
equation index: 12373
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12373(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12373};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5232]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12373;
}

/*
equation index: 12374
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12374(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12374};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5227]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12374;
}

/*
equation index: 12375
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12375(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12375};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5226]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12375;
}

/*
equation index: 12376
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12376(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12376};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5261]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12376;
}

/*
equation index: 12377
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12377(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12377};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5266]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12377;
}

/*
equation index: 12378
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12378(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12378};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5260]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12378;
}

/*
equation index: 12379
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12379(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12379};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5259]] /* chassis.detailedChassis.frAxleDW.rightUnsprungBody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12379;
}

/*
equation index: 12380
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.cylinder.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12380(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12380};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2402]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.cylinder.length variable */) = 0.03;
  threadData->lastEquationSolved = 12380;
}

/*
equation index: 12381
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.cylinder.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12381(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12381};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2409]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.cylinder.width variable */) = 0.03;
  threadData->lastEquationSolved = 12381;
}

/*
equation index: 12382
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.cylinder.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12382(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12382};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2401]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.cylinder.height variable */) = 0.03;
  threadData->lastEquationSolved = 12382;
}

/*
equation index: 12383
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12383(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12383};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2400]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.revolute.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12383;
}

/*
equation index: 12384
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.length = Modelica.Math.Vectors.norm({0.027651137991999995, 0.09765641835200001, 0.004604186625999984}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12384(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12384};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2424]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT34, 2.0);
  threadData->lastEquationSolved = 12384;
}

/*
equation index: 12385
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12385(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12385};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2437]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.width variable */) = 0.015;
  threadData->lastEquationSolved = 12385;
}

/*
equation index: 12386
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12386(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12386};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2423]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.height variable */) = 0.015;
  threadData->lastEquationSolved = 12386;
}

/*
equation index: 12387
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12387(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12387};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2416]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12387;
}

/*
equation index: 12388
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_2.length = Modelica.Math.Vectors.norm({0.003465897055999999, -0.002875737454000049, 0.036645724016000025}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12388(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12388};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2449]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_2.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT35, 2.0);
  threadData->lastEquationSolved = 12388;
}

/*
equation index: 12389
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_2.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12389(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12389};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2459]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_2.width variable */) = 0.015;
  threadData->lastEquationSolved = 12389;
}

/*
equation index: 12390
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_2.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12390(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12390};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2448]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_2.height variable */) = 0.015;
  threadData->lastEquationSolved = 12390;
}

/*
equation index: 12391
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12391(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12391};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2441]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12391;
}

/*
equation index: 12392
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_3.length = Modelica.Math.Vectors.norm({-0.017982744577999997, -0.048393882129999954, -0.039062922128}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12392(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12392};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2471]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_3.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT36, 2.0);
  threadData->lastEquationSolved = 12392;
}

/*
equation index: 12393
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_3.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12393(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12393};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2481]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_3.width variable */) = 0.015;
  threadData->lastEquationSolved = 12393;
}

/*
equation index: 12394
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_3.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12394(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12394};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2470]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_3.height variable */) = 0.015;
  threadData->lastEquationSolved = 12394;
}

/*
equation index: 12395
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_3.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12395(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12395};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2463]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_3.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12395;
}

/*
equation index: 12396
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.length = Modelica.Math.Vectors.norm({-0.013134290469999997, -0.046386798768000004, -0.00218698851400001}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12396(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12396};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2493]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT37, 2.0);
  threadData->lastEquationSolved = 12396;
}

/*
equation index: 12397
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12397(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12397};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2506]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.width variable */) = 0.015;
  threadData->lastEquationSolved = 12397;
}

/*
equation index: 12398
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12398(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12398};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2492]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.height variable */) = 0.015;
  threadData->lastEquationSolved = 12398;
}

/*
equation index: 12399
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12399(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12399};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2485]] /* chassis.detailedChassis.frAxleDW.leftBellcrank.side_4.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12399;
}

/*
equation index: 12400
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.cylinder.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12400(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12400};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4167]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.cylinder.length variable */) = 0.03;
  threadData->lastEquationSolved = 12400;
}

/*
equation index: 12401
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.cylinder.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12401(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12401};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4174]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.cylinder.width variable */) = 0.03;
  threadData->lastEquationSolved = 12401;
}

/*
equation index: 12402
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.cylinder.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12402(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12402};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4166]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.cylinder.height variable */) = 0.03;
  threadData->lastEquationSolved = 12402;
}

/*
equation index: 12403
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12403(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12403};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4165]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.revolute.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12403;
}

/*
equation index: 12404
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.length = Modelica.Math.Vectors.norm({chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[1] - chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[1], chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[2] - chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[2], chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[3] - chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12404(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12404};
  real_array tmp851;
  array_alloc_scalar_real_array(&tmp851, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1448]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1457]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1449]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1458]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1450]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1459]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[3] PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4189]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, tmp851, 2.0);
  threadData->lastEquationSolved = 12404;
}

/*
equation index: 12405
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12405(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12405};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4202]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.width variable */) = 0.015;
  threadData->lastEquationSolved = 12405;
}

/*
equation index: 12406
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12406(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12406};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4188]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.height variable */) = 0.015;
  threadData->lastEquationSolved = 12406;
}

/*
equation index: 12407
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12407(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12407};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4181]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12407;
}

/*
equation index: 12408
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_2.length = Modelica.Math.Vectors.norm({chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[1] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[1], chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[2] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[2], chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[3] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12408(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12408};
  real_array tmp852;
  array_alloc_scalar_real_array(&tmp852, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1451]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1448]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1452]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1449]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1453]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1450]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_1[3] PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4214]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_2.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, tmp852, 2.0);
  threadData->lastEquationSolved = 12408;
}

/*
equation index: 12409
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_2.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12409(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12409};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4224]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_2.width variable */) = 0.015;
  threadData->lastEquationSolved = 12409;
}

/*
equation index: 12410
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_2.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12410(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12410};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4213]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_2.height variable */) = 0.015;
  threadData->lastEquationSolved = 12410;
}

/*
equation index: 12411
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12411(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12411};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4206]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12411;
}

/*
equation index: 12412
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_3.length = Modelica.Math.Vectors.norm({chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[1] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[1], chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[2] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[2], chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[3] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12412(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12412};
  real_array tmp853;
  array_alloc_scalar_real_array(&tmp853, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1454]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1451]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1455]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1452]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1456]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1453]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_2[3] PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4236]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_3.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, tmp853, 2.0);
  threadData->lastEquationSolved = 12412;
}

/*
equation index: 12413
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_3.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12413(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12413};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4246]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_3.width variable */) = 0.015;
  threadData->lastEquationSolved = 12413;
}

/*
equation index: 12414
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_3.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12414(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12414};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4235]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_3.height variable */) = 0.015;
  threadData->lastEquationSolved = 12414;
}

/*
equation index: 12415
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_3.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12415(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12415};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4228]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_3.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12415;
}

/*
equation index: 12416
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.length = Modelica.Math.Vectors.norm({chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[1] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[1], chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[2] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[2], chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[3] - chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12416(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12416};
  real_array tmp854;
  array_alloc_scalar_real_array(&tmp854, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1457]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1454]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1458]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1455]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1459]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pivot[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[1456]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.pickup_3[3] PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4258]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, tmp854, 2.0);
  threadData->lastEquationSolved = 12416;
}

/*
equation index: 12417
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12417(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12417};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4271]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.width variable */) = 0.015;
  threadData->lastEquationSolved = 12417;
}

/*
equation index: 12418
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12418(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12418};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4257]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.height variable */) = 0.015;
  threadData->lastEquationSolved = 12418;
}

/*
equation index: 12419
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12419(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12419};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4250]] /* chassis.detailedChassis.frAxleDW.rightBellcrank.side_4.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12419;
}

/*
equation index: 12420
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toLeftArmEnd.shape.length = 0.06985000218483962
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12420(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12420};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5849]] /* chassis.detailedChassis.frAxleDW.stabar.toLeftArmEnd.shape.length variable */) = 0.06985000218483962;
  threadData->lastEquationSolved = 12420;
}

/*
equation index: 12421
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toLeftArmEnd.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12421(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12421};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5859]] /* chassis.detailedChassis.frAxleDW.stabar.toLeftArmEnd.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12421;
}

/*
equation index: 12422
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toLeftArmEnd.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12422(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12422};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5848]] /* chassis.detailedChassis.frAxleDW.stabar.toLeftArmEnd.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12422;
}

/*
equation index: 12423
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toRightArmEnd.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12423(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12423};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5896]] /* chassis.detailedChassis.frAxleDW.stabar.toRightArmEnd.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12423;
}

/*
equation index: 12424
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toRightArmEnd.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12424(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12424};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5889]] /* chassis.detailedChassis.frAxleDW.stabar.toRightArmEnd.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12424;
}

/*
equation index: 12425
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.stabarAxis.cylinder.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12425(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12425};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5826]] /* chassis.detailedChassis.frAxleDW.stabar.stabarAxis.cylinder.length variable */) = 0.03;
  threadData->lastEquationSolved = 12425;
}

/*
equation index: 12426
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.stabarAxis.cylinder.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12426(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12426};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5830]] /* chassis.detailedChassis.frAxleDW.stabar.stabarAxis.cylinder.width variable */) = 0.03;
  threadData->lastEquationSolved = 12426;
}

/*
equation index: 12427
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.stabarAxis.cylinder.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12427(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12427};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5825]] /* chassis.detailedChassis.frAxleDW.stabar.stabarAxis.cylinder.height variable */) = 0.03;
  threadData->lastEquationSolved = 12427;
}

/*
equation index: 12428
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.stabarAxis.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12428(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12428};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5824]] /* chassis.detailedChassis.frAxleDW.stabar.stabarAxis.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12428;
}

/*
equation index: 12429
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toLeftBarEnd.shape.length = 0.2667
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12429(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12429};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5872]] /* chassis.detailedChassis.frAxleDW.stabar.toLeftBarEnd.shape.length variable */) = 0.2667;
  threadData->lastEquationSolved = 12429;
}

/*
equation index: 12430
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toLeftBarEnd.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12430(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12430};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5879]] /* chassis.detailedChassis.frAxleDW.stabar.toLeftBarEnd.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12430;
}

/*
equation index: 12431
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toLeftBarEnd.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12431(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12431};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5871]] /* chassis.detailedChassis.frAxleDW.stabar.toLeftBarEnd.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12431;
}

/*
equation index: 12432
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.length = 0.2667
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12432(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12432};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5910]] /* chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.length variable */) = 0.2667;
  threadData->lastEquationSolved = 12432;
}

/*
equation index: 12433
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12433(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12433};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5920]] /* chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12433;
}

/*
equation index: 12434
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12434(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12434};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5909]] /* chassis.detailedChassis.frAxleDW.stabar.toRightBarEnd.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12434;
}

/*
equation index: 12435
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_rod.length = 0.2581380594740711
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12435(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12435};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4374]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_rod.length variable */) = 0.2581380594740711;
  threadData->lastEquationSolved = 12435;
}

/*
equation index: 12436
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_rod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12436(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12436};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4378]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_rod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12436;
}

/*
equation index: 12437
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_rod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12437(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12437};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4373]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_rod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12437;
}

/*
equation index: 12438
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_rod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12438(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12438};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4372]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_rod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12438;
}

/*
equation index: 12439
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_a.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12439(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12439};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4333]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_a.length variable */) = 0.03;
  threadData->lastEquationSolved = 12439;
}

/*
equation index: 12440
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_a.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12440(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12440};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4337]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_a.width variable */) = 0.03;
  threadData->lastEquationSolved = 12440;
}

/*
equation index: 12441
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_a.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12441(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12441};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4332]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_a.height variable */) = 0.03;
  threadData->lastEquationSolved = 12441;
}

/*
equation index: 12442
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_a.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12442(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12442};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4331]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_a.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12442;
}

/*
equation index: 12443
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12443(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12443};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4358]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12443;
}

/*
equation index: 12444
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12444(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12444};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4365]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12444;
}

/*
equation index: 12445
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12445(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12445};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4357]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12445;
}

/*
equation index: 12446
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightDroplink.shape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12446(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12446};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4356]] /* chassis.detailedChassis.frAxleDW.rightDroplink.shape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12446;
}

/*
equation index: 12447
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_rod.length = 0.2581380594740711
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12447(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12447};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2609]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_rod.length variable */) = 0.2581380594740711;
  threadData->lastEquationSolved = 12447;
}

/*
equation index: 12448
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_rod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12448(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12448};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2613]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_rod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12448;
}

/*
equation index: 12449
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_rod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12449(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12449};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2608]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_rod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12449;
}

/*
equation index: 12450
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_rod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12450(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12450};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2607]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_rod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12450;
}

/*
equation index: 12451
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_a.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12451(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12451};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2568]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_a.length variable */) = 0.03;
  threadData->lastEquationSolved = 12451;
}

/*
equation index: 12452
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_a.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12452(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12452};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2572]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_a.width variable */) = 0.03;
  threadData->lastEquationSolved = 12452;
}

/*
equation index: 12453
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_a.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12453(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12453};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2567]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_a.height variable */) = 0.03;
  threadData->lastEquationSolved = 12453;
}

/*
equation index: 12454
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_a.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12454(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12454};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2566]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_a.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12454;
}

/*
equation index: 12455
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12455(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12455};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2593]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12455;
}

/*
equation index: 12456
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12456(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12456};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2600]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12456;
}

/*
equation index: 12457
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12457(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12457};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2592]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12457;
}

/*
equation index: 12458
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftDroplink.shape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12458(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12458};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2591]] /* chassis.detailedChassis.frAxleDW.leftDroplink.shape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12458;
}

/*
equation index: 12459
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodShape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12459(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12459};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2779]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodShape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12459;
}

/*
equation index: 12460
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodShape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12460(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12460};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2772]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodShape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12460;
}

/*
equation index: 12461
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodShape.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12461(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12461};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2771]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.rodShape.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12461;
}

/*
equation index: 12462
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.sphericalShape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12462(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12462};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2788]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.sphericalShape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12462;
}

/*
equation index: 12463
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.sphericalShape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12463(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12463};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2798]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.sphericalShape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12463;
}

/*
equation index: 12464
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.sphericalShape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12464(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12464};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2787]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.sphericalShape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12464;
}

/*
equation index: 12465
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.sphericalShape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12465(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12465};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2786]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.sphericalShape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12465;
}

/*
equation index: 12466
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12466(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12466};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2820]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.length variable */) = 0.03;
  threadData->lastEquationSolved = 12466;
}

/*
equation index: 12467
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12467(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12467};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2824]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.width variable */) = 0.03;
  threadData->lastEquationSolved = 12467;
}

/*
equation index: 12468
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12468(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12468};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2819]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.height variable */) = 0.03;
  threadData->lastEquationSolved = 12468;
}

/*
equation index: 12469
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12469(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12469};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2818]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12469;
}

/*
equation index: 12470
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12470(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12470};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2845]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.length variable */) = 0.03;
  threadData->lastEquationSolved = 12470;
}

/*
equation index: 12471
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12471(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12471};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2855]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.width variable */) = 0.03;
  threadData->lastEquationSolved = 12471;
}

/*
equation index: 12472
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12472(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12472};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2844]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.height variable */) = 0.03;
  threadData->lastEquationSolved = 12472;
}

/*
equation index: 12473
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12473(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12473};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2843]] /* chassis.detailedChassis.frAxleDW.leftPushrod.rod.universalShape2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12473;
}

/*
equation index: 12474
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.rodShape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12474(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12474};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4539]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rodShape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12474;
}

/*
equation index: 12475
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.rodShape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12475(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12475};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4532]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rodShape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12475;
}

/*
equation index: 12476
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.rodShape.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12476(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12476};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4531]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.rodShape.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12476;
}

/*
equation index: 12477
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.sphericalShape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12477(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12477};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4548]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.sphericalShape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12477;
}

/*
equation index: 12478
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.sphericalShape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12478(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12478};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4558]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.sphericalShape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12478;
}

/*
equation index: 12479
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.sphericalShape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12479(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12479};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4547]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.sphericalShape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12479;
}

/*
equation index: 12480
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.sphericalShape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12480(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12480};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4546]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.sphericalShape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12480;
}

/*
equation index: 12481
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12481(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12481};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4580]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.length variable */) = 0.03;
  threadData->lastEquationSolved = 12481;
}

/*
equation index: 12482
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12482(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12482};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4584]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.width variable */) = 0.03;
  threadData->lastEquationSolved = 12482;
}

/*
equation index: 12483
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12483(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12483};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4579]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.height variable */) = 0.03;
  threadData->lastEquationSolved = 12483;
}

/*
equation index: 12484
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12484(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12484};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4578]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12484;
}

/*
equation index: 12485
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12485(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12485};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4605]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.length variable */) = 0.03;
  threadData->lastEquationSolved = 12485;
}

/*
equation index: 12486
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12486(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12486};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4615]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.width variable */) = 0.03;
  threadData->lastEquationSolved = 12486;
}

/*
equation index: 12487
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12487(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12487};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4604]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.height variable */) = 0.03;
  threadData->lastEquationSolved = 12487;
}

/*
equation index: 12488
type: SIMPLE_ASSIGN
chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12488(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12488};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4603]] /* chassis.detailedChassis.frAxleDW.rightPushrod.rod.universalShape2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12488;
}

/*
equation index: 12489
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12489(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12489};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6931]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.hubAxis.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12489;
}

/*
equation index: 12490
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.box.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12490(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12490};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6966]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.box.width variable */) = 0.02;
  threadData->lastEquationSolved = 12490;
}

/*
equation index: 12491
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.box.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12491(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12491};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6958]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.box.height variable */) = 0.02;
  threadData->lastEquationSolved = 12491;
}

/*
equation index: 12492
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.box.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12492(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12492};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6957]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.prismatic_z.box.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12492;
}

/*
equation index: 12493
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.pipe.width = 2.0 * (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.ri + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.h)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12493(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12493};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7012]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.pipe.width variable */) = (2.0) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3127]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.ri PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3120]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.h PARAM */));
  threadData->lastEquationSolved = 12493;
}

/*
equation index: 12494
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.pipe.height = 2.0 * (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.ri + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.h)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12494(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12494};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7005]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.pipe.height variable */) = (2.0) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3127]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.ri PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3120]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.h PARAM */));
  threadData->lastEquationSolved = 12494;
}

/*
equation index: 12495
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.pipe.extra = chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.rRim2 / (chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.ri + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.h)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12495(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12495};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7004]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.pipe.extra variable */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3125]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.rRim2 PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3127]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.ri PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3120]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.h PARAM */),"chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.ri + chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.h",equationIndexes);
  threadData->lastEquationSolved = 12495;
}

/*
equation index: 12496
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.transparency = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12496(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12496};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7025]] /* chassis.detailedChassis.rrAxleDW.leftTire.wheelModel.voluminousWheel.torus.transparency variable */) = 0.0;
  threadData->lastEquationSolved = 12496;
}

/*
equation index: 12497
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.forceAndTorque.forceArrow.headAtOrigin = true
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12497(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12497};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[34]] /* chassis.detailedChassis.rrAxleDW.leftTire.forceAndTorque.forceArrow.headAtOrigin DISCRETE */) = 1 /* true */;
  threadData->lastEquationSolved = 12497;
}

/*
equation index: 12498
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.forceAndTorque.forceArrow.twoHeadedArrow = false
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12498(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12498};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[35]] /* chassis.detailedChassis.rrAxleDW.leftTire.forceAndTorque.forceArrow.twoHeadedArrow DISCRETE */) = 0 /* false */;
  threadData->lastEquationSolved = 12498;
}

/*
equation index: 12499
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.forceAndTorque.torqueArrow.headAtOrigin = true
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12499(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12499};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* chassis.detailedChassis.rrAxleDW.leftTire.forceAndTorque.torqueArrow.headAtOrigin DISCRETE */) = 1 /* true */;
  threadData->lastEquationSolved = 12499;
}

/*
equation index: 12500
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTire.forceAndTorque.torqueArrow.twoHeadedArrow = true
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12500(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12500};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[37]] /* chassis.detailedChassis.rrAxleDW.leftTire.forceAndTorque.torqueArrow.twoHeadedArrow DISCRETE */) = 1 /* true */;
  threadData->lastEquationSolved = 12500;
}

/*
equation index: 12501
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12501(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12501};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8697]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.hubAxis.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12501;
}

/*
equation index: 12502
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.box.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12502(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12502};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8732]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.box.width variable */) = 0.02;
  threadData->lastEquationSolved = 12502;
}

/*
equation index: 12503
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.box.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12503(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12503};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8724]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.box.height variable */) = 0.02;
  threadData->lastEquationSolved = 12503;
}

/*
equation index: 12504
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.box.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12504(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12504};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8723]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.prismatic_z.box.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12504;
}

/*
equation index: 12505
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.pipe.width = 2.0 * (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.ri + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.h)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12505(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12505};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8778]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.pipe.width variable */) = (2.0) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4216]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.ri PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4209]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.h PARAM */));
  threadData->lastEquationSolved = 12505;
}

/*
equation index: 12506
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.pipe.height = 2.0 * (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.ri + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.h)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12506(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12506};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8771]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.pipe.height variable */) = (2.0) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4216]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.ri PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4209]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.h PARAM */));
  threadData->lastEquationSolved = 12506;
}

/*
equation index: 12507
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.pipe.extra = chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.rRim2 / (chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.ri + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.h)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12507(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12507};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8770]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.pipe.extra variable */) = DIVISION_SIM((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4214]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.rRim2 PARAM */),(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4216]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.ri PARAM */) + (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4209]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.h PARAM */),"chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.ri + chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.h",equationIndexes);
  threadData->lastEquationSolved = 12507;
}

/*
equation index: 12508
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.transparency = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12508(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12508};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8791]] /* chassis.detailedChassis.rrAxleDW.rightTire.wheelModel.voluminousWheel.torus.transparency variable */) = 0.0;
  threadData->lastEquationSolved = 12508;
}

/*
equation index: 12509
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.forceAndTorque.forceArrow.headAtOrigin = true
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12509(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12509};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[38]] /* chassis.detailedChassis.rrAxleDW.rightTire.forceAndTorque.forceArrow.headAtOrigin DISCRETE */) = 1 /* true */;
  threadData->lastEquationSolved = 12509;
}

/*
equation index: 12510
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.forceAndTorque.forceArrow.twoHeadedArrow = false
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12510(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12510};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* chassis.detailedChassis.rrAxleDW.rightTire.forceAndTorque.forceArrow.twoHeadedArrow DISCRETE */) = 0 /* false */;
  threadData->lastEquationSolved = 12510;
}

/*
equation index: 12511
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.forceAndTorque.torqueArrow.headAtOrigin = true
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12511(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12511};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[40]] /* chassis.detailedChassis.rrAxleDW.rightTire.forceAndTorque.torqueArrow.headAtOrigin DISCRETE */) = 1 /* true */;
  threadData->lastEquationSolved = 12511;
}

/*
equation index: 12512
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTire.forceAndTorque.torqueArrow.twoHeadedArrow = true
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12512(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12512};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[41]] /* chassis.detailedChassis.rrAxleDW.rightTire.forceAndTorque.torqueArrow.twoHeadedArrow DISCRETE */) = 1 /* true */;
  threadData->lastEquationSolved = 12512;
}

/*
equation index: 12513
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.length = 0.02 + Modelica.Math.Vectors.norm({0.22024339999999998, 0.013385800000000003, 0.004800599999999988}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12513(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12513};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7617]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.length variable */) = 0.02 + omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT31, 2.0);
  threadData->lastEquationSolved = 12513;
}

/*
equation index: 12514
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12514(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12514};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7624]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12514;
}

/*
equation index: 12515
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12515(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12515};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7616]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12515;
}

/*
equation index: 12516
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12516(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12516};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7615]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12516;
}

/*
equation index: 12517
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12517(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12517};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7712]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12517;
}

/*
equation index: 12518
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12518(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12518};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7705]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12518;
}

/*
equation index: 12519
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12519(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12519};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7704]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12519;
}

/*
equation index: 12520
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12520(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12520};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7721]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12520;
}

/*
equation index: 12521
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12521(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12521};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7728]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12521;
}

/*
equation index: 12522
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12522(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12522};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7720]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12522;
}

/*
equation index: 12523
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12523(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12523};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7719]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12523;
}

/*
equation index: 12524
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12524(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12524};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7736]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12524;
}

/*
equation index: 12525
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12525(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12525};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7749]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12525;
}

/*
equation index: 12526
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod2.shape.length = 0.2921464835470554
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12526(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12526};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7771]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperWishboneUpright.rod2.shape.length variable */) = 0.2921464835470554;
  threadData->lastEquationSolved = 12526;
}

/*
equation index: 12527
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.length = 0.02 + Modelica.Math.Vectors.norm({0.1855977999999998, -5.08000000000175e-5, -3.555999999999976e-4}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12527(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12527};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7373]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.length variable */) = 0.02 + omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT33, 2.0);
  threadData->lastEquationSolved = 12527;
}

/*
equation index: 12528
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12528(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12528};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7383]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12528;
}

/*
equation index: 12529
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12529(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12529};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7372]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12529;
}

/*
equation index: 12530
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12530(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12530};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7371]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerJoint_i.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12530;
}

/*
equation index: 12531
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.cylinder.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12531(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12531};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7428]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.cylinder.length variable */) = 0.03;
  threadData->lastEquationSolved = 12531;
}

/*
equation index: 12532
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.cylinder.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12532(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12532};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7435]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.cylinder.width variable */) = 0.03;
  threadData->lastEquationSolved = 12532;
}

/*
equation index: 12533
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.cylinder.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12533(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12533};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7427]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.cylinder.height variable */) = 0.03;
  threadData->lastEquationSolved = 12533;
}

/*
equation index: 12534
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12534(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12534};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7426]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.steeringAxis.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12534;
}

/*
equation index: 12535
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeRod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12535(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12535};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7500]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeRod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12535;
}

/*
equation index: 12536
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeRod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12536(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12536};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7487]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeRod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12536;
}

/*
equation index: 12537
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeRod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12537(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12537};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7480]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeRod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12537;
}

/*
equation index: 12538
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftRod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12538(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12538};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7472]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftRod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12538;
}

/*
equation index: 12539
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftRod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12539(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12539};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7459]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftRod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12539;
}

/*
equation index: 12540
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftRod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12540(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12540};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7452]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftRod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12540;
}

/*
equation index: 12541
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeRod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12541(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12541};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7332]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeRod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12541;
}

/*
equation index: 12542
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeRod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12542(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12542};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7319]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeRod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12542;
}

/*
equation index: 12543
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeRod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12543(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12543};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7312]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeRod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12543;
}

/*
equation index: 12544
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftRod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12544(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12544};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7304]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftRod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12544;
}

/*
equation index: 12545
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftRod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12545(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12545};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7291]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftRod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12545;
}

/*
equation index: 12546
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftRod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12546(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12546};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7284]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftRod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12546;
}

/*
equation index: 12547
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12547(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12547};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9375]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12547;
}

/*
equation index: 12548
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12548(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12548};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9368]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12548;
}

/*
equation index: 12549
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12549(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12549};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9367]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.revolute.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12549;
}

/*
equation index: 12550
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12550(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12550};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9463]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12550;
}

/*
equation index: 12551
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12551(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12551};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9456]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12551;
}

/*
equation index: 12552
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12552(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12552};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9455]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.rodShape.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12552;
}

/*
equation index: 12553
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12553(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12553};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9472]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12553;
}

/*
equation index: 12554
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12554(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12554};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9479]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12554;
}

/*
equation index: 12555
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12555(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12555};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9471]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12555;
}

/*
equation index: 12556
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12556(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12556};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9470]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.sphericalShape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12556;
}

/*
equation index: 12557
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12557(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12557};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9487]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12557;
}

/*
equation index: 12558
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12558(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12558};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9500]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperWishboneUpright.rod1.universalShape2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12558;
}

/*
equation index: 12559
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12559(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12559};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9138]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12559;
}

/*
equation index: 12560
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12560(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12560};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9128]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12560;
}

/*
equation index: 12561
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12561(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12561};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9127]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerJoint_i.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12561;
}

/*
equation index: 12562
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12562(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12562};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9183]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.length variable */) = 0.03;
  threadData->lastEquationSolved = 12562;
}

/*
equation index: 12563
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12563(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12563};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9190]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.width variable */) = 0.03;
  threadData->lastEquationSolved = 12563;
}

/*
equation index: 12564
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12564(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12564};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9182]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.height variable */) = 0.03;
  threadData->lastEquationSolved = 12564;
}

/*
equation index: 12565
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12565(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12565};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9181]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.steeringAxis.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12565;
}

/*
equation index: 12566
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeRod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12566(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12566};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9255]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeRod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12566;
}

/*
equation index: 12567
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeRod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12567(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12567};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9242]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeRod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12567;
}

/*
equation index: 12568
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeRod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12568(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12568};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9235]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeRod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12568;
}

/*
equation index: 12569
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftRod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12569(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12569};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9227]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftRod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12569;
}

/*
equation index: 12570
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftRod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12570(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12570};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9214]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftRod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12570;
}

/*
equation index: 12571
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftRod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12571(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12571};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9207]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftRod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12571;
}

/*
equation index: 12572
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeRod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12572(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12572};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9088]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeRod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12572;
}

/*
equation index: 12573
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeRod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12573(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12573};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9075]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeRod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12573;
}

/*
equation index: 12574
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeRod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12574(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12574};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9068]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeRod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12574;
}

/*
equation index: 12575
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftRod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12575(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12575};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9060]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftRod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12575;
}

/*
equation index: 12576
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftRod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12576(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12576};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9047]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftRod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12576;
}

/*
equation index: 12577
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftRod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12577(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12577};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9040]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftRod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12577;
}

/*
equation index: 12578
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12578(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12578};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6776]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12578;
}

/*
equation index: 12579
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12579(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12579};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6769]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12579;
}

/*
equation index: 12580
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShape.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12580(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12580};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6768]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.rodShape.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12580;
}

/*
equation index: 12581
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12581(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12581};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6798]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12581;
}

/*
equation index: 12582
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12582(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12582};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6808]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12582;
}

/*
equation index: 12583
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12583(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12583};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6797]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12583;
}

/*
equation index: 12584
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12584(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12584};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6796]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12584;
}

/*
equation index: 12585
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12585(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12585};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6785]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.length variable */) = 0.03;
  threadData->lastEquationSolved = 12585;
}

/*
equation index: 12586
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12586(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12586};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6792]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.width variable */) = 0.03;
  threadData->lastEquationSolved = 12586;
}

/*
equation index: 12587
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12587(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12587};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6784]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.height variable */) = 0.03;
  threadData->lastEquationSolved = 12587;
}

/*
equation index: 12588
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12588(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12588};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6783]] /* chassis.detailedChassis.rrAxleDW.leftTieRod.rod.sphericalShape_a.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12588;
}

/*
equation index: 12589
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12589(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12589};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8542]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12589;
}

/*
equation index: 12590
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12590(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12590};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8532]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12590;
}

/*
equation index: 12591
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShape.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12591(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12591};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8531]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.rodShape.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12591;
}

/*
equation index: 12592
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12592(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12592};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8564]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12592;
}

/*
equation index: 12593
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12593(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12593};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8574]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12593;
}

/*
equation index: 12594
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12594(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12594};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8563]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12594;
}

/*
equation index: 12595
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12595(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12595};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8562]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12595;
}

/*
equation index: 12596
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12596(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12596};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8551]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.length variable */) = 0.03;
  threadData->lastEquationSolved = 12596;
}

/*
equation index: 12597
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12597(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12597};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8558]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.width variable */) = 0.03;
  threadData->lastEquationSolved = 12597;
}

/*
equation index: 12598
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12598(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12598};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8550]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.height variable */) = 0.03;
  threadData->lastEquationSolved = 12598;
}

/*
equation index: 12599
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12599(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12599};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8549]] /* chassis.detailedChassis.rrAxleDW.rightTieRod.rod.sphericalShape_a.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12599;
}

/*
equation index: 12600
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.box.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12600(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12600};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7836]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.rackAxis.box.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12600;
}

/*
equation index: 12601
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12601(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12601};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7797]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12601;
}

/*
equation index: 12602
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12602(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12602};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7787]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.fromLeft.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12602;
}

/*
equation index: 12603
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12603(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12603};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7870]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12603;
}

/*
equation index: 12604
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12604(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12604};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7863]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.toRight.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12604;
}

/*
equation index: 12605
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.length = 0.3183098861837907 * chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12605(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12605};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7815]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.length variable */) = (0.3183098861837907) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3663]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor PARAM */));
  threadData->lastEquationSolved = 12605;
}

/*
equation index: 12606
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.width = 0.1989436788648692 * chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12606(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12606};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7828]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.width variable */) = (0.1989436788648692) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3663]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor PARAM */));
  threadData->lastEquationSolved = 12606;
}

/*
equation index: 12607
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.height = 0.1989436788648692 * chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12607(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12607};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7814]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.height variable */) = (0.1989436788648692) * ((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3663]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pRack.cFactor PARAM */));
  threadData->lastEquationSolved = 12607;
}

/*
equation index: 12608
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12608(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12608};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7807]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.pinionVisualizer.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12608;
}

/*
equation index: 12609
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.length = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12609(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12609};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7882]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.length variable */) = 0.02;
  threadData->lastEquationSolved = 12609;
}

/*
equation index: 12610
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.width = 0.022000000000000002
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12610(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12610};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7895]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.width variable */) = 0.022000000000000002;
  threadData->lastEquationSolved = 12610;
}

/*
equation index: 12611
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.height = 0.022000000000000002
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12611(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12611};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7881]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.height variable */) = 0.022000000000000002;
  threadData->lastEquationSolved = 12611;
}

/*
equation index: 12612
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12612(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12612};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7874]] /* chassis.detailedChassis.rrAxleDW.rackAndPinion.travelVisualizer.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12612;
}

/*
equation index: 12613
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.length = 0.13237302841883952
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12613(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12613};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7147]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.length variable */) = 0.13237302841883952;
  threadData->lastEquationSolved = 12613;
}

/*
equation index: 12614
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12614(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12614};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7154]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12614;
}

/*
equation index: 12615
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12615(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12615};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7146]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12615;
}

/*
equation index: 12616
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12616(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12616};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7145]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12616;
}

/*
equation index: 12617
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12617(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12617};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7192]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12617;
}

/*
equation index: 12618
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12618(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12618};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7199]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12618;
}

/*
equation index: 12619
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12619(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12619};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7191]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12619;
}

/*
equation index: 12620
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12620(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12620};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7190]] /* chassis.detailedChassis.rrAxleDW.leftUCABody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12620;
}

/*
equation index: 12621
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.length = 0.16667867514257156
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12621(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12621};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6387]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.length variable */) = 0.16667867514257156;
  threadData->lastEquationSolved = 12621;
}

/*
equation index: 12622
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12622(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12622};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6394]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12622;
}

/*
equation index: 12623
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12623(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12623};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6386]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12623;
}

/*
equation index: 12624
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12624(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12624};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6385]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12624;
}

/*
equation index: 12625
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12625(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12625};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6432]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12625;
}

/*
equation index: 12626
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12626(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12626};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6439]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12626;
}

/*
equation index: 12627
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12627(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12627};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6431]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12627;
}

/*
equation index: 12628
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12628(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12628};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6430]] /* chassis.detailedChassis.rrAxleDW.leftLCABody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12628;
}

/*
equation index: 12629
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.length = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12629(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12629};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7224]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.length variable */) = 0.0;
  threadData->lastEquationSolved = 12629;
}

/*
equation index: 12630
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12630(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12630};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7231]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12630;
}

/*
equation index: 12631
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12631(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12631};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7223]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12631;
}

/*
equation index: 12632
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12632(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12632};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7222]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12632;
}

/*
equation index: 12633
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12633(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12633};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7260]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12633;
}

/*
equation index: 12634
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12634(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12634};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7267]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12634;
}

/*
equation index: 12635
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12635(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12635};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7259]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12635;
}

/*
equation index: 12636
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12636(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12636};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7258]] /* chassis.detailedChassis.rrAxleDW.leftUnsprungBody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12636;
}

/*
equation index: 12637
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12637(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12637};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8917]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12637;
}

/*
equation index: 12638
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12638(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12638};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8912]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12638;
}

/*
equation index: 12639
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12639(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12639};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8911]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12639;
}

/*
equation index: 12640
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12640(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12640};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8955]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12640;
}

/*
equation index: 12641
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12641(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12641};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8960]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12641;
}

/*
equation index: 12642
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12642(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12642};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8954]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12642;
}

/*
equation index: 12643
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12643(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12643};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8953]] /* chassis.detailedChassis.rrAxleDW.rightUCABody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12643;
}

/*
equation index: 12644
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12644(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12644};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8159]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12644;
}

/*
equation index: 12645
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12645(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12645};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8154]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12645;
}

/*
equation index: 12646
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12646(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12646};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8153]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12646;
}

/*
equation index: 12647
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12647(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12647};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8197]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12647;
}

/*
equation index: 12648
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12648(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12648};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8202]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12648;
}

/*
equation index: 12649
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12649(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12649};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8196]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12649;
}

/*
equation index: 12650
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12650(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12650};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8195]] /* chassis.detailedChassis.rrAxleDW.rightLCABody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12650;
}

/*
equation index: 12651
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12651(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12651};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8989]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.width variable */) = 0.02;
  threadData->lastEquationSolved = 12651;
}

/*
equation index: 12652
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12652(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12652};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8984]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.height variable */) = 0.02;
  threadData->lastEquationSolved = 12652;
}

/*
equation index: 12653
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12653(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12653};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8983]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12653;
}

/*
equation index: 12654
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12654(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12654};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9018]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12654;
}

/*
equation index: 12655
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12655(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12655};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9023]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12655;
}

/*
equation index: 12656
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12656(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12656};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9017]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12656;
}

/*
equation index: 12657
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12657(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12657};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9016]] /* chassis.detailedChassis.rrAxleDW.rightUnsprungBody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12657;
}

/*
equation index: 12658
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12658(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12658};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6156]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.length variable */) = 0.03;
  threadData->lastEquationSolved = 12658;
}

/*
equation index: 12659
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12659(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12659};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6163]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.width variable */) = 0.03;
  threadData->lastEquationSolved = 12659;
}

/*
equation index: 12660
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12660(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12660};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6155]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.height variable */) = 0.03;
  threadData->lastEquationSolved = 12660;
}

/*
equation index: 12661
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12661(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12661};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6154]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.revolute.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12661;
}

/*
equation index: 12662
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.length = Modelica.Math.Vectors.norm({-0.013807150000000101, 0.059671909999999995, -0.01675936}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12662(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12662};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6178]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT38, 2.0);
  threadData->lastEquationSolved = 12662;
}

/*
equation index: 12663
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12663(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12663};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6191]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.width variable */) = 0.015;
  threadData->lastEquationSolved = 12663;
}

/*
equation index: 12664
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12664(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12664};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6177]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.height variable */) = 0.015;
  threadData->lastEquationSolved = 12664;
}

/*
equation index: 12665
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12665(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12665};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6170]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12665;
}

/*
equation index: 12666
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.length = Modelica.Math.Vectors.norm({-0.025337289999999957, 0.009399680000000021, 0.056759840000000006}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12666(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12666};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6203]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT39, 2.0);
  threadData->lastEquationSolved = 12666;
}

/*
equation index: 12667
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12667(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12667};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6213]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.width variable */) = 0.015;
  threadData->lastEquationSolved = 12667;
}

/*
equation index: 12668
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12668(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12668};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6202]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.height variable */) = 0.015;
  threadData->lastEquationSolved = 12668;
}

/*
equation index: 12669
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12669(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12669};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6195]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12669;
}

/*
equation index: 12670
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.length = Modelica.Math.Vectors.norm({0.02454310999999998, -0.05079721000000004, -0.018531649999999997}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12670(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12670};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6225]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT40, 2.0);
  threadData->lastEquationSolved = 12670;
}

/*
equation index: 12671
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12671(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12671};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6235]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.width variable */) = 0.015;
  threadData->lastEquationSolved = 12671;
}

/*
equation index: 12672
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12672(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12672};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6224]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.height variable */) = 0.015;
  threadData->lastEquationSolved = 12672;
}

/*
equation index: 12673
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12673(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12673};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6217]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_3.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12673;
}

/*
equation index: 12674
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.length = Modelica.Math.Vectors.norm({0.014601330000000079, -0.01827437999999998, -0.021468830000000008}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12674(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12674};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6247]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, _OMC_LIT41, 2.0);
  threadData->lastEquationSolved = 12674;
}

/*
equation index: 12675
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12675(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12675};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6260]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.width variable */) = 0.015;
  threadData->lastEquationSolved = 12675;
}

/*
equation index: 12676
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12676(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12676};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6246]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.height variable */) = 0.015;
  threadData->lastEquationSolved = 12676;
}

/*
equation index: 12677
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12677(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12677};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6239]] /* chassis.detailedChassis.rrAxleDW.leftBellcrank.side_4.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12677;
}

/*
equation index: 12678
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12678(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12678};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7924]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.length variable */) = 0.03;
  threadData->lastEquationSolved = 12678;
}

/*
equation index: 12679
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12679(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12679};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7931]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.width variable */) = 0.03;
  threadData->lastEquationSolved = 12679;
}

/*
equation index: 12680
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12680(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12680};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7923]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.height variable */) = 0.03;
  threadData->lastEquationSolved = 12680;
}

/*
equation index: 12681
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12681(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12681};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7922]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.revolute.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12681;
}

/*
equation index: 12682
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.length = Modelica.Math.Vectors.norm({chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[1], chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[2] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[2], chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[3] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12682(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12682};
  real_array tmp855;
  array_alloc_scalar_real_array(&tmp855, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3697]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3706]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3698]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3707]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3699]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3708]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[3] PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7946]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, tmp855, 2.0);
  threadData->lastEquationSolved = 12682;
}

/*
equation index: 12683
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12683(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12683};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7959]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.width variable */) = 0.015;
  threadData->lastEquationSolved = 12683;
}

/*
equation index: 12684
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12684(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12684};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7945]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.height variable */) = 0.015;
  threadData->lastEquationSolved = 12684;
}

/*
equation index: 12685
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12685(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12685};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7938]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12685;
}

/*
equation index: 12686
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.length = Modelica.Math.Vectors.norm({chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1], chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[2] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[2], chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[3] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12686(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12686};
  real_array tmp856;
  array_alloc_scalar_real_array(&tmp856, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3700]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3697]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3701]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3698]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3702]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3699]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_1[3] PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7971]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, tmp856, 2.0);
  threadData->lastEquationSolved = 12686;
}

/*
equation index: 12687
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12687(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12687};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7981]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.width variable */) = 0.015;
  threadData->lastEquationSolved = 12687;
}

/*
equation index: 12688
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12688(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12688};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7970]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.height variable */) = 0.015;
  threadData->lastEquationSolved = 12688;
}

/*
equation index: 12689
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12689(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12689};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7963]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12689;
}

/*
equation index: 12690
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.length = Modelica.Math.Vectors.norm({chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[1] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1], chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[2] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[2], chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[3] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12690(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12690};
  real_array tmp857;
  array_alloc_scalar_real_array(&tmp857, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3703]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3700]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3704]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3701]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3705]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3702]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_2[3] PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7993]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, tmp857, 2.0);
  threadData->lastEquationSolved = 12690;
}

/*
equation index: 12691
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12691(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12691};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8003]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.width variable */) = 0.015;
  threadData->lastEquationSolved = 12691;
}

/*
equation index: 12692
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12692(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12692};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7992]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.height variable */) = 0.015;
  threadData->lastEquationSolved = 12692;
}

/*
equation index: 12693
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12693(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12693};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7985]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_3.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12693;
}

/*
equation index: 12694
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.length = Modelica.Math.Vectors.norm({chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[1] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[1], chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[2] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[2], chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[3] - chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[3]}, 2.0)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12694(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12694};
  real_array tmp858;
  array_alloc_scalar_real_array(&tmp858, 3, (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3706]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[1] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3703]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[1] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3707]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[2] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3704]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[2] PARAM */), (modelica_real)(data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3708]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pivot[3] PARAM */) - (data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[3705]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.pickup_3[3] PARAM */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8015]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.length variable */) = omc_Modelica_Math_Vectors_norm(threadData, tmp858, 2.0);
  threadData->lastEquationSolved = 12694;
}

/*
equation index: 12695
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.width = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12695(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12695};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8028]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.width variable */) = 0.015;
  threadData->lastEquationSolved = 12695;
}

/*
equation index: 12696
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.height = 0.015
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12696(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12696};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8014]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.height variable */) = 0.015;
  threadData->lastEquationSolved = 12696;
}

/*
equation index: 12697
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12697(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12697};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8007]] /* chassis.detailedChassis.rrAxleDW.rightBellcrank.side_4.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12697;
}

/*
equation index: 12698
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shape.length = 0.038099998370741246
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12698(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12698};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9606]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shape.length variable */) = 0.038099998370741246;
  threadData->lastEquationSolved = 12698;
}

/*
equation index: 12699
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12699(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12699};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9616]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12699;
}

/*
equation index: 12700
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12700(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12700};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9605]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftArmEnd.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12700;
}

/*
equation index: 12701
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12701(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12701};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9653]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12701;
}

/*
equation index: 12702
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12702(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12702};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9646]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightArmEnd.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12702;
}

/*
equation index: 12703
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12703(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12703};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9583]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.length variable */) = 0.03;
  threadData->lastEquationSolved = 12703;
}

/*
equation index: 12704
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12704(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12704};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9587]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.width variable */) = 0.03;
  threadData->lastEquationSolved = 12704;
}

/*
equation index: 12705
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12705(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12705};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9582]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.height variable */) = 0.03;
  threadData->lastEquationSolved = 12705;
}

/*
equation index: 12706
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12706(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12706};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9581]] /* chassis.detailedChassis.rrAxleDW.stabar.stabarAxis.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12706;
}

/*
equation index: 12707
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shape.length = 0.3032125
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12707(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12707};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9629]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shape.length variable */) = 0.3032125;
  threadData->lastEquationSolved = 12707;
}

/*
equation index: 12708
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12708(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12708};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9636]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12708;
}

/*
equation index: 12709
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12709(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12709};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9628]] /* chassis.detailedChassis.rrAxleDW.stabar.toLeftBarEnd.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12709;
}

/*
equation index: 12710
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shape.length = 0.3032125
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12710(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12710};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9667]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shape.length variable */) = 0.3032125;
  threadData->lastEquationSolved = 12710;
}

/*
equation index: 12711
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12711(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12711};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9677]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12711;
}

/*
equation index: 12712
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12712(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12712};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9666]] /* chassis.detailedChassis.rrAxleDW.stabar.toRightBarEnd.shape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12712;
}

/*
equation index: 12713
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.length = 0.2829876939111886
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12713(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12713};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8131]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.length variable */) = 0.2829876939111886;
  threadData->lastEquationSolved = 12713;
}

/*
equation index: 12714
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12714(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12714};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8135]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12714;
}

/*
equation index: 12715
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12715(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12715};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8130]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12715;
}

/*
equation index: 12716
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12716(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12716};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8129]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_rod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12716;
}

/*
equation index: 12717
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12717(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12717};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8090]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.length variable */) = 0.03;
  threadData->lastEquationSolved = 12717;
}

/*
equation index: 12718
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12718(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12718};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8094]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.width variable */) = 0.03;
  threadData->lastEquationSolved = 12718;
}

/*
equation index: 12719
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12719(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12719};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8089]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.height variable */) = 0.03;
  threadData->lastEquationSolved = 12719;
}

/*
equation index: 12720
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12720(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12720};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8088]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_a.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12720;
}

/*
equation index: 12721
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12721(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12721};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8115]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12721;
}

/*
equation index: 12722
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12722(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12722};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8122]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12722;
}

/*
equation index: 12723
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12723(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12723};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8114]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12723;
}

/*
equation index: 12724
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12724(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12724};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8113]] /* chassis.detailedChassis.rrAxleDW.rightDroplink.shape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12724;
}

/*
equation index: 12725
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.length = 0.2829876939111886
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12725(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12725};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6363]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.length variable */) = 0.2829876939111886;
  threadData->lastEquationSolved = 12725;
}

/*
equation index: 12726
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12726(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12726};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6367]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.width variable */) = 0.02;
  threadData->lastEquationSolved = 12726;
}

/*
equation index: 12727
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12727(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12727};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6362]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.height variable */) = 0.02;
  threadData->lastEquationSolved = 12727;
}

/*
equation index: 12728
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12728(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12728};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6361]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_rod.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12728;
}

/*
equation index: 12729
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12729(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12729};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6322]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.length variable */) = 0.03;
  threadData->lastEquationSolved = 12729;
}

/*
equation index: 12730
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12730(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12730};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6326]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.width variable */) = 0.03;
  threadData->lastEquationSolved = 12730;
}

/*
equation index: 12731
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12731(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12731};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6321]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.height variable */) = 0.03;
  threadData->lastEquationSolved = 12731;
}

/*
equation index: 12732
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12732(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12732};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6320]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_a.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12732;
}

/*
equation index: 12733
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12733(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12733};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6347]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12733;
}

/*
equation index: 12734
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12734(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12734};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6354]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12734;
}

/*
equation index: 12735
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12735(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12735};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6346]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12735;
}

/*
equation index: 12736
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12736(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12736};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6345]] /* chassis.detailedChassis.rrAxleDW.leftDroplink.shape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12736;
}

/*
equation index: 12737
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12737(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12737};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6533]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12737;
}

/*
equation index: 12738
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12738(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12738};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6526]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12738;
}

/*
equation index: 12739
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShape.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12739(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12739};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6525]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.rodShape.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12739;
}

/*
equation index: 12740
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12740(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12740};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6542]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12740;
}

/*
equation index: 12741
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12741(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12741};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6552]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12741;
}

/*
equation index: 12742
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12742(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12742};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6541]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12742;
}

/*
equation index: 12743
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12743(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12743};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6540]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.sphericalShape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12743;
}

/*
equation index: 12744
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12744(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12744};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6574]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.length variable */) = 0.03;
  threadData->lastEquationSolved = 12744;
}

/*
equation index: 12745
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12745(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12745};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6578]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.width variable */) = 0.03;
  threadData->lastEquationSolved = 12745;
}

/*
equation index: 12746
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12746(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12746};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6573]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.height variable */) = 0.03;
  threadData->lastEquationSolved = 12746;
}

/*
equation index: 12747
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12747(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12747};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6572]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12747;
}

/*
equation index: 12748
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12748(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12748};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6599]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.length variable */) = 0.03;
  threadData->lastEquationSolved = 12748;
}

/*
equation index: 12749
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12749(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12749};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6609]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.width variable */) = 0.03;
  threadData->lastEquationSolved = 12749;
}

/*
equation index: 12750
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12750(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12750};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6598]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.height variable */) = 0.03;
  threadData->lastEquationSolved = 12750;
}

/*
equation index: 12751
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12751(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12751};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6597]] /* chassis.detailedChassis.rrAxleDW.leftPushrod.rod.universalShape2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12751;
}

/*
equation index: 12752
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShape.width = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12752(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12752};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8296]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShape.width variable */) = 0.02;
  threadData->lastEquationSolved = 12752;
}

/*
equation index: 12753
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShape.height = 0.02
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12753(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12753};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8289]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShape.height variable */) = 0.02;
  threadData->lastEquationSolved = 12753;
}

/*
equation index: 12754
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShape.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12754(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12754};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8288]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.rodShape.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12754;
}

/*
equation index: 12755
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12755(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12755};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8305]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.length variable */) = 0.03;
  threadData->lastEquationSolved = 12755;
}

/*
equation index: 12756
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12756(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12756};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8315]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.width variable */) = 0.03;
  threadData->lastEquationSolved = 12756;
}

/*
equation index: 12757
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12757(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12757};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8304]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.height variable */) = 0.03;
  threadData->lastEquationSolved = 12757;
}

/*
equation index: 12758
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12758(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12758};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8303]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.sphericalShape_b.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12758;
}

/*
equation index: 12759
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12759(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12759};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8337]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.length variable */) = 0.03;
  threadData->lastEquationSolved = 12759;
}

/*
equation index: 12760
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12760(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12760};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8341]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.width variable */) = 0.03;
  threadData->lastEquationSolved = 12760;
}

/*
equation index: 12761
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12761(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12761};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8336]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.height variable */) = 0.03;
  threadData->lastEquationSolved = 12761;
}

/*
equation index: 12762
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12762(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12762};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8335]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape1.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12762;
}

/*
equation index: 12763
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12763(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12763};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8362]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.length variable */) = 0.03;
  threadData->lastEquationSolved = 12763;
}

/*
equation index: 12764
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12764(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12764};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8372]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.width variable */) = 0.03;
  threadData->lastEquationSolved = 12764;
}

/*
equation index: 12765
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12765(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12765};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8361]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.height variable */) = 0.03;
  threadData->lastEquationSolved = 12765;
}

/*
equation index: 12766
type: SIMPLE_ASSIGN
chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12766(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12766};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8360]] /* chassis.detailedChassis.rrAxleDW.rightPushrod.rod.universalShape2.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12766;
}

/*
equation index: 12767
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.cylinder.length = if sqrt(chassis.detailedChassis.spaceFrame.sprungBody.r_CM * chassis.detailedChassis.spaceFrame.sprungBody.r_CM) > 0.015 then sqrt(chassis.detailedChassis.spaceFrame.sprungBody.r_CM * chassis.detailedChassis.spaceFrame.sprungBody.r_CM) - (if chassis.detailedChassis.spaceFrame.sprungBody.cylinderDiameter > 0.033 then 0.015 else 0.0) else 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12767(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12767};
  real_array tmp859;
  real_array tmp860;
  modelica_real tmp861;
  modelica_boolean tmp862;
  real_array tmp863;
  real_array tmp864;
  modelica_real tmp865;
  modelica_boolean tmp866;
  modelica_boolean tmp867;
  modelica_real tmp868;
  real_array_create(&tmp859, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4966]] /* chassis.detailedChassis.spaceFrame.sprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  real_array_create(&tmp860, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4966]] /* chassis.detailedChassis.spaceFrame.sprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
  tmp861 = mul_real_scalar_product(tmp859, tmp860);
  if(!(tmp861 >= 0.0))
  {
    if (data->simulationInfo->noThrowAsserts) {
      FILE_INFO info = {"",0,0,0,0,0};
      infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      data->simulationInfo->needToReThrow = 1;
    } else {
      FILE_INFO info = {"",0,0,0,0,0};
      omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
      throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.spaceFrame.sprungBody.r_CM * chassis.detailedChassis.spaceFrame.sprungBody.r_CM) was %g should be >= 0", tmp861);
    }
  }tmp862 = Greater(sqrt(tmp861),0.015);
  tmp867 = (modelica_boolean)tmp862;
  if(tmp867)
  {
    real_array_create(&tmp863, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4966]] /* chassis.detailedChassis.spaceFrame.sprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    real_array_create(&tmp864, ((modelica_real*)&((&data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4966]] /* chassis.detailedChassis.spaceFrame.sprungBody.r_CM[1] PARAM */)[((modelica_integer) 1) - 1])), 1, (_index_t)3);
    tmp865 = mul_real_scalar_product(tmp863, tmp864);
    if(!(tmp865 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(chassis.detailedChassis.spaceFrame.sprungBody.r_CM * chassis.detailedChassis.spaceFrame.sprungBody.r_CM) was %g should be >= 0", tmp865);
      }
    }tmp866 = Greater((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[4961]] /* chassis.detailedChassis.spaceFrame.sprungBody.cylinderDiameter PARAM */),0.033);
    tmp868 = sqrt(tmp865) - ((tmp866?0.015:0.0));
  }
  else
  {
    tmp868 = 0.0;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9898]] /* chassis.detailedChassis.spaceFrame.sprungBody.cylinder.length variable */) = tmp868;
  threadData->lastEquationSolved = 12767;
}

/*
equation index: 12768
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12768(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12768};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9897]] /* chassis.detailedChassis.spaceFrame.sprungBody.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12768;
}

/*
equation index: 12769
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.sphere.length = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12769(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12769};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9930]] /* chassis.detailedChassis.spaceFrame.sprungBody.sphere.length variable */) = 0.03;
  threadData->lastEquationSolved = 12769;
}

/*
equation index: 12770
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.sphere.width = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12770(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12770};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9935]] /* chassis.detailedChassis.spaceFrame.sprungBody.sphere.width variable */) = 0.03;
  threadData->lastEquationSolved = 12770;
}

/*
equation index: 12771
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.sphere.height = 0.03
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12771(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12771};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9929]] /* chassis.detailedChassis.spaceFrame.sprungBody.sphere.height variable */) = 0.03;
  threadData->lastEquationSolved = 12771;
}

/*
equation index: 12772
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.sprungBody.sphere.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12772(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12772};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9928]] /* chassis.detailedChassis.spaceFrame.sprungBody.sphere.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12772;
}

/*
equation index: 12773
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToFore.shape.length = 0.7747
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12773(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12773};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9866]] /* chassis.detailedChassis.spaceFrame.midToFore.shape.length variable */) = 0.7747;
  threadData->lastEquationSolved = 12773;
}

/*
equation index: 12774
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.midToAft.shape.length = 0.7747
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12774(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12774};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9843]] /* chassis.detailedChassis.spaceFrame.midToAft.shape.length variable */) = 0.7747;
  threadData->lastEquationSolved = 12774;
}

/*
equation index: 12775
type: SIMPLE_ASSIGN
chassis.detailedChassis.spaceFrame.torsionalRevolute.cylinder.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12775(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12775};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9963]] /* chassis.detailedChassis.spaceFrame.torsionalRevolute.cylinder.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12775;
}

/*
equation index: 12776
type: SIMPLE_ASSIGN
road.roadShape.specularCoefficient = 0.7
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12776(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12776};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10271]] /* road.roadShape.specularCoefficient variable */) = 0.7;
  threadData->lastEquationSolved = 12776;
}

/*
equation index: 12777
type: SIMPLE_ASSIGN
road.roadShape.transparency = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12777(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12777};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10272]] /* road.roadShape.transparency variable */) = 0.0;
  threadData->lastEquationSolved = 12777;
}

/*
equation index: 12778
type: SIMPLE_ASSIGN
world.x_arrowLine.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12778(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12778};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10440]] /* world.x_arrowLine.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12778;
}

/*
equation index: 12779
type: SIMPLE_ASSIGN
world.x_arrowLine.specularCoefficient = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12779(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12779};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10450]] /* world.x_arrowLine.specularCoefficient variable */) = 0.0;
  threadData->lastEquationSolved = 12779;
}

/*
equation index: 12780
type: SIMPLE_ASSIGN
world.x_arrowHead.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12780(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12780};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10415]] /* world.x_arrowHead.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12780;
}

/*
equation index: 12781
type: SIMPLE_ASSIGN
world.x_arrowHead.specularCoefficient = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12781(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12781};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10424]] /* world.x_arrowHead.specularCoefficient variable */) = 0.0;
  threadData->lastEquationSolved = 12781;
}

/*
equation index: 12782
type: SIMPLE_ASSIGN
world.x_label.cylinders[1].extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12782(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12782};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10478]] /* world.x_label.cylinders[1].extra variable */) = 0.0;
  threadData->lastEquationSolved = 12782;
}

/*
equation index: 12783
type: SIMPLE_ASSIGN
world.x_label.cylinders[2].length = 1.4142135623730951 * abs(world.scaledLabel)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12783(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12783};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10481]] /* world.x_label.cylinders[2].length variable */) = (1.4142135623730951) * (fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6927]] /* world.scaledLabel PARAM */)));
  threadData->lastEquationSolved = 12783;
}

/*
equation index: 12784
type: SIMPLE_ASSIGN
world.x_label.cylinders[1].length = 1.4142135623730951 * abs(world.scaledLabel)
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12784(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12784};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10480]] /* world.x_label.cylinders[1].length variable */) = (1.4142135623730951) * (fabs((data->simulationInfo->realParameter[data->simulationInfo->realParamsIndex[6927]] /* world.scaledLabel PARAM */)));
  threadData->lastEquationSolved = 12784;
}

/*
equation index: 12785
type: SIMPLE_ASSIGN
world.x_label.r_abs[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12785(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12785};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10517]] /* world.x_label.r_abs[3] variable */) = 0.0;
  threadData->lastEquationSolved = 12785;
}

/*
equation index: 12786
type: SIMPLE_ASSIGN
world.x_label.r_abs[2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12786(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12786};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10516]] /* world.x_label.r_abs[2] variable */) = 0.0;
  threadData->lastEquationSolved = 12786;
}

/*
equation index: 12787
type: SIMPLE_ASSIGN
world.x_label.r[1] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12787(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12787};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10513]] /* world.x_label.r[1] variable */) = 0.0;
  threadData->lastEquationSolved = 12787;
}

/*
equation index: 12788
type: SIMPLE_ASSIGN
world.x_label.r[2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12788(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12788};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10514]] /* world.x_label.r[2] variable */) = 0.0;
  threadData->lastEquationSolved = 12788;
}

/*
equation index: 12789
type: SIMPLE_ASSIGN
world.x_label.r[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12789(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12789};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10515]] /* world.x_label.r[3] variable */) = 0.0;
  threadData->lastEquationSolved = 12789;
}

/*
equation index: 12790
type: SIMPLE_ASSIGN
world.x_label.r_lines[2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12790(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12790};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10518]] /* world.x_label.r_lines[2] variable */) = 0.0;
  threadData->lastEquationSolved = 12790;
}

/*
equation index: 12791
type: SIMPLE_ASSIGN
world.x_label.r_lines[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12791(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12791};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10519]] /* world.x_label.r_lines[3] variable */) = 0.0;
  threadData->lastEquationSolved = 12791;
}

/*
equation index: 12792
type: SIMPLE_ASSIGN
world.x_label.n_x[1] = 1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12792(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12792};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10507]] /* world.x_label.n_x[1] variable */) = 1.0;
  threadData->lastEquationSolved = 12792;
}

/*
equation index: 12793
type: SIMPLE_ASSIGN
world.x_label.n_x[2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12793(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12793};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10508]] /* world.x_label.n_x[2] variable */) = 0.0;
  threadData->lastEquationSolved = 12793;
}

/*
equation index: 12794
type: SIMPLE_ASSIGN
world.x_label.n_x[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12794(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12794};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10509]] /* world.x_label.n_x[3] variable */) = 0.0;
  threadData->lastEquationSolved = 12794;
}

/*
equation index: 12795
type: SIMPLE_ASSIGN
world.x_label.n_y[1] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12795(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12795};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10510]] /* world.x_label.n_y[1] variable */) = 0.0;
  threadData->lastEquationSolved = 12795;
}

/*
equation index: 12796
type: SIMPLE_ASSIGN
world.x_label.n_y[2] = 1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12796(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12796};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10511]] /* world.x_label.n_y[2] variable */) = 1.0;
  threadData->lastEquationSolved = 12796;
}

/*
equation index: 12797
type: SIMPLE_ASSIGN
world.x_label.n_y[3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12797(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12797};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10512]] /* world.x_label.n_y[3] variable */) = 0.0;
  threadData->lastEquationSolved = 12797;
}

/*
equation index: 12798
type: SIMPLE_ASSIGN
world.x_label.lines[1,1,1] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12798(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12798};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10503]] /* world.x_label.lines[1,1,1] variable */) = 0.0;
  threadData->lastEquationSolved = 12798;
}

/*
equation index: 12799
type: SIMPLE_ASSIGN
world.x_label.lines[1,1,2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12799(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12799};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10504]] /* world.x_label.lines[1,1,2] variable */) = 0.0;
  threadData->lastEquationSolved = 12799;
}

/*
equation index: 12800
type: SIMPLE_ASSIGN
world.x_label.lines[2,1,1] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12800(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12800};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10505]] /* world.x_label.lines[2,1,1] variable */) = 0.0;
  threadData->lastEquationSolved = 12800;
}

/*
equation index: 12801
type: SIMPLE_ASSIGN
world.x_label.lines[2,2,2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12801(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12801};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10506]] /* world.x_label.lines[2,2,2] variable */) = 0.0;
  threadData->lastEquationSolved = 12801;
}

/*
equation index: 12802
type: SIMPLE_ASSIGN
world.x_label.R.T[1,1] = 1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12802(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12802};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10454]] /* world.x_label.R.T[1,1] variable */) = 1.0;
  threadData->lastEquationSolved = 12802;
}

/*
equation index: 12803
type: SIMPLE_ASSIGN
world.x_label.R.T[1,2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12803(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12803};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10455]] /* world.x_label.R.T[1,2] variable */) = 0.0;
  threadData->lastEquationSolved = 12803;
}

/*
equation index: 12804
type: SIMPLE_ASSIGN
world.x_label.R.T[1,3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12804(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12804};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10456]] /* world.x_label.R.T[1,3] variable */) = 0.0;
  threadData->lastEquationSolved = 12804;
}

/*
equation index: 12805
type: SIMPLE_ASSIGN
world.x_label.R.T[2,1] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12805(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12805};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10457]] /* world.x_label.R.T[2,1] variable */) = 0.0;
  threadData->lastEquationSolved = 12805;
}

/*
equation index: 12806
type: SIMPLE_ASSIGN
world.x_label.R.T[2,2] = 1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12806(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12806};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10458]] /* world.x_label.R.T[2,2] variable */) = 1.0;
  threadData->lastEquationSolved = 12806;
}

/*
equation index: 12807
type: SIMPLE_ASSIGN
world.x_label.R.T[2,3] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12807(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12807};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10459]] /* world.x_label.R.T[2,3] variable */) = 0.0;
  threadData->lastEquationSolved = 12807;
}

/*
equation index: 12808
type: SIMPLE_ASSIGN
world.x_label.R.T[3,1] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12808(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12808};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10460]] /* world.x_label.R.T[3,1] variable */) = 0.0;
  threadData->lastEquationSolved = 12808;
}

/*
equation index: 12809
type: SIMPLE_ASSIGN
world.x_label.R.T[3,2] = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12809(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12809};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10461]] /* world.x_label.R.T[3,2] variable */) = 0.0;
  threadData->lastEquationSolved = 12809;
}

/*
equation index: 12810
type: SIMPLE_ASSIGN
world.x_label.R.T[3,3] = 1.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12810(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12810};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10462]] /* world.x_label.R.T[3,3] variable */) = 1.0;
  threadData->lastEquationSolved = 12810;
}

/*
equation index: 12811
type: SIMPLE_ASSIGN
world.x_label.cylinders[2].extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12811(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12811};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10479]] /* world.x_label.cylinders[2].extra variable */) = 0.0;
  threadData->lastEquationSolved = 12811;
}

/*
equation index: 12812
type: SIMPLE_ASSIGN
world.x_label.specularCoefficient = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12812(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12812};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10520]] /* world.x_label.specularCoefficient variable */) = 0.0;
  threadData->lastEquationSolved = 12812;
}

/*
equation index: 12813
type: SIMPLE_ASSIGN
world.y_arrowLine.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12813(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12813};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10561]] /* world.y_arrowLine.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12813;
}

/*
equation index: 12814
type: SIMPLE_ASSIGN
world.y_arrowLine.specularCoefficient = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12814(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12814};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10571]] /* world.y_arrowLine.specularCoefficient variable */) = 0.0;
  threadData->lastEquationSolved = 12814;
}

/*
equation index: 12815
type: SIMPLE_ASSIGN
world.y_arrowHead.extra = 0.0
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_12815(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,12815};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10536]] /* world.y_arrowHead.extra variable */) = 0.0;
  threadData->lastEquationSolved = 12815;
}
OMC_DISABLE_OPT
void BobLib_Experiments_Standards_VehicleSim_functionInitialEquations_16(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[494])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12322,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12323,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12324,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12325,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12326,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12327,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12328,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12329,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12330,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12331,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12332,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12333,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12334,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12335,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12336,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12337,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12338,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12339,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12340,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12341,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12342,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12343,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12344,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12345,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12346,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12347,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12348,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12349,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12350,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12351,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12352,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12353,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12354,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12355,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12356,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12357,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12358,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12359,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12360,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12361,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12362,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12363,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12364,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12365,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12366,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12367,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12368,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12369,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12370,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12371,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12372,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12373,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12374,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12375,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12376,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12377,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12378,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12379,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12380,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12381,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12382,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12383,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12384,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12385,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12386,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12387,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12388,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12389,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12390,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12391,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12392,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12393,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12394,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12395,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12396,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12397,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12398,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12399,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12400,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12401,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12402,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12403,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12404,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12405,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12406,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12407,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12408,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12409,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12410,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12411,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12412,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12413,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12414,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12415,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12416,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12417,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12418,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12419,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12420,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12421,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12422,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12423,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12424,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12425,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12426,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12427,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12428,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12429,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12430,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12431,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12432,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12433,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12434,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12435,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12436,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12437,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12438,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12439,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12440,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12441,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12442,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12443,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12444,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12445,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12446,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12447,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12448,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12449,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12450,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12451,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12452,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12453,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12454,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12455,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12456,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12457,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12458,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12459,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12460,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12461,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12462,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12463,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12464,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12465,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12466,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12467,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12468,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12469,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12470,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12471,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12472,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12473,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12474,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12475,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12476,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12477,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12478,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12479,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12480,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12481,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12482,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12483,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12484,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12485,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12486,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12487,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12488,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12489,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12490,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12491,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12492,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12493,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12494,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12495,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12496,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12497,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12498,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12499,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12500,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12501,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12502,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12503,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12504,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12505,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12506,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12507,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12508,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12509,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12510,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12511,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12512,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12513,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12514,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12515,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12516,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12517,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12518,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12519,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12520,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12521,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12522,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12523,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12524,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12525,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12526,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12527,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12528,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12529,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12530,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12531,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12532,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12533,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12534,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12535,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12536,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12537,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12538,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12539,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12540,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12541,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12542,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12543,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12544,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12545,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12546,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12547,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12548,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12549,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12550,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12551,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12552,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12553,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12554,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12555,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12556,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12557,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12558,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12559,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12560,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12561,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12562,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12563,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12564,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12565,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12566,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12567,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12568,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12569,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12570,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12571,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12572,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12573,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12574,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12575,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12576,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12577,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12578,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12579,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12580,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12581,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12582,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12583,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12584,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12585,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12586,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12587,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12588,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12589,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12590,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12591,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12592,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12593,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12594,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12595,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12596,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12597,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12598,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12599,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12600,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12601,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12602,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12603,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12604,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12605,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12606,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12607,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12608,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12609,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12610,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12611,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12612,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12613,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12614,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12615,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12616,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12617,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12618,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12619,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12620,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12621,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12622,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12623,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12624,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12625,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12626,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12627,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12628,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12629,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12630,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12631,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12632,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12633,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12634,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12635,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12636,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12637,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12638,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12639,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12640,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12641,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12642,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12643,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12644,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12645,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12646,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12647,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12648,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12649,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12650,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12651,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12652,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12653,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12654,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12655,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12656,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12657,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12658,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12659,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12660,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12661,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12662,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12663,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12664,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12665,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12666,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12667,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12668,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12669,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12670,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12671,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12672,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12673,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12674,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12675,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12676,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12677,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12678,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12679,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12680,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12681,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12682,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12683,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12684,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12685,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12686,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12687,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12688,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12689,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12690,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12691,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12692,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12693,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12694,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12695,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12696,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12697,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12698,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12699,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12700,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12701,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12702,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12703,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12704,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12705,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12706,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12707,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12708,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12709,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12710,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12711,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12712,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12713,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12714,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12715,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12716,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12717,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12718,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12719,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12720,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12721,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12722,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12723,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12724,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12725,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12726,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12727,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12728,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12729,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12730,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12731,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12732,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12733,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12734,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12735,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12736,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12737,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12738,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12739,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12740,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12741,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12742,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12743,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12744,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12745,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12746,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12747,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12748,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12749,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12750,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12751,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12752,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12753,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12754,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12755,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12756,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12757,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12758,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12759,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12760,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12761,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12762,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12763,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12764,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12765,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12766,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12767,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12768,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12769,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12770,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12771,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12772,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12773,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12774,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12775,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12776,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12777,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12778,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12779,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12780,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12781,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12782,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12783,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12784,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12785,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12786,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12787,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12788,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12789,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12790,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12791,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12792,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12793,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12794,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12795,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12796,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12797,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12798,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12799,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12800,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12801,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12802,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12803,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12804,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12805,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12806,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12807,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12808,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12809,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12810,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12811,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12812,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12813,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12814,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_12815
  };
  
  for (int id = 0; id < 494; id++) {
    eqFunctions[id](data, threadData);
  }
}
#if defined(__cplusplus)
}
#endif