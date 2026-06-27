/* Asserts */
#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
equation index: 49366
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperForeLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperForeLinkLength, has value: " + String(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperForeLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49366(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49366};
  modelica_boolean tmp0;
  static const MMC_DEFSTRINGLIT(tmp1,131,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperForeLinkLength, has value: ");
  modelica_string tmp2;
  modelica_metatype tmpMeta3;
  static int tmp4 = 0;
  if(!tmp4)
  {
    tmp0 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3728]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperForeLinkLength variable */),0.0);
    if(!tmp0)
    {
      tmp2 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3728]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperForeLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta3 = stringAppend(MMC_REFSTRINGLIT(tmp1),tmp2);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperForeLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",153,3,153,27,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta3));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",153,3,153,27,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta3));
        }
      }
      tmp4 = 1;
    }
  }
  threadData->lastEquationSolved = 49366;
}

/*
equation index: 49367
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperAftLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperAftLinkLength, has value: " + String(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperAftLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49367(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49367};
  modelica_boolean tmp5;
  static const MMC_DEFSTRINGLIT(tmp6,130,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperAftLinkLength, has value: ");
  modelica_string tmp7;
  modelica_metatype tmpMeta8;
  static int tmp9 = 0;
  if(!tmp9)
  {
    tmp5 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3700]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperAftLinkLength variable */),0.0);
    if(!tmp5)
    {
      tmp7 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3700]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperAftLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta8 = stringAppend(MMC_REFSTRINGLIT(tmp6),tmp7);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.upperAftLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",155,3,155,26,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta8));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",155,3,155,26,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta8));
        }
      }
      tmp9 = 1;
    }
  }
  threadData->lastEquationSolved = 49367;
}

/*
equation index: 49368
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerForeLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerForeLinkLength, has value: " + String(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerForeLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49368(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49368};
  modelica_boolean tmp10;
  static const MMC_DEFSTRINGLIT(tmp11,131,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerForeLinkLength, has value: ");
  modelica_string tmp12;
  modelica_metatype tmpMeta13;
  static int tmp14 = 0;
  if(!tmp14)
  {
    tmp10 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3557]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerForeLinkLength variable */),0.0);
    if(!tmp10)
    {
      tmp12 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3557]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerForeLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta13 = stringAppend(MMC_REFSTRINGLIT(tmp11),tmp12);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerForeLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",157,3,157,27,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta13));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",157,3,157,27,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta13));
        }
      }
      tmp14 = 1;
    }
  }
  threadData->lastEquationSolved = 49368;
}

/*
equation index: 49369
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerAftLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerAftLinkLength, has value: " + String(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerAftLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49369(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49369};
  modelica_boolean tmp15;
  static const MMC_DEFSTRINGLIT(tmp16,130,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerAftLinkLength, has value: ");
  modelica_string tmp17;
  modelica_metatype tmpMeta18;
  static int tmp19 = 0;
  if(!tmp19)
  {
    tmp15 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3529]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerAftLinkLength variable */),0.0);
    if(!tmp15)
    {
      tmp17 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3529]] /* chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerAftLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta18 = stringAppend(MMC_REFSTRINGLIT(tmp16),tmp17);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.leftWishboneUprightLoop.lowerAftLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",159,3,159,26,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta18));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",159,3,159,26,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta18));
        }
      }
      tmp19 = 1;
    }
  }
  threadData->lastEquationSolved = 49369;
}

/*
equation index: 49370
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperForeLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperForeLinkLength, has value: " + String(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperForeLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49370(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49370};
  modelica_boolean tmp20;
  static const MMC_DEFSTRINGLIT(tmp21,132,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperForeLinkLength, has value: ");
  modelica_string tmp22;
  modelica_metatype tmpMeta23;
  static int tmp24 = 0;
  if(!tmp24)
  {
    tmp20 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5483]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperForeLinkLength variable */),0.0);
    if(!tmp20)
    {
      tmp22 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5483]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperForeLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta23 = stringAppend(MMC_REFSTRINGLIT(tmp21),tmp22);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperForeLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",153,3,153,27,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta23));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",153,3,153,27,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta23));
        }
      }
      tmp24 = 1;
    }
  }
  threadData->lastEquationSolved = 49370;
}

