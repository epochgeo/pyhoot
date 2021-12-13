
#include <boost/noncopyable.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/util/Factory.h>

namespace py = pybind11;
using namespace hoot;

namespace pybind11 { 
    namespace detail {
        /// Automatic Python string <--> QString conversion
        template<> struct type_caster<QString> {
        public:
            PYBIND11_TYPE_CASTER(QString, _("QString"));

            bool load(handle src, bool) {
                if(!src) return false;
                object temp;
                handle load_src = src;
                if(PyUnicode_Check(load_src.ptr())) {
                    temp = reinterpret_steal<object>(PyUnicode_AsUTF8String(load_src.ptr()));
                    if (!temp) { PyErr_Clear(); return false; }  // UnicodeEncodeError
                    load_src = temp;
                }
                char *buffer;
                ssize_t length;
                int err = PYBIND11_BYTES_AS_STRING_AND_SIZE(load_src.ptr(), &buffer, &length);
                if (err == -1) { PyErr_Clear(); return false; }  // TypeError
                value = QString::fromUtf8(buffer, (int)length);
                return true;
            }

            static handle cast(const QString& src, return_value_policy /* policy */, handle /* parent */) {
#if PY_VERSION_HEX >= 0x03030000    // Python 3.3
                assert(sizeof(QChar) == 2);
                return PyUnicode_FromKindAndData(PyUnicode_2BYTE_KIND, src.constData(), src.length());
#else
                QByteArray a = src.toUtf8();
                return PyUnicode_FromStringAndSize(a.data(), (ssize_t)a.length());
#endif
            }
        };
    }
}

void init_Factory(py::module_& m)
{
    py::class_<hoot::Factory, std::unique_ptr<Factory, py::nodelete> >(m, "Factory")
        .def(py::init([]() { return &Factory::getInstance(); }))
        .def("getObjectNamesByBase",
            [](const QString& base) {
                std::vector<std::string> result;
                std::vector<QString> convertMe = Factory::getInstance().getObjectNamesByBase(base);
                for (size_t i = 0; i < convertMe.size(); i++)
                {
                    result.push_back(convertMe[i].toStdString());
                }
                return result;
            },
            "returns all registered classes that implement the given base class"
        );
}

