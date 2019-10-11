.. image:: http://img.shields.io/pypi/v/h5pyvol.svg
   :target: https://pypi.python.org/pypi/h5pyvol

.. image:: https://img.shields.io/badge/python-3.5+-blue.svg
	:target: https://github.com/pierlauro/h5pyvol


H5PyVOL: Python HDF5 VOLs
==============================================

A simple library providing an abstract data model to implement Python virtual object layers for HDF5.


Usage
=====

Simply ``from h5pyvol import *`` in your code and implement a concrete class for each of the provided abstract ones: ``H5VOL``, ``H5File``, ``H5Group``, ``H5Dataset``.


Install from source
======================
``python3 setup.py install``

Install from pypi
====================
``pip install h5pyvol``

======

This is free software released into the public domain under the license AGPL, version 3.0. For more information, please refer to https://www.gnu.org/licenses/agpl-3.0.html
