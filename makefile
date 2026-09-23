PYTHON ?= python
RUFF_CACHE_DIR ?= /tmp/bobsim-ruff-cache
MYPY_CACHE_DIR ?= /tmp/bobsim-mypy-cache

QUALITY_DIRS := _0_Utils _1_VisualSim _2_EnvelopeSim _3_StandardSim _4_OptSim _5_App tests
TYPECHECK_DIRS := _0_Utils _1_VisualSim _2_EnvelopeSim _3_StandardSim _4_OptSim _5_App tests
BOBLIB_PATH := _0_Utils/external/BobLib
BOBLIB_PACKAGE_PATH := $(BOBLIB_PATH)/BobLib
VEHICLE_SIM_CLASS := BobLib.Experiments.Standards.VehicleSim
FOUR_POST_SIM_CLASS := BobLib.Experiments.Standards.FourPostSim

VEHICLE_SIM_MODEL := $(BOBLIB_PACKAGE_PATH)/Experiments/Standards/VehicleSim.mo
FOUR_POST_SIM_MODEL := $(BOBLIB_PACKAGE_PATH)/Experiments/Standards/FourPostSim.mo
VEHICLE_SIM_EXE := _3_StandardSim/BuildBobLib/VehicleSim/$(VEHICLE_SIM_CLASS)
FOUR_POST_SIM_EXE := _3_StandardSim/BuildBobLib/FourPostSim/$(FOUR_POST_SIM_CLASS)

BUILD_VEHICLE_MOS := _3_StandardSim/build_vehicle_sim.mos
BUILD_FOUR_POST_MOS := _3_StandardSim/build_four_post_sim.mos

SEARCH_TOP ?= 1
TARGETS ?=
KNOBS ?=
STUDY ?=
REDUCED_DOF ?= 6
REDUCED_KINEMATICS ?= lookup
REDUCED_BOBLIB_CSV ?=
REDUCED_MBD_DIR ?=
REDUCED_SUSPENSION_METRICS ?= _3_StandardSim/generated_results/four_post_eval_report_metrics.csv
LAP_CONFIG ?= _3_StandardSim/LapTimeEval/lap_time_eval_config.yml
LAP_SCENARIO ?= both
LAP_DOF ?=

# DOE overrides. Empty means use configs/vehicle_architecture.yaml.
# DOE_SCOPE is setup or architecture. Empty means all.
DOE_METHOD ?=
DOE_SAMPLES ?=
DOE_INTERVALS ?=
DOE_SCOPE ?=
DOE_ENV := \
	$(if $(DOE_METHOD),BOBSIM_DOE_METHOD=$(DOE_METHOD),) \
	$(if $(DOE_SAMPLES),BOBSIM_DOE_SAMPLES=$(DOE_SAMPLES),) \
	$(if $(DOE_INTERVALS),BOBSIM_DOE_INTERVALS=$(DOE_INTERVALS),) \
	$(if $(DOE_SCOPE),BOBSIM_DOE_SCOPE=$(DOE_SCOPE),)

FOUR_POST_METRICS := _3_StandardSim/generated_results/four_post_eval_report_metrics.csv

# BobVis targets write scenes into $(VISUAL_RESULTS). The app's Replay tab draws them.
VISUAL_DIR := _1_VisualSim
VISUAL_RESULTS := $(VISUAL_DIR)/results
VISUAL_DEMO_CONFIG := $(VISUAL_RESULTS)/demo_step_steer.yml
VISUAL_DEMO_DATA := $(VISUAL_RESULTS)/demo_step_steer.npz
# Evaluation for visual-capture: four_post, transient, ramp_steer or steady_state.
VISUAL_EVAL ?= four_post
VISUAL_MANEUVER ?= transient
VISUAL_CAPTURE := $(VISUAL_RESULTS)/$(VISUAL_EVAL)
VISUAL_EVAL_MODULE_four_post := FourPostEval.four_post_eval_sim
VISUAL_EVAL_MODULE_transient := TransientEval.transient_eval_sim
VISUAL_EVAL_MODULE_ramp_steer := RampSteerEval.ramp_steer_eval_sim
VISUAL_EVAL_MODULE_steady_state := SteadyStateEval.steady_state_eval_sim
VISUAL_EVAL_BUILD := $(if $(filter four_post,$(VISUAL_EVAL)),standard-build-four-post,standard-build)

