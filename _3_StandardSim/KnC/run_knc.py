from pathlib import Path
import yaml

from _3_StandardSim.KnC.knc_sim import KnCSim


def _to_serializable(obj):
    if hasattr(obj, "tolist"):
        return obj.tolist()
    return obj


def main():
    config_path = Path(__file__).with_name("knc_config.yml")

    with open(config_path, "r") as f:
        cfg = yaml.safe_load(f)

    sim = KnCSim(cfg)

    print("🚀 Running KnC simulation...")
    result = sim.run()
    print("✅ Done")
    print("Summary:", result["summary"])

if __name__ == "__main__":
    main()