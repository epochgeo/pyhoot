"""
utils contains a number of useful utility functions that are not part of
c++ hootenanny
"""
from .libpyhoot import OsmMap, OsmJsonReader, Status


def load_json(json: str, default_status=Status.INVALID):
    """load_json loads an OsmMap from json and returns it."""

    result = OsmMap()

    reader = OsmJsonReader()
    reader.set_default_status(Status(default_status))
    reader.load_from_string(json, result)

    return result
