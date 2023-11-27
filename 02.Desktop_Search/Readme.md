# Desktop Search

[![ShellCheck](https://github.com/kolbacer/MSDTT/actions/workflows/shellcheck.yml/badge.svg)](https://github.com/kolbacer/MSDTT/actions/workflows/shellcheck.yml)

**import_spbu_umd.sh** - a bash script for automated searching, loading, unpacking and indexing informational resources of SPbU.

## Prerequisites
- [**unzip**](https://infozip.sourceforge.net/UnZip.html) - .zip unarchiver
- [**recoll**](https://www.lesbonscomptes.com/recoll/pages/index-recoll.html) - Desktop full text search tool. May require [additional packages](https://www.lesbonscomptes.com/recoll/usermanual/webhelp/docs/RCL.INSTALL.EXTERNAL.html) for some file types (PDF, MS Word, etc).

## Usage

```console
import_spbu_umd [option...]
```

### Options
- <code>-s <i>src</i></code> or <code>--source=<i>src</i></code> - specify the url address from which resources should be downloaded (default is *https://spbu.ru/sveden/education*)
- <code>-d <i>dst</i></code> or <code>--destination=<i>dst</i></code> - specify the directory where resources should be saved (default is *./downloads/*)
- `-p` or `--probe` - if specified, 10 random resources will be downloaded

### Example
```shell 
$ import_spbu_umd -s 'https://spbu.ru/sveden/education' --destination='./folder_to_download_to' -p
```

## Searching

```shell
$ recoll -c ./.recoll -t <your query>
```

Or use a GUI instead.