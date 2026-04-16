.PHONY: setup shell-doe shell-standard sim-doe sim-knc sim-iso clean

# ── Setup ──────────────────────────────────────────────────────────────────
# Init submodules (BobLib) then build the Docker image

init:
	git submodule update --init --recursive

setup:
	docker compose build

rebuild:
	docker compose build --no-cache

# ── Shells ─────────────────────────────────────────────────────────────────
# Drop into a bash terminal inside the container for debugging/manual runs
# make shell-doe     → bash inside _4_DOE
# make shell-standard → bash inside _3_StandardSim

shell-doe:
	docker compose run --rm doe bash

shell-standard:
	docker compose run --rm standard bash

# ── DOE ────────────────────────────────────────────────────────────────────

sim-doe:
	docker compose run --rm doe python run_doe.py configs/doe_config.yaml

# ── Standard sims ──────────────────────────────────────────────────────────

sim-knc:
	docker compose run --rm standard python run_standard.py KnC/knc_config.yml

sim-iso:
	docker compose run --rm standard python run_standard.py ISO4138/iso4138_config.yml

# ── Clean ──────────────────────────────────────────────────────────────────
# Removes Python artifacts, simulation outputs, and OMC temp files
# Does NOT delete compile_error_*.log files so failures are preserved for debugging

clean:
	@echo "Cleaning Python + simulation artifacts..."
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type f -name "*.pyc" -delete
	find . -type f -name "*.pyo" -delete
	rm -rf .pytest_cache .mypy_cache .ruff_cache
	rm -rf .coverage htmlcov
	rm -rf build dist *.egg-info
	find . -type f -name "*.csv" -delete
	find . -type f -name "*.mat" -delete
	rm -rf _4_DOE/population/* _4_DOE/results/*
	rm -rf _3_StandardSim/ISO4138/build _3_StandardSim/KnC/build
	rm -rf ~/.openmodelica/tmp/* 2>/dev/null || true
	@echo "Clean complete"