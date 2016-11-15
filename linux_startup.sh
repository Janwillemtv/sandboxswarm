#if you run this hacky script in rc.local for example the sandbox will start at boot.
git fetch --all
git reset --hard origin/master
make
xinit &
./bin/sandboxSwarmDebug
