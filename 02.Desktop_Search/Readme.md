# Desktop Search

[![ShellCheck](https://github.com/kolbacer/MSDTT/actions/workflows/shellcheck.yml/badge.svg)](https://github.com/kolbacer/MSDTT/actions/workflows/shellcheck.yml)

**import_spbu_umd.sh** - a bash script for automated searching, loading and unpacking informational resources of SPbU.

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