"""The dev image's build cache only works if compose reads what CI publishes."""

from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[1]


def test_compose_reuses_the_published_image_layers():
    compose = yaml.safe_load((ROOT / "docker-compose.yml").read_text())
    build = compose["services"]["bobsim"]["build"]
    workflow = yaml.safe_load((ROOT / ".github/workflows/image.yml").read_text())
    push = next(
        step["with"]
        for step in workflow["jobs"]["publish"]["steps"]
        if step.get("uses", "").startswith("docker/build-push-action")
    )
    published = push["tags"].split()
    assert build["cache_from"][0] in published
    # Compose can only reuse layers that carry their cache metadata.
    assert push["cache-to"] == "type=inline"
    # The image must be rebuilt whenever an input to it changes.
    triggers = workflow[True]["push"]["paths"]
    assert {"Dockerfile", "requirements.txt"} <= set(triggers)
