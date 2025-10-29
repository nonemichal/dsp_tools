from dataclasses import dataclass
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
from enum import StrEnum


class CsvFileType(StrEnum):
    """Enum representing types of CSV files."""

    SIGNAL = "signal.csv"
    OUTPUT = "out.csv"

    def get_full_path(self, csv_files_dir: str) -> Path:
        # Create a CSV file path based on the enum file type
        base_dir = Path(__file__).parent.parent.resolve()
        csv_path = base_dir / csv_files_dir
        csv_path.mkdir(parents=True, exist_ok=True)  # Create dir if does not exists
        file_name = self.value
        file_path = csv_path / file_name
        return file_path


@dataclass
class CsvFile:
    """Represents a CSV file with data and delimiter."""

    file_type: CsvFileType
    full_path: Path
    data: np.ndarray
    delimiter: str

    CSV_FILES_DIR: str = "csv_files"

    @classmethod
    def from_data(cls, data: np.ndarray, delimiter: str) -> "CsvFile":
        """Create a CSV object from data"""
        file_type = CsvFileType.SIGNAL
        full_path = file_type.get_full_path(cls.CSV_FILES_DIR)
        return cls(file_type, full_path, data, delimiter)

    @classmethod
    def from_output(cls, delimiter: str) -> "CsvFile":
        """Create a CSV object from output file"""
        file_type = CsvFileType.OUTPUT
        full_path = file_type.get_full_path(cls.CSV_FILES_DIR)
        data = np.loadtxt(full_path)
        return cls(file_type, full_path, data, delimiter)

    def save(self) -> None:
        """Save a CSV file."""
        np.savetxt(self.full_path, self.data, fmt="%2.10f")

    def plot(self) -> None:
        """Plot a CSV file"""
        plt.plot(self.data)
        plt.show()
