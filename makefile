.PHONY: clean setup sim sim-knc sim-iso

# ── Setup ────────────────────────────────────────────────────────────────────

setup:
	# First time setup - builds docker environment
	docker compose build

# ── Simulations ──────────────────────────────────────────────────────────────

sim:
	# Default sim - runs full DOE pipeline
	docker compose run doe python _4_DOE/run_doe.py configs/doe_config.yaml

sim-knc:
	# K&C sweep - front and rear kinematics and compliance
	docker compose run doe python _4_DOE/run_doe.py configs/knc_sweep.yaml

sim-iso:
	# Steady state cornering sweep (ISO4138)
	docker compose run doe python _4_DOE/run_doe.py configs/iso4138_sweep.yaml

# TODO: hook into GeneralSim/StandardSim entry points once merged
# TODO: add sim-transient for ISO8726 once StandardSim supports it

ISO4138:
	omc ./ISO4138/ISO4138.mos
	python3 -m ISO4138.run_ISO4138

# ── Clean ────────────────────────────────────────────────────────────────────

clean:
	@echo "Cleaning Python + simulation artifacts..."

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

	# DOE artifacts
	rm -rf _4_DOE/population/* _4_DOE/results/*

	# OpenModelica temp junk
	rm -rf ~/.openmodelica/tmp/* 2>/dev/null || true

	@echo "Clean complete"