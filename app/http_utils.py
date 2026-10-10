from __future__ import annotations


def parse_byte_range(range_header: str | None, size: int) -> tuple[int, int] | None:
    if not range_header or not range_header.startswith("bytes=") or size <= 0:
        return None
    raw_range = range_header.removeprefix("bytes=").split(",", 1)[0].strip()
    if "-" not in raw_range:
        return None
    start_text, end_text = raw_range.split("-", 1)
    try:
        if start_text:
            start = int(start_text)
            end = int(end_text) if end_text else size - 1
        else:
            suffix_size = int(end_text)
            if suffix_size <= 0:
                return None
            start = max(0, size - suffix_size)
            end = size - 1
    except ValueError:
        return None
    if start < 0 or start >= size:
        raise ValueError("Range start is outside the file.")
    end = min(end, size - 1)
    if end < start:
        raise ValueError("Range end is before the range start.")
    return start, end
