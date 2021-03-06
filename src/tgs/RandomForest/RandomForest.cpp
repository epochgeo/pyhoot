/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

// tgs
#include <tgs/RandomForest/RandomForest.h>

namespace py = pybind11;
using namespace Tgs;

namespace hoot
{

using namespace std;

static void init_RandomForest(py::module_& m)
{
  auto wrapme =
    py::class_<RandomForest, std::shared_ptr<RandomForest> >
      (m, "RandomForest")
    .def(py::init<>())
    .def("clear", &RandomForest::clear,
R"TOK(
 Clears the random forest of its trees.
)TOK")
    .def("classifyVector",
      [](RandomForest& self, const vector<double> & dataVector, py::dict& dict) {
        map<string, double> scores;
        self.classifyVector(dataVector, scores);
        for (const auto& kvp: scores)
        {
          dict[py::str(kvp.first)] = kvp.second;
        }
      }, R"TOK(
Classifies a data vector against a generated random forest.

The vector is classified against each tree in the forest and the final classification is the
result of majority vote for each tree.

:param dataVector: a single data vector of size N where N is the number of factors
:param scores: a map to hold the classification results as class name mapped to probability
)TOK")
//    .def("exportModel", &RandomForest::exportModel, R"TOK(
// Exports the random forest to a file

//:param modelDoc: the active DOM document
//:param parentNode: the parent node to append the forest
//)TOK")
//    .def("exportModel", &RandomForest::exportModel, R"TOK(
//Exports the random forest to a file

//:param fileStream: Opened filestream for writing the random forest to a file; caller is
//responsible for closing the stream
//)TOK")
    .def("findAverageError", &RandomForest::findAverageError, R"TOK(
Finds the average classification error statistic for the forest based on the
oob sets for the trees

:param data: the data set to operate upon
:param average: variable to hold the computed average error
:param stdDev: variable to hold the computed standard deviation
)TOK")
    .def("findProximity", &RandomForest::findProximity, R"TOK(
Computes the proximity of the data vectors in the data set by running the
complete data set through the tree and then tracking which vectors
were classified to the same node

:param data: the set of data vectors
:param proximity: a n x n (where n is the number of total data vectors) adjacency matrix
)TOK")
//    .def("generateResults", &RandomForest::generateResults, R"TOK(
//This generates a text file containing the raw probability scores and a text file
//containing the confusion matrix along with generated balanced *accuracy
//)TOK")
//    .def("getFactorImportance", &RandomForest::getFactorImportance, R"TOK(
// Gets the factor importance as generated by the random forest the highest
// values correspond to most important factors.

// :param data: the original data set
// :param factorImportance: a map of factor labels to purity improvement
//)TOK")
//    .def("getFactorLabels", &RandomForest::getFactorLabels, R"TOK(
//Return a vector of the factor labels used to train this random forest.
//)TOK")
    .def("importModel", [](RandomForest& self, QString filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          throw IoException("failure opening " + filename);
        }
        self.importModel(file);
      }, R"TOK(
importModel import the random forest object
:param e: the XML DOM element for the forest
)TOK")
//    .def("importModel", &RandomForest::importModel, R"TOK(
//Import the random forest object

//:param file: an opened file handle to a random forest (.rf) file; caller is responsible for
//closing the handle
//)TOK")
    .def("isTrained", &RandomForest::isTrained, R"TOK(
 :returns: true if the forest has been trained
)TOK")
//    .def("replaceMissingTrainingValues", &RandomForest::replaceMissingTrainingValues, R"TOK(
//replaceMissingTrainingValues

//Replaces null values in the training data with the median values by class

//Should be used after all training data is applied and before a model is generated
//)TOK")
    .def("trainBinary", &RandomForest::trainBinary, R"TOK(
Build the forest from a data set

:param data: the data set to train on
:param numTrees: the number of random trees to create
:param numFactors: the number of factors to randomly choose as candidates for node splitting
:param posClass: the name of the positive class
:param nodeSize: the minimum number of data vectors in a set to split a node
:param retrain: fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)
:param balanced: true if the forest will be balanced
)TOK")
    .def("trainMulticlass", &RandomForest::trainMulticlass, R"TOK(
Build the forest from a data set

:param data: the data set to train on
:param numTrees: the number of random trees to create
:param numFactors: the number of factors to randomly choose as candidates for node splitting
:param nodeSize: the minimum number of data vectors in a set to split a node
:param retrain: fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)
:param balanced: true if the forest will be balanced
)TOK")
    .def("trainRoundRobin", &RandomForest::trainRoundRobin, R"TOK(
Build the forest from a data set

:param data: the data set to train on
:param numTrees: the number of random trees to create
:param numFactors: the number of factors to randomly choose as candidates for node splitting
:param posClass: the name of the positive class
:param negClass: the name of the negative class
:param nodeSize: the minimum number of data vectors in a set to split a node
:param retrain: fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)
:param balanced: true if the forest will be balanced
)TOK")
    .def("trainBinary", &RandomForest::trainBinary,
R"TOK(
Build the forest from a data set

:param data: the data set to train on
:param numTrees: the number of random trees to create
:param numFactors: the number of factors to randomly choose as candidates for node splitting
:param posClass: the name of the positive class
:param nodeSize: the minimum number of data vectors in a set to split a node
:param retrain: fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)
:param balanced: true if the forest will be balanced
)TOK")
    .def("trainMulticlass", &RandomForest::trainMulticlass, R"TOK(
Build the forest from a data set

:param data: the data set to train on
:param numTrees: the number of random trees to create
:param numFactors: the number of factors to randomly choose as candidates for node splitting
:param nodeSize: the minimum number of data vectors in a set to split a node
:param retrain: fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)
:param balanced: true if the forest will be balanced
)TOK")
    .def("trainRoundRobin", &RandomForest::trainRoundRobin, R"TOK(
Build the forest from a data set

:param data: the data set to train on
:param numTrees: the number of random trees to create
:param numFactors: the number of factors to randomly choose as candidates for node splitting
:param posClass: the name of the positive class
:param negClass: the name of the negative class
:param nodeSize: the minimum number of data vectors in a set to split a node
:param retrain: fraction of top factors to use in retraining model (1.0 means use all factors and no retraining)
:param balanced: true if the forest will be balanced
)TOK")
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_RandomForest)

}
