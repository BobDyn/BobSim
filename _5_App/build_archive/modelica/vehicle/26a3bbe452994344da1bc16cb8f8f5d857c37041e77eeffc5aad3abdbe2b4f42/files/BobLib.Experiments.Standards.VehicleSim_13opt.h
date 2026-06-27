#if defined(__cplusplus)
  extern "C" {
#endif
  int BobLib_Experiments_Standards_VehicleSim_mayer(DATA* data, modelica_real** res, short*);
  int BobLib_Experiments_Standards_VehicleSim_lagrange(DATA* data, modelica_real** res, short *, short *);
  int BobLib_Experiments_Standards_VehicleSim_getInputVarIndicesInOptimization(DATA* data, int* input_var_indices);
  int BobLib_Experiments_Standards_VehicleSim_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int BobLib_Experiments_Standards_VehicleSim_setInputData(DATA *data, const modelica_boolean file);
  int BobLib_Experiments_Standards_VehicleSim_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif
