///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (2014) Alexander Stukowski
//
//  This file is part of OVITO (Open Visualization Tool).
//
//  OVITO is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  OVITO is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////

// taken from: https://gitlab.com/stuko/ovito/blob/67b18c48141054f20da94e67e6d899c27bcd75c1/src/plugins/pyscript/binding/PythonBinding.h

#ifndef __QT_BINDINGS_H__
#define __QT_BINDINGS_H__

// hoot
#include <hoot/core/util/Log.h>

// pybind11
#include <pybind11/pybind11.h>

// qt
#include <QString>
#include <QStringList>

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
                    if (!temp)
                    {
                      // TODO: Downgrading the logging of these error messages until the errors can be fixed in 
                      // the unit tests.
                      LOG_TRACE("Unable to encode str as UTF-8")
                      // UnicodeEncodeError
                      //PyErr_Print();
                      //PyErr_Clear();
                      return false;
                    }
                    load_src = temp;
                }
                char *buffer;
                ssize_t length;
                int err = PYBIND11_BYTES_AS_STRING_AND_SIZE(load_src.ptr(), &buffer, &length);
                if (err == -1)
                {
                  LOG_TRACE("Type error converting string")
                  // TypeError
                  //PyErr_Print();
                  //PyErr_Clear();
                  return false;
                }
                value = QString::fromUtf8(buffer, (int)length);
                return true;
            }

            static handle cast(const QString& src, return_value_policy /* policy */,
                handle /* parent */) {
                // this approach should be faster but there are edge cases with unicode escape
                // sequences.
//#if PY_VERSION_HEX >= 0x03030000    // Python 3.3
//                assert(sizeof(QChar) == 2);
//                return PyUnicode_FromKindAndData(PyUnicode_2BYTE_KIND, src.constData(),
//                  src.length());
//#else
                QByteArray a = src.toUtf8();
                return PyUnicode_FromStringAndSize(a.data(), (ssize_t)a.length());
//#endif
            }
        };

        /// Automatic Python <--> QStringList conversion
        template<> struct type_caster<QStringList> {
        public:
            PYBIND11_TYPE_CASTER(QStringList, _("QStringList"));

            bool load(handle src, bool) {
                if(!isinstance<sequence>(src)) return false;
                sequence seq = reinterpret_borrow<sequence>(src);
                for(size_t i = 0; i < seq.size(); i++)
                    value.push_back(seq[i].cast<QString>());
                return true;
            }

            static handle cast(const QStringList& src, return_value_policy /* policy */,
                handle /* parent */) {
                list lst;
                for(const QString& s : src)
                    lst.append(pybind11::cast(s));
                return lst.release();
            }
        };

    }
}

#endif
