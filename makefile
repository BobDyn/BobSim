PYTHON ?= python
RUFF_CACHE_DIR ?= /tmp/bobsim-ruff-cache
MYPY_CACHE_DIR ?= /tmp/bobsim-mypy-cache

QUALITY_DIRS := _0_Utils _1_VisualSim _2_EnvelopeSim _3_StandardSim _4_OptSim _5_App tests
TYPECHECK_DIRS := _0_Utils _1_VisualSim _3_StandardSim _5_App tests
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
CLEAN_WORKSPACE ?= $(CURDIR)
CLEAN_DOCKER_IMAGE ?= bobdyn/bobsim:latest

.DEFAULT_GOAL := help

.PHONY: help init docker-build docker-rebuild \
	app deploy deploy-deps deploy-assets deploy-package deploy-release deploy-clean \
	lint typecheck test regression-invariants regression-baseline ci \
	shell shell-bobsim shell-standard shell-envelope shell-opt \
	sync-vehicle standard-build standard-build-four-post standard-regression-four-post \
	standard-eval-ramp-steer standard-eval-steady-state standard-eval-transient standard-eval-four-post standard-eval-fbrc standard-eval-all \
	envelope-ggv envelope-ymd envelope-all \
	opt-standard opt-envelope opt-refined \
	clean clean-app clean-visual clean-standard clean-envelope clean-opt clean-owned clean-all

help:
	@printf '%s\n' \
		'BobSim targets:' \
		'' \
		'  init                      Initialize submodules' \
		'  docker-build              Build the Docker development image' \
		'  docker-rebuild            Rebuild the Docker image from scratch' \
		'  app                       Open the BobSim browser app' \
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
		'  standard-build            Build BobLib VehicleSim' \
		'  standard-build-four-post  Build BobLib FourPostSim' \
		'' \
		'  standard-eval-ramp-steer   Run RampSteerEval' \
		'  standard-eval-steady-state Run SteadyStateEval' \
		'  standard-eval-transient    Run TransientEval' \
		'  standard-eval-four-post    Run FourPostEval' \
		'  standard-eval-fbrc         Run FbrcEval' \
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

init:
	git submodule update --init --recursive

docker-build:
	$(DOCKER_BUILD_CMD)

docker-rebuild:
	$(DOCKER_REBUILD_CMD)

app:
	$(PYTHON) -m _5_App.app

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

sync-vehicle:
	@printf '%s\n' 'Static BobLib models use checked-in Modelica records; vehicle.yml remains a BobSim projection/report input.'

$(VEHICLE_SIM_EXE): $(VEHICLE_SIM_MODEL) $(BUILD_VEHICLE_MOS) $(BOBLIB_PACKAGE_PATH)/package.mo
	$(RUN) bash -lc 'omc $(WORKSPACE)/$(BUILD_VEHICLE_MOS) && test -f $(WORKSPACE)/$(VEHICLE_SIM_EXE)'

$(FOUR_POST_SIM_EXE): $(FOUR_POST_SIM_MODEL) $(BUILD_FOUR_POST_MOS) $(BOBLIB_PACKAGE_PATH)/package.mo
	$(RUN) bash -lc 'omc $(WORKSPACE)/$(BUILD_FOUR_POST_MOS) && test -f $(WORKSPACE)/$(FOUR_POST_SIM_EXE)'

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

standard-eval-fbrc: standard-build
	$(RUN) $(PYTHON) -m _3_StandardSim.FbrcEval.fbrc_eval_sim

standard-eval-all: standard-eval-ramp-steer standard-eval-steady-state standard-eval-transient standard-eval-four-post standard-eval-fbrc

standard-regression-four-post: regression-baseline

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
	bash -lc 'find $(CLEAN_WORKSPACE) -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null; \
		find $(CLEAN_WORKSPACE) -type f \( -name "*.pyc" -o -name "*.pyo" \) -delete 2>/dev/null; \
		rm -rf $(CLEAN_WORKSPACE)/.pytest_cache $(CLEAN_WORKSPACE)/.mypy_cache $(CLEAN_WORKSPACE)/.ruff_cache; \
		rm -rf $(CLEAN_WORKSPACE)/.coverage $(CLEAN_WORKSPACE)/htmlcov $(CLEAN_WORKSPACE)/build $(CLEAN_WORKSPACE)/dist; \
		find $(CLEAN_WORKSPACE) -maxdepth 2 -name "*.egg-info" -exec rm -rf {} + 2>/dev/null; \
		echo "Python/tool caches cleaned"'

clean-app:
	bash -lc 'for path in \
		$(CLEAN_WORKSPACE)/_5_App/build_archive \
		$(CLEAN_WORKSPACE)/_5_App/saved_results \
		$(CLEAN_WORKSPACE)/_5_App/settings \
		$(CLEAN_WORKSPACE)/_5_App/vehicle_workspaces; do \
		mkdir -p "$$path"; \
		find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} + 2>/dev/null || true; \
		done; \
		mkdir -p $(CLEAN_WORKSPACE)/_5_App/sim_configs $(CLEAN_WORKSPACE)/_5_App/vehicle_configs; \
		find $(CLEAN_WORKSPACE)/_5_App/sim_configs -mindepth 1 -maxdepth 1 ! -name "_defaults" -exec rm -rf {} + 2>/dev/null || true; \
		find $(CLEAN_WORKSPACE)/_5_App/vehicle_configs -mindepth 1 ! -name ".gitkeep" -exec rm -rf {} + 2>/dev/null || true; \
		echo "App-generated configs/workspaces cleaned"'

clean-visual:
	bash -lc 'for path in $(CLEAN_WORKSPACE)/_1_VisualSim/results; do \
		mkdir -p "$$path"; \
		find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} + 2>/dev/null || true; \
		done; \
		rm -f $(CLEAN_WORKSPACE)/_1_VisualSim/*_visual.npz; \
		echo "VisualSim artifacts cleaned"'

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
			_5_App/build_archive \
			_5_App/saved_results \
			_5_App/settings \
			_5_App/vehicle_workspaces; do \
			mkdir -p "$$path"; \
			find "$$path" -mindepth 1 -maxdepth 1 ! -name ".gitkeep" -exec rm -rf {} +; \
			done; \
			mkdir -p _5_App/sim_configs _5_App/vehicle_configs; \
			find _5_App/sim_configs -mindepth 1 -maxdepth 1 ! -name "_defaults" -exec rm -rf {} +; \
			find _5_App/vehicle_configs -mindepth 1 ! -name ".gitkeep" -exec rm -rf {} +; \
			rm -f _1_VisualSim/*_visual.npz'; then \
			echo 'Root-owned generated artifacts cleaned'; \
		else \
			echo 'warning: root-owned generated artifact cleanup failed'; \
		fi; \
	else \
		echo 'Docker cleanup fallback skipped'; \
	fi

clean-all: clean clean-app clean-visual clean-standard clean-envelope clean-opt clean-owned
