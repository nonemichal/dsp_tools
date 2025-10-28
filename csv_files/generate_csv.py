import numpy as np
from common import get_file_path

if __name__ == "__main__":
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

    # Get a file path
    file_path = get_file_path()

    # Save to a CSV file
    np.savetxt(file_path, s, fmt="%2.10f")
    print(f"Signal saved as {file_path}")
