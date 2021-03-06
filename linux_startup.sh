#if you run this hacky script in rc.local for example the sandbox will start at boot.
export DISPLAY=:0
cd /home/janwillem/sandbox/of_v0.9.7_linux64_release/apps/myApps/sandboxswarm/
git fetch --all
if [[ $(git status) == *"Your branch is behind"* ]] 
then
    echo "update needed"
  
    git reset --hard origin/master
    alias gcc='clang'
    alias g++='clang++'
    make
fi

echo "#################- RUNNING SANDBOX -#############################"
xinit &
export DISPLAY=:0
sleep 6
xrandr --output VGA-0 --mode 1024x768
xset s off         # don't activate screensaver
xset -dpms         # disable DPMS (Energy Star) features.
xset s noblank     # don't blank the video device
./bin/sandboxswarm
reboot