DEPLOY_MODE ?= onefile
DEPLOY_INSTALL_DEPS ?= 1
DEPLOY_SKIP_CONFLICT_CHECK ?= 0
DEPLOY_VERSION ?=
DEPLOY_UPLOAD_RELEASE ?= 0
DEPLOY_TOOL := _0_Utils/deploy/deploy.py
DEPLOY_REQUIREMENTS := _0_Utils/deploy/requirements.txt
DEPLOY_ASSET_DIR := _0_Utils/deploy/assets
DEPLOY_BUILD_DIR := _0_Utils/deploy/build
DEPLOY_DIST_DIR := _0_Utils/deploy/dist
DEPLOY_OUTPUT_DIR := $(DEPLOY_DIST_DIR)/BobSim/$(DEPLOY_MODE)
DEPLOY_INSTALL_DEPS_ARG := $(if $(filter 1 true yes,$(DEPLOY_INSTALL_DEPS)),--install-deps,)
DEPLOY_SKIP_CONFLICT_CHECK_ARG := $(if $(filter 1 true yes,$(DEPLOY_SKIP_CONFLICT_CHECK)),--skip-conflict-check,)
DEPLOY_VERSION_ARG := $(if $(DEPLOY_VERSION),--version $(DEPLOY_VERSION),)
DEPLOY_UPLOAD_RELEASE_ARG := $(if $(filter 1 true yes,$(DEPLOY_UPLOAD_RELEASE)),--upload-release,)

# cmd.exe cannot parse this POSIX test. A Windows host is never in the container.
ifeq ($(OS),Windows_NT)
IN_CONTAINER :=
else
IN_CONTAINER := $(shell if [ -f /.dockerenv ]; then printf 1; fi)
endif

ifeq ($(IN_CONTAINER),1)
RUN :=
DOCKER_BUILD_CMD := @echo "Already inside the BobSim container."
DOCKER_REBUILD_CMD := @echo "Already inside the BobSim container."
SHELL_BOBSIM_CMD := bash
SHELL_STANDARD_CMD := cd _3_StandardSim && bash
SHELL_ENVELOPE_CMD := cd _2_EnvelopeSim && bash
SHELL_OPT_CMD := cd _4_OptSim && bash
else
# cmd.exe cannot parse the POSIX probe, so Windows uses `docker compose` directly.
ifeq ($(OS),Windows_NT)
COMPOSE ?= docker compose
else
COMPOSE ?= $(shell if docker compose version >/dev/null 2>&1; then printf "docker compose"; elif command -v docker-compose >/dev/null 2>&1; then printf "docker-compose"; else printf "docker compose"; fi)
endif
RUN := $(COMPOSE) run --rm -T bobsim
DOCKER_BUILD_CMD := $(COMPOSE) build
DOCKER_REBUILD_CMD := $(COMPOSE) build --no-cache
SHELL_BOBSIM_CMD := $(COMPOSE) run --rm bobsim bash
SHELL_STANDARD_CMD := $(COMPOSE) run --rm standard bash
SHELL_ENVELOPE_CMD := $(COMPOSE) run --rm envelope bash
SHELL_OPT_CMD := $(COMPOSE) run --rm opt bash
endif

# The app needs a network to publish its port, so it uses the app service, not
# bobsim. Recursive so that `make app RUN=` also runs the app on the host.
APP_PORT ?= 8765
APP_RUN = $(if $(RUN),$(COMPOSE) run --rm -p 127.0.0.1:$(APP_PORT):8765 app,)

WORKSPACE ?= $(if $(RUN),/workspace,$(CURDIR))
CLEAN_WORKSPACE ?= $(CURDIR)
CLEAN_DOCKER_IMAGE ?= bobdyn/bobsim:latest

.DEFAULT_GOAL := help

.PHONY: help init docker-build docker-rebuild \
	visual-demo visual-capture visual-rig visual-maneuver \
	app deploy deploy-deps deploy-assets deploy-package deploy-release deploy-clean \
	lint typecheck test regression-invariants regression-baseline ci \
	shell shell-bobsim shell-standard shell-envelope shell-opt \
	sync-vehicle sync-vehicle-write standard-build standard-build-four-post standard-regression-four-post \
	standard-eval-ramp-steer standard-eval-steady-state standard-eval-transient standard-eval-four-post standard-eval-all reduced-eval reduced-fidelity-suite reduced-suspension-correlation reduced-kinematics-benchmark \
	lap-eval lap-eval-qss lap-eval-transient lap-eval-all-dof \
	lap-validation-visuals \
	envelope-ggv envelope-ymd envelope-all \
	opt-standard opt-standard-setup opt-standard-architecture \
	opt-envelope opt-refined opt-search opt-solve opt-trade opt-doe-smoke \
	clean clean-app clean-visual clean-standard clean-envelope clean-opt clean-owned clean-all

