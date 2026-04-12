from dataclasses import dataclass
from typing import Callable, Dict, List, Optional


Validator = Callable[[object, Dict[str, object]], None]
Extractor = Callable[[object, Dict[str, object]], Dict[str, float]]


@dataclass
class OutputSchema:
    signals: List[str]
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
        return {s: sim.steady(data, s) for s in self.signals}