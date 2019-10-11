from setuptools import setup, find_packages
from codecs import open
from os import path

setup(
	name = 'H5PyVOL',

	version = '1.0.dev0',

	description = 'Abstract data model for HDF5 Python virtual object layers',

	author = 'pierlauro',

	url = 'https://github.com/pierlauro/H5PyVOL',

	classifiers = [
		'Development Status :: 5 - Production/Stable',
		'Intended Audience :: Developers',
		'Programming Language :: Python :: 3.5',
		'Programming Language :: Python :: 3.6',
		'Programming Language :: Python :: 3.7'
	],
	
	python_requires='>=3.5',

	keywords = 'hdf5 vol h5py',

	packages = find_packages( exclude = ['tests'] ),

	license = 'GNU Affero General Public License v3.0',

	project_urls = {
		'Bug Tracker': 'https://github.com/pierlauro/H5PyVOL/issues',
		'Source': 'https://github.com/pierlauro/H5PyVOL',
	}
)
