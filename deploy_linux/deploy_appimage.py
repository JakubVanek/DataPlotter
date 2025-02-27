import os
import shutil
import subprocess
import logging
import re
import urllib.request


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

def setup_logging():
    """Configures logging."""
    logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')

def create_directories(app_dir):
    """Creates necessary directories for the Debian package."""
    dirs = [
        os.path.join(app_dir, "usr", "bin"),
        os.path.join(app_dir, "usr", "share", "doc", "data-plotter"),
        os.path.join(app_dir, "usr", "share", "icons", "hicolor", "256x256", "apps"),
        os.path.join(app_dir, "usr", "share", "applications"),
    ]
    for dir in dirs:
        os.makedirs(dir, exist_ok=True)

def copy_files(app_dir):
    """Copies necessary files into the deployment directory."""
    files = {
        "../build/DataPlotter": os.path.join(app_dir, "usr", "bin", "data-plotter"),
        "../documentation/license.txt": os.path.join(app_dir, "usr", "share", "doc", "data-plotter", "copyright"),
        "icon.png": os.path.join(app_dir, "usr", "share", "icons", "hicolor", "256x256", "apps", "data-plotter.png"),
        "data-plotter.desktop": os.path.join(app_dir, "usr", "share", "applications", "data-plotter.desktop")
    }
    for src, dst in files.items():
        try:
            shutil.copy2(src, dst)
        except FileNotFoundError:
            logging.error(f"Missing file: {src}")
            raise

def update_desktop_file(app_dir, version):
    """Updates the .desktop file with the correct version."""
    file_path = os.path.join(app_dir, "usr", "share", "applications", "data-plotter.desktop")
    with open(file_path, "r") as file:
        content = file.read().replace("{version}", version)
    with open(file_path, "w") as file:
        file.write(content)

def set_permissions(app_dir):
    """Sets correct permissions for executable and DEBIAN directory."""
    subprocess.run(["chmod", "755", os.path.join(app_dir, "usr", "bin", "data-plotter")], check=True)

def download_tools(output_dir):
    linuxdeployqt = os.path.join(output_dir, "linuxdeployqt")
    appimagetool = os.path.join(output_dir, "appimagetool")
    urllib.request.urlretrieve("https://github.com/probonopd/linuxdeployqt/releases/download/continuous/"
                               "linuxdeployqt-continuous-x86_64.AppImage", linuxdeployqt)
    urllib.request.urlretrieve("https://github.com/AppImage/appimagetool/releases/download/continuous/"
                               "appimagetool-x86_64.AppImage", appimagetool)
    subprocess.run(["chmod", "755", linuxdeployqt], check=True)
    subprocess.run(["chmod", "755", appimagetool], check=True)
    return linuxdeployqt, appimagetool

def build_appimage(linuxdeployqt, appimagetool, version, src_dir, app_dir):
    """Builds the AppImage bundle."""

    # just a pointer t placeo the application
    desktop_file = os.path.join(app_dir, "usr", "share", "applications", "data-plotter.desktop")
    # scan thhese QML sources for imports
    qml_sources = os.path.join(src_dir, 'qml')
    # place where external auto-update tools will look for incremental update files
    update_info = 'gh-releases-zsync|jirimaier|DataPlotter|latest|DataPlotter-*x86_64.AppImage.zsync'

    appimagetool_env = os.environ.copy()
    appimagetool_env['APPIMAGETOOL_APP_NAME'] = 'DataPlotter'
    appimagetool_env['VERSION'] = version

    # copy dependencies into the AppDir
    subprocess.run([linuxdeployqt, desktop_file, "-bundle-non-qt-libs", "-qmldir=" + qml_sources], check=True)

    # use appimagetool directly for AppImage packaging in order to get the static AppImage runtime
    # (that runtime no longer depends on the old libfuse2)
    subprocess.run([appimagetool, "--updateinformation", update_info, app_dir],
                   env=appimagetool_env,
                   cwd=os.path.dirname(app_dir),
                   check=True)
    logging.info("AppImage created successfully!")


def main():
    """Main function to execute the build steps."""
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    setup_logging()

    version = get_version('../CMakeLists.txt')
    if not version:
        raise Exception("Could not extract version from CMakeLists file")

    logging.info(f"Building DataPlotter version {version}")

    src_dir = os.path.abspath('..')
    output_dir = os.path.abspath("deploy")
    app_dir = os.path.join(output_dir, "AppDir")

    if os.path.exists(output_dir):
        shutil.rmtree(output_dir)

    create_directories(app_dir)
    copy_files(app_dir)
    update_desktop_file(app_dir, version)
    set_permissions(app_dir)
    linuxdeployqt, appimagetool = download_tools(output_dir)
    build_appimage(linuxdeployqt, appimagetool, version, src_dir, app_dir)

if __name__ == "__main__":
    main()
