import numpy as np
from .common import get_file_path

if __name__ == "__main__":
    # Generate linspace
    start = 0.0
    end = 1.0
    n = 1000
    x = np.linspace(start, end, n)

    # Frequencies
    f1 = 2
    f2 = 6
    f3 = 10

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

    # Get file path
    file_path = get_file_path()

    # Save to csv file
    np.savetxt(file_path, s, fmt="%2.10f")
    print(f"Signal saved as {file_path}")
