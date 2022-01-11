# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
"""
HootPythonize contains a number of "quality of life" functions that make
working with hoot a little easier and more Pythonic.
"""

import inspect

import hoot
from hoot import Log, OsmMap

# ******
# Logging
# ******


# Taken from:
# https://stackoverflow.com/questions/2749796/how-to-get-the-original-variable-name-of-variable-passed-to-a-function
def var_name(var):
    """
    var_name returns the name of the passed variable in the calling function.

    Example:
        Shows how the var_name can be used.

            def my_func(a):
                print(var_name(a))

            foo=1
            my_func(foo)
            # prints "foo"

    Note:
        It is possible that the wrong value will be returned if the variable
        is referenced by multiple names. E.g.

            foo = 1
            bar = foo
            my_func(foo)
            # may print "foo" or "bar"

    Args:
        var (TYPE): The variable to investigate.

    Returns:
        name (TYPE): Returns the variables name or None if it can't be derived.
    """
    lcls = inspect.stack()[2][0].f_locals
    for name in lcls:
        if id(var) == id(lcls[name]):
            return name
    return None


def _log(level, msg, *args):
    """_log logs a message to hoot's logging framework

    The filename, function and line number are automagically populated.

    Args:
        msg: message to log, this will be converted to a str before logging.
    """
    if int(level) < int(Log.get_instance().get_level()): return
    frame = inspect.stack()[2]
    msg_str = str(msg)
    if len(args) > 0:
        msg_str = msg_str.format(*args)
    Log.log(level, msg_str, frame.filename, frame.function, frame.lineno)


def log_vart(var):
    """
    log_vart provides similar functionality to hoot's LOG_VART

    A best effort is made to derive the name of the variable passed and log
    the variable's name and value at TRACE level.

    Example:
        Simple call of log_vart

            a = 1
            log_vart(a)
            # prints "a: 1"

    Args:
        var: Variable to log
    """
    if int(Log.WarningLevel.TRACE) < int(Log.get_instance().get_level()):
        return
    _log(Log.WarningLevel.TRACE, f"{var_name(var)}: {var}")


def trace(msg, *args):
    """
    trace logs a message to hoot's logging system at the TRACE level.

    Args:
        msg:
            Message to log. This will be converted to a str in Python before
            logging.
    """
    _log(Log.WarningLevel.TRACE, msg, *args)


def log_vard(var):
    """
    log_vard provides similar functionality to hoot's LOG_VARD

    See log_vart for details.
    """
    if int(Log.WarningLevel.DEBUG) < int(Log.get_instance().get_level()):
        return
    _log(Log.WarningLevel.DEBUG, f"{var_name(var)}: {var}")


def debug(msg, *args):
    """
    debug logs a message to hoot's logging system at the DEBUG level.

    Args:
        msg:
            Message to log. This will be converted to a str in Python before
            logging.
    """
    _log(Log.WarningLevel.DEBUG, msg, *args)


def log_vari(var):
    """
    log_vari provides similar functionality to hoot's LOG_VARI

    See log_vart for details.
    """
    if int(Log.WarningLevel.INFO) < int(Log.get_instance().get_level()):
        return
    _log(Log.WarningLevel.INFO, f"{var_name(var)}: {var}")


def info(msg, *args):
    """
    info logs a message to hoot's logging system at the INFO level.

    Args:
        msg:
            Message to log. This will be converted to a str in Python before
            logging.
    """
    _log(Log.WarningLevel.INFO, msg, *args)


def log_vars(var):
    """
    log_vars provides similar functionality to hoot's LOG_VARS

    See log_vart for details.
    """
    _log(Log.WarningLevel.STATUS, f"{var_name(var)}: {var}")


def status(msg, *args):
    """
    status logs a message to hoot's logging system at the STATUS level.

    Args:
        msg:
            Message to log. This will be converted to a str in Python before
            logging.
    """
    _log(Log.WarningLevel.STATUS, msg, *args)


def log_varw(var):
    """
    log_varw provides similar functionality to hoot's LOG_VARW

    See log_varw for details.
    """
    _log(Log.WarningLevel.WARN, f"{var_name(var)}: {var}")


def warn(msg, *args):
    """
    warn logs a message to hoot's logging system at the WARN level.

    Args:
        msg:
            Message to log. This will be converted to a str in Python before
            logging.
    """
    _log(Log.WarningLevel.WARN, msg, *args)


def log_vare(var):
    """
    log_vare provides similar functionality to hoot's LOG_VARE

    See log_vart for details.
    """
    _log(Log.WarningLevel.ERROR, f"{var_name(var)}: {var}")


def error(msg, *args):
    """
    error logs a message to hoot's logging system at the ERROR level.

    Args:
        msg:
            Message to log. This will be converted to a str in Python before
            logging.
    """
    _log(Log.WarningLevel.ERROR, msg, *args)


def log_varf(var):
    """
    log_vars provides similar functionality to hoot's LOG_VARF

    See log_varf for details.
    """
    _log(Log.WarningLevel.FATAL, f"{var_name(var)}: {var}")


def fatal(msg, *args):
    """
    fatal logs a message to hoot's logging system at the FATAL level.

    Args:
        msg:
            Message to log. This will be converted to a str in Python before
            logging.
    """
    _log(Log.WarningLevel.FATAL, msg, *args)

# ******
# OsmMap
# ******


def distance(osm_map: OsmMap, element1: hoot.Element, element2: hoot.Element):
    """
    distance calculates the distance between two elements and returns the
    result. It is assumed that the map is already in a planar projection.
    """
    return hoot.EuclideanDistanceExtractor().distance(osm_map, element1,
                                                      element2)


OsmMap.distance = distance


def to_json(osm_map: OsmMap):
    "to_json converts the map to JSON and returns the result as a string."
    return hoot.OsmJsonWriter().to_string(osm_map)


OsmMap.to_json = to_json
