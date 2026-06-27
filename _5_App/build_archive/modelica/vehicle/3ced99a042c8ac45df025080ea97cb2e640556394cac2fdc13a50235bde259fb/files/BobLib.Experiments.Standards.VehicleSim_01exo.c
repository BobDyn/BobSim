/* External objects file */
#include "BobLib.Experiments.Standards.VehicleSim_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

void BobLib_Experiments_Standards_VehicleSim_callExternalObjectDestructors(DATA *data, threadData_t *threadData)
{
  if(data->simulationInfo->extObjs)
  {
    omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData,(data->simulationInfo->extObjs[1]));
    omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData,(data->simulationInfo->extObjs[0]));
    omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData,(data->simulationInfo->extObjs[3]));
    omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData,(data->simulationInfo->extObjs[2]));
    omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData,(data->simulationInfo->extObjs[5]));
    omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData,(data->simulationInfo->extObjs[4]));
    omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData,(data->simulationInfo->extObjs[7]));
    omc_Modelica_Blocks_Types_ExternalCombiTable1D_destructor(threadData,(data->simulationInfo->extObjs[6]));
    free(data->simulationInfo->extObjs);
    data->simulationInfo->extObjs = 0;
  }
}
#if defined(__cplusplus)
}
#endif
