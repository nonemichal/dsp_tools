import numpy as np
import matplotlib.pyplot as plt
from common import get_file_path


def plot_signal(s: np.ndarray):
    """Plot signal"""
    plt.plot(s)
    plt.show()


if __name__ == "__main__":
    # Get a file path
    file_path = get_file_path()

    # Load a CSV file
    s = np.loadtxt(file_path)

    # Plot signal
    plot_signal(s)
