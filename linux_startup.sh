#if you run this hacky script in rc.local for example the sandbox will start at boot.
if [ $(/usr/local/bin/git status) == *"Your branch is up-to-date with"* ] 
then
    git fetch --all
    git reset --hard origin/master
    make
fi

xinit &
./bin/sandboxSwarmDebug
