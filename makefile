IN_CONTAINER := $(shell if [ -f /.dockerenv ]; then printf 1; fi)

ifeq ($(IN_CONTAINER),1)
RUN_BOBSIM :=
RUN_DOE := cd /workspace/_4_OptSim &&
SETUP_CMD := @echo "Already inside the bobsim container; run 'make setup' on the host to build the image."
REBUILD_CMD := @echo "Already inside the bobsim container; run 'make rebuild' on the host to rebuild the image."
SHELL_BOBSIM_CMD := bash
SHELL_DOE_CMD := cd /workspace/_4_OptSim && bash
SHELL_STANDARD_CMD := cd /workspace/_3_StandardSim && bash
else
COMPOSE ?= $(shell if docker compose version >/dev/null 2>&1; then printf "docker compose"; elif command -v docker-compose >/dev/null 2>&1; then printf "docker-compose"; else printf "docker compose"; fi)
RUN_BOBSIM := $(COMPOSE) run --rm -T bobsim
RUN_DOE := $(COMPOSE) run --rm -T doe
SETUP_CMD := $(COMPOSE) build
REBUILD_CMD := $(COMPOSE) build --no-cache
SHELL_BOBSIM_CMD := $(COMPOSE) run --rm bobsim bash
SHELL_DOE_CMD := $(COMPOSE) run --rm doe bash
SHELL_STANDARD_CMD := $(COMPOSE) run --rm standard bash
endif

VEHICLE_YAML_SRC := vehicle.yml
VEHICLE_YAML_DST := _0_Utils/external/BobLib/Generation/vehicle.yml
VEHICLE_SIM_MODEL := _0_Utils/external/BobLib/BobLib/Standards/VehicleSim.mo
VEHICLE_SIM_EXE := _3_StandardSim/Build/VehicleSim/BobLib.Standards.VehicleSim
FOUR_POST_SIM_EXE := _3_StandardSim/Build/FourPostSim/BobLib.Standards.FourPostSim

.PHONY: init setup rebuild \
	shell shell-bobsim shell-doe shell-standard \
	sim-doe sim-standard-sensitivities sim-envelope-sensitivities sim-envelope-all sim-refined-response-surfaces \
	sim-steady-state sim-transient sim-four-post \
	sync-vehicle-yaml build-records build-axle-models \
	build-vehicle-sim build-standard build-four-post-sim build-four-post \
	steady-state-eval transient-eval four-post-eval \
	ggv-envelope ymd-envelope \
	clean-doe clean-envelope clean-standard clean-build clean-results clean

# Setup

init:
	git submodule update --init --recursive

setup:
	$(SETUP_CMD)

rebuild:
	$(REBUILD_CMD)

# Shells

shell: shell-bobsim

shell-bobsim:
	$(SHELL_BOBSIM_CMD)

shell-doe:
	$(SHELL_DOE_CMD)

shell-standard:
	$(SHELL_STANDARD_CMD)

# DOE / sensitivity runs

sim-doe:
	$(RUN_DOE) python -m StandardSens.pre_screen_sensitivities

sim-standard-sensitivities:
	$(RUN_DOE) python -m StandardSens.pre_screen_sensitivities

sim-envelope-sensitivities:
	$(RUN_DOE) python -m EnvelopeSens.sensitivities

sim-envelope-all:
	$(MAKE) sim-four-post
	$(MAKE) ggv-envelope
	$(MAKE) ymd-envelope
	$(MAKE) sim-envelope-sensitivities

sim-refined-response-surfaces:
	$(RUN_DOE) python -m StandardSens.refined_response_surfaces

# Standard simulations
# Build is skipped by sim targets if the executable already exists.
# Run make clean-standard to force a rebuild.