/*
equation index: 49371
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperAftLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperAftLinkLength, has value: " + String(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperAftLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49371(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49371};
  modelica_boolean tmp25;
  static const MMC_DEFSTRINGLIT(tmp26,131,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperAftLinkLength, has value: ");
  modelica_string tmp27;
  modelica_metatype tmpMeta28;
  static int tmp29 = 0;
  if(!tmp29)
  {
    tmp25 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5455]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperAftLinkLength variable */),0.0);
    if(!tmp25)
    {
      tmp27 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5455]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperAftLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta28 = stringAppend(MMC_REFSTRINGLIT(tmp26),tmp27);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.upperAftLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",155,3,155,26,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta28));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",155,3,155,26,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta28));
        }
      }
      tmp29 = 1;
    }
  }
  threadData->lastEquationSolved = 49371;
}

/*
equation index: 49372
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerForeLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerForeLinkLength, has value: " + String(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerForeLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49372(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49372};
  modelica_boolean tmp30;
  static const MMC_DEFSTRINGLIT(tmp31,132,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerForeLinkLength, has value: ");
  modelica_string tmp32;
  modelica_metatype tmpMeta33;
  static int tmp34 = 0;
  if(!tmp34)
  {
    tmp30 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5310]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerForeLinkLength variable */),0.0);
    if(!tmp30)
    {
      tmp32 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5310]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerForeLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta33 = stringAppend(MMC_REFSTRINGLIT(tmp31),tmp32);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerForeLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",157,3,157,27,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta33));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",157,3,157,27,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta33));
        }
      }
      tmp34 = 1;
    }
  }
  threadData->lastEquationSolved = 49372;
}

/*
equation index: 49373
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerAftLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerAftLinkLength, has value: " + String(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerAftLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49373(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49373};
  modelica_boolean tmp35;
  static const MMC_DEFSTRINGLIT(tmp36,131,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerAftLinkLength, has value: ");
  modelica_string tmp37;
  modelica_metatype tmpMeta38;
  static int tmp39 = 0;
  if(!tmp39)
  {
    tmp35 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5282]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerAftLinkLength variable */),0.0);
    if(!tmp35)
    {
      tmp37 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5282]] /* chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerAftLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta38 = stringAppend(MMC_REFSTRINGLIT(tmp36),tmp37);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.rightWishboneUprightLoop.lowerAftLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",159,3,159,26,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta38));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",159,3,159,26,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta38));
        }
      }
      tmp39 = 1;
    }
  }
  threadData->lastEquationSolved = 49373;
}

/*
equation index: 49374
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.s_rel >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.s_rel, has value: " + String(chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.s_rel, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49374(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49374};
  modelica_boolean tmp40;
  static const MMC_DEFSTRINGLIT(tmp41,124,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.s_rel, has value: ");
  modelica_string tmp42;
  modelica_metatype tmpMeta43;
  static int tmp44 = 0;
  if(!tmp44)
  {
    tmp40 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2864]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.s_rel DUMMY_STATE */),0.0);
    if(!tmp40)
    {
      tmp42 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2864]] /* chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.s_rel DUMMY_STATE */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta43 = stringAppend(MMC_REFSTRINGLIT(tmp41),tmp42);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.leftShockLinkage.TabularDamper.s_rel >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Linkages/Templates/TabularCompliant.mo",23,3,23,13,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta43));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Linkages/Templates/TabularCompliant.mo",23,3,23,13,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta43));
        }
      }
      tmp44 = 1;
    }
  }
  threadData->lastEquationSolved = 49374;
}

/*
equation index: 49375
type: ALGORITHM

  assert(chassis.detailedChassis.frAxleDW.rightShockLinkage.TabularDamper.s_rel >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightShockLinkage.TabularDamper.s_rel, has value: " + String(chassis.detailedChassis.frAxleDW.rightShockLinkage.TabularDamper.s_rel, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49375(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49375};
  modelica_boolean tmp45;
  static const MMC_DEFSTRINGLIT(tmp46,125,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.frAxleDW.rightShockLinkage.TabularDamper.s_rel, has value: ");
  modelica_string tmp47;
  modelica_metatype tmpMeta48;
  static int tmp49 = 0;
  if(!tmp49)
  {
    tmp45 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4624]] /* chassis.detailedChassis.frAxleDW.rightShockLinkage.TabularDamper.s_rel DUMMY_STATE */),0.0);
    if(!tmp45)
    {
      tmp47 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4624]] /* chassis.detailedChassis.frAxleDW.rightShockLinkage.TabularDamper.s_rel DUMMY_STATE */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta48 = stringAppend(MMC_REFSTRINGLIT(tmp46),tmp47);
      {
        const char* assert_cond = "(chassis.detailedChassis.frAxleDW.rightShockLinkage.TabularDamper.s_rel >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Linkages/Templates/TabularCompliant.mo",23,3,23,13,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta48));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Linkages/Templates/TabularCompliant.mo",23,3,23,13,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta48));
        }
      }
      tmp49 = 1;
    }
  }
  threadData->lastEquationSolved = 49375;
}

