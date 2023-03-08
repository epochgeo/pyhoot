import glob
import os
import re
from shutil import copyfile, copymode, copytree, copy
import multiprocessing
from pathlib import Path
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

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=["libcode.version"])
        self.sourcedir = os.path.abspath(sourcedir)
        print("self.sourcedir: " + self.sourcedir)

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
        #os.system(f"find {ext.sourcedir}")
        extdir = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name)))
        #extdir = os.path.abspath(ext.sourcedir)
        print(f"extdir {extdir}")
        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir]

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
            build_args += ['--', f'-j{multiprocessing.cpu_count()}']

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
        #os.system(f"find {ext.sourcedir}")
        lib_dir = self.build_temp.replace("temp", "lib")
        out_dir = self.build_temp.replace("temp", "")
        print([f"{self.build_temp}/lib/libpyhoot.so", f"{lib_dir}/hoot/libpyhoot.so"])
        # When creating a local development pip install, this won't exist
        if os.path.exists(f"{self.build_temp}/lib/libpyhoot.so"):
            os.system(f"mkdir -p {lib_dir}/hoot")
            copyfile(f"{self.build_temp}/lib/libpyhoot.so", f"{lib_dir}/hoot/libpyhoot.so")
        os.system(f"find {ext.sourcedir}")
        self.copy_dir(f"{self.build_temp}/conf", f"{lib_dir}/hoot/conf")
        os.system(f"gunzip {lib_dir}/hoot/conf/dictionary/WordsAbridged.sqlite.gz")
        os.system(f"mv " +\
                  "{lib_dir}/hoot/conf/dictionary/WordsAbridged.sqlite.gz " + \
                  "{lib_dir}/hoot/conf/dictionary/Words.sqlite")

        self.copy_dir(f"{self.build_temp}/docs", f"{lib_dir}/hoot/docs",
                      extension="*.asciidoc")
        self.copy_dir(f"{self.build_temp}/rules", f"{lib_dir}/hoot/rules")
        self.copy_dir(f"{self.build_temp}/bin", f"{lib_dir}/hoot/bin")
        # We don't need HootTest and it is kinda big
        os.system(f"rm -f {lib_dir}/hoot/bin/HootTest")
        self.copy_dir(f"{self.build_temp}/gdal", f"{lib_dir}/hoot/gdal")
        copyfile(f"{self.build_temp}/bin/RunHoot.sh",
                 f"{lib_dir}/hoot/bin/hoot")
        # This needs to be executable.
        os.system(f"chmod +x {lib_dir}/hoot/bin/hoot")
        # use `python -m hoot download-data` instead
        # copyfile(f"{self.build_temp}/proj.db", f"{lib_dir}/hoot/proj.db")
        # copyfile(f"{self.build_temp}/res/icudt69l.dat",
        #          f"{lib_dir}/hoot/conf/icudt69l.dat")
        copyfile(f"{self.build_temp}/res/test-files/ToyTestA.osm",
                 f"{lib_dir}/hoot/ToyTestA.osm")
        copyfile(f"{self.build_temp}/res/test-files/ToyTestB.osm",
                 f"{lib_dir}/hoot/ToyTestB.osm")
        print()  # Add an empty line for cleaner output

    def copy_dir(self, src, dest, extension=None):
        if extension is not None:
            print(f"copying directory from {src} to {dest} with extension {extension}")
            for file_path in glob.glob(os.path.join(src, '**', extension), recursive=True):
                rel_path = str(Path(file_path).relative_to(src))
                new_path = os.path.join(dest, rel_path)
                print(f"copying {file_path} to {new_path}")
                os.makedirs(os.path.dirname(new_path), exist_ok=True)
                copy(file_path, new_path)
        else:
            print(f"copying directory from {src} to {dest}")
            copytree(src, dest)

    def copy_file(self, src_file, dest_dir):
        '''
        Copy ``src_file`` to ``dest_file`` ensuring parent directory exists.
        By default, message like `creating directory /path/to/package` and
        `copying directory /src/path/to/package -> path/to/package` are 
        displayed on standard output. Adapted from scikit-build.
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

# TODO: make the version be read from the VERSION file again
setup(name = 'hoot',
        version = "0.2.64.13",
        description = 'This is an unofficial wrapper of Hootenanny',
        long_description = open("README.md").read(),
        long_description_content_type = "text/markdown",
        ext_modules = [CMakeExtension("hoot/hoot")],
        extras_require = {
            "dev": [
                "setuptools",
                "auditwheel",
                "setuptools",
                # For building API docs
                "sphinx",
                "sphinx-markdown-builder",
                "sphinx-autodoc-typehints",
                "conan",
                "build",
                "twine",
                "pydoc-markdown",
            ]
        },
        packages = find_packages("src"),
        package_dir = {"": "src"},
        package_data = {"": [
            "VERSION",
            "libcode.version",
            "py/*",
            "py/*/*",
            "py/*/*/*",
            "py/*/*/*/*",
            "py/*/*/*/*/*",
            "py/*/*/*/*/*/*",
            "*.so",
        ]},
        platforms = "manylinux2014",
        cmdclass=dict(build_ext=CMakeBuild),
        # don't try to run this from a zip file
        zip_safe=False,
)
