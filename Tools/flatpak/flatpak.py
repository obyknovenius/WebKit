# Copyright (C) 2024 Igalia S.L.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this program; if not, write to the
# Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
# Boston, MA 02110-1301, USA.

import os
import subprocess
import sys

source_dir = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
build_dir = os.path.join(source_dir, "WebKitBuild")
flatpak_sdk_dir = os.path.join(build_dir, "UserFlatpak")
flatpak_state_dir = os.path.join(build_dir, "flatpak-builder")
flatpak_build_dir = os.path.join(build_dir, "build-dir")

def install_sdk():
    env = os.environ.copy()
    env["FLATPAK_USER_DIR"] = flatpak_sdk_dir

    command = ["flatpak",
               "remote-add",
               "--user",
               "--if-not-exists",
               "flathub",
               "https://flathub.org/repo/flathub.flatpakrepo"]
    print(command)

    subprocess.run(command, env=env)

    command = ["flatpak",
               "install",
               "--user",
               "--assumeyes",
               "flathub",
               "org.gnome.Platform//45",
               "org.gnome.Sdk//45"]
    print(command)

    subprocess.run(command, env=env)

def update_dependencies():
    env = os.environ.copy()
    env["FLATPAK_USER_DIR"] = flatpak_sdk_dir

    command = ["flatpak-builder",
               "--force-clean",
               "--state-dir=" + flatpak_state_dir,
               "--stop-at=webkit",
               flatpak_build_dir,
               "org.webkitgtk.MiniBrowser.json"]
    print(command)

    subprocess.run(command, env=env)

def run(args):
    env = os.environ.copy()
    env["FLATPAK_USER_DIR"] = flatpak_sdk_dir

    command = ["flatpak",
               "build",
               "--socket=wayland",
               "--socket=x11",
               "--device=dri",
               "--filesystem=host",
               "--share=network",
               "--talk-name=org.a11y.Bus",
               "--bind-mount=/run/host/font-dirs.xml=" + os.path.expanduser("~/.cache/font-dirs.xml"),
               flatpak_build_dir]
    command += args;
    print(command)

    subprocess.run(command, env=env)
