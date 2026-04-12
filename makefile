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

ISO4138:
	omc ./ISO4138/ISO4138.mos
	python3 -m ISO4138.run_ISO4138