import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
from enum import StrEnum
from typing import Any


class CsvFileType(StrEnum):
    """Enum representing types of CSV files."""

    SIGNAL = "signal.csv"
    OUTPUT = "out.csv"


class CsvFile:
    """Represents a CSV file with data and delimiter."""

    CSV_FILES_DIR: str = "csv_files"

    def __init__(
        self, file_type: CsvFileType, data: np.ndarray | None, delimiter: str
    ) -> None:
        self.file_type: CsvFileType = file_type

        if not delimiter:
            raise ValueError("delimiter cannot be empty.")

        self.file_path: Path = self._get_file_path()

        if data is None or len(data) == 0:
            if file_type == CsvFileType.OUTPUT:
                self.data = np.loadtxt(self.file_path)
            else:
                raise ValueError("data cannot be None or empty.")

        self.data: np.ndarray = data
        self.delimiter: str = delimiter

        self._dict: dict[str, Any] = dict(vars(self))

        print("CsvFile created")

    def _get_file_path(self) -> Path:
        # Create a CSV file path based on the enum value
        base_dir = Path(__file__).parent.parent.parent.resolve()
        csv_path = base_dir / self.CSV_FILES_DIR
        csv_path.mkdir(parents=True, exist_ok=True)  # Create dir if does not exists
        file_name = Path(self.file_type.value)
        file_path = csv_path / file_name
        return file_path

    def save(self) -> None:
        """Save a CSV file."""
        np.savetxt(self.file_path, self.data, fmt="%2.10f")
        print(f"Signal saved as {self.file_path}.")

    def plot(self):
        """Plot a CSV file"""
        plt.plot(self.data)
        plt.show()
