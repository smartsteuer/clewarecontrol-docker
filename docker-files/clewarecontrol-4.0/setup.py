#!/usr/bin/env python

from distutils.core import setup, Extension

cleware_module = Extension('_cleware',
                           sources=['cleware_wrap.cxx', 'USBaccessBasic.cpp', 'USBaccess.cpp'],
                           )

setup (name = 'cleware',
       version = '2.3',
       author      = "Folkert van Heusden",
       description = """Cleware library bindings for Python""",
       ext_modules = [cleware_module],
       py_modules = ["cleware"],
       )
