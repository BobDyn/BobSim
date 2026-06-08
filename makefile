PYTHON ?= python

QUALITY_DIRS := _0_Utils _1_VisualSim _2_EnvelopeSim _3_StandardSim _4_OptSim tests
TYPECHECK_DIRS := _0_Utils _1_VisualSim _3_StandardSim tests
BOBLIB_PATH := _0_Utils/external/BobLib

VEHICLE_YAML_SRC := vehicle.yml
VEHICLE_YAML_DST := $(BOBLIB_PATH)/Generation/vehicle.yml
VEHICLE_SIM_MODEL := $(BOBLIB_PATH)/BobLib/Standards/VehicleSim.mo
FOUR_POST_SIM_MODEL := $(BOBLIB_PATH)/BobLib/Standards/FourPostSim.mo
VEHICLE_SIM_EXE := _3_StandardSim/Build/VehicleSim/BobLib.Standards.VehicleSim
FOUR_POST_SIM_EXE := _3_StandardSim/Build/FourPostSim/BobLib.Standards.FourPostSim

BUILD_VEHICLE_SCRIPT := $(BOBLIB_PATH)/Generation/scripts/build_vehicle_sim.py
BUILD_FOUR_POST_SCRIPT := $(BOBLIB_PATH)/Generation/scripts/build_four_post_sim.py
BUILD_VEHICLE_MOS := _3_StandardSim/build_vehicle_sim.mos
BUILD_FOUR_POST_MOS := _3_StandardSim/build_four_post_sim.mos

IN_CONTAINER := $(shell if [ -f /.dockerenv ]; then printf 1; fi)

ifeq ($(IN_CONTAINER),1)
RUN :=
DOCKER_BUILD_CMD := @echo "Already inside the BobSim container."
DOCKER_REBUILD_CMD := @echo "Already inside the BobSim container."
SHELL_BOBSIM_CMD := bash
SHELL_STANDARD_CMD := cd _3_StandardSim && bash
SHELL_ENVELOPE_CMD := cd _2_EnvelopeSim && bash
SHELL_OPT_CMD := cd _4_OptSim && bash
else
COMPOSE ?= $(shell if docker compose version >/dev/null 2>&1; then printf "docker compose"; elif command -v docker-compose >/dev/null 2>&1; then printf "docker-compose"; else printf "docker compose"; fi)
RUN := $(COMPOSE) run --rm -T bobsim
DOCKER_BUILD_CMD := $(COMPOSE) build
DOCKER_REBUILD_CMD := $(COMPOSE) build --no-cache
SHELL_BOBSIM_CMD := $(COMPOSE) run --rm bobsim bash
SHELL_STANDARD_CMD := $(COMPOSE) run --rm standard bash
SHELL_ENVELOPE_CMD := $(COMPOSE) run --rm envelope bash
SHELL_OPT_CMD := $(COMPOSE) run --rm opt bash
endif

WORKSPACE ?= $(if $(RUN),/workspace,$(CURDIR))

.DEFAULT_GOAL := help

.PHONY: help init docker-build docker-rebuild \
	lint typecheck test ci \
	shell shell-bobsim shell-standard shell-envelope shell-opt \
	sync-vehicle standard-build standard-build-four-post \
	standard-eval-steady-state standard-eval-transient standard-eval-four-post standard-eval-all \
	envelope-ggv envelope-ymd envelope-all \
	opt-standard opt-envelope opt-refined \
	clean clean-standard clean-envelope clean-opt clean-all

help:
	@printf '%s\n' \
		'BobSim targets:' \
		'' \
		'  init                      Initialize submodules' \
		'  docker-build              Build the Docker development image' \
		'  docker-rebuild            Rebuild the Docker image from scratch' \
		'' \
		'  shell                     Open the main BobSim shell' \
		'  shell-standard            Open a StandardSim shell' \
		'  shell-envelope            Open an EnvelopeSim shell' \
		'  shell-opt                 Open an OptSim shell' \
		'' \
		'  standard-build            Build BobLib.Standards.VehicleSim' \
		'  standard-build-four-post  Build BobLib.Standards.FourPostSim' \
		'' \
		'  standard-eval-steady-state Run SteadyStateEval' \
		'  standard-eval-transient    Run TransientEval' \
		'  standard-eval-four-post    Run FourPostEval' \
		'  standard-eval-all          Run all standard evaluations' \
		'' \
		'  envelope-ggv              Generate the GGV envelope' \
		'  envelope-ymd              Generate the YMD envelope' \
		'  envelope-all              Generate all envelope outputs' \
		'' \
		'  opt-standard              Run StandardSens pre-screen sensitivities' \
		'  opt-envelope              Run EnvelopeSens sensitivities' \
		'  opt-refined               Run StandardSens refined response surfaces' \
		'' \
		'  ci                        Run lint, typecheck, and tests' \
		'  clean-all                 Remove caches and generated workflow artifacts'

init:
	git submodule update --init --recursive

docker-build:
	$(DOCKER_BUILD_CMD)

docker-rebuild:
	$(DOCKER_REBUILD_CMD)

lint:
	$(RUN) $(PYTHON) -m ruff check $(QUALITY_DIRS) --exclude $(BOBLIB_PATH)

