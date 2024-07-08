TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = libDownload SecondDownloader

libDownload.file = src/libDownload/libDownload.pro

SecondDownloader.file = src/SecondDownloader/SecondDownloader.pro

SecondDownloader.depends += libDownload

