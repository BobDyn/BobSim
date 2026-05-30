"""Read and patch generated Modelica record parameters for OptSim DOE."""

from __future__ import annotations

import re
from typing import Any


def parse_float(raw: str) -> float:
    raw = raw.strip()
    if any((c.isalpha() and c not in "eE") or c in "{}[]" for c in raw):
        raise ValueError(f"Cannot parse non-scalar value as float: {raw!r}")
    allowed = set("0123456789eE.+-*/() ")
    if not all(c in allowed for c in raw):
        raise ValueError(f"Unexpected characters in value: {raw!r}")
    return float(eval(raw))  # safe: numeric literals and arithmetic only


def read_value(text: str, spec: dict[str, Any]) -> float:
    start, end = locate_value_span(text, spec)
    return parse_float(text[start:end])


def replace_value(text: str, spec: dict[str, Any], value: float) -> str:
    start, end = locate_value_span(text, spec)
    return text[:start] + f"{value:.12g}" + text[end:]


def scale_value(text: str, spec: dict[str, Any], factor: float) -> str:
    start, end = locate_value_span(text, spec)
    raw = text[start:end]
    scaled = _scale_numeric_literals(raw, factor)
    return text[:start] + scaled + text[end:]


def locate_value_span(text: str, spec: dict[str, Any]) -> tuple[int, int]:
    block = str(spec["block"])
    param = spec.get("param")

    if param is None:
        start, end = _locate_scalar_parameter_value(text, block)
    else:
        block_start, block_end = _locate_parameter_call_body(text, block)
        start, end = _locate_named_value(text, block_start, block_end, str(param))

    for field in spec.get("field_path", []):
        start, end = _maybe_call_body(text, start, end)
        start, end = _locate_named_value(text, start, end, str(field))

    if "index" in spec:
        start, end = _locate_indexed_value(text, start, end, list(spec["index"]))

    return start, end


def _locate_parameter_statement(text: str, name: str) -> tuple[int, int, int]:
    pattern = re.compile(rf"\b{re.escape(name)}\b")
    for match in pattern.finditer(text):
        stmt_start = text.rfind(";", 0, match.start()) + 1
        prefix = text[stmt_start:match.start()]
        if "parameter" not in prefix:
            continue
        stmt_end = _find_statement_end(text, match.end())
        return stmt_start, match.start(), stmt_end
    raise ValueError(f"Parameter {name!r} not found in generated record")


def _find_statement_end(text: str, start: int) -> int:
    depth = 0
    for i in range(start, len(text)):
        ch = text[i]
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        elif ch == ";" and depth == 0:
            return i
    raise ValueError("Could not find end of Modelica parameter statement")


def _locate_parameter_call_body(text: str, name: str) -> tuple[int, int]:
    _stmt_start, name_start, stmt_end = _locate_parameter_statement(text, name)
    paren_open = text.find("(", name_start, stmt_end)
    if paren_open == -1:
        raise ValueError(f"Parameter {name!r} is not a record/call-style parameter")
    paren_close = _find_matching(text, paren_open)
    return paren_open + 1, paren_close


def _locate_scalar_parameter_value(text: str, name: str) -> tuple[int, int]:
    _stmt_start, name_start, stmt_end = _locate_parameter_statement(text, name)
    eq = text.find("=", name_start, stmt_end)
    if eq == -1:
        raise ValueError(f"Scalar parameter {name!r} has no '=' value")
    return _trim_span(text, eq + 1, stmt_end)


def _locate_named_value(
    text: str,
    body_start: int,
    body_end: int,
    name: str,
) -> tuple[int, int]:
    for item_start, item_end in _split_top_level(text, body_start, body_end, ","):
        eq = _find_top_level_char(text, item_start, item_end, "=")
        if eq == -1:
            continue
        key_start, key_end = _trim_span(text, item_start, eq)
        if text[key_start:key_end] == name:
            return _trim_span(text, eq + 1, item_end)
    raise ValueError(f"Named parameter {name!r} not found")


def _locate_indexed_value(
    text: str,
    start: int,
    end: int,
    indexes: list[int],
) -> tuple[int, int]:
    current_start, current_end = start, end
    for index in indexes:
        current_start, current_end = _trim_span(text, current_start, current_end)
        if text[current_start] in "{[":
            inner_start, inner_end = _collection_inner_span(
                text, current_start, current_end
            )
        else:
            inner_start, inner_end = current_start, current_end
        rows = _split_top_level(text, inner_start, inner_end, ";")
        if len(rows) > 1:
            items = rows
        else:
            items = _split_top_level(text, inner_start, inner_end, ",")
        if index < 0 or index >= len(items):
            raise IndexError(f"Index {index} out of range for {text[start:end]!r}")
        current_start, current_end = _trim_span(text, *items[index])
    return current_start, current_end


def _collection_inner_span(text: str, start: int, end: int) -> tuple[int, int]:
    start, end = _trim_span(text, start, end)
    if text[start] == "{" and text[end - 1] == "}":
        return start + 1, end - 1
    if text[start] == "[" and text[end - 1] == "]":
        return start + 1, end - 1
    raise ValueError(f"Expected vector or matrix expression, got {text[start:end]!r}")


def _maybe_call_body(text: str, start: int, end: int) -> tuple[int, int]:
    start, end = _trim_span(text, start, end)
    paren_open = text.find("(", start, end)
    if paren_open == -1:
        return start, end
    prefix = text[start:paren_open].strip()
    if not prefix or not all(ch.isalnum() or ch in "_." for ch in prefix):
        return start, end
    paren_close = _find_matching(text, paren_open)
    if paren_close != end - 1:
        return start, end
    return paren_open + 1, paren_close


def _split_top_level(
    text: str,
    start: int,
    end: int,
    separators: str,
) -> list[tuple[int, int]]:
    spans: list[tuple[int, int]] = []
    depth = 0
    token_start = start

    for i in range(start, end):
        ch = text[i]
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        elif ch in separators and depth == 0:
            spans.append((token_start, i))
            token_start = i + 1

    spans.append((token_start, end))
    return [_trim_span(text, a, b) for a, b in spans if text[a:b].strip()]


def _find_top_level_char(text: str, start: int, end: int, target: str) -> int:
    depth = 0
    for i in range(start, end):
        ch = text[i]
        if ch in "({[":
            depth += 1
        elif ch in ")}]":
            depth -= 1
        elif ch == target and depth == 0:
            return i
    return -1


def _find_matching(text: str, open_index: int) -> int:
    pairs = {"(": ")", "{": "}", "[": "]"}
    opener = text[open_index]
    closer = pairs[opener]
    depth = 1
    for i in range(open_index + 1, len(text)):
        if text[i] == opener:
            depth += 1
        elif text[i] == closer:
            depth -= 1
            if depth == 0:
                return i
    raise ValueError(f"Could not find matching {closer!r}")


def _trim_span(text: str, start: int, end: int) -> tuple[int, int]:
    while start < end and text[start].isspace():
        start += 1
    while end > start and text[end - 1].isspace():
        end -= 1
    return start, end


def _scale_numeric_literals(raw: str, factor: float) -> str:
    pattern = re.compile(
        r"(?<![A-Za-z0-9_])[-+]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][-+]?\d+)?"
    )

    def repl(match: re.Match[str]) -> str:
        return f"{float(match.group(0)) * factor:.12g}"

    return pattern.sub(repl, raw)
