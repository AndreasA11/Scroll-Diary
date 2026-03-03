from setuptools import find_packages
from setuptools import setup

setup(
    name='audio_samples_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('audio_samples_interfaces', 'audio_samples_interfaces.*')),
)
