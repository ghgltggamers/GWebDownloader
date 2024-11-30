# GWebDownloader
An OpenSource software for linux systems for downloading entire static websites with a lot of ease, Written entirely in C++ with GTK+ 3.0 and WebKit2Gtk 4.0.
Uses wget for downloading websites with a lot of ease. wget comes preinstalled locally with GWebDownloader itself.

## Pre-requesties
Make sure that you have the following packages installed in you distro othevise due to lack of dependencies the software itself won't work at all.

1.) Gtk+ 3.0 <br>
2.) Webkit2Gtk 4.0 <br>
3.) GNU GCC/G++ <br>

### Don't have any of these dependencies ?
Install them for you distro! Example linux

**Ubuntu/Debian**
```bash
sudo apt update
sudo apt install libgtk-3-dev libwebkit2gtk-4.0-dev g++
```

**Fedora**
```bash
sudo dnf install gtk3-devel webkit2gtk3-devel gcc-c++
```

**Arch/Manjaro**
```bash
sudo pacman -S gtk3 webkit2gtk gcc
```

**OpenSUSE**
```bash
sudo zypper install gtk3-devel libwebkit2gtk-4_0-devel gcc-c++
```

If you don't uses any of the above distros then please check there installation guides for the best install.

## Installation of GWebDownloader
GWebDownloader install is a lot easier just use the following commands in your terminal/Konsole or any CLI interface which can give you access to execute commands fo bash or zsh.

```bash
git clone https://github.com/ghgltggamers/GWebDownloader.git
cd GWebDownloader/src
chmod +x build
./build .
```

That's it! now in the <code>GWebDownloader/src/</code> you will see the <code>main</code> file which is the compiled binary of the software. You can move this binary anywhere with <code>bin</code>, <code>config</code> directories, you want and can use it.


## Contributions!
This project accepts the contributions just fork this project and then modify the source code and then leave a pull request and if your contribution is safe then it will be accepted!

## License
Licensed under the MIT LICENSE check the LICENSE file forr more information.

Copyright (c) GWebDownloade 2024
Author ghgltggamer.