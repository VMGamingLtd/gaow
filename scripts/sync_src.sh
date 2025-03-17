set -xe
rsync -avz --exclude=.git/ --exclude=uWebSockets/fuzzing/ --exclude='*.o' --exclude='*.exe' --exclude=uWebSockets/uSockets/boringssl/fuzz/  /c/w1/gaow/ root@usrv:/var/www/html/sources/gaow
ssh root@usrv "chown -R www-data:www-data /var/www/html/sources/gaow"
