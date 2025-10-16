import numpy as np
from pathlib import Path


def plot_signal(x: np.ndarray, s: np.ndarray):
    import matplotlib.pyplot as plt

    plt.plot(x, s)
    plt.show()


if __name__ == "__main__":
    # Linspace
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

    # Plot signals
    plot_signal(x, s)

    # Save to csv file
    base_dir = Path(__file__).parent.resolve()
    file_name = "signal.csv"
    file_path = base_dir / file_name
    np.savetxt(file_path, s, fmt="%2.10f")
    print(f"Signal saved as {file_path}")
