TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = libDownload SecondDownloader \
    src/libDialog

libDownload.file = src/libDownload/libDownload.pro

SecondDownloader.file = src/SecondDownloader/SecondDownloader.pro

SecondDownloader.depends += libDownload

