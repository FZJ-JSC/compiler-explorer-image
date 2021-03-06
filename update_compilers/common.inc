OPT=/opt/compiler-explorer

set -ex
set -o pipefail
mkdir -p ${OPT}
cd ${OPT}

s3get() {
    aws s3 cp --force $*
}

# Grossly assumes the same proxy for http, https and ftp
fetch() {
    curl -s ${http_proxy:+--proxy $http_proxy} -L "$*"
}

do_unzip() {
    unzip "$*"
}

do_strip() {
    find $1 -executable -type f | xargs strip 2>&1 || true
}

ARG1="$1"

install_nightly() {
    if [[ "$ARG1" = "nightly" ]]; then
        return 0
    else
        return 1
    fi
}

PATCHELF=${OPT}/patchelf-0.8/src/patchelf
