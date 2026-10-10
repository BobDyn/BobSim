"""Print the Makefile's canonical help text on hosts without POSIX ``printf``."""

from __future__ import annotations

import ast
from pathlib import Path


def main() -> None:
    makefile = Path(__file__).resolve().parents[1] / "Makefile"
    lines = makefile.read_text(encoding="utf-8").splitlines()
    start = next(
        index + 1
        for index, line in enumerate(lines)
        if line.lstrip().startswith("@printf '%s\\n'")
    )
    output: list[str] = []
    for line in lines[start:]:
        expression = line.strip()
        continued = expression.endswith("\\")
        if continued:
            expression = expression[:-1].rstrip()
        if not expression.startswith("'"):
            break
        output.append(str(ast.literal_eval(expression)))
        if not continued:
            break
    print("\n".join(output))


if __name__ == "__main__":
    main()