sim-steady-state: sync-vehicle-yaml
	$(RUN_BOBSIM) bash -c "\
		if [ ! -f $(VEHICLE_SIM_EXE) ] || \
		   [ $(VEHICLE_SIM_MODEL) -nt $(VEHICLE_SIM_EXE) ] || \
		   [ $(VEHICLE_YAML_SRC) -nt $(VEHICLE_SIM_EXE) ] || \
		   [ $(VEHICLE_YAML_DST) -nt $(VEHICLE_SIM_EXE) ]; then \
			python _0_Utils/external/BobLib/Generation/scripts/build_vehicle_sim.py && \
			omc /workspace/_3_StandardSim/build_vehicle_sim.mos && \
			[ -f $(VEHICLE_SIM_EXE) ] || \
				{ echo 'ERROR: OMC build failed - executable not produced'; exit 1; }; \
		fi && \
		python -m _3_StandardSim.SteadyStateEval.steady_state_eval_sim"

sim-transient: sync-vehicle-yaml
	$(RUN_BOBSIM) bash -c "\
		if [ ! -f $(VEHICLE_SIM_EXE) ]; then \
			python _0_Utils/external/BobLib/Generation/scripts/build_vehicle_sim.py && \
			omc /workspace/_3_StandardSim/build_vehicle_sim.mos && \
			[ -f $(VEHICLE_SIM_EXE) ] || \
				{ echo 'ERROR: OMC build failed - executable not produced'; exit 1; }; \
		fi && \
		python -m _3_StandardSim.TransientEval.transient_eval_sim"

sim-four-post: sync-vehicle-yaml
	$(RUN_BOBSIM) bash -c "\
		if [ ! -f $(FOUR_POST_SIM_EXE) ]; then \
			python _0_Utils/external/BobLib/Generation/scripts/build_four_post_sim.py && \
			omc /workspace/_3_StandardSim/build_four_post_sim.mos && \
			[ -f $(FOUR_POST_SIM_EXE) ] || \
				{ echo 'ERROR: OMC build failed - executable not produced'; exit 1; }; \
		fi && \
		python -m _3_StandardSim.FourPostEval.four_post_eval_sim"

# Generated Modelica builds

sync-vehicle-yaml:
	@mkdir -p $(dir $(VEHICLE_YAML_DST))
	@if ! cmp -s "$(VEHICLE_YAML_SRC)" "$(VEHICLE_YAML_DST)"; then \
		cp "$(VEHICLE_YAML_SRC)" "$(VEHICLE_YAML_DST)"; \
	fi

build-records: sync-vehicle-yaml
	$(RUN_BOBSIM) python _0_Utils/external/BobLib/Generation/scripts/build_records.py

build-axle-models: sync-vehicle-yaml
	$(RUN_BOBSIM) python _0_Utils/external/BobLib/Generation/scripts/build_axle_models.py

build-vehicle-sim: sync-vehicle-yaml
	$(RUN_BOBSIM) bash -c "\
		python _0_Utils/external/BobLib/Generation/scripts/build_vehicle_sim.py && \
		omc /workspace/_3_StandardSim/build_vehicle_sim.mos && \
		[ -f $(VEHICLE_SIM_EXE) ] || \
			{ echo 'ERROR: OMC build failed - executable not produced'; exit 1; }"

build-standard: build-vehicle-sim

build-four-post-sim: sync-vehicle-yaml
	$(RUN_BOBSIM) bash -c "\
		python _0_Utils/external/BobLib/Generation/scripts/build_four_post_sim.py && \
		omc /workspace/_3_StandardSim/build_four_post_sim.mos && \
		[ -f $(FOUR_POST_SIM_EXE) ] || \
			{ echo 'ERROR: OMC build failed - executable not produced'; exit 1; }"

build-four-post: build-four-post-sim

# Evaluation-only entry points

