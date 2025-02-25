import os
import sys
import shutil
import subprocess
import multiprocessing
import logging
import re
import urllib.request

os.chdir(os.path.dirname(os.path.realpath(__file__)))

def get_version(file_path):
    """Extracts the version from the CMakeLists.txt file."""
    try:
        with open(file_path, 'r') as file:
            content = file.read()
            match = re.search(r'project\(\s*\w+\s+VERSION\s+([\d.]+)', content, re.IGNORECASE)
            if match:
                return match.group(1)
    except FileNotFoundError:
        logging.error("CMakeLists.txt file not found!")
        raise

    logging.error("Could not extract version from CMakeLists.txt")
    return None

# Setup logging
logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')

# Get the version
version = get_version('../CMakeLists.txt')
if not version:
    raise Exception("Could not extract version from CMakeLists file")

logging.info(f"Building DataPlotter version {version}")

# Define base directory
deploy_dir = os.path.join("deploy", "appdir")
if os.path.exists(deploy_dir):
    shutil.rmtree(deploy_dir)

# Create required directories
dirs = [
    os.path.join(deploy_dir, "usr", "bin"),
    os.path.join(deploy_dir, "usr", "share", "doc", "data-plotter"),
    os.path.join(deploy_dir, "usr", "share", "icons", "hicolor", "256x256", "apps"),
    os.path.join(deploy_dir, "usr", "share", "applications"),
]

for dir in dirs:
    os.makedirs(dir, exist_ok=True)

# File copying
files = {
    os.path.join("..", "build", "DataPlotter"): os.path.join(deploy_dir, "usr", "bin", "data-plotter"),
    os.path.join("..", "documentation", "license.txt"): os.path.join(deploy_dir, "usr", "share", "doc", "data-plotter", "copyright"),
    os.path.join("icon.png"): os.path.join(deploy_dir, "usr", "share", "icons", "hicolor", "256x256", "apps", "data-plotter.png"),
    os.path.join("data-plotter.desktop"): os.path.join(deploy_dir, "usr", "share", "applications", "data-plotter.desktop")
}

for src, dst in files.items():
    try:
        shutil.copy2(src, dst)
    except FileNotFoundError:
        logging.error(f"Missing file: {src}")
        raise

# Download appimage tools
linuxdeployqt = os.path.join("deploy", "linuxdeployqt")
appimagetool = os.path.join("deploy", "appimagetool")
urllib.request.urlretrieve("https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage", linuxdeployqt)
urllib.request.urlretrieve("https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage", appimagetool)
subprocess.run(["chmod", "+x", linuxdeployqt], check=True)
subprocess.run(["chmod", "+x", appimagetool], check=True)

# Copy required libraries
subprocess.run([linuxdeployqt, os.path.join(deploy_dir, "usr", "share", "applications", "data-plotter.desktop"), "-bundle-non-qt-libs"], check=True)

# Create the AppImage package
subprocess.run([appimagetool, "--guess", "--no-appstream", deploy_dir], check=True, env=dict(os.environ, VERSION=version))

logging.info("AppImage package created successfully!")
