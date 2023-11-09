#!/bin/bash

dl_spbu_s_e () {
    curl "$source" -s --compressed -H 'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:109.0) Gecko/20100101 Firefox/118.0' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8' -H 'Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3' -H 'Accept-Encoding: gzip, deflate, br' -H 'DNT: 1' -H 'Connection: keep-alive'
}

dl_spbu_oop () {
    dl_spbu_s_e | grep -o -P "'https://nc\.spbu\.ru/.+?'" | sed "s/'//g" | sort | uniq | { if $probe; then sort -R | head -n 10; else cat; fi; }
                # grep -o -E
}

function download {
    if ! wget "$1/download" -O "$destination$2.zip"; then
        >&2 echo "Cannot download $1"
        return 15
    fi
}

# params
source=https://spbu.ru/sveden/education
destination=./downloads/
probe=false

VALID_ARGS=''
if ! VALID_ARGS=$(getopt -o s:d:p --long source:,destination:,probe -- "$@"); then
    exit 1;
fi

eval set -- "$VALID_ARGS"
while true; do
  case "$1" in
    -s | --source)
        source=$2
        shift 2
        ;;
    -d | --destination)
        destination=$2
        if ! [ "${destination: -1}" = "/" ]; then
            destination="$destination/"
        fi
        shift 2
        ;;
    -p | --probe)
        probe=true
        shift
        ;;
    --) shift; 
        break 
        ;;
  esac
done

mkdir -p "$destination"
count=1
for u in $(dl_spbu_oop); do
    download "${u}" "${count}"
    unzip "$destination${count}.zip" -d "$destination${count}"
    rm "$destination${count}.zip"
    echo $?
    (( count++ ))
done