/*
equation index: 49376
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeLinkLength, has value: " + String(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49376(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49376};
  modelica_boolean tmp50;
  static const MMC_DEFSTRINGLIT(tmp51,131,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeLinkLength, has value: ");
  modelica_string tmp52;
  modelica_metatype tmpMeta53;
  static int tmp54 = 0;
  if(!tmp54)
  {
    tmp50 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7479]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeLinkLength variable */),0.0);
    if(!tmp50)
    {
      tmp52 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7479]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta53 = stringAppend(MMC_REFSTRINGLIT(tmp51),tmp52);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperForeLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",153,3,153,27,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta53));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",153,3,153,27,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta53));
        }
      }
      tmp54 = 1;
    }
  }
  threadData->lastEquationSolved = 49376;
}

/*
equation index: 49377
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftLinkLength, has value: " + String(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49377(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49377};
  modelica_boolean tmp55;
  static const MMC_DEFSTRINGLIT(tmp56,130,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftLinkLength, has value: ");
  modelica_string tmp57;
  modelica_metatype tmpMeta58;
  static int tmp59 = 0;
  if(!tmp59)
  {
    tmp55 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7451]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftLinkLength variable */),0.0);
    if(!tmp55)
    {
      tmp57 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7451]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta58 = stringAppend(MMC_REFSTRINGLIT(tmp56),tmp57);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.upperAftLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",155,3,155,26,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta58));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",155,3,155,26,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta58));
        }
      }
      tmp59 = 1;
    }
  }
  threadData->lastEquationSolved = 49377;
}

/*
equation index: 49378
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeLinkLength, has value: " + String(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49378(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49378};
  modelica_boolean tmp60;
  static const MMC_DEFSTRINGLIT(tmp61,131,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeLinkLength, has value: ");
  modelica_string tmp62;
  modelica_metatype tmpMeta63;
  static int tmp64 = 0;
  if(!tmp64)
  {
    tmp60 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7311]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeLinkLength variable */),0.0);
    if(!tmp60)
    {
      tmp62 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7311]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta63 = stringAppend(MMC_REFSTRINGLIT(tmp61),tmp62);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerForeLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",157,3,157,27,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta63));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",157,3,157,27,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta63));
        }
      }
      tmp64 = 1;
    }
  }
  threadData->lastEquationSolved = 49378;
}

/*
equation index: 49379
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftLinkLength, has value: " + String(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49379(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49379};
  modelica_boolean tmp65;
  static const MMC_DEFSTRINGLIT(tmp66,130,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftLinkLength, has value: ");
  modelica_string tmp67;
  modelica_metatype tmpMeta68;
  static int tmp69 = 0;
  if(!tmp69)
  {
    tmp65 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7283]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftLinkLength variable */),0.0);
    if(!tmp65)
    {
      tmp67 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7283]] /* chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta68 = stringAppend(MMC_REFSTRINGLIT(tmp66),tmp67);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.leftWishboneUprightLoop.lowerAftLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",159,3,159,26,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta68));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",159,3,159,26,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta68));
        }
      }
      tmp69 = 1;
    }
  }
  threadData->lastEquationSolved = 49379;
}

/*
equation index: 49380
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeLinkLength, has value: " + String(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49380(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49380};
  modelica_boolean tmp70;
  static const MMC_DEFSTRINGLIT(tmp71,132,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeLinkLength, has value: ");
  modelica_string tmp72;
  modelica_metatype tmpMeta73;
  static int tmp74 = 0;
  if(!tmp74)
  {
    tmp70 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9234]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeLinkLength variable */),0.0);
    if(!tmp70)
    {
      tmp72 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9234]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta73 = stringAppend(MMC_REFSTRINGLIT(tmp71),tmp72);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperForeLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",153,3,153,27,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta73));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",153,3,153,27,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta73));
        }
      }
      tmp74 = 1;
    }
  }
  threadData->lastEquationSolved = 49380;
}

