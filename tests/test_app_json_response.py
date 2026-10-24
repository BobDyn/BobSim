"""JSON transport preserves payloads while reducing large responses."""
import gzip
from io import BytesIO
import json
from typing import Any

import pytest

from app.server import BobSimHandler


@pytest.mark.parametrize("accept", ["gzip, deflate, br", "gzip;q=0", ""])
def test_large_json_response_roundtrip(accept):
    handler: Any = object.__new__(BobSimHandler)
    handler.headers = {"Accept-Encoding": accept}
    handler.wfile = BytesIO()
    headers = {}
    handler.send_response = lambda status: None
    handler.send_header = lambda key, value: headers.update({key: value})
    handler.end_headers = lambda: None
    payload = {"curves": [{"force": 123.456789, "load": 650}] * 1000}
    handler._send_json(payload)
    encoded = handler.wfile.getvalue()
    assert int(headers["Content-Length"]) == len(encoded)
    if accept.startswith("gzip,"):
        assert headers["Content-Encoding"] == "gzip"
        assert len(encoded) < 1000
        encoded = gzip.decompress(encoded)
    else:
        assert "Content-Encoding" not in headers
    assert json.loads(encoded) == payload
