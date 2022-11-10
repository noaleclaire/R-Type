@echo off

if %1 == 1 (
    cd %~dp0
    echo "Stop Firewall..."
    netsh advfirewall set allprofiles state off
    echo | set /p addr="Server address :" > tmp.cache
    ipconfig /all | findstr IPv4 > tmp.cache
)

if %1 == 0 (
    echo "Restart Firewall..."
    netsh advfirewall set allprofiles state on
)