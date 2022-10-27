OS="`uname`"
case $OS in
  'Linux')
    OS='Linux'
    echo -ne "Server address : "
    ip addr show | grep inet | head -n 3 | tail -n 1 | cut -d '/' -f 1 | cut -d ' ' -f 6
    ;;
    'WindowsNT')
    OS='Windows'
esac