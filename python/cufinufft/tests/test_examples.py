"""
Discover and run Python example scripts as unit tests.
"""

import os
import subprocess
import sys
from pathlib import Path

import pytest

examples_dir = os.path.join(Path(__file__).resolve().parents[1], "examples")

scripts = []
for filename in os.listdir(examples_dir):
    if filename.endswith(".py"):
        scripts.append(os.path.join(examples_dir, filename))

@pytest.mark.parametrize("filename", scripts)
def test_example(filename):
    subprocess.check_call([sys.executable, filename])
