import os
import re
from shutil import copyfile
import sys
import sysconfig
import platform
from pprint import pprint
import subprocess

from distutils.core import setup, Extension
from distutils.version import LooseVersion
from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext
from setuptools.command.test import test as TestCommand
from shutil import copyfile, copymode

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: " +
                ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)',
                                         out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        print(['cmake', ext.sourcedir])
        pprint(ext)
        pprint(ext.__dict__)
        pprint(self.build_temp)
        os.system(f"conan install {ext.sourcedir}")
        os.system(f"find {ext.sourcedir}")
        #self.copy_file("src/hoot/info/Version.cpp", ext.sourcedir)
        extdir = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name)))
        #extdir = os.path.abspath(ext.sourcedir)
        print(f"extdir {extdir}")
        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      ]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(
                cfg.upper(),
                extdir)]
            if sys.maxsize > 2**32:
                cmake_args += ['-A', 'x64']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j2']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(
            env.get('CXXFLAGS', ''),
            self.distribution.get_version())
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args,
                              cwd=self.build_temp, env=env)
        subprocess.check_call(['cmake', '--build', '.'] + build_args,
                              cwd=self.build_temp)
        # Copy *_test file to tests directory
        #test_bin = os.path.join(self.build_temp, 'tests')
        #self.copy_test_file(self.build_temp, "src/hoot")
        os.system(f"find {ext.sourcedir}")
        lib_dir = self.build_temp.replace("temp", "lib")
        print([f"{self.build_temp}/lib/libpyhoot.so", f"{lib_dir}/hoot/libpyhoot.so"])
        copyfile(f"{self.build_temp}/lib/libpyhoot.so", f"{lib_dir}/hoot/libpyhoot.so")
        os.system(f"find {ext.sourcedir}")
        print()  # Add an empty line for cleaner output

    def copy_file(self, src_file, dest_dir):
        '''
        Copy ``src_file`` to ``dest_file`` ensuring parent directory exists.
        By default, message like `creating directory /path/to/package` and
        `copying directory /src/path/to/package -> path/to/package` are displayed on standard output. Adapted from scikit-build.
        '''
        print(os.path.dirname(src_file))
        # Create directory if needed
        dest_dir = os.path.join(os.path.dirname(os.path.abspath(dest_dir)), 
            os.path.dirname(src_file))
        if dest_dir != "" and not os.path.exists(dest_dir):
            print("creating directory {}".format(dest_dir))
            os.makedirs(dest_dir)

        # Copy file
        src_dir = os.path.dirname(os.path.abspath(__file__))
        print(src_dir)
        src_file = os.path.join(src_dir, src_file)
        dest_file = os.path.join(dest_dir, os.path.basename(src_file))
        print("copying {} -> {}".format(src_file, dest_file))
        copyfile(src_file, dest_file)
        copymode(src_file, dest_file)

setup(name = 'hoot',
        version = '0.0.4',
        description = 'This is an unofficial wrapper of Hootenanny',
        ext_modules = [CMakeExtension("hoot/hoot")],
        packages = find_packages("src"),
        package_data = {"": [
            "*.cpp",
            "info/*.cpp",
            "*.so",
        ]},
	platforms = "manylinux2014",
        package_dir = {"": "src"},
        cmdclass=dict(build_ext=CMakeBuild),
        # don't try to run this from a zip file
        zip_safe=False,
)
