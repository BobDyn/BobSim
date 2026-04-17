DOCKER_RUN := docker run --rm -v "$(CURDIR):/bobsim" openmodelica/openmodelica:v1.26.3-ompython

.PHONY: init setup rebuild shell-doe shell-standard sim-doe sim-knc sim-iso clean-doe clean

# ── Setup ──────────────────────────────────────────────────────────────────

init:
	git submodule update --init --recursive

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

clean-doe-population:
	@echo "Cleaning DOE population contents (preserving .gitkeep)..."
	@if [ -d _4_DOE/population ]; then \
		find _4_DOE/population -mindepth 1 -type f ! -name ".gitkeep" -delete; \
		find _4_DOE/population -mindepth 1 -type d -empty -delete; \
	fi

clean-doe-results:
	@echo "Cleaning DOE results contents (preserving .gitkeep)..."
	@if [ -d _4_DOE/results ]; then \
		find _4_DOE/results -mindepth 1 -type f ! -name ".gitkeep" -delete; \
		find _4_DOE/results -mindepth 1 -type d -empty -delete; \
	fi

clean-doe: clean-doe-population clean-doe-results
	@true

clean:
	$(DOCKER_RUN) bash -c "\
		find /bobsim -type d -name '__pycache__' -exec rm -rf {} + ; \
		find /bobsim -type f -name '*.pyc' -delete ; \
		find /bobsim -type f -name '*.pyo' -delete ; \
		find /bobsim/_4_DOE/population -mindepth 1 ! -name '.gitkeep' -delete ; \
		find /bobsim/_4_DOE/results    -mindepth 1 ! -name '.gitkeep' -delete ; \
		find /bobsim/_3_StandardSim    -type d -name 'build' -exec rm -rf {} +"
