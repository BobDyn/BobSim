.PHONY: clean setup sim sim-knc sim-iso

setup:
	docker compose build

sim:
	docker compose run --rm doe python run_doe.py ../configs/doe_config.yaml

sim-knc:
	docker compose run --rm doe python run_doe.py ../configs/knc_sweep.yaml

sim-iso:
	docker compose run --rm doe python run_doe.py ../configs/iso4138_sweep.yaml

ISO4138:
	omc ./ISO4138/ISO4138.mos
	python3 -m ISO4138.run_ISO4138

clean:
	@echo "Cleaning Python + simulation artifacts..."
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type f -name "*.pyc" -delete
	find . -type f -name "*.pyo" -delete
	rm -rf .pytest_cache .mypy_cache .ruff_cache
	rm -rf .coverage htmlcov
	rm -rf build dist *.egg-info
	rm -rf results
	find . -type f -name "*.csv" -delete
	find . -type f -name "*.mat" -delete
	find . -type f -name "*.log" -delete
	rm -rf _4_DOE/population/* _4_DOE/results/*
	rm -rf ~/.openmodelica/tmp/* 2>/dev/null || true
	@echo "Clean complete"