/*
equation index: 49381
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftLinkLength, has value: " + String(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49381(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49381};
  modelica_boolean tmp75;
  static const MMC_DEFSTRINGLIT(tmp76,131,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftLinkLength, has value: ");
  modelica_string tmp77;
  modelica_metatype tmpMeta78;
  static int tmp79 = 0;
  if(!tmp79)
  {
    tmp75 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9206]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftLinkLength variable */),0.0);
    if(!tmp75)
    {
      tmp77 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9206]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta78 = stringAppend(MMC_REFSTRINGLIT(tmp76),tmp77);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.upperAftLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",155,3,155,26,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta78));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",155,3,155,26,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta78));
        }
      }
      tmp79 = 1;
    }
  }
  threadData->lastEquationSolved = 49381;
}

/*
equation index: 49382
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeLinkLength, has value: " + String(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49382(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49382};
  modelica_boolean tmp80;
  static const MMC_DEFSTRINGLIT(tmp81,132,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeLinkLength, has value: ");
  modelica_string tmp82;
  modelica_metatype tmpMeta83;
  static int tmp84 = 0;
  if(!tmp84)
  {
    tmp80 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9067]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeLinkLength variable */),0.0);
    if(!tmp80)
    {
      tmp82 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9067]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta83 = stringAppend(MMC_REFSTRINGLIT(tmp81),tmp82);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerForeLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",157,3,157,27,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta83));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",157,3,157,27,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta83));
        }
      }
      tmp84 = 1;
    }
  }
  threadData->lastEquationSolved = 49382;
}

/*
equation index: 49383
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftLinkLength >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftLinkLength, has value: " + String(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftLinkLength, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49383(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49383};
  modelica_boolean tmp85;
  static const MMC_DEFSTRINGLIT(tmp86,131,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftLinkLength, has value: ");
  modelica_string tmp87;
  modelica_metatype tmpMeta88;
  static int tmp89 = 0;
  if(!tmp89)
  {
    tmp85 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9039]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftLinkLength variable */),0.0);
    if(!tmp85)
    {
      tmp87 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9039]] /* chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftLinkLength variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta88 = stringAppend(MMC_REFSTRINGLIT(tmp86),tmp87);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.rightWishboneUprightLoop.lowerAftLinkLength >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",159,3,159,26,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta88));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Templates/DoubleWishbone/WishboneUprightLoop.mo",159,3,159,26,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta88));
        }
      }
      tmp89 = 1;
    }
  }
  threadData->lastEquationSolved = 49383;
}

/*
equation index: 49384
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.s_rel >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.s_rel, has value: " + String(chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.s_rel, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49384(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49384};
  modelica_boolean tmp90;
  static const MMC_DEFSTRINGLIT(tmp91,124,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.s_rel, has value: ");
  modelica_string tmp92;
  modelica_metatype tmpMeta93;
  static int tmp94 = 0;
  if(!tmp94)
  {
    tmp90 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6618]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.s_rel DUMMY_STATE */),0.0);
    if(!tmp90)
    {
      tmp92 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6618]] /* chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.s_rel DUMMY_STATE */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta93 = stringAppend(MMC_REFSTRINGLIT(tmp91),tmp92);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.leftShockLinkage.TabularDamper.s_rel >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Linkages/Templates/TabularCompliant.mo",23,3,23,13,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta93));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Linkages/Templates/TabularCompliant.mo",23,3,23,13,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta93));
        }
      }
      tmp94 = 1;
    }
  }
  threadData->lastEquationSolved = 49384;
}

