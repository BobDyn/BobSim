from dataclasses import dataclass
from typing import Callable, Dict, List, Optional


Validator = Callable[[object, Dict[str, object]], None]
Extractor = Callable[[object, Dict[str, object]], Dict[str, float]]


@dataclass
class OutputSchema:
    signals: List[str]
    mode: str = "steady"
    validator: Optional[Validator] = None
    extractor: Optional[Extractor] = None

    def build_filter(self) -> str:
        return "|".join(["time"] + self.signals)

    def validate(self, sim, data):
        if self.validator:
            self.validator(sim, data)

    def extract(self, sim, data):
        if self.extractor:
            return self.extractor(sim, data)

        if self.mode == "steady":
            return {s: sim.steady(data, s) for s in self.signals}

        elif self.mode == "raw":
            out = {"time": sim.get(data, "time")}
            for s in self.signals:
                out[s] = sim.get(data, s)
            return out

        elif self.mode == "last":
            return {s: sim.last(data, s) for s in self.signals}

        else:
            raise ValueError(f"Unknown schema mode: {self.mode}")