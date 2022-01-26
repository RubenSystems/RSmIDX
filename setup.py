from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11.setup_helpers import ParallelCompile


ext_modules = [
    Pybind11Extension(
        "rsmidx",
        sorted(glob("sources/*.cpp") + ["Binding.cpp"]),  # Sort source files for reproducibility
    ),
]

ParallelCompile("NPY_NUM_BUILD_JOBS").install()


setup(cmdclass={"build_ext": build_ext}, ext_modules=ext_modules)