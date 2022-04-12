# hoot package

## Submodules

## hoot.hoot_pythonic module

HootPythonize contains a number of “quality of life” functions that make
working with hoot a little easier and more Pythonic.


### hoot.hoot_pythonic.debug(msg, \*args)
debug logs a message to hoot’s logging system at the DEBUG level.

Args:

    msg:

        Message to log. This will be converted to a str in Python before
        logging.


### hoot.hoot_pythonic.distance(osm_map, element1, element2)
distance calculates the distance between two elements and returns the
result. It is assumed that the map is already in a planar projection.


### hoot.hoot_pythonic.error(msg, \*args)
error logs a message to hoot’s logging system at the ERROR level.

Args:

    msg:

        Message to log. This will be converted to a str in Python before
        logging.


### hoot.hoot_pythonic.fatal(msg, \*args)
fatal logs a message to hoot’s logging system at the FATAL level.

Args:

    msg:

        Message to log. This will be converted to a str in Python before
        logging.


### hoot.hoot_pythonic.info(msg, \*args)
info logs a message to hoot’s logging system at the INFO level.

Args:

    msg:

        Message to log. This will be converted to a str in Python before
        logging.


### hoot.hoot_pythonic.log_vard(var)
log_vard provides similar functionality to hoot’s LOG_VARD

See log_vart for details.


### hoot.hoot_pythonic.log_vare(var)
log_vare provides similar functionality to hoot’s LOG_VARE

See log_vart for details.


### hoot.hoot_pythonic.log_varf(var)
log_vars provides similar functionality to hoot’s LOG_VARF

See log_varf for details.


### hoot.hoot_pythonic.log_vari(var)
log_vari provides similar functionality to hoot’s LOG_VARI

See log_vart for details.


### hoot.hoot_pythonic.log_vars(var)
log_vars provides similar functionality to hoot’s LOG_VARS

See log_vart for details.


### hoot.hoot_pythonic.log_vart(var)
log_vart provides similar functionality to hoot’s LOG_VART

A best effort is made to derive the name of the variable passed and log
the variable’s name and value at TRACE level.

Example:

    Simple call of log_vart

    > a = 1
    > log_vart(a)
    > # prints “a: 1”

Args:

    var: Variable to log


### hoot.hoot_pythonic.log_varw(var)
log_varw provides similar functionality to hoot’s LOG_VARW

See log_varw for details.


### hoot.hoot_pythonic.status(msg, \*args)
status logs a message to hoot’s logging system at the STATUS level.

Args:

    msg:

        Message to log. This will be converted to a str in Python before
        logging.


### hoot.hoot_pythonic.to_json(osm_map)
to_json converts the map to JSON and returns the result as a string.


### hoot.hoot_pythonic.trace(msg, \*args)
trace logs a message to hoot’s logging system at the TRACE level.

Args:

    msg:

        Message to log. This will be converted to a str in Python before
        logging.


### hoot.hoot_pythonic.var_name(var)
var_name returns the name of the passed variable in the calling function.

Example:

    Shows how the var_name can be used.

    > def my_func(a):

    >     print(var_name(a))

    > foo=1
    > my_func(foo)
    > # prints “foo”

Note:

    It is possible that the wrong value will be returned if the variable
    is referenced by multiple names. E.g.

    > foo = 1
    > bar = foo
    > my_func(foo)
    > # may print “foo” or “bar”

Args:

    var (TYPE): The variable to investigate.

Returns:

    name (TYPE): Returns the variables name or None if it can’t be derived.


### hoot.hoot_pythonic.warn(msg, \*args)
warn logs a message to hoot’s logging system at the WARN level.

Args:

    msg:

        Message to log. This will be converted to a str in Python before
        logging.

## hoot.libpyhoot module

Unofficial hootenanny python bindings


### _class_ hoot.libpyhoot.AreaCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.AreaCriterion) -> None


2. __init__(self: hoot.libpyhoot.AreaCriterion, arg0: hoot::OsmMap) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setOsmMap(_ = Non_ )

#### set_osm_map()
setOsmMap(self: hoot.libpyhoot.AreaCriterion, arg0: hoot::OsmMap) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.ChainCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.ChainCriterion) -> None


2. __init__(self: hoot.libpyhoot.ChainCriterion, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.ChainCriterion, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.ChainCriterion, arg0: hoot::OsmMap) -> None


2. __init__(self: hoot.libpyhoot.ChainCriterion, arg0: hoot.libpyhoot.ElementCriterion, 

```
*
```

args) -> None


#### addCriterion(_ = Non_ )

#### add_criterion()
addCriterion(self: hoot.libpyhoot.ChainCriterion, arg0: hoot.libpyhoot.ElementCriterion) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setConfiguration(_ = Non_ )

#### setOsmMap(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.ChainCriterion, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_osm_map()
setOsmMap(self: hoot.libpyhoot.ChainCriterion, arg0: hoot::OsmMap) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.CircularErrorExtractor()
Bases: `hoot.libpyhoot.FeatureExtractor`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.CircularErrorExtractor) -> None


2. __init__(self: hoot.libpyhoot.CircularErrorExtractor, arg0: int) -> None


#### extract(\*args, \*\*kwargs)
Overloaded function.


1. extract(self: hoot.libpyhoot.FeatureExtractor, arg0: hoot::OsmMap, arg1: hoot::Element, arg2: hoot::Element) -> float

extract extracts a feature from a given pair of elements.

The feature may be something like the distance between colors, the overlap of two polygons,
etc.


1. extract(self: hoot.libpyhoot.FeatureExtractor, map: hoot::OsmMap, target: List[hoot::Element], candidate: List[hoot::Element], ignored: List[bool] = []) -> numpy.ndarray[numpy.float64]

This override to the distance function is pyhoot specific and allows you to calculate distance
on an array of values in one pass.


#### getFactorType(_ = Non_ )

#### getNullTreatment(_ = Non_ )