ifeq ($(OS),Windows_NT)
help:
	@$(PYTHON) _0_Utils/print_make_help.py
else
help:
	@printf '%s\n' \
		'BobSim targets:' \
		'' \
		'  init                      Initialize submodules' \
		'  docker-build              Build the Docker development image' \
		'  docker-rebuild            Rebuild the Docker image from scratch' \
		'  app                       Open the BobSim browser app in Docker' 		'      APP_PORT=8765 sets the host port, RUN= runs it on the host' \
		'' \
		'  BobVis - scenes for the Replay tab. Write one, then open the app.' \
		'  visual-maneuver           Simulate a VehicleSim manoeuvre and write its scene' \
		'  visual-rig                Simulate the four-post rig and write its scene' \
		'  visual-demo               Synthetic scene, no simulation needed' \
		'  visual-capture            Simulate VISUAL_EVAL and write its scene' \
		'' \
		'  Visual variables:' \
		'    VISUAL_MANEUVER=<name>               transient (default), ramp_steer, steady_state' \
		'    VISUAL_EVAL=<name>                   four_post (default) or a manoeuvre' \
		'    example: make visual-rig && make app' \
		'' \
		'  deploy                    Build the BobSim desktop executable/app bundle' \
		'  deploy-deps               Install deploy packaging dependencies' \
		'  deploy-assets             Generate BobSim icon assets' \
		'  deploy-package            Package the current deploy artifact for release' \
		'  deploy-release            Clean, build, and package a release artifact' \
		'  deploy-clean              Remove deploy build outputs' \
		'' \
		'  Deploy variables:' \
		'    DEPLOY_MODE=onefile|onedir           Default: onefile' \
		'    DEPLOY_INSTALL_DEPS=1|0              Default: 1' \
		'    DEPLOY_SKIP_CONFLICT_CHECK=1|0       Default: 0' \
		'    DEPLOY_VERSION=<version>             Optional release package version' \
		'    DEPLOY_UPLOAD_RELEASE=1|0            Upload package with GitHub CLI' \
		'    output: _0_Utils/deploy/dist/BobSim/$(DEPLOY_MODE)' \
		'' \
		'  shell                     Open the main BobSim shell' \
		'  shell-standard            Open a StandardSim shell' \
		'  shell-envelope            Open an EnvelopeSim shell' \
		'  shell-opt                 Open an OptSim shell' \
		'' \
		'  sync-vehicle              Report whether the BobLib records match vehicle.yml' \
		'  sync-vehicle-write        Regenerate those records from vehicle.yml' \
		'' \
		'  standard-build            Build BobLib VehicleSim' \
		'  standard-build-four-post  Build BobLib FourPostSim' \
		'  shark-overlay             Overlay the imported car against Orion on the kinematic' \
		'                            curves. [SHARK=file.shk] to import first.' \
		'                            ARGS=--four-post adds the experimental force sim;' \
		'                            --actuation imported uses the variant actuation instead' \
		'                            of holding the baseline constant; --tol-deg/--tol-mm set' \
		'                            the engineering tolerances used for ranking.' \
		'' \
		'  standard-eval-ramp-steer   Run RampSteerEval' \
		'  standard-eval-steady-state Run SteadyStateEval' \
		'  standard-eval-transient    Run TransientEval' \
		'  standard-eval-four-post    Run FourPostEval' \
		'  standard-eval-all          Run all standard evaluations' \
		'  reduced-eval               Run N-DOF step steer; optionally compare BobLib CSV' \
		'    REDUCED_DOF=3|6|10|14 REDUCED_KINEMATICS=lookup|nonlinear' \
		'  reduced-fidelity-suite     Overlay 3/6/10/14DOF discriminating maneuvers' \
		'    REDUCED_MBD_DIR=<directory containing one BobLib CSV per case>' \
		'  reduced-suspension-correlation Compare instant links with BobLib FourPost metrics' \
		'  reduced-kinematics-benchmark Compare lookup grids with in-loop nonlinear kinematics' \
		'  lap-eval                   Run QSS optimization and forward-transient lap' \
		'  lap-eval-qss               Run QSS racing-line and speed optimization only' \
		'  lap-eval-transient         Run transient lap against the optimized QSS reference' \
		'  lap-eval-all-dof           Run QSS and transient laps for 3/6/10/14DOF' \
		'  lap-validation-visuals     Validate all DOFs; write QSS/transient figures under temp/' \
		'    LAP_CONFIG=<path> LAP_SCENARIO=qss|transient|both LAP_DOF=3|6|10|14' \
		'' \
		'  envelope-ggv              Generate the GGV envelope' \
		'  envelope-ymd              Generate the YMD envelope' \
		'  envelope-all              Generate all envelope outputs' \
		'' \
		'  opt-doe-smoke             Check DOE plumbing without OpenModelica' \
		'  opt-standard              Run StandardSens pre-screen sensitivities' \
		'  opt-standard-setup        Pre-screen over setup parameters only' \
		'  opt-standard-architecture Pre-screen over architecture parameters only' \
		'  opt-envelope              Run EnvelopeSens sensitivities' \
		'  opt-refined               Run StandardSens refined response surfaces' \
		'  opt-search                Reverse lookup: target metrics -> vehicle parameters' \
		'  opt-solve                 Solve for the setup that hits target metrics, then simulate it' \
		'  opt-trade                 Compare named vehicles across the standard sims' \
		'' \
		'  Search variables:' \
		'    METRICS="NAME=VALUE ..."             Required target metrics' \
		'    SEARCH_TOP=<n>                       Nearest variants to return. Default: 1' \
		'    TARGETS="NAME=VALUE ..."             opt-solve targets. Default: configs/solve_config.yaml' \
		'    KNOBS="path ..."                     opt-solve knobs. Default: configs/solve_config.yaml' \
		'    STUDY=<path>                         opt-trade study. Default: configs/trade_study.yaml' \
		'' \
		'  DOE sweep variables (default: configs/vehicle_architecture.yaml):' \
		'    DOE_METHOD=lhs|interval_splice       Sampling method' \
		'    DOE_SAMPLES=<n>                      LHS samples (plus baseline)' \
		'    DOE_INTERVALS=<n>                    interval_splice intervals' \
		'    DOE_SCOPE=all|setup|architecture     Swept parameter scope. Default: all' \
		'    example: make opt-standard DOE_METHOD=lhs DOE_SAMPLES=3' \
		'' \
		'  regression-invariants     Check current regression artifacts for physical consistency' \
		'  regression-baseline       Run full default StandardSim baseline simulations' \
		'  standard-regression-four-post  Alias for regression-baseline' \
		'' \
		'  ci                        Run lint, typecheck, and tests' \
		'  clean                     Remove local Python/tool caches' \
		'  clean-app                 Remove generated app configs/workspaces' \
		'  clean-visual             Remove generated VisualSim artifacts' \
		'  clean-standard           Remove generated StandardSim artifacts' \
		'  clean-envelope           Remove generated EnvelopeSim artifacts' \
		'  clean-opt                Remove generated OptSim artifacts' \
		'  clean-owned               Remove root-owned generated artifacts via no-network Docker' \
		'  clean-all                 Remove caches and generated workflow artifacts'
