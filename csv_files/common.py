import numpy as np
from pathlib import Path
from enum import StrEnum


class CsvFile(StrEnum):
    SIGNAL = "signal.csv"
    OUTPUT = "output.csv"

    def get_csv_path(self):
        """Get a CSV file path based on the enum value"""
        base_dir = Path(__file__).parent.resolve()
        file_name = Path(self.value)
        file_path = base_dir / file_name
        return file_path

    def generate_csv(self):
        """Generate a CSV file based on hardcoded values"""

        # Generate linspace
        start = 0.0
        end = 1.0
        n = 1000
        x = np.linspace(start, end, n)

        # Frequencies
        f1 = 80
        f2 = 240
        f3 = 400

        # Amplitudes
        a1 = 5
        a2 = 3
        a3 = 2

        # Signals
        s1 = a1 * np.sin(2 * np.pi * f1 * x)
        s2 = a2 * np.sin(2 * np.pi * f2 * x)
        s3 = a3 * np.sin(2 * np.pi * f3 * x)

        # Mixed signal
        s = s1 + s2 + s3

        # Get a csv file path
        file_path = get_csv_path()

        # Save to a CSV file
        np.savetxt(file_path, s, fmt="%2.10f")
        print(f"Signal saved as {file_path}")
