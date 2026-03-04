from setuptools import find_packages
from setuptools import setup

setup(
    name='speech_to_text_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('speech_to_text_interfaces', 'speech_to_text_interfaces.*')),
)
