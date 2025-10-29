import numpy as np


class Signal:
    """Universal signal class that stores x and data."""

    def __init__(self, x: np.ndarray, data: np.ndarray) -> None:
        self.x: np.ndarray = np.asarray(x)
        self.data: np.ndarray = np.asarray(data)

        if len(self.x) != len(self.data):
            raise ValueError("x and data must have the same length.")

    @classmethod
    def sine(
        cls,
        amplitude: float,
        frequency: float,
        duration: float,
        sample_rate: float,
        phase: float = 0.0,
    ) -> "Signal":
        """Generate a sine wave signal."""
        x = np.linspace(0, duration, int(duration * sample_rate), endpoint=False)
        data = amplitude * np.sin(2 * np.pi * frequency * x + phase)
        return cls(x, data)

    @classmethod
    def square(
        cls, amplitude: float, frequency: float, duration: float, sample_rate: float
    ) -> "Signal":
        """Generate a square wave signal."""
        x = np.linspace(0, duration, int(duration * sample_rate), endpoint=False)
        data = amplitude * np.sign(np.sin(2 * np.pi * frequency * x))
        return cls(x, data)

    @classmethod
    def noise(cls, amplitude: float, duration: float, sample_rate: float) -> "Signal":
        """Generate a random noise signal."""
        x = np.linspace(0, duration, int(duration * sample_rate), endpoint=False)
        data = amplitude * np.random.randn(len(x))
        return cls(x, data)

    def __add__(self, other: "Signal") -> "Signal":
        """Add two signals (must have the same x)."""
        if not np.allclose(self.x, other.x):
            raise ValueError("Signals must have the same x axis to be added.")
        return Signal(self.x, self.data + other.data)

    def normalize(self) -> "Signal":
        """Normalize signal to range [-1, 1]."""
        max_val = np.max(np.abs(self.data))
        return Signal(self.x, self.data / max_val)

    def copy(self) -> "Signal":
        """Return a deep copy of the signal."""
        return Signal(np.copy(self.x), np.copy(self.data))
