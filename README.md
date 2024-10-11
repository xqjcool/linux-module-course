# linux-module-course
A simple Linux module development course.

## Linux System and Compilation Environment Setup
### Install Multipass and VirtualBox
#### Download and Install Multipass
1. Open your browser and navigate to https://multipass.run/ .
2. Click the "Windows" icon, then click "Download Multipass for Windows" to begin downloading the installer.
3. Double-click the downloaded Multipass installer.
4. Follow the installation process by clicking Next in each step until installation completes.
Note: For Home Edition users, VirtualBox is required.
#### Download and Install VirtualBox
1. Open your browser and navigate to https://www.virtualbox.org/ .
2. Click Download and then choose Windows hosts to download the installer.
3. Double-click the downloaded VirtualBox installer.
4. Follow the installation process by clicking Next to complete the installation.
### Virtual Machine Setup
#### Create a Virtual Machine
multipass launch -n xqjcool -c 2 -m 4G -d 20G --timeout 1800 --network Wi-Fi
#### List all Virtual Machines
multipass list
#### Start/Stop/Suspend a VM
multipass start/stop/suspend VMname
#### Mount Directory to VM Directory
On VM:
mkdir shared_with_win11

On Windows:
create a directory "ubuntu_shared" for share.

Enable multipass mount option:
Run PowerShell as administrator,
multipass set local.privileged-mounts=true

In Windows PowerShell:
multipass mount "D:\ubuntu_shared" xqjcool:/home/ubuntu/shared_with_win11

### Install Compilation Environment
#### Update System
sudo apt update
sudo apt upgrade -y
#### Install Kernel Headers
sudo apt install linux-headers-$(uname -r)
#### Install Development Tools
sudo apt install build-essential
#### Install Kernel Source
sudo apt install linux-source

cd /usr/src/
sudo tar -xvf linux-source-*.tar.bz2

### SSH Key and GitHub
#### Create SSH Key Pair
ssh-keygen -t ed25519 -C "youremaliaddress"

