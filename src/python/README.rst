.. image:: http://img.shields.io/pypi/v/cpyvol.svg
   :target: https://pypi.python.org/pypi/cpyvol

.. image:: https://img.shields.io/badge/python-3.5+-blue.svg
	:target: https://github.com/pierlauro/cpyvol


CPyVol: Python HDF5 VOLs usable from C
==============================================

A simple library providing an abstract data model to implement Python virtual object layers for HDF5.


Usage
=====

Simply ``from cpyvol import *`` in your code and implement a concrete class for each of the provided abstract ones: ``H5VOL``, ``H5File``, ``H5Group``, ``H5Dataset``.


Installing
==========
``pip install cpyvol`` - no dependencies needed.

======

This is free software released into the public domain under the license AGPL, version 3.0. For more information, please refer to https://www.gnu.org/licenses/agpl-3.0.html
