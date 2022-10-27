OS="`uname`"
case $OS in
  'Linux')
    OS='Linux'
    if [$1 -eq 0]
    then
        echo -ne "Server address : "
        ip addr show | grep inet | head -n 3 | tail -n 1 | cut -d '/' -f 1 | cut -d ' ' -f 6
        sudo systemctl stop firewalld.service
        echo -e "Stop Firewall..."
    fi
    if [$1 -eq 1]
    then
        echo -e "Restart Firewall..."
        sudo systemctl start firewalld.service
    fi
    ;;
    'WindowsNT')
    OS='Windows'
esac