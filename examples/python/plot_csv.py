import sys
from pathlib import Path

# Determine the root directory of the project
project_root = Path(__file__).parent.parent.parent.resolve()

# Add the project root to sys.path if it's not already there
# This allows imports from the package to work regardless of the current working directory
if str(project_root) not in sys.path:
    sys.path.insert(0, str(project_root))

# Now we can safely import classes from our package
from python_dsp_tools import CsvFile, CsvFileType, Signal

if __name__ == "__main__":
    # Create a CSV file
    csv_file = CsvFile(CsvFileType.OUTPUT, None, "\n")
    csv_file.plot()
