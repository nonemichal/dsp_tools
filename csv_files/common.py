from pathlib import Path
from enum import StrEnum


class CsvFile(StrEnum):
    SIGNAL = ("signal.csv",)
    OUTPUT = ("output.csv",)

    def get_file_path(self):
        """Get a CSV file path based on the file directory"""
        base_dir = Path(__file__).parent.resolve()
        file_name = Path(self.value)
        file_path = base_dir / file_name
        return file_path