steady-state-eval: sync-vehicle-yaml
	$(RUN_BOBSIM) bash -c "\
		if [ ! -f $(VEHICLE_SIM_EXE) ] || \
		   [ $(VEHICLE_SIM_MODEL) -nt $(VEHICLE_SIM_EXE) ] || \
		   [ $(VEHICLE_YAML_SRC) -nt $(VEHICLE_SIM_EXE) ] || \
		   [ $(VEHICLE_YAML_DST) -nt $(VEHICLE_SIM_EXE) ]; then \
			python _0_Utils/external/BobLib/Generation/scripts/build_vehicle_sim.py && \
			omc /workspace/_3_StandardSim/build_vehicle_sim.mos && \
			[ -f $(VEHICLE_SIM_EXE) ] || \
				{ echo 'ERROR: OMC build failed - executable not produced'; exit 1; }; \
		fi && \
		python -m _3_StandardSim.SteadyStateEval.steady_state_eval_sim"

transient-eval:
	$(RUN_BOBSIM) python -m _3_StandardSim.TransientEval.transient_eval_sim

four-post-eval:
	$(RUN_BOBSIM) python -m _3_StandardSim.FourPostEval.four_post_eval_sim

ggv-envelope:
	$(RUN_BOBSIM) python -m _2_EnvelopeSim.GGV.ggv_generation

ymd-envelope:
	$(RUN_BOBSIM) python -m _2_EnvelopeSim.YMD.ymd_generation

# Clean
# compile_error_*.log files are preserved for debugging.

clean-doe:
	$(RUN_BOBSIM) bash -c '\
		for path in \
			/workspace/_4_OptSim/Build \
			/workspace/_4_OptSim/StandardSens/results \
			/workspace/_4_OptSim/EnvelopeSens/results \
			/workspace/_4_OptSim/population \
			/workspace/_4_OptSim/population_refined \
			/workspace/_4_OptSim/results; do \
			if [ -d "$$path" ]; then \
				find "$$path" -mindepth 1 ! -name ".gitkeep" -delete; \
			fi; \
		done; \
		echo "DOE artifacts cleaned"'

clean-envelope:
	$(RUN_BOBSIM) bash -c '\
		for path in /workspace/_2_EnvelopeSim/results /workspace/_2_EnvelopeSim/Build; do \
			if [ -d "$$path" ]; then \
				find "$$path" -mindepth 1 ! -name ".gitkeep" -delete; \
			fi; \
		done; \
		echo "EnvelopeSim artifacts cleaned"'

clean-standard:
	$(RUN_BOBSIM) bash -c '\
		for path in /workspace/_3_StandardSim/Build /workspace/_3_StandardSim/results; do \
			if [ -d "$$path" ]; then \
				find "$$path" -mindepth 1 ! -name ".gitkeep" -delete; \
			fi; \
		done; \
		echo "StandardSim artifacts cleaned"'

clean-build:
	$(RUN_BOBSIM) bash -c '\
		find /workspace/_3_StandardSim -type d -name Build -exec find {} -mindepth 1 -delete \;; \
		echo "Build artifacts cleaned"'

clean-results:
	$(RUN_BOBSIM) bash -c '\
		find /workspace/_2_EnvelopeSim -type d -name results -exec find {} -mindepth 1 -delete \;; \
		find /workspace/_2_EnvelopeSim -type d -name Build -exec find {} -mindepth 1 -delete \;; \
		find /workspace/_3_StandardSim -type d -name results -exec find {} -mindepth 1 -delete \;; \
		echo "Result artifacts cleaned"'

clean:
	$(RUN_BOBSIM) bash -c "\
		find /workspace -type d -name '__pycache__' -exec rm -rf {} + 2>/dev/null; \
		find /workspace -type f \( -name '*.pyc' -o -name '*.pyo' \) -delete 2>/dev/null; \
		rm -rf /workspace/.pytest_cache /workspace/.mypy_cache /workspace/.ruff_cache; \
		rm -rf /workspace/.coverage /workspace/htmlcov; \
		rm -rf /workspace/build /workspace/dist; \
		find /workspace -maxdepth 2 -name '*.egg-info' -exec rm -rf {} + 2>/dev/null; \
		echo 'Clean complete'"
