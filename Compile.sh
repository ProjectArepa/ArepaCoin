#!/bin/bash
# Script for compile Daemon and WalletQt for ArepaCoin

installAptLibs16Qt() {
    sudo apt-get -y update
    sudo apt-get -y install  \
      qt5-default qt5-qmake qtbase5-dev-tools qttools5-dev-tools software-properties-common build-essential \
      libssl-dev libdb++-dev libboost-all-dev libqrencode-dev qrencode libminiupnpc-dev automake autoconf \
      git pkg-config libcurl4-openssl-dev libjansson-dev libgmp-dev make g++ gcc
}

installAptLibs18Qt() {
    sudo apt-get -y update
    sudo apt-get -y install  \
      qt5-default qt5-qmake qtbase5-dev-tools qttools5-dev-tools software-properties-common build-essential \
      libssl1.0-dev libdb++-dev libboost-all-dev libqrencode-dev qrencode libminiupnpc-dev automake autoconf \
      git pkg-config libcurl-openssl1.0-dev libjansson-dev libgmp-dev make g++ gcc
}

installLibsQt() {
    echo "Installing prerequisites"
    . /etc/os-release
    case "$ID-$VERSION_ID" in
        ubuntu-16.04 ) installAptLibs16 ;;
        ubuntu-18.04 ) installAptLibs18 ;;
        * ) echo "ERROR: only Ubuntu 16.04 or 18.04 are supported now."; exit 1;;
    esac
}

installAptLibs16() {
    sudo apt-get -y update
    sudo apt-get -y install  \
      software-properties-common build-essential \
      libssl-dev libdb++-dev libboost-all-dev libminiupnpc-dev automake autoconf \
      git pkg-config libcurl4-openssl-dev libjansson-dev libgmp-dev make g++ gcc
}

installAptLibs18() {
    sudo apt-get -y update
    sudo apt-get -y install  \
      software-properties-common build-essential \
      libssl1.0-dev libdb++-dev libboost-all-dev libminiupnpc-dev automake autoconf \
      git pkg-config libcurl-openssl1.0-dev libjansson-dev libgmp-dev make g++ gcc
}

installLibs() {
    echo "Installing prerequisites"
    . /etc/os-release
    case "$ID-$VERSION_ID" in
        ubuntu-16.04 ) installAptLibs16 ;;
        ubuntu-18.04 ) installAptLibs18 ;;
        * ) echo "ERROR: only Ubuntu 16.04 or 18.04 are supported now."; exit 1;;
    esac
}

installBerkeleyDB() {
    echo "Installing Berkeley DB"
    sudo env LC_ALL=C.UTF-8 add-apt-repository -y ppa:bitcoin/bitcoin
    sudo apt-get -y update
    sudo apt-get -y install libdb4.8-dev libdb4.8++-dev
}

compileDaemonWallet() {
    echo "Compile Arepa Daemon Wallet"
    cd src
    make -j$(nproc) -f makefile.unix
    strip arepacoind
}

compileQtWallet() {
    echo "Compile Arepa Qt Wallet"
    qmake "USE_QRCODE=1"
    make -j$(nproc)
}

PS3='Please enter your choice: '
options=("Compile Qt Wallet" "Compile Daemon Wallet" "Compile Qt and Daemon Wallet")
select opt in "${options[@]}"
do
    case $opt in
        "Compile Qt Wallet")
            echo "Compile Qt Wallet"
            installLibsQt
            installBerkeleyDB
            compileQtWallet
            echo "Complete!"
            break
            ;;
        "Compile Daemon Wallet")
            echo "Compile Daemon Wallet"
            installLibs
            installBerkeleyDB
            compileDaemonWallet
            echo "Complete!"
            break
            ;;
        "Compile Qt and Daemon Wallet")
            echo "Compile Qt and Daemon Wallet"
            installLibsQt
            installBerkeleyDB
            compileQtWallet
            compileDaemonWallet
            echo "Complete!"
            break
            ;;
        *) echo "invalid option $REPLY";;
    esac
done