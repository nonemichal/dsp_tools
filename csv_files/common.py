from pathlib import Path


def get_file_path():
    """Get a CSV file path based on the file directory"""
    base_dir = Path(__file__).parent.resolve()
    file_name = "signal.csv"
    file_path = base_dir / file_name
    return file_path
