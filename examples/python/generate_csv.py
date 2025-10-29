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
    # Common values
    duration = 1  # 1 second
    sample_rate = 1000  # 1000 samples per second
    delimiter = "\n"

    Amps = [1, 2, 3]  # Amplitudes
    Freqs = [100, 250, 450]  # Frequencies

    # Create signals
    s1 = Signal.sine(Amps[0], Freqs[0], duration, sample_rate)
    s2 = Signal.sine(Amps[1], Freqs[1], duration, sample_rate)
    s3 = Signal.sine(Amps[2], Freqs[2], duration, sample_rate)

    # Sum signals
    s = s1 + s2 + s3
    print("Signals mixed")

    # Create a CSV file
    csv_file = CsvFile.from_data(s.data, delimiter)
    csv_file.plot()
    csv_file.save()
    print(f"File saved as {csv_file.full_path}")
