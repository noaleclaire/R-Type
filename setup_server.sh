# OS="`uname`"
# case $OS in
#   'Linux')
#     OS='Linux'
#     if [ $1 -eq 1 ]
#     then
#         sudo systemctl stop firewalld.service
#         ip addr show | grep inet | head -n 3 | tail -n 1 | cut -d '/' -f 1 | cut -d ' ' -f 6 > tmp.cache
#     fi
#     if [ $1 -eq 0 ]
#     then
#         sudo systemctl start firewalld.service
#     fi
# esac