/*
equation index: 49385
type: ALGORITHM

  assert(chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.s_rel >= 0.0, "Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.s_rel, has value: " + String(chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.s_rel, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49385(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49385};
  modelica_boolean tmp95;
  static const MMC_DEFSTRINGLIT(tmp96,125,"Variable violating min constraint: 0.0 <= chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.s_rel, has value: ");
  modelica_string tmp97;
  modelica_metatype tmpMeta98;
  static int tmp99 = 0;
  if(!tmp99)
  {
    tmp95 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8381]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.s_rel DUMMY_STATE */),0.0);
    if(!tmp95)
    {
      tmp97 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8381]] /* chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.s_rel DUMMY_STATE */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta98 = stringAppend(MMC_REFSTRINGLIT(tmp96),tmp97);
      {
        const char* assert_cond = "(chassis.detailedChassis.rrAxleDW.rightShockLinkage.TabularDamper.s_rel >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Linkages/Templates/TabularCompliant.mo",23,3,23,13,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta98));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/Chassis/Suspension/Linkages/Templates/TabularCompliant.mo",23,3,23,13,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta98));
        }
      }
      tmp99 = 1;
    }
  }
  threadData->lastEquationSolved = 49385;
}

/*
equation index: 49386
type: ALGORITHM

  assert(battery.SOC >= 0.0 and battery.SOC <= 1.0, "Variable violating min/max constraint: 0.0 <= battery.SOC <= 1.0, has value: " + String(battery.SOC, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49386(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49386};
  modelica_boolean tmp100;
  modelica_boolean tmp101;
  static const MMC_DEFSTRINGLIT(tmp102,77,"Variable violating min/max constraint: 0.0 <= battery.SOC <= 1.0, has value: ");
  modelica_string tmp103;
  modelica_metatype tmpMeta104;
  static int tmp105 = 0;
  if(!tmp105)
  {
    tmp100 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2235]] /* battery.SOC variable */),0.0);
    tmp101 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2235]] /* battery.SOC variable */),1.0);
    if(!(tmp100 && tmp101))
    {
      tmp103 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2235]] /* battery.SOC variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta104 = stringAppend(MMC_REFSTRINGLIT(tmp102),tmp103);
      {
        const char* assert_cond = "(battery.SOC >= 0.0 and battery.SOC <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/EnergyStorage/BatteryPack.mo",21,3,21,53,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta104));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/EnergyStorage/BatteryPack.mo",21,3,21,53,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta104));
        }
      }
      tmp105 = 1;
    }
  }
  threadData->lastEquationSolved = 49386;
}

/*
equation index: 49387
type: ALGORITHM

  assert(battery.SOE >= 0.0 and battery.SOE <= 1.0, "Variable violating min/max constraint: 0.0 <= battery.SOE <= 1.0, has value: " + String(battery.SOE, "g"));
*/
void BobLib_Experiments_Standards_VehicleSim_eqFunction_49387(DATA *data, threadData_t *threadData)
{
  const int equationIndexes[2] = {1,49387};
  modelica_boolean tmp106;
  modelica_boolean tmp107;
  static const MMC_DEFSTRINGLIT(tmp108,77,"Variable violating min/max constraint: 0.0 <= battery.SOE <= 1.0, has value: ");
  modelica_string tmp109;
  modelica_metatype tmpMeta110;
  static int tmp111 = 0;
  if(!tmp111)
  {
    tmp106 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2236]] /* battery.SOE variable */),0.0);
    tmp107 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2236]] /* battery.SOE variable */),1.0);
    if(!(tmp106 && tmp107))
    {
      tmp109 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2236]] /* battery.SOE variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta110 = stringAppend(MMC_REFSTRINGLIT(tmp108),tmp109);
      {
        const char* assert_cond = "(battery.SOE >= 0.0 and battery.SOE <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/EnergyStorage/BatteryPack.mo",22,3,22,53,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta110));
        } else {
          FILE_INFO info = {"/home/rhorvath/Documents/Github/BobSim/_0_Utils/external/BobLib/BobLib/EnergyStorage/BatteryPack.mo",22,3,22,53,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta110));
        }
      }
      tmp111 = 1;
    }
  }
  threadData->lastEquationSolved = 49387;
}
/* function to check assert after a step is done */
OMC_DISABLE_OPT
int BobLib_Experiments_Standards_VehicleSim_checkForAsserts(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[22])(DATA*, threadData_t*) = {
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49366,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49367,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49368,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49369,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49370,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49371,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49372,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49373,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49374,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49375,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49376,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49377,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49378,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49379,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49380,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49381,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49382,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49383,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49384,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49385,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49386,
    BobLib_Experiments_Standards_VehicleSim_eqFunction_49387
  };
  
  for (int id = 0; id < 22; id++) {
    eqFunctions[id](data, threadData);
  }
  
  return 0;
}

#if defined(__cplusplus)
}
#endif
