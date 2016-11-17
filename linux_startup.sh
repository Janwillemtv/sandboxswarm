#if you run this hacky script in rc.local for example the sandbox will start at boot.
exprot DISPLAY=:0
cd /home/janwillem/sandbox/of_v0.9.7_linux64_release/apps/myApps/sandboxswarm/
xrandr --output VGA-1 --mode 1024x768
if [[ $(git status) != *"Your branch is up-to-date with"* ]] 
then
    echo "update needed"
    git fetch --all
    git reset --hard origin/master
    alias gcc='clang'
    alias g++='clang++'
    make
fi

echo "#################- RUNNING SANDBOX -#############################"
xinit &
sleep 2
./bin/sandboxswarm
