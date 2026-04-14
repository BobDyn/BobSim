.PHONY: clean

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

	# OpenModelica temp junk (very helpful)
	rm -rf ~/.openmodelica/tmp/* 2>/dev/null || true

	@echo "Clean complete"

clean_build:
	@echo "Cleaning all build directories under _3_StandardSim..."
	@find _3_StandardSim -type d -name "build" -exec sh -c 'rm -rf "$$1"/* "$$1"/.[!.]* "$$1"/..?*' _ {} \;

ISO4138:
	omc _3_StandardSim/ISO4138/build.mos
	python3 -m _3_StandardSim.run_standard _3_StandardSim/ISO4138/iso4138_config.yml

KnC:
	omc _3_StandardSim/KnC/build.mos
	python3 -m _3_StandardSim.run_standard _3_StandardSim/KnC/knc_config.yml