#### get_factor_type()
getFactorType(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::FactorType

getFactorType returns the factor type for this feature/factor (Nominal or Numeric).


#### get_null_treatment()
getNullTreatment(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::NullTreatment

getNullTreatment returns the null treatment for this feature/factor (NullAsValue or
NullAsMissingValue).


#### isNull(_ = Non_ )

#### _static_ is_null()
isNull(arg0: float) -> bool


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.FeatureExtractor) -> QString


### _class_ hoot.libpyhoot.Command()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### _static_ run(arg0: QString, arg1: QStringList)
run will run a hootenanny command line command within the current runtime.

Example:

    An example conflation command that is equivalent to running the hoot command line
    “python -m hoot conflate $HOOT_HOME/ToyTestA.osm $HOOT_HOME/ToyTestB.osm output.osm”

    > hoot.Command.run(“conflate”, [hoot.TOY_TEST_A_PATH, hoot.TOY_TEST_B_PATH, “output.osm”])


### _class_ hoot.libpyhoot.ConflateCaseTestSuite()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### _static_ run_dir(arg0: QString)

### _class_ hoot.libpyhoot.ConflateExecutor()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.ConflateExecutor)

#### conflate(self: hoot.libpyhoot.ConflateExecutor, arg0: QString, arg1: QString, arg2: QString)
conflate two inputs and write the conflated data to an output.


* **Parameters**

    
    * **input1** – URL of first map to conflate


    * **input2** – URL of second map to conflate


:param outputPath; URL to write conflated output


#### setDiffConflateEnableTags(_ = Non_ )

#### setDiffConflateSeparateOutput(_ = Non_ )

#### setDiffRemoveLinearPartialMatchesAsWhole(_ = Non_ )

#### setDiffRemoveRiverPartialMatchesAsWhole(_ = Non_ )

#### setDisplayChangesetStats(_ = Non_ )

#### setDisplayStats(_ = Non_ )

#### setIsDiffConflate(_ = Non_ )

#### setOsmApiDbUrl(_ = Non_ )

#### setOutputChangesetStatsFile(_ = Non_ )

#### setOutputStatsFile(_ = Non_ )

#### set_diff_conflate_enable_tags()
setDiffConflateEnableTags(self: hoot.libpyhoot.ConflateExecutor, arg0: bool) -> None


#### set_diff_conflate_separate_output()
setDiffConflateSeparateOutput(self: hoot.libpyhoot.ConflateExecutor, arg0: bool) -> None


#### set_diff_remove_linear_partial_matches_as_whole()
setDiffRemoveLinearPartialMatchesAsWhole(self: hoot.libpyhoot.ConflateExecutor, arg0: bool) -> None


#### set_diff_remove_river_partial_matches_as_whole()
setDiffRemoveRiverPartialMatchesAsWhole(self: hoot.libpyhoot.ConflateExecutor, arg0: bool) -> None


#### set_display_changeset_stats()
setDisplayChangesetStats(self: hoot.libpyhoot.ConflateExecutor, arg0: bool) -> None


#### set_display_stats()
setDisplayStats(self: hoot.libpyhoot.ConflateExecutor, arg0: bool) -> None


#### set_is_diff_conflate()
setIsDiffConflate(self: hoot.libpyhoot.ConflateExecutor, arg0: bool) -> None


#### set_osm_api_db_url()
setOsmApiDbUrl(self: hoot.libpyhoot.ConflateExecutor, arg0: QString) -> None


#### set_output_changeset_stats_file()
setOutputChangesetStatsFile(self: hoot.libpyhoot.ConflateExecutor, arg0: QString) -> None


#### set_output_stats_file()
setOutputStatsFile(self: hoot.libpyhoot.ConflateExecutor, arg0: QString) -> None


### _class_ hoot.libpyhoot.ConstOsmMapOperation()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### apply(self: hoot.libpyhoot.ConstOsmMapOperation, arg0: hoot.libpyhoot.OsmMap)

### _class_ hoot.libpyhoot.CreatorDescription()
Bases: `pybind11_builtins.pybind11_object`


#### AREA(_ = <BaseFeatureType.AREA: 6_ )

#### BUILDING(_ = <BaseFeatureType.BUILDING: 2_ )

#### _class_ BaseFeatureType()
Bases: `pybind11_builtins.pybind11_object`

This is how we map various match creators to the feature they operate on.
Helpful when generating stats later.

Members:

> POI

> HIGHWAY

> BUILDING

> RIVER

> POIPOLYGONPOI : This is a superset of POI specific to poi/poly conflation.

> POLYGON : Polygon is a superset of building.

> AREA

> RAILWAY

> POWERLINE

> POINT

> LINE

> RELATION

> UNKNOWN


#### AREA(_ = <BaseFeatureType.AREA: 6_ )

#### BUILDING(_ = <BaseFeatureType.BUILDING: 2_ )

#### HIGHWAY(_ = <BaseFeatureType.HIGHWAY: 1_ )

#### LINE(_ = <BaseFeatureType.LINE: 10_ )

#### POI(_ = <BaseFeatureType.POI: 0_ )

#### POINT(_ = <BaseFeatureType.POINT: 9_ )

#### POIPOLYGONPOI(_ = <BaseFeatureType.POIPOLYGONPOI: 4_ )

#### POLYGON(_ = <BaseFeatureType.POLYGON: 5_ )

#### POWERLINE(_ = <BaseFeatureType.POWERLINE: 8_ )

#### RAILWAY(_ = <BaseFeatureType.RAILWAY: 7_ )

#### RELATION(_ = <BaseFeatureType.RELATION: 11_ )

#### RIVER(_ = <BaseFeatureType.RIVER: 3_ )

#### UNKNOWN(_ = <BaseFeatureType.UNKNOWN: 12_ )

#### \__init__(self: hoot.libpyhoot.CreatorDescription.BaseFeatureType, value: int)

#### _property_ name()

#### _property_ value()

#### CALCTYPEAREA(_ = <FeatureCalcType.CALCTYPEAREA: 2_ )

#### CALCTYPELENGTH(_ = <FeatureCalcType.CALCTYPELENGTH: 1_ )

#### CALCTYPENONE(_ = <FeatureCalcType.CALCTYPENONE: 0_ )

#### _class_ FeatureCalcType()
Bases: `pybind11_builtins.pybind11_object`

Members:

CALCTYPENONE

CALCTYPELENGTH

CALCTYPEAREA


#### CALCTYPEAREA(_ = <FeatureCalcType.CALCTYPEAREA: 2_ )

#### CALCTYPELENGTH(_ = <FeatureCalcType.CALCTYPELENGTH: 1_ )

#### CALCTYPENONE(_ = <FeatureCalcType.CALCTYPENONE: 0_ )

#### \__init__(self: hoot.libpyhoot.CreatorDescription.FeatureCalcType, value: int)

#### _property_ name()

#### _property_ value()

#### HIGHWAY(_ = <BaseFeatureType.HIGHWAY: 1_ )

#### LINE(_ = <BaseFeatureType.LINE: 10_ )

#### POI(_ = <BaseFeatureType.POI: 0_ )

#### POINT(_ = <BaseFeatureType.POINT: 9_ )

#### POIPOLYGONPOI(_ = <BaseFeatureType.POIPOLYGONPOI: 4_ )

#### POLYGON(_ = <BaseFeatureType.POLYGON: 5_ )

#### POWERLINE(_ = <BaseFeatureType.POWERLINE: 8_ )

#### RAILWAY(_ = <BaseFeatureType.RAILWAY: 7_ )

#### RELATION(_ = <BaseFeatureType.RELATION: 11_ )

#### RIVER(_ = <BaseFeatureType.RIVER: 3_ )

#### UNKNOWN(_ = <BaseFeatureType.UNKNOWN: 12_ )

#### \__init__(\*args, \*\*kwargs)

#### baseFeatureTypeToString(_ = Non_ )

#### _static_ base_feature_type_to_string()
baseFeatureTypeToString(arg0: hoot::CreatorDescription::BaseFeatureType) -> QString

Converts a base feature type to a string representation


* **Parameters**

    **t** – the feature type to convert



* **Returns**

    a string



#### getBaseFeatureType(_ = Non_ )

#### getClassName(_ = Non_ )

#### getDescription(_ = Non_ )

#### getElementCriterion(_ = Non_ )

#### getElementCriterionName(_ = Non_ )

#### getExperimental(_ = Non_ )

#### getFeatureCalcType(_ = Non_ )

#### getGeometryType(_ = Non_ )

#### get_base_feature_type()
getBaseFeatureType(self: hoot.libpyhoot.CreatorDescription) -> hoot::CreatorDescription::BaseFeatureType


#### get_class_name()
getClassName(self: hoot.libpyhoot.CreatorDescription) -> QString


#### get_description()
getDescription(self: hoot.libpyhoot.CreatorDescription) -> QString


#### get_element_criterion()
getElementCriterion(self: hoot::CreatorDescription::BaseFeatureType, arg0: hoot.libpyhoot.OsmMap) -> hoot.libpyhoot.ElementCriterion

Returns a GeometryTypeCriterion instantiation associated with the given feature type


* **Parameters**

    
    * **t** – a feature type


    * **map** – map used to initialize the criterion



* **Returns**

    a GeometryTypeCriterion


@note It would be better to return a ConflatableElementCriterion here instead, but returning
NonBuildingAreaCriterion doesn’t allow for that. Doing so also makes this inconsistent with
getElementCriterionName. Think if we change to AreaCriterion, however, that will throw the
stats off.


#### _static_ get_element_criterion_name()
getElementCriterionName(arg0: hoot::CreatorDescription::BaseFeatureType) -> QString

Returns the name of a ConflatableElementCriterion associated with the given feature type


* **Parameters**

    **t** – a feature type



* **Returns**

    the class name of a ConflatableElementCriterion



#### get_experimental()
getExperimental(self: hoot.libpyhoot.CreatorDescription) -> bool


#### _static_ get_feature_calc_type()
getFeatureCalcType(arg0: hoot::CreatorDescription::BaseFeatureType) -> hoot::CreatorDescription::FeatureCalcType

Returns the physical measurement feature stat calculation type for a base feature type e.g.
an area calc type is returned for polygon features


* **Parameters**

    **t** – the feature type to retrieve the statistics calculation type for



* **Returns**

    a feature statistics calculation type enumeration value



#### get_geometry_type()
getGeometryType(self: hoot.libpyhoot.CreatorDescription) -> hoot::GeometryTypeCriterion::GeometryType


#### setBaseFeatureType(_ = Non_ )

#### setClassName(_ = Non_ )

#### setDescription(_ = Non_ )

#### setExperimental(_ = Non_ )

#### setGeometryType(_ = Non_ )

#### setMatchCandidateCriteria(_ = Non_ )

#### set_base_feature_type()
setBaseFeatureType(self: hoot.libpyhoot.CreatorDescription, arg0: hoot::CreatorDescription::BaseFeatureType) -> None


#### set_class_name()
setClassName(self: hoot.libpyhoot.CreatorDescription, arg0: QString) -> None


#### set_description()
setDescription(self: hoot.libpyhoot.CreatorDescription, arg0: QString) -> None


#### set_experimental()
setExperimental(self: hoot.libpyhoot.CreatorDescription, arg0: bool) -> None


#### set_geometry_type()
setGeometryType(self: hoot.libpyhoot.CreatorDescription, arg0: hoot::GeometryTypeCriterion::GeometryType) -> None


#### set_match_candidate_criteria()
setMatchCandidateCriteria(self: hoot.libpyhoot.CreatorDescription, arg0: QStringList) -> None


#### stringToBaseFeatureType(_ = Non_ )

#### _static_ string_to_base_feature_type()
stringToBaseFeatureType(arg0: QString) -> hoot::CreatorDescription::BaseFeatureType

Converts the string representation of a base feature type to an enum


* **Parameters**

    **s** – the string to convert



* **Returns**

    a feature type enumeration value



#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.CreatorDescription) -> QString


### _class_ hoot.libpyhoot.DataFrame()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.DataFrame)

#### addData(_ = Non_ )

#### addDataVector(_ = Non_ )

#### add_data()
addData(self: hoot.libpyhoot.DataFrame, data_array: buffer) -> None

Appends a data vector to the end of the dataframe


* **Parameters**

    
    * **label** – the class label for the training vector


    * **dataItem** – the data vector to add


    * **eventWeight** – the weight associated with the data vector



#### add_data_vector()
addDataVector(self: hoot.libpyhoot.DataFrame, label: str, data_item: List[float], event_weight: float = 1) -> None

Appends a data vector to the end of the dataframe


* **Parameters**

    
    * **label** – the class label for the training vector


    * **dataItem** – the data vector to add


    * **eventWeight** – the weight associated with the data vector



#### clear(self: hoot.libpyhoot.DataFrame)
Resets all the internal data structures associated with data frame


#### computeBandwidthByFactor(_ = Non_ )

#### compute_bandwidth_by_factor()
computeBandwidthByFactor(self: hoot.libpyhoot.DataFrame, arg0: int, arg1: List[int], arg2: float, arg3: float, arg4: float, arg5: float, arg6: float) -> float

> Computes the Silverman’s rule for a set of data vectors values for a single
> factor


* **Parameters**

    
    * **fIdx** – the factor index


    * **dataIndices** – the data vectors of interest


    * **minVal** – returns the minimum factor value computed by the function


    * **minVal** – returns the minimum factor value computed by the function


    * **mean** – returns the mean factor value computed by the function


    * **q1** – returns the first quartile


    * **q3** – returns the third quartile



* **Returns**

    the computed bandwidth



#### deactivateFactor(_ = Non_ )

#### deactivate_factor()
deactivateFactor(self: hoot.libpyhoot.DataFrame, arg0: str) -> None

Deactivates the factor by removing its index from the
list of active factor indices


* **Parameters**

    **factor** – the factor to deactivate



#### empty(self: hoot.libpyhoot.DataFrame)

* **Returns**

    true is DataFrame contains 0 data vectors



#### getActiveFactorCount(_ = Non_ )

#### getClassDistribution(_ = Non_ )

#### getClassLabels(_ = Non_ )

#### getClassPopulations(_ = Non_ )

#### getDataElement(_ = Non_ )

#### getDataVector(_ = Non_ )

#### getFactorLabelFromIndex(_ = Non_ )

#### getFactorLabels(_ = Non_ )

#### getFactorTypes(_ = Non_ )

#### getIndexFromFactorLabel(_ = Non_ )

#### getMajorityTrainingLabel(_ = Non_ )

#### getNullTreatment(_ = Non_ )

#### getNumDataVectors(_ = Non_ )

#### getTrainingLabel(_ = Non_ )

#### getTrainingLabelList(_ = Non_ )

#### getWeight(_ = Non_ )

#### get_active_factor_count()
getActiveFactorCount(self: hoot.libpyhoot.DataFrame) -> int

getActiveFactorCount
:returns: the number of active factors


#### get_class_distribution()
getClassDistribution(self: hoot.libpyhoot.DataFrame, arg0: List[int], arg1: List[int]) -> None

Get the number of instances per class based on the subset of data
vectors represented by the index value within the indices input parameter. This cannot
be mapped back to the enumerated classes and is provided because it is slightly more
efficient than the above function.


* **Parameters**

    
    * **indices** – a list of data vector indices in the data set


    * **populations** – the output of number of instances in each class represented



#### get_class_labels()
getClassLabels(self: hoot.libpyhoot.DataFrame) -> Set[str]

> Gets the class labels unique to the whole data set


* **Returns**

    the class labels



#### get_class_populations()
getClassPopulations(self: hoot.libpyhoot.DataFrame, arg0: List[int], arg1: __gnu_cxx::hash_map<std::string, int, __gnu_cxx::hash<std::string>, std::equal_to<std::string>, std::allocator<int> >) -> None

Get the number of instances per class based on the subset of data
vectors represented by the index value within the indices input parameter


* **Parameters**

    
    * **indices** – a list of data vector indices in the data set


    * **populations** – the output map of class names to number of instances



#### get_data_element()
getDataElement(self: hoot.libpyhoot.DataFrame, arg0: int, arg1: int) -> float

Gets the value of a factor within a data vector
within the data frame


* **Parameters**

    
    * **vIdx** – the vector index


    * **fIdx** – the factor index



* **Returns**

    the requested value



#### get_data_vector()
getDataVector(self: hoot.libpyhoot.DataFrame, arg0: int) -> List[float]

Gets reference to a single data vector in the data frame


* **Parameters**

    **vIdx** – the vector index



* **Returns**

    a reference to the requested vector



#### get_factor_label_from_index()
getFactorLabelFromIndex(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. getFactorLabelFromIndex(self: hoot.libpyhoot.DataFrame, arg0: int) -> str


* **Returns**

    the number of data vectors in the data set



1. getFactorLabelFromIndex(self: hoot.libpyhoot.DataFrame, arg0: int) -> str

> Gets the factor label corresponding to the factor index


* **Parameters**

    **fIdx** – the index into the list of factors



* **Returns**

    the factor label corresponding to the entry in the factor list



#### get_factor_labels()
getFactorLabels(self: hoot.libpyhoot.DataFrame) -> List[str]

Gets the list of factor labels


* **Parameters**

    **factors** – a container to hold the factor labels



#### get_factor_types()
getFactorTypes(self: hoot.libpyhoot.DataFrame) -> List[int]


#### get_index_from_factor_label()
getIndexFromFactorLabel(self: hoot.libpyhoot.DataFrame, arg0: str) -> int

Gets the index into the factor list based on its string
representation


* **Parameters**

    **fLabel** – the factor label to find the index



* **Returns**

    the index into the list of factors



#### get_majority_training_label()
getMajorityTrainingLabel(self: hoot.libpyhoot.DataFrame, arg0: List[int]) -> str

> Gets the majority class label corresponding to the data set


* **Parameters**

    **dataSet** – the data vector set



* **Returns**

    the class label corresponding to the majority of data vectors



#### get_null_treatment()
getNullTreatment(self: hoot.libpyhoot.DataFrame, arg0: int) -> int

Returns the NullTreatment for a given factor


#### get_num_data_vectors()
getNumDataVectors(self: hoot.libpyhoot.DataFrame) -> int


* **Returns**

    the number of factors in the data set



#### get_training_label()
getTrainingLabel(self: hoot.libpyhoot.DataFrame, arg0: int) -> str

> Gets the class label corresponding to the data vector index


* **Parameters**

    **dIdx** – the data vector index into the dataset



* **Returns**

    the class label corresponding to the data vector



#### get_training_label_list()
getTrainingLabelList(self: hoot.libpyhoot.DataFrame) -> List[str]

getTrainingLabelList
:returns: the list of class labels corresponding to the training data vectors


#### get_weight()
getWeight(self: hoot.libpyhoot.DataFrame, arg0: int) -> float

Returns the weight for the row
:param vIdx: the vector index


#### hasFactorTypes(_ = Non_ )

#### hasNullTreatments(_ = Non_ )

#### has_factor_types()
hasFactorTypes(self: hoot.libpyhoot.DataFrame) -> bool

hasFactorTypes
:returns: true is factor types have been set


#### has_null_treatments()
hasNullTreatments(self: hoot.libpyhoot.DataFrame) -> bool

hasNullTreatments
:returns: true if null treatment values have been set


#### isDataSetPure(_ = Non_ )

#### isNominal(_ = Non_ )

#### isNull(_ = Non_ )

#### is_data_set_pure()
isDataSetPure(self: hoot.libpyhoot.DataFrame, arg0: List[int]) -> bool

> Checks to see if the data vectors belonging to the set of indices

are all of the same class


#### is_nominal()
isNominal(self: hoot.libpyhoot.DataFrame, arg0: int) -> bool

Returns true if the specified column is nominal.


#### _static_ is_null()
isNull(arg0: float) -> bool

Returns true if v is a “null”


#### makeBalancedBoostrapAndOobSets(_ = Non_ )

#### makeBalancedRoundRobinBootstrapAndOobSets(_ = Non_ )

#### makeBoostrapAndOobSets(_ = Non_ )

#### make_balanced_boostrap_and_oob_sets()
makeBalancedBoostrapAndOobSets(self: hoot.libpyhoot.DataFrame, arg0: List[int], arg1: List[int]) -> None

> Creates balanced bootstrap and out of bag sets with replacement

based on paper:


1. Chen, et.al. Using Random Forest to Learn Imbalanced Data


* **Parameters**

    
    * **bootstrap** – the output container to hold indices to data vectors for the bootstrap set


    * **oob** – the output container to hold indices to data vectors for the out of bag set



#### make_balanced_round_robin_bootstrap_and_oob_sets()
makeBalancedRoundRobinBootstrapAndOobSets(self: hoot.libpyhoot.DataFrame, arg0: str, arg1: str, arg2: List[int], arg3: List[int]) -> None

> Creates balanced binary bootstrap and out of bag sets with replacement

based on paper:


1. Chen, et.al. Using Random Forest to Learn Imbalanced Data


* **Parameters**

    
    * **className1** – the name of the class to represent the positive class


    * **className2** – the name of the class to represent the negative class


    * **bootstrap** – the output container to hold indices to data vectors for the bootstrap set


    * **oob** – the output container to hold indices to data vectors for the out of bag set



#### make_boostrap_and_oob_sets()
makeBoostrapAndOobSets(self: hoot.libpyhoot.DataFrame, arg0: List[int], arg1: List[int]) -> None

> Creates bootstrap and out of bag sets with replacement


* **Parameters**

    
    * **bootstrap** – the output container to hold indices to data vectors for the bootstrap set


    * **oob** – the output container to hold indices to data vectors for the out of bag set



#### _static_ null()
Returns what DataFrame considers a null value (NaN in double land).


#### remapClassLabels(_ = Non_ )

#### remap_class_labels()
remapClassLabels(self: hoot.libpyhoot.DataFrame, arg0: Dict[str, str]) -> None

Assignment operator, copies all data. Potentially very expensive.


#### restoreClassLabels(_ = Non_ )

#### restore_class_labels()
restoreClassLabels(self: hoot.libpyhoot.DataFrame) -> None

Restores the list of class labels from the backup (use after creating binary classes)


#### selectRandomFactors(_ = Non_ )

#### select_random_factors()
selectRandomFactors(self: hoot.libpyhoot.DataFrame, arg0: int, arg1: List[int]) -> None

Random picks indices of m factors without replacement


* **Parameters**

    **fIndices** – a list of the resulting factor indices that


has already been resized to the number of requested factors


#### setAllFactorsActive(_ = Non_ )

#### setBinaryClassLabels(_ = Non_ )

#### setDataElement(_ = Non_ )

#### setFactorLabels(_ = Non_ )

#### setFactorType(_ = Non_ )

#### setFactorTypes(_ = Non_ )

#### setNullTreatment(_ = Non_ )

#### set_all_factors_active()
setAllFactorsActive(self: hoot.libpyhoot.DataFrame) -> None

Adds all factors to the active factor list.


#### set_binary_class_labels()
setBinaryClassLabels(self: hoot.libpyhoot.DataFrame, arg0: str) -> None

Goes through the training label list and renames all classes not matching posClass
to “other”

Use restoreClassLabels to restore to original scheme


* **Parameters**

    **posClass** – the positive class label



#### set_data_element()
setDataElement(self: hoot.libpyhoot.DataFrame, arg0: int, arg1: int, arg2: float) -> None

Sets the value of a single data element.


#### set_factor_labels()
setFactorLabels(self: hoot.libpyhoot.DataFrame, arg0: List[str]) -> None

Copies the factor names into an internal vector (not strictly needed inside the data set)


#### set_factor_type()
setFactorType(self: hoot.libpyhoot.DataFrame, arg0: int, arg1: int) -> None

Sets one factor type to one of Nominal or Numeric


#### set_factor_types()
setFactorTypes(self: hoot.libpyhoot.DataFrame, arg0: List[int]) -> None

Sets the factor type to one of Nominal or Numeric


#### set_null_treatment()
setNullTreatment(self: hoot.libpyhoot.DataFrame, arg0: int, arg1: int) -> None

Set the null treatment to one of NullAsMissingValue or NullAsValue. The exact way that a
null will be treated will depend on the algorithm that operates on the data.


#### sortIndicesOnFactorValue(_ = Non_ )

#### sort_indices_on_factor_value()
sortIndicesOnFactorValue(self: hoot.libpyhoot.DataFrame, arg0: List[int], arg1: int) -> None

Sorts a vector of indices to data vectors by the selected factor
value.


* **Parameters**

    
    * **indices** – the input/output containing the data vector indices


    * **fIdx** – the factor index on the data vector



#### to_list(self: hoot.libpyhoot.DataFrame)

#### validateData(_ = Non_ )

#### validate_data()
validateData(self: hoot.libpyhoot.DataFrame) -> None

Checks to ensure that there is a value for each factor.  If all values are the
same then the factor is deactivated.


### _class_ hoot.libpyhoot.DataSamples()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### get(self: hoot.libpyhoot.DataSamples, arg0: int)

#### getUniqueLabels(_ = Non_ )

#### get_unique_labels()
getUniqueLabels(self: hoot.libpyhoot.DataSamples) -> List[str]


#### toDataFrame(_ = Non_ )

#### to_data_frame()
toDataFrame(self: hoot.libpyhoot.DataSamples, arg0: float) -> Tgs::DataFrame


### _class_ hoot.libpyhoot.Element()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### addTags(_ = Non_ )

#### add_tags()
addTags(self: hoot.libpyhoot.Element, arg0: hoot::Tags) -> None


#### clear(self: hoot.libpyhoot.Element)

#### clone(self: hoot.libpyhoot.Element)

#### getChangeset(_ = Non_ )

#### getCircularError(_ = Non_ )

#### getElementId(_ = Non_ )

#### getElementType(_ = Non_ )

#### getId(_ = Non_ )

#### getRawCircularError(_ = Non_ )

#### getStatus(_ = Non_ )

#### getStatusString(_ = Non_ )

#### getTag(_ = Non_ )

#### getTagCount(_ = Non_ )

#### getTags(_ = Non_ )

#### getTimestamp(_ = Non_ )

#### getUid(_ = Non_ )

#### getUser(_ = Non_ )

#### getVersion(_ = Non_ )

#### getVisible(_ = Non_ )

#### get_changeset()
getChangeset(self: hoot.libpyhoot.Element) -> int


#### get_circular_error()
getCircularError(self: hoot.libpyhoot.Element) -> float

Circular Error is in meters to 2 standard deviations. In other words it is about the 95%
confidence interval assuming a normal distribution.


#### get_element_id()
getElementId(self: hoot.libpyhoot.Element) -> hoot::ElementId


#### get_element_type()
getElementType(self: hoot.libpyhoot.Element) -> hoot::ElementType


#### get_id()
getId(self: hoot.libpyhoot.Element) -> int


#### get_raw_circular_error()
getRawCircularError(self: hoot.libpyhoot.Element) -> float


#### get_status()
getStatus(self: hoot.libpyhoot.Element) -> hoot::Status


#### get_status_string()
getStatusString(self: hoot.libpyhoot.Element) -> QString


#### get_tag()
getTag(self: hoot.libpyhoot.Element, arg0: QString) -> QString


#### get_tag_count()
getTagCount(self: hoot.libpyhoot.Element) -> int


#### get_tags()
getTags(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. getTags(self: hoot.libpyhoot.Element) -> hoot::Tags


2. getTags(self: hoot.libpyhoot.Element) -> hoot::Tags


#### get_timestamp()
getTimestamp(self: hoot.libpyhoot.Element) -> int


#### get_uid()
getUid(self: hoot.libpyhoot.Element) -> int


#### get_user()
getUser(self: hoot.libpyhoot.Element) -> QString


#### get_version()
getVersion(self: hoot.libpyhoot.Element) -> int


#### get_visible()
getVisible(self: hoot.libpyhoot.Element) -> bool


#### hasCircularError(_ = Non_ )

#### hasSameNonMetadataTags(_ = Non_ )

#### hasTag(_ = Non_ )

#### has_circular_error()
hasCircularError(self: hoot.libpyhoot.Element) -> bool


#### has_same_non_metadata_tags()
hasSameNonMetadataTags(self: hoot.libpyhoot.Element, arg0: hoot.libpyhoot.Element) -> bool

Compares information tags with another element
:param other: element to compare this element’s tags with
:returns: true if this element has the same information tags as the other element;

> false otherwise


#### has_tag()
hasTag(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. hasTag(self: hoot.libpyhoot.Element, arg0: QString) -> bool


2. hasTag(self: hoot.libpyhoot.Element, arg0: QString, arg1: QString) -> bool


#### isUnknown(_ = Non_ )

#### is_unknown()
isUnknown(self: hoot.libpyhoot.Element) -> bool


#### removeTag(_ = Non_ )

#### remove_tag()
removeTag(self: hoot.libpyhoot.Element, arg0: QString) -> None


#### setChangeset(_ = Non_ )

#### setCircularError(_ = Non_ )

#### setId(_ = Non_ )

#### setStatus(_ = Non_ )

#### setTag(_ = Non_ )

#### setTags(_ = Non_ )

#### setTimestamp(_ = Non_ )

#### setUid(_ = Non_ )

#### setUser(_ = Non_ )

#### setVersion(_ = Non_ )

#### setVisible(_ = Non_ )

#### set_changeset()
setChangeset(self: hoot.libpyhoot.Element, arg0: int) -> None


#### set_circular_error()
setCircularError(self: hoot.libpyhoot.Element, arg0: float) -> None


#### set_id()
setId(self: hoot.libpyhoot.Element, arg0: int) -> None


#### set_status()
setStatus(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. setStatus(self: hoot.libpyhoot.Element, arg0: hoot::Status) -> None


2. setStatus(self: hoot.libpyhoot.Element, arg0: int) -> None


#### set_tag()
setTag(self: hoot.libpyhoot.Element, arg0: QString, arg1: QString) -> None


#### set_tags()
setTags(self: hoot.libpyhoot.Element, arg0: hoot::Tags) -> None


#### set_timestamp()
setTimestamp(self: hoot.libpyhoot.Element, arg0: int) -> None


#### set_uid()
setUid(self: hoot.libpyhoot.Element, arg0: int) -> None


#### set_user()
setUser(self: hoot.libpyhoot.Element, arg0: QString) -> None


#### set_version()
setVersion(self: hoot.libpyhoot.Element, arg0: int) -> None


#### set_visible()
setVisible(self: hoot.libpyhoot.Element, arg0: bool) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.Element) -> QString


### _class_ hoot.libpyhoot.ElementCriterion()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.ElementId()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.ElementId) -> None


2. __init__(self: hoot.libpyhoot.ElementId, arg0: QString) -> None


#### getId(_ = Non_ )

#### getType(_ = Non_ )

#### get_id()
getId(self: hoot.libpyhoot.ElementId) -> int


#### get_type()
getType(self: hoot.libpyhoot.ElementId) -> hoot::ElementType


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementId) -> QString


### _class_ hoot.libpyhoot.ElementOsmMapVisitorPy()
Bases: `hoot.libpyhoot.ElementVisitor`


#### \__init__(self: hoot.libpyhoot.ElementOsmMapVisitorPy)

#### _property_ function()
function is the user defined function that will be called for all elements. Elements can be
modified directly by the user function.


### _class_ hoot.libpyhoot.ElementVisitor()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

### _class_ hoot.libpyhoot.EuclideanDistanceExtractor()
Bases: `hoot.libpyhoot.FeatureExtractor`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.EuclideanDistanceExtractor) -> None


2. __init__(self: hoot.libpyhoot.EuclideanDistanceExtractor, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.EuclideanDistanceExtractor, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


#### combinedEnvelopeDiagonalDistance(_ = Non_ )

#### combined_envelope_diagonal_distance()
combinedEnvelopeDiagonalDistance(self: hoot.libpyhoot.EuclideanDistanceExtractor, arg0: hoot::OsmMap, arg1: hoot::Element, arg2: hoot::Element) -> float


#### distance(\*args, \*\*kwargs)
Overloaded function.


1. distance(self: hoot.libpyhoot.EuclideanDistanceExtractor, arg0: hoot::OsmMap, arg1: hoot::Element, arg2: hoot::Element) -> float


2. distance(self: hoot.libpyhoot.EuclideanDistanceExtractor, arg0: hoot::OsmMap, arg1: List[hoot::Element], arg2: List[hoot::Element]) -> numpy.ndarray[numpy.float64]

This override to the distance function is pyhoot specific and allows you to calculate distance
on an array of values in one pass.

Returns:

    A numpy array of the calculated distances.


#### extract(\*args, \*\*kwargs)
Overloaded function.


1. extract(self: hoot.libpyhoot.FeatureExtractor, arg0: hoot::OsmMap, arg1: hoot::Element, arg2: hoot::Element) -> float

extract extracts a feature from a given pair of elements.

The feature may be something like the distance between colors, the overlap of two polygons,
etc.


1. extract(self: hoot.libpyhoot.FeatureExtractor, map: hoot::OsmMap, target: List[hoot::Element], candidate: List[hoot::Element], ignored: List[bool] = []) -> numpy.ndarray[numpy.float64]

This override to the distance function is pyhoot specific and allows you to calculate distance
on an array of values in one pass.


#### getFactorType(_ = Non_ )

#### getNullTreatment(_ = Non_ )

#### get_factor_type()
getFactorType(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::FactorType

getFactorType returns the factor type for this feature/factor (Nominal or Numeric).


#### get_null_treatment()
getNullTreatment(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::NullTreatment

getNullTreatment returns the null treatment for this feature/factor (NullAsValue or
NullAsMissingValue).


#### isNull(_ = Non_ )

#### _static_ is_null()
isNull(arg0: float) -> bool


#### setConfiguration(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.EuclideanDistanceExtractor, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.FeatureExtractor) -> QString


### _class_ hoot.libpyhoot.ExactStringDistance()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(self: hoot.libpyhoot.ExactStringDistance)

#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


### _class_ hoot.libpyhoot.Factory()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.Factory)

#### getObjectNamesByBase(_ = Non_ )

#### _static_ get_object_names_by_base()
getObjectNamesByBase(arg0: QString) -> List[str]

returns all registered classes that implement the given base class


### _class_ hoot.libpyhoot.FeatureExtractor()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### extract(\*args, \*\*kwargs)
Overloaded function.


1. extract(self: hoot.libpyhoot.FeatureExtractor, arg0: hoot::OsmMap, arg1: hoot::Element, arg2: hoot::Element) -> float

extract extracts a feature from a given pair of elements.

The feature may be something like the distance between colors, the overlap of two polygons,
etc.


1. extract(self: hoot.libpyhoot.FeatureExtractor, map: hoot::OsmMap, target: List[hoot::Element], candidate: List[hoot::Element], ignored: List[bool] = []) -> numpy.ndarray[numpy.float64]

This override to the distance function is pyhoot specific and allows you to calculate distance
on an array of values in one pass.


#### getFactorType(_ = Non_ )

#### getNullTreatment(_ = Non_ )

#### get_factor_type()
getFactorType(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::FactorType

getFactorType returns the factor type for this feature/factor (Nominal or Numeric).


#### get_null_treatment()
getNullTreatment(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::NullTreatment

getNullTreatment returns the null treatment for this feature/factor (NullAsValue or
NullAsMissingValue).


#### isNull(_ = Non_ )

#### _static_ is_null()
isNull(arg0: float) -> bool


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.FeatureExtractor) -> QString


### _class_ hoot.libpyhoot.HasNameCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(self: hoot.libpyhoot.HasNameCriterion)

#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.IoUtils()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### anyAreSupportedOgrFormats(_ = Non_ )

#### _static_ any_are_supported_ogr_formats()
anyAreSupportedOgrFormats(arg0: QStringList, arg1: bool) -> bool

Determines if any in a set of inputs paths are OGR supported formats


* **Parameters**

    
    * **inputs** – input paths


    * **allowDir** – if true; then a directory can be passed as an input



* **Returns**

    true if any of the inputs passed in are supported by OGR; false otherwise



#### areStreamableInputs(_ = Non_ )

#### areStreamableIo(_ = Non_ )

#### areSupportedOgrFormats(_ = Non_ )

#### areValidStreamingOps(_ = Non_ )

#### _static_ are_streamable_inputs()
areStreamableInputs(arg0: QStringList, arg1: bool) -> bool

Determines whether inputs and are streamable data sources (associated
readers/writers must implemented the partial map interfaces)


* **Parameters**

    
    * **inputs** – data sources


    * **logUnstreamable** – if true, a message is logged to indicate the input being parsed is not


a streamable input
:returns: true if all inputs are streamable; false otherwise


#### _static_ are_streamable_io()
areStreamableIo(arg0: QStringList, arg1: QString) -> bool

Determines whether both inputs and output are streamable data sources (associated
readers/writers must implemented the partial map interfaces)


* **Parameters**

    
    * **inputs** – data sources


    * **output** – data destination



* **Returns**

    true if all formats are streamable; false otherwise



#### _static_ are_supported_ogr_formats()
areSupportedOgrFormats(arg0: QStringList, arg1: bool) -> bool

Determines if a set of inputs paths are all OGR supported formats


* **Parameters**

    
    * **inputs** – input paths


    * **allowDir** – if true; then a directory can be passed as an input



* **Returns**

    true if all inputs passed in are supported by OGR; false otherwise



#### _static_ are_valid_streaming_ops()
areValidStreamingOps(arg0: QStringList) -> bool

Return true if all the specified operations are valid streaming operations.

There are some ops that require the whole map be available in RAM (e.g. remove duplicate
nodes). These operations are not applicable for streaming.


* **Parameters**

    **ops** – class names of operation to determine streamability of



* **Returns**

    true if all inputs represent streamable operations; false otherwise



#### className(_ = Non_ )

#### _static_ class_name()
className() -> QString


#### expandInputs(_ = Non_ )

#### _static_ expand_inputs()
expandInputs(arg0: QStringList) -> QStringList

Returns all valid input file paths expanding any paths by looking inside of VSI files


* **Parameters**

    **inputs** – one or more input files



* **Returns**

    a list of file paths



#### getFilteredInputStream(_ = Non_ )

#### getOutputUrlFromInput(_ = Non_ )

#### getSupportedInputsRecursively(_ = Non_ )

#### _static_ get_filtered_input_stream()
getFilteredInputStream(arg0: hoot::ElementInputStream, arg1: QStringList) -> hoot::ElementInputStream

Get an input stream set up to be filtered by operations


* **Parameters**

    
    * **streamToFilter** – the stream to be filtered


    * **ops** – a list of Hoot operation class names to use for inline filtering on the input stream



* **Returns**

    an input stream



#### _static_ get_output_url_from_input()
getOutputUrlFromInput(arg0: QString, arg1: QString, arg2: QString) -> QString

Creates an output URL based on an input URL that will not overwrite the input


* **Parameters**

    
    * **inputUrl** – the input URL to generate an output URL for


    * **appendText** – optional text to append to the output URL; not optional if outputFormat is


not specified
:param outputFormat: optional output format made up of a file extension (e.g. osm) or a custom
output directory extension (e.g. shp); not option if appendText is not specified
:returns: a URL


#### _static_ get_supported_inputs_recursively()
getSupportedInputsRecursively(arg0: QStringList, arg1: QStringList) -> QStringList

Returns all file paths under a directory point to a supported input format


* **Parameters**

    
    * **topLevelPaths** – one or more directory paths


    * **nameFilters** – wildcard filters for path exclusion; e.g. *myFile*, 

    ```
    *
    ```

    .json



* **Returns**

    a list of file paths



#### isStreamableInput(_ = Non_ )

#### isStreamableIo(_ = Non_ )

#### isStreamableOutput(_ = Non_ )

#### isSupportedInputFormat(_ = Non_ )

#### isSupportedOgrFormat(_ = Non_ )

#### isSupportedOsmFormat(_ = Non_ )

#### isSupportedOutputFormat(_ = Non_ )

#### isUrl(_ = Non_ )

#### _static_ is_streamable_input()
isStreamableInput(arg0: QString) -> bool

Determines if a URL points to a valid streamable input


* **Parameters**

    **url** – the URL to examine



* **Returns**

    true if the URL points to a valid streamable input; false otherwise



#### _static_ is_streamable_io()
isStreamableIo(arg0: QString, arg1: QString) -> bool

Determines whether both input and output are streamable data sources (associated
readers/writers must implemented the partial map interfaces)


* **Parameters**

    
    * **input** – data source


    * **output** – data destination



* **Returns**

    true if both formats are streamable; false otherwise



#### _static_ is_streamable_output()
isStreamableOutput(arg0: QString) -> bool

Determines if a URL points to a valid streamable output


* **Parameters**

    **url** – the URL to examine



* **Returns**

    true if the URL points to a valid streamable output; false otherwise



#### _static_ is_supported_input_format()
isSupportedInputFormat(arg0: QString) -> bool

Determines if the a URL is a supported input format


* **Parameters**

    **url** – the URL to examine



* **Returns**

    true if the URL points to a valid input format; false otherwise



#### _static_ is_supported_ogr_format()
isSupportedOgrFormat(arg0: QString, arg1: bool) -> bool

Returns true if the input format is a Hootenanny supported OGR format


* **Parameters**

    
    * **input** – input path


    * **allowDir** – if true; then a directory can be passed as an input



* **Returns**

    true if the input is supported by OGR; false otherwise



#### _static_ is_supported_osm_format()
isSupportedOsmFormat(arg0: QString) -> bool

Returns true if the input format is a Hootenanny supported OSM format


* **Parameters**

    **input** – input path



* **Returns**

    true if the input is OSM and supported; false otherwise



#### _static_ is_supported_output_format()
isSupportedOutputFormat(arg0: QString) -> bool

Determines if the a URL is a supported output format


* **Parameters**

    **url** – the URL to examine



* **Returns**

    true if the URL points to a valid output format; false otherwise



#### _static_ is_url()
isUrl(arg0: QString) -> bool

Determines if an input string is a URL by the hoot definition


* **Parameters**

    **str** – string to examine



* **Returns**

    true if the input is a hoot URL, false otherwise



#### loadMap(_ = Non_ )

#### loadMaps(_ = Non_ )

#### _static_ load_map()
loadMap(map: hoot.libpyhoot.OsmMap, path: QString, useFileId: bool = True, defaultStatus: hoot.libpyhoot.Status = <hoot.libpyhoot.Status object at 0x7fe32753b650>, translationScript: QString = ‘’, ogrFeatureLimit: int = -1, jobSource: QString = ‘’, numTasks: int = -1) -> None

Loads an OSM map into an OsmMap object


* **Parameters**

    
    * **map** – the object to load the map into


    * **path** – the file path to load the map from


    * **useFileId** – if true, uses the element ID’s in the map file; otherwise, generates new


element ID’s
:param defaultStatus: the hoot status to assign to all elements
:param translationScript: script used to translate data; required only if the input is an OGR
format; ignored otherwise
:param ogrFeatureLimit: limit of features to read per input; applicable to OGR inputs only;
ignored otherwise
:param jobSource: job name for status reporting; applicable to OGR inputs only; ignored otherwise
:param numTasks: number of job tasks being performed for status reporting; applicable to OGR
inputs only; ignored otherwise


#### _static_ load_maps()
loadMaps(arg0: hoot.libpyhoot.OsmMap, arg1: QStringList, arg2: bool, arg3: hoot.libpyhoot.Status, arg4: QString, arg5: int, arg6: QString, arg7: int) -> None

Loads multiple OSM maps into an OsmMap object


* **Parameters**

    
    * **map** – the object to load the map into


    * **paths** – the file paths to load the maps from


    * **useFileId** – if true, uses the element ID’s in the map file; otherwise, generates new


element ID’s
:param defaultStatus: the hoot status to assign to all elements
:param translationScript: script used to translate data; required only if the input is an OGR
format; ignored otherwise
:param ogrFeatureLimit: limit of features to read per input; applicable to OGR inputs only;
ignored otherwise
:param jobSource: job name for status reporting; applicable to OGR inputs only; ignored otherwise
:param numTasks: number of job tasks being performed for status reporting; applicable to OGR
inputs only; ignored otherwise


#### ogrPathAndLayerToLayer(_ = Non_ )

#### ogrPathAndLayerToPath(_ = Non_ )

#### ogrPathsAndLayersToPaths(_ = Non_ )

#### _static_ ogr_path_and_layer_to_layer()
ogrPathAndLayerToLayer(arg0: QString) -> None

Converts the OGR input with layer syntax to the layer


* **Parameters**

    **input** – the input to convert



* **Returns**

    a layer name



#### _static_ ogr_path_and_layer_to_path()
ogrPathAndLayerToPath(arg0: QString) -> None

Converts the OGR input with layer syntax to the input path


* **Parameters**

    **input** – the input to convert



* **Returns**

    a path



#### _static_ ogr_paths_and_layers_to_paths()
ogrPathsAndLayersToPaths(arg0: QStringList) -> None

Converts the OGR inputs with layer syntax to just the inputs


* **Parameters**

    **inputs** – the inputs to convert



* **Returns**

    a list of paths



#### saveMap(_ = Non_ )

#### _static_ save_map()
saveMap(arg0: hoot.libpyhoot.OsmMap, arg1: QString) -> None

Saves an OSM map to an OsmMap object


* **Parameters**

    
    * **map** – the map object to save


    * **path** – the file path to save the map to



#### toStreamingOps(_ = Non_ )

#### _static_ to_streaming_ops()
toStreamingOps(arg0: QStringList) -> QList<std::shared_ptr<hoot::ElementVisitor> >

toStreamingOps returns a list of instantiated streaming operation objects
:param ops: the class names of the operations to instantiate
:returns: a list of instantiated visitor objects (OsmMapOperations are not streamable)
@throws IllegalArgumentException if a class name is passed in that does not represent a
streamable operation (not ElementVisitor or ConstElementVisitor) or a class name represents a
class that is an OsmMap consumer (implements OsmMapConsumer or ConstOsmMapConsumer)


#### writeOutputDir(_ = Non_ )

#### _static_ write_output_dir()
writeOutputDir(arg0: QString) -> None

Writes an output directory


* **Parameters**

    **dirName** – name of the directory to write



### _class_ hoot.libpyhoot.KskipBigramDistance()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(self: hoot.libpyhoot.KskipBigramDistance)

#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


### _class_ hoot.libpyhoot.LevenshteinDistance()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.LevenshteinDistance) -> None


2. __init__(self: hoot.libpyhoot.LevenshteinDistance, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.LevenshteinDistance, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


#### setConfiguration(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.LevenshteinDistance, arg0: hoot::Settings) -> None

Set the configuration for this object.


### _class_ hoot.libpyhoot.LinearCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(self: hoot.libpyhoot.LinearCriterion)

#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.Log()
Bases: `pybind11_builtins.pybind11_object`


#### DEBUG(_ = <WarningLevel.DEBUG: 1000_ )

#### ERROR(_ = <WarningLevel.ERROR: 4000_ )

#### FATAL(_ = <WarningLevel.FATAL: 5000_ )

#### INFO(_ = <WarningLevel.INFO: 2000_ )

#### NONE(_ = <WarningLevel.NONE: 0_ )

#### STATUS(_ = <WarningLevel.STATUS: 2500_ )

#### TRACE(_ = <WarningLevel.TRACE: 500_ )

#### WARN(_ = <WarningLevel.WARN: 3000_ )

#### _class_ WarningLevel()
Bases: `pybind11_builtins.pybind11_object`

Members:

NONE

TRACE

DEBUG

INFO

STATUS

WARN

ERROR

FATAL


#### DEBUG(_ = <WarningLevel.DEBUG: 1000_ )

#### ERROR(_ = <WarningLevel.ERROR: 4000_ )

#### FATAL(_ = <WarningLevel.FATAL: 5000_ )

#### INFO(_ = <WarningLevel.INFO: 2000_ )

#### NONE(_ = <WarningLevel.NONE: 0_ )

#### STATUS(_ = <WarningLevel.STATUS: 2500_ )

#### TRACE(_ = <WarningLevel.TRACE: 500_ )

#### WARN(_ = <WarningLevel.WARN: 3000_ )

#### \__init__(self: hoot.libpyhoot.Log.WarningLevel, value: int)

#### _property_ name()

#### _property_ value()

#### \__init__(\*args, \*\*kwargs)

#### _static_ bad_string()

#### getInstance(_ = Non_ )

#### getLevel(_ = Non_ )

#### getLevelAsString(_ = Non_ )

#### getWarnMessageLimit(_ = Non_ )

#### _static_ get_instance()
getInstance() -> hoot.libpyhoot.Log


#### get_level()
getLevel(self: hoot.libpyhoot.Log) -> hoot::Log::WarningLevel


#### get_level_as_string()
getLevelAsString(self: hoot.libpyhoot.Log) -> QString


#### _static_ get_warn_message_limit()
getWarnMessageLimit() -> int


#### isDebugEnabled(_ = Non_ )

#### isInfoEnabled(_ = Non_ )

#### is_debug_enabled()
isDebugEnabled(self: hoot.libpyhoot.Log) -> bool


#### is_info_enabled()
isInfoEnabled(self: hoot.libpyhoot.Log) -> bool


#### levelFromString(_ = Non_ )

#### levelToString(_ = Non_ )

#### _static_ level_from_string()
levelFromString(arg0: QString) -> hoot::Log::WarningLevel


#### _static_ level_to_string()
levelToString(arg0: hoot::Log::WarningLevel) -> QString


#### _static_ log(\*args, \*\*kwargs)
Overloaded function.


1. log(arg0: hoot::Log::WarningLevel, arg1: str) -> None


2. log(arg0: hoot::Log::WarningLevel, arg1: str, arg2: str, arg3: str, arg4: int) -> None


#### progress(self: hoot.libpyhoot.Log, arg0: hoot::Log::WarningLevel, arg1: str, arg2: str, arg3: str, arg4: int)

#### setDecorateLogs(_ = Non_ )

#### setLevel(_ = Non_ )

#### set_decorate_logs()
setDecorateLogs(self: hoot.libpyhoot.Log, arg0: bool) -> None


#### set_level()
setLevel(self: hoot.libpyhoot.Log, arg0: hoot::Log::WarningLevel) -> None


### _class_ hoot.libpyhoot.MapCleaner()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.MapCleaner)

#### apply(self: hoot.libpyhoot.MapCleaner, arg0: hoot.libpyhoot.OsmMap)

### _class_ hoot.libpyhoot.MapComparator()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.MapComparator)

#### isMatch(_ = Non_ )

#### is_match()
isMatch(self: hoot.libpyhoot.MapComparator, arg0: hoot.libpyhoot.OsmMap, arg1: hoot.libpyhoot.OsmMap) -> bool

Returns true if the maps are essentially the same. Minor differences in node locations are
ignored.


#### setErrorLimit(_ = Non_ )

#### setIgnoreTagKeys(_ = Non_ )

#### setUseDateTime(_ = Non_ )

#### set_error_limit()
setErrorLimit(self: hoot.libpyhoot.MapComparator, arg0: int) -> None


#### set_ignore_tag_keys()
setIgnoreTagKeys(self: hoot.libpyhoot.MapComparator, arg0: QStringList) -> None


#### set_ignore_uuid(self: hoot.libpyhoot.MapComparator)

#### set_use_date_time()
setUseDateTime(self: hoot.libpyhoot.MapComparator) -> None


### _class_ hoot.libpyhoot.MapProjector()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### projectToPlanar(_ = Non_ )

#### projectToWgs84(_ = Non_ )

#### _static_ project_to_planar()
projectToPlanar(arg0: hoot::OsmMap) -> None

Uses createPlanarProjection to create a planar projection and then reprojects the given map.
Uses the envelope of the map to determine the projection.


#### _static_ project_to_wgs84()
projectToWgs84(arg0: hoot::OsmMap) -> None


### _class_ hoot.libpyhoot.MatchClassification()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.MatchClassification) -> None


2. __init__(self: hoot.libpyhoot.MatchClassification, arg0: float, arg1: float, arg2: float) -> None

The match classification object represents the classification of a match. A match may be in
one of three states:

> 
> * match - we’re confident the two elements represent the same feature


> * miss - we’re confident the two elements do not represent the same feature


> * review - we’re confident the data is ambiguous or wrong and it requires human review

Of course, there are different levels to each of those states. This class represents those
varying levels of confidence.


#### _property_ match()

#### _property_ miss()

#### _property_ review()

#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.MatchClassification) -> QString


### _class_ hoot.libpyhoot.MatchCreator()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

### _class_ hoot.libpyhoot.MatchFeatureExtractor()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.MatchFeatureExtractor, arg0: bool)

#### addMatchCreator(_ = Non_ )

#### add_match_creator()
addMatchCreator(self: hoot.libpyhoot.MatchFeatureExtractor, arg0: hoot.libpyhoot.MatchCreator) -> None

Adds a match creator to the list of matches that will be evaluated. There must be at least one.
The match creator’s matches must implement MatchDetails.


#### getResults(_ = Non_ )

#### getSampleList(_ = Non_ )

#### getSamples(_ = Non_ )

#### get_results()
getResults(self: hoot.libpyhoot.MatchFeatureExtractor, arg0: bool) -> QString

Returns the results as an ARFF file: [http://www.cs.waikato.ac.nz/ml/weka/arff.html](http://www.cs.waikato.ac.nz/ml/weka/arff.html)


#### get_sample_list()
getSampleList(self: hoot.libpyhoot.MatchFeatureExtractor) -> List[Dict[QString, float]]


#### get_samples()
getSamples(self: hoot.libpyhoot.MatchFeatureExtractor) -> hoot.libpyhoot.DataSamples


#### processMap(_ = Non_ )

#### process_map()
processMap(self: hoot.libpyhoot.MatchFeatureExtractor, arg0: hoot.libpyhoot.OsmMap) -> None

Evaluates all the features in the given map.


### _class_ hoot.libpyhoot.MatchThreshold()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.MatchThreshold) -> None


2. __init__(self: hoot.libpyhoot.MatchThreshold, arg0: float, arg1: float, arg2: float) -> None

Constructor


* **Parameters**

    
    * **matchThreshold** – the score threshold at which a match object is considered a match


    * **missThreshold** – the score threshold at which a match object is considered a miss


    * **reviewThreshold** – the score threshold at which a match object is considered a review


    * **validateRange** – if true, the range (0.0, 1.0] will be honored. For conflate usage we


generally want to honor that range for thresholds. In some instances, though, we may not want
to.


#### _property_ match_threshold()

#### _property_ miss_threshold()

#### _property_ review_threshold()

#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.MatchThreshold) -> QString


### _class_ hoot.libpyhoot.MaxWordSetDistance()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.MaxWordSetDistance) -> None


2. __init__(self: hoot.libpyhoot.MaxWordSetDistance, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.MaxWordSetDistance, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.MaxWordSetDistance, arg0: hoot.libpyhoot.StringDistance) -> None


2. __init__(self: hoot.libpyhoot.MaxWordSetDistance, arg0: hoot::Settings, arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a Settings object and StringDistance function.


1. __init__(self: hoot.libpyhoot.MaxWordSetDistance, arg0: Dict[QString, QString], arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a dict of strings and a StringDistance function.


#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


#### setConfiguration(_ = Non_ )

#### setStringDistance(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.MaxWordSetDistance, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_string_distance()
setStringDistance(self: hoot.libpyhoot.MaxWordSetDistance, arg0: hoot.libpyhoot.StringDistance) -> None


### _class_ hoot.libpyhoot.MeanWordSetDistance()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.MeanWordSetDistance) -> None


2. __init__(self: hoot.libpyhoot.MeanWordSetDistance, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.MeanWordSetDistance, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.MeanWordSetDistance, arg0: hoot.libpyhoot.StringDistance) -> None


2. __init__(self: hoot.libpyhoot.MeanWordSetDistance, arg0: hoot::Settings, arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a Settings object and StringDistance function.


1. __init__(self: hoot.libpyhoot.MeanWordSetDistance, arg0: Dict[QString, QString], arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a dict of strings and a StringDistance function.


#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


#### setConfiguration(_ = Non_ )

#### setStringDistance(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.MeanWordSetDistance, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_string_distance()
setStringDistance(self: hoot.libpyhoot.MeanWordSetDistance, arg0: hoot.libpyhoot.StringDistance) -> None


### _class_ hoot.libpyhoot.MinSumWordSetDistance()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.MinSumWordSetDistance) -> None


2. __init__(self: hoot.libpyhoot.MinSumWordSetDistance, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.MinSumWordSetDistance, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.MinSumWordSetDistance, arg0: hoot.libpyhoot.StringDistance) -> None


2. __init__(self: hoot.libpyhoot.MinSumWordSetDistance, arg0: hoot::Settings, arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a Settings object and StringDistance function.


1. __init__(self: hoot.libpyhoot.MinSumWordSetDistance, arg0: Dict[QString, QString], arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a dict of strings and a StringDistance function.


#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


#### setConfiguration(_ = Non_ )

#### setStringDistance(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.MinSumWordSetDistance, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_string_distance()
setStringDistance(self: hoot.libpyhoot.MinSumWordSetDistance, arg0: hoot.libpyhoot.StringDistance) -> None


### _class_ hoot.libpyhoot.NameExtractor()
Bases: `hoot.libpyhoot.FeatureExtractor`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.NameExtractor) -> None


2. __init__(self: hoot.libpyhoot.NameExtractor, arg0: hoot::StringDistance) -> None


#### extract(\*args, \*\*kwargs)
Overloaded function.


1. extract(self: hoot.libpyhoot.FeatureExtractor, arg0: hoot::OsmMap, arg1: hoot::Element, arg2: hoot::Element) -> float

extract extracts a feature from a given pair of elements.

The feature may be something like the distance between colors, the overlap of two polygons,
etc.


1. extract(self: hoot.libpyhoot.FeatureExtractor, map: hoot::OsmMap, target: List[hoot::Element], candidate: List[hoot::Element], ignored: List[bool] = []) -> numpy.ndarray[numpy.float64]

This override to the distance function is pyhoot specific and allows you to calculate distance
on an array of values in one pass.


#### getFactorType(_ = Non_ )

#### getNullTreatment(_ = Non_ )

#### get_factor_type()
getFactorType(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::FactorType

getFactorType returns the factor type for this feature/factor (Nominal or Numeric).


#### get_null_treatment()
getNullTreatment(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::NullTreatment

getNullTreatment returns the null treatment for this feature/factor (NullAsValue or
NullAsMissingValue).


#### isNull(_ = Non_ )

#### _static_ is_null()
isNull(arg0: float) -> bool


#### setStringDistance(_ = Non_ )

#### set_string_distance()
setStringDistance(self: hoot.libpyhoot.NameExtractor, arg0: hoot::StringDistance) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.FeatureExtractor) -> QString


### _class_ hoot.libpyhoot.NoInformationCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.NoInformationCriterion) -> None


2. __init__(self: hoot.libpyhoot.NoInformationCriterion, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.NoInformationCriterion, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setConfiguration(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.NoInformationCriterion, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.NodeCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(self: hoot.libpyhoot.NodeCriterion)

#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.NotCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.NotCriterion) -> None


2. __init__(self: hoot.libpyhoot.NotCriterion, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.NotCriterion, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.NotCriterion, arg0: hoot::OsmMap) -> None


2. __init__(self: hoot.libpyhoot.NotCriterion, arg0: hoot.libpyhoot.ElementCriterion, 

```
*
```

args) -> None


3. __init__(self: hoot.libpyhoot.NotCriterion, arg0: hoot.libpyhoot.ElementCriterion) -> None


#### addCriterion(_ = Non_ )

#### add_criterion()
addCriterion(self: hoot.libpyhoot.NotCriterion, arg0: hoot.libpyhoot.ElementCriterion) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setConfiguration(_ = Non_ )

#### setOsmMap(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.NotCriterion, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_osm_map()
setOsmMap(self: hoot.libpyhoot.NotCriterion, arg0: hoot::OsmMap) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.OrCriterion()
Bases: `hoot.libpyhoot.ChainCriterion`


#### \__init__(self: hoot.libpyhoot.OrCriterion, \*args)

#### addCriterion(_ = Non_ )

#### add_criterion()
addCriterion(self: hoot.libpyhoot.ChainCriterion, arg0: hoot.libpyhoot.ElementCriterion) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setConfiguration(_ = Non_ )

#### setOsmMap(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.ChainCriterion, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_osm_map()
setOsmMap(self: hoot.libpyhoot.ChainCriterion, arg0: hoot::OsmMap) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.OsmJsonReader()
Bases: `hoot.libpyhoot.OsmMapReader`


#### \__init__(self: hoot.libpyhoot.OsmJsonReader)

#### getCopyright(_ = Non_ )

#### getGenerator(_ = Non_ )

#### getIgnoreDuplicates(_ = Non_ )

#### getTimestampBase(_ = Non_ )

#### getVersion(_ = Non_ )

#### get_copyright()
getCopyright(self: hoot.libpyhoot.OsmJsonReader) -> QString

getCopyright Copyright statement, if supplied in JSON
:returns: copyright string


#### get_generator()
getGenerator(self: hoot.libpyhoot.OsmJsonReader) -> QString

getGenerator Map generator name, if supplied in JSON
:returns: generator name string


#### get_ignore_duplicates()
getIgnoreDuplicates(self: hoot.libpyhoot.OsmMapReader) -> bool

Gets the ignore duplicates flag


#### get_timestamp_base()
getTimestampBase(self: hoot.libpyhoot.OsmJsonReader) -> QString

getTimestampBase OSM timestamp base, if supplied in JSON
:returns: timestamp base string


#### get_version()
getVersion(self: hoot.libpyhoot.OsmJsonReader) -> QString

getVersion Overpass API version, if that’s where JSON comes from
:returns: version string


#### isSupported(_ = Non_ )

#### isValidJson(_ = Non_ )

#### is_supported()
isSupported(self: hoot.libpyhoot.OsmMapReader, arg0: QString) -> bool

Returns true if the output URL is likely supported. This won’t necessarily do an exhaustive
check. It will look to see if the URL is properly formatted (e.g. ends in .osm, or starts
with postgresql:, etc.)


#### is_valid_json()
isValidJson(self: hoot.libpyhoot.OsmJsonReader, arg0: QString) -> bool


#### loadFromFile(_ = Non_ )

#### loadFromString(_ = Non_ )

#### load_from_file()
loadFromFile(self: hoot.libpyhoot.OsmJsonReader, arg0: QString) -> hoot.libpyhoot.OsmMap

loadFromFile - Reads the whole file as a string, passes it

    to loadFromString()


* **Parameters**

    **path** – 
    * Path to file




* **Returns**

    Smart pointer to the OSM map



#### load_from_string()
loadFromString(self: hoot.libpyhoot.OsmJsonReader, arg0: QString, arg1: hoot.libpyhoot.OsmMap) -> None

loadFromString - Builds a map from the JSON string. Throws a

    HootException with error and line number if JSON parsing fails


* **Parameters**

    **jsonStr** – 
    * input string, map - The OSM map to load it into




#### open(self: hoot.libpyhoot.OsmMapReader, arg0: QString)
Opens the specified URL for reading.


#### read(self: hoot.libpyhoot.OsmMapReader, arg0: hoot.libpyhoot.OsmMap)
Reads the specified map. When this method is complete the input will likely be closed.


#### setConfiguration(_ = Non_ )

#### setDefaultStatus(_ = Non_ )

#### setIgnoreDuplicates(_ = Non_ )

#### setKeepImmediatelyConnectedWaysOutsideBounds(_ = Non_ )

#### setLogWarningsForMissingElements(_ = Non_ )

#### setUseDataSourceIds(_ = Non_ )

#### setUseFileStatus(_ = Non_ )

#### setWarnOnVersionZeroElement(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.OsmJsonReader, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_default_status()
setDefaultStatus(self: hoot.libpyhoot.OsmMapReader, arg0: hoot.libpyhoot.Status) -> None

Determines the reader’s default element status


#### set_ignore_duplicates()
setIgnoreDuplicates(self: hoot.libpyhoot.OsmMapReader, arg0: bool) -> None

Set the ignore duplicates flag, when set to true, derived classes will ignore any element
who’s ID is already being used.  This is useful when elements cross bounding box boundaries
and multiple bounding boxes are being merged together.


#### set_keep_immediately_connected_ways_outside_bounds()
setKeepImmediatelyConnectedWaysOutsideBounds(self: hoot.libpyhoot.OsmJsonReader, arg0: bool) -> None


#### set_log_warnings_for_missing_elements()
setLogWarningsForMissingElements(self: hoot.libpyhoot.OsmJsonReader, arg0: bool) -> None


#### set_use_data_source_ids()
setUseDataSourceIds(self: hoot.libpyhoot.OsmMapReader, arg0: bool) -> None

Determines whether the reader should use the element id’s from the data being read


#### set_use_file_status()
setUseFileStatus(self: hoot.libpyhoot.OsmMapReader, arg0: bool) -> None

Uses the element status from the file


#### set_warn_on_version_zero_element()
setWarnOnVersionZeroElement(self: hoot.libpyhoot.OsmMapReader, arg0: bool) -> None


#### supportedFormats(_ = Non_ )

#### supported_formats()
supportedFormats(self: hoot.libpyhoot.OsmJsonReader) -> QString


### _class_ hoot.libpyhoot.OsmJsonWriter()
Bases: `hoot.libpyhoot.OsmMapWriter`


#### \__init__(self: hoot.libpyhoot.OsmJsonWriter)

#### close(self: hoot.libpyhoot.OsmJsonWriter)

#### getIsDebugMap(_ = Non_ )

#### get_is_debug_map()
getIsDebugMap(self: hoot.libpyhoot.OsmMapWriter) -> bool

Gets flag indicating the writer is writing a debug map so that extra debugging metadata can
be included in each implementation of the output formats


#### isSupported(_ = Non_ )

#### is_supported()
isSupported(self: hoot.libpyhoot.OsmJsonWriter, arg0: QString) -> bool


#### markupString(_ = Non_ )

#### _static_ markup_string()
markupString(arg0: QString) -> QString

Mark up a string so it can be used in JSON. This will add double quotes around the string too.


#### open(self: hoot.libpyhoot.OsmJsonWriter, arg0: QString)

#### setConfiguration(_ = Non_ )

#### setIncludeCircularError(_ = Non_ )

#### setIncludeCompatibilityTags(_ = Non_ )

#### setIsDebugMap(_ = Non_ )

#### setPrecision(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.OsmJsonWriter, arg0: hoot::Settings) -> None


#### set_include_circular_error()
setIncludeCircularError(self: hoot.libpyhoot.OsmJsonWriter, arg0: bool) -> None


#### set_include_compatibility_tags()
setIncludeCompatibilityTags(self: hoot.libpyhoot.OsmJsonWriter, arg0: bool) -> None


#### set_is_debug_map()
setIsDebugMap(self: hoot.libpyhoot.OsmMapWriter, arg0: bool) -> None

Sets flag indicating the writer is writing a debug map so that extra debugging metadata is
included in the output


#### set_precision()
setPrecision(self: hoot.libpyhoot.OsmJsonWriter, arg0: int) -> None


#### supportedFormats(_ = Non_ )

#### supported_formats()
supportedFormats(self: hoot.libpyhoot.OsmJsonWriter) -> QString


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.OsmJsonWriter, arg0: hoot.libpyhoot.OsmMap) -> QString

Very handy for testing.


#### write(self: hoot.libpyhoot.OsmJsonWriter, arg0: hoot.libpyhoot.OsmMap)

### _class_ hoot.libpyhoot.OsmMap()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.OsmMap)

#### addNode(_ = Non_ )

#### addNodes(_ = Non_ )

#### addRelation(_ = Non_ )

#### addWay(_ = Non_ )

#### add_node()
addNode(self: hoot.libpyhoot.OsmMap, arg0: hoot::Node) -> None


#### add_nodes()
addNodes(self: hoot.libpyhoot.OsmMap, arg0: List[hoot::Node]) -> None

Add all the nodes in the provided vector. This can be faster than calling addNode multiple
times.


#### add_relation()
addRelation(self: hoot.libpyhoot.OsmMap, arg0: hoot::Relation) -> None


#### add_way()
addWay(self: hoot.libpyhoot.OsmMap, arg0: hoot::Way) -> None


#### append(self: hoot.libpyhoot.OsmMap, arg0: hoot.libpyhoot.OsmMap, arg1: bool)
Append all the elements in input map to this map.

The default behavior is to skip an element from the map being appended from if it has the same
ID as an element in this map and the elements are considered identical. If the elements are
considered to be identical, an error occurs. Alternatively, the throwOutDupes parameter will
allow for overriding that behavior at the expense of not appending the elements.

:param map
@param: throwOutDupes if true, and elements in the map being appended from have the same IDs as
elements in this map, those elements are ignored
@throws if there is element ID overlap and throwOutDupes = false
@throws if the map being appended to is the same as the map being appended from
@throws if the map being appended to does not have the same projection as the map being
appended from


#### appendSource(_ = Non_ )

#### append_source()
appendSource(self: hoot.libpyhoot.OsmMap, arg0: QString) -> None


#### clear(self: hoot.libpyhoot.OsmMap)

#### containsNode(_ = Non_ )

#### containsRelation(_ = Non_ )

#### containsWay(_ = Non_ )

#### contains_node()
containsNode(self: hoot.libpyhoot.OsmMap, arg0: int) -> bool

Returns true if the node is in this map.


#### contains_relation()
containsRelation(self: hoot.libpyhoot.OsmMap, arg0: int) -> bool


#### contains_way()
containsWay(self: hoot.libpyhoot.OsmMap, arg0: int) -> bool


#### createNextNodeId(_ = Non_ )

#### createNextRelationId(_ = Non_ )

#### createNextWayId(_ = Non_ )

#### create_next_node_id()
createNextNodeId(self: hoot.libpyhoot.OsmMap) -> int


#### create_next_relation_id()
createNextRelationId(self: hoot.libpyhoot.OsmMap) -> int


#### create_next_way_id()
createNextWayId(self: hoot.libpyhoot.OsmMap) -> int


#### distance(element1, element2)
distance calculates the distance between two elements and returns the
result. It is assumed that the map is already in a planar projection.


#### getCachedRubberSheet(_ = Non_ )

#### getElement(_ = Non_ )

#### getElementCount(_ = Non_ )

#### getIdGenerator(_ = Non_ )

#### getIdSwap(_ = Non_ )

#### getIndex(_ = Non_ )

#### getListeners(_ = Non_ )

#### getName(_ = Non_ )

#### getNodeCount(_ = Non_ )

#### getNodeIds(_ = Non_ )

#### getNodes(_ = Non_ )

#### getParents(_ = Non_ )

#### getProjection(_ = Non_ )

#### getRelationCount(_ = Non_ )

#### getRelationIds(_ = Non_ )

#### getRelations(_ = Non_ )

#### getRoundabouts(_ = Non_ )

#### getSource(_ = Non_ )

#### getWayCount(_ = Non_ )

#### getWayIds(_ = Non_ )

#### getWays(_ = Non_ )

#### get_cached_rubber_sheet()
getCachedRubberSheet(self: hoot.libpyhoot.OsmMap) -> hoot::RubberSheet


#### get_element()
getElement(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. getElement(self: hoot.libpyhoot.OsmMap, arg0: hoot.libpyhoot.ElementId) -> hoot.libpyhoot.Element

getElement returns an element by ElementId


1. getElement(self: hoot.libpyhoot.OsmMap, arg0: hoot::ElementType, arg1: int) -> hoot.libpyhoot.Element

getElement returns an element by element type and id


#### get_element_count()
getElementCount(self: hoot.libpyhoot.OsmMap) -> int


#### get_id_generator()
getIdGenerator(self: hoot.libpyhoot.OsmMap) -> hoot::IdGenerator


#### get_id_swap()
getIdSwap(self: hoot.libpyhoot.OsmMap) -> hoot::IdSwap


#### get_index()
getIndex(self: hoot.libpyhoot.OsmMap) -> hoot::OsmMapIndex

This returns an index of the OsmMap. Adding or removing ways from the map will make the index
out of date and will require calling getIndex again.


#### get_listeners()
getListeners(self: hoot.libpyhoot.OsmMap) -> List[hoot::OsmMapListener]


#### get_name()
getName(self: hoot.libpyhoot.OsmMap) -> QString


#### get_node_count()
getNodeCount(self: hoot.libpyhoot.OsmMap) -> int


#### get_node_ids()
getNodeIds(self: hoot.libpyhoot.OsmMap) -> QSet<long>


#### get_nodes()
getNodes(self: hoot.libpyhoot.OsmMap) -> Dict[int, hoot.libpyhoot.Element]


#### get_parents()
getParents(self: hoot.libpyhoot.OsmMap, arg0: hoot.libpyhoot.ElementId) -> Set[hoot.libpyhoot.ElementId]


#### get_projection()
getProjection(self: hoot.libpyhoot.OsmMap) -> OGRSpatialReference

Returns the SRS for this map. The SRS should never be changed and defaults to WGS84.


#### get_relation_count()
getRelationCount(self: hoot.libpyhoot.OsmMap) -> int


#### get_relation_ids()
getRelationIds(self: hoot.libpyhoot.OsmMap) -> QSet<long>


#### get_relations()
getRelations(self: hoot.libpyhoot.OsmMap) -> __gnu_cxx::hash_map<long, std::shared_ptr<hoot::Relation>, __gnu_cxx::hash<long>, std::equal_to<long>, std::allocator<std::shared_ptr<hoot::Relation> > >


#### get_roundabouts()
getRoundabouts(self: hoot.libpyhoot.OsmMap) -> List[hoot::Roundabout]


#### get_source()
getSource(self: hoot.libpyhoot.OsmMap) -> QString


#### get_way_count()
getWayCount(self: hoot.libpyhoot.OsmMap) -> int


#### get_way_ids()
getWayIds(self: hoot.libpyhoot.OsmMap) -> QSet<long>


#### get_ways()
getWays(self: hoot.libpyhoot.OsmMap) -> __gnu_cxx::hash_map<long, std::shared_ptr<hoot::Way>, __gnu_cxx::hash<long>, std::equal_to<long>, std::allocator<std::shared_ptr<hoot::Way> > >


#### isEmpty(_ = Non_ )

#### is_empty()
isEmpty(self: hoot.libpyhoot.OsmMap) -> bool


#### numNodesAppended(_ = Non_ )

#### numNodesSkippedForAppending(_ = Non_ )

#### numRelationsAppended(_ = Non_ )

#### numRelationsSkippedForAppending(_ = Non_ )

#### numWaysAppended(_ = Non_ )

#### numWaysSkippedForAppending(_ = Non_ )

#### num_nodes_appended()
numNodesAppended(self: hoot.libpyhoot.OsmMap) -> int


#### num_nodes_skipped_for_appending()
numNodesSkippedForAppending(self: hoot.libpyhoot.OsmMap) -> int


#### num_relations_appended()
numRelationsAppended(self: hoot.libpyhoot.OsmMap) -> int


#### num_relations_skipped_for_appending()
numRelationsSkippedForAppending(self: hoot.libpyhoot.OsmMap) -> int


#### num_ways_appended()
numWaysAppended(self: hoot.libpyhoot.OsmMap) -> int


#### num_ways_skipped_for_appending()
numWaysSkippedForAppending(self: hoot.libpyhoot.OsmMap) -> int


#### registerListener(_ = Non_ )

#### register_listener()
registerListener(self: hoot.libpyhoot.OsmMap, arg0: hoot::OsmMapListener) -> None


#### replaceNode(_ = Non_ )

#### replaceSource(_ = Non_ )

#### replace_node()
replaceNode(self: hoot.libpyhoot.OsmMap, arg0: int, arg1: int) -> None

Intelligently replaces all instances of oldNode with newNode. This looks at all the ways
for references to oldNode and replaces those references with newNode. Finally, oldNode is
removed from this OsmMap entirely.


#### replace_source()
replaceSource(self: hoot.libpyhoot.OsmMap, arg0: QString) -> None


#### resetCounters(_ = Non_ )

#### resetIterator(_ = Non_ )

#### _static_ reset_counters()
resetCounters() -> None

Resets the way and node counters. This should ONLY BE CALLED BY UNIT TESTS.


#### reset_iterator()
resetIterator(self: hoot.libpyhoot.OsmMap) -> None


#### setCachedRubberSheet(_ = Non_ )

#### setEnableProgressLogging(_ = Non_ )

#### setIdGenerator(_ = Non_ )

#### setIdSwap(_ = Non_ )

#### setName(_ = Non_ )

#### setProjection(_ = Non_ )

#### setRoundabouts(_ = Non_ )

#### set_cached_rubber_sheet()
setCachedRubberSheet(self: hoot.libpyhoot.OsmMap, arg0: hoot::RubberSheet) -> None


#### set_enable_progress_logging()
setEnableProgressLogging(self: hoot.libpyhoot.OsmMap, arg0: bool) -> None


#### set_id_generator()
setIdGenerator(self: hoot.libpyhoot.OsmMap, arg0: hoot::IdGenerator) -> None


#### set_id_swap()
setIdSwap(self: hoot.libpyhoot.OsmMap, arg0: hoot::IdSwap) -> None


#### set_name()
setName(self: hoot.libpyhoot.OsmMap, arg0: QString) -> None


#### set_projection()
setProjection(self: hoot.libpyhoot.OsmMap, arg0: OGRSpatialReference) -> None


#### set_roundabouts()
setRoundabouts(self: hoot.libpyhoot.OsmMap, arg0: List[hoot::Roundabout]) -> None


#### size(self: hoot.libpyhoot.OsmMap)

#### to_json()
to_json converts the map to JSON and returns the result as a string.


#### validate(self: hoot.libpyhoot.OsmMap, arg0: bool)
Validates the consistency of the map. Primarily this checks to make sure that all nodes
referenced by a way exist in the map. A full dump of all invalid ways is logged before the
function throws an error.
:param strict: If true, the method throws an exception rather than returning a result if the

> validation fails.


* **Returns**

    True if the map is valid, false otherwise.



#### visitNodesRo(_ = Non_ )

#### visitNodesRw(_ = Non_ )

#### visitRelationsRo(_ = Non_ )

#### visitRelationsRw(_ = Non_ )

#### visitRo(_ = Non_ )

#### visitRw(_ = Non_ )

#### visitWaysRo(_ = Non_ )

#### visitWaysRw(_ = Non_ )

#### visit_nodes_ro()
visitNodesRo(self: hoot.libpyhoot.OsmMap, arg0: hoot::ConstElementVisitor) -> None


#### visit_nodes_rw()
visitNodesRw(self: hoot.libpyhoot.OsmMap, arg0: hoot::ElementVisitor) -> None


#### visit_relations_ro()
visitRelationsRo(self: hoot.libpyhoot.OsmMap, arg0: hoot::ConstElementVisitor) -> None


#### visit_relations_rw()
visitRelationsRw(self: hoot.libpyhoot.OsmMap, arg0: hoot::ElementVisitor) -> None


#### visit_ro()
visitRo(self: hoot.libpyhoot.OsmMap, arg0: hoot::ConstElementVisitor) -> None

Calls the visitRo method on all elements. See Element::visitRo for a more
thorough description.

> 
> * The order will always be nodes, ways, relations, but the IDs will not
> be in any specific order.


> * Unlike Element::visitRo, elements will not be visited multiple times.


> * Modifying the OsmMap while traversing will result in undefined behaviour.


> * This should be slightly faster than visitRw.

If the visitor implements OsmMapConsumer then setOsmMap will be called before visiting any
elements.


#### visit_rw()
visitRw(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. visitRw(self: hoot.libpyhoot.OsmMap, arg0: hoot::ElementVisitor) -> None

Calls the visitRw method on all elements. See Element::visitRw for a more
thorough description.

> 
> * The order will always be nodes, ways, relations, but the IDs will not
> be in any specific order.


> * Elements that are added during the traversal may or may not be visited.


> * Elements may be deleted during traversal.


> * The visitor is guaranteed to not visit deleted elements.

If the visitor implements OsmMapConsumer then setOsmMap will be called before
visiting any elements.


1. visitRw(self: hoot.libpyhoot.OsmMap, arg0: hoot::ConstElementVisitor) -> None


#### visit_ways_ro()
visitWaysRo(self: hoot.libpyhoot.OsmMap, arg0: hoot::ConstElementVisitor) -> None


#### visit_ways_rw()
visitWaysRw(self: hoot.libpyhoot.OsmMap, arg0: hoot::ElementVisitor) -> None


### _class_ hoot.libpyhoot.OsmMapReader()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### getIgnoreDuplicates(_ = Non_ )

#### get_ignore_duplicates()
getIgnoreDuplicates(self: hoot.libpyhoot.OsmMapReader) -> bool

Gets the ignore duplicates flag


#### isSupported(_ = Non_ )

#### is_supported()
isSupported(self: hoot.libpyhoot.OsmMapReader, arg0: QString) -> bool

Returns true if the output URL is likely supported. This won’t necessarily do an exhaustive
check. It will look to see if the URL is properly formatted (e.g. ends in .osm, or starts
with postgresql:, etc.)


#### open(self: hoot.libpyhoot.OsmMapReader, arg0: QString)
Opens the specified URL for reading.


#### read(self: hoot.libpyhoot.OsmMapReader, arg0: hoot.libpyhoot.OsmMap)
Reads the specified map. When this method is complete the input will likely be closed.


#### setConfiguration(_ = Non_ )

#### setDefaultStatus(_ = Non_ )

#### setIgnoreDuplicates(_ = Non_ )

#### setUseDataSourceIds(_ = Non_ )

#### setUseFileStatus(_ = Non_ )

#### setWarnOnVersionZeroElement(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.OsmMapReader, arg0: hoot::Settings) -> None

Configurable interface


#### set_default_status()
setDefaultStatus(self: hoot.libpyhoot.OsmMapReader, arg0: hoot.libpyhoot.Status) -> None

Determines the reader’s default element status


#### set_ignore_duplicates()
setIgnoreDuplicates(self: hoot.libpyhoot.OsmMapReader, arg0: bool) -> None

Set the ignore duplicates flag, when set to true, derived classes will ignore any element
who’s ID is already being used.  This is useful when elements cross bounding box boundaries
and multiple bounding boxes are being merged together.


#### set_use_data_source_ids()
setUseDataSourceIds(self: hoot.libpyhoot.OsmMapReader, arg0: bool) -> None

Determines whether the reader should use the element id’s from the data being read


#### set_use_file_status()
setUseFileStatus(self: hoot.libpyhoot.OsmMapReader, arg0: bool) -> None

Uses the element status from the file


#### set_warn_on_version_zero_element()
setWarnOnVersionZeroElement(self: hoot.libpyhoot.OsmMapReader, arg0: bool) -> None


#### supportedFormats(_ = Non_ )

#### supported_formats()
supportedFormats(self: hoot.libpyhoot.OsmMapReader) -> QString

Lists supported data format extensions

If multiple are supported, delimit them with a semicolon.


* **Returns**

    a formats string



### _class_ hoot.libpyhoot.OsmMapWriter()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### getIsDebugMap(_ = Non_ )

#### get_is_debug_map()
getIsDebugMap(self: hoot.libpyhoot.OsmMapWriter) -> bool

Gets flag indicating the writer is writing a debug map so that extra debugging metadata can
be included in each implementation of the output formats


#### isSupported(_ = Non_ )

#### is_supported()
isSupported(self: hoot.libpyhoot.OsmMapWriter, arg0: QString) -> bool

Returns true if the output URL is likely supported. This won’t necessarily do an exhaustive
check. It will look to see if the URL is properly formatted (e.g. ends in .osm, or starts
with postgresql:, etc.)


#### open(self: hoot.libpyhoot.OsmMapWriter, arg0: QString)
Opens the specified URL for writing.


#### setIsDebugMap(_ = Non_ )

#### set_is_debug_map()
setIsDebugMap(self: hoot.libpyhoot.OsmMapWriter, arg0: bool) -> None

Sets flag indicating the writer is writing a debug map so that extra debugging metadata is
included in the output


#### supportedFormats(_ = Non_ )

#### supported_formats()
supportedFormats(self: hoot.libpyhoot.OsmMapWriter) -> QString

Lists supported data format extensions

If multiple are supported, delimit them with a semicolon.


* **Returns**

    a formats string



#### write(self: hoot.libpyhoot.OsmMapWriter, arg0: hoot.libpyhoot.OsmMap)
Writes the specified map out. When this method is complete the output will likely be closed
and all data is guaranteed to be flushed.


### _class_ hoot.libpyhoot.OsmSchema()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.OsmSchema)

#### addAssociatedWith(_ = Non_ )

#### addIsA(_ = Non_ )

#### addSimilarTo(_ = Non_ )

#### add_associated_with()
addAssociatedWith(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> None


#### add_is_a()
addIsA(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> None


#### add_similar_to()
addSimilarTo(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString, arg2: float, arg3: bool) -> None


#### createTestingGraph(_ = Non_ )

#### create_testing_graph()
createTestingGraph(self: hoot.libpyhoot.OsmSchema) -> None

ONLY FOR UNIT TESTING. Be a good neighbor and call loadDefault() when you’re done.”


#### explicitTypeMismatch(_ = Non_ )

#### explicit_type_mismatch()
explicitTypeMismatch(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags, arg2: float) -> bool

Determines if two sets of tags have an explicit type mismatch. Empty tags and generic types
are ignored during the comparison


* **Parameters**

    
    * **tags1** – the first set of tags to compare


    * **tags2** – the second set of tags to compare


    * **minTypeScore** – the minimum similarity score at or above which the two sets of tags must


score in to be considered a match
:returns: true if the tags explicitly mismatch; false otherwise”


#### getAliasTags(_ = Non_ )

#### getAllTagKeys(_ = Non_ )

#### getAllTags(_ = Non_ )

#### getAssociatedTags(_ = Non_ )

#### getChildTags(_ = Non_ )

#### getFirstCommonAncestor(_ = Non_ )

#### getFirstType(_ = Non_ )

#### getInstance(_ = Non_ )

#### getIsACost(_ = Non_ )

#### getParentKvp(_ = Non_ )

#### getSchemaVertices(_ = Non_ )

#### getSimilarTags(_ = Non_ )

#### getSimilarTagsAsVertices(_ = Non_ )

#### getTagVertex(_ = Non_ )

#### get_alias_tags()
getAliasTags(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags) -> hoot.libpyhoot.Tags

Retrieves tags that are aliases of the input tags


* **Parameters**

    **tags** – tags to search aliases for



* **Returns**

    a set of tags”



#### get_all_tag_keys()
getAllTagKeys(self: hoot.libpyhoot.OsmSchema) -> QSet<QString>

Retrieves all possible tag keys from the schema


* **Returns**

    a collection of key strings



#### get_all_tags()
getAllTags(self: hoot.libpyhoot.OsmSchema) -> List[hoot::SchemaVertex]


#### get_associated_tags()
getAssociatedTags(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags) -> hoot.libpyhoot.Tags

Retrieves a set of tags that are associated with the input tags, as defined by the hoot schema


* **Parameters**

    **tags** – tags to search associations for



* **Returns**

    a set of tags”



#### get_child_tags()
getChildTags(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags) -> hoot.libpyhoot.Tags

Retrieves all child tags for the given input tags


* **Parameters**

    **tags** – tags for which to retrieve child tags



* **Returns**

    a set of tags”



#### get_first_common_ancestor()
getFirstCommonAncestor(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> hoot::SchemaVertex

Searches for the first common ancestor between two key value pairs. If there is no common
ancestor then an empty TagVertex is returned.”


#### get_first_type()
getFirstType(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags, arg1: bool) -> QString

Returns the first type key/value pair found in a set of tags


* **Parameters**

    
    * **tags** – the tags to search


    * **allowGeneric** – if true, kvps associated with generic types are returned



* **Returns**

    a single key/value pair string”



#### _static_ get_instance()
getInstance() -> hoot.libpyhoot.OsmSchema

get_instance() is provided for consistency w/ hoot but just calling OsmSchema() gives the same
result and is more concise.


#### get_is_acost()
getIsACost(self: hoot.libpyhoot.OsmSchema) -> float


#### get_parent_kvp()
getParentKvp(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> QString

Determine the ancestor between two tags


* **Parameters**

    
    * **kvp1** – first tag to examine


    * **kvp2** – second tag to examine



* **Returns**

    tag that is the ancestor of the other or the first tag if neither is an ancestor of


each other”


#### get_schema_vertices()
getSchemaVertices(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags) -> List[hoot::SchemaVertex]

Returns all schema vertices that are represented in the set of tags. This will return both
compound vertices and tag vertices.


#### get_similar_tags()
getSimilarTags(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: float) -> hoot.libpyhoot.Tags

Retrieves tags similar to the input tag


* **Parameters**

    
    * **name** – a kvp


    * **minimumScore** – tag similarity threshold



* **Returns**

    a set of tags”



#### get_similar_tags_as_vertices()
getSimilarTagsAsVertices(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: float) -> List[hoot::SchemaVertex]

Returns all tags that have a similar score >= minimumScore.

minimumScore must be > 0.


#### get_tag_vertex()
getTagVertex(self: hoot.libpyhoot.OsmSchema, arg0: QString) -> hoot::SchemaVertex

Returns the tag vertex for a given kvp. If the vertex is compound then an empty vertex will
be returned.


#### hasAnyCategory(_ = Non_ )

#### hasMoreThanOneType(_ = Non_ )

#### hasTagKey(_ = Non_ )

#### hasType(_ = Non_ )

#### has_any_category()
hasAnyCategory(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> bool

Determines if the key is part of any category in the schema


* **Parameters**

    
    * **key** – tag key


    * **val** – tag value



* **Returns**

    true if the tag is part of at least one schema category; false otherwise



#### has_more_than_one_type()
hasMoreThanOneType(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags) -> bool

Determines if a set of tags have more than one feature type


* **Parameters**

    **tags** – the tags to examine



* **Returns**

    true if the tags have at least two type tags”



#### has_tag_key()
hasTagKey(self: hoot.libpyhoot.OsmSchema, arg0: QString) -> bool


#### has_type()
hasType(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags) -> bool

Determines if a set of tags has a feature type


* **Parameters**

    **tags** – the tags to examine



* **Returns**

    true if the tags have at least one type tag”



#### isAncestor(_ = Non_ )

#### isGeneric(_ = Non_ )

#### isGenericKvp(_ = Non_ )

#### isList(_ = Non_ )

#### isMetaData(_ = Non_ )

#### isNumericTag(_ = Non_ )

#### isTextTag(_ = Non_ )

#### isTypeKey(_ = Non_ )

#### is_ancestor()
isAncestor(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> bool


#### is_generic()
isGeneric(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags) -> bool

Determines whether a set of tags represents a generic feature type


* **Parameters**

    **tags** – the tags to examine



* **Returns**

    true if the tags contain only a generic feature type; false otherwise”



#### is_generic_kvp()
isGenericKvp(self: hoot.libpyhoot.OsmSchema, arg0: QString) -> bool

Determines if a key/value pair represents a generic feature type


* **Parameters**

    **kvp** – the key/value pair to examine



* **Returns**

    true if the input key/value pair represents a generic type; false otherwise”



#### is_list()
isList(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> bool

Returns true if this is a list of values. Right now this just looks for a semicolon in value,
but in the future the list of valid list keys may be stored in the schema file.”


#### is_meta_data()
isMetaData(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> bool

Returns true if the kvp contains metadata about the feature as opposed to real information
about the features.

Tags such as "hoot:status", "source”, "uuid"”


#### is_numeric_tag()
isNumericTag(self: hoot.libpyhoot.OsmSchema, arg0: QString) -> bool

Return true if this tag can contain numeric text.”


#### is_text_tag()
isTextTag(self: hoot.libpyhoot.OsmSchema, arg0: QString) -> bool

Return true if this tag can contain free-form text.”


#### is_type_key()
isTypeKey(self: hoot.libpyhoot.OsmSchema, arg0: QString) -> bool

Determines if a tag key corresponds to a type in the schema


* **Parameters**

    **key** – tag key to examine



* **Returns**

    true if the key corresponds to a type; false otherwise”



#### loadDefault(_ = Non_ )

#### load_default()
loadDefault(self: hoot.libpyhoot.OsmSchema) -> None

Loads the default configuration. This should only be used by unit tests.”


#### mostSpecificType(_ = Non_ )

#### most_specific_type()
mostSpecificType(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags) -> QString

Returns the most specific type in a set of tags according to the schema


* **Parameters**

    **tags** – the tags to search



* **Returns**

    a single key/value pair string”



#### score(\*args, \*\*kwargs)
Overloaded function.


1. score(self: hoot.libpyhoot.OsmSchema, arg0: hoot::SchemaVertex, arg1: hoot::SchemaVertex) -> float


2. score(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: hoot.libpyhoot.Tags) -> float

Scores a particular kvp against an element’s tags


* **Parameters**

    
    * **kvp** – the key/value pair to compare against


    * **tags** – the tags to compare against



* **Returns**

    the highest similarity score found in tags when compared to kvp”



#### scoreOneWay(_ = Non_ )

#### scoreTypes(_ = Non_ )

#### score_one_way()
scoreOneWay(self: hoot.libpyhoot.OsmSchema, arg0: QString, arg1: QString) -> float

@brief scoreOneWay Returns a oneway score. E.g. highway=primary is similar to highway=road,

    but a highway=road isn’t necessarily similar to a highway=primary (so it gets a low score).”


#### score_types()
scoreTypes(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags, arg2: bool) -> float

Scores the type similarity between two sets of tags


* **Parameters**

    
    * **tags1** – the first set of tags to score


    * **tags2** – the second set of tags to score


    * **ignoreGenericTypes** – if true, generic types such as ‘poi=yes’ are ignored during


comparison
:returns: a similarity score from 0.0 to 1.0”


#### setIsACost(_ = Non_ )

#### set_is_acost()
setIsACost(self: hoot.libpyhoot.OsmSchema, arg0: float) -> None

Sets the cost when traversing up the tree to a parent node. This is useful for strict score
checking rather than equivalent tags.”


#### tags(self: hoot.libpyhoot.OsmSchema)
Returns a collection of tag key/value pairs that represent generic feature types


* **Returns**

    a collection of tag key/value pairs



#### toGraphvizString(_ = Non_ )

#### toKvp(_ = Non_ )

#### to_graphviz_string()
toGraphvizString(self: hoot.libpyhoot.OsmSchema) -> QString


#### _static_ to_kvp()
toKvp(arg0: QString, arg1: QString) -> QString


#### typeMismatch(_ = Non_ )

#### type_mismatch()
typeMismatch(self: hoot.libpyhoot.OsmSchema, arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags, arg2: float) -> bool

Determines if two sets of tags have an explicit type mismatch. Empty tags and generic types
are not ignored during the comparison


* **Parameters**

    
    * **tags1** – the first set of tags to compare


    * **tags2** – the second set of tags to compare


    * **minTypeScore** – the minimum similarity score at or above which the two sets of tags must


score in to be considered a match
:returns: true if the tags mismatch; false otherwise”


#### update(self: hoot.libpyhoot.OsmSchema)

#### updateOrCreateVertex(_ = Non_ )

#### update_or_create_vertex()
updateOrCreateVertex(self: hoot.libpyhoot.OsmSchema, arg0: hoot::SchemaVertex) -> None


### _class_ hoot.libpyhoot.OsmXmlWriter()
Bases: `hoot.libpyhoot.OsmMapWriter`


#### \__init__(self: hoot.libpyhoot.OsmXmlWriter)

#### close(self: hoot.libpyhoot.OsmXmlWriter)

#### getIsDebugMap(_ = Non_ )

#### get_is_debug_map()
getIsDebugMap(self: hoot.libpyhoot.OsmMapWriter) -> bool

Gets flag indicating the writer is writing a debug map so that extra debugging metadata can
be included in each implementation of the output formats


#### isSupported(_ = Non_ )

#### is_supported()
isSupported(self: hoot.libpyhoot.OsmXmlWriter, arg0: QString) -> bool


#### open(self: hoot.libpyhoot.OsmXmlWriter, arg0: QString)

#### setIncludeCompatibilityTags(_ = Non_ )

#### setIsDebugMap(_ = Non_ )

#### setPrecision(_ = Non_ )

#### set_include_compatibility_tags()
setIncludeCompatibilityTags(self: hoot.libpyhoot.OsmXmlWriter, arg0: bool) -> None


#### set_is_debug_map()
setIsDebugMap(self: hoot.libpyhoot.OsmMapWriter, arg0: bool) -> None

Sets flag indicating the writer is writing a debug map so that extra debugging metadata is
included in the output


#### set_precision()
setPrecision(self: hoot.libpyhoot.OsmXmlWriter, arg0: int) -> None


#### supportedFormats(_ = Non_ )

#### supported_formats()
supportedFormats(self: hoot.libpyhoot.OsmXmlWriter) -> QString


#### toString(_ = Non_ )

#### _static_ to_string()
toString(map: hoot.libpyhoot.OsmMap, format_xml: bool = True) -> QString

Write the map out to a string and return it. This is handy for debugging, but has obvious
memory limitations with real data.


* **Parameters**

    
    * **map** – the map to write out as a string


    * **formatXml** – if true, formats the xml with indentations and new lines



* **Returns**

    an OSM XML string



#### write(self: hoot.libpyhoot.OsmXmlWriter, arg0: hoot.libpyhoot.OsmMap)

### _class_ hoot.libpyhoot.PointCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.PointCriterion) -> None


2. __init__(self: hoot.libpyhoot.PointCriterion, arg0: hoot::OsmMap) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setOsmMap(_ = Non_ )

#### set_osm_map()
setOsmMap(self: hoot.libpyhoot.PointCriterion, arg0: hoot::OsmMap) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.PolygonCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.PolygonCriterion) -> None


2. __init__(self: hoot.libpyhoot.PolygonCriterion, arg0: hoot::OsmMap) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setOsmMap(_ = Non_ )

#### set_osm_map()
setOsmMap(self: hoot.libpyhoot.PolygonCriterion, arg0: hoot::OsmMap) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.PythonCreatorDescription()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.PythonCreatorDescription)

#### _property_ criterion()
Criterion is a criteria to apply to determine if this is a match candidate. E.g. PoiCriterion


#### _property_ description()
description is used to set matcher/merger routine metadata.


#### _property_ extract_features()
The features function returns a map of column names to values. These features can be used to train
or evaluate a machine learning model.


* **Parameters**

    **map** – OsmMap that contains the match



* **Returns**

    a dict of strings to floats



#### _property_ is_match_candidate()
is_match_candidate is called to evaluate two elements for match candidacy.


* **Returns**

    True if the two elements might match. A more restrictive function will run faster later
    in the process, sometimes dramatically faster.



#### _property_ is_whole_group()
is_whole_group is a function that is called to determine if the
matches generated by this matcher should be treated as a group, or as
a graph that should be deconflicted.

An example of whole group would be 2 buildings, and 2 points that all represent
a single POI that you want to conflate into a single polygon.


* **Returns**

    True if the matches should be treated as a whole group.



#### _property_ match_score()
match_score determines scores a pair of elements with a match/miss/review.
score. The sum of all the scores _should_ add to one.

Example return value:

> return (hoot.MatchClassification(1, 0, 0), “obvious to robots”)


* **Returns**

    A tuple with (MatchClassification, string) where the MatchClassification object has the


match, miss & review scores populated and the score contains a human readable explanation of why
the match classification was chosen.


#### _property_ match_threshold()
match_threshold determines what value is a match/miss/review.


#### _property_ merge_pair()
merge_pair merges a pair of matched elements into one element.


* **Returns**

    The merged element.



#### _property_ merge_set()
merge_set merges a set of matched elements into one element. Any elements that are replaced
must be returned as an array of element ID tuples.


* **Parameters**

    
    * **map** – The OsmMap that contains the elements to merge.


    * **pairs** – A set of pairs of element IDs. These are the interrelated matched pairs.



* **Returns**

    The replaced pairs. E.g. [(ElementId(‘way:1’), ElementId(‘way:100’))]



#### _property_ search_radius()
search_radius is the fixed search radius for all elements, use this or 
search_radius_function but not both.


#### _property_ search_radius_function()
search_radius_function is a function that returns a customized search radius per element
in lieu of a fixed search_radius. This is useful when different elements have different radii,
for example: towns and cities.


### _class_ hoot.libpyhoot.PythonMatchCreator()
Bases: `hoot.libpyhoot.MatchCreator`


#### \__init__(self: hoot.libpyhoot.PythonMatchCreator)

#### _static_ clear()

#### getCreatorByName(_ = Non_ )

#### getName(_ = Non_ )

#### get_creator_by_name()
getCreatorByName(self: QString) -> hoot.libpyhoot.PythonCreatorDescription

getCreatorByName returns the creator python info for a specified name.


#### get_name()
getName(self: hoot.libpyhoot.PythonMatchCreator) -> QString


#### init(self: hoot.libpyhoot.PythonMatchCreator, arg0: hoot::OsmMap)

#### registerCreator(_ = Non_ )

#### _static_ register_creator()
registerCreator(arg0: hoot.libpyhoot.PythonCreatorDescription) -> None


#### setArguments(_ = Non_ )

#### setName(_ = Non_ )

#### set_arguments()
setArguments(self: hoot.libpyhoot.PythonMatchCreator, arg0: List[QString]) -> None


#### set_name()
setName(self: hoot.libpyhoot.PythonMatchCreator, arg0: QString) -> None


### _class_ hoot.libpyhoot.PythonMergerCreator()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.PythonMergerCreator)

#### _static_ clear()

#### registerCreator(_ = Non_ )

#### _static_ register_creator()
registerCreator(arg0: hoot.libpyhoot.PythonCreatorDescription) -> None


#### setArguments(_ = Non_ )

#### set_arguments()
setArguments(self: hoot.libpyhoot.PythonMergerCreator, arg0: List[QString]) -> None


### _class_ hoot.libpyhoot.RandomForest()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.RandomForest)

#### classifyVector(_ = Non_ )

#### classify_vector()
classifyVector(self: hoot.libpyhoot.RandomForest, arg0: List[float], arg1: dict) -> None

Classifies a data vector against a generated random forest.

The vector is classified against each tree in the forest and the final classification is the
result of majority vote for each tree.


* **Parameters**

    
    * **dataVector** – a single data vector of size N where N is the number of factors


    * **scores** – a map to hold the classification results as class name mapped to probability



#### clear(self: hoot.libpyhoot.RandomForest)
Clears the random forest of its trees.


#### findAverageError(_ = Non_ )

#### findProximity(_ = Non_ )

#### find_average_error()
findAverageError(self: hoot.libpyhoot.RandomForest, arg0: hoot.libpyhoot.DataFrame, arg1: float, arg2: float) -> None

Finds the average classification error statistic for the forest based on the
oob sets for the trees


* **Parameters**

    
    * **data** – the data set to operate upon


    * **average** – variable to hold the computed average error


    * **stdDev** – variable to hold the computed standard deviation



#### find_proximity()
findProximity(self: hoot.libpyhoot.RandomForest, arg0: hoot.libpyhoot.DataFrame, arg1: List[int]) -> None

Computes the proximity of the data vectors in the data set by running the
complete data set through the tree and then tracking which vectors
were classified to the same node


* **Parameters**

    
    * **data** – the set of data vectors


    * **proximity** – a n x n (where n is the number of total data vectors) adjacency matrix



#### importModel(_ = Non_ )

#### import_model()
importModel(self: hoot.libpyhoot.RandomForest, arg0: QString) -> None

importModel import the random forest object
:param e: the XML DOM element for the forest


#### isTrained(_ = Non_ )

#### is_trained()
isTrained(self: hoot.libpyhoot.RandomForest) -> bool


* **Returns**

    true if the forest has been trained



#### trainBinary(_ = Non_ )

#### trainMulticlass(_ = Non_ )

#### trainRoundRobin(_ = Non_ )

#### train_binary()
trainBinary(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. trainBinary(self: hoot.libpyhoot.RandomForest, arg0: hoot.libpyhoot.DataFrame, arg1: int, arg2: int, arg3: str, arg4: int, arg5: float, arg6: bool) -> None

Build the forest from a data set


* **Parameters**

    
    * **data** – the data set to train on


    * **numTrees** – the number of random trees to create


    * **numFactors** – the number of factors to randomly choose as candidates for node splitting


    * **posClass** – the name of the positive class


    * **nodeSize** – the minimum number of data vectors in a set to split a node


    * **retrain** – fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)


    * **balanced** – true if the forest will be balanced



1. trainBinary(self: hoot.libpyhoot.RandomForest, arg0: hoot.libpyhoot.DataFrame, arg1: int, arg2: int, arg3: str, arg4: int, arg5: float, arg6: bool) -> None

Build the forest from a data set


* **Parameters**

    
    * **data** – the data set to train on


    * **numTrees** – the number of random trees to create


    * **numFactors** – the number of factors to randomly choose as candidates for node splitting


    * **posClass** – the name of the positive class


    * **nodeSize** – the minimum number of data vectors in a set to split a node


    * **retrain** – fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)


    * **balanced** – true if the forest will be balanced



#### train_multiclass()
trainMulticlass(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. trainMulticlass(self: hoot.libpyhoot.RandomForest, arg0: hoot.libpyhoot.DataFrame, arg1: int, arg2: int, arg3: int, arg4: float, arg5: bool) -> None

Build the forest from a data set


* **Parameters**

    
    * **data** – the data set to train on


    * **numTrees** – the number of random trees to create


    * **numFactors** – the number of factors to randomly choose as candidates for node splitting


    * **nodeSize** – the minimum number of data vectors in a set to split a node


    * **retrain** – fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)


    * **balanced** – true if the forest will be balanced



1. trainMulticlass(self: hoot.libpyhoot.RandomForest, arg0: hoot.libpyhoot.DataFrame, arg1: int, arg2: int, arg3: int, arg4: float, arg5: bool) -> None

Build the forest from a data set


* **Parameters**

    
    * **data** – the data set to train on


    * **numTrees** – the number of random trees to create


    * **numFactors** – the number of factors to randomly choose as candidates for node splitting


    * **nodeSize** – the minimum number of data vectors in a set to split a node


    * **retrain** – fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)


    * **balanced** – true if the forest will be balanced



#### train_round_robin()
trainRoundRobin(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. trainRoundRobin(self: hoot.libpyhoot.RandomForest, arg0: hoot.libpyhoot.DataFrame, arg1: int, arg2: int, arg3: str, arg4: str, arg5: int, arg6: float, arg7: bool) -> None

Build the forest from a data set


* **Parameters**

    
    * **data** – the data set to train on


    * **numTrees** – the number of random trees to create


    * **numFactors** – the number of factors to randomly choose as candidates for node splitting


    * **posClass** – the name of the positive class


    * **negClass** – the name of the negative class


    * **nodeSize** – the minimum number of data vectors in a set to split a node


    * **retrain** – fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)


    * **balanced** – true if the forest will be balanced



1. trainRoundRobin(self: hoot.libpyhoot.RandomForest, arg0: hoot.libpyhoot.DataFrame, arg1: int, arg2: int, arg3: str, arg4: str, arg5: int, arg6: float, arg7: bool) -> None

Build the forest from a data set


* **Parameters**

    
    * **data** – the data set to train on


    * **numTrees** – the number of random trees to create


    * **numFactors** – the number of factors to randomly choose as candidates for node splitting


    * **posClass** – the name of the positive class


    * **negClass** – the name of the negative class


    * **nodeSize** – the minimum number of data vectors in a set to split a node


    * **retrain** – fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)


    * **balanced** – true if the forest will be balanced



### _class_ hoot.libpyhoot.RecursiveElementRemover()
Bases: `hoot.libpyhoot.ConstOsmMapOperation`


#### \__init__(self: hoot.libpyhoot.RecursiveElementRemover, arg0: hoot.libpyhoot.ElementId)

#### apply(self: hoot.libpyhoot.ConstOsmMapOperation, arg0: hoot.libpyhoot.OsmMap)

### _class_ hoot.libpyhoot.RemoveElementsVisitor()
Bases: `hoot.libpyhoot.ElementVisitor`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.RemoveElementsVisitor) -> None


2. __init__(self: hoot.libpyhoot.RemoveElementsVisitor, arg0: hoot.libpyhoot.Settings) -> None


3. __init__(self: hoot.libpyhoot.RemoveElementsVisitor, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.RemoveElementsVisitor, arg0: hoot.libpyhoot.ElementCriterion, 

```
*
```

args) -> None


#### addCriterion(_ = Non_ )

#### add_criterion(_ = Non_ )

#### setConfiguration(_ = Non_ )

#### setRecursive(_ = Non_ )

#### set_configuration(_ = Non_ )

#### set_recursive()
setRecursive(self: hoot.libpyhoot.RemoveElementsVisitor, arg0: bool) -> None


### _class_ hoot.libpyhoot.RemoveMissingElementsVisitor()
Bases: `hoot.libpyhoot.ElementVisitor`


#### \__init__(self: hoot.libpyhoot.RemoveMissingElementsVisitor)

### _class_ hoot.libpyhoot.ReplaceElementOp()
Bases: `hoot.libpyhoot.ConstOsmMapOperation`


#### \__init__(self: hoot.libpyhoot.ReplaceElementOp, arg0: hoot.libpyhoot.ElementId, arg1: hoot.libpyhoot.ElementId)

#### apply(self: hoot.libpyhoot.ConstOsmMapOperation, arg0: hoot.libpyhoot.OsmMap)

### _class_ hoot.libpyhoot.ReviewMarker()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.ReviewMarker)

#### getBadGeometryType(_ = Non_ )

#### getReviewElements(_ = Non_ )

#### getReviewType(_ = Non_ )

#### _static_ get_bad_geometry_type()
getBadGeometryType() -> QString


#### _static_ get_review_elements()
getReviewElements(arg0: hoot::OsmMap, arg1: hoot::ElementId) -> Set[hoot::ElementId]


#### _static_ get_review_type()
getReviewType(arg0: hoot::OsmMap, arg1: hoot::ElementId) -> QString


#### isReview(_ = Non_ )

#### isReviewUid(_ = Non_ )

#### _static_ is_review()
isReview(arg0: hoot::Element) -> bool

Returns true if this element is a review record (not an element that needs to be reviewed, but
the relation that describes the review).

isReviewUid is preferred over this method. If we change the review mechanism in the future
this method may be broken. (unlikely)


#### _static_ is_review_uid()
isReviewUid(arg0: hoot::OsmMap, arg1: hoot::ElementId) -> bool

Returns true if the specified UID is a review tag.


#### mark(\*args, \*\*kwargs)
Overloaded function.


1. mark(self: hoot.libpyhoot.ReviewMarker, map: hoot::OsmMap, e1: hoot::Element, e2: hoot::Element, note: QString, reviewType: QString, score: float = -1, choices: List[QString] = []) -> None

Marks e1 and e2 as needing review and sets them to reference each other. If the score is
negative then the score is omitted.


* **Parameters**

    
    * **note** – A human readable note describing the review.


    * **reviewType** – A human readable review type. Typically this is a one word description of
    the feature being reviewed. E.g. “Highway” or “Building”.



1. mark(self: hoot.libpyhoot.ReviewMarker, map: hoot::OsmMap, ids: List[hoot::ElementId], note: QString, reviewType: QString, score: float = -1, choices: List[QString] = []) -> None

Marks a vector of elements as needing review and sets them to reference each other. If the score
is negative then the score is omitted.


* **Parameters**

    
    * **note** – A human readable note describing the review.


    * **reviewType** – A human readable review type. Typically this is a one word description of
    the feature being reviewed. E.g. “Highway” or “Building”.



#### removeElement(_ = Non_ )

#### _static_ remove_element()
removeElement(arg0: hoot::OsmMap, arg1: hoot::ElementId) -> None

Removes a single element.


### _class_ hoot.libpyhoot.SchemaVertex()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.SchemaVertex)

#### addCategory(_ = Non_ )

#### addCompoundRule(_ = Non_ )

#### add_category()
addCategory(self: hoot.libpyhoot.SchemaVertex, arg0: QString) -> None


#### add_compound_rule()
addCompoundRule(self: hoot.libpyhoot.SchemaVertex, arg0: QList<std::shared_ptr<hoot::KeyValuePair> >) -> None

Add a compound rule. This must be a “Compound” type to be valid.


#### getAliases(_ = Non_ )

#### getCategories(_ = Non_ )

#### getChildWeight(_ = Non_ )

#### getCompoundRules(_ = Non_ )

#### getDescription(_ = Non_ )

#### getGeometries(_ = Non_ )

#### getInfluence(_ = Non_ )

#### getKey(_ = Non_ )

#### getMismatchScore(_ = Non_ )

#### getName(_ = Non_ )

#### getType(_ = Non_ )

#### getValue(_ = Non_ )

#### getValueType(_ = Non_ )

#### get_aliases()
getAliases(self: hoot.libpyhoot.SchemaVertex) -> QStringList


#### get_categories()
getCategories(self: hoot.libpyhoot.SchemaVertex) -> QStringList


#### get_child_weight()
getChildWeight(self: hoot.libpyhoot.SchemaVertex) -> float


#### get_compound_rules()
getCompoundRules(self: hoot.libpyhoot.SchemaVertex) -> QList<QList<std::shared_ptr<hoot::KeyValuePair> > >

Yes, technically you could modify the contents of the rules returned. Please don’t. Taking
this short cut we don’t need to copy the rules into a proper const object each time.


#### get_description()
getDescription(self: hoot.libpyhoot.SchemaVertex) -> QString


#### get_geometries()
getGeometries(self: hoot.libpyhoot.SchemaVertex) -> int


#### get_influence()
getInfluence(self: hoot.libpyhoot.SchemaVertex) -> float


#### get_key()
getKey(self: hoot.libpyhoot.SchemaVertex) -> QString


#### get_mismatch_score()
getMismatchScore(self: hoot.libpyhoot.SchemaVertex) -> float


#### get_name()
getName(self: hoot.libpyhoot.SchemaVertex) -> QString


#### get_type()
getType(self: hoot.libpyhoot.SchemaVertex) -> hoot::SchemaVertex::VertexType


#### get_value()
getValue(self: hoot.libpyhoot.SchemaVertex) -> QString


#### get_value_type()
getValueType(self: hoot.libpyhoot.SchemaVertex) -> hoot::TagValueType


#### isCompoundMatch(_ = Non_ )

#### isEmpty(_ = Non_ )

#### isMatch(_ = Non_ )

#### isValid(_ = Non_ )

#### is_compound_match()
isCompoundMatch(self: hoot.libpyhoot.SchemaVertex, arg0: hoot.libpyhoot.Tags) -> bool

Returns true if one or more of the compound rules match this tag.


#### is_empty()
isEmpty(self: hoot.libpyhoot.SchemaVertex) -> bool


#### _static_ is_match()
isMatch(arg0: QList<std::shared_ptr<hoot::KeyValuePair> >, arg1: hoot.libpyhoot.Tags) -> bool

Returns true if each of the elements in this rule matches one of the kvps in t.


#### is_valid()
isValid(self: hoot.libpyhoot.SchemaVertex) -> bool


#### setAliases(_ = Non_ )

#### setCategories(_ = Non_ )

#### setChildWeight(_ = Non_ )

#### setDescription(_ = Non_ )

#### setGeometries(_ = Non_ )

#### setInfluence(_ = Non_ )

#### setKey(_ = Non_ )

#### setMismatchScore(_ = Non_ )

#### setName(_ = Non_ )

#### setNameKvp(_ = Non_ )

#### setType(_ = Non_ )

#### setValue(_ = Non_ )

#### setValueType(_ = Non_ )

#### setValueTypeString(_ = Non_ )

#### set_aliases()
setAliases(self: hoot.libpyhoot.SchemaVertex, arg0: QStringList) -> None


#### set_categories()
setCategories(self: hoot.libpyhoot.SchemaVertex, arg0: QStringList) -> None


#### set_child_weight()
setChildWeight(self: hoot.libpyhoot.SchemaVertex, arg0: float) -> None


#### set_description()
setDescription(self: hoot.libpyhoot.SchemaVertex, arg0: QString) -> None


#### set_geometries()
setGeometries(self: hoot.libpyhoot.SchemaVertex, arg0: int) -> None


#### set_influence()
setInfluence(self: hoot.libpyhoot.SchemaVertex, arg0: float) -> None


#### set_key()
setKey(self: hoot.libpyhoot.SchemaVertex, arg0: QString) -> None


#### set_mismatch_score()
setMismatchScore(self: hoot.libpyhoot.SchemaVertex, arg0: float) -> None


#### set_name()
setName(self: hoot.libpyhoot.SchemaVertex, arg0: QString) -> None

Sets the name and does not parse out the key/value. The key and value will not be changed.


#### set_name_kvp()
setNameKvp(self: hoot.libpyhoot.SchemaVertex, arg0: QString) -> None

Sets the name and parses out and stores the key/value.


#### set_type()
setType(self: hoot.libpyhoot.SchemaVertex, arg0: hoot::SchemaVertex::VertexType) -> None


#### set_value()
setValue(self: hoot.libpyhoot.SchemaVertex, arg0: QString) -> None


#### set_value_type()
setValueType(self: hoot.libpyhoot.SchemaVertex, arg0: hoot::TagValueType) -> None


#### set_value_type_string()
setValueTypeString(self: hoot.libpyhoot.SchemaVertex, arg0: QString) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.SchemaVertex) -> QString


### _class_ hoot.libpyhoot.Settings()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### get(self: hoot.libpyhoot.Settings, arg0: QString)

#### getDouble(_ = Non_ )

#### getInstance(_ = Non_ )

#### get_double()
getDouble(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. getDouble(self: hoot.libpyhoot.Settings, arg0: QString) -> float


2. getDouble(self: hoot.libpyhoot.Settings, arg0: QString, arg1: float) -> float


#### _static_ get_instance()
getInstance() -> hoot.libpyhoot.Settings


#### set(\*args, \*\*kwargs)
Overloaded function.


1. set(self: hoot.libpyhoot.Settings, arg0: QString, arg1: QString) -> None


2. set(self: hoot.libpyhoot.Settings, arg0: QString, arg1: float) -> None


3. set(self: hoot.libpyhoot.Settings, arg0: QString, arg1: int) -> None


4. set(self: hoot.libpyhoot.Settings, arg0: QString, arg1: bool) -> None


### _class_ hoot.libpyhoot.Soundex()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(self: hoot.libpyhoot.Soundex)

#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


### _class_ hoot.libpyhoot.Status()
Bases: `pybind11_builtins.pybind11_object`


#### CONFLATED(_ = <TypeEnum.CONFLATED: 3_ )

#### ENUMEND(_ = <TypeEnum.ENUMEND: 5_ )

#### INVALID(_ = <TypeEnum.INVALID: 0_ )

#### TAGCHANGE(_ = <TypeEnum.TAGCHANGE: 4_ )

#### _class_ TypeEnum()
Bases: `pybind11_builtins.pybind11_object`

Members:

INVALID

UNKNOWN1

UNKNOWN2

CONFLATED

TAGCHANGE

ENUMEND


#### CONFLATED(_ = <TypeEnum.CONFLATED: 3_ )

#### ENUMEND(_ = <TypeEnum.ENUMEND: 5_ )

#### INVALID(_ = <TypeEnum.INVALID: 0_ )

#### TAGCHANGE(_ = <TypeEnum.TAGCHANGE: 4_ )

#### UNKNOWN1(_ = <TypeEnum.UNKNOWN1: 1_ )

#### UNKNOWN2(_ = <TypeEnum.UNKNOWN2: 2_ )

#### \__init__(self: hoot.libpyhoot.Status.TypeEnum, value: int)

#### _property_ name()

#### _property_ value()

#### UNKNOWN1(_ = <TypeEnum.UNKNOWN1: 1_ )

#### UNKNOWN2(_ = <TypeEnum.UNKNOWN2: 2_ )

#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.Status) -> None


2. __init__(self: hoot.libpyhoot.Status, arg0: hoot::Status::TypeEnum) -> None


#### _static_ fromString(arg0: QString)
fromString Parses type from either a human readable status string or the numeric status
string.
:param statusString: The status string to parse.
:returns: The status parsed or throws an exception if it is an invalid status string.


#### getEnum(self: hoot.libpyhoot.Status)

#### getInput(self: hoot.libpyhoot.Status)

#### isInput(\*args, \*\*kwargs)
Overloaded function.


1. isInput(self: hoot.libpyhoot.Status) -> bool

getInput Unlike the enumeration names and strings, this returns the zero-based number
for the input.
:returns: The zero-based input for this status or throws an exception if this isn’t an input.
E.g. Unknown1 returns 0, Unknown2 return 1, etc.


1. isInput(self: hoot.libpyhoot.Status) -> bool


* **Returns**

    Returns true if the status is one of any input value (multiary)



#### isUnknown(self: hoot.libpyhoot.Status)
isUnknown Provided for backwards compatibility.
:returns: Returns true if the status is one of the first two inputs.


#### toString(self: hoot.libpyhoot.Status)

#### toTextStatus(self: hoot.libpyhoot.Status)
This is not pretty and it is a copy of “toString”.
It is a lot easier to change this when the users want different text output
instead of changing “toString” and all of code, unit tests etc that rely on it.


### _class_ hoot.libpyhoot.StatusEqualsExtractor()
Bases: `hoot.libpyhoot.FeatureExtractor`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.StatusEqualsExtractor) -> None


2. __init__(self: hoot.libpyhoot.StatusEqualsExtractor, arg0: hoot::Status::TypeEnum) -> None


#### extract(\*args, \*\*kwargs)
Overloaded function.


1. extract(self: hoot.libpyhoot.FeatureExtractor, arg0: hoot::OsmMap, arg1: hoot::Element, arg2: hoot::Element) -> float

extract extracts a feature from a given pair of elements.

The feature may be something like the distance between colors, the overlap of two polygons,
etc.


1. extract(self: hoot.libpyhoot.FeatureExtractor, map: hoot::OsmMap, target: List[hoot::Element], candidate: List[hoot::Element], ignored: List[bool] = []) -> numpy.ndarray[numpy.float64]

This override to the distance function is pyhoot specific and allows you to calculate distance
on an array of values in one pass.


#### getFactorType(_ = Non_ )

#### getNullTreatment(_ = Non_ )

#### get_factor_type()
getFactorType(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::FactorType

getFactorType returns the factor type for this feature/factor (Nominal or Numeric).


#### get_null_treatment()
getNullTreatment(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::NullTreatment

getNullTreatment returns the null treatment for this feature/factor (NullAsValue or
NullAsMissingValue).


#### isNull(_ = Non_ )

#### _static_ is_null()
isNull(arg0: float) -> bool


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.FeatureExtractor) -> QString


### _class_ hoot.libpyhoot.StringDistance()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


### _class_ hoot.libpyhoot.SuperfluousNodeRemover()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.SuperfluousNodeRemover) -> None


2. __init__(self: hoot.libpyhoot.SuperfluousNodeRemover, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.SuperfluousNodeRemover, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


#### apply(self: hoot.libpyhoot.SuperfluousNodeRemover, arg0: hoot.libpyhoot.OsmMap)

#### setConfiguration(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.SuperfluousNodeRemover, arg0: hoot::Settings) -> None

Set the configuration for this object.


### _class_ hoot.libpyhoot.TagCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.TagCriterion) -> None


2. __init__(self: hoot.libpyhoot.TagCriterion, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.TagCriterion, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.TagCriterion, arg0: QString, arg1: QString) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setConfiguration(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.TagCriterion, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.TagKeyCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.TagKeyCriterion) -> None


2. __init__(self: hoot.libpyhoot.TagKeyCriterion, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.TagKeyCriterion, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.TagKeyCriterion, arg0: QString) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setConfiguration(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.TagKeyCriterion, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.TagMatchExtractor()
Bases: `hoot.libpyhoot.FeatureExtractor`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.TagMatchExtractor) -> None


2. __init__(self: hoot.libpyhoot.TagMatchExtractor, arg0: QString) -> None


#### extract(\*args, \*\*kwargs)
Overloaded function.


1. extract(self: hoot.libpyhoot.FeatureExtractor, arg0: hoot::OsmMap, arg1: hoot::Element, arg2: hoot::Element) -> float

extract extracts a feature from a given pair of elements.

The feature may be something like the distance between colors, the overlap of two polygons,
etc.


1. extract(self: hoot.libpyhoot.FeatureExtractor, map: hoot::OsmMap, target: List[hoot::Element], candidate: List[hoot::Element], ignored: List[bool] = []) -> numpy.ndarray[numpy.float64]

This override to the distance function is pyhoot specific and allows you to calculate distance
on an array of values in one pass.


#### getFactorType(_ = Non_ )

#### getNullTreatment(_ = Non_ )

#### get_factor_type()
getFactorType(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::FactorType

getFactorType returns the factor type for this feature/factor (Nominal or Numeric).


#### get_null_treatment()
getNullTreatment(self: hoot.libpyhoot.FeatureExtractor) -> Tgs::DataFrame::NullTreatment

getNullTreatment returns the null treatment for this feature/factor (NullAsValue or
NullAsMissingValue).


#### isNull(_ = Non_ )

#### _static_ is_null()
isNull(arg0: float) -> bool


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.FeatureExtractor) -> QString


### _class_ hoot.libpyhoot.TagMergerFactory()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.TagMergerFactory)

#### getDefault(_ = Non_ )

#### getInstance(_ = Non_ )

#### getMerger(_ = Non_ )

#### get_default()
getDefault(self: hoot.libpyhoot.TagMergerFactory) -> hoot::TagMerger

Returns the default TagMerger.


#### _static_ get_instance()
getInstance() -> hoot.libpyhoot.TagMergerFactory


#### get_merger()
getMerger(self: hoot.libpyhoot.TagMergerFactory, arg0: QString) -> hoot::TagMerger


#### mergeTags(_ = Non_ )

#### _static_ merge_tags()
mergeTags(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. mergeTags(arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags, arg2: hoot::ElementType) -> hoot.libpyhoot.Tags

A convenience function for merging tags using the default mechanism. Equivalent to:
TagMergerFactory::getInstance().getDefault().mergeTags(t1, t2, et);


1. mergeTags(arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags) -> hoot.libpyhoot.Tags

A convenience function for merging tags using the default mechanism. Equivalent to:
TagMergerFactory::getInstance().getDefault().mergeTags(t1, t2, ElementType::Unknown);


#### reset(self: hoot.libpyhoot.TagMergerFactory)
Reset all cached information. This is necessary if the default tag config information changes.


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.TagMergerFactory) -> QString

Return the list of mergers as a string


### _class_ hoot.libpyhoot.Tags()
Bases: `pybind11_builtins.pybind11_object`


#### Tags(_ = Non_ )

#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.Tags) -> None


2. __init__(self: hoot.libpyhoot.Tags, arg0: QString, arg1: QString) -> None


#### add(self: hoot.libpyhoot.Tags, arg0: hoot.libpyhoot.Tags)
Adds all the tags in t into this set of tags. Tags in t overwrite tags in this.


#### addNote(_ = Non_ )

#### add_note()
addNote(self: hoot.libpyhoot.Tags, arg0: QString) -> None


#### appendValue(_ = Non_ )

#### appendValueIfUnique(_ = Non_ )

#### append_value()
appendValue(self: hoot.libpyhoot.Tags, arg0: QString, arg1: QString) -> None

Appends a value to a key. If the key already has a value then the values are semi-colon
delimited. If the key has no value then it is equivalent to simply setting the tag.


#### append_value_if_unique()
appendValueIfUnique(self: hoot.libpyhoot.Tags, arg0: QString, arg1: QString) -> None

Appends a value to a key. If the key already has a value then the values are semi-colon
delimited. If the key has no value then it is equivalent to simply setting the tag.

The value is only appended if it doesn’t already exist in the list.


#### bothHaveInformation(_ = Non_ )

#### _static_ both_have_information()
bothHaveInformation(arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags) -> bool

Determines if two sets of tags contain non-metadata information


* **Parameters**

    
    * **tags1** – first set of tags to examine


    * **tags2** – second set of tags to examine



* **Returns**

    true if both sets of tags contain non-metadata information; false otherwise



#### className(_ = Non_ )

#### _static_ class_name()
className() -> QString


#### clone(self: hoot.libpyhoot.Tags)

#### dataOnlyEqual(_ = Non_ )

#### data_only_equal()
dataOnlyEqual(self: hoot.libpyhoot.Tags, arg0: hoot.libpyhoot.Tags) -> bool

Similar to operator== but ‘hoot:

```
*
```

’ tags are ignored


#### get(self: hoot.libpyhoot.Tags, arg0: QString)

#### getCreateUuid(_ = Non_ )

#### getDataOnlyValues(_ = Non_ )

#### getDouble(_ = Non_ )

#### getFirstMatchingKey(_ = Non_ )

#### getFirstMatchingKvp(_ = Non_ )

#### getInformationCount(_ = Non_ )

#### getLength(_ = Non_ )

#### getList(_ = Non_ )

#### getMatchingKeys(_ = Non_ )

#### getName(_ = Non_ )

#### getNameKeys(_ = Non_ )

#### getNames(_ = Non_ )

#### getNonDebugCount(_ = Non_ )

#### getPseudoNames(_ = Non_ )

#### getVelocity(_ = Non_ )

#### get_create_uuid()
getCreateUuid(self: hoot.libpyhoot.Tags) -> QStringList

Gets the element’s UUID(s). If the UUID doesn’t exist then it creates a new UUID.

Given that elements can be conflated and all the old UUIDs are maintained, you may get a list
of multiple UUIDs. All of these UUIDs reference the same element.


#### get_data_only_values()
getDataOnlyValues(self: hoot.libpyhoot.Tags, arg0: hoot.libpyhoot.Tags) -> QStringList

Get a list of all non-‘hoot:

```
*
```

’ tags


#### get_double()
getDouble(self: hoot.libpyhoot.Tags, arg0: QString) -> float

Returns a double version of the value associated with k. If it cannot be parsed into a double
then an exception is thrown.


#### get_first_matching_key()
getFirstMatchingKey(self: hoot.libpyhoot.Tags, arg0: QStringList) -> QString

Returns the first tag key found from an input list of keys


* **Parameters**

    **keys** – tag keys to search for



* **Returns**

    a non-empty string if any key in the list was found; otherwise an empty string



#### get_first_matching_kvp()
getFirstMatchingKvp(self: hoot.libpyhoot.Tags, arg0: QStringList) -> QString

Returns the first matching key/value pair (kvp) from the input list


* **Parameters**

    **kvps** – list of kvp string to match; value wildcards are supported using ‘\*’



* **Returns**

    a kvp or an empty string if no matching kvp is found



#### get_information_count()
getInformationCount(self: hoot.libpyhoot.Tags) -> int

Return the number of tags that contain actual information, not meta-data or debug tags.
Meta-data tags include things like source and license. Debug is anything that starts with
hoot:. An example of an informational tag is name or highway.


#### get_length()
getLength(self: hoot.libpyhoot.Tags, arg0: QString) -> boost::units::quantity<boost::units::unit<boost::units::list<boost::units::dim<boost::units::length_base_dimension, boost::units::static_rational<1l, 1l> >, boost::units::dimensionless_type>, boost::units::homogeneous_system<boost::units::list<boost::units::si::meter_base_unit, boost::units::list<boost::units::scaled_base_unit<boost::units::cgs::gram_base_unit, boost::units::scale<10l, boost::units::static_rational<3l, 1l> > >, boost::units::list<boost::units::si::second_base_unit, boost::units::list<boost::units::si::ampere_base_unit, boost::units::list<boost::units::si::kelvin_base_unit, boost::units::list<boost::units::si::mole_base_unit, boost::units::list<boost::units::si::candela_base_unit, boost::units::list<boost::units::angle::radian_base_unit, boost::units::list<boost::units::angle::steradian_base_unit, boost::units::dimensionless_type> > > > > > > > > >, void>, double>

Returns the length in standard units (m).


#### get_list()
getList(self: hoot.libpyhoot.Tags, arg0: QString) -> QStringList

Returns the list of values associated with the key k. If k starts with regex? then all values
associated with the regular expression after regex? are returned. E.g. regex?a.\* will return
all values that start with a. The order of the results is arbitrary.


#### get_matching_keys()
getMatchingKeys(self: hoot.libpyhoot.Tags, arg0: QStringList) -> QStringList

Given a list of keys (that may include regex values), find all the keys in this Tags set that
match one or more entries in the list and return it. Each key will only be returned at most
once.


#### get_name()
getName(self: hoot.libpyhoot.Tags) -> QString

Returns a name given tags


* **Returns**

    the first name found, if one is present



#### _static_ get_name_keys()
getNameKeys(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. getNameKeys() -> QStringList

Return all the keys that are used in names.


1. getNameKeys(arg0: hoot.libpyhoot.Tags) -> QStringList

Get name keys for a set of tags


* **Parameters**

    **tags** – tags to parse name keys from



* **Returns**

    a list of name keys



#### get_names()
getNames(self: hoot.libpyhoot.Tags, include_alt_name: bool = True) -> QStringList

Return all the names for the current feature.


* **Parameters**

    **include_alt_name** – if true, returns names with the alt_name tag key



#### get_non_debug_count()
getNonDebugCount(self: hoot.libpyhoot.Tags) -> int


#### get_pseudo_names()
getPseudoNames(self: hoot.libpyhoot.Tags) -> QStringList

Return all the names associated with the feature. These are more loosely defined and may
include things like operator name and brand name. See conf/NameSchema.json for a definition.


#### get_velocity()
getVelocity(self: hoot.libpyhoot.Tags, arg0: QString) -> boost::units::quantity<boost::units::unit<boost::units::list<boost::units::dim<boost::units::length_base_dimension, boost::units::static_rational<1l, 1l> >, boost::units::list<boost::units::dim<boost::units::time_base_dimension, boost::units::static_rational<-1l, 1l> >, boost::units::dimensionless_type> >, boost::units::homogeneous_system<boost::units::list<boost::units::si::meter_base_unit, boost::units::list<boost::units::scaled_base_unit<boost::units::cgs::gram_base_unit, boost::units::scale<10l, boost::units::static_rational<3l, 1l> > >, boost::units::list<boost::units::si::second_base_unit, boost::units::list<boost::units::si::ampere_base_unit, boost::units::list<boost::units::si::kelvin_base_unit, boost::units::list<boost::units::si::mole_base_unit, boost::units::list<boost::units::si::candela_base_unit, boost::units::list<boost::units::angle::radian_base_unit, boost::units::list<boost::units::angle::steradian_base_unit, boost::units::dimensionless_type> > > > > > > > > >, void>, double>

Returns the speed in standard units (m/s).


#### hasAnyKey(_ = Non_ )

#### hasAnyKvp(_ = Non_ )

#### hasInformationTag(_ = Non_ )

#### hasKvp(_ = Non_ )

#### hasName(_ = Non_ )

#### hasSameNonMetadataTags(_ = Non_ )

#### has_any_key()
hasAnyKey(self: hoot.libpyhoot.Tags, arg0: QStringList) -> bool

Returns true if the tags have any key in the input list


* **Parameters**

    **keys** – tag keys to search for



* **Returns**

    true if the tags contain at least one of the keys; false otherwise



#### has_any_kvp()
hasAnyKvp(self: hoot.libpyhoot.Tags, arg0: QStringList) -> bool

Returns true if the tags have any key=value in the input list


* **Parameters**

    **kvps** – kvps to search for; value wildcards are supported using ‘\*’



* **Returns**

    true if tags contain at least one kvp; false otherwise



#### has_information_tag()
hasInformationTag(self: hoot.libpyhoot.Tags) -> bool

Return if there is at least one non-metadata tag. @sa getInformationalCount()


#### has_kvp()
hasKvp(self: hoot.libpyhoot.Tags, arg0: QString) -> bool

Returns true if the tags have the specified kvp


* **Parameters**

    **kvp** – kvp to search for; value wildcards are supported using ‘\*’



* **Returns**

    true if tags contain the kvp; false otherwise



#### has_name()
hasName(self: hoot.libpyhoot.Tags) -> bool

Determines whether a name exists in the set of tag


* **Returns**

    true if at least one name exists; false otherwise



#### has_same_non_metadata_tags()
hasSameNonMetadataTags(self: hoot.libpyhoot.Tags, arg0: hoot.libpyhoot.Tags) -> bool

Determines if two sets of tags have the same information values

This may have overlap with dataOnlyEqual, however the two have differences…worth looking
into at some point.


* **Parameters**

    **other** – tags to compare with



* **Returns**

    true if both sets of tags have the same information values; false otherwise



#### haveMatchingName(_ = Non_ )

#### _static_ have_matching_name()
haveMatchingName(arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags, arg2: bool) -> bool

Determines if two set of tags have a matching name


* **Parameters**

    
    * **tags1** – first set of tags to examine


    * **tags2** – second set of tags to examine


@parm strictNameMatch if true, will not consider names with the alt_name tag key
:returns: true if the tags have at least one matching name; false otherwise


#### isFalse(_ = Non_ )

#### isTrue(_ = Non_ )

#### isValidKvp(_ = Non_ )

#### is_false()
isFalse(self: hoot.libpyhoot.Tags, arg0: QString) -> bool

Checks for common false values such as ‘no’, ‘false’, ‘0’, ‘off’.

Note: It is not guaranteed that isFalse(tag) != isTrue(tag), but you are guaranteed that if
one of them is true the other will be false. E.g. value=apple will return false for both
methods.


#### is_true()
isTrue(self: hoot.libpyhoot.Tags, arg0: QString) -> bool

Checks for common true values such as ‘yes’, ‘true’, ‘1’, ‘on’.

Note: It is not guaranteed that isFalse(tag) != isTrue(tag), but you are guaranteed that if
one of them is true the other will be false. E.g. value=apple will return false for both
methods.


#### _static_ is_valid_kvp()
isValidKvp(arg0: QString) -> bool

Determines if a string is a valid tag key/value pair


* **Parameters**

    **str** – the string to examine



* **Returns**

    true if the input string is a valid kvp; false otherwise



#### kvpToKey(_ = Non_ )

#### kvpToParts(_ = Non_ )

#### kvpToVal(_ = Non_ )

#### kvp_to_key()
kvpToKey(self: QString) -> QString

Extracts a tag key from a tag key/value pair


* **Parameters**

    **kvp** – string to extract from



* **Returns**

    a tag key string



#### kvp_to_parts()
kvpToParts(self: QString) -> QStringList

@brief kvpToParts Breaks a KVP string into its constituent parts
:param kvp: a KVP string of the form <key>=<value>
:returns: a list of strings


#### kvp_to_val()
kvpToVal(self: QString) -> QString

Extracts a tag value from a tag key/value pair


* **Parameters**

    **kvp** – string to extract from



* **Returns**

    a tag value string



#### onlyOneContainsKvp(_ = Non_ )

#### onlyOneHasInformation(_ = Non_ )

#### _static_ only_one_contains_kvp()
onlyOneContainsKvp(arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags, arg2: QString) -> bool

Determines if either one of two sets of tags contain a particular key/value pair


* **Parameters**

    
    * **tags1** – first set of tags to examine


    * **tags2** – second set of tags to examine


    * **kvp** – key/value pair to search for



* **Returns**

    true if exactly one of the sets of tags contain the key/value pair; false otherwise



#### _static_ only_one_has_information()
onlyOneHasInformation(arg0: hoot.libpyhoot.Tags, arg1: hoot.libpyhoot.Tags) -> bool

Determines if one of two sets of tags contain non-metadata information


* **Parameters**

    
    * **tags1** – first set of tags to examine


    * **tags2** – second set of tags to examine



* **Returns**

    true if exactly one of sets of tags contain non-metadata information; false otherwise



#### readMeters(_ = Non_ )

#### readValues(_ = Non_ )

#### read_meters()
readMeters(self: hoot.libpyhoot.Tags, arg0: QString) -> float


#### read_values()
readValues(self: hoot.libpyhoot.Tags, arg0: QString, arg1: QStringList) -> None


#### remove(self: hoot.libpyhoot.Tags, arg0: QString)

#### removeByTagKeyStartsWith(_ = Non_ )

#### removeKeys(_ = Non_ )

#### removeMetadata(_ = Non_ )

#### remove_by_tag_key_starts_with()
removeByTagKeyStartsWith(self: hoot.libpyhoot.Tags, arg0: QString) -> int

Removes all tags with keys that start with the input substring


* **Parameters**

    **tagKeySubstring** – a substring to match



* **Returns**

    the number of tags removed



#### remove_keys()
removeKeys(self: hoot.libpyhoot.Tags, arg0: QStringList) -> None

Removes all tags with keys exactly matching those in the input list


* **Parameters**

    **keys** – the list of keys to remove



* **Returns**

    the number of tags removed



#### remove_metadata()
removeMetadata(self: hoot.libpyhoot.Tags) -> int

Removes all metadata tags (hoot:\* and those identified in the schema)


* **Returns**

    the number of tags removed



#### schemaVerticesToTags(_ = Non_ )

#### schema_vertices_to_tags()
schemaVerticesToTags(self: List[hoot::SchemaVertex]) -> hoot.libpyhoot.Tags

Converts a collection of schema vertices to tags


* **Parameters**

    **vertices** – schema vertices to convert



* **Returns**

    a set of tags



#### set(self: hoot.libpyhoot.Tags, arg0: QString, arg1: QString)
If a kvp is in other, then set it in this. If this already has that key then the value will
be overwritten.


#### setArea(_ = Non_ )

#### setList(_ = Non_ )

#### set_area()
setArea(self: hoot.libpyhoot.Tags, arg0: bool) -> None

Sets the area tag to either true (is an area element), or false (is not an area element)


#### set_list()
setList(self: hoot.libpyhoot.Tags, arg0: QString, arg1: QStringList) -> None


#### split(self: QString)
Splits the specified value up into individual values. For now it just splits on “;”, but it
may get more robust later.


#### _static_ tags()
Tags(arg0: QStringList) -> hoot.libpyhoot.Tags

Converts a list of KVPs into tags


* **Parameters**

    **kvps** – kvps to convert



* **Returns**

    a set of tags



#### toKeys(_ = Non_ )

#### toKvps(_ = Non_ )

#### to_dict(self: hoot.libpyhoot.Tags)

#### to_keys()
toKeys(self: hoot.libpyhoot.Tags) -> QStringList

toKeys returns the tags as a list of key strings
:returns: a list of key strings


#### to_kvps()
toKvps(self: hoot.libpyhoot.Tags) -> QStringList

Returns the tags as key/value pair strings


* **Returns**

    a list of key/value pairs



#### uuidKey(_ = Non_ )

#### _static_ uuid_key()
uuidKey() -> QString


### _class_ hoot.libpyhoot.TestUtils()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.TestUtils)
Return the singleton instance.


#### registerReset(_ = Non_ )

#### register_reset()
registerReset(self: hoot.libpyhoot.TestUtils, arg0: hoot::TestUtils::RegisteredReset) -> None

Register a way to reset the environment. This is most useful in plugins to avoid circular
references.


#### resetAll(_ = Non_ )

#### resetBasic(_ = Non_ )

#### resetConfigs(_ = Non_ )

#### resetEnvironment(_ = Non_ )

#### _static_ reset_all()
resetAll(confs: QStringList = []) -> None

resetAll Resets the test environment and including the MatchFactory
:param confs: custom confs to load during reset; if left blank the default config in

> ConfigOptions will be loaded


#### _static_ reset_basic()
resetBasic() -> None

Resets the test environment including counters, keys, and seeds


#### _static_ reset_configs()
resetConfigs(confs: QStringList = []) -> None

resetConfigs Reset the configuration from the default, Testing.conf, and input files
:param confs: custom config files to load during reset; if left blank the default config

> in ConfigOptions will be loaded


#### _static_ reset_environment()
resetEnvironment(confs: QStringList = []) -> None

resetEnvironment Resets the test environment to a known state.
:param confs: custom confs to load during reset; if left blank the default config in

> ConfigOptions will be loaded


#### toQuotedString(_ = Non_ )

#### _static_ to_quoted_string()
toQuotedString(arg0: QString) -> QString

Converts a string into a format that can be cut/paste into c++ code.


### _class_ hoot.libpyhoot.ToEnglishTranslateStringDistance()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.ToEnglishTranslateStringDistance) -> None


2. __init__(self: hoot.libpyhoot.ToEnglishTranslateStringDistance, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.ToEnglishTranslateStringDistance, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.ToEnglishTranslateStringDistance, arg0: hoot.libpyhoot.StringDistance) -> None


2. __init__(self: hoot.libpyhoot.ToEnglishTranslateStringDistance, arg0: hoot::Settings, arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a Settings object and StringDistance function.


1. __init__(self: hoot.libpyhoot.ToEnglishTranslateStringDistance, arg0: Dict[QString, QString], arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a dict of strings and a StringDistance function.


#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


#### setConfiguration(_ = Non_ )

#### setStringDistance(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.ToEnglishTranslateStringDistance, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_string_distance()
setStringDistance(self: hoot.libpyhoot.ToEnglishTranslateStringDistance, arg0: hoot.libpyhoot.StringDistance) -> None


### _class_ hoot.libpyhoot.UnifyingConflator()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(self: hoot.libpyhoot.UnifyingConflator)

#### apply(self: hoot.libpyhoot.UnifyingConflator, arg0: hoot::OsmMap)
apply conflates the specified map.

If the map is not in a planar projection it is reprojected. The map is not reprojected back to
the original projection when conflation is complete.
@see OsmMapOperation


#### getClassName(_ = Non_ )

#### getDescription(_ = Non_ )

#### getName(_ = Non_ )

#### getNumSteps(_ = Non_ )

#### get_class_name()
getClassName(self: hoot.libpyhoot.UnifyingConflator) -> QString


#### get_description()
getDescription(self: hoot.libpyhoot.UnifyingConflator) -> QString


#### get_name()
getName(self: hoot.libpyhoot.UnifyingConflator) -> QString


#### get_num_steps()
getNumSteps(self: hoot.libpyhoot.UnifyingConflator) -> int


### _class_ hoot.libpyhoot.Version()
Bases: `pybind11_builtins.pybind11_object`


#### \__init__(\*args, \*\*kwargs)

#### getBuiltBy(_ = Non_ )

#### getFullVersion(_ = Non_ )

#### getRevision(_ = Non_ )

#### getVersion(_ = Non_ )

#### _static_ get_built_by()
getBuiltBy() -> str


#### _static_ get_full_version()
getFullVersion() -> str


#### _static_ get_revision()
getRevision() -> str


#### _static_ get_version()
getVersion() -> str


### _class_ hoot.libpyhoot.WayNodeCriterion()
Bases: `hoot.libpyhoot.ElementCriterion`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.WayNodeCriterion) -> None


2. __init__(self: hoot.libpyhoot.WayNodeCriterion, arg0: hoot::OsmMap) -> None


#### clone(self: hoot.libpyhoot.ElementCriterion)

#### isSatisfied(_ = Non_ )

#### is_satisfied()
isSatisfied(

```
*
```

args, 

```
**
```

kwargs)
Overloaded function.


1. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: hoot::Element) -> bool


2. isSatisfied(self: hoot.libpyhoot.ElementCriterion, arg0: List[hoot::Element]) -> numpy.ndarray[bool]

This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:

    a boolean numpy array


#### setOsmMap(_ = Non_ )

#### set_osm_map()
setOsmMap(self: hoot.libpyhoot.WayNodeCriterion, arg0: hoot::OsmMap) -> None


#### toString(_ = Non_ )

#### to_string()
toString(self: hoot.libpyhoot.ElementCriterion) -> QString


### _class_ hoot.libpyhoot.WeightedWordDistance()
Bases: `hoot.libpyhoot.StringDistance`


#### \__init__(\*args, \*\*kwargs)
Overloaded function.


1. __init__(self: hoot.libpyhoot.WeightedWordDistance) -> None


2. __init__(self: hoot.libpyhoot.WeightedWordDistance, arg0: hoot::Settings) -> None


3. __init__(self: hoot.libpyhoot.WeightedWordDistance, arg0: Dict[QString, QString]) -> None

This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.


1. __init__(self: hoot.libpyhoot.WeightedWordDistance, arg0: hoot.libpyhoot.StringDistance) -> None


2. __init__(self: hoot.libpyhoot.WeightedWordDistance, arg0: hoot::Settings, arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a Settings object and StringDistance function.


1. __init__(self: hoot.libpyhoot.WeightedWordDistance, arg0: Dict[QString, QString], arg1: hoot.libpyhoot.StringDistance) -> None

Construct and set the configuration with a dict of strings and a StringDistance function.


#### compare(self: hoot.libpyhoot.StringDistance, arg0: QString, arg1: QString)
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.


#### setConfiguration(_ = Non_ )

#### setStringDistance(_ = Non_ )

#### set_configuration()
setConfiguration(self: hoot.libpyhoot.WeightedWordDistance, arg0: hoot::Settings) -> None

Set the configuration for this object.


#### set_string_distance()
setStringDistance(self: hoot.libpyhoot.WeightedWordDistance, arg0: hoot.libpyhoot.StringDistance) -> None


### hoot.libpyhoot.conf()
conf is a shortcut for Settings.get_instance()

## hoot.utils module

utils contains a number of useful utility functions that are not part of
c++ hootenanny


### hoot.utils.load_json(json, default_status=<TypeEnum.INVALID: 0>)
load_json loads an OsmMap from json and returns it.

## Module contents

pyhoot is an unofficial wrapper for Hootenanny.

Hootenanny is an open source map data conflation tool developed with machine
learning techniques to facilitate automated and semi-automated conflation of
critical Foundation GEOINT features in the topographic domain. In short, it
merges multiple maps into a single seamless map.

Use help(hoot.libpyhoot) for a complete list of wrapped classes.