endif

init:
	git submodule update --init --recursive

docker-build:
	$(DOCKER_BUILD_CMD)

docker-rebuild:
	$(DOCKER_REBUILD_CMD)

app:
	$(if $(APP_RUN),@echo BobSim app in Docker. Open http://127.0.0.1:$(APP_PORT),)
	$(APP_RUN) $(PYTHON) -m _5_App.app $(if $(APP_RUN),--host 0.0.0.0 --port 8765,--port $(APP_PORT))

# Normal evaluation CSVs have no geometry. This re-runs VISUAL_EVAL with the
# suspension frames and converts the result to a scene.
visual-capture: $(VISUAL_EVAL_BUILD)
	$(RUN) $(PYTHON) -m _1_VisualSim.capture config $(VISUAL_CAPTURE)_capture_config.yml --eval $(VISUAL_EVAL)
	$(RUN) $(PYTHON) -m _3_StandardSim.$(VISUAL_EVAL_MODULE_$(VISUAL_EVAL)) $(VISUAL_CAPTURE)_capture_config.yml
	$(RUN) $(PYTHON) -m _1_VisualSim.capture convert $(VISUAL_CAPTURE)_capture_config.yml \
		--npz $(VISUAL_CAPTURE)_visual.npz --template $(VISUAL_CAPTURE)_visual.yml
	@printf '%s\n' 'Scene written. Open it with: make app, then the Replay tab.'

# The four-post rig: suspension travel with the car held still.
visual-rig:
	$(MAKE) visual-capture VISUAL_EVAL=four_post

visual-maneuver:
	$(MAKE) visual-capture VISUAL_EVAL=$(VISUAL_MANEUVER)

# The demo scene is generated, never committed, so build it whenever it is
# missing. Both outputs come from one run of the generator.
$(VISUAL_DEMO_CONFIG) $(VISUAL_DEMO_DATA):
	$(RUN) $(PYTHON) -m _1_VisualSim.demo --out-dir $(VISUAL_RESULTS)

visual-demo: $(VISUAL_DEMO_CONFIG) $(VISUAL_DEMO_DATA)
	@printf '%s\n' 'Synthetic scene written. Open it with: make app, then the Replay tab.'

deploy:
	$(PYTHON) $(DEPLOY_TOOL) --clean
	$(PYTHON) $(DEPLOY_TOOL) --preflight-only $(DEPLOY_SKIP_CONFLICT_CHECK_ARG)
	$(PYTHON) $(DEPLOY_TOOL) --mode $(DEPLOY_MODE) $(DEPLOY_INSTALL_DEPS_ARG) $(DEPLOY_SKIP_CONFLICT_CHECK_ARG)
	@printf '%s\n' 'Deploy output: $(DEPLOY_OUTPUT_DIR)'

deploy-deps:
	$(PYTHON) -m pip install -r $(DEPLOY_REQUIREMENTS)

deploy-assets:
	$(PYTHON) $(DEPLOY_TOOL) --assets-only $(DEPLOY_INSTALL_DEPS_ARG)

deploy-package:
	$(PYTHON) $(DEPLOY_TOOL) --package-release --mode $(DEPLOY_MODE) $(DEPLOY_VERSION_ARG) $(DEPLOY_UPLOAD_RELEASE_ARG)

deploy-release:
	$(PYTHON) $(DEPLOY_TOOL) --release --mode $(DEPLOY_MODE) $(DEPLOY_INSTALL_DEPS_ARG) $(DEPLOY_SKIP_CONFLICT_CHECK_ARG) $(DEPLOY_VERSION_ARG) $(DEPLOY_UPLOAD_RELEASE_ARG)

deploy-clean:
	rm -rf $(DEPLOY_DIST_DIR) $(DEPLOY_BUILD_DIR) $(DEPLOY_ASSET_DIR)

lint:
	$(RUN) env RUFF_CACHE_DIR=$(RUFF_CACHE_DIR) $(PYTHON) -m ruff check $(QUALITY_DIRS) --exclude $(BOBLIB_PATH)

typecheck:
	$(RUN) $(PYTHON) -m mypy $(TYPECHECK_DIRS) \
		--ignore-missing-imports \
		--no-strict-optional \
		--cache-dir $(MYPY_CACHE_DIR) \
		--exclude '(^|/)$(BOBLIB_PATH)/'

test:
	$(RUN) $(PYTHON) -m pytest tests

regression-invariants:
	$(RUN) $(PYTHON) -m pytest tests/test_simulation_regression.py

regression-baseline:
	$(RUN) env BOBSIM_BASELINE_REGRESSION=1 $(PYTHON) -m pytest tests/test_simulation_regression.py

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

# Reporting, not writing, is the default. The Modelica entry points read the
# checked-in BobLib records, so regenerating them is a deliberate act; what was
# missing was any way to find out whether they still match vehicle.yml.
# Host-side like app and deploy-*: pure Python, no omc.
sync-vehicle:
	$(PYTHON) -m _5_App.modelica_generator

sync-vehicle-write:
	$(PYTHON) -m _5_App.modelica_generator --write

# Records and templates hold the hardpoints. Without them, make misses geometry changes.
GENERATED_RECORDS := $(wildcard $(BOBLIB_PACKAGE_PATH)/Records/VehicleDefn/*.mo)
GENERATED_TEMPLATES := \
	$(wildcard $(BOBLIB_PACKAGE_PATH)/Experiments/Standards/Templates/Vehicle/*.mo) \
	$(wildcard $(BOBLIB_PACKAGE_PATH)/Experiments/Standards/Templates/FourPost/*.mo)

# BOBSIM_NATIVE_CFLAGS is computed inside the container so it reflects the
# container's actual architecture, not the host `make` runs on -- clang on
# AArch64 (e.g. Apple Silicon under Docker Desktop) rejects -march=native,
# an x86-ism, and needs -mcpu=native instead.
$(VEHICLE_SIM_EXE): $(VEHICLE_SIM_MODEL) $(BUILD_VEHICLE_MOS) $(BOBLIB_PACKAGE_PATH)/package.mo \
		$(GENERATED_RECORDS) $(GENERATED_TEMPLATES)
	$(RUN) bash -lc 'BOBSIM_NATIVE_CFLAGS="-O3 -march=native -mtune=native"; case "$$(uname -m)" in aarch64|arm64) BOBSIM_NATIVE_CFLAGS="-O3 -mcpu=native -mtune=native";; esac; export BOBSIM_NATIVE_CFLAGS; omc $(WORKSPACE)/$(BUILD_VEHICLE_MOS) && test -f $(WORKSPACE)/$(VEHICLE_SIM_EXE)'

$(FOUR_POST_SIM_EXE): $(FOUR_POST_SIM_MODEL) $(BUILD_FOUR_POST_MOS) $(BOBLIB_PACKAGE_PATH)/package.mo \
		$(GENERATED_RECORDS) $(GENERATED_TEMPLATES)
	$(RUN) bash -lc 'BOBSIM_NATIVE_CFLAGS="-O3 -march=native -mtune=native"; case "$$(uname -m)" in aarch64|arm64) BOBSIM_NATIVE_CFLAGS="-O3 -mcpu=native -mtune=native";; esac; export BOBSIM_NATIVE_CFLAGS; omc $(WORKSPACE)/$(BUILD_FOUR_POST_MOS) && test -f $(WORKSPACE)/$(FOUR_POST_SIM_EXE)'

# SHARK is optional. Without it, the already-imported variant is overlaid.
# Runs in the container because ARGS=--four-post needs the container-built simulator.
SHARK_ARG := $(if $(SHARK),--shark $(SHARK),)
shark-overlay:
	$(RUN) $(PYTHON) -m _3_StandardSim.FourPostEval.shark_overlay_report $(SHARK_ARG) $(ARGS)

standard-build: $(VEHICLE_SIM_EXE)

standard-build-four-post: $(FOUR_POST_SIM_EXE)

standard-eval-ramp-steer: standard-build
	$(RUN) $(PYTHON) -m _3_StandardSim.RampSteerEval.ramp_steer_eval_sim

standard-eval-steady-state: standard-build
	$(RUN) $(PYTHON) -m _3_StandardSim.SteadyStateEval.steady_state_eval_sim

standard-eval-transient: standard-build
	$(RUN) $(PYTHON) -m _3_StandardSim.TransientEval.transient_eval_sim

standard-eval-four-post: standard-build-four-post
	$(RUN) $(PYTHON) -m _3_StandardSim.FourPostEval.four_post_eval_sim

standard-eval-all: standard-eval-ramp-steer standard-eval-steady-state standard-eval-transient standard-eval-four-post

reduced-eval:
	$(RUN) $(PYTHON) -m _3_StandardSim.ReducedOrderEval.reduced_order_eval_sim \
		--dof $(REDUCED_DOF) \
		--kinematics-mode $(REDUCED_KINEMATICS) \
		$(if $(REDUCED_BOBLIB_CSV),--boblib-csv $(REDUCED_BOBLIB_CSV),)

reduced-fidelity-suite:
	$(RUN) $(PYTHON) -m _3_StandardSim.ReducedOrderEval.fidelity_suite \
		$(if $(REDUCED_MBD_DIR),--mbd-directory $(REDUCED_MBD_DIR),)

reduced-suspension-correlation:
	$(RUN) $(PYTHON) -m _3_StandardSim.ReducedOrderEval.suspension_correlation \
		--metrics $(REDUCED_SUSPENSION_METRICS)

reduced-kinematics-benchmark:
	$(RUN) $(PYTHON) -m _3_StandardSim.ReducedOrderEval.kinematics_benchmark

lap-eval:
	$(RUN) $(PYTHON) -m _3_StandardSim.LapTimeEval.lap_time_eval_sim \
		--config $(LAP_CONFIG) --scenario $(LAP_SCENARIO) \
		$(if $(LAP_DOF),--model-dof $(LAP_DOF),)

lap-eval-qss:
	$(MAKE) lap-eval LAP_SCENARIO=qss

lap-eval-transient:
	$(MAKE) lap-eval LAP_SCENARIO=transient

lap-eval-all-dof:
	$(RUN) $(PYTHON) -m _3_StandardSim.LapTimeEval.lap_time_eval_sim \
		--config $(LAP_CONFIG) --scenario $(LAP_SCENARIO) --all-dof

lap-validation-visuals:
	$(RUN) $(PYTHON) -m _3_StandardSim.LapTimeEval.validation_visuals

standard-regression-four-post: regression-baseline

envelope-ggv:
	$(RUN) $(PYTHON) -m _2_EnvelopeSim.GGV.ggv_generation

envelope-ymd:
	$(RUN) $(PYTHON) -m _2_EnvelopeSim.YMD.ymd_generation

envelope-all: envelope-ggv envelope-ymd

# Variant generation needs FourPostEval motion ratios to hold ride height.
$(FOUR_POST_METRICS):
	$(MAKE) standard-eval-four-post

opt-doe-smoke:
	$(RUN) $(PYTHON) -m pytest tests/test_doe_pipeline.py -q

opt-standard: $(FOUR_POST_METRICS)
	$(RUN) env $(DOE_ENV) PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m StandardSens.pre_screen_sensitivities

# A scope change requires 'make clean-opt'. These targets do not clean, to keep earlier results.
opt-standard-setup:
	$(MAKE) opt-standard DOE_SCOPE=setup

opt-standard-architecture:
	$(MAKE) opt-standard DOE_SCOPE=architecture

opt-envelope:
	$(RUN) env PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m EnvelopeSens.sensitivities

opt-refined:
	$(RUN) env PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m StandardSens.refined_response_surfaces

opt-search:
	@if [ -z '$(METRICS)' ]; then \
		printf '%s\n' \
			'error: METRICS is required.' \
			'' \
			'  make opt-search METRICS="SteadyStateEval_understeer_gradient_deg_per_g=0.05"' \
			'  make opt-search METRICS="MetricA=1.0 MetricB=2.0" SEARCH_TOP=5' \
			'' \
			'Requires a populated results table; run make opt-standard first.'; \
		exit 1; \
	fi
	$(RUN) env PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m StandardSens.pipeline.search --metrics $(METRICS) --top $(SEARCH_TOP)

# Solves for the setup directly and simulates the result.
opt-solve: $(FOUR_POST_METRICS)
	$(RUN) env PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m StandardSens.solve_setup $(if $(TARGETS),--targets $(TARGETS),) $(if $(KNOBS),--knobs $(KNOBS),)

# Compiles each candidate once and runs every requested standard on it.
opt-trade: $(FOUR_POST_METRICS)
	$(RUN) env PYTHONPATH=$(WORKSPACE)/_4_OptSim:$(WORKSPACE) $(PYTHON) -m StandardSens.trade_study $(if $(STUDY),--study $(STUDY),)

clean:
	bash -lc 'find $(CLEAN_WORKSPACE) -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null; \
		find $(CLEAN_WORKSPACE) -type f \( -name "*.pyc" -o -name "*.pyo" \) -delete 2>/dev/null; \
		rm -rf $(CLEAN_WORKSPACE)/.pytest_cache $(CLEAN_WORKSPACE)/.mypy_cache $(CLEAN_WORKSPACE)/.ruff_cache; \
		rm -rf $(CLEAN_WORKSPACE)/.coverage $(CLEAN_WORKSPACE)/htmlcov $(CLEAN_WORKSPACE)/build $(CLEAN_WORKSPACE)/dist; \
		find $(CLEAN_WORKSPACE) -maxdepth 2 -name "*.egg-info" -exec rm -rf {} + 2>/dev/null; \
		echo "Python/tool caches cleaned"'

# Everything the app generates lives under _5_App/user_data/. These are the leaf
# directories _5_App/storage.py declares and the app recreates on launch, so
# emptying them resets app state without touching the checked-in study configs.
# Emptying config/active is what "reset every study config to the shipped one"
# means now.
APP_USER_DATA_DIRS := \
	_5_App/user_data/cache/modelica \
	_5_App/user_data/config/active \
	_5_App/user_data/config/app \
	_5_App/user_data/config/defaults \
	_5_App/user_data/config/simulations \
	_5_App/user_data/config/vehicles \
	_5_App/user_data/results/saved \
	_5_App/user_data/workspaces/vehicles

clean-app:
	bash -lc 'for path in $(addprefix $(CLEAN_WORKSPACE)/,$(APP_USER_DATA_DIRS)); do \
		mkdir -p "$$path"; \
		find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} + 2>/dev/null || true; \
		done; \
		echo "App-generated configs/workspaces cleaned"'

clean-visual:
	bash -lc 'for path in $(CLEAN_WORKSPACE)/_1_VisualSim/results; do \
		mkdir -p "$$path"; \
		find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} + 2>/dev/null || true; \
		done; \
		rm -f $(CLEAN_WORKSPACE)/_1_VisualSim/*_visual.npz; \
		echo "VisualSim artifacts cleaned (including any generated demo scene)"'

clean-standard:
	bash -lc 'for path in \
		$(CLEAN_WORKSPACE)/_3_StandardSim/Build \
		$(CLEAN_WORKSPACE)/_3_StandardSim/BuildBobLib \
		$(CLEAN_WORKSPACE)/_3_StandardSim/generated_results \
		$(CLEAN_WORKSPACE)/_3_StandardSim/results; do \
		mkdir -p "$$path"; \
		if [ -d "$$path" ]; then find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} + 2>/dev/null || true; fi; \
		done; echo "StandardSim artifacts cleaned"'

clean-envelope:
	bash -lc 'for path in $(CLEAN_WORKSPACE)/_2_EnvelopeSim/Build $(CLEAN_WORKSPACE)/_2_EnvelopeSim/results; do \
		mkdir -p "$$path"; \
		if [ -d "$$path" ]; then find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} + 2>/dev/null || true; fi; \
		done; echo "EnvelopeSim artifacts cleaned"'

clean-opt:
	bash -lc 'for path in \
		$(CLEAN_WORKSPACE)/_4_OptSim/Build \
		$(CLEAN_WORKSPACE)/_4_OptSim/StandardSens/results \
		$(CLEAN_WORKSPACE)/_4_OptSim/EnvelopeSens/results \
		$(CLEAN_WORKSPACE)/_4_OptSim/population \
		$(CLEAN_WORKSPACE)/_4_OptSim/population_refined \
		$(CLEAN_WORKSPACE)/_4_OptSim/results; do \
		mkdir -p "$$path"; \
		if [ -d "$$path" ]; then find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} + 2>/dev/null || true; fi; \
		done; echo "OptSim artifacts cleaned"'

clean-owned:
	@if command -v docker >/dev/null 2>&1 && docker image inspect $(CLEAN_DOCKER_IMAGE) >/dev/null 2>&1; then \
		if docker run --rm --network none -v $(CLEAN_WORKSPACE):/workspace -w /workspace $(CLEAN_DOCKER_IMAGE) bash -lc 'for path in \
			_1_VisualSim/results \
			_2_EnvelopeSim/Build \
			_2_EnvelopeSim/results \
			_3_StandardSim/Build \
			_3_StandardSim/BuildBobLib \
			_3_StandardSim/generated_results \
			_3_StandardSim/results \
			_4_OptSim/Build \
			_4_OptSim/EnvelopeSens/results \
			_4_OptSim/StandardSens/results \
			_4_OptSim/population \
			_4_OptSim/population_refined \
			_4_OptSim/results \
			$(APP_USER_DATA_DIRS); do \
			mkdir -p "$$path"; \
			find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} +; \
			done; \
			rm -f _1_VisualSim/*_visual.npz'; then \
			echo 'Root-owned generated artifacts cleaned'; \
		else \
			echo 'warning: root-owned generated artifact cleanup failed'; \
		fi; \
	else \
		echo 'Docker cleanup fallback skipped'; \
	fi

clean-all: clean clean-app clean-visual clean-standard clean-envelope clean-opt clean-owned
