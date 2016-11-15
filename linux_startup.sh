#if you run this hacky script in rc.local for example the sandbox will start at boot.
if [ $(git status) == *"Your branch is up-to-date with"* ] 
then
    echo "update needed"
    git fetch --all
    git reset --hard origin/master
    make
fi

echo "#################- RUNNING SANDBOX -#############################"
xinit &
./bin/sandboxSwarmDebug
