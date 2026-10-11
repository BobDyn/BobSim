# CMake reads this through CMAKE_TOOLCHAIN_FILE before creating the FMU target.
# GCC -O3 on VehicleSim's large initializer can exceed the container memory limit.
# Keep stepping code at Release optimization; setup cost is reported separately.
if(FMU_NAME)
  set_source_files_properties(
    "${CMAKE_CURRENT_SOURCE_DIR}/${FMU_NAME}_init_fmu.c"
    PROPERTIES COMPILE_OPTIONS "-O0")
endif()
