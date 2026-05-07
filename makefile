DOCKER_RUN := docker run --rm -v "$(CURDIR):/bobsim" openmodelica/openmodelica:v1.26.3-ompython

.PHONY: init setup rebuild shell-doe shell-standard sim-doe sim-knc sim-iso clean-doe clean

# ── Setup ──────────────────────────────────────────────────────────────────

init:
	git submodule update --init --recursive

msl-setup:
	mkdir -p ~/.openmodelica/libraries

	curl -L \
	--retry 10 \
	--retry-delay 5 \
	--connect-timeout 60 \
	--max-time 600 \
	-o ~/.openmodelica/libraries/index.json \
	https://libraries.openmodelica.org/index/v1/index.json

setup:
	docker compose build

rebuild:
	docker compose build --no-cache

# ── Shells ─────────────────────────────────────────────────────────────────

shell-doe:
	docker compose run --rm doe bash

shell-standard:
	docker compose run --rm standard bash

# ── Sims ───────────────────────────────────────────────────────────────────

sim-doe:
	docker compose run --rm doe python run_doe.py

sim-knc:
	docker compose run --rm standard python run_standard.py KnC/knc_config.yml

sim-iso:
	docker compose run --rm standard python run_standard.py ISO4138/iso4138_config.yml

# ── Clean ──────────────────────────────────────────────────────────────────
# Uses docker run directly (not compose) to avoid Windows TTY hang.
# compile_error_*.log files are preserved for debugging.

clean-doe:
	$(DOCKER_RUN) bash -c "\
		find /bobsim/_4_DOE/population -mindepth 1 ! -name '.gitkeep' -delete && \
		find /bobsim/_4_DOE/results    -mindepth 1 ! -name '.gitkeep' -delete"

clean:
	$(DOCKER_RUN) bash -c "\
		find /bobsim -type d -name '__pycache__' -exec rm -rf {} + ; \
		find /bobsim -type f -name '*.pyc' -delete ; \
		find /bobsim -type f -name '*.pyo' -delete ; \
		find /bobsim/_4_DOE/population -mindepth 1 ! -name '.gitkeep' -delete ; \
		find /bobsim/_4_DOE/results    -mindepth 1 ! -name '.gitkeep' -delete ; \
		find /bobsim/_3_StandardSim    -type d -name 'build' -exec rm -rf {} +"

	# Python caches
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type f -name "*.pyc" -delete
	find . -type f -name "*.pyo" -delete

	# Test / coverage
	rm -rf .pytest_cache .mypy_cache .ruff_cache
	rm -rf .coverage htmlcov

	# Build artifacts
	rm -rf build dist *.egg-info

	# Modelica / sim outputs
	rm -rf results
	find . -type f -name "*.csv" -delete
	find . -type f -name "*.mat" -delete
	find . -type f -name "*.log" -delete

	# OpenModelica temp junk (very helpful)
	rm -rf ~/.openmodelica/tmp/* 2>/dev/null || true

	@echo "Clean complete"

clean_build:
	@echo "Cleaning all build directories under _3_StandardSim..."
	@find _3_StandardSim -type d -name "Build" -exec sh -c 'rm -rf "$$1"/* "$$1"/.[!.]* "$$1"/..?*' _ {} \;

clean_results:
	@echo "Cleaning all result directories under _3_StandardSim..."
	@find _3_StandardSim -type d -name "results" -exec sh -c 'rm -rf "$$1"/* "$$1"/.[!.]* "$$1"/..?*' _ {} \;

# omc _3_StandardSim/build.mos
ISO4138:
	python3 -m _3_StandardSim.ISO4138.iso4138_sim

ISO7401:
	python3 -m _3_StandardSim.ISO7401.iso7401_sim