typecheck:
	$(RUN) $(PYTHON) -m mypy $(TYPECHECK_DIRS) \
		--ignore-missing-imports \
		--no-strict-optional \
		--exclude '(^|/)$(BOBLIB_PATH)/'

test:
	$(RUN) $(PYTHON) -m pytest tests

ci: lint typecheck test

shell: shell-bobsim

shell-bobsim:
	$(SHELL_BOBSIM_CMD)

shell-standard:
	$(SHELL_STANDARD_CMD)

shell-envelope:
	$(SHELL_ENVELOPE_CMD)

shell-opt:
	$(SHELL_OPT_CMD)

$(VEHICLE_YAML_DST): $(VEHICLE_YAML_SRC)
	@mkdir -p $(dir $@)
	cp "$<" "$@"

sync-vehicle: $(VEHICLE_YAML_DST)

$(VEHICLE_SIM_EXE): $(VEHICLE_YAML_DST) $(VEHICLE_SIM_MODEL) $(BUILD_VEHICLE_SCRIPT) $(BUILD_VEHICLE_MOS)
	$(RUN) bash -lc '$(PYTHON) $(BUILD_VEHICLE_SCRIPT) && omc $(WORKSPACE)/$(BUILD_VEHICLE_MOS) && test -f $(WORKSPACE)/$(VEHICLE_SIM_EXE)'

$(FOUR_POST_SIM_EXE): $(VEHICLE_YAML_DST) $(FOUR_POST_SIM_MODEL) $(BUILD_FOUR_POST_SCRIPT) $(BUILD_FOUR_POST_MOS)
	$(RUN) bash -lc '$(PYTHON) $(BUILD_FOUR_POST_SCRIPT) && omc $(WORKSPACE)/$(BUILD_FOUR_POST_MOS) && test -f $(WORKSPACE)/$(FOUR_POST_SIM_EXE)'

standard-build: $(VEHICLE_SIM_EXE)

standard-build-four-post: $(FOUR_POST_SIM_EXE)

standard-eval-steady-state: standard-build
	$(RUN) $(PYTHON) -m _3_StandardSim.SteadyStateEval.steady_state_eval_sim

standard-eval-transient: standard-build
	$(RUN) $(PYTHON) -m _3_StandardSim.TransientEval.transient_eval_sim

standard-eval-four-post: standard-build-four-post
	$(RUN) $(PYTHON) -m _3_StandardSim.FourPostEval.four_post_eval_sim

standard-eval-all: standard-eval-steady-state standard-eval-transient standard-eval-four-post

envelope-ggv:
	$(RUN) $(PYTHON) -m _2_EnvelopeSim.GGV.ggv_generation

envelope-ymd:
	$(RUN) $(PYTHON) -m _2_EnvelopeSim.YMD.ymd_generation

envelope-all: envelope-ggv envelope-ymd

opt-standard:
	$(RUN) env PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m StandardSens.pre_screen_sensitivities

opt-envelope:
	$(RUN) env PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m EnvelopeSens.sensitivities

opt-refined:
	$(RUN) env PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m StandardSens.refined_response_surfaces

clean:
	$(RUN) bash -lc "find $(WORKSPACE) -type d -name '__pycache__' -exec rm -rf {} + 2>/dev/null; \
		find $(WORKSPACE) -type f \( -name '*.pyc' -o -name '*.pyo' \) -delete 2>/dev/null; \
		rm -rf $(WORKSPACE)/.pytest_cache $(WORKSPACE)/.mypy_cache $(WORKSPACE)/.ruff_cache; \
		rm -rf $(WORKSPACE)/.coverage $(WORKSPACE)/htmlcov $(WORKSPACE)/build $(WORKSPACE)/dist; \
		find $(WORKSPACE) -maxdepth 2 -name '*.egg-info' -exec rm -rf {} + 2>/dev/null; \
		echo 'Python/tool caches cleaned'"

clean-standard:
	$(RUN) bash -lc "for path in $(WORKSPACE)/_3_StandardSim/Build $(WORKSPACE)/_3_StandardSim/results; do \
		if [ -d \"$$path\" ]; then find \"$$path\" -mindepth 1 ! -name '.gitkeep' -delete; fi; \
		done; echo 'StandardSim artifacts cleaned'"

clean-envelope:
	$(RUN) bash -lc "for path in $(WORKSPACE)/_2_EnvelopeSim/Build $(WORKSPACE)/_2_EnvelopeSim/results; do \
		if [ -d \"$$path\" ]; then find \"$$path\" -mindepth 1 ! -name '.gitkeep' -delete; fi; \
		done; echo 'EnvelopeSim artifacts cleaned'"

clean-opt:
	$(RUN) bash -lc "for path in \
		$(WORKSPACE)/_4_OptSim/Build \
		$(WORKSPACE)/_4_OptSim/StandardSens/results \
		$(WORKSPACE)/_4_OptSim/EnvelopeSens/results \
		$(WORKSPACE)/_4_OptSim/population \
		$(WORKSPACE)/_4_OptSim/population_refined \
		$(WORKSPACE)/_4_OptSim/results; do \
		if [ -d \"$$path\" ]; then find \"$$path\" -mindepth 1 ! -name '.gitkeep' -delete; fi; \
		done; echo 'OptSim artifacts cleaned'"

clean-all: clean clean-standard clean-envelope clean-opt
