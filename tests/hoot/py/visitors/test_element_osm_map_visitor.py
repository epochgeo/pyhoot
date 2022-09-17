# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

from os.path import join
import unittest

import hoot


def visit_me(element):
    tags = element.get_tags()
    tags["foo"] = "bar"
    element.set_tags(tags)

class TestElementOsmMapVisitor(unittest.TestCase):

    def test_basic(self):
        """
        test_basic tests to make sure a custom visitor can visit.
        """
        hoot.OsmMap.reset_counters()
        osm_map = hoot.OsmMap()

        json1 = """
{
    "version": 0.6,
    "generator": "Overpass API",
    "osm3s": {
        "timestamp_osm_base": "date",
        "copyright": "c 1999"
    },
    "elements": [
        {
            "type": "node",
            "id": -1,
            "lat": 2.0,
            "lon": -3.000001,
            "tags": {
                "name": "foo"
            }
        }
    ]
}
"""
        reader = hoot.OsmJsonReader()
        reader.set_use_data_source_ids(False)

        # match one feature against itself.
        reader.set_default_status(hoot.Status(hoot.Status.INVALID))
        reader.load_from_string(json1, osm_map)

        visitor = hoot.ElementOsmMapVisitorPy()
        visitor.function = visit_me

        osm_map.visit_rw(visitor)

        expected = """
{"version": 0.6,"generator": "Hootenanny","elements": [
{"type":"node","id":-1,"timestamp":"1970-01-01T00:00:00Z","version":1,"lat":2,"lon":-3.000001,"tags":{"name":"foo","foo":"bar","error:circular":"15"}}]
}
"""
        '''
        {"version": 0.6,"generator": "Hootenanny","elements": [
        {"type":"node","id":-118181,"timestamp":"1970-01-01T00:00:00Z","version":1,"lat":2,"lon":-3.000001,"tags":{"foo":"bar","name":"foo","error:circular":"15"}}]
        }
        '''
        expected_map = hoot.load_json(expected,
                                      default_status=hoot.Status.INVALID)
        self.assertTrue(hoot.MapComparator().is_match(osm_map, expected